#include <iostream>
#include <cmath>
#include <vector>
#include <stack>
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

Tokens CreateToken(TokenType t, Value v, Associativity a, Precedence p){
  Tokens out;
  out.type = t;
  out.value = v;
  out.assoc = a;
  out.prec = p;
  return out;
}

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

std::vector<Tokens> Tokenize(std::string str){
  Tokens tmp;
  std::string num, temp;
  std::vector<Tokens> out;
  bool sign = false;
  bool found_sign = false;
  for(size_t i=0; i<str.size(); i++){
    char tok = str.at(i);
    if(IsDigit(tok)){
      num += tok;
    }else if(IsOperator(tok)){
      if(num.size() > 0){
        found_sign = false;
        if(sign){
          num = "-" + num;
          sign = false;
        }
        out.push_back(CreateToken(Number, num, No_Assoc, 0));
        num = "";
      }
      if(tok == '+' || tok == '-'){
        found_sign = true;
        if(tok == '-'){
          sign = sign ? false : true;
        }
      }else{
        temp = "";
        temp += tok;
        out.push_back(CreateToken(Operator, temp, GetAssoc(tok), GetPrec(tok)));
      }
    }else if(IsParenthesis(tok) && tok == '('){
      if(found_sign){
        temp = "";
        if(sign){
          temp += '-';
          out.push_back(CreateToken(Operator, temp, GetAssoc('-'), GetPrec('-')));
        }else{
          temp += '+';
          out.push_back(CreateToken(Operator, temp, GetAssoc('-'), GetPrec('+')));
        }
        found_sign = false;
        sign = false;
      }
      if(num.size() > 0){
        found_sign = false;
        if(sign){
          num = "-" + num;
          sign = false;
        }
        out.push_back(CreateToken(Number, num, No_Assoc, 0));
        num = "";
        
        temp = "";
        temp += '*';
        out.push_back(CreateToken(Operator, temp, GetAssoc('*'), GetPrec('*')));
      }
        temp = "";
        temp += tok;
        out.push_back(CreateToken(Left_Parenthesis, temp, GetAssoc(tok), GetPrec(tok)));
    }else if(IsParenthesis(tok) && tok == ')'){
      //std::cout << i << "Token is " << tok << std::endl;
    if(num.size() > 0){
      //std::cout << "Num" << num << std::endl;
      found_sign = false;
      if(sign){
        num = "-" + num;
        sign = false;
      }
      out.push_back(CreateToken(Number, num, No_Assoc, 0));
      num = "";
      }
      temp = "";
      temp += tok;
      out.push_back(CreateToken(Right_Parenthesis, temp, GetAssoc(tok), GetPrec(tok)));
      if(i+1<str.size()){
        if(str.at(i+1) == '(' || IsDigit(str.at(i+1))){
          temp = "";
          temp += '*';
          out.push_back(CreateToken(Operator, temp, GetAssoc('*'), GetPrec('*')));
        }
      }
    }
  }
  // for leftover number
  if(num.size() > 0){
    found_sign = false;
    if(sign){
      num = "-" + num;
      sign = false;
    }
    out.push_back(CreateToken(Number, num, No_Assoc, 0));
    num = "";
  }
  return out;
}

std::vector<Tokens> FixTokens(std::vector<Tokens> & toks){
  std::vector<Tokens> out;
  std::string temp;
  for(size_t i=0; i<toks.size(); i++){
    Tokens t = toks.at(i);
    out.push_back(t);
    if(t.type == Number){
      if(i+1<toks.size()){
        if(toks.at(i+1).type == Number){
         temp = "";
         temp += '+';
         out.push_back(CreateToken(Operator, temp, GetAssoc('+'), GetPrec('+')));
        }
      }
    }else if(t.type == Right_Parenthesis){
      if(i+1<toks.size()){
        if(toks.at(i+1).type == Number){
         temp = "";
         temp += '+';
         out.push_back(CreateToken(Operator, temp, GetAssoc('+'), GetPrec('+')));
        }
      }
    }else if(t.type == Operator && (t.value == "+" || t.value == "-")){
      std::cout << "----" << std::endl;
      if(i+1<toks.size()){
        if(toks.at(i+1).type == Left_Parenthesis){
          if(t.value == "-"){
            out.at(out.size() - 1) = CreateToken(Number, "-1", No_Assoc, 0); 
          }else{
            out.at(out.size() - 1) = CreateToken(Number, "1", No_Assoc, 0);
          }
          temp = "";
          temp += '*';
          out.push_back(CreateToken(Operator, temp, GetAssoc('*'), GetPrec('*')));
        }
      }
    }
  }
  return out;
}

std::vector<Tokens> Parse(std::vector<Tokens> & toks){
  std::vector<Tokens> out;
  std::stack<Tokens> s;
  for(size_t i=0; i<toks.size(); i++){
    Tokens t = toks.at(i);
    if(t.type == Number){
      out.push_back(t);
    }else if(t.type == Operator){
      while(!s.empty() && s.top().type != Left_Parenthesis && (s.top().prec > t.prec || (t.prec == s.top().prec && t.assoc == Left_Assoc))){
        out.push_back(s.top());
        s.pop();
      }
      s.push(t);
    }else if(t.type == Left_Parenthesis){
      s.push(t);
    }else if(t.type == Right_Parenthesis){
     while(!s.empty() && s.top().type != Left_Parenthesis){
       out.push_back(s.top());
       s.pop();
     }
     s.pop();
    }
  }
  while(!s.empty()){
    out.push_back(s.top());
    s.pop();
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
  std::stack<Tokens> s;
  for(size_t i=0; i<toks.size(); i++){
    Tokens t = toks.at(i);
    if(t.type == Number){
      s.push(t);
    }else if(t.type == Operator){
      int b = std::stoi(s.top().value); s.pop();
      int a = std::stoi(s.top().value); s.pop();
      int c = Compute(a,b,t.value.at(0));
      s.push(CreateToken(Number, std::to_string(c), No_Assoc, 0));
    }
  }
  return std::stoi(s.top().value);
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
  */
  std::vector<Tokens> a = Tokenize("-(+(-(8)))");
  std::vector<Tokens> b = FixTokens(a);
  std::vector<Tokens> c = Parse(b);
  //int r = Evaluate(c);
  //std::cout << "Result: " << r << std::endl;
  for(auto &t: b){
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