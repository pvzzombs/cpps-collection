#include <iostream>
#include <vector>

enum PType{
  kLETTER,
  kWORD,
  kSPACE,
  kEOL,
  kEOF
};

struct PToken{
  PType type;
  int col;
  int line;
  char value;
};

bool IsAlpha(char c){
  return (c >= 'a' && c <= 'z') || 
         (c >= 'A' && c <= 'Z');
}

bool IsSpace(char c){
  return c == ' ' || c == '\t';
}

bool IsEol(char c){
  return c == '\n';
}

class parser{
public:
  std::vector<PToken> parse(std::string inp){
    std::vector<PToken> arr;
    arr.reserve(inp.size());
    PToken t;
    int line = 1;

    for(int i=0; i<inp.size(); i++){
      t.line = line;
      t.col = i+1;
      t.value = inp.at(i);
      if(IsAlpha(inp.at(i))){
        t.type = kLETTER;
      }else if(IsSpace(inp.at(i))){
        t.type = kSPACE;
      }else if(IsEol(inp.at(i))){
        t.type = kEOL;
        line++;
      }
      arr.push_back(t);
    }
    return arr;
  }
};

int main(){
  parser p;
  p.parse("Hello, welcome to Jollibee.");
  return 0;
}
