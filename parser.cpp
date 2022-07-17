#include<iostream>

enum p_type{
  WORD,
  SPACE,
  EOL,
  EOF
}

enum p_token{
  p_type type;
  int col;
  int line;
}

class parser{
public:
  void parse(std::string inp){
    for(int i=0; i<inp.size(); i++){
      
    }
  }
}

int main(){
  parser p;
  p.parse("Hello, welcome to Jollibee.");
  return 0;
}