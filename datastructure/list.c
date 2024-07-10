#include<stdio.h>
#include<stdlib.h>
#include "shared.h"
typedef struct List{
    int size;
    int len;
    valueType* arr;
} List;

// 啊
void copyList(List* list, int extendSize);
List* initList(int size);
STATUS add(List* list, valueType ele);
valueType get(List* list, int index, valueType* getValue);
STATUS del(List* list, int index);
STATUS modify(List* list, int index, valueType val);
int findFirst(List* list, valueType val);
void sort(List* list, int start, int end);




void copyList(List* list, int extendSize){
    int* copyArr = (valueType*)malloc(sizeof(valueType) * extendSize);
    for(int i = 0;i < list->size;++i){
        copyArr[i] = list->arr[i];
    }
    free(list->arr);
    list->arr = copyArr;
    list->size = extendSize;
}
List* initList(int size){
    List* list = (List*)malloc(sizeof(List));
    list->size = size;
    list->len = 0;
    list->arr = (valueType*)malloc(sizeof(valueType) * size);
    return list;
}
STATUS add(List* list, valueType ele){
    if(list->size == list->len){
        copyList(list, list->size + list->size / 2);
    }
    list->arr[list->len++] = ele;
    return SUCESS;
}
STATUS get(List* list, int index, valueType* getValue){
    if(list->len <= index){
        return ERROR;
    }
    *getValue = list->arr[index];
    return SUCESS;
}
STATUS del(List* list, int index){
    if(list->len <= index) return ERROR;
    for(int i = index;i < list->len - 1;++i){
        list->arr[i] = list->arr[i + 1];
    }
    list->len--;
    return SUCESS;
}
STATUS modify(List* list, int index, valueType val){
    if(list->len <= index) return ERROR;
    list->arr[index] = val;
    return SUCESS;
}
int findFirst(List* list, valueType val){
    for(int i = 0;i < list->len;++i){
        if(list->arr[i] == val){
            return i;
        }
    }
    return ERROR;
}
void sort(List* list, int start, int end){
    int l = start;
    int r = end;
    if(start < end){
        valueType base = list->arr[start];
        while(l < r){
            while(l < r && list->arr[r] >= base){
                r--;
            }
            list->arr[l] = list->arr[r];
            while(l < r && list->arr[l] <= base){
                l++;
            }
            list->arr[r] = list->arr[l];
        }
        list->arr[l] = base;
        sort(list, start, l - 1);
        sort(list, l + 1, end);
    }
}

// int main(){
//     List* list = initList(10);
//     add(list, 10);
//     add(list, 9);
//     add(list, 7);
//     add(list, 8);
//     add(list, 1);
//     add(list, 3);
//     add(list, 5);
//     add(list, 10);
//     add(list, 9);
//     add(list, 7);
//     add(list, 8);
//     add(list, 1);
//     add(list, 3);
//     add(list, 5);
//     add(list, 10);
//     add(list, 9);
//     add(list, 7);
//     add(list, 8);
//     add(list, 1);
//     add(list, 3);
//     add(list, 5);
//     sort(list, 0, list->len - 1);
//     del(list, 1);
//     modify(list, 1, 10);
//     for(int i = 0;i < list->len;++i){
//         valueType getValue;
//         get(list, i, &getValue);
//         printf("%d ", getValue);
//     }
// }