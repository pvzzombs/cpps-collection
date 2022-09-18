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
  BSTNode* traverse_min(BSTNode * node){
    while(node->left != nullptr){
      node = node->left;
    }
    return node;
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
  void remove(const Z& data){
    BSTNode * parent = nullptr;
    BSTNode * current = tree;

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
      if(current == tree){
        tree = nullptr;
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
      if(current == tree){
        tree = current->left;
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
      if(current == tree){
        tree = current->right;
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
    BSTNode * current = tree;
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
  //tree.print_preorder();
  //tree.print_postorder();
  //tree.remove(2);
  std::cout << tree.search(6) << std::endl;
  tree.print_inorder();
  return 0;
}
