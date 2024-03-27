#include <iostream>
#include <vector>
#include <cmath>

struct Polynomial{
  std::vector<double> nc;
  double hd;
  Polynomial(){}
  Polynomial(std::vector<double> p){
    nc = p;
    hd = p.size()-1;
  }
  double eval(double e){
    double q=hd;
    double temp=0;
    for(int i=0; i<nc.size(); i++){
      double t=1;
      for(int i=0; i<q; i++){
        t *= e;
      }
      t *= nc.at(i);
      temp += t;
      q--;
    }
    return temp;
  }
  Polynomial derivative(){
    double hd_ = hd;
    std::vector<double> d;
    for(int i=0; i<hd; i++){
      d.push_back(hd_ * nc.at(i));
      hd_--;
    }
    return Polynomial(d);
  }

};

double nm(Polynomial p, double x0){
  double x = x0, xnew;
  Polynomial p_ = p.derivative();
  double eps = 0.0000001;
  double tol = 0.0000001;
  double t;
  int i;
  for(i=0; i<1000; i++){
    xnew = x - p.eval(x) / p_.eval(x);
    //std::cout << p.eval(x) << " " << p_.eval(x) << std::endl;
    t = xnew;
    if(std::abs(p_.eval(x)) < eps){
      break;
    }
    if(std::abs(xnew - x) <= tol){
      return t;
    }
    x = t;
    //std::cout << xnew << " " << x << " "<< std::endl;
  }
  if(i==1000){
    std::cout << "Did not converge" << std::endl;
  }
  return x;
}

int main(){
  std::vector<double> v={1,4,4};
  Polynomial a(v);
  std::cout << a.eval(-1.5) << std::endl;
  std::cout << a.derivative().eval(2) << std::endl;
  std::cout << nm(a, 2) << std::endl;
  return 0;

}
