#include "safe.hpp"
#include <stdint.h>
#include <iomanip>
#include <sstream>

template <typename T>
std::string ith(T i){
  std::stringstream ss;
  size_t s = (sizeof(T) == 1) ? 1 : sizeof(T);
  ss << std::setfill('0')
    << std::setw(s*2)
    << std::hex
    << (s == 1 ? (uint32_t(i) & 0xff) : i);
  return ss.str();
}
// TODO ciw
class Aes {
  arr_<arr_<uint8_t>> sbox;
  arr_<arr_<uint8_t>> isbox;
  arr_<arr_<uint8_t>> state;

  arr_<uint32_t> expk;
  arr_<uint32_t> rcon;
  void init(){
    uint32_t _t[] = { 0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000,
			0x1b000000, 0x36000000 };
    sbox.alloc2(16, 16);
    isbox.alloc2(16, 16);
    state.alloc2(4, 4);

    expk.alloc(44);
    rcon.alloc(10);
    memcpy(rcon._get_address(), _t, 10*sizeof(uint32_t));
    //rcon.for_each([this](uint32_t & x, size_t & i){
    //  pHex(x);
    //});
    //std::cout << "\n";
  }

  uint8_t rotl8(uint8_t x, uint32_t shift) {
		return (uint8_t) (((x & 0xff) << (shift & 0xff)) | ((x & 0xff) >> (8 - (shift & 0xff))));
	}

  void init_sbox() {
		arr_<uint8_t> a(256);
		arr_<uint8_t> b(256);
		uint8_t p = 1, q = 1;
		do {
			p = (uint8_t) ((p ^ (p << 1)) ^ (((p & 0x80) > 0) ? 0x11b : 0));
			q ^= q << 1;
			q ^= q << 2;
			q ^= q << 4;
			q ^= ((q & 0x80) > 0) ? 0x09 : 0;

			uint8_t xformed = (uint8_t) (q ^ rotl8(q, 1) ^ rotl8(q, 2) ^ rotl8(q, 3) ^ rotl8(q, 4));
			uint32_t temp = (xformed ^ 0x63) & 0xff;
			a[p] = (uint8_t) (temp);
			b[temp] = p;
		} while (p != 1);

		for (uint32_t i = 0; i < 16; i++) {
			for (uint32_t j = 0; j < 16; j++) {
				sbox[i][j] = a[i * 16 + j];
			}
		}

		for (uint32_t i = 0; i < 16; i++) {
			for (uint32_t j = 0; j < 16; j++) {
				isbox[i][j] = b[i * 16 + j];
			}
		}
		sbox[0][0] = 0x63;
    isbox[6][3] = 0x0;

    /*for (uint32_t i = 0; i < 16; i++) {
			for (uint32_t j = 0; j < 16; j++) {
				std::cout << ith(sbox[i][j]) << ' ';
			}
      std::cout << std::endl;
		}
    std::cout << std::endl; 

    for (uint32_t i = 0; i < 16; i++) {
			for (uint32_t j = 0; j < 16; j++) {
				std::cout << ith(isbox[i][j]) << ' ';
			}
      std::cout << std::endl;
		}

    std::cout << std::endl;*/
	}

  uint32_t subword(uint32_t in) {
		// in -> a b c d
		uint32_t temp;
		uint8_t a = (uint8_t) ((in >> 24) & 0xff);
		uint8_t b = (uint8_t) ((in >> 16) & 0xff);
		uint8_t c = (uint8_t) ((in >> 8) & 0xff);
		uint8_t d = (uint8_t) (in & 0xff);
		temp = (sbox[(a & 240) >> 4][a & 15] << 24) | (sbox[(b & 240) >> 4][b & 15] << 16)
				| (sbox[(c & 240) >> 4][c & 15] << 8) | (sbox[(d & 240) >> 4][d & 15]);
		// System.out.println("After subword: " + toHex(temp));
		return temp;
	}

  uint32_t rotword(uint32_t in) {
		uint32_t temp = 0;

		temp |= (in >> 24) & 0x000000ff;
		temp |= (in << 8) & 0xffffff00;
		// System.out.println("After rotword: " + toHex(temp));
		return temp;
	}

