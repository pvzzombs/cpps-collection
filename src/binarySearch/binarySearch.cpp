#include <iostream>
#include <vector>

int BinarySearch(std::vector<int> nums, int find){
  if(nums.size() < 2){
    return -1;
  }
  int l=0;
  int r=nums.size() - 1;
  int mid;
  while(true){
    mid = (l+r)/2;
    if(l == mid){
      break;
    }
    if(nums.at(mid) == find){
      return mid;
    }else if(nums.at(mid) > find){
      r = mid;
    }else{
      l = mid;
    }
  }
  
  if(nums.at(l) == find){
    return l;
  }else if(nums.at(r) == find){
    return r;
  }else{
    return -1;
  }
}

int main(int argc, char *argv[]) {
  std::vector<int> arr= {1,3};
  std::cout << BinarySearch(arr, 0) << std::endl;
  return 0;
}