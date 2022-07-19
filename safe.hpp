#ifndef PVZZOMBS_SAFE_HEADER
#define PVZZOMBS_SAFE_HEADER

#include <iostream>
#include <exception>
#include <new>

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || __cplusplus>=201103L)
#include <initializer_list>
#endif

#ifdef SAFE_USE_NAMESPACE
namespace safe {
#endif

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 199711L && _MSVC_LANG<201103L) || (__cplusplus>=199711L && __cplusplus<201103L))
#define nullptr NULL
#endif

// Constant strings
const char * message_1 = "-- Found memory leak at ";
const char * message_2 = ", releasing...\n";
const char * message_3 = "Bad Memory Allocation";
const char * message_4 = "Dangling Memory should not be released";
const char * message_5 = "Array index is out of bounds";
const char * message_6 = "-- Memory allocation: ";
const char * message_7 = "-- Memory released: ";
const char * message_8 = "-- There is a problem releasing memory!\n";
const char * message_9 = "-- There is a problem allocating memory!\n";
const char * message_10 = " at line ";
const char * message_11 = " ~ at line ";
const char * message_12 = " ~ size ";
const char * message_13 = "-- New array at line ";
const char * message_14 = "-- Array released...";
const char * message_15 = "-- Array is empty";
const char * message_16 = "-- Array index out of bounds : index ";
const char * message_17 = "Array is not initialized";
const char * message_18 = "-- Warning: An array with size 0 will be initialized with a size of 1\n";
const char * message_19 = "-- Address found at ";
const char * message_20 = "-- Copy constructor called";
const char * message_21 = "-- Move constructor called";
const char * message_22 = "-- Copy assignment called";
const char * message_23 = "-- Move assignment called";
const char * message_24 = "-- std::initializer_list constructor called";
const char * message_25 = "-- std::initializer_list assignment called";
const char * message_26 = "-- (Memory Heap) An existing address found in heap, ignoring duplicate...\n";
const char * message_27 = "@@ Cannot allocate memory for memory_heap_debug!";

template <typename T>
class heap_linked_list{
public:
  heap_linked_list * RIGHT;
  T * address_holder;

  heap_linked_list(){
    RIGHT = nullptr;
    address_holder = nullptr;
  }

  heap_linked_list(T * addr_t){
    RIGHT = nullptr;
    address_holder = addr_t;
  }

};

template <typename T>
class mem_heap_debug{
private:
  heap_linked_list<T> * HEAD;
  bool HEAD_INIT;
  bool destroyed_;

public:
  mem_heap_debug(){
    destroyed_ = false;
    HEAD_INIT = false;
    HEAD = nullptr;
  }

  T * operator[] (size_t index) const {
    size_t counter_ = 0;
    if(HEAD_INIT){
      heap_linked_list<T> * temp_ = HEAD;
      while(!(temp_ == nullptr)){
        if(index == counter_){
          return temp_->address_holder;
        }
        if(!(temp_->RIGHT == nullptr)){
          temp_ = temp_->RIGHT;
          ++counter_;
        }else{
          break;
        }
      }
    }
    return nullptr;
  }

  bool add_address(T * addr_t){
    if(!HEAD_INIT){
      //newly used heap
      HEAD = new (std::nothrow) heap_linked_list<T>(addr_t);
      if(HEAD == nullptr){
        std::cout << message_27 << std::endl;
        return false;
      }
      HEAD_INIT = true;
    }else{
      heap_linked_list<T> * temp_ = HEAD;
      while(!(temp_ == nullptr)){
        if(temp_->address_holder == addr_t){
#ifdef DEBUG_
          std::cout << message_26;
#endif
          return false;
        }
        if(!(temp_->RIGHT == nullptr)){
          temp_ = temp_->RIGHT;
        }else{
          break;
        }
      }

      heap_linked_list<T> * TAIL = temp_;
      //always work from right then left
      TAIL->RIGHT = new (std::nothrow) heap_linked_list<T>(addr_t);
      //std::cout << (void *)TAIL->RIGHT << std::endl;
      if (TAIL->RIGHT == nullptr) {
        std::cout << message_27 << std::endl;
        return false;
      }
    }
    return true;
  }

