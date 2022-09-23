#include <iostream>

template <typename Z>
class Stack{
  Z * arr;
  size_t alloc_size;
  size_t internal_size;
  bool destroyed;
  void resize(const size_t& num){
    if(arr == nullptr){
      arr = new Z[num];
      alloc_size = num;
    }else{
      Z * temp = arr;
      arr = new Z[num];
      for(size_t i=0; i<alloc_size; i++){
        arr[i] = temp[i];
      }
      alloc_size = num;
      delete [] temp;
    }
  }
public:
  Stack(): arr(nullptr), alloc_size(0), internal_size(0), destroyed(false){
  }
  Stack(const size_t &num): Stack(){
    resize(num);
  }
  Stack(const Stack &rhs): Stack(){
    if(rhs.internal_size > 0 && !rhs.destroyed){
      resize(rhs.alloc_size);
      for(size_t i=0; i<rhs.internal_size; i++){
        arr[i] = rhs.arr[i];
      }
      internal_size = rhs.internal_size;
    }
  }
  Stack& operator=(const Stack &rhs){
    Stack tmp(rhs);
    std::swap(arr, tmp.arr);
    std::swap(alloc_size, tmp.alloc_size);
    std::swap(internal_size, tmp.internal_size);
    std::swap(destroyed, tmp.destroyed);
    return *this;
  }
  void push(const Z& data){
    if(!destroyed){
      if(alloc_size == 0){
        resize(2);
      }
      arr[internal_size] = data;
      ++internal_size;
      if(internal_size == alloc_size){
        resize(alloc_size * 2);
      }
    }
  }
  void pop(){
    if(!destroyed){
      if(internal_size > 0){
        --internal_size;
      }
    }
  }
  bool empty(){
    return internal_size == 0;
  }
  size_t size(){
    return internal_size;
  }
  Z& top(){
    return arr[internal_size-1];
  }
  void print(){
    if(!destroyed){
      std::cout << "Allocation size = " << alloc_size << std::endl;
      std::cout << "Internal size = " << internal_size << std::endl;
      for(size_t i=0; i<internal_size; i++){
        std::cout << arr[i] << " ";
      }
      std::cout << std::endl;
    }
  }
  void destroy(){
    if(!destroyed){
      delete [] arr;
      arr = nullptr;
      //ptr = 0;
      alloc_size = 0;
      internal_size = 0;
      destroyed = true;
    }
  }
  ~Stack(){
    destroy();
  }
};

int main(){
  Stack<int> a;
  a.push(10);
  a.push(20);
  a.push(30);
  Stack<int> b;
  b = a;
  //std::cout << a.top() << std::endl;
  //std::cout << a.size() << std::endl;
  //std::cout << a.empty() << std::endl;
  a.print();
  b.print();
  return 0;
}