  uint32_t pow(uint32_t a, uint32_t b) {
		uint32_t temp = 1;
		for (uint32_t i = 0; i < b; i++) {
			temp *= a;
		}
		// System.out.println(toHex(temp));
		return temp;
	}

  void expand_key(uint8_t * key) {
		uint32_t temp;
		uint32_t i = 0;

		while (i < 4) {
			expk[i] = (key[4 * i] & 0xff) << 24 | (key[4 * i + 1] & 0xff) << 16 | (key[4 * i + 2] & 0xff) << 8
					| (key[4 * i + 3] & 0xff);
			++i;
		}

		i = 4;
		while (i < 44) {
			temp = expk[i - 1];

			if (i % 4 == 0) {
				// System.out.println(toHex(temp));
				// System.out.println("After pow: " + toHex(rcon[(i/4)-1]));
				temp = subword(rotword(temp)) ^ rcon[(i / 4) - 1];
				// System.out.println(pow(2 ,i/4));
			} else {
			}
			expk[i] = expk[i - 4] ^ temp;
			++i;
		}
	}

  void addroundkey(uint32_t expk_start, uint32_t expk_end) {
		uint32_t c = 0;
		for (uint32_t i = expk_start; i <= expk_end; i++) {
			state[0][c] = (uint8_t) (state[0][c] ^ ((expk[i] >> 24) & 0xff));
			state[1][c] = (uint8_t) (state[1][c] ^ ((expk[i] >> 16) & 0xff));
			state[2][c] = (uint8_t) (state[2][c] ^ ((expk[i] >> 8) & 0xff));
			state[3][c] = (uint8_t) (state[3][c] ^ (expk[i] & 0xff));
			++c;
		}
	}

  void subbytes() {
		for(uint32_t i=0;i<4; i++) {
			for(uint32_t j=0;j<4;j++) {
				uint32_t temp = state[i][j] & 0xff;
				state[i][j] = sbox[(temp >> 4) & 0xf][temp & 0xf];
			}
		}
	}

  void shiftrows() {
		arr_<arr_<uint8_t>> temp;
    temp.alloc2(4, 4);

		for(uint32_t i=0; i<4; i++) {
			temp[0][i] = state[0][i];
		}
		for(uint32_t i=0; i<4; i++) {
			temp[1][i] = state[1][(i+1) % 4];
		}
		for(uint32_t i=0; i<4; i++) {
			temp[2][i] = state[2][(i+2) % 4];
		}
		for(uint32_t i=0; i<4; i++) {
			temp[3][i] = state[3][(i+3) % 4];
		}
		for(uint32_t i=0; i<4; i++) {
			for(uint32_t j=0; j<4; j++) {
				state[i][j] = temp[i][j];
			}
		}
	}

  uint32_t mul(uint32_t a, uint32_t b) {
		uint32_t p = 0;
		for(uint32_t i=0; i<8; i++) {
			p ^= -(b & 1) & a;
			uint8_t mask = (uint8_t)((-((a >> 7) & 1)) & 0xff);
			a = (a << 1) ^ (0x011b & mask);
			b >>= 1;
		}
		return p & 0xff;
	}

  void mixcolumns() {
    arr_<arr_<uint8_t>> ss;
    ss.alloc2(4, 4);

		for(uint32_t c=0; c < 4; c++) {
			ss[0][c] = (uint8_t)( (mul(0x02, state[0][c]) ^
					mul(0x03, state[1][c]) ^
					state[2][c] ^
					state[3][c]) & 0xff);
			ss[1][c] = (uint8_t)( (state[0][c] ^
					mul(0x02, state[1][c]) ^
					mul(0x03, state[2][c]) ^
					state[3][c]) & 0xff);
			ss[2][c] = (uint8_t)( (state[0][c] ^
					state[1][c] ^
					mul(0x02, state[2][c]) ^
					mul(0x03, state[3][c])) & 0xff);
			ss[3][c] = (uint8_t)( (mul(0x03, state[0][c]) ^
					state[1][c] ^
					state[2][c] ^
					mul(0x02, state[3][c])) & 0xff);
		}
		state = ss;
	}