  // remove the node 
  bool remove_address(T * addr_t){
    if(HEAD_INIT){
      heap_linked_list<T> * temp_ = HEAD, * prev_ = nullptr;
      bool has_right, has_left;
      while(!(temp_ == nullptr)){
        has_right = false; has_left = false;
        if(temp_->address_holder == addr_t){
          if( !(temp_->RIGHT == nullptr) )
            has_right = true;

          if( !(prev_ == nullptr) )
            has_left = true;

          if( has_left && has_right ){

            prev_->RIGHT = temp_->RIGHT;
          }else if( has_right && !has_left ){
            //we need to replace the head ofcourse
            HEAD = temp_->RIGHT;
          }else if( has_left && !has_right ){
            
            prev_->RIGHT = nullptr;
          }else{
            //this the head
            HEAD_INIT = false;
          }

          //note that we did not deleted the
          //allocation of addr_t, we just
          //deleted this node so we know
          //that it no longer exists
          delete temp_;
          return true;
        }
        if(!(temp_->RIGHT == nullptr)){
          prev_ = temp_;
          temp_ = temp_->RIGHT;
        }else{
          return false;
        }
      }
    }
    return false;
  }

  //delete or free the address holder and remove the node
  bool free_address(T * addr_t, bool preserve_ = false){
    if(HEAD_INIT){
      heap_linked_list<T> * temp_ = HEAD, * prev_ = nullptr;
      bool has_right, has_left;
      while(!(temp_ == nullptr)){
        has_right = false; has_left = false;
        if(temp_->address_holder == addr_t){
          if( !(temp_->RIGHT == nullptr) )
            has_right = true;

          if( !(prev_ == nullptr) )
            has_left = true;

          if( has_left && has_right ){

            prev_->RIGHT = temp_->RIGHT;
          }else if( has_right && !has_left ){
            //we need to replace the head ofcourse
            HEAD = temp_->RIGHT;
          }else if( has_left && !has_right ){
            
            prev_->RIGHT = nullptr;
          }else{
            //this the head
            HEAD_INIT = false;
          }

          if(!preserve_){
            delete [] temp_->address_holder;
          }
          temp_->address_holder = nullptr;
          delete temp_;
          return true;
        }
        if(!(temp_->RIGHT == nullptr)){
          prev_ = temp_;
          temp_ = temp_->RIGHT;
        }else{
          return false;
        }
      }
    }
    return false;
  }

  void destroy(){
    if(!destroyed_){
      if(HEAD_INIT){
        //we delete everything
        heap_linked_list<T> * temp_ = HEAD, * prev_ = nullptr;
        while(!(temp_ == nullptr)){
          if( !(temp_->address_holder == nullptr) ){
#ifdef DEBUG_
            std::cout << message_1 << (void *)temp_->address_holder << message_2;
#endif
            delete [] temp_->address_holder;
          }
          if(!(temp_->RIGHT == nullptr)){
            prev_ = temp_;
            temp_ = temp_->RIGHT;
            delete prev_;
          }else{
            delete temp_;
            break;
          }
        }
      }
    }
    destroyed_ = true;
  }
  
  bool find_address(T * addr_t){
    if(HEAD_INIT){
      heap_linked_list<T> * temp_ = HEAD;
      while(!(temp_ == nullptr)){
        if(temp_->address_holder == addr_t){
          return true;
        }
        if(!(temp_->RIGHT == nullptr)){
          temp_ = temp_->RIGHT;
        }else{
          break;
        }
      }
    }
    return false;
  }

