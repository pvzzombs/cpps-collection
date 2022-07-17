#include <iostream>
#include <vector>

enum flags { ARIT, GEOM };
struct item{
  flags type;
  int num;
};

class seq_solver {
private:
  std::vector<item> s;
  int last_num;
  int err;
public:
  bool arit(std::vector<item> &a, item &c){
    //std::cout << "arith --------" << std::endl
    for(int i=0; i<a.size(); i++){
      a.at(i).type = ARIT;
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
    c.type = ARIT;
    return true;
  }
  
  bool geom(std::vector<item> &a, item &c){
    for(int i=0; i<a.size(); i++){
      a.at(i).type = GEOM;
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
    c.type = GEOM;
    std::cout << "geo end ------" <<std::endl;
    return true;
  }
  
  bool reset_item(std::vector<item> &a, item &c){
    for(int i=0; i<a.size(); i++){
      a.at(i).type = ARIT;
    }
    c.type = ARIT;
    return true;
  }
  
  bool multi_stage(std::vector<int> &inp, int nth){
    s.clear();
    s.resize(nth);
    err = 0;
    int index = 0;
    int depth = 0;
    
    std::vector<item> arr(inp.size());
    for(int i=0; i<arr.size(); i++){
      arr.at(i).num = inp.at(i);
    }
    
    std::vector<item> tmp;
    
    while(true){
      if(depth == 5){
        err = 1;
        break;
      }
      
      item c;
      item first_term = arr.at(0);
      bool is_arit = arit(arr, c);
      bool is_geom = false;
      if(!is_arit){
        is_geom = geom(arr, c);        
      }
      if(!is_geom){
        reset_item(arr, c);
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
          tmp.at(i).type = ARIT;
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
          case ARIT:
            s.at(i).num = s.at(i).num + s.at(i-1).num;
            s.at(i).type = s.at(i-1).type;
            break;
          case GEOM:
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
    std::vector<item> arr(inp.size());
    for(int i=0; i<inp.size(); i++){
      arr.at(i).num = inp.at(i);
    }
    item c;
    int d, a_1 = inp.at(0);
    bool is_arit = arit(arr, c);
    d = c.num;
    if(is_arit){
      last_num = a_1 + nth * d - d;
      return true;
    }
    return false;
  }
  
};

int main(int argc, char *argv[]) {
  seq_solver m;
  std::vector<int> a = {1,3,5,7,9};
  std::cout <<  m.arithmetic(a, 10);
  std::cout << "==================" << std::endl;
  std::vector<int> b = {1,4,9,16,25};
}