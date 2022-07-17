#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <conio.h>
//#include <windows.h>


//////////////sha256.hpp//////////////////////////////
//C++ header file
#ifndef _SHA256_HEADER_FILE_AC75F356_AFE1_4F4F_B2D6_10FC42BFA635_
#define _SHA256_HEADER_FILE_AC75F356_AFE1_4F4F_B2D6_10FC42BFA635_

#include <iostream>
#include <stdint.h>

#ifdef MEMLEAK
#define _CRTDBG_MAP_ALLOC 1
#include <stdlib.h>
#include <crtdbg.h>
#endif //MEMLEAK

using namespace std;
//// let's define some things
//// to make it easy to use

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int32_t i32;
typedef int64_t i64;

class sha256{
	bool hash_error;
	char mapping[36];

	u32 K[64];
	u32 H[8];

	//updatable
	u32 H_up[8];
	u64 m_length_up;
	u8 blockOfBytes_up[64];
	u32 blockOfBytes_count;
	//vector<u8> blockOfBytes_up;
	string hashResult_up;

	void resetH();
	string padStringZeroes(string Num, u32 padlength);
	string decToRadix(u32 num, u32 radix);

	u64 mod(i64 a, i64 b);

	//all function needs below here
	//needs to return uint32_t

	u32 rotr(u32 n, u32 x);
	u32 ch(u32 x, u32 y, u32 z);
	u32 maj(u32 x, u32 y, u32 z);

	u32 sigma0(u32 x);
	u32 sigma1(u32 x);
	u32 omega0(u32 x);
	u32 omega1(u32 x);

	void process_block();

	//file accessories
	//string fileHash;

public:
	/**
	\brief The default constructor of sha256.
	*/
	sha256();

	/**
	  \brief This function will take the input and hashes it immediately.
	  \param input The input to be hashed.
	  \return sha256 hash
	*/
	string hash(string input);

	/**
	  \brief Updates the message block. Note that this is part
	         of sha256 update and finalize function.
    \param input The string that will be added to the message block.
	*/
	void hash_update(string input);

	/**
	  \brief Updates the message block. Note that this is part
	         of sha256 update and finalize function.
    \param input The character to be added to the message block.
	*/
	void hash_update(char input);

	/**
	  \brief Updates the message block. Note that this is part
	         of sha256 update and finalize function.
    \param input[] The array of characters to be added to the message block.
    \param input_length The total length of the characters inside the array.
	*/
	void hash_update_array(char input[], u32 input_length);

	/**
	  \brief Updates the message block. Note that this is part
	         of sha256 update and finalize function.
    \param *input The pointer to character array or dynamic array or buffer to be added to the message block.
    \param input_length The total length of the characters inside the array or dynamic array or buffer.
	*/
	void hash_update(char * input, u64 input_length);

	/**
	  \brief Updates the message block. Note that this is part
	         of sha256 update and finalize function.
    \param *input The pointer to character array or dynamic array or buffer to be added to the message block.
    \param input_length The total length of the characters inside the array or dynamic array or buffer.
	\param (*func) The function that will be pass tah will accept parameter as unsigned integer
	*/
	void hash_update(char * input, u64 input_length, void (*func)(u32 percentage));

	/**
	  \brief Updates the message block. Note that this is part
	         of sha256 update and finalize function.

    The function that takes the message block inside and finishes everything inside of it.
    It hashes the message block's final content. Now the all you need to do is to collect the
    hash by calling the hash_result().
	*/
	void hash_finalize();

	/**
	  \brief After finalizing the hash, get the result as a string
	  \return sha256 hash
	*/
	string hash_result();
};


#endif //_SHA256_HEADER_FILE_AC75F356_AFE1_4F4F_B2D6_10FC42BFA635_

//////////////////////////////////////////////////////
//////////////sha256.cpp//////////////////////////////
//C++ file
//#include "sha256.hpp"

#ifdef _SHA256_HEADER_FILE_AC75F356_AFE1_4F4F_B2D6_10FC42BFA635_
#include <exception>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;
//// let's define some things
//// to make it easy to use

string sha256::padStringZeroes(string Num, u32 padlength){
  u32 length = u32(Num.length());
  while(length < padlength){
    Num = "0" + Num;
    length++;
  }
  return Num;
}

string sha256::decToRadix(u32 num, u32 radix){
  string rem;
  u32 temp = 0;
  stringstream ss;
  string result = "";
  while(num > 0){
    temp = num % radix;
    result = mapping[temp] + result;
    num = num / radix;
  }
  if(result == "")
  {
    result = "0";
  }
  return result;
}

void sha256::resetH(){
  H[0] = 0x6a09e667;
  H[1] = 0xbb67ae85;
  H[2] = 0x3c6ef372;
  H[3] = 0xa54ff53a;
  H[4] = 0x510e527f;
  H[5] = 0x9b05688c;
  H[6] = 0x1f83d9ab;
  H[7] = 0x5be0cd19;
}