  void free_address(){
    if(HEAD_INIT){
      //we delete everything
      heap_linked_list<T> * temp_ = HEAD, * prev_ = nullptr;
      while(!(temp_ == nullptr)){
        if( !(temp_->address_holder == nullptr) ){
#ifdef DEBUG_
          std::cout << message_1 << (void *)temp_->address_holder << message_2;
#endif
          delete [] temp_->address_holder;
        }
        if(!(temp_->RIGHT == nullptr)){
          prev_ = temp_;
          temp_ = temp_->RIGHT;
          delete prev_;
        }else{
          delete temp_;
          break;
        }
      }
    }
    HEAD_INIT = false;
  }

  void delete_list(){
    if(HEAD_INIT){
      //we delete the list
      //address inside address holder
      //are leave untouched
      heap_linked_list<T> * temp_ = HEAD, * prev_ = nullptr;
      while(!(temp_ == nullptr)){
        if(!(temp_->RIGHT == nullptr)){
          prev_ = temp_;
          temp_ = temp_->RIGHT;
          delete prev_;
        }else{
          delete temp_;
          break;
        }
      }
    }
    HEAD_INIT = false;
  }

  ~mem_heap_debug(){
    if(!destroyed_){
      destroy();
    }
  }

};

class bad_memory_alloc_error_debug: public std::exception{
  virtual const char * what() const throw(){
    return message_3;
  }
} BMARD_;

class bad_memory_release_error_debug: public std::exception{
  virtual const char * what() const throw(){
    return message_4;
  }
} BMRED_;

class bad_memory_access_error_debug: public std::exception{
  virtual const char * what() const throw(){
    return message_5;
  }
} BMCRD_;

class bad_array_uninitialized_error_debug: public std::exception{
  virtual const char * what() const throw(){
    return message_17;
  }
} BAUED_;

#if defined(DEBUG_) || defined(SAFE_USE_FUNCTIONALITY)
template <typename T>
T * new_(size_t size, mem_heap_debug<T> &heap_, int line=0){
  T * d = NULL;
  d = new (std::nothrow) T[size];
  if(d == NULL || size == 0 || d == nullptr){
    throw BMARD_;
  }

  bool result_ = heap_.add_address(d);
#ifdef DEBUG_
  if(result_){
    std::cout << message_6 << (void *)d << message_12 << size << message_10 << line << "\n";
  }else{
    std::cout << message_9;
  }
#endif
  return d;
}
/// D
template <typename T>
void del_(T * block, mem_heap_debug<T> &heap_, int line=0){
  if(block == NULL || block == nullptr){
    throw BMRED_;
  }

  bool result_ = heap_.remove_address(block);

  if(result_){
    delete[] block;
#ifdef DEBUG_
    std::cout << message_7 << (void *)block << message_11 << line << "\n";
  }else{
    std::cout << message_8;
#endif
  }
}

#else
template <typename T>
T * new_(size_t size, mem_heap_debug<T> &heap_, int line=0){
  T * d = NULL;
  d = new (std::nothrow) T[size];
  if(d == NULL || size == 0 || d == nullptr){
    throw BMARD_;
  }
  return d;
}
/// D
template <typename T>
void del_(T * block, mem_heap_debug<T> &heap_, int line=0){
  if(block == NULL || block == nullptr){
    throw BMRED_;
  }
  delete[] block;
}

#endif

#if defined(DEBUG_) || defined(SAFE_USE_FUNCTIONALITY)

template <typename T>
class arr_{
  size_t size_;
  bool destroy;
  bool init_;
  T * data;

  template <class X> void swap_(X& a, X& b){
    X c(a); a=b; b=c;
  }
  void swap(arr_<T> & f, arr_<T> & l){
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || __cplusplus>=201103L)
    std::swap(f.size_, l.size_);
    std::swap(f.destroy, l.destroy);
    std::swap(f.init_, l.init_);
    std::swap(f.data, l.data);
#else
    swap_(f.size_, l.size_);
    swap_(f.destroy, l.destroy);
    swap_(f.init_, l.init_);
    swap_(f.data, l.data);
#endif
  }

