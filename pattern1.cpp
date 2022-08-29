#include <iostream>
#include <vector>

void PrintArray(std::vector<int> & arr){
  for(size_t i=0; i<arr.size(); i++){
    std::cout << arr.at(i) << " ";
  }
  std::cout << std::endl;
}

std::vector<int> GenArray(int n, int twos){
  std::vector<int> out(n);
  for(size_t i=0; i<out.size(); i++){
    out.at(i) = 1;
  }
  for(size_t i=0; i<twos; i++){
    out.at(i) = 2;
  }
  return out;
} 

void Gen(int num){
  int n = num;
  int twos = 0;
  int begin, end, last_two;
  std::vector<int> arr = GenArray(num, 0);
  PrintArray(arr);
  while(true){
    n -= 1;
    twos += 1;
    std::cout << "n and twos are " << n << " " << twos << std::endl;
    if(n < twos){
      break;
    }
    arr = GenArray(n, twos);
    PrintArray(arr);
    last_two = twos - 1;
    begin = last_two;
    end = arr.size() - 1;
    while(begin > -1){
      for(int i=begin; i < end; i++){
        std::swap(arr.at(i), arr.at(i+1));
        PrintArray(arr);
      }
      begin--;
      end--;
    }
  }
  
}

int main(int argc, char *argv[]) {
  Gen(6);
  return 0;
}