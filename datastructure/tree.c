#include "shared.h"
typedef struct tree{
    valueType val;
    struct tree* leftSon;
    struct tree* rightSon;
}Tree;
Tree* initTree(valueType val){
    Tree* node = (Tree*)malloc(sizeof(Tree*));
    node->val = val;
    node->leftSon = NULL;
    node->rightSon = NULL;
}

void dfs(Tree* root){
    if(root == NULL){
        return;
    }
    printf("%d ", root->val);
    dfs(root->leftSon);
    dfs(root->rightSon);
}

// test
int main(){
    Tree* tree = initTree(10);
    tree->leftSon = initTree(13);
    tree->rightSon = initTree(19);
    tree->leftSon->leftSon = initTree(29);
    tree->leftSon->rightSon = initTree(22);
    dfs(tree);
    return 0;
}