#include <iostream>
#include <vector>
#include <sstream>

void Solution(std::vector<std::vector<std::string>> input, std::vector<int> c_max, std::stringstream& out){
  std::vector<int> c(c_max.size());
  for(int i=0; i<c.size(); i++){
    c.at(i) = 0;
  }
  while(true){
    for(int i=0; i<c.size(); i++){
      out << input.at(i).at(c.at(i)) << " ";
    }
    
    out << std::endl;
    bool break_loop = true;
    for(int i=0; i<c.size(); i++){
      if(c.at(i) != c_max.at(i)){
        break_loop = false;
      }
    }
    
    if(break_loop){
      break;
    }
    c.at(0)++;
    for(int i=1; i<c.size(); i++){
      if(c.at(i-1) > c_max.at(i-1)){
        c.at(i-1) = 0;
        c.at(i)++;
      }
    }
  }
}


/*
2
3
3 a b c
3 1 2 3
3 x y z
2
3 A B C
3 + - *
*/

int main(int argc, char *argv[]) {
  int testcases, lines, cols;
  std::vector<int> max_clock;
  std::stringstream out;
  std::vector<std::vector<std::string>> inputs;
  std::cin >> testcases;
  for(int i=0; i<testcases; i++){
    std::cin >> lines;
    max_clock.resize(lines);
    inputs.resize(lines);
    for(int j=0; j<lines; j++){
      std::cin >> cols;
      max_clock.at(j) = cols - 1;
      inputs.at(j).resize(cols);
      for(int k=0; k<cols; k++){
        std::cin >> inputs.at(j).at(k);
      }
    }
    Solution(inputs, max_clock, out);
    inputs.clear();
    max_clock.clear();
  }
  std::cout << out.str();
}