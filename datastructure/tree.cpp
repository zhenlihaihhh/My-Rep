#include "shared.h"
#include<queue>
#include<iostream>
using namespace std;
typedef struct tree{
    valueType val;
    struct tree* leftSon;
    struct tree* rightSon;
}Tree;

Tree* init_tree(valueType val){
    Tree* node = (Tree*)malloc(sizeof(Tree*));
    node->val = val;
    node->leftSon = nullptr;
    node->rightSon = nullptr;
    return node;
}

void dfs(Tree* root){
    if(root == nullptr){
        return;
    }
    printf("%d ", root->val);
    dfs(root->leftSon);
    dfs(root->rightSon);
}
void bfs(Tree* root){
    queue<Tree*> q;
    q.push(root);
    while(!q.empty()){
        Tree* node = q.front();
        q.pop();
        cout << node->val << " ";
        if(node->leftSon != nullptr) q.push(node->leftSon);
        if(node->rightSon != nullptr) q.push(node->rightSon);
    }
}
// test
int main(){
    Tree* tree = init_tree(10);
    tree->leftSon = init_tree(13);
    tree->rightSon = init_tree(19);
    tree->leftSon->leftSon = init_tree(29);
    tree->leftSon->rightSon = init_tree(22);
    dfs(tree);
    cout << endl;
    bfs(tree);
    return 0;
}