u64 sha256::mod(i64 a, i64 b){
  i64 temp = a % b;
  while(temp < 0){
    temp += b;
  }
  return (u64)(temp);
}

//all function needs below here
//needs to return uint32_t

u32 sha256::rotr(u32 n, u32 x){
  return (x >> n) | (x << (32 - n));
}

u32 sha256::ch(u32 x, u32 y, u32 z){
  return (x & y) ^ (~x & z);
}

u32 sha256::maj(u32 x, u32 y, u32 z){
  return (x & y) ^ (x & z) ^ (y & z);
}

u32 sha256::sigma0(u32 x){
  return ((x >> 2) | (x << 30)) ^ ((x >> 13) | (x << 19)) ^ ((x >> 22) | (x << 10));
  //return rotr(2,x) ^ rotr(13,x) ^ rotr(22,x);
}

u32 sha256::sigma1(u32 x){
  return ((x >> 6) | (x << 26)) ^ ((x >> 11) | (x << 21)) ^ ((x >> 25) | (x << 7));
  //return rotr(6,x) ^ rotr(11,x) ^ rotr(25,x);
}

u32 sha256::omega0(u32 x){
  return ((x >> 7) | (x << 25)) ^ ((x >> 18) | (x << 14)) ^ (x >> 3);
  //return rotr(7,x) ^ rotr(18,x) ^ (x >> 3);
}

u32 sha256::omega1(u32 x){
  return ((x >> 17) | (x << 15)) ^ ((x >> 19) | (x << 13)) ^ (x >> 10);
  //return rotr(17,x) ^ rotr(19,x) ^ (x >> 10);
}

////sha256 constructor
sha256::sha256(){
	char * _mapping = "0123456789abcdefghijklmnopqrstuvwxyz";
	memcpy(mapping, _mapping, strlen(_mapping));
	////this constructor initializes the sha256 hash function
	hash_error = false;

	u32 K_[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
  };

  for(u32 m=0; m<64; m++){
    K[m] = K_[m];
  }

  m_length_up = 0;
  blockOfBytes_count = 0;

  H_up[0] = 0x6a09e667;
  H_up[1] = 0xbb67ae85;
  H_up[2] = 0x3c6ef372;
  H_up[3] = 0xa54ff53a;
  H_up[4] = 0x510e527f;
  H_up[5] = 0x9b05688c;
  H_up[6] = 0x1f83d9ab;
  H_up[7] = 0x5be0cd19;
}
///================================================================================///
///                            SHA-256 IMPLEMENTATION                              ///
///================================================================================///

string sha256::hash(string input){
	////resetH
  resetH();
  ////the actual message
  vector<u8> message_blocks;
  ////storage of length of message
  u64 a_length = input.length();
  u64 m_length = a_length * 8;
  ////cout << m_length;

  ////convert characters into group
  ////of bytes
  vector<u8> blockOfBytes;
  for(u64 ia=0; ia<a_length; ia++){
    blockOfBytes.push_back(input[ia]);
  }
  ////this is known to be 8 bytes
  u8 blockOfLength[8];

  ////we store the 64 bit length
  ////into 8 bytes using big endian order
  for(u32 lb=0; lb < 8; lb++){
    blockOfLength[lb] = (m_length >> ((7-lb)*8)) & 255;
    ////cout << " " << (u32)blockOfLength[lb];
  }

  ////the number of zeroes between the message
  ////and the length in bytes
  vector<u8> blockOfZeroes;
  u64 numberOfBlockOfZeroes = (mod((448-(m_length+1)), 512) + 1) / 8;

  ////store the zeroes in bytes
  ////note that the first block of zero
  ////will contain 128
  ////see below
  for(u64 nb=0; nb<numberOfBlockOfZeroes; nb++){
    blockOfZeroes.push_back(0);
  }

  ////add 1 bit plus 7 zeroes
  blockOfZeroes[0] = 128;

  ////Now concatenate the message, zeros and length
  ////in bytes, respectively
  for(u32 ij = 0; ij < blockOfBytes.size(); ij++){
    message_blocks.push_back(blockOfBytes[ij]);
  }

  for(u32 ij = 0; ij < blockOfZeroes.size(); ij++){
    message_blocks.push_back(blockOfZeroes[ij]);
  }

  for(u32 ij = 0; ij < 8; ij++){
    message_blocks.push_back(blockOfLength[ij]);
  }

  ////should be a multiple of 64
  ////cout << "Sizeof message " << message_blocks.size() << endl;

  ////create the main message block which
  ////is the M block
  ////note that this a 2d array,
  ////where each item in M[] will contain
  ////x16 32bits which is the padded message
  vector<vector<u32>> M;
  ////this will be always 16 in .size()
  vector<u32> tempa;
  u32 message_blocks_length = message_blocks.size() * 8;
  u32 lastIndex = 0;

  ////a strategy for storing 32bits padded message
  ////inside a 2d array
  ////will be re-factored soon...
  for(u32 ib=0; ib<message_blocks_length; ib+=512){
    tempa.clear();
    for(u32 j=0; j<64; j+=4){
      u32 word = (message_blocks[lastIndex+j] << 24) | (message_blocks[lastIndex+j+1] << 16) | (message_blocks[lastIndex+j+2] << 8) | (message_blocks[lastIndex+j+3]);
      tempa.push_back(word);
    }
    lastIndex += 64;
    M.push_back(tempa);
  }

  ////cout << M[0].size() << endl;
  ////THE MAIN PROCEDURE

  u32 a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,t1=0,t2 =0,M_length = M.size();

  ////THE MAIN LOOP
  for(u32 i = 0; i < M_length; i++){
    ////Initialize the working schedule
    ////This will use the M[], which is
    ////the 2d array being stored while
    ////extending it's content to 64,
    ////that means, W[] total size is 64
    vector<u32> W;
    u32 temp = 0;

    ////the working schedule loop
    for(u32 tb = 0; tb<64; tb++){
      if(tb < 16){
        W.push_back(M[i][tb]);
      }else{
        temp = (omega1(W[tb-2]) + W[tb-7] + omega0(W[tb-15]) + W[tb-16]);
        W.push_back(temp);
      }
    }

    ////initialize the 8 variables
    ////using the H[] table
    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
    e = H[4];
    f = H[5];
    g = H[6];
    h = H[7];

    ////the compression function, which will be done
    ////64 times for each working schedule
    for(u32 t=0; t<64; t++){
      t1 = h + sigma1(e) + ch(e,f,g) + K[t] + W[t];
      t2 = sigma0(a) + maj(a,b,c);
      h = g;
      g = f;
      f = e;
      e = d + t1;
      d = c;
      c = b;
      b = a;
      a = t1 + t2;
    }

    ////modify the content of the H[] table
    H[0] = (a + H[0]);
    H[1] = (b + H[1]);
    H[2] = (c + H[2]);
    H[3] = (d + H[3]);
    H[4] = (e + H[4]);
    H[5] = (f + H[5]);
    H[6] = (g + H[6]);
    H[7] = (h + H[7]);
  }

  ////after  the main loop, output
  ////the contents of the H[] table
  string output = "";
  for(u32 ic=0; ic<8; ic++){
    string tempb = decToRadix(H[ic], 16);
    output += padStringZeroes(tempb, 8);
  }

  return output;
}

