#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<int> A= {2,3,4,5};
  std::vector<int> B= {1,2,3,4,5,6};
  int m = A.size();
  int n = B.size();
  int length = m + n;
  std::vector<int> arr(length);
  
  int i=0, j=0, k=0;
  while(i < m && j < n){
    if(A.at(i) < B.at(j)){
      arr.at(k) = A.at(i);
      i++; k++;
    }else{
      arr.at(k) = B.at(j);
      j++; k++;
    }
  }
  
  while(i < m){
    arr.at(k) = A.at(i);
    i++; k++;
  }
  
  while(j < n){
    arr.at(k) = B.at(j);
    j++; k++;
  }
  
  
  for(int q=0; q<arr.size(); q++){
    std::cout << arr.at(q) << std::endl;
  }
  return 0;
}