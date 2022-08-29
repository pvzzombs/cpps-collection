#include <iostream>
#include <vector>

void Subset(int num){
  std::vector<std::vector<int>> out = {{}};
  for(int i=1; i<=num; i++){
    //auto temp = out;
    size_t s = out.size();
    for(size_t j=0; j<s; j++){
      std::vector<int> x = out.at(j);
      x.push_back(i);
      out.push_back(x);
    }
  }
  
  for(size_t i=0; i<out.size(); i++){
    std::cout << "{";
    size_t len = out.at(i).size();
    for(size_t j=0; j<len; j++){
      std::cout << out.at(i).at(j);
      if(j+1 < len){
        std::cout << ", ";
      }
    }
    std::cout << "}" << std::endl;
  }
}

int main(int argc, char *argv[]) {
  Subset(3);
  /* insert code here */
  return 0;
}