void sha256::process_block(){
  ////cout << "DEBUG - PROCESSING M BLOCK" << endl;
  u32 a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,t1=0,t2 =0;
  u32 W[64];

  W[0] = (blockOfBytes_up[0] << 24) | (blockOfBytes_up[1] << 16) | (blockOfBytes_up[2] << 8) | (blockOfBytes_up[3]);
  W[1] = (blockOfBytes_up[4] << 24) | (blockOfBytes_up[5] << 16) | (blockOfBytes_up[6] << 8) | (blockOfBytes_up[7]);
  W[2] = (blockOfBytes_up[8] << 24) | (blockOfBytes_up[9] << 16) | (blockOfBytes_up[10] << 8) | (blockOfBytes_up[11]);
  W[3] = (blockOfBytes_up[12] << 24) | (blockOfBytes_up[13] << 16) | (blockOfBytes_up[14] << 8) | (blockOfBytes_up[15]);

  W[4] = (blockOfBytes_up[16] << 24) | (blockOfBytes_up[17] << 16) | (blockOfBytes_up[18] << 8) | (blockOfBytes_up[19]);
  W[5] = (blockOfBytes_up[20] << 24) | (blockOfBytes_up[21] << 16) | (blockOfBytes_up[22] << 8) | (blockOfBytes_up[23]);
  W[6] = (blockOfBytes_up[24] << 24) | (blockOfBytes_up[25] << 16) | (blockOfBytes_up[26] << 8) | (blockOfBytes_up[27]);
  W[7] = (blockOfBytes_up[28] << 24) | (blockOfBytes_up[29] << 16) | (blockOfBytes_up[30] << 8) | (blockOfBytes_up[31]);

  W[8] = (blockOfBytes_up[32] << 24) | (blockOfBytes_up[33] << 16) | (blockOfBytes_up[34] << 8) | (blockOfBytes_up[35]);
  W[9] = (blockOfBytes_up[36] << 24) | (blockOfBytes_up[37] << 16) | (blockOfBytes_up[38] << 8) | (blockOfBytes_up[39]);
  W[10] = (blockOfBytes_up[40] << 24) | (blockOfBytes_up[41] << 16) | (blockOfBytes_up[42] << 8) | (blockOfBytes_up[43]);
  W[11] = (blockOfBytes_up[44] << 24) | (blockOfBytes_up[45] << 16) | (blockOfBytes_up[46] << 8) | (blockOfBytes_up[47]);

  W[12] = (blockOfBytes_up[48] << 24) | (blockOfBytes_up[49] << 16) | (blockOfBytes_up[50] << 8) | (blockOfBytes_up[51]);
  W[13] = (blockOfBytes_up[52] << 24) | (blockOfBytes_up[53] << 16) | (blockOfBytes_up[54] << 8) | (blockOfBytes_up[55]);
  W[14] = (blockOfBytes_up[56] << 24) | (blockOfBytes_up[57] << 16) | (blockOfBytes_up[58] << 8) | (blockOfBytes_up[59]);
  W[15] = (blockOfBytes_up[60] << 24) | (blockOfBytes_up[61] << 16) | (blockOfBytes_up[62] << 8) | (blockOfBytes_up[63]);

  for(u32 tb = 16; tb<64; tb++){
    W[tb] = (omega1(W[tb-2]) + W[tb-7] + omega0(W[tb-15]) + W[tb-16]);
  }

  a = H_up[0];
  b = H_up[1];
  c = H_up[2];
  d = H_up[3];
  e = H_up[4];
  f = H_up[5];
  g = H_up[6];
  h = H_up[7];

  ////cout << "DEBUG - MAIN LOOP STARTED" << endl;

  for(u32 t=0; t<64; t++){
    t1 = h + sigma1(e) + ch(e,f,g) + K[t] + W[t];
    t2 = sigma0(a) + maj(a,b,c);
    h = g;
    g = f;
    f = e;
    e = d + t1;
    d = c;
    c = b;
    b = a;
    a = t1 + t2;
  }

  H_up[0] += a;
  H_up[1] += b;
  H_up[2] += c;
  H_up[3] += d;
  H_up[4] += e;
  H_up[5] += f;
  H_up[6] += g;
  H_up[7] += h;
}

