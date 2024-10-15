#include <iostream>
#include <vector>
#include <string>

class Polynomial{
  std::vector<double> nc;
  std::vector<int> epn;
  bool is_sign(char c){
    return c == '+' || c == '-';
  }
  bool is_digit(char c){
    return c >= '0' && c <= '9';
  }
  bool is_x(char c){
    return c == 'x' || c == 'X';
  }
  bool is_pow(char c){
    return c == '^';
  }

public:
  Polynomial(){}
  Polynomial(std::string str){
    int sign = 1;
    std::string tmpnum;
    bool is_epn = false;
    bool skip = false;

    std::vector<double> a;
    std::vector<int> b;

    for(int i=0; i<str.size(); i++){
      char c = str.at(i);
      if(skip){
        skip = false;
        continue;
      }
      if(is_sign(c)){
        if(is_epn){
          if(tmpnum.size()){
            b.push_back(std::stoi(tmpnum) * sign);
            tmpnum = "";
          }else{
            b.push_back(1 * sign);
          }
          is_epn = false;
        }else{
          if(tmpnum.size()){
            a.push_back(std::stod(tmpnum) * sign);
            tmpnum = "";
            b.push_back(0);
          }
        }
        if(c == '-'){
          sign = -1;
        }else{
          sign = 1;
        }
      }
      if(is_digit(c)){
        tmpnum += c;
      }
      if(is_x(c)){
        if(tmpnum.size()){
          a.push_back(std::stod(tmpnum) * sign);
        }else{
          a.push_back(1 * sign);
        }
        tmpnum = "";
        sign = 1;
        is_epn = true;
      }
      if(is_pow(c)){
        char d = '\0';
        if(i+1 < str.size()){
          d = str.at(i+1);
        }
        if(is_sign(d) && d == '-'){
          sign = -1;
          skip = true;
        }else{
          sign = 1;
          skip = false;
        }
        is_epn = true;
      }
    }
    if(tmpnum.size()){
      if(!is_epn){
        a.push_back(std::stod(tmpnum) * sign);
        b.push_back(0);
      }else{
        b.push_back(std::stoi(tmpnum) * sign);
      }
      is_epn = false;
      sign = 1;
      tmpnum = "";
    }
    if(b.size() < a.size()){
      b.push_back(1);
    }
    if(a.size() != b.size()){
      std::cerr << "Fatal Error: Numerical Coefficient and Exponent Mismatch" << std::endl;
    }else{
      nc = a;
      epn = b;
    }
  }
  Polynomial(std::vector<double> nc_, std::vector<int> epn_){
    nc = nc_;
    epn = epn_;
  }
  Polynomial(double * nc_, int * epn_, int len){
    nc.reserve(len);
    epn.reserve(len);
    for(int i=0; i<len; i++){
      nc.push_back(nc_[i]);
      epn.push_back(epn_[i]);
    }
  }
  double eval(double n){
    double sum = 0;
    for(int i=0; i<nc.size(); i++){
      double t = 1;
      int epn_;
      if(epn.at(i) < 0){
        epn_ = epn.at(i) * -1;
        for(int i=0; i<epn_; i++){
          t *= n;
        }
        if(t == 0){
          std::cerr << "Error: Division by zero" << std::endl;
        }
        sum += (nc.at(i) / t);
      }else{
        epn_ = epn.at(i);
        for(int i=0; i<epn_; i++){
          t *= n;
        }
        sum += (nc.at(i) * t);
      } 
    }
    return sum;
  }
  Polynomial derivative(){
    std::vector<double> a;
    std::vector<int> b;
    for(int i=0; i<nc.size(); i++){
      if(epn.at(i) == 0) {continue;}
      a.push_back(nc.at(i) * epn.at(i));
      b.push_back(epn.at(i) - 1);
    }
    return Polynomial(a, b);
  }
  void print(){
    for(int i=0; i<nc.size(); i++){
      double t = nc.at(i);
      //std::cout << "==== " << t << std::endl;
      char sign = '+';
      if(t < 0){
        t *= -1;
        sign = '-';
      }
      if(i > 0){
        std::cout << " " << sign << " ";
      }else{
        if(sign == '-'){
          std::cout << sign;
        }
      }
      //std::cout << "****" << t << std::endl;
      if(t != 0){
        if(t != 1){
          std::cout << t;
        }else{
          if(epn.at(i) == 0){
            std::cout << t;
          }
        }
        if(epn.at(i) != 0){
          std::cout << "x";
          if(epn.at(i) != 1){
            std::cout << "^" << epn.at(i);
          }
        }
      }
    }
    std::cout << std::endl;
  }
};

int main(){
  //double a[] = {1,4,4};
  //int b[] = {2,1,0};
  //Polynomial c(a, b, 3);
  //std::cout << c.eval(1) << std::endl;
  //c.print();
  //c.derivative().print();
  Polynomial d("x^2 + 4x - 2 + x^-2");
  d.derivative().print();
  d.print();
  return 0;
}
