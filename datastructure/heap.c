#include "shared.h"
typedef struct {
    int len;
    int size;
    valueType* data;
}Heap;

Heap* initHeap(int size){
    Heap* heap = (Heap*)malloc(sizeof(Heap*));
    heap->len = 0;
    heap->size = size;
    heap->data = (valueType*)malloc(sizeof(valueType) * (size + 1));
    return heap;
}

int isEmpty(Heap* heap){
    return heap->len == 0;
}

void up(Heap* heap, int child){
    int parent;
    valueType temp;
    while(child != 1){
        parent = child / 2;
        if (heap->data[parent] > heap->data[child]){
            temp = heap->data[child];
            heap->data[child] = heap->data[parent];
            heap->data[parent] = temp;
            child = parent;
        }else return;
    }
}

void down(Heap* heap, int size, int root){
    int temp;
    while(root < size){
        int l = root * 2;
        int r = root * 2 + 1;
        int min = l;
        if(l > size) return;
        if(r <= size && heap->data[r] < heap->data[min]) min = r;
        if(heap->data[root] > heap->data[min]) {
            temp = heap->data[root];
            heap->data[root] = heap->data[min];
            heap->data[min] = temp;
            root = min;
        } else return;
    }
}

STATUS add(Heap* heap, valueType val){
    if(heap->len == heap->size) return ERROR;
    heap->data[++heap->len] = val;
    up(heap, heap->len);
}

STATUS pop(Heap* heap, valueType* val){
    if(heap->len == 0) return ERROR;
    *val = heap->data[1];
    heap->data[1] = heap->data[heap->len--];
    down(heap, heap->len, 1);
}

Heap* createHeapByArray(valueType* arr, int size){
    Heap* heap = initHeap(size);
    for(int i = 1;i < size + 1;++i){
        heap->data[i] = arr[i - 1];
        heap->len++;
    }
    for(int i = size / 2; i >= 1;--i){
        down(heap, heap->size, i);
    }
    return heap;
}

void printHeap(Heap* heap){
    for(int i = 1;i < heap->len;++i){
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

//test
int main(){
    valueType arr[10] = {1, 2 ,3 ,4 ,5 ,5 ,6, 4, 5, 2};
    Heap* heap = createHeapByArray(arr, 10);
    printHeap(heap);
    valueType val;
    while(!isEmpty(heap)){
        pop(heap, &val);
        printf("%d ", val);
    }
    printf("\n");
    add(heap, 10);
    add(heap, 20);
    add(heap, 1);
    add(heap, 2);
    add(heap, 120);
    add(heap, 24);
    while(!isEmpty(heap)){
        pop(heap, &val);
        printf("%d ", val);
    }
}