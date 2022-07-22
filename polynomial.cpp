#include <iostream>
#include <vector>

class polynomial{
  std::vector<double> nc;
  std::vector<int> epn;
public:
  polynomial(){}
  polynomial(std::string str){

  };
  polynomial(std::vector<double> nc_, std::vector<int> epn_){
    nc = nc_;
    epn = epn_;
  }
  polynomial(double * nc_, int * epn_, int len){
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
  polynomial derivative(){
    std::vector<double> a;
    std::vector<int> b;
    for(int i=0; i<nc.size(); i++){
      if(epn.at(i) == 0) {continue;}
      a.push_back(nc.at(i) * epn.at(i));
      b.push_back(epn.at(i) - 1);
    }
    return polynomial(a, b);
  }
  void print(){
    for(int i=0; i<nc.size(); i++){
      double t = nc.at(i);
      char sign = '+';
      if(i > 0){
        if(t < 0){
          t *= -1;
          sign = '-';
        }
        std::cout << " " << sign << " ";
      }
      if(t != 0){
        if(t != 1){
          std::cout << t;
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
  double a[] = {1,4,4};
  int b[] = {2,1,-1};
  polynomial c(a, b, 3);
  std::cout << c.eval(1) << std::endl;
  c.print();
  c.derivative().print();
  return 0;
}
