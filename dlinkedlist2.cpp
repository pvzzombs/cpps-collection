#include <iostream>
#include <exception>

template<typename Z>
class Dll{
  struct DllNode{
    Z data;
    DllNode * prev;
    DllNode * next;
    DllNode(){
      prev = nullptr;
      next = nullptr;
    }
  };
  DllNode * head;
  DllNode * tail;
  size_t internal_size;
  bool destroyed;
  public:
  class DllError: public std::exception{
    virtual const char* what() const throw(){
      return "Invalid memory location or invalid index or value does not exist";
    }
  };
  inline void init(){
    head = new DllNode;
    tail = new DllNode;
    head->next = tail;
    tail->prev = head;
  }
  Dll(): head(nullptr), tail(nullptr), internal_size(0), destroyed(false){
    init();
  }
  Dll(const Dll &rhs): head(nullptr), tail(nullptr), internal_size(0), destroyed(false){
    init();
    if(rhs.internal_size > 0 && !rhs.destroyed){
      DllNode * source = rhs.head->next;
      DllNode * a = head;
      DllNode * b = nullptr;
      while(source != rhs.tail){
        b = new DllNode;
        b->data = source->data;
        a->next = b;
        b->prev = a;
        source = source->next;
        a = b;
        b = nullptr;
        ++internal_size;
      }
      a->next = tail;
      tail->prev = a;
    }
  }
  Dll& operator=(const Dll &rhs){
    Dll tmp(rhs);
    std::swap(head, tmp.head);
    std::swap(tail, tmp.tail);
    std::swap(internal_size, tmp.internal_size);
    std::swap(destroyed, tmp.destroyed);
    return *this;
  }
  void push_back(Z m){
    if(!destroyed){
      DllNode * n = new DllNode;
      n->data = m;
      n->next = tail;
      n->prev = tail->prev;
      tail->prev->next = n;
      tail->prev = n;
      ++internal_size;
    }
  }
  void pop_back(){
    if(internal_size > 0 && !destroyed){
      DllNode * temp = tail->prev;
      temp->prev->next = tail;
      tail->prev = temp->prev;
      delete temp;
      --internal_size;
    }
  }
  void push_front(Z m){
    if(!destroyed){
      DllNode * n = new DllNode;
      n->data = m;
      n->prev = head;
      n->next = head->next;
      head->next->prev = n;
      head->next = n;
      ++internal_size;
    }
  }
  void pop_front(){
    if(internal_size > 0 && !destroyed){
      DllNode * temp = head->next;
      temp->next->prev = head;
      head->next = temp->next;
      delete temp;
      --internal_size;
    }
  }
  void insert(size_t index, Z m){
    if(!destroyed){
      DllNode * current = head->next;
      size_t i=0;
      while(i != index && current != tail){
        current = current->next;
        ++i;
      }
      DllNode * n = new DllNode;
      n->data = m;
      n->prev = current->prev;
      n->next = current;
      current->prev->next = n;
      current->prev = n;
      ++internal_size;
    }
  }
  void remove(size_t index){
    if(internal_size > 0 && index < internal_size && !destroyed){
      DllNode * current = head->next;
      size_t i=0;
      while(i != index && current->next != tail){
        current = current->next;
        ++i;
      }
      current->prev->next = current->next;
      current->next->prev = current->prev;
      delete current;
      --internal_size;
    }
  }
  inline void erase(size_t index){
    remove(index);
  } 
  void print(){
    if(!destroyed){
      DllNode * current = head->next;
      while(current != tail){
        std::cout << "[" << current->data << "]" << " ";
        current = current->next;
      }
      std::cout << std::endl;
    }
  }
  void rprint(){
    if(!destroyed){
      DllNode * current = tail->prev;
      while(current != head){
        std::cout << "[" << current->data << "]" << " ";
        current = current->prev;
      }
      std::cout << std::endl;
    }
  }
  inline Z& at(size_t index){
    if(internal_size > 0 && index < internal_size && !destroyed){
      DllNode * current = head->next;
      size_t i=0;
      while(i != index && current->next != tail){
        current=current->next;
        ++i;
      }
      return current->data;
    }
    DllError err; throw err;
  } 
  inline Z& front(){
    if(internal_size > 0 && !destroyed){
      return head->next->data;
    }
    DllError err; throw err;
  }
  inline Z& back(){
    if(internal_size > 0 && !destroyed){
      return tail->prev->data;
    }
    DllError err; throw err;
  }
  inline int size(){
    return internal_size;
  }
  inline bool empty(){
    return internal_size == 0;
  }
  void reverse(){
    if(internal_size > 1 && !destroyed){
      DllNode * current = head;
      while(current != nullptr){
        DllNode * temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
      }
      DllNode * temp = head;
      head = tail;
      tail = temp;
    }
  }
  void sort(){
    
  } 
  void rsort(){
    
  }
  void del(){
    DllNode * current = head->next;
    DllNode * temp;
    while(current != tail){
      temp = current->next;
      delete current;
      current = temp;
    }
    internal_size = 0;
    head->next = tail;
    tail->prev = head;
  }
  void clear(){
    del();
  }
  void destroy(){
    if(!destroyed){
      del();
      delete head;
      delete tail;
      head = nullptr;
      tail = nullptr;
      destroyed = true;
    }
  }
  ~Dll(){
    destroy();
  }
};

int main(){
  Dll<int> a;
  a.push_back(10);
  a.push_back(4);
  a.push_back(3);
  a.push_back(5);
  a.push_back(2);
  a.push_back(0);
  a.back() = 12;
  a.reverse();
  a.print();
  a.rprint();
  Dll<int> b(a);
  b.rprint();
  b.push_front(1);
  b.push_front(7);
  b.print();
  //b.rprint();
  /*for(Dll::Iterator i=a.end()-1; i!=a.begin(); --i){
    std::cerr << "Hello " << std::endl;
    std::cout << "Data: " << *i << std::endl;
  }*/
  //a.remove(b);
  //a.sort(b, c);
  //a.rsort();
  std::cout << b.size() << std::endl;
  return 0;
}
