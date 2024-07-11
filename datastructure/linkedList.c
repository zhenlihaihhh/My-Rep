#include "shared.h"
typedef struct LinkedList{
    valueType val;
    struct LinkedList* next;
} LinkedList;


LinkedList* initLinkedList(valueType);
void add(LinkedList*, valueType);
void del(LinkedList*, valueType);
STATUS delEleByPos(LinkedList*, int);
LinkedList* reverse(LinkedList*);
void foreachList(LinkedList*);


LinkedList* initLinkedList(valueType val){
    LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList*));
    node->val = val;
    node->next = NULL;
    return node;
}

void add(LinkedList* head, valueType val){
    LinkedList* pre = head;
    LinkedList* newNode = initLinkedList(val);
    while(pre->next != NULL){
        pre = pre->next;
    }
    pre->next = newNode;
}

// delete value in the first position
void del(LinkedList* head, valueType val){
    while(head->next != NULL && head->next->val != val){
        head = head->next;
    }
    LinkedList* now = head->next;
    head->next = now->next;
    now->next = NULL;
}

STATUS delEleByPos(LinkedList* head, int pos){
    LinkedList* node = head;
    int count = 0;
    while(node != NULL){
        count++;
        node = node->next;
    }
    if (count <= pos) return ERROR;
    while(--pos){
        head = head->next;
    }
    LinkedList* now = head->next;
    head->next = now->next;
    now->next = NULL;
    return SUCESS;
}

LinkedList* reverse(LinkedList* head){
    LinkedList* pre = NULL;
    LinkedList* next;
    while(head != NULL){
        next = head->next;
        head->next = pre;
        pre = head;
        head = next;
    }
    return pre;
}

void foreachList(LinkedList* head){
    while(head->next != NULL){
        printf("%d->", head->val);
        head = head->next;
    }
    printf("%d\n", head->val);
}

//test
// int main(){
//     LinkedList* head = initLinkedList(1);
//     add(head, 2);
//     add(head, 3);
//     add(head, 4);
//     add(head, 5);
//     add(head, 6);
//     add(head, 7);
//     del(head, 3);
//     delEleByPos(head, 1);
//     foreachList(head);
//     head = reverse(head);
//     foreachList(head);
// }