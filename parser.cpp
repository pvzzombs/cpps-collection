#include <iostream>
#include <vector>

enum p_type{
  LETTER
  WORD,
  SPACE,
  EOL,
  EOF
}

enum p_token{
  p_type type;
  int col;
  int line;
  char value;
}

bool is_alpha(char c){
  return (c >= 'a' && c <= 'z') || 
         (c >= 'A' && c <= 'Z');
}

bool is_space(char c){
  return c == ' ' || c == '\t';
}

bool is_eol(char c){
  return c == '\n';
}

class parser{
public:
  std::vector<p_token> parse(std::string inp){
    std::vector<p_token> arr;
    arr.reserve(inp.size());
    p_token t;
    int line = 1;

    for(int i=0; i<inp.size(); i++){
      t.line = line;
      t.col = i+1;
      t.value = inp.at(i);
      if(is_alpha(inp.at(i))){
        t.type = LETTER;
      }else if(is_space(inp.at(i))){
        t.type = SPACE;
      }else if(is_eol(inp.at(i))){
        t.type = EOL;
        line++;
      }
      arr.push_back(t);
    }
  }
}

int main(){
  parser p;
  p.parse("Hello, welcome to Jollibee.");
  return 0;
}
