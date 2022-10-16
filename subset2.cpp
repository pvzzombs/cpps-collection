#include <iostream>
#include <vector>

void Subset(
  std::vector<std::vector<int>> & res,
  std::vector<int> & sets,
  std::vector<int> & nums,
  int i
  ){
  if(i >= nums.size()){
    res.push_back(sets);
    return;
  }
  
  sets.push_back(nums.at(i));
  Subset(res, sets, nums, i+1);
  
  sets.pop_back();
  Subset(res, sets, nums, i+1);
}

int main(int argc, char *argv[]) {
  std::vector<std::vector<int>> res;
  std::vector<int> sets;
  std::vector<int> nums = {1,2,3};
  int i = 0;
  Subset(res, sets, nums, i);
  for(int i=0; i<res.size(); i++){
    std::cout << "{";
    int len = res.at(i).size();
    for(int j=0; j<len; j++){
      std::cout << res.at(i).at(j);
      if(j + 1 < len){
        std::cout << ", ";
      }
    }
    std::cout << "}" << std::endl;
  }
  return 0;
}