#include <iostream>
#include <vector>

void fibonacci(size_t count){
  std::vector<size_t> cow;
  size_t a=0, b=2, t, p1=0, p2=0;
  bool odd = true;
  for(size_t i=0; i<count; i++){
    std::cout << b << std::endl;
    t = a + b;
    a = b;
    b = t;
    if(odd){
      p1+=a;
      cow.push_back(p1);
      odd = false;
    }else{
      p2+=b;
      odd = true;
    }
  }
  
  std::cout << "----" << std::endl;
  for(size_t i=0; i<cow.size(); i++){
    std::cout << cow.at(i) << std::endl;
  }
}

int main(int argc, char *argv[]) {
  using namespace std;
  /* insert code here */
  fibonacci(20);
}