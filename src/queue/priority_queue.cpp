#include <iostream>

template <typename Z>
class PriorityQueue{
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
  PriorityQueue(): arr(nullptr), alloc_size(0), internal_size(0), destroyed(false){
  }
  PriorityQueue(const size_t &num): PriorityQueue(){
    resize(num);
  }
  PriorityQueue(const PriorityQueue &rhs): PriorityQueue(){
    if(rhs.internal_size > 0 && !rhs.destroyed){
      resize(rhs.alloc_size);
      for(size_t i=0; i<rhs.internal_size; i++){
        arr[i] = rhs.arr[i];
      }
      internal_size = rhs.internal_size;
    }
  }
  PriorityQueue& operator=(const PriorityQueue &rhs){
    PriorityQueue tmp(rhs);
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

      int i = internal_size;

      while(i > 0){
        int parent = (i-1)/2;
        if(arr[parent] > arr[i]){
          std::swap(arr[parent], arr[i]);
        }else{
          break;
        }
      }

      ++internal_size;
      if(internal_size == alloc_size){
        resize(alloc_size * 2);
      }
    }
  }
  void pop(){
    if(!destroyed){
      if(internal_size > 0){
        bool cont = true;

        arr[0] = arr[internal_size-1];
        int i = 0;
        int l = 1;
        int r = 2;

        while(l<internal_size && r<internal_size){
          if(arr[l] <= arr[r] && arr[l] < arr[i]){
            std::swap(arr[l], arr[i]);
            i = l;
          }else if(arr[l] > arr[r] && arr[r] < arr[i]){
            std::swap(arr[r], arr[i]);
            i = r;
          }else{
            cont = false;
            break;
          }
          l = (2 * i) + 1;
          r = (2 * i) + 2;
        }

        if(cont && l < internal_size){
          if(arr[l] < arr[i]){
            std::swap(arr[l], arr[i]);
          }
        }

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
  Z& front(){
    return arr[0];
  }
  Z& back(){
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
      if(alloc_size){
        delete [] arr;
      }
      arr = nullptr;
      //ptr = 0;
      alloc_size = 0;
      internal_size = 0;
      destroyed = true;
    }
  }
  ~PriorityQueue(){
    destroy();
  }
};

int main(){
  PriorityQueue<int> a;
  a.push(5);
  a.push(3);
  a.push(6);
  a.push(4);
  //PriorityQueue<int> b;
  //b = a;
  //std::cout << a.top() << std::endl;
  //std::cout << a.size() << std::endl;
  //std::cout << a.empty() << std::endl;
  a.print();
  a.pop();
  a.print();
  //b.print();
  return 0;
}