void sha256::hash_update(string input){
  ////get the input
  u64 lx = input.length();
  for(u32 jx=0; jx<lx; jx++){
    blockOfBytes_up[blockOfBytes_count++] = input[jx];
    if(blockOfBytes_count == 64){
      process_block();
      blockOfBytes_count = 0;
    }
  }
  ////compute new length
  m_length_up = m_length_up + (lx * 8);
}

void sha256::hash_update(char input){
  blockOfBytes_up[blockOfBytes_count++] = input;
  if(blockOfBytes_count == 64){
    process_block();
    blockOfBytes_count = 0;
  }
  m_length_up += 8;
}

void sha256::hash_update_array(char input[], u32 input_length){
  try{
    for(u32 jx=0; jx<input_length; jx++){
      blockOfBytes_up[blockOfBytes_count++] = input[jx];
      if(blockOfBytes_count == 64){
        process_block();
        blockOfBytes_count = 0;
      }
    }

    m_length_up = m_length_up + (input_length * 8);
  }catch(exception& e){
    ////cerr << "An error occured while updating. Error type: " << e.what() << endl;
    hashResult_up = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    hash_error = true;

    //clean up
    //blockOfBytes_up.clear();
    blockOfBytes_count = 0;
    m_length_up = 0;
  }
}

void sha256::hash_update(char * input, u64 input_length){
  try{
    for(u64 jx=0; jx<input_length; jx++){
      blockOfBytes_up[blockOfBytes_count++] = input[jx];
      if(blockOfBytes_count == 64){
        process_block();
        blockOfBytes_count = 0;
      }
    }

    m_length_up = m_length_up + (input_length * 8);
  }catch(exception& e){
    ////cerr << "An error occured while updating. Error type: " << e.what() << endl;
    hashResult_up = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    hash_error = true;

    //clean up
        //blockOfBytes_up.clear();
    blockOfBytes_count = 0;
    m_length_up = 0;
  }
}

void sha256::hash_update(char * input, u64 input_length, void (*func)(u32 percentage)){
  u64 m = input_length / 100;
  m = (m > 0) ? m : 1;
  double ab = 0, cd = input_length;
  try{
    for(u64 jx=0; jx<input_length; jx++){
      blockOfBytes_up[blockOfBytes_count++] = input[jx];
      if(blockOfBytes_count == 64){
        process_block();
        blockOfBytes_count = 0;
      }
	  if( (jx+1) % m == 0 ){
		ab = (jx+1);
		ab = ab / cd * 100;
		(*func)((u32)ab);
	  }
    }

    m_length_up = m_length_up + (input_length * 8);
  }catch(exception& e){
    ////cerr << "An error occured while updating. Error type: " << e.what() << endl;
    hashResult_up = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    hash_error = true;

    //clean up
        //blockOfBytes_up.clear();
    blockOfBytes_count = 0;
    m_length_up = 0;
  }
}

