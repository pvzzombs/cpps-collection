#include <iostream>
#include <vector>

const int n = 6;

std::vector<char> pars;

void PrintString(){
  for(char c: pars){
    std::cout << c;
  }
  std::cout << std::endl;
}

bool IsValid(char c){
  int x = 0;
  for(char ch: pars){
    switch(ch){
      case '(':
        ++x;
        break;
      case ')':
        --x;
        break;
    }
  }
  switch(c){
    case '(':
      ++x;
      break;
    case ')':
      --x;
      break;
  }
  if(x < 0 || x > n){
    return false;
  }
  return true;
}

bool IsSolved(){
  if(pars.size() != static_cast<size_t>(n*2)){
    return false;
  }
  int x = 0;
  std::vector<int> s;
  for(char c: pars){
    switch(c){
      case '(':
        ++x;
        s.push_back(1);
        break;
      case ')':
        if(x == 0){
          return false;
        }
        --x;
        if(s.size() == 0){
          return false;
        }
        s.pop_back();
        break;
    }
  }
  return (x == 0) && (s.size() == 0);
}

void Solve(){
  if(IsSolved()){
    PrintString();
    //return true;
    return;
  }
  if(pars.size() >= n*2){
    //std::cout << "== ";
    //PrintString();
    return;
  }
  //Generate Possible Choices;
  std::vector<char> choice = {'(', ')'};
  for(char c : choice){
    if(IsValid(c)){
      pars.push_back(c);
      //if(Solve()){
      //  return true;
      //}
      Solve();
      pars.pop_back();
    }
  }

}

int main(){
  Solve();
  return 0;
}
