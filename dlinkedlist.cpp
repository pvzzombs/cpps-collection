#include <iostream>

struct dll{
  int x;
  dll * prev;
  dll * next;
  dll(){
    prev = nullptr;
    next = nullptr;
  }
};

class double_ll{
  dll * head;
  int size_;
  bool destroyed;
public:
  void init(int num){
    if(head == nullptr){
      head = new dll;
      head->x = num;
      ++size_;
    }
  }
  double_ll(): head(nullptr), size_(0), destroyed(false){
  }
  void push_back(int num){
    dll * current = head;
    if(current != nullptr){
      while(current->next != nullptr){
        current = current->next;
      }
      current->next = new dll;
      current->next->x = num;
      current->next->prev = current;
    }else{
      head = new dll;
      head->x = num;
    }
    ++size_;
  }
  void pop_back(){
    dll * current = head;
    if(current != nullptr){
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
  void insert(int index, int num){
    dll * current = head;
    int i=0;
    if(current != nullptr){
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
        dll * a = new dll;
        a->x = num;

        a->next = current;
        current->prev = a;

        head = a;
      }else{
        dll * a = current->prev;
        dll * b = new dll;
        b->x = num;

        a->next = b;
        current->prev = b;

        b->next = current;
        b->prev = a;
      }  
    }else{
      head = new dll;
      head->x = num;
    }
    ++size_;
  }
  void remove(int index){
    dll * current = head;
    int i=0;
    if(current != nullptr){
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
        dll * y = current->next;
        y->prev = nullptr;
        delete current;
      }else if(current->next == nullptr){
        dll * w = current->prev;
        w->next = nullptr;
        delete current;
      }else{
        dll * w = current->prev;
        dll * y = current->next;
        w->next = y;
        y->prev = w;
        delete current;
      }
      --size_;
    }else{
      std::cerr << "Nothing to remove" << std::endl;
    }
  }
  void print(){
    dll * current = head;
    if(current != nullptr){
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
    dll * current = head;
    if(current != nullptr){
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
  dll * at(int index){
    dll * current = head;
    int i=0;
    if(current != nullptr){
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
  int size(){
    return size_;
  }
  void sort(){
    for(int i=0; i<size_; i++){
      for(int j=i+1; j<size_; j++){
        //std::cout << i << " " << j << std::endl;
        if(at(j)->x < at(i)->x){
          //std::cout << i << " " << j << std::endl;
          int n = at(j)->x;
          remove(j);
          insert(i, n);
          //remove(j+1);
        }
      }
    }
  }
  void rsort(){
    for(int i=0; i<size_; i++){
      for(int j=i+1; j<size_; j++){
        if(at(j)->x > at(i)->x){
          int n = at(j)->x;
          remove(j);
          insert(i, n);
          //remove(j+1);
        }
      }
    }
  }
  void destroy(){
    dll * current = head;
    if(!destroyed){
      while(current != nullptr){
        dll * temp = current->next;
        delete current;
        current = temp;
        --size_;
      }
      destroyed = true;
      //std::cout << "Destroyed" << std::endl;
    }
  }
  ~double_ll(){
    destroy();
  }
};

int main(){
  double_ll a;
  a.push_back(1);
  a.push_back(4);
  a.push_back(3);
  a.push_back(2);
  //a.insert(0, 0);
  //a.remove(3);
  a.print();
  //a.rprint();
  a.rsort();
  a.print();
  std::cout << a.size() << std::endl;
  return 0;
}