void sha256::hash_finalize(){
  if(hash_error){
    hash_error = false;
    ////cerr << "DEBUG - ERROR HASHING" << endl;
    return ;
  }
  ////cout << "DEBUG - FINALIZING" << endl;
  u32 end_count = (blockOfBytes_count < 56) ? 56 : 64;
  u32 start_zero = blockOfBytes_count;
  ////cout << "Start of zero is " << start_zero << endl;

  ////cout << "Block of bytes is " << start_zero << endl;
  //START OF PADDING ZEROES
  blockOfBytes_up[start_zero] = 128;

  for(u32 sz = (start_zero + 1); sz < end_count; sz++){
    blockOfBytes_up[sz] = 0;
  }
  //END OF PADDING

  if(blockOfBytes_count >= 56){
    ////cout << "Verifying" << endl;
    process_block();
    //CLEANING LEFT OVER
    //This is only done if blockOfBytes_count < 56
    //or starting from index 0 to 55
    for(u32 ch=0; ch < 56; ch++){
      blockOfBytes_up[ch] = 0;
    }
    //END OF CLEANING LEFT OVER
  }

  blockOfBytes_up[56] = (m_length_up >> 56) & 255;
  blockOfBytes_up[57] = (m_length_up >> 48) & 255;
  blockOfBytes_up[58] = (m_length_up >> 40) & 255;
  blockOfBytes_up[59] = (m_length_up >> 32) & 255;

  blockOfBytes_up[60] = (m_length_up >> 24) & 255;
  blockOfBytes_up[61] = (m_length_up >> 16) & 255;
  blockOfBytes_up[62] = (m_length_up >> 8) & 255;
  blockOfBytes_up[63] = m_length_up & 255;

  process_block();


  ////cout << "DEBUG - COLLECTING HASH STARTED" << endl;
  string tempb;
  hashResult_up = "";

  tempb = decToRadix(H_up[0], 16);
  hashResult_up += padStringZeroes(tempb, 8);

  tempb = decToRadix(H_up[1], 16);
  hashResult_up += padStringZeroes(tempb, 8);

  tempb = decToRadix(H_up[2], 16);
  hashResult_up += padStringZeroes(tempb, 8);

  tempb = decToRadix(H_up[3], 16);
  hashResult_up += padStringZeroes(tempb, 8);

  tempb = decToRadix(H_up[4], 16);
  hashResult_up += padStringZeroes(tempb, 8);

  tempb = decToRadix(H_up[5], 16);
  hashResult_up += padStringZeroes(tempb, 8);

  tempb = decToRadix(H_up[6], 16);
  hashResult_up += padStringZeroes(tempb, 8);

  tempb = decToRadix(H_up[7], 16);
  hashResult_up += padStringZeroes(tempb, 8);

  ////cout << "DEBUG - HASHING DONE" << endl;
  //reset H_tables
  H_up[0] = 0x6a09e667;
  H_up[1] = 0xbb67ae85;
  H_up[2] = 0x3c6ef372;
  H_up[3] = 0xa54ff53a;
  H_up[4] = 0x510e527f;
  H_up[5] = 0x9b05688c;
  H_up[6] = 0x1f83d9ab;
  H_up[7] = 0x5be0cd19;
  //reset blockOfbytes
  ////cout << "DEBUG - PERFORMING CLEAN UP" << endl;
  //blockOfBytes_up.clear();
  blockOfBytes_count = 0;
  m_length_up = 0;
}

string sha256::hash_result(){
  return hashResult_up;
}

#endif //_SHA256_HEADER_FILE_AC75F356_AFE1_4F4F_B2D6_10FC42BFA635_

//////////////////////////////////////////////////////
#ifdef _WIN32
  #include <windows.h>
#endif // _WIN32

#define GREEN 0
#define RED 1
#define ORANGE 2
#define YELLOW 3
#define CYAN_BLUE 4
#define BRIGHT_WHITE 5
#define NORMALIZE 6

using namespace std;

/**
  colorize the console
  0 - green - good
  1 - red   - error
  2 - orange - warning
  3 - yellow - info
  4 - cyan blue
  5 - bright white
  6 - normalize (default)
*/
void colorize(long color_coding){
  #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  #else

  #endif // _WIN32

  switch(color_coding){
    case GREEN:
      #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, 10);
      #else
        std::cout << "\033[1;92m";
      #endif // _WIN32
    break;
    case RED:
      #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, 12);
      #else
        std::cout << "\033[1;91m";
      #endif // _WIN32
    break;
    case ORANGE:
      #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, 12);
      #else
        std::cout << "\033[1;91m";
      #endif // _WIN32
    break;
    case YELLOW:
      #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, 14);
      #else
        std::cout << "\033[1;93m";
      #endif // _WIN32
    break;
    case CYAN_BLUE:
      #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, 11);
      #else
        std::cout << "\033[1;96m";
      #endif // _WIN32
    break;
    case BRIGHT_WHITE:
      #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, 15);
      #else
        std::cout << "\033[1;97m";
      #endif // _WIN32
    break;
    case NORMALIZE:
      #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, 7);
      #else
        std::cout << "\033[0m";
      #endif // _WIN32
    break;
  }
}

const char * mapping = "0123456789abcdefghijklmnopqrstuvwxyz";

long ERROR_CODE_RAISED = 0;
long ERROR_END_OF_FILE = 0;
long ERROR_MEMORY_UNALLOCATED = 123456;
long GLOBAL_HEX_LENGTH = 0;
long EDIT_MODE = 0;

string editModeFileName = "";

