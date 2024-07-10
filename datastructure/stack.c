#include "list.c"
typedef struct {
    valueType top;
    List* list; 
} Stack;
int isEmpty(Stack*);
Stack* initStack(int);
STATUS top(Stack*, valueType*);
STATUS pop(Stack*);
STATUS push(Stack*, valueType);
int isEmpty(Stack* stack){
    if(stack->top == -1){
        return true;
    }
    return false;
}

// size is initial size of stack
Stack* initStack(int size){
    Stack* stack = (Stack*)malloc(sizeof(Stack*));
    stack->top = -1;
    stack->list = initList(size);
    return stack;
}

STATUS top(Stack* stack, valueType* val){
    if(stack->top == -1) return ERROR;
    get(stack->list, stack->top, &(*val));
    return SUCESS;
}

// pop a element out of stack
STATUS pop(Stack* stack){
    if(stack->top == -1) return ERROR;
    stack->top--;
    return SUCESS;
}


STATUS push(Stack* stack, valueType val){
    stack->top++;
    add(stack->list, val);
    return SUCESS;
}

// test
// int main(){
//     Stack* stack = initStack(10);
//     push(stack, 1);
//     push(stack, 2);
//     push(stack, 3);
//     push(stack, 1);
//     push(stack, 2);
//     push(stack, 3);
//     push(stack, 1);
//     push(stack, 2);
//     push(stack, 3);
//     push(stack, 1);
//     push(stack, 2);
//     push(stack, 3);
//     push(stack, 1);
//     push(stack, 2);
//     push(stack, 3);
//     push(stack, 1);
//     push(stack, 2);
//     push(stack, 3);
//     valueType val;
//     while(!isEmpty(stack)){
//         top(stack, &val);
//         pop(stack);
//         printf("%d ", val);
//     }
// }