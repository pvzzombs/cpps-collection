#include <iostream>
#include <vector>

int BinarySearch(std::vector<int> nums, int find){
  if(nums.size() < 2){
    return -1;
  }
  int l=0;
  int r=nums.size() - 1;
  int mid;
  while(l<=r){
    mid = (l+r)/2;
    if(nums.at(mid) == find){
      return mid;
    }else if(nums.at(mid) > find){
      r = mid - 1;
    }else{
      l = mid + 1;
    }
  }
  
  if(nums.at(mid) == find){
    return mid;
  }else{
    return -1;
  }
}

int main(int argc, char *argv[]) {
  std::vector<int> arr= {1,3,5};
  std::cout << BinarySearch(arr, 5) << std::endl;
  return 0;
}