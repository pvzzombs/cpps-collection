#include <iostream>

int Fibonacci(int n){
  int i=1, a=0, b=1, c=1;
  while(i < n){
    a = b;
    b = c;
    c = a + b;
    i++;
  }
  return c;
}

int main(int argc, char *argv[]) {
  std::cout << Fibonacci(5) << std::endl;
  return 0;
}