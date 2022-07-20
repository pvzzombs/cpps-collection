#include <iostream>
#include <vector>

struct polynomial{
  std::vector<double> nc;
  double hd;
  polynomial(){}
  polynomial(std::vector<double> p){
    nc = p;
    hd = p.size()-1;
  }
  double eval(double e){
    double q=hd;
    double temp=0;
    for(int i=0; i<nc.size(); i++){
      int t=1;
      for(int i=0; i<q; i++){
        t *= e;
      }
      t *= nc.at(i);
      temp += t;
      q--;
    }
    return temp;
  }
  polynomial derivative(){
    double hd_ = hd;
    std::vector<double> d;
    for(int i=0; i<hd; i++){
      d.push_back(hd_ * nc.at(i));
      hd_--;
    }
    return polynomial(d);
  }

};

double nm(polynomial p, double x0){
  double x = x0, xnew;
  polynomial p_ = p.derivative();
  double eps = 0.00005;
  for(int i=0; i<100; i++){
    xnew = x - p.eval(x) / p_.eval(x);
    double t = xnew;
    if(p_.eval(x) < eps){
      break;
    }
    x = t;
    std::cout << xnew << std::endl;
  }
  return x;
}

int main(){
  std::vector<double> v={1,4,4};
  polynomial a(v);
  std::cout << a.eval(-2) << std::endl;
  std::cout << a.derivative().eval(2) << std::endl;
  std::cout << nm(a, 2) << std::endl;
  return 0;

}
