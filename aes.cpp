#define SAFE_USE_FUNCTIONALITY
//#define DEBUG_
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
#include "aes.hpp"
//#include "safe.hpp"

int main(){
   //_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
   
   uint8_t m[] = {0x00, 0x11, 0x22, 0x33,
				0x44, 0x55, 0x66, 0x77,
				0x88, 0x99, 0xaa, 0xbb,
				0xcc, 0xdd, 0xee, 0xff};
		uint8_t k[] = {0x00, 0x01, 0x02, 0x03,
				0x04, 0x05, 0x06, 0x07,
				0x08, 0x09, 0x0a, 0x0b,
				0x0c, 0x0d, 0x0e, 0x0f};
		uint8_t im[] = {0x69, 0xc4, 0xe0, 0xd8,
				0x6a, 0x7b, 0x04, 0x30,
				0xd8, 0xcd, 0xb7, 0x80,
				0x70, 0xb4, 0xc5, 0x5a
		};
		uint8_t ik[] = {0x13, 0x11, 0x1d, 0x7f,
				0xe3, 0x94, 0x4a, 0x17,
				0xf3, 0x07, 0xa7, 0x8b,
				0x4d, 0x2b, 0x30, 0xc5
		};

   Aes test;
   test.set_key(k);
   test.encrypt(m);
   std::cout << "%%%%%" << std::endl;
   test.printState();
   std::cout << "%%%%%" << std::endl;

   test.set_key(k);
   test.decrypt(im);
   std::cout << "%%%%%" << std::endl;
   test.printState();
   std::cout << "%%%%%" << std::endl;
   
   //arr_<int> a;
   //bool q = a._assert_null_equals_zero();

   //arr_<arr_<int>> a;
   //a.alloc2(3, 3);
   //a.at(0).print();
   //a.at(1).print();
   //a.at(2).print();
   //a.at(4).print();

   std::getchar();
   return 0;
}
