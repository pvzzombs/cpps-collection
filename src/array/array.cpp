#include <cstddef>
#include <initializer_list>
#include <iostream>

template <typename Z>
class Array{
  Z * arr;
  size_t alloc_size;
  size_t internal_size;
  bool destroyed;

public:
  Array(): arr(nullptr), alloc_size(0), internal_size(0), destroyed(false){}
  Array(std::initializer_list<Z> args){
    arr = new Z[args.size()];
    alloc_size = args.size();
    internal_size = alloc_size;
    size_t i=0;
    for(Z data : args){
      arr[i] = data;
      ++i;
    }
  }
  Array& operator=(std::initializer_list<Z> args){
    if(alloc_size == 0 && !destroyed){
      arr = new Z[args.size()];
      alloc_size = args.size();
      internal_size = alloc_size;
      size_t i=0;
      for(Z data : args){
        arr[i] = data;
        ++i;
      } 
    }
    //std::cout << "Called" << std::endl;
    return *this;
  }
  inline Z& at(size_t index){
    if(arr != nullptr && !destroyed){
      if(index < internal_size){
        return arr[index];
      }
    }
    throw;
  }
  void print(){
    for(size_t i=0; i<internal_size; i++){
      std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
  }
  inline bool empty(){
    return internal_size == 0;
  }
  inline size_t size(){
    return internal_size;
  }
  void destroy(){
    if(!destroyed){
      if(alloc_size > 0){
        delete [] arr;
      }
      arr = nullptr;
      alloc_size = 0;
      internal_size = 0;
      destroyed = true;
    }
  }
  ~Array(){
    destroy();
  }
};

int main(){
  Array<int> a;
  a = {1, 2, 3, 4, 5};
  a.print();
  std::cout << a.at(0) << std::endl;
  std::cout << a.at(4) << std::endl;
  return 0;
}
