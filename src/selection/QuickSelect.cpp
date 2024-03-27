#include <iostream>
#include <vector>

int QuickSelectPartition(std::vector<int> &nums, int l, int r){
  //the pivot is the last element
  int pivot = nums.at(r);
  //after iterations, p is the position of the pivot
  int p = l;
  for(int i=l; i<r; i++){
    if(nums.at(i) <= pivot){
      std::swap(nums.at(p), nums.at(i));
      p++;
    }
  }
  std::swap(nums.at(p), nums.at(r));
  return p;
}

int QuickSelectAlgo(std::vector<int> &nums, int l, int r, int n){
  int p = QuickSelectPartition(nums, l, r);
  if(p > n){
    return QuickSelectAlgo(nums, l, p-1, n);
  }else if(p < n){
    return QuickSelectAlgo(nums, p+1, r, n);
  }else{
    return nums.at(p);
  };
}

int QuickSelect(std::vector<int> &nums, int n){
  return QuickSelectAlgo(nums, 0, nums.size()-1, nums.size()-n);
}

int main(int argc, char *argv[]) {
  std::vector<int> a = {5,4,3,2,1};
  // Select 2nd largest element
  std::cout << QuickSelect(a, 2);
  
}