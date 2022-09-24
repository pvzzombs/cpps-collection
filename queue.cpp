#include <iostream>

template <typename Z>
class Queue{
  Z * arr;
  size_t alloc_size;
  size_t internal_size;
  size_t l,r;
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
  Queue(): arr(nullptr), alloc_size(0), internal_size(0), l(0), r(0),  destroyed(false){
  }
  Queue(const size_t &num): Queue(){
    resize(num);
  }
  Queue(const Queue &rhs): Queue(){
    if(rhs.internal_size > 0 && !rhs.destroyed){
      resize(rhs.alloc_size);
      for(size_t i=0; i<rhs.alloc_size; i++){
        arr[i] = rhs.arr[i];
      }
      internal_size = rhs.internal_size;
      l = rhs.l;
      r = rhs.r;
    }
  }
  Queue& operator=(const Queue &rhs){
    Queue tmp(rhs);
    std::swap(arr, tmp.arr);
    std::swap(alloc_size, tmp.alloc_size);
    std::swap(internal_size, tmp.internal_size);
    std::swap(l, tmp.l);
    std::swap(r, tmp.r);
    std::swap(destroyed, tmp.destroyed);
    return *this;
  }
  void push(const Z& data){
    if(!destroyed){
      if(alloc_size == 0){
        resize(2);
      }
      arr[r] = data;
      ++r;
      ++internal_size;
      if(r == alloc_size){
        resize(alloc_size * 2);
      }
    }
  }
  void pop(){
    if(!destroyed){
      if(internal_size > 0){
        ++l;
        --internal_size;
        if(l == r && r > 0){
          l = r = 0;
        }
      }
    }
  }
  bool empty(){
    return internal_size == 0;
  }
  size_t size(){
    return internal_size;
  }
  Z& front(){
    if(l != r){
      return arr[l];
    }
  }
  Z& back(){
    if(l != r){
      return arr[r-1];
    }
  }
  void print(){
    if(!destroyed){
      std::cout << "Allocation size = " << alloc_size << std::endl;
      std::cout << "Internal size = " << internal_size << std::endl;
      std::cout << "l is " << l << " and r is " << r << std::endl;
      for(size_t i=l; i<r; i++){
        std::cout << arr[i] << " ";
      }
      std::cout << std::endl;
    }
  }
  void destroy(){
    if(!destroyed){
      delete [] arr;
      arr = nullptr;
      alloc_size = 0;
      internal_size = 0;
      l = 0;
      r = 0;
      destroyed = true;
    }
  }
  ~Queue(){
    destroy();
  }
};

int main(){
  Queue<int> a;
  a.push(10);
  a.push(20);
  a.push(30);
  a.print();
  a.pop();
  Queue<int> b(a);
  //b = a;
  //std::cout << a.top() << std::endl;
  //std::cout << a.size() << std::endl;
  //std::cout << a.empty() << std::endl;
  //a.print();
  //a.pop();
  //a.pop();
  a.print();
  b.print();
  return 0;
}
