#include <iostream>
#include <vector>

void Merge(std::vector<int> &arr, int beg, int mid, int end){
  int i=0, j=0, k=0;
  int m = mid - beg + 1;
  int n = end - mid;

  std::vector<int> out(m+n);
  while(i < m && j < n){
    if(arr.at(beg+i) < arr.at(mid+1+j)){
      out.at(k) = arr.at(beg+i);
      k++; i++;
    }else{
      out.at(k) = arr.at(mid+1+j);
      k++; j++;
    }
  }
  
  while(i<m){
    out.at(k) = arr.at(beg+i);
    k++; i++;
  }
  
  while(j<n){
    out.at(k) = arr.at(mid+1+j);
    k++; j++;
  }
 
  k=0;
  for(int q=beg; q<=end; q++){
    arr.at(q) = out.at(k++);
  }
}

void MergeSort(std::vector<int> &arr, int beg, int end){
  //std::cout << beg << std::endl;
  //std::cout << end << std::endl;
  if(beg < end){
    int mid = (beg + end) / 2;
    MergeSort(arr, beg, mid);
    MergeSort(arr, mid+1, end);
    Merge(arr, beg, mid ,end);
  }
}

int main(int argc, char *argv[]) {
  std::vector<int> a= {8,6,7,5,4};
  MergeSort(a,0,a.size()-1);
  for(int q : a){
    std::cout << q << std::endl;
  }
  return 0;
}
