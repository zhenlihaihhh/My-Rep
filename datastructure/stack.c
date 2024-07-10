#include "list.c"
typedef struct {
    valueType top;
    List* list; 
} Stack;
Stack* initStack(int size){
    Stack* stack = (Stack*)malloc(sizeof(Stack*));
    stack->top = -1;
    stack->list = initList(size);
    return stack;
}
int main(){
    Stack* stack = initStack(10);
    for(int i = 0;i < 10;++i){
        printf("%d ",stack->list->arr[i]);
    }
}
