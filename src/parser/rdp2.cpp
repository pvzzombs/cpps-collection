#include <iostream>
#include <string>
//using namespace std;

enum kType { OPERATOR, NUMBER };

struct ASTNode {
  kType type;
  ASTNode* left;
  ASTNode* right;
  std::string value;
};

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
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
  }
}

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
        temp->right = b;
        temp->value = "*";
        return term_(temp);
        //break;
      case '/': match('/');
        b = factor();
        temp->left = a;
        temp->right = b;
        temp->value = "/";
        //std::cout << peek() << std::endl;
        return term_(temp);
        //break;
    }
  }
  return a;
}
ASTNode* term(){
  ASTNode* a = factor();
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
        //std::cout << peek() << std::endl;
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
    std::cout << indent << t->value << std::endl;
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
  ASTNode* result = expr();
  printASTNode(result, "");
  deleteASTNode(result);
  return 0;
}