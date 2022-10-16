#include <iostream>
#include <cmath>
#include <vector>
//#include <stack>
//using namespace std;
//Infix to Postfix

enum TokenType { Operator, Left_Parenthesis, Right_Parenthesis, Number };

enum Associativity { No_Assoc, Left_Assoc, Right_Assoc };

typedef int Precedence;
typedef std::string Value;

struct Tokens{
  TokenType type;
  Value value;
  Associativity assoc;
  Precedence prec;
};

std::string digits = "0123456789";
std::string ops = "+-*/^";
std::string pars = "()";

bool IsDigit(char c){
  for(auto &d: digits){
    if(c == d){
      return true;
    }
  }
  return false;
}

bool IsOperator(char c){
  for(auto &o: ops){
    if(c == o){
      return true;
    }
  }
  return false;
}

bool IsParenthesis(char c){
  for(auto &p: pars){
    if(c == p){
      return true;
    }
  }
  return false;
}

Associativity GetAssoc(char c){
  switch(c){
    case '+':
    case '-':
    case '*':
    case '/':
      return Left_Assoc;
    case '^':
      return Right_Assoc;
  }
  return No_Assoc;
}

Precedence GetPrec(char c){
  switch(c){
    case '+': case '-':
      return 1;
    case '*': case '/':
      return 2;
    case '^':
      return 3;
  }
  return 0;
}

Tokens CreateToken(TokenType t, Value v, Associativity a, Precedence p){
  Tokens out;
  out.type = t;
  out.value = v;
  out.assoc = a;
  out.prec = p;
  return out;
}

std::vector<Tokens> Tokenize(std::string str){
  std::string num, temp;
  std::vector<Tokens> out;
  bool sign = false;
  bool collect_signs = true;
  size_t i=0;
  while(i < str.size()){
    char tok = str.at(i);
    if(IsDigit(tok)){
      collect_signs = false;
      num += tok;
    }else if(IsOperator(tok)){
      if(num.size() > 0){
        if(sign){
          num = "-" + num;
        }
        out.push_back(CreateToken(Number, num, No_Assoc, 0));
        num = "";
      }
      if(collect_signs){
        if(tok == '-'){
          //std::cout << "----" << std::endl;
          sign = sign ? false : true;
        }else if(tok == '+'){
          
        }else{
          std::cerr << "Error, unexpected operator token " << tok << std::endl;
        }
      }else{
        temp = "";
        temp += tok;
        out.push_back(CreateToken(Operator, temp, GetAssoc(tok), GetPrec(tok)));
        collect_signs = true;
        sign = false;
      }
    }else if(IsParenthesis(tok) && tok == '('){
      if(num.size() > 0){
        if(sign){
          num = "-" + num;
        }
        out.push_back(CreateToken(Number, num, No_Assoc, 0));
        num = "";
        temp = "*";
        out.push_back(CreateToken(Operator, temp, GetAssoc('*'), GetPrec('*')));
      }
      if(collect_signs){
        if(sign){
          temp = "-1";
          out.push_back(CreateToken(Number, temp, No_Assoc, 0));
        }else{
          temp = "1";
          out.push_back(CreateToken(Number, temp, No_Assoc, 0));
        }
        temp = "*";
        out.push_back(CreateToken(Operator, temp, GetAssoc('*'), GetPrec('*')));
      }
      temp = "(";
      out.push_back(CreateToken(Left_Parenthesis, temp, GetAssoc('('), GetPrec('(')));
      collect_signs = true;
      sign = false;
    }else if(IsParenthesis(tok) && tok == ')'){
      if(num.size() > 0){
        if(sign){
          num = "-" + num;
        }
        out.push_back(CreateToken(Number, num, No_Assoc, 0));
        num = "";
      }
      temp = ")";
      out.push_back(CreateToken(Left_Parenthesis, temp, GetAssoc(')'), GetPrec(')')));
      if(i+1<str.size()){
        char tok2=str.at(i+1);
        if(tok2 == '(' || IsDigit(tok2)){
          temp = "*";
          out.push_back(CreateToken(Operator, temp, GetAssoc('*'), GetPrec('*')));
        }
      }
      collect_signs = false;
      sign = false;
    }
    ++i;
  }
  if(num.size() > 0){
    if(sign){
      num = "-" + num;
    }
    out.push_back(CreateToken(Number, num, No_Assoc, 0));
    num = "";
  }
  return out;
}

