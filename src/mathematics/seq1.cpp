#include <iostream>
#include <vector>

enum Flags { kARIT, kGEOM };
struct Item{
  Flags type;
  int num;
};

class SeqSolver {
private:
  std::vector<Item> s;
  int last_num;
  int err;

public:
  int get_error(){
    return err;
  }
  int get_result(){
    return last_num;
  }
  bool arit(std::vector<Item> &a, Item &c){
    //std::cout << "arith --------" << std::endl
    for(int i=0; i<a.size(); i++){
      a.at(i).type = kARIT;
    }
    int q = a.at(1).num - a.at(0).num;
    //std::cout << "common diff" << c << std::endl;
    for(int i=0; i<a.size()-1; i++){
      int t = a.at(i+1).num - a.at(i).num;
      if(q != t){
        return false;
      }
    }
    c.num = q;
    c.type = kARIT;
    return true;
  }
  
  bool geom(std::vector<Item> &a, Item &c){
    for(int i=0; i<a.size(); i++){
      a.at(i).type = kGEOM;
      std::cout << a.at(i).num << std::endl;
    }
    int q = a.at(1).num / a.at(0).num;
    for(int i=0; i<a.size()-1; i++){
      int t = a.at(i+1).num / a.at(i).num;
      if(q != t){
        return false;
      }
    }
    c.num = q;
    c.type = kGEOM;
    std::cout << "geo end ------" <<std::endl;
    return true;
  }
  
  bool reset_Item(std::vector<Item> &a, Item &c){
    for(int i=0; i<a.size(); i++){
      a.at(i).type = kARIT;
    }
    c.type = kARIT;
    return true;
  }
  
  bool multi_stage(std::vector<int> &inp, int nth){
    s.clear();
    s.resize(nth);
    err = 0;
    int index = 0;
    int depth = 0;
    
    std::vector<Item> arr(inp.size());
    for(int i=0; i<arr.size(); i++){
      arr.at(i).num = inp.at(i);
    }
    
    std::vector<Item> tmp;
    
    while(true){
      if(depth == 5){
        err = 1;
        break;
      }
      
      Item c;
      Item first_term = arr.at(0);
      bool is_arit = arit(arr, c);
      bool is_geom = false;
      if(!is_arit){
        is_geom = geom(arr, c);        
      }
      if(!is_geom){
        reset_Item(arr, c);
        std::cout << "---";
      }
      std::cout << "c is " << c.num << std::endl;
      
      if(is_arit){
        s.at(index) = first_term;
        index++;
        for(int i=index; i<nth; i++){
          s.at(i) = c;
        }
        for(int i=0; i<nth; i++){
          std::cout << s[i].num << " " << s[i].type << std::endl;
        }
        err = 0;
        break;
      }else if(is_geom){
        s.at(index) = first_term;
        //s.at(index).type = GEOM;
        index++;
        for(int i=index; i<nth; i++){
          s.at(i) = c;
        }
        for(int i=0; i<nth; i++){
          std::cout << s[i].num << " " << s[i].type << std::endl;
        }
        err = 0;
        break;
      }else{
        s.at(index) = first_term;
        tmp.clear(); tmp.resize(arr.size()-1);
        for(int i=0; i<arr.size()-1; i++){
          tmp.at(i).num = arr.at(i+1).num - arr.at(i).num;
          tmp.at(i).type = kARIT;
        }
        arr = tmp;
      }
      index++;
      depth++;
    }
    
    std::cout << "Index is " << index << std::endl;
    while(index > 0){
      for(int i=index; i<nth; i++){
        switch(s.at(i).type){
          case kARIT:
            s.at(i).num = s.at(i).num + s.at(i-1).num;
            s.at(i).type = s.at(i-1).type;
            break;
          case kGEOM:
          s.at(i).num = s.at(i).num * s.at(i-1).num;
          s.at(i).type = s.at(i-1).type;
        }
      }
      index--;
    }
    for(int i=0; i<nth; i++){
      std::cout << s[i].num << " " << s[i].type << std::endl;
    }
    if(!err){
      last_num = s.at(s.size()-1).num;
      return true;
    }
    return false;
  }
  
  bool arithmetic(std::vector<int> &inp, int nth){
    err = 0;
    std::vector<Item> arr(inp.size());
    for(int i=0; i<inp.size(); i++){
      arr.at(i).num = inp.at(i);
    }
    Item c;
    int d, a_1 = inp.at(0);
    bool is_arit = arit(arr, c);
    d = c.num;
    if(is_arit){
      last_num = a_1 + nth * d - d;
      return true;
    }
    return false;
  }
  
  bool geometric(std::vector<int> &inp, int nth){
    err = 0;
    std::vector<Item> arr(inp.size());
    for(int i=0; i<inp.size(); i++){
      arr.at(i).num = inp.at(i);
    }
    Item c;
    int r, a_1 = inp.at(0);
    bool is_geom = geom(arr, c);
    r = c.num;
    if(is_geom){
      int t = 1;
      for(int i=1; i<=nth-1; i++){
        t *= r;
      }
      last_num = a_1 * t;
      return true;
    }
    return false;
  }
};

int main(int argc, char *argv[]) {
  SeqSolver m;
  std::vector<int> a = {1,3,5,7,9};
  std::cout <<  m.arithmetic(a, 10) << std::endl;
  std::cout << m.get_result() << std::endl;
  std::cout << "==================" << std::endl;
  std::vector<int> b = {1,4,9,16,25};
}