/*
void printChar(const wchar_t * c){
  WriteConsoleW(hConsole, c, 1, NULL, NULL);
}*/

bool IsHex(string num){
  if(num.substr(0,  2) == "0x")
  {
    return true;
  }
  return false;
}

long POWER(long a, long b){
  long result = 1;
  for(int i = 0; i < b; i++){
    result *= a;
  }
  return result;
}

int hexDigitToDecDigit(char digit){
  int result = digit - '0';
  if(result > -1 && result < 10){
    return result;
  }else{
    switch (result)
    {
    case 49:
    case 17:
      return 10;
    case 50:
    case 18:
      return 11;
    case 51:
    case 19:
      return 12;
    case 52:
    case 20:
      return 13;
    case 53:
    case 21:
      return 14;
    case 54:
    case 22:
      return 15;
    }
  }
  return 0;
}

long hexToDec(string hexNum){
  long length = long(hexNum.length());
  long power = length - 1;
  long result = 0;
  long tmp;
  int i;
  for(i = 0; i < length; i++){
    if(hexNum[i] == '0'){
      power -= 1;
      continue;
    }
    tmp = long(hexDigitToDecDigit(hexNum[i]));
    result += (tmp * POWER(16, power));
    power -= 1;
  }
  return result;
}

long stringToDec(string Num){
  long length = long(Num.length());
  long power = length - 1;
  long result = 0;
  long tmp;
  int i;
  for(i = 0; i < length; i++){
    if(Num[i] == '0'){
      power -= 1;
      continue;
    }
    tmp = Num[i] - '0';
    result += (tmp * POWER(10, power));
    power -= 1;
  }
  return result;
}

string charToRadix(unsigned char symbol, int radix){
  int num = int(symbol);
  string rem;
  int temp = 0;
  stringstream ss;
  string result = "";
  while(num > 0){
    temp = num % radix;
    result = mapping[temp] + result;
    num = num / radix;
  }
  if(result == ""){
    result = "0";
  }
  return result;
}

string decToRadix(int num, int radix){
  string rem;
  int temp = 0;
  stringstream ss;
  string result = "";
  while(num > 0){
    temp = num % radix;
    result = mapping[temp] + result;
    num = num / radix;
  }
  if(result == "")
  {
    result = "0";
  }
  return result;
}

string padStringZeroes(string Num, int padlength){
  int length = int(Num.length());
  while(length < padlength){
    Num = "0" + Num;
    length++;
  }
  return Num;
}

//START OF HEX EDITOR MAIN FUNCTIONS



int writeHex(fstream * file, long address, char charByte){
  if(address < 0){
    ERROR_CODE_RAISED = ERROR_MEMORY_UNALLOCATED;

    colorize(RED);
    cout << "An Error Occurred." << endl;
    colorize(NORMALIZE);
    exit(3);
  }
  file->seekp(address);
  if(file->eof()){
    file->clear();
    return 1;
  }
  file->put(charByte);
  return 0;
}

char * readHex(ifstream * file, long start, long ends){
  long length = ends - start + 1;

  if(start < 0 || ends < 0 || start > ends){
    ERROR_CODE_RAISED = ERROR_MEMORY_UNALLOCATED;
    colorize(RED);
    cout << "An Error Occurred." << endl;
    colorize(NORMALIZE);
    exit(3);
  }

  //long address = start;
  char * arr = new char[length];
  char store;

  if(arr == 0){
    ERROR_CODE_RAISED = ERROR_MEMORY_UNALLOCATED;
    colorize(RED);
    cout << "An Error Occurred." << endl;
    colorize(BRIGHT_WHITE);
  }else{
    long i;
    file->seekg(start);
    for(i = 0; i < length; i++){
      if(file->eof()){
        file->clear();
        GLOBAL_HEX_LENGTH = i-1;
        ERROR_END_OF_FILE = 1;
        return arr;
      }else{
        file->get(store);
        arr[i] = store;
      }
    }
    GLOBAL_HEX_LENGTH = i-1;
  }
  return arr;
}

//START OF HEX EDITOR FUNCTIONS
void clearErrors(){
  ERROR_CODE_RAISED = 0;
  GLOBAL_HEX_LENGTH = 0;
  ERROR_END_OF_FILE = 0;
}

string askFileName(){
  clearErrors();
  string name;
  cout << "Enter your file name: " ;
  getline(cin, name);
  int nameLength = name.length();
  if(name[0] == '"' && name[nameLength - 1] == '"')
  {
    name = name.substr(1, nameLength - 2);
  }
  return name;
}

void editModeFile(){
  editModeFileName = askFileName();
}

