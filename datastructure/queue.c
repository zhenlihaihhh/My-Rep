#include "shared.h"
typedef struct CirCularQueue{
    valueType* data;
    int size;
    int front;
    int rear;
} CirCularQueue;

CirCularQueue* initCirCularQueue(int);
int isEmpty(CirCularQueue*);
int isFull(CirCularQueue*);
STATUS push(CirCularQueue*, valueType);
STATUS pull(CirCularQueue*, valueType*);
STATUS peek(CirCularQueue*, valueType*);

CirCularQueue* initCirCularQueue(int size){
    CirCularQueue* queue = (CirCularQueue*)malloc(sizeof(CirCularQueue*));
    queue->data = (valueType*)malloc(sizeof(valueType) * size);
    queue->size = size + 1;
    queue->front = 0;
    queue->rear = 0;
}

int isEmpty(CirCularQueue* queue){
    return queue->rear == queue->front;
}
int isFull(CirCularQueue* queue){
    return (queue->front + 1) % queue->size == queue->rear;
}
STATUS push(CirCularQueue* queue, valueType val){
    if(isFull(queue)) return ERROR;
    queue->data[queue->front] = val;
    queue->front = (queue->front + 1) % queue->size;
    return SUCESS;
}

STATUS pull(CirCularQueue* queue, valueType* val){
    if(isEmpty(queue)) return ERROR;
    *val = queue->data[queue->rear];
    queue->rear = (queue->rear + 1) % queue->size;
    return SUCESS;
}

STATUS peek(CirCularQueue* queue, valueType* val){
    if(isEmpty(queue)) return ERROR;
    *val = queue->data[queue->rear];
    return SUCESS;
}

//test
// int main(){
//     CirCularQueue* queue = initCirCularQueue(10);
//     printf("%d ", push(queue, 213));
//     printf("%d ", push(queue, 1));
//     printf("%d ", push(queue, 2));
//     printf("%d ", push(queue, 3));
//     printf("%d ", push(queue, 4));
//     printf("%d ", push(queue, 5));
//     printf("%d ", push(queue, 6));
//     printf("%d ", push(queue, 7));
//     printf("%d ", push(queue, 8));
//     printf("%d ", push(queue, 9));
//     printf("%d ", push(queue, 10));
//     valueType val;
//     printf("\n");
//     while(!isEmpty(queue)){
//         pull(queue, &val);
//         printf("%d ", val);
//     }
//     printf("%d ", push(queue, 213));
//     printf("%d ", push(queue, 1));
//     printf("%d ", push(queue, 2));
//     printf("%d ", push(queue, 3));
//     printf("%d ", push(queue, 4));
//     printf("%d ", push(queue, 5));
//     printf("%d ", push(queue, 6));
//     printf("%d ", push(queue, 7));
//     printf("%d ", push(queue, 8));
//     printf("%d ", push(queue, 9));
//     printf("%d ", push(queue, 10));
// }