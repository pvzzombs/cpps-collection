#include <iostream>
#include <vector>
#include <sstream>

int len_of_nums; int nth; 
std::vector<int> inputs;
int nth_result = 0;

int error_flag = 0;
int max_depth = 5;

enum SeqType { kARIT_SEQ, kGEO_SEQ };
struct MsItem{
  SeqType type;
  int num;
};
std::vector<MsItem> ms_stack;

bool IsCommonDiff(std::vector<int> &arr){
  bool cd = true;
  for(int i=0; i<arr.size()-1; i++){
    if(arr[i] != arr[i+1]){
      cd = false;
      break;
    }
  }
  return cd;
}

bool IsCommonRatio(std::vector<int> &arr){
  bool cd = true;
  for(int i=0; i<arr.size()-1; i++){
    if(arr[i] != arr[i+1]){
      cd = false;
      break;
    }
  }
  return cd;
}

void MultiStage(std::vector<int> &arr, int index, int depth, int N){
  if(depth == max_depth || arr.size() < 2){
    error_flag = 1;
    return;
  }
  
  std::vector<int>  arr2, arr3;
  arr2.resize(arr.size() - 1);
  arr3.resize(arr.size() - 1);

  // test arithmetic seq
  for(int i=0; i<arr2.size(); i++){
    arr2.at(i) = arr.at(i+1) - arr.at(i);
    // std::cout << arr2.at(i) <<  std::endl;
  }
  
  for(int i=0; i<arr2.size(); i++){
    arr3.at(i) = arr.at(i+1) / arr.at(i);
    // std::cout << arr2.at(i) <<  std::endl;
  }
  
  bool is_cd = IsCommonDiff(arr2);
  bool is_cr = IsCommonRatio(arr3);
  
  if(is_cd){
    int cd = arr2.at(0);
    for(int i=index; i<nth; i++){
      ms_stack.at(i).type = kARIT_SEQ;
      ms_stack.at(i).num = cd;
    }
    
    /*std::cout << "[";
    for(int i=0; i<ms_stack.size(); i++){
      std::cout <<  ms_stack.at(i) << ", ";
    }
    std::cout << "]" <<  std::endl;*/
  }else if(is_cr){
    int cd = arr3.at(0);
    for(int i=index; i<nth; i++){
      ms_stack.at(i).type = kGEO_SEQ;
      ms_stack.at(i).num = cd;
    }
    
    std::cout << "[";
    for(int i=0; i<ms_stack.size(); i++){
      std::cout <<  ms_stack.at(i).num << ", ";
    }
    std::cout << "]" <<  std::endl;
  }else{
    ms_stack.at(index).type = kARIT_SEQ;
    ms_stack.at(index).num = arr.at(index);
    MultiStage(arr2, index+1, depth+1, N-1);
    for(int i=index+1; i<nth; i++){
      switch(ms_stack.at(i).type){
        case kARIT_SEQ:
          ms_stack.at(i).num = ms_stack.at(i).num + ms_stack.at(i-1).num;
          break;
        case kGEO_SEQ:
          ms_stack.at(i).num = ms_stack.at(i).num * ms_stack.at(i-1).num;
          ms_stack.at(i).type = ms_stack.at(i-1).type;
          break;
      }
      //std::cout << ms_stack.at(i) << " ";
    }
    //std::cout <<  std::endl;
    
    std::cout << "[";
    for(int i=0; i<ms_stack.size(); i++){
      std::cout <<  ms_stack.at(i).num << " op " <<  ms_stack.at(i).type  << ", ";
    }
    std::cout << "]" <<  std::endl;
  }
}

void FindNth(){
  
  // Multi Stage
  ms_stack.clear();
  //ms_stack.reserve(nth);
  ms_stack.resize(nth);
  MultiStage(inputs, 0, 0, nth);
  
  for(int i=1; i<nth; i++){
    switch(ms_stack.at(i).type){
      case kARIT_SEQ:
        ms_stack.at(i).num = ms_stack.at(i).num + ms_stack.at(i-1).num;
        break;
      case kGEO_SEQ:
        ms_stack.at(i).num = ms_stack.at(i).num * ms_stack.at(i-1).num;
        ms_stack.at(i).type = ms_stack.at(i-1).type;
        break;
    }
    //std::cout << ms_stack.at(i) << " ";
  }
  
  nth_result = ms_stack.at(nth - 1).num;
}


void Driver(){
  char choice = '\0';
  std::string temp;
  do{
    std::cout << "-------------------" << std::endl;
    std::cin >> len_of_nums;
    std::cin >> nth;
    
    inputs.clear();
    //inputs.reserve(len_of_nums);
    inputs.resize(len_of_nums);
    
    for(int i=0; i<len_of_nums; i++){
      std::cin >> inputs.at(i);
    }
    FindNth();
    std::cout <<  nth_result << std::endl;
    //std::cin.clear();
    std::cin.ignore(1000, '\n');
    std::cout << "Press n to quit: ";
    std::getline(std::cin, temp);
    if(temp.size()){
      choice = temp.at(0);
    }
  }while(choice != 'n' &&  choice != 'N'); 
}

int main(int argc, char *argv[]) {
  Driver();
  return 0;
}
