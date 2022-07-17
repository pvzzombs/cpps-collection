#include <iostream>
int arr[6];
int main(int argc, char *argv[]) {
  using namespace std;
  /* insert code here */
  int length = 6;
  int i=0, j=1, k=2;
  while(1){
    cout << i << " " << j << " " << k << endl;
    if(k == length-1){
      if(j == length-2){
        if(i== length-3){
          break;
        }else{
          ++i;
          j=i+1;
          k=j+1;
        }
      }else{
        ++j;
        k=j+1;
      }
    }else{
      ++k;
    }
  }
  cout << "Done" << endl;
  return 0;
}