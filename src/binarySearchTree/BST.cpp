#include <iostream>
#include <queue>
#include <exception>

template <typename Z>
class BST{
  struct BSTNode{
    Z data;
    BSTNode * left;
    BSTNode * right;
    BSTNode(){
      left = nullptr;
      right = nullptr;
    }
  };
  BSTNode * root;
  bool destroyed;
  BSTNode * create_node(const Z& data){
    BSTNode * temp = new BSTNode;
    temp->data = data;
    return temp;
  }
  void traverse_insert(BSTNode * node, const Z& data){
    if(data < node->data){
      if(node->left == nullptr){
        node->left = create_node(data);
      }else{
        traverse_insert(node->left, data);
      }
    }else if(data > node->data){
      if(node->right == nullptr){
        node->right = create_node(data);
      }else{
        traverse_insert(node->right, data);
      }
    }else{
      return;
    }
  }
  void traverse_copy(BSTNode * node, BSTNode * rhs_node){
    if(rhs_node->left != nullptr){
      node->left = create_node(rhs_node->left->data);
      traverse_copy(node->left, rhs_node->left);
    }
    if(rhs_node->right != nullptr){
      node->right = create_node(rhs_node->right->data);
      traverse_copy(node->right, rhs_node->right);
    }
  }
  void traverse_print_inorder(BSTNode * node){
    if(node != nullptr){
      traverse_print_inorder(node->left);
      std::cout << node->data << " ";
      traverse_print_inorder(node->right);
    }
  }
  void traverse_print_preorder(BSTNode * node){
    if(node != nullptr){ 
      std::cout << node->data << " ";
      traverse_print_preorder(node->left);
      traverse_print_preorder(node->right);
    }
  }
  void traverse_print_postorder(BSTNode * node){
    if(node != nullptr){
      traverse_print_postorder(node->left);
      traverse_print_postorder(node->right);
      std::cout << node->data << " ";
    }
  }
  void traverse_print_breadth(BSTNode * node){
    std::queue<BSTNode*> q;
    q.push(node);
    while(!q.empty()){
      size_t cs = q.size();
      for(size_t i=0; i<cs; i++){
        if(q.front() != nullptr){
          std::cout << q.front()->data << " ";
          q.push(q.front()->left);
          q.push(q.front()->right);
        }else{
          std::cout << "<NIL> ";
        }
        q.pop();
      }
      std::cout << std::endl;
    }
  }
  void traverse_destroy(BSTNode * node){
    if(node != nullptr){
      traverse_destroy(node->left);
      traverse_destroy(node->right);
      delete node;
    }
  }
  BSTNode* traverse_min(BSTNode * node){
    while(node->left != nullptr){
      node = node->left;
    }
    return node;
  }

  public:
  BST(): root(nullptr), destroyed(false){
  }
  BST(const BST &rhs): BST(){
    if(!rhs.destroyed){
      if(rhs.root != nullptr){
        root = create_node(rhs.root->data);
        traverse_copy(root, rhs.root);
      }
    }
  }
  BST& operator=(const BST &rhs){
    BST tmp(rhs);
    std::swap(root, tmp.root);
    std::swap(destroyed, tmp.destroyed);
    return *this;
  }
  void insert(const Z& data){
    if(!destroyed){
      if(root == nullptr){
        root = create_node(data);
      }else{
        traverse_insert(root, data);
      }
    }
  }
  void remove(const Z& data){
    BSTNode * parent = nullptr;
    BSTNode * current = root;

    while(current != nullptr){
      if(data < current->data){
        parent = current;
        current = current->left;
      }else if(data > current->data){
        parent = current;
        current = current->right;
      }else{
        break;
      }
    }

    if(current == nullptr){
      return;
    }

    if(current->left == nullptr && current->right == nullptr){
      if(current == root){
        root = nullptr;
        delete current;
      }else{
        if(parent->left == current){
          parent->left = nullptr;
        }else{
          parent->right = nullptr;
        }
        delete current;
      }
    }else if(current->left != nullptr && current->right == nullptr){
      if(current == root){
        root = current->left;
        delete current;
      }else{
        if(parent->left == current){
          parent->left = current->left;
        }else{
          parent->right = current->left;
        }
        delete current;
      }
    }else if(current->left == nullptr && current->right != nullptr){
      if(current == root){
        root = current->right;
        delete current;
      }else{
        if(parent->left == current){
          parent->left = current->right;
        }else{
          parent->right = current->right;
        }
        delete current;
      }
    }else{
      BSTNode * temp = traverse_min(current->right);
      Z temp_data = temp->data;
      remove(temp_data);
      current->data = temp_data;
    }
  }
  BSTNode* search(const Z& data){
    BSTNode * current = root;
    while(current != nullptr){
      if(data < current->data){
        current = current->left;
      }else if(data > current->data){
        current = current->right;
      }else{
        return current;
      }
    }
    return nullptr;
  }
  void print_inorder(){
    if(!destroyed){
      traverse_print_inorder(root);
      std::cout << std::endl;
    }
  }
  void print_preorder(){
    if(!destroyed){
      traverse_print_preorder(root);
      std::cout << std::endl;
    }
  }
  void print_postorder(){
    if(!destroyed){
      traverse_print_postorder(root);
      std::cout << std::endl;
    }
  }
  void print_breadth(){
    if(!destroyed){
      traverse_print_breadth(root);
    }
  }
  void destroy(){
    if(!destroyed){
      traverse_destroy(root);
      root = nullptr;
      destroyed = true;
    }
  }
  ~BST(){
    destroy();
  }
};

int main(){
  BST<int> a;
  a.insert(4);
  a.insert(2);
  a.insert(6);
  a.insert(3);
  BST<int> b;
  b = a;
  /*a.insert(1);
  a.insert(5);
  a.insert(8);
  a.insert(7);*/
  //a.print_inorder();
  a.print_breadth();
  //a.print_preorder();
  //a.print_postorder();
  /*a.remove(2);
  a.remove(3);
  a.remove(4);
  a.remove(6);*/
  //std::cout << a.search(6) << std::endl;
  b.print_inorder();
  return 0;
}
