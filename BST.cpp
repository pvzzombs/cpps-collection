#include <iostream>
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
  BSTNode * tree;
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
    }else{
      if(node->right == nullptr){
        node->right = create_node(data);
      }else{
        traverse_insert(node->right, data);
      }
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
  void traverse_destroy(BSTNode * node){
    if(node != nullptr){
      traverse_destroy(node->left);
      traverse_destroy(node->right);
      delete node;
    }
  }
  public:
  BST(): tree(nullptr), destroyed(false){
  }
  void insert(const Z& data){
    if(!destroyed){
      if(tree == nullptr){
        tree = create_node(data);
      }else{
        traverse_insert(tree, data);
      }
    }
  } 
  void print_inorder(){
    if(!destroyed){
      traverse_print_inorder(tree);
      std::cout << std::endl;
    }
  }
  void print_preorder(){
    if(!destroyed){
      traverse_print_preorder(tree);
      std::cout << std::endl;
    }
  }
  void print_postorder(){
    if(!destroyed){
      traverse_print_postorder(tree);
      std::cout << std::endl;
    }
  }
  void destroy(){
    if(!destroyed){
      traverse_destroy(tree);
      tree = nullptr;
      destroyed = true;
    }
  }
  ~BST(){
    destroy();
  }
};

int main(){
  BST<int> tree;
  tree.insert(4);
  tree.insert(2);
  tree.insert(6);
  tree.insert(3);
  /*tree.insert(1);
  tree.insert(5);
  tree.insert(8);
  tree.insert(7);*/
  tree.print_inorder();
  tree.print_preorder();
  tree.print_postorder();
  return 0;
}
