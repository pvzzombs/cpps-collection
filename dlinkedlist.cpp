#include <iostream>

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
  class iterator{
    friend class dll;
    dll_node * c;
    bool fh, ft;
    void to_null(){
      c = nullptr;
    }
    public:
    iterator(): c(nullptr), fh(false),
    ft(false){
    }
    iterator& operator++(){
      if(c != nullptr){
        c = c->next;
      }
      return *this;
    }
    iterator& operator--(){
      if(c != nullptr){
        c = c->prev;
      }
      return *this;
    }
    int& operator*(){
      if(c != nullptr){
        return c->x;
      }
    }
    bool operator!=(iterator rhs){
      if(fh && rhs.c != nullptr){
        rhs.to_null();
      }
      if(ft && rhs.c != nullptr){
        rhs.to_null();
      }
      return c != rhs.c;
    }
    bool operator==(iterator rhs){
      if(fh && rhs.c != nullptr){
        rhs.to_null();
      }
      if(ft && rhs.c != nullptr){
        rhs.to_null();
      }
      return c == rhs.c;
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
      tmp.c = head;
      tmp.fh = true;
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
      tmp.c = current;
      tmp.ft = true;
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
  inline void erase(int index){
    remove(index);
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
  inline dll_node * at(int index){
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
      std::cerr << "Error, double linked list is uninitialized" << std::endl;
    }
    return current;
  }
  inline dll_node * front(){
    dll_node * current = head;
    if(current != nullptr && !destroyed){
      return current;
    }
    return nullptr;
  }
  inline dll_node * back(){
    dll_node * current = head;
    if(current != nullptr && !destroyed){
      while(current->next != nullptr){
        current = current->next;
      }
      return current;
    }
    return nullptr;
  }
  inline int size(){
    return size_;
  }
  inline bool empty(){
    return size_ == 0;
  }
  void sort(){
    if(head != nullptr && !destroyed){
      for(int i=0; i<size_; i++){
        for(int j=i+1; j<size_; j++){
          //std::cout << i << " " << j << std::endl;
          if(at(j)->x < at(i)->x){
            //std::cout << i << " " << j << std::endl;
            int n = at(j)->x;
            remove(j);
            insert(i, n);
          }
        }
      }
    }
  }
  void rsort(){
    if(head != nullptr && !destroyed){
      for(int i=0; i<size_; i++){
        for(int j=i+1; j<size_; j++){
          if(at(j)->x > at(i)->x){
            int n = at(j)->x;
            remove(j);
            insert(i, n);
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
      --size_;
    }
    head = nullptr;
  }
  void destroy(){
    dll_node * current = head;
    if(!destroyed){
      while(current != nullptr){
        dll_node * temp = current->next;
        delete current;
        current = temp;
        --size_;
      }
      head = nullptr;
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
  a.push_back(1);
  a.push_back(4);
  a.push_back(3);
  a.push_back(2);
  for(dll::iterator i=a.begin(); i!=a.end(); ++i){
    std::cerr << "Hello " << std::endl;
    std::cout << "Data: " << *i << std::endl;
  }
  //std::cout << a.size() << std::endl;
  return 0;
}
