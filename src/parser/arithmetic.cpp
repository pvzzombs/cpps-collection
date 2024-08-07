#include <iostream>
#include <string>
#include <exception>

class SyntaxError: public std::exception{
  public:
  std::string err_msg_ = "Syntax Error: ";
  void add_cause(std::string str){
    err_msg_ += str;
  }
  virtual const char* what() const throw(){
    return err_msg_.c_str();
  }
} syntax_err;

enum NodeType { OPERATOR, NUMBER, SIGN };

struct ASTNode {
  NodeType type;
  ASTNode* left;
  ASTNode* right;
  std::string value;
  ASTNode(){
    left = nullptr;
    right = nullptr;
    value = "";
  }
};

ASTNode * expr();
ASTNode * term();
ASTNode * power();
ASTNode * factor();

std::string err_msg;
std::string program;

int ptr = 0;

inline char peek(){
  if(ptr < program.size()){
    return program.at(ptr);
  }else{
    return 0;
  }
}

inline void match(char a){
  if(peek() == a){
    ++ptr;
  }else{
    err_msg = "Unexpected token ";
    err_msg += a;
    err_msg += " at column ";
    err_msg += std::to_string(ptr + 1);
    err_msg += ", inside match()";
    syntax_err.add_cause(err_msg);
    throw syntax_err;
  }
}

inline void eat(){
  if(ptr < program.size()){
    ++ptr;
  }else{
    err_msg = "EOF";
    err_msg += ", inside eat()";
    syntax_err.add_cause(err_msg);
    throw syntax_err;
  }
}

ASTNode * factor(){
  if(peek() >= '0' && peek() <= '9'){
    ASTNode * temp = new ASTNode;
    std::string num = "";
    while(peek() >= '0' && peek() <= '9'){
      num += peek();
      eat();
    }
    temp->type = NUMBER;
    temp->value = num;
    return temp;
  }else if(peek() == '+' || peek() == '-'){
    //std::cout << "Test" << std::endl;
    ASTNode * temp = new ASTNode;
    int sign = 1;
    while(peek() == '+' || peek() == '-'){
      if(peek() == '-'){
        sign *= -1;
      }
      eat();
    }
    if (sign == -1) {
      temp->type = SIGN;
      temp->value = "-";
      temp->left = factor();
      return temp;
    }
    return factor();
  }else if(peek() == '('){
    match('(');
    ASTNode * temp = expr();
    match(')');
    return temp;
  }else{
    err_msg = "Unexpected token ";
    err_msg += peek();
    err_msg += " at column ";
    err_msg += std::to_string(ptr + 1);
    err_msg += ", inside factor()";
    syntax_err.add_cause(err_msg);
    throw syntax_err;
  }
}

ASTNode * power() {
  ASTNode * left = factor();
  if (peek() == '^') {
    match('^');
    ASTNode * temp = new ASTNode;
    temp->type = OPERATOR;
    temp->value = "^";
    temp->left = left;
    temp->right = power();
    return temp;
  }
  return left;
}

ASTNode * term() {
  ASTNode * left = power();
  while(peek() == '*' || peek() == '/') {
    char ch = peek();
    ASTNode * temp = new ASTNode;
    temp->type = OPERATOR;
    switch (ch) {
      case '*':
        match('*');
        temp->value = "*";
        temp->left = left;
        temp->right = power();
        left = temp;
      break;
      case '/':
        match('/');
        temp->value = "/";
        temp->left = left;
        temp->right = power();
        left = temp;
      break;
    }
  }
  return left;
}

ASTNode * expr() {
  ASTNode * left = term();
  while(peek() == '+' || peek() == '-') {
    char ch = peek();
    ASTNode * temp = new ASTNode;
    temp->type = OPERATOR;
    switch (ch) {
      case '+':
        match('+');
        temp->value = "+";
        temp->left = left;
        temp->right = term();
        left = temp;
      break;
      case '-':
        match('-');
        temp->value = "-";
        temp->left = left;
        temp->right = term();
        left = temp;
      break;
    }
  }
  return left;
}

void printASTNode(ASTNode * t, std::string indent){
  if(t != nullptr){
    std::cout << indent;
    switch(t->type){
      case OPERATOR:
        std::cout << "[Operator] ";
        break;
      case NUMBER:
        std::cout << "[Number] ";
        break;
      case SIGN:
        std::cout << "[Sign] ";
        break;
    }
    std::cout << t->value << std::endl;
    indent += "  ";
    printASTNode(t->left, indent);
    printASTNode(t->right, indent);
  }
}

void deleteASTNode(ASTNode * t){
  if(t != nullptr){
    deleteASTNode(t->left);
    deleteASTNode(t->right);
    delete t;
  }
}

int main(int argc, char *argv[]) {
  // program = "2*3+(2^2)^3";
  program = "-(1*-1)";
  ASTNode* result = expr();
  printASTNode(result, "");
  deleteASTNode(result);
  return 0;
}