void editModeSnapView(long addressHex){
  ifstream file;
  file.open(editModeFileName.c_str(), ios::binary);
  if(file.is_open()){
    string hexStart;
    string hexEnd;
    long start = 0;
    long ends = 0;
    char * tape;

    start = addressHex;
    ends = addressHex + 1;

    tape = readHex(&file, start, ends);
    if(ERROR_CODE_RAISED == ERROR_MEMORY_UNALLOCATED){
      system("pause");
      exit(0);
    }

    if(ERROR_END_OF_FILE){
      colorize(RED);
      cout << "0x??";
      colorize(BRIGHT_WHITE);
    }else{
      cout << "0x" << padStringZeroes(charToRadix(tape[0], 16), 2);
    }
    delete[] tape;
    file.close();
    cout << endl;
  }else{
    colorize(RED);
    cout << "xx" << endl;
    colorize(BRIGHT_WHITE);
  }
}

void editModeView(){
  ifstream file;
  file.open(editModeFileName.c_str(), ios::binary);
  int counter = 0;
  int lineNumber = 0;
  int k = GREEN;
  if(file.is_open())
  {
    string hexStart;
    string hexEnd;
    long start = 0;
    long ends = 0;
    long length = 0;
    char * tape;
    unsigned char crap;
    cout << "start> ";
    cin >> hexStart;

    if(IsHex(hexStart)){
      hexStart = hexStart.substr(2, 100);
      start = hexToDec(hexStart);
    }else{
      start = stringToDec(hexStart);
    }

    cin.ignore();
    cout << "end> ";
    cin >> hexEnd;

    if(IsHex(hexEnd)){
      hexEnd = hexEnd.substr(2, 100);
      ends = hexToDec(hexEnd)+1;
    }else{
      ends = stringToDec(hexEnd)+1;
    }


    cin.ignore();
    tape = readHex(&file, start, ends);
    if(ERROR_CODE_RAISED == ERROR_MEMORY_UNALLOCATED)
    {
        system("pause");
        exit(0);
    }
    length = GLOBAL_HEX_LENGTH;

    cout << "Hex> " << endl;
    colorize(CYAN_BLUE);
    cout << "Offset (h)  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --" << endl;
    lineNumber = int(start);
    for(int i = 0; i < length; i++){
      if(counter == 0){
        colorize(YELLOW);
        cout << "0x" << padStringZeroes(decToRadix(lineNumber, 16), 8) << ": ";
      }
      counter += 1;
      colorize(k);
      crap = tape[i];
      cout << padStringZeroes(charToRadix(crap, 16), 2) << " ";
      k = k == GREEN ? NORMALIZE : GREEN;
      if(counter % 16 == 0){
        counter = 0;
        lineNumber+= 16;
        cout << endl;
      }
    }
    k = k == GREEN ? NORMALIZE : GREEN;
    colorize(k == GREEN ? NORMALIZE : GREEN);
    if(ERROR_END_OF_FILE){
      colorize(RED);
      cout << "??";
      colorize(BRIGHT_WHITE);
    }
    delete[] tape;
    file.close();
    cout << endl;
  }else{
    colorize(RED);
    cout << "File Error>" << endl;
    colorize(BRIGHT_WHITE);
  }
}

void editModeCharView(){
  ifstream file;
  file.open(editModeFileName.c_str(), ios::binary);
  int counter = 0;
  int lineNumber = 0;
  int k = GREEN;
  //wchar_t iChar;
  //int charTest = 0;
  if(file.is_open()){
    string hexStart;
    string hexEnd;
    long start = 0;
    long ends = 0;
    long length = 0;
    char * tape;
    unsigned char crap;
    cout << "start> ";
    cin >> hexStart;

    if(IsHex(hexStart)){
      hexStart = hexStart.substr(2, 100);
      start = hexToDec(hexStart);
    }else{
      start = stringToDec(hexStart);
    }

    cin.ignore();
    cout << "end> ";
    cin >> hexEnd;

    if(IsHex(hexEnd)){
      hexEnd = hexEnd.substr(2, 100);
      ends = hexToDec(hexEnd)+1;
    }else{
        ends = stringToDec(hexEnd)+1;
    }

    cin.ignore();
    tape = readHex(&file, start, ends);
    if(ERROR_CODE_RAISED == ERROR_MEMORY_UNALLOCATED){
      system("pause");
      exit(0);
    }
    length = GLOBAL_HEX_LENGTH;

    cout << "Hex> " << endl;
    colorize(CYAN_BLUE);
    cout << "Offset (h)  - - - - - - - - - - - - - - - -" << endl;
    lineNumber = int(start);
    for(int i = 0; i < length; i++){
      if(counter == 0){
        colorize(YELLOW);
        cout << "0x" << padStringZeroes(decToRadix(lineNumber, 16), 8) << ": ";
      }
      counter += 1;
      colorize(k);
      crap = tape[i];
      //setvbuf(stdout, NULL, _IONBF, 0);
      //printChar((crap > 31 ? char(crap) : '.'));
      //cout << " ";
      //wchar_t _how = crap;
      //cout << crap << endl;
      //charTest = int(crap);
      //string aba = crap + "";
      //wchar_t* str = L(a)
      //const wchar_t abac = static_cast<wchar_t>(crap);
      //printChar(&abac);
      //iChar = static_cast<wchar_t>(crap);
      //MultiByteToWideChar(CP_UTF8, 0, buf)
      if(crap > 31){
        cout << (char)(crap);
        //printChar(&abac);
      }else{
        cout << ".";
      }
      //(crap > 31 ? printChar(&iChar) : printChar('.\0'));
      //cout << "=" << charTest;
      //cout << flush;
      cout << " ";
      //cout << flush;
      k = k == GREEN ? NORMALIZE : GREEN;
      if(counter % 16 == 0){
        counter = 0;
        lineNumber+= 16;
        cout << endl;
      }
      //cout << flush;
    }
    k = k == GREEN ? NORMALIZE : GREEN;
    colorize(k == GREEN ? NORMALIZE : GREEN);
    if(ERROR_END_OF_FILE){
      colorize(RED);
      cout << "??";
      colorize(BRIGHT_WHITE);
    }
    delete[] tape;
    file.close();
    cout << endl;
  }else{
    colorize(RED);
    cout << "File Error>" << endl;
    colorize(BRIGHT_WHITE);
  }
  //cout << flush;
}

