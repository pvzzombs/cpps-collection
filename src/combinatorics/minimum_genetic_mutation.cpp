#include <iostream>
#include <string>
#include <vector>
//#include <queue>
//using namespace std;

std::vector<std::string> mut(std::string o, std::string n){
  std::vector<std::string> out;
  if(o.size() != n.size()){
    return out;
  }
  for(size_t i=0; i<o.size(); i++){
    if(o.at(i) != n.at(i)){
      char temp = o.at(i);
      o.at(i) = n.at(i);
      out.push_back(o);
      o.at(i) = temp;
    }
  }
  return out;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> bank = {"AACCGGTA", "AACCGCTA", "AAACGGTA"};
  std::string start = "AACCGGTT";
  std::string end = "AAACGGTA";
  
  size_t count = 0;
  bool quit = false;
  bool q = false;
  bool found_child = false;
  std::string parent;
  //std::string child;
  parent = start;
  
  //check if start is in the bank
  //if it is, count as mutation
  for(auto &b: bank){
    if(start == b){
      ++count;
      std::cout << "start is in the gene bank" << std::endl;
      break;
    }
  }
  
  while(!quit){
    found_child = false;
    q = false;
    //size_t c = childs.size();
    //auto muts = mut(start, end);
    std::cout << "Parent: " << parent << std::endl;
    auto muts = mut(parent, end);
    //std::cout << "Mutation size: " << muts.size() << std::endl;
    for(auto &m: muts){
      //std::cout << m << std::endl;
      for(auto &b: bank){
        if(m == b){
          std::cout << "Matched " << b << std::endl;
          parent = m;
          found_child = true;
          ++count;
          if(m == end){
            quit = true;
          }
          q = true;
          break;
        }
      } 
      if(quit || q) break;
    }
    if(!found_child){
      //No possible permutation in the gene bank
      quit = true;
      break;
    }
    //parent = child;
    //child = "";
    //std::cout << "Child: " << parent << std::endl;
  }
  std::cout << count << std::endl;
  return 0;
}