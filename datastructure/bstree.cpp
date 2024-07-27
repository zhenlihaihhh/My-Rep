#include<iostream>
using namespace std;
template <class T> 
class BSTreeNode{
    public:
        T _val;
        BSTreeNode<T>* _left;
        BSTreeNode<T>* _right;
        BSTreeNode(T val):
            _val(val),
            _left(nullptr),
            _right(nullptr)
            {}
};
template <class T>
class BSTree{
    public:
    BSTreeNode<T>* _root;
        BSTree(): 
            _root(nullptr) 
            {}; 
        ~BSTree() {};
        bool insert(T val);
        bool earse(T val);
        void printBSTree();
    private:
        void _printBS(BSTreeNode<T>* node);
        BSTreeNode<T>* find(T val);
};
template <class T>
bool BSTree<T>::insert(T val){
    if(_root == nullptr) {
        _root = new BSTreeNode<int>(val);
        return true;
    }; 
    BSTreeNode<T>* pre = nullptr;
    BSTreeNode<T>* now = _root;
    while(now) {
        if(now->_val == val) return false;
        pre = now;
        if(now->_val < val){
            now = now->_right;
        }else if(now->_val > val){
            now = now->_left;
        }
    }
    now = new BSTreeNode<T>(val);
    if(pre->_val < val) pre->_right = now;
    else pre->_left = now;
    return true;
}
template <class T>
void BSTree<T>::printBSTree(){
    _printBS(_root);
}
template <class T>
void BSTree<T>::_printBS(BSTreeNode<T>* node){
    if(node == nullptr) return;
    _printBS(node->_left);
    cout << node->_val << endl;
    _printBS(node->_right);
}
template <class T>
BSTreeNode<T>* BSTree<T>::find(T val){
    BSTreeNode<T>* node = _root;
    while(node){
        if(node->_val == val) return node;
        else if(node->_val < val) node = node->_right;
        else node = node->_left;
    }
}
template <class T>
bool BSTree<T>::earse(T val){
    BSTreeNode<T>* pre = nullptr;
    BSTreeNode<T>* node = _root;
    while(node) {
        if (node->_val == val) break;
        pre = node;
        if(node->_val < val) node = node->_right;
        else if (node->_val > val) node = node->_left;
    }
    if(node == nullptr) return false;
    if(node->_left == nullptr){
        if(node == _root){
            _root = node->_right;
        }else {
            if(pre->_left == node) pre->_left = node->_right;
            else pre->_right = node->_right;
        }
    }else if(node->_right == nullptr){
        if(node == _root){
            _root = _root->_left;
        } else{
            if(pre->_left == node) pre->_left = node->_left;
            else pre->_right = node->_left;
        }
    }else {
        BSTreeNode<T>* right = node->_right;
        BSTreeNode<T>* rparent = node;
        while(right->_left){
            rparent = right;
            right = right->_left;
        }
        node->_val = right->_val;
        if(rparent->_left == right){
            rparent->_left = right->_right;
            node = right;
        }else {
            rparent->_right = right->_right;
            node = right;
        }
    }
    free(node);
    node = nullptr;
    return true;
}
// // test
int main(){
    BSTree<int> tree = BSTree<int>();
    for(int i = 5;i <= 10; ++i){
        bool a = tree.insert(i);
    }
    for(int i = 1;i <= 4; ++i){
        bool a = tree.insert(i);
    }
    for(int i = 3;i <= 10; ++i){
        tree.earse(i);
    }
    tree.printBSTree();
}