public:
  bool _try_leak(){
    T * a = nullptr;
    a = new (std::nothrow) T;
    if(a == nullptr){
      return false;
    }
    return true;
  }
  T * _get_address(){
    if(data == nullptr){
#ifdef DEBUG_
      std::cout << message_17 << std::endl;
#endif
      throw BMCRD_;
    }
    return data;
  }

/////////////////////////////
  arr_(): size_(0), destroy(false), init_(false){
    data = nullptr;
  }
/////////////////////////////
/////////////////////////////
  arr_(size_t s, unsigned int line=0): size_(s), destroy(true), init_(true){
    if(s == 0){
#ifdef DEBUG_
      std::cout << message_18;
#endif
      s = 1;
      size_ = 1;
    }
    data = new (std::nothrow) T[s];
#ifdef DEBUG_
    std::cout << message_13 << line << std::endl;
#endif
  }
/////////////////////////////
/////////////////////////////
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || __cplusplus>=201103L)
  arr_(std::initializer_list<T> arr_list): size_(arr_list.size()), destroy(true), init_(true){
#ifdef DEBUG_
  std::cout << message_24 << std::endl;
#endif
    if(size_ == 0){
      destroy = false;
      init_ = false;
#ifdef DEBUG_
  std::cout << message_15 << std::endl;
#endif
    }else{
      data = new (std::nothrow) T[size_];
      size_t i=0;
      for(const T & elem : arr_list){
        data[i] = elem;
        ++i;
      }
#ifdef DEBUG_
  std::cout << message_13 << std::endl;
#endif
    }
  }
#endif
/////////////////////////////
/////////////////////////////
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || __cplusplus>=201103L)
  arr_ & operator= (std::initializer_list<T> arr_list){
#ifdef DEBUG_
  std::cout << message_25 << std::endl;
#endif
    size_t prev_size_ = size_;
    size_ = arr_list.size();
    destroy = true;
    init_ = true;

    if(size_ == 0){
      destroy = false;
      init_ = false;
#ifdef DEBUG_
  std::cout << message_15 << std::endl;
#endif
    }else{
      //check if data is valid
      if(data != nullptr){
        //if the previous data size is big enough, we will use it
        //else destroy it
        if(prev_size_ < size_){
          delete [] data;
          data = new (std::nothrow) T[size_];
        }
      }
      
      size_t i=0;
      for(const T & elem : arr_list){
        data[i] = elem;
        ++i;
      }
#ifdef DEBUG_
  std::cout << message_13 << std::endl;
#endif
    }
    return *this;
  }
#endif
/////////////////////////////
/////////////////////////////
  arr_(const arr_<T> & rhs_): size_(rhs_.size()), destroy(true), init_(true){
#ifdef DEBUG_
      std::cout << message_20 << std::endl;
#endif
    data = nullptr;
    if(rhs_.size() == 0){
#ifdef DEBUG_
      std::cout << message_18;
#endif
      size_ = 1;
    }
    data = new (std::nothrow) T[size_];
    for(size_t i=0; i<size_; i++){
      data[i] = rhs_.at(i);
    }
#ifdef DEBUG_
    std::cout << message_13 << std::endl;
#endif
  }
/////////////////////////////
/////////////////////////////
  arr_ & operator= (const arr_<T> & rhs_){
#ifdef DEBUG_
    std::cout << message_22 << std::endl;
#endif
    arr_<T> t_(rhs_);
    swap(*this, t_);
    return *this;
  }
/////////////////////////////
/////////////////////////////
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || __cplusplus>=201103L)
  arr_(arr_<T> && rhs_): size_(0), destroy(false), init_(false){
#ifdef DEBUG_
    std::cout << message_21 << std::endl;
#endif
    data = nullptr;
    swap(*this, rhs_);
  }