void editModeReplace(){
  fstream fileStream(editModeFileName.c_str(), ios::in | ios::out| ios::binary);
  if(fileStream.is_open()){
    long address = 0;
    int value;
    char finalValue;
    string hexNum;
    string Value;

    cout << "address> ";
    getline(cin, hexNum);

    if(IsHex(hexNum)){
      hexNum = hexNum.substr(2, 100);
      address = hexToDec(hexNum);
    }else{
      address = stringToDec(hexNum);
    }

    cout << "value> ";
    cin >> Value;
    if(IsHex(Value)){
      Value = Value.substr(2, 100);
      value = hexToDec(Value);
    }else{
      value = stringToDec(Value);
    }

    cin.ignore();
    finalValue = (value % 256);

    if(writeHex(&fileStream, address, finalValue)){
      colorize(RED);
      cout << "EOF>" << endl;
      colorize(BRIGHT_WHITE);
    }

    fileStream.close();

  }else{
    colorize(RED);
    cout << "File Error>" << endl;
    colorize(BRIGHT_WHITE);
  }
}

void editModeSha256(){
  sha256 sh;
  ifstream filex(editModeFileName.c_str(), ios::binary | ios::ate);
  u64 sizex;
  char * inp = nullptr;

  if(filex.is_open()){
    sizex = (u64)filex.tellg();
    inp = new (nothrow) char[sizex];
    if(inp == 0){
      colorize(RED);
      cout << "Allocation Error, the file cannot be hashed." << endl;
      colorize(BRIGHT_WHITE);
      return ;
    }
    filex.seekg(0, ios::beg);
    filex.read(inp, sizex);
    filex.close();
    cout << "File hashing started..." << endl;
    sh.hash_update(inp, sizex);
    sh.hash_finalize();
    colorize(GREEN);
    cout << sh.hash_result();
    cout << endl;
    delete [] inp;
    colorize(BRIGHT_WHITE);
  }else{
    colorize(RED);
    cout << "Hashing error." << endl;
    colorize(BRIGHT_WHITE);
  }
}

void editMode(){
  string cmd = "";
  EDIT_MODE = 1;
  cout << "Type HELP for help, END for exit" << endl;
  while(EDIT_MODE){
    clearErrors();
    cout << "> ";
    getline(cin, cmd);
    if(cmd == "EXIT" || cmd == "exit" || cmd == "END" || cmd == "end"){
      EDIT_MODE = 0;
    }else if(cmd == "FILE" || cmd == "file"){
      editModeFile();
    }else if(cmd == "VIEW" || cmd == "view"){
      editModeView();
    }else if(cmd == "REPLACE" || cmd == "replace" || cmd == "REPL" || cmd == "repl"){
      editModeReplace();
    }else if(cmd == "CHAR" || cmd == "char"){
      editModeCharView();
    }else if(cmd == "sha256" || cmd == "SHA256"){
      editModeSha256();
    }else if(IsHex(cmd)){
      editModeSnapView(hexToDec(cmd));
    }else if(cmd == "CLS" || cmd == "cls"){
      system("cls");
    }else if(cmd == "HELP" || cmd == "help"){
      cout << "Version: 1.4b1\nAuthor: Miles MJ Jamon\nIcon made by iconixar from www.flaticon.com\nAvailable commands: exit, end, file, view, replace, repl, char, cls, sha256" << endl;
    }
    colorize(BRIGHT_WHITE);
  }
}

int main(){
  char choice;

  #ifdef _WIN32
    SetConsoleOutputCP(1252);
    //SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IONBF, 0);
  #endif // _WIN32

  colorize(CYAN_BLUE);
  cout << "CPP Hex Editor v1.4b1" << endl;
  colorize(BRIGHT_WHITE);

  while(true){
    editMode();
    cout << "Enter (y) to exit: ";
    choice = getch();
    cout << choice;
    if(choice == 'Y' || choice == 'y'){
      break;
    }
    cout << endl;
  }
  colorize(NORMALIZE);
  return 0;
}
