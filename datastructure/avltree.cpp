#include<iostream>
using namespace std;
template <class K, class V>
class AVLnode{
    public:
        pair<K, V> _val;
        AVLnode<K, V> *_left;
        AVLnode<K, V> *_right; 
        AVLnode<K, V> *_parent;
        int _bf;
        AVLnode(pair<K, V> val):
            _val(val),
            _left(nullptr),
            _right(nullptr),
            _parent(nullptr),
            _bf(0)
            {}
};
template <class K, class V>
class AVLTree{
    public:
        bool insert(const pair<K, V> &val);
        bool earse(const K &key);
        V find(const K &key);
        int height();
    private:
        AVLnode<K, V> *_root;
        void RotateR(AVLnode<K, V> *root);
        void RotateL(AVLnode<K, V> *root);
        void RotateLR(AVLnode<K, V> *root);
        void RotateRL(AVLnode<K, V> *root);
        int _height(AVLnode<K, V> *root);
};
template <class K, class V> 
bool AVLTree<K, V>::insert(const pair<K, V> &val){
    if(_root == nullptr){
        _root = new AVLnode<K, V>(val);
        return true;
    }
    AVLnode<K, V> *pre = nullptr;
    AVLnode<K, V> *cur = _root;
    while(cur){
        if(cur->_val.first == val.first){
            return false;
        }
        pre = cur;
        if(cur->_val.first < val.first) cur = cur->_right;
        else cur = cur->_left;
    }
    cur = new AVLnode<K, V>(val);
    if(pre->_val.first < val.first) pre->_right = cur;
    else pre->_left = cur;
    cur->_parent = pre;
    while(pre != nullptr){
        if(pre->_left) pre->_bf--;
        else pre->_bf++;
        if(pre->_bf == 1 || pre->_bf == -1){
            cur = cur->_parent;
            pre = pre->_parent;
        }else if(pre->_bf == 0){
            break;
        }else if(pre->_bf == 2 || pre->_bf == -2){
            if(pre->_bf == 2 && cur->_bf == 1) RotateL(pre);
            else if(pre->_bf == -2 && cur->_bf == -1) RotateR(pre);
            else if(pre->_bf == 2 && cur->_bf == -1) RotateRL(pre);
            else if(pre->_bf == -2 && cur->_bf == 1) RotateLR(pre);
            break;
        }
    }
    return true;
}
template <class K, class V>
V AVLTree<K, V>::find(const K &key){
    AVLnode<K, V> *root = _root;
    while(root){
        if(root->_val.first < key){
            root = root->_right;
        }else if(root->_val.first > key){
            root = root->_left;
        }else {
            break;
        }
    }
    return root->_val.second;
}

