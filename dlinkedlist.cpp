#include <iostream>
#include <exception>

class Dll{
  struct DllNode{
    int x;
    DllNode * prev;
    DllNode * next;
    DllNode(){
      prev = nullptr;
      next = nullptr;
    }
  };
  DllNode * head;
  int size_;
  bool destroyed;
  public:
  class DllError: public std::exception{
    virtual const char* what() const throw(){
      return "Invalid memory location or value does not exist";
    }
  };
  class Iterator{
    friend class Dll;
    DllNode * ip;
    bool is_begin, is_end;
    Iterator operator+(size_t i){
      Iterator tmp = *this;
      for(size_t j=0; j<i; j++){
        if(ip != nullptr){
          tmp.ip = tmp.ip->next;
        }
      }
      return tmp;
    }
    Iterator operator-(size_t i){
      Iterator tmp = *this;
      for(size_t j=0; j<i; j++){
        if(ip != nullptr){
          tmp.ip = tmp.ip->prev;
        }
      }
      return tmp;
    }
    public:
    Iterator(): ip(nullptr), is_begin(false),
    is_end(false){
    }
    Iterator& operator++(){
      if(ip != nullptr){
        ip = ip->next;
      }
      return *this;
    }
    Iterator& operator--(){
      if(ip != nullptr){
        ip = ip->prev;
      }
      return *this;
    }
    Iterator operator++(int t){
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    Iterator operator--(int t){
      Iterator tmp = *this;
      --(*this);
      return tmp;
    }
    int& operator*(){
      if(ip != nullptr){
        return ip->x;
      }
      DllError err;
      throw err;
    }
    bool operator!=(const Iterator& rhs){
      if((is_begin && rhs.is_end) ||
          (is_end && rhs.is_begin)){
        return ip != nullptr;
      }
      return ip != rhs.ip;
    }
    bool operator==(const Iterator& rhs){
      return ip == rhs.ip;
    }
  };
  inline void init(int num, bool b=false){
    if(head == nullptr && !destroyed){
      head = new DllNode;
      head->x = num;
      if(b){
        ++size_;
      }
    }
  }
  Iterator begin(){
    Iterator tmp;
    if(head != nullptr && !destroyed){
      tmp.ip = head;
      tmp.is_begin = true;
    }
    return tmp;
  }
  Iterator end(){
    Iterator tmp;
    DllNode * current = head;
    if(current != nullptr && !destroyed){
      while(current->next != nullptr){
        current = current->next;
      }
      tmp.ip = current;
      tmp.is_end = true;
    }
    return tmp;
  }
  Dll(): head(nullptr), size_(0), destroyed(false){
  }
  Dll(const Dll &rhs): head(nullptr), size_(0), destroyed(false){
    if(rhs.size_ > 0 && !rhs.destroyed){
      DllNode * current = nullptr;
      DllNode * rhs_ = rhs.head;
      head = new DllNode;
      head->x = rhs.head->x;
      current = head;
      ++size_;
      while(true){
        if(rhs_->next != nullptr){
          current->next = new DllNode;
          current->next->x = rhs_->next->x;
          current = current->next;
          rhs_ = rhs_->next;
          ++size_;
        }else{
          break;
        }
      }
    }
  }
  Dll& operator=(const Dll &rhs){
    Dll tmp(rhs);
    std::swap(head, tmp.head);
    std::swap(size_, tmp.size_);
    std::swap(destroyed, tmp.destroyed);
    return *this;
  }
  void push_back(int num){
    DllNode * current = head;
    if(current != nullptr && !destroyed){
      while(current->next != nullptr){
        current = current->next;
      }
      current->next = new DllNode;
      current->next->x = num;
      current->next->prev = current;
    }else{
      init(num);
    }
    ++size_;
  }
  void pop_back(){
    DllNode * current = head;
    if(current != nullptr && !destroyed){
      while(current->next != nullptr){
        current = current->next;
      }
      if(current->prev != nullptr){
        current->prev->next = nullptr;
      }else{
        head = nullptr;
      }
      delete current;
      --size_;
    }
  }
  void push_front(int num){
    DllNode * current = head;
    if(current != nullptr && !destroyed){
      DllNode * a = new DllNode;
      a->x = num;
      a->next = current;
      current->prev = a;
      head = a;
    }else{
      init(num);
    }
    ++size_;
  }
  void pop_front(){
    DllNode * current = head;
    if(current != nullptr && !destroyed){
      DllNode * y = current->next;
      if(y != nullptr){
        y->prev = nullptr;
        head = y;
      }else{
        head = nullptr;
      }
      delete current;
      --size_;
    }
  }
  void insert(int index, int num){
    DllNode * current = head;
    int i=0;
    if(current != nullptr && !destroyed){
      while(true){
        if(i == index){
          break;
        }
        if(current->next != nullptr){
          current = current->next;
          i++;
        }else{
          break;
        }
      }
      if(head == current){
        DllNode * a = new DllNode;
        a->x = num;

        a->next = current;
        current->prev = a;

        head = a;
      }else if(index < size_){
        DllNode * a = current->prev;
        DllNode * b = new DllNode;
        b->x = num;

        a->next = b;
        current->prev = b;

        b->next = current;
        b->prev = a;
      }else{
        current->next = new DllNode;
        current->next->x = num;
        current->next->prev = current;
      }
    }else{
      init(num);
    }
    ++size_;
  }
  void insert(Iterator i, int num){
    DllNode * current = i.ip;
    if(current != nullptr && !destroyed){ 
      if(head == current){
        DllNode * a = new DllNode;
        a->x = num;

        a->next = current;
        current->prev = a;

        head = a;
      }else{
        DllNode * a = current->prev;
        DllNode * b = new DllNode;
        b->x = num;

        a->next = b;
        current->prev = b;

        b->next = current;
        b->prev = a;
      }
    }else{
      init(num);
    }
    ++size_;
  }
  void remove(int index){
    DllNode * current = head;
    int i=0;
    if(current != nullptr && !destroyed){
      while(true){
        if(i == index){
          break;
        }
        if(current->next != nullptr){
          current = current->next;
          i++;
        }else{
          break;
        }
      }
      if(head == current){
        DllNode * y = current->next;
        if(y != nullptr){
          y->prev = nullptr;
          head = y;
        }else{
          head = nullptr;
        }
        delete current;
      }else if(current->next == nullptr){
        DllNode * w = current->prev;
        w->next = nullptr;
        delete current;
      }else{
        DllNode * w = current->prev;
        DllNode * y = current->next;
        w->next = y;
        y->prev = w;
        delete current;
      }
      --size_;
    }else{
      std::cerr << "Nothing to remove" << std::endl;
    }
  }
  void remove(Iterator i){
    DllNode * current = i.ip;
    if(current != nullptr && !destroyed){
      if(head == current){
        DllNode * y = current->next;
        if(y != nullptr){
          y->prev = nullptr;
          head = y;
        }else{
          head = nullptr;
        }
        delete current;
      }else if(current->next == nullptr){
        DllNode * w = current->prev;
        w->next = nullptr;
        delete current;
      }else{
        DllNode * w = current->prev;
        DllNode * y = current->next;
        w->next = y;
        y->prev = w;
        delete current;
      }
      --size_;
    }else{
      std::cerr << "Nothing to remove" << std::endl;
    }
  }
  inline void erase(int index){
    remove(index);
  }
  inline void erase(Iterator i){
    remove(i);
  }
  void print(){
    DllNode * current = head;
    if(current != nullptr && !destroyed){
      while(true){
        std::cout << "[" << current->x << "]";
        if(current->next != nullptr){
          std::cout << " => ";
          current = current->next;
        }else{
          break;
        }
      }
      std::cout << std::endl;
    }
  }
  void rprint(){
    DllNode * current = head;
    if(current != nullptr && !destroyed){
      while(current->next != nullptr){
        current = current->next;
      }
      while(true){
        std::cout << "[" << current->x << "]";
        if(current->prev != nullptr){
          std::cout << " <= ";
          current = current->prev;
        }else{
          break;
        }
      }
      std::cout << std::endl;
    }
  }
  inline int& at(int index){
    DllNode * current = head;
    int i=0;
    if(current != nullptr && !destroyed){
      while(true){
        if(i == index){
          break;
        }
        if(current->next != nullptr){
          current = current->next;
          i++;
        }else{
          break;
        }
      }
    }else{
      DllError err;
      throw err;
    }
    return current->x;
  }
  inline int& at(Iterator i){
    DllNode * current = i.ip;
    if(current != nullptr && !destroyed){
      return current->x;
    }
    DllError err;
    throw err;
  }
  inline int& front(){
    DllNode * current = head;
    if(current != nullptr && !destroyed){
      return current->x;
    }
    DllError err;
    throw err;
  }
  inline int& back(){
    DllNode * current = head;
    if(current != nullptr && !destroyed){
      while(current->next != nullptr){
        current = current->next;
      }
      return current->x;
    }
    DllError err;
    throw err;
  }
  inline int size(){
    return size_;
  }
  inline bool empty(){
    return size_ == 0;
  }
  void reverse(){
    DllNode * current = head;
    if(current != nullptr && !destroyed){
      int s = size_;
      DllNode * temp = new DllNode;
      temp->x = current->x;
      while(current->next != nullptr){
        current = current->next;
        temp->prev = new DllNode;
        temp->prev->x = current->x;
        temp->prev->next = temp;
        temp = temp->prev;
      }
      clear();
      head = temp;
      size_ = s;
    }
  }
  void sort(){
    if(head != nullptr && !destroyed){
      for(int i=0; i<size_; i++){
        for(int j=i+1; j<size_; j++){
          if(at(j) < at(i)){
            int n = at(j);
            at(j) = at(i);
            at(i) = n;
          }
        }
      }
    }
  }
  void sort(Iterator a, Iterator b){
    if(head != nullptr && !destroyed){
      if(a.is_end){
        for(Iterator i=b; i!=a; ++i){
          for(Iterator j=i+1; j!=a; ++j){
            if(at(j) > at(i)){
              int n = at(j);
              at(j) = at(i);
              at(i) = n;
            }
          }
        }
      }else{
        for(Iterator i=a; i!=b; ++i){
          for(Iterator j=i+1; j!=b; ++j){
            if(at(j) < at(i)){
              int n = at(j);
              at(j) = at(i);
              at(i) = n;
            }
          }
        }
      }
    }
  }
  void rsort(){
    if(head != nullptr && !destroyed){
      for(int i=0; i<size_; i++){
        for(int j=i+1; j<size_; j++){
          if(at(j) > at(i)){
            int n = at(j);
            at(j) = at(i);
            at(i) = n;
          }
        }
      }
    }
  }
  void clear(){
    DllNode * current = head;
    while(current != nullptr){
      DllNode * temp = current->next;
      delete current;
      current = temp;
    }
    head = nullptr;
    size_ = 0;
  }
  void destroy(){
    DllNode * current = head;
    if(!destroyed){
      while(current != nullptr){
        DllNode * temp = current->next;
        delete current;
        current = temp;
      }
      head = nullptr;
      size_ = 0;
      destroyed = true;
      //std::cout << "Destroyed" << std::endl;
    }
  }
  ~Dll(){
    destroy();
  }
};

int main(){
  Dll a;
  a.push_back(10);
  a.push_back(4);
  a.push_back(3);
  a.push_back(5);
  a.push_back(2);
  a.push_back(0);
  a.print();
  /*for(Dll::Iterator i=a.end()-1; i!=a.begin(); --i){
    std::cerr << "Hello " << std::endl;
    std::cout << "Data: " << *i << std::endl;
  }*/
  //a.remove(b);
  //a.sort(b, c);
  //a.rsort();
  a.reverse();
  a.print();
  std::cout << a.size() << std::endl;
  return 0;
}