std::vector<Tokens> Parse(std::vector<Tokens> & toks){
  std::vector<Tokens> out;
  std::vector<Tokens> s;
  for(size_t i=0; i<toks.size(); i++){
    Tokens t = toks.at(i);
    if(t.type == Number){
      out.push_back(t);
    }else if(t.type == Operator){
      while(!s.empty() && s.back().type != Left_Parenthesis && (s.back().prec > t.prec || (t.prec == s.back().prec && t.assoc == Left_Assoc))){
        out.push_back(s.back());
        s.pop_back();
      }
      s.push_back(t);
    }else if(t.type == Left_Parenthesis){
      s.push_back(t);
    }else if(t.type == Right_Parenthesis){
     while(!s.empty() && s.back().type != Left_Parenthesis){
       out.push_back(s.back());
       s.pop_back();
     }
     s.pop_back();
    }
  }
  while(!s.empty()){
    out.push_back(s.back());
    s.pop_back();
  }
  
  return out;
}

int Compute(int a, int b, char c){
  switch(c){
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '*':
      return a * b;
    case '/':
      return a / b;
    case '^':
      return static_cast<int>(std::pow(static_cast<double>(a),static_cast<double>(b)));
    default:
      throw "ERROR";
  }
}

int Evaluate(std::vector<Tokens> & toks){
  std::vector<Tokens> s;
  for(size_t i=0; i<toks.size(); i++){
    Tokens t = toks.at(i);
    if(t.type == Number){
      s.push_back(t);
    }else if(t.type == Operator){
      int b = std::stoi(s.back().value); s.pop_back();
      int a = std::stoi(s.back().value); s.pop_back();
      int c = Compute(a,b,t.value.at(0));
      s.push_back(CreateToken(Number, std::to_string(c), No_Assoc, 0));
    }
  }
  return std::stoi(s.back().value);
}

int main(int argc, char *argv[]) {
  /*
  -1+2+(54)-8*(89)1
  1--2
  1+-2*-3
  -1-2(54)
  (6)(8)
  (8)-2-7*1
  ((6)+7)+8
  (1)(2)(3)
  1---8
  (7)-10(9)-3
  1(7)2(4)
  (8)---9
  2^3^2
  (3)^2
  100/10
  24/(12)
  -(24)*12
  -123
  -(8)
  -(+(-(8)))
  (((1)+2)+3)
  --8(9)
  (1+(2+(3)+4)+5)
  1+2*3-4*5
  1-(9)
  (1+2*3-4*-5)
  8--(9)
  (9)--(8)
  8(-(9))
  ((8)7)
  1+(2+(3))
  */
  std::vector<Tokens> a = Tokenize("((8)7)");
  //std::vector<Tokens> c = Parse(a);
  //int r = Evaluate(c);
  //std::cout << "Result: " << r << std::endl;
  for(auto &t: a){
    switch(t.type){
      case Operator:
        std::cout << "Operator: ";
        break;
      case Number:
        std::cout << "Number: ";
        break;
      case Left_Parenthesis: 
        std::cout << "Left: ";
        break;
      case Right_Parenthesis:
        std::cout << "Right: ";
        break;
    }
    std::cout << t.value << std::endl;
  }
  /*for(size_t i=0; i<b.size(); i++){
    auto t = b.at(i);
    switch(t.type){
      case Operator:
        std::cout << "Operator: ";
        break;
      case Number:
        std::cout << "Number: ";
        break;
    }
    std::cout << t.value << std::endl;
  }*/
  return 0;
}