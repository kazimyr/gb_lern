#pragma once
#include <malloc.h>
//=
typedef struct {
    T data;
    struct OLNode* next;
}OLNode;
//=
typedef struct{
    OLNode* head;
    int size;
}OLList;
//=
OLList* initOLList(OLList *list){
    list=(OLList*)malloc(sizeof(OLList));
    list->size=0;
    list->head=NULL;
    return list;
}
//=
void pushOLList(OLList *list, T data){
    OLNode *node=(OLNode*)malloc(sizeof(OLNode));
    node->data=data;
    node->next=NULL;
    OLNode* current=list->head;
    if(current==NULL){
        list->head=node;
        list->size++;
        return;
    }else{
        while(current->next!=NULL){
            current=current->next;
        }
        current->next=node;
        list->size++;
    }
}
//=
void pushOLListSt(OLList *list, T data){
    OLNode *node=(OLNode*)malloc(sizeof(OLNode));
    node->data=data;
    node->next=list->head;
    list->head=node;
    list->size++;
}
//=
void popOLList(OLList *list, T data){
    OLNode *current=list->head;
    OLNode *parent = NULL;
    if (current == NULL)
        return;
    while (current->next != NULL && current->data != data) {
        parent=current;
        current=current->next;
    }
    if (current->data != data) {
         return;
    }
    if (current == list->head) {
        list->head = current->next;
        list->size--;
        return;
    }
    parent->next = current->next;
    list->size--;
    return;
}
//=
T popOLListSt(OLList *list){
    if(list->size == 0){
        printf("OLList is empty.\n");
        return -1;
    }
    OLNode *tmp=list->head;
    T data=list->head->data;
    list->head=list->head->next;
    list->size--;
    free(tmp);
    return data;
}
//=
void printOLNode(OLNode *node){
    if(node==NULL){
        printf("{}");
        return;
    }
    printf("{%i}", node->data);
}
//=
void printOLList(OLList* list){
    OLNode *current=list->head;
    if(current==NULL){
        printOLNode(current);
    }else{
        do{
            printOLNode(current);
            current=current->next;
        }while(current!=NULL);
    }
    printf("Size: %d \n", list->size);
}
//=
void testOLList(){
    OLList *ol=initOLList(ol);
    pushOLList(ol,1);
    printOLList(ol);
    pushOLList(ol,2);
    pushOLList(ol,3);
    pushOLList(ol,4);
    pushOLList(ol,5);
    pushOLList(ol,6);
    pushOLList(ol,7);
    pushOLList(ol,8);
    pushOLList(ol,9);
    pushOLList(ol,10);
    printOLList(ol);
    popOLList(ol, 5);
    popOLList(ol, 1);
    popOLList(ol, 11);
    printOLList(ol);
}
//==
typedef struct{
    T data;
    struct TLNode *prev;
    struct TLNode *next;
}TLNode;
//
typedef struct{
    TLNode *head;
    TLNode *tail;
    int size;
}TLList;
//==
TLList *initTLList(TLList *list){
    list=(TLList*)malloc(sizeof(TLList));
    list->head=NULL;
    list->tail=NULL;
    list->size=0;
    return list;
}
//==
void pushFrontTL(TLList *lst, int data) {
    TLNode *new = (TLNode*) malloc(sizeof(TLNode));
    new->data=data;
    new->prev=NULL;
    new->next=lst->head;
    if (lst->head!=NULL) {
        lst->head->prev=new;
    }
    if (lst->tail==NULL) {
        lst->tail=new;
    }
    lst->head=new;
    lst->size++;
}
//==
void pushBackTL(TLList *lst, int data) {
    TLNode *new = (TLNode*) malloc(sizeof(TLNode));
    new->data=data;
    new->next=NULL;
    new->prev=lst->tail;
    if (lst->tail != NULL) {
        lst->tail->next=new;
    }
    if (lst->head == NULL) {
        lst->head=new;
    }
    lst->tail = new;
    lst->size++;
}
//==
T popFrontTL(TLList *lst) {
    if (lst->size == 0) {
        return -1;
    }
    TLNode *tmp = lst->head;
    T data=lst->head->data;
    lst->head = lst->head->next;
    if (lst->head != NULL) {
        lst->head->prev = NULL;
    }
    if (tmp == lst->tail) {
        lst->tail = NULL;
    }
    //tmp=NULL;
    free(tmp);
    lst->size--;
    return data;
}
//==
void popBackTL(TLList *lst) {
    if (lst->tail == NULL) {
        return NULL;
    }
    TLNode *tmp = lst->tail;
    lst->tail = lst->tail->prev;
    if (lst->tail != NULL) {
        lst->tail->next = NULL;
    }
    if (tmp == lst->head) {
        lst->head = NULL;
    }
    lst->size--;
}
//=
void printTLNode(TLNode *node){
    if(node==NULL){
        printf("{}");
        return;
    }
    printf("{%i}", node->data);
}
//=
void printTLList(TLList* list){
    TLNode *current=list->head;
    if(current==NULL){
        printTLNode(current);
    }else{
        do{
            printTLNode(current);
            current=current->next;
        }while(current!=NULL);
    }
    printf("Size: %d \n", list->size);
}
//==
void testTLList(){
    TLList *tl=initTLList(tl);
    printTLList(tl);
    pushBackTL(tl, 1);
    printTLList(tl);
    pushBackTL(tl, 2);
    pushFrontTL(tl, 3);
    pushFrontTL(tl, 4);
    printTLList(tl);
    popBackTL(tl);
    printTLList(tl);
    popFrontTL(tl);
    printTLList(tl);
}
//*
OLList *initCyrcleList(OLList* list){
    list=(OLList*)malloc(sizeof(OLList));
    list->size=0;
    list->head=NULL;
    return list;
}
//*
void printCyrcleList(OLList* list){
    OLNode *current=list->head;
    if(current==NULL){
        printOLNode(current);
    }else{
        do{
            printOLNode(current);
            current=current->next;
        }while(current!=list->head);
    }
    printf("Size: %d \n", list->size);
}
//*
void puschCyrcleList(OLList *lst, int data) {
    OLNode *new = (OLNode*) malloc(sizeof(OLNode));
    new->data = data;
    new->next = lst->head;
    OLNode *current = lst->head;
    if (current == NULL) {
        lst->head = new;
        new->next = lst->head;
        lst->size++;
        return;
    } else {
        while (current->next != lst->head) {
            current= current->next;
        }
        current->next = new;
        lst->size++;
    }
}
//*
void popCyrcleList(OLList *lst, int data) {
    OLNode *current = lst->head;
    OLNode *parent = NULL;
    if (current == NULL) {
        return;
    }
    while (current->next != lst->head && current->data != data) {
        parent = current;
        current = current->next;
    }
    if (current->data != data) {
        return;
    }
    if (current == lst->head) {
        if (current->next == lst->head) {
            lst->head = NULL;
            lst->size--;
            return;
        } else {
            OLNode *tmp = current;
            while (current->next != lst->head) {
                current = current->next;
            }
            lst->head = tmp->next;
            current->next = lst->head;
            lst->size--;
            return;
        }
    }
    parent->next = current->next;
    lst->size--;
    return;
}
//*
void testCyrcleList() {
    OLList *cl=initCyrcleList(cl);
    printCyrcleList(cl);
    puschCyrcleList(cl, 1);
    puschCyrcleList(cl, 2);
    puschCyrcleList(cl, 3);
    printCyrcleList(cl);
    popCyrcleList(cl, 3);
    printCyrcleList(cl);
}
