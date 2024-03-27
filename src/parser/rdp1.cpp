#include <iostream>
#include <string>
//using namespace std;

std::string program = "2*2-3";

int ptr = 0;

char peek(){
  if(ptr < program.size()){
    return program.at(ptr);
  }else{
    return 0;
  }
}

void match(char a){
  if(peek() == a){
    ++ptr;
  }else{
    std::cerr << "Error: Unexpected token " << a << std::endl;
  }
}

void eat(){
  if(ptr < program.size()){
    ++ptr;
  }else{
    std::cerr << "Error: EOF" << std::endl;
  }
}

int factor(){
  if(peek() >= '0' && peek() <= '9'){
    std::string num = "";
    while(peek() >= '0' && peek() <= '9'){
      num += peek();
      eat();
    }
    return std::stoi(num);
  }
}

int term_(int a){
  char ch = peek();
  int b;
  if(ch == '*' || ch == '/'){
    switch(ch){
      case '*': match('*');
        b = factor();
        a = a * b;
        return term_(a);
        //break;
      case '/': match('/');
        b = factor();
        a = a / b;
        //std::cout << peek() << std::endl;
        return term_(a);
        //break;
    }
  }
  return a;
}
int term(){
  int a = factor();
  return term_(a);
}

int expr_(int a){
  char ch = peek();
  int b;
  if(ch == '+' || ch == '-'){
    switch(ch){
      case '+': match('+');
        b = term();
        a = a + b;
        return expr_(a);
        //break;
      case '-': match('-');
        b = term();
        a = a - b;
        //std::cout << peek() << std::endl;
        return expr_(a);
        //break;
    }
  }
  return a;
}

int expr(){
  int a = term();
  return expr_(a);
}

int main(int argc, char *argv[]) {
  int result = expr();
  std::cout << result << std::endl;
  return 0;
}