#endif
/////////////////////////////
/////////////////////////////
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || __cplusplus>=201103L)
  arr_ & operator= (arr_<T> && rhs_){
#ifdef DEBUG_
    std::cout << message_23 << std::endl;
#endif
    data = nullptr;
    swap(*this, rhs_);
    return *this;
  }
#endif
/////////////////////////////
/////////////////////////////
  ~arr_(){
    if(destroy){
      delete [] data;
#ifdef DEBUG_
      std::cout << message_14 << std::endl;
#endif
    }
  }
/////////////////////////////

  bool alloc(size_t s, unsigned int line=0){
    if(init_){
      return false;
    }
    if(s == 0){
#ifdef DEBUG_
      std::cout << message_18;
#endif
      s = 1;
      size_ = 1;
    }
    data = new (std::nothrow) T[s];
    if(data == nullptr){
      return false;
    }else{
      size_ = s;
      destroy = true;
      init_ = true;
    }
    return true;
  }

  void print(){
    for(size_t i=0; i<size_; i++){
      std::cout << data[i] << " " << std::flush;
    }
    std::cout << std::endl;
  }

  T & at(long index) const {
    if(!init_){
      throw BAUED_;
    }
    long t = (long)(size_-1);
    if(index < 0 || index > t){
#ifdef DEBUG_
      std::cout << message_16 << index << std::endl;
#endif
      throw BMCRD_;
    }
    return data[index];
  }

  T & operator[] (long index) const {
    if(!init_){
      throw BAUED_;
    }
    long t = (long)(size_-1);
    if(index < 0 || index > t){
#ifdef DEBUG_
      std::cout << message_16 << index << std::endl;
#endif
      throw BMCRD_;
    }
    return data[index];
  }

  size_t size() const {
    return size_;
  }

  size_t length() const {
    return size_;
  }

  template <typename Func>
  void for_each( Func fun ){
    for(size_t i=0; i<size_; i++){
      fun(data[i], i);
    }
  }

  bool alloc2(size_t s, size_t o, unsigned int line=0){
    bool ok_inner_arr;

    if(init_){
      return false;
    }
    if(s == 0){
#ifdef DEBUG_
      std::cout << message_18;
#endif
      s = 1;
      size_ = 1;
    }
    if(o == 0){
#ifdef DEBUG_
      std::cout << message_18;
#endif
      o = 1;
    }

    data = new (std::nothrow) T[s];
    if(data == nullptr){
      return false;
    }else{
      for(size_t i=0; i<s; i++){
        ok_inner_arr = data[i].alloc(o);
        if(!ok_inner_arr){
          delete [] data;
          data = nullptr;
          return false;
        }
      }
      size_ = s;
      destroy = true;
      init_ = true;
    }
    return true;
  }

};

#else

template <typename T>
class arr_{
  size_t size_;
  bool destroy;
  bool init_;
  T * data;

  template <class X> void swap_(X& a, X& b){
    X c(a); a=b; b=c;
  }
  void swap(arr_<T> & f, arr_<T> & l){
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || __cplusplus>=201103L)
    std::swap(f.size_, l.size_);
    std::swap(f.destroy, l.destroy);
    std::swap(f.init_, l.init_);
    std::swap(f.data, l.data);
#else
    swap_(f.size_, l.size_);
    swap_(f.destroy, l.destroy);
    swap_(f.init_, l.init_);
    swap_(f.data, l.data);
#endif
  }

public:
  bool _try_leak(){
    T * a = nullptr;
    a = new (std::nothrow) T;
    if(a == nullptr){
      return false;
    }
    return true;
  }
  T * _get_address(){
    return data;
  }

/////////////////////////////
  arr_(): size_(0), destroy(false), init_(false){
    data = nullptr;
  }
/////////////////////////////
/////////////////////////////
  arr_(size_t s, unsigned int line=0): size_(s), destroy(true), init_(true){
    data = new (std::nothrow) T[s];
  }
