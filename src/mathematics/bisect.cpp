#include <iostream>
#include <cmath>

double f(double x){
  return x*x +4*x + 4;
}

int Sign(double q){
  if(q > 0){
    return 1;
  }
  if(q < 0){
    return -1;
  }
  return 0;
}

double Bisection(double a, double b){
  double t = 0.00001, c=(a+b)/2;
  //double f_a, f_c=f(c);
  int Max = 10000, i=0;
  //std::cout << "C is " << c << std::endl;
  while(std::abs(f(c)) > t && i<Max){
    if(f(c) < 0){
      a = c;
      //std::cout << a << std::endl;
    }else if(f(c) > 0){
      b = c;
    }

    /*if(sign(f(c)) == sign(f(a))){
      a = c;
    }else{
      b = c;
    }*/
    c=(a+b)/2;
    i++;
    std::cout << a << " " << b << " " << c << " " << f(a) << " " << f(b) << std::endl;    
  }
  if(i == Max){
    std::cerr << "Cannot be solved" << std::endl;
  }
  return c;
}

int main(){
  std::cout << "Answer: " <<  Bisection(-3,3);
  return 0;
}