template <class K, class V>
bool AVLTree<K, V>::earse(const K &key){
    AVLnode<K, V> *cur = _root;
    AVLnode<K, V> *pre = nullptr;
    while(cur) {
        if(cur->_val.first == key) break;
        pre = cur;
        if(cur->_val.first < key) cur = cur->_right;
        else cur = cur->_left;
    }
    if(cur == nullptr) return false;
    if(cur->_left == nullptr) {
        if(cur == _root){
            _root = cur->_right;
            _root->_parent = nullptr;
        }else {
            if(pre->_left == cur) {
                pre->_bf++;
                pre->_left = cur->_right;
            } else {
                pre->_bf--;
                pre->_right = cur->_right;
            }
            cur->_right->_parent = pre;

        }
        delete cur;
    }else if (cur->_right == nullptr){
        if(cur == _root) {
            _root = cur->_left;
            _root->_parent = nullptr;
        }else {
            if(pre->_left == cur) {
                pre->_bf++;
                pre->_left = cur->_left;
            } else {
                pre->_bf--;
                pre->_right = cur->_left;
            }
            cur->_left->_parent = pre;
        }
        delete cur;
    }else {
        AVLnode<K, V> *curR = cur->_right;
        AVLnode<K, V> *p = cur;
        while(curR->_left) {
            curR = curR->_left;
            p = curR;
        }
        cur->_val = curR->_val;
        if(curR == p->_left){
            p->_bf++;
            p->_left = curR->_right;
        }else {
            p->_bf--;
            p->_right = curR->_right;
        }
        pre = p;
        cur = curR->_right;
        curR->_right->_parent = p;
        delete curR;
    }

    bool ischecked = true;
    while(pre) {
        if(!ischecked){
            if(pre->_left == cur){
                pre->_bf++;
            } else {
                pre->_bf--;
            }
        }
        ischecked = false;
        if(pre->_bf == 1 || pre->_bf == -1) return true;
        else if (pre->_bf == 0) {
            cur = pre;
            pre = pre->_parent;
        }else if (pre->_bf == 2 || pre->_bf == -2) {
            int sign = 0;
            AVLnode<K, V> *child = nullptr;
            if (pre->_bf > 0) {
                sign = 1;
                child = pre->_right;
            }else {
                sign = -1;
                child = pre->_left;
            }
            if(child->_bf == 0) {
                if(sign > 0) {
                    RotateL(pre);
                    pre->_bf = 1;
                    child->_bf = -1;
                }else {
                    RotateR(pre);
                    pre->_bf = -1;
                    child->_bf = 1;
                }
                return true;
            }else if(child->_bf == sign){
                if (sign == 1){
                    RotateL(pre);
                }else {
                    RotateR(pre);
                }
            }else {
                if(sign == 1){
                    RotateRL(pre);
                }else {
                    RotateLR(pre);
                }
            }
        }
        cur = pre;
        pre = pre->_parent;
    }
    return false;
}
template <class K, class V>
int AVLTree<K, V>::height(){
    return _height(_root);
}
template <class K, class V>
int AVLTree<K, V>::_height(AVLnode<K, V> *root){
    if(root == nullptr) return 0;
    int l = _height(root->_left);
    int r = _height(root->_right);
    return l > r ? l + 1 : r + 1; 
}
template <class K, class V>
void AVLTree<K, V>::RotateR(AVLnode<K, V> *root){
    AVLnode<K, V> rootL = root->_left;
    AVLnode<K, V> rootLR = rootL._right;

    root->_left = rootLR;
    if(rootLR) rootLR->_parent = root;
    rootL._right = root;
    if(root == _root){
        _root = rootL;
        rootL->_parent = nullptr;
    }else {
        if(root->_parent->_left == root) root->_parent->_left = rootL;
        else root->_parent->_right = rootL;
    }
    root->_parent = rootL;
    root->_bf = 0;
    rootL._bf = 0;

}
template <class K, class V>
void AVLTree<K, V>::RotateL(AVLnode<K, V> *root){
    AVLnode<K, V> *rootR = root->_right;
    AVLnode<K, V> *rootRL = rootR->_left;
    root->_right = rootRL;
    if(rootRL) rootRL->_parent = root;
    rootR->_left = root;
    rootR->_parent = root->_parent;
    if(root == _root){
        rootR->_parent = nullptr;
        _root = rootR;
    }else {
        if(root->_parent->_left == root){
            root->_parent->_left = rootR;
        }else {
            root->_parent->_right = rootR;
        }
    }
    root->_parent = rootR;
    rootR->_bf = 0;
    root->_bf = 0;
}
template <class K, class V>
void AVLTree<K, V>::RotateRL(AVLnode<K, V> *root){
    AVLnode<K, V> *rootR = root->_right;
    AVLnode<K, V> *rootRL = rootR->_left;
    int bf = rootRL->_bf;
    RotateR(rootR);
    RotateL(root);
    if(bf == -1){
        root->_bf = -1;
        rootR->_bf = 0;
        rootRL->_bf = 0;
    }else if(bf == 0){
        root->_bf = 0;
        rootR->_bf = 0;
        rootRL->_bf = 0;
    }else {
        root->_bf = 0;
        rootR->_bf = 1;
        rootRL->_bf = 0;
    }
}
template <class K, class V>
void AVLTree<K, V>::RotateLR(AVLnode<K, V> *root){
    AVLnode<K, V> *rootL = root->_left;
    AVLnode<K, V> *rootLR = rootL->_right;
    int bf = rootLR->_bf;
    RotateL(rootL);
    RotateR(root);
    if(bf == -1){
        root->_bf = 1;
        rootL->_bf = 0;
        rootLR->_bf = 0;
    }else if(bf == 0){
        root->_bf = 0;
        rootL->_bf = 0;
        rootLR->_bf = 0;
    }else {
        root->_bf = 0;
        rootL->_bf = -1;
        rootLR->_bf = 0;
    }
}

// int main(){
//     AVLTree<int, int> a;
    
    
// }