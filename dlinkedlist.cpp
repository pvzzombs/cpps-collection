#include <iostream>
#include <exception>

class dll{
  struct dll_node{
    int x;
    dll_node * prev;
    dll_node * next;
    dll_node(){
      prev = nullptr;
      next = nullptr;
    }
  };
  dll_node * head;
  int size_;
  bool destroyed;
  public:
  class dll_error: public std::exception{
    virtual const char* what() const throw(){
      return "Invalid memory location or value does not exist";
    }
  };
  class iterator{
    friend class dll;
    dll_node * ip;
    bool is_begin, is_end;
    iterator operator+(size_t i){
      iterator tmp = *this;
      for(size_t j=0; j<i; j++){
        if(ip != nullptr){
          tmp.ip = tmp.ip->next;
        }
      }
      return tmp;
    }
    iterator operator-(size_t i){
      iterator tmp = *this;
      for(size_t j=0; j<i; j++){
        if(ip != nullptr){
          tmp.ip = tmp.ip->prev;
        }
      }
      return tmp;
    }
    public:
    iterator(): ip(nullptr), is_begin(false),
    is_end(false){
    }
    iterator& operator++(){
      if(ip != nullptr){
        ip = ip->next;
      }
      return *this;
    }
    iterator& operator--(){
      if(ip != nullptr){
        ip = ip->prev;
      }
      return *this;
    }
    int& operator*(){
      if(ip != nullptr){
        return ip->x;
      }
      dll_error err;
      throw err;
    }
    bool operator!=(const iterator& rhs){
      if((is_begin && rhs.is_end) ||
          (is_end && rhs.is_begin)){
        return ip != nullptr;
      }
      return ip != rhs.ip;
    }
    bool operator==(const iterator& rhs){
      return ip == rhs.ip;
    }
  };
  inline void init(int num, bool b=false){
    if(head == nullptr && !destroyed){
      head = new dll_node;
      head->x = num;
      if(b){
        ++size_;
      }
    }
  }
  iterator begin(){
    iterator tmp;
    if(head != nullptr && !destroyed){
      tmp.ip = head;
      tmp.is_begin = true;
    }
    return tmp;
  }
  iterator end(){
    iterator tmp;
    dll_node * current = head;
    if(current != nullptr && !destroyed){
      while(current->next != nullptr){
        current = current->next;
      }
      tmp.ip = current;
      tmp.is_end = true;
    }
    return tmp;
  }
  dll(): head(nullptr), size_(0), destroyed(false){
  }
  dll(const dll &rhs): head(nullptr), size_(0), destroyed(false){
    if(rhs.size_ > 0 && !rhs.destroyed){
      dll_node * current = nullptr;
      dll_node * rhs_ = rhs.head;
      head = new dll_node;
      head->x = rhs.head->x;
      current = head;
      ++size_;
      while(true){
        if(rhs_->next != nullptr){
          current->next = new dll_node;
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
  dll& operator=(const dll &rhs){
    dll tmp(rhs);
    std::swap(head, tmp.head);
    std::swap(size_, tmp.size_);
    std::swap(destroyed, tmp.destroyed);
    return *this;
  }
  void push_back(int num){
    dll_node * current = head;
    if(current != nullptr && !destroyed){
      while(current->next != nullptr){
        current = current->next;
      }
      current->next = new dll_node;
      current->next->x = num;
      current->next->prev = current;
    }else{
      init(num);
    }
    ++size_;
  }
  void pop_back(){
    dll_node * current = head;
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
    dll_node * current = head;
    if(current != nullptr && !destroyed){
      dll_node * a = new dll_node;
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
    dll_node * current = head;
    if(current != nullptr && !destroyed){
      dll_node * y = current->next;
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
    dll_node * current = head;
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
        dll_node * a = new dll_node;
        a->x = num;

        a->next = current;
        current->prev = a;

        head = a;
      }else if(index < size_){
        dll_node * a = current->prev;
        dll_node * b = new dll_node;
        b->x = num;

        a->next = b;
        current->prev = b;

        b->next = current;
        b->prev = a;
      }else{
        current->next = new dll_node;
        current->next->x = num;
        current->next->prev = current;
      }
    }else{
      init(num);
    }
    ++size_;
  }
  void insert(iterator i, int num){
    dll_node * current = i.ip;
    if(current != nullptr && !destroyed){ 
      if(head == current){
        dll_node * a = new dll_node;
        a->x = num;

        a->next = current;
        current->prev = a;

        head = a;
      }else{
        dll_node * a = current->prev;
        dll_node * b = new dll_node;
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
    dll_node * current = head;
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
        dll_node * y = current->next;
        if(y != nullptr){
          y->prev = nullptr;
          head = y;
        }else{
          head = nullptr;
        }
        delete current;
      }else if(current->next == nullptr){
        dll_node * w = current->prev;
        w->next = nullptr;
        delete current;
      }else{
        dll_node * w = current->prev;
        dll_node * y = current->next;
        w->next = y;
        y->prev = w;
        delete current;
      }
      --size_;
    }else{
      std::cerr << "Nothing to remove" << std::endl;
    }
  }
  void remove(iterator i){
    dll_node * current = i.ip;
    if(current != nullptr && !destroyed){
      if(head == current){
        dll_node * y = current->next;
        if(y != nullptr){
          y->prev = nullptr;
          head = y;
        }else{
          head = nullptr;
        }
        delete current;
      }else if(current->next == nullptr){
        dll_node * w = current->prev;
        w->next = nullptr;
        delete current;
      }else{
        dll_node * w = current->prev;
        dll_node * y = current->next;
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
  inline void erase(iterator i){
    remove(i);
  }
  void print(){
    dll_node * current = head;
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
    dll_node * current = head;
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
    dll_node * current = head;
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
      dll_error err;
      throw err;
    }
    return current->x;
  }
  inline int& at(iterator i){
    dll_node * current = i.ip;
    if(current != nullptr && !destroyed){
      return current->x;
    }
    dll_error err;
    throw err;
  }
  inline int& front(){
    dll_node * current = head;
    if(current != nullptr && !destroyed){
      return current->x;
    }
    dll_error err;
    throw err;
  }
  inline int& back(){
    dll_node * current = head;
    if(current != nullptr && !destroyed){
      while(current->next != nullptr){
        current = current->next;
      }
      return current->x;
    }
    dll_error err;
    throw err;
  }
  inline int size(){
    return size_;
  }
  inline bool empty(){
    return size_ == 0;
  }
  void reverse(){
    dll_node * current = head;
    if(current != nullptr && !destroyed){
      int s = size_;
      dll_node * temp = new dll_node;
      temp->x = current->x;
      while(current->next != nullptr){
        current = current->next;
        temp->prev = new dll_node;
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
  void sort(iterator a, iterator b){
    if(head != nullptr && !destroyed){
      if(a.is_end){
        for(iterator i=b; i!=a; ++i){
          for(iterator j=i+1; j!=a; ++j){
            if(at(j) > at(i)){
              int n = at(j);
              at(j) = at(i);
              at(i) = n;
            }
          }
        }
      }else{
        for(iterator i=a; i!=b; ++i){
          for(iterator j=i+1; j!=b; ++j){
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
    dll_node * current = head;
    while(current != nullptr){
      dll_node * temp = current->next;
      delete current;
      current = temp;
    }
    head = nullptr;
    size_ = 0;
  }
  void destroy(){
    dll_node * current = head;
    if(!destroyed){
      while(current != nullptr){
        dll_node * temp = current->next;
        delete current;
        current = temp;
      }
      head = nullptr;
      size_ = 0;
      destroyed = true;
      //std::cout << "Destroyed" << std::endl;
    }
  }
  ~dll(){
    destroy();
  }
};

int main(){
  dll a;
  a.push_back(10);
  a.push_back(4);
  a.push_back(3);
  a.push_back(5);
  a.push_back(2);
  a.push_back(0);
  a.print();
  /*for(dll::iterator i=a.end()-1; i!=a.begin(); --i){
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
