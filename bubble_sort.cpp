#include <iostream>
#include <vector>


int main(){
  std::vector<int> arr = {5,4,3,2,1};

  for(int i=0; i<arr.size(); i++){
    for(int j=i+1; j<arr.size(); j++){
      if(arr[j] < arr[i]){
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
  for(int i=0; i<arr.size(); i++){
    std::cout << arr.at(i) << std::endl;
  }
  return 0;
}