  void invshiftrows() {
    arr_<arr_<uint8_t>> temp;
    temp.alloc2(4, 4);
		for(uint32_t i=0; i<4; i++) {
			temp[0][i] = state[0][i];
		}
		for(uint32_t i=0; i<4; i++) {
			temp[1][(i+1) % 4] = state[1][i];
		}
		for(uint32_t i=0; i<4; i++) {
			temp[2][(i+2) % 4] = state[2][i];
		}
		for(uint32_t i=0; i<4; i++) {
			temp[3][(i+3) % 4] = state[3][i];
		}
		for(uint32_t i=0; i<4; i++) {
			for(uint32_t j=0; j<4; j++) {
				state[i][j] = temp[i][j];
			}
		}
	}

  void invsubbytes() {
		for(uint32_t i=0;i<4; i++) {
			for(uint32_t j=0;j<4;j++) {
				uint32_t temp = state[i][j] & 0xff;
				state[i][j] = isbox[(temp >> 4) & 0xf][temp & 0xf];
			}
		}
	}

  void invmixcolumns() {
		arr_<arr_<uint8_t>> ss;
    ss.alloc2(4, 4);
    for(uint32_t c=0; c < 4; c++) {
			ss[0][c] = (uint8_t)( (mul(0x0e, state[0][c]) ^
					 mul(0x0b, state[1][c]) ^
					mul(0x0d, state[2][c]) ^
					mul(0x09, state[3][c])) & 0xff);
			ss[1][c] = (uint8_t)( (mul(0x09, state[0][c]) ^
					mul(0x0e, state[1][c]) ^
			 		mul(0x0b, state[2][c]) ^
					mul(0x0d, state[3][c])) & 0xff);
			ss[2][c] = (uint8_t)( (mul(0x0d, state[0][c]) ^
					mul(0x09, state[1][c]) ^
					mul(0x0e, state[2][c]) ^
					mul(0x0b, state[3][c])) & 0xff);
			ss[3][c] = (uint8_t)( (mul(0x0b, state[0][c]) ^
					mul(0x0d, state[1][c]) ^
					mul(0x09, state[2][c]) ^
					mul(0x0e, state[3][c])) & 0xff);
		}
		state = ss;
	}

public:
  void pHex(uint32_t num){
    std::cout << ith(num) << " ";
  }

  void print_u8(uint8_t num){
    std::cout << ith(num) << " ";
  }
  void set_key(uint8_t * key) {
		expand_key(key);
	}
  void printState() {
		for (int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				print_u8(state[j][i]);
			}
		}
		std::cout << "\n";
	}
  void encrypt(uint8_t * input) {
		//System.out.println(toHex(mul(0x57, 0x83)));
		
		// input: 4 x 4
		// key: 4 by 4
		// out: 4 by 4
		for (uint32_t i = 0; i < 4; i++) {
			for (uint32_t j = 0; j < 4; j++) {
				state[i][j] = input[j * 4 + i];
			}
		}
    //state._try_leak();
		//printState();
		addroundkey(0, 3);
		for(uint32_t i=1; i<10; i++) {
			//printState();
			//System.out.print("---------\n");
			subbytes();
			printState();
			shiftrows();
			printState();
			mixcolumns();
			printState();
			addroundkey(i*4, (i+1)*4-1);
			printState();
		}
		subbytes();
		shiftrows();
		addroundkey(40, 43);
		printState();
	}
  void decrypt(uint8_t * input) {
		for (uint32_t i = 0; i < 4; i++) {
			for (uint32_t j = 0; j < 4; j++) {
				state[i][j] = input[j * 4 + i];
			}
		}
		//printState();
		addroundkey(40, 43);
		for(uint32_t i=9; i>=1; i--) {
			printState();
			//System.out.print("---------\n");
			invshiftrows();
			printState();
			invsubbytes();
			printState();
			addroundkey(i*4, (i+1)*4-1);
			printState();
			invmixcolumns();
			printState();
		}
		invshiftrows();
    printState();
		invsubbytes();
    printState();
		addroundkey(0, 3);
		//printState();
	}

  Aes(){
    init();
    init_sbox();
  }
};
