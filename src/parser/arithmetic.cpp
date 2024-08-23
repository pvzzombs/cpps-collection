#include <iostream>
#include <string>
#include <exception>
#include <cmath>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
// #include <windows.h>
void setToU16Text() {
  _setmode(_fileno(stdout), _O_U16TEXT);
  // SetConsoleOutputCP(CP_UTF8);
}
void setToNormalText() {
  _setmode(_fileno(stdout), _O_TEXT);
}
#else
void setToU16Text() {
}
void setToNormalText() {
}
#endif

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
    std::string c = "";
    c += peek();
    std::string cause = peek() == 0 ? "EOF" : c;
    err_msg = "Unexpected token ";
    err_msg += cause;
    err_msg += ", expecting ";
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

void printASTNode(ASTNode * t, std::string indent) {
  if(t != nullptr){
    std::cout << indent;
    switch(t->type){
      case OPERATOR:
        std::cout << "[Operator] ";
        break;
      case NUMBER:
        std::cout << "[ Number ] ";
        break;
      case SIGN:
        std::cout << "[  Sign  ] ";
        break;
    }
    std::cout << t->value << std::endl;
    indent += "  ";
    printASTNode(t->left, indent);
    printASTNode(t->right, indent);
  }
}

void prettyPrintASTNode(ASTNode * t, std::wstring indent, int direction) {
  if(t != nullptr){
    setToU16Text();
    std::wcout << indent;
    setToNormalText();
    switch(t->type){
      case OPERATOR:
        std::cout << "[Operator] ";
        break;
      case NUMBER:
        std::cout << "[ Number ] ";
        break;
      case SIGN:
        std::cout << "[  Sign  ] ";
        break;
    }
    if (t->right != nullptr && direction == 0) {
      indent = indent.substr(0, indent.size() - 2) + L"\u2502 ";
    } else {
      if (indent != L"") {
        indent = indent.substr(0, indent.size() - 2) + L"  ";
      }
    }
    setToNormalText();
    std::cout << t->value << std::endl;
    std::wstring tempIndent = indent;
    int dir = 0;
    if (t->left != nullptr) {
      if (t->right != nullptr) {
        indent += L"\u251c\u2500";
      } else {
        indent += L"\u2514\u2500";
        dir = 1;
      }
    }
    prettyPrintASTNode(t->left, indent, dir);
    indent = tempIndent;
    if (t->right != nullptr) {
      indent += L"\u2514\u2500";
    }
    prettyPrintASTNode(t->right, indent, 1);
  }
}

void deleteASTNode(ASTNode * t) {
  if(t != nullptr){
    deleteASTNode(t->left);
    deleteASTNode(t->right);
    delete t;
  }
}

int generateSolution(ASTNode * t) {
  if (t->type == NUMBER) {
    return std::stoi(t->value);
  }
  if (t->type == SIGN) {
    return -1 * generateSolution(t->left);
  }
  if (t->type == OPERATOR) {
    int left = generateSolution(t->left);
    int right = generateSolution(t->right);
    switch (t->value.at(0)) {
      case '+':
        return left + right;
      break;
      case '-':
        return left - right;
      break;
      case '*':
        return left * right;
      break;
      case '/':
        return left / right;
      break;
      case '^':
        return std::pow(left, right);
      break;
    }
  }
  throw 1;
}

int main(int argc, char *argv[]) {
  // program = "2*3+(2^2)^3";
  // program = "-(1*-1)";
  // program = "2*3*4^5^9*6*8";
  program = "-(1)";
  ASTNode* result = expr();
  // printASTNode(result, "");
  prettyPrintASTNode(result, L"", 1);
  setToNormalText();
  std::cout << "Answer: ";
  std::cout << generateSolution(result) << std::endl;
  deleteASTNode(result);
  return 0;
}