/////////////////////////////
/////////////////////////////
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || __cplusplus>=201103L)
  arr_(std::initializer_list<T> arr_list): size_(arr_list.size()), destroy(true), init_(true){
    if(size_ == 0){
      destroy = false;
      init_ = false;
    }else{
      data = new (std::nothrow) T[size_];
      size_t i=0;
      for(const T & elem : arr_list){
        data[i] = elem;
        ++i;
      }
    }
  }
#endif
/////////////////////////////
/////////////////////////////
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || __cplusplus>=201103L)
  arr_ & operator= (std::initializer_list<T> arr_list){
    size_t prev_size_ = size_;
    size_ = arr_list.size();
    destroy = true;
    init_ = true;

    if(size_ == 0){
      destroy = false;
      init_ = false;
    }else{
      //check if data is valid
      if(data != nullptr){
        //if the previous data size is big enough, we will use it
        //else destroy it
        if(prev_size_ < size_){
          delete [] data;
          data = new (std::nothrow) T[size_];
        }
      }
      
      size_t i=0;
      for(const T & elem : arr_list){
        data[i] = elem;
        ++i;
      }
    }
    return *this;
  }
#endif
/////////////////////////////
/////////////////////////////
  arr_(const arr_<T> & rhs_): size_(rhs_.size()), destroy(true), init_(true){
    data = nullptr;
    if(rhs_.size() == 0){
      size_ = 1;
    }
    data = new (std::nothrow) T[size_];
    for(size_t i=0; i<size_; i++){
      data[i] = rhs_.at(i);
    }
  }
/////////////////////////////
/////////////////////////////
  arr_ & operator= (const arr_<T> & rhs_){
    arr_<T> t_(rhs_);
    swap(*this, t_);
    return *this;
  }
/////////////////////////////
/////////////////////////////
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || __cplusplus>=201103L)
  arr_(arr_<T> && rhs_): size_(0), destroy(false), init_(false){
    data = nullptr;
    swap(*this, rhs_);
  }
#endif
/////////////////////////////
/////////////////////////////
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || __cplusplus>=201103L)
  arr_ & operator= (arr_<T> && rhs_){
    data = nullptr;
    swap(*this, rhs_);
  }
#endif
/////////////////////////////
/////////////////////////////
  ~arr_(){
    if(destroy){
      delete [] data;
    }
  }
/////////////////////////////

  bool alloc(size_t s, unsigned int line=0){
    if(init_){
      return false;
    }
    if(s == 0){
      s = 1;
      size_ = 1;
    }
    data = new (std::nothrow) T[s];
    if(data == nullptr){
      return false;
    }else{
      size_ = s;
      destroy = true;
      init_ = true;
    }
    return true;
  }

  void print(){
    for(size_t i=0; i<size_; i++){
      std::cout << data[i] << " " << std::flush;
    }
    std::cout << std::endl;
  }

  T & at(long index) const {
    return data[index];
  }

  T & operator[] (long index) const {
    return data[index];
  }

  size_t size() const {
    return size_;
  }

  size_t length() const {
    return size_;
  }

  template <typename Func>
  void for_each( Func fun ){
    for(size_t i=0; i<size_; i++){
      fun(data[i], i);
    }
  }

  bool alloc2(size_t s, size_t o, unsigned int line=0){
    bool ok_inner_arr;

    if(init_){
      return false;
    }
    if(s == 0){
      s = 1;
      size_ = 1;
    }
    if(o == 0){
      o = 1;
    }

    data = new (std::nothrow) T[s];
    if(data == nullptr){
      return false;
    }else{
      for(size_t i=0; i<s; i++){
        ok_inner_arr = data[i].alloc(o);
        if(!ok_inner_arr){
          delete [] data;
          data = nullptr;
          return false;
        }
      }
      size_ = s;
      destroy = true;
      init_ = true;
    }
    return true;
  }

};

#endif

#ifdef SAFE_USE_NAMESPACE
};
#endif

#endif
