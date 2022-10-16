#include <iostream>
#include <string>
#include <exception>

//using namespace std;

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

std::string err_msg;

enum kType { OPERATOR, NUMBER, SIGN };

struct ASTNode {
  kType type;
  ASTNode* left;
  ASTNode* right;
  std::string value;
  ASTNode(){
    left = nullptr;
    right = nullptr;
    value = "";
  }
};

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

ASTNode * expr();
void printASTNode(ASTNode * t, std::string indent);

/*ASTNode * get_lowest_left(ASTNode * t){
  while(t->left!=nullptr){
    t = t->left;
  }
  return t;
}*/

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
    temp->type = SIGN;
    temp->value = sign == 1?"+":"-";
    temp->left = factor();
    return temp;
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

//int sign = 1;

/*void usign(){
  while(peek() == '+' || peek() == '-'){
    //std::cout << "Hey" << std::endl;
    if(peek() == '-'){
      sign *= -1;
    }
    eat();
  }
}*/

ASTNode* term_(ASTNode* a){
  char ch = peek();
  ASTNode * b = nullptr;
  if(ch == '*' || ch == '/'){
    ASTNode * temp = new ASTNode;
    temp->type = OPERATOR;
    switch(ch){
      case '*': match('*');
        b = factor();
        temp->left = a;
        temp->value = "*";
        temp->right = b;
        return term_(temp);
        //break;
      case '/': match('/');
        b = factor();
        temp->left = a;
        temp->value = "/";
        temp->right = b;
        return term_(temp);
        //break;
    }
  }
  return a;
}

ASTNode* term(){
  ASTNode* a = factor();
  //printASTNode(a, "");
  return term_(a);
}

ASTNode* expr_(ASTNode* a){
  char ch = peek();
  ASTNode * b = nullptr;
  if(ch == '+' || ch == '-'){
    ASTNode * temp = new ASTNode;
    temp->type = OPERATOR;
    switch(ch){
      case '+': match('+');
        b = term();
        temp->left = a;
        temp->right = b;
        temp->value = "+";
        return expr_(temp);
        //break;
      case '-': match('-');
        b = term();
        temp->left = a;
        temp->right = b;
        temp->value = "-";
        return expr_(temp);
        //break;
    }
  }
  return a;
}

ASTNode* expr(){
  ASTNode* a = term();
  return expr_(a);
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
  program = "-(1*-1)";
  ASTNode* result = expr();
  printASTNode(result, "");
  deleteASTNode(result);
  return 0;
}
