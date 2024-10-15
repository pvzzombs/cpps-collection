#include <iostream>

std::string str = "ABCD";
void Solve(int x){
  if(x == str.size()){
    std::cout << str << std::endl;
    return;
  }
  for(int i=x; i<str.size(); i++){
    std::swap(str[i], str[x]);
    Solve(x+1);
    std::swap(str[i], str[x]);
  }
}

int main(int argc, char *argv[]) {
  Solve(0);
}