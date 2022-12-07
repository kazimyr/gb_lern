#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define T char
#define true 1 == 1
#define false 1 != 1
typedef int boolean;

typedef struct OneLinkNode {
    int dat;
    struct OneLinkNode *next;
} OneLinkNode;

typedef struct {
    OneLinkNode *head;
    int size;
} OneLinkList;

void initOneLinkList(OneLinkList *lst) {
    lst->head = NULL;
    lst->size = 0;
}
void printOneLinkCharNode(OneLinkNode *n) {
    if (n == NULL) {
        printf("[]");
        return;
    }
    printf("[%c]", n->dat);
}
void printOneLinkCharList(OneLinkList *stack) {
    OneLinkNode *current = stack->head;
    if (current == NULL) {
        printOneLinkCharNode(current);
    } else {
        do {
            printOneLinkCharNode(current);
            current = current->next;
        } while (current != NULL);
    }
    printf(" Size: %d \n", stack->size);
}
boolean pushOneLinkStack(OneLinkList *stack, T value) {
    OneLinkNode *tmp = (OneLinkNode*) malloc(sizeof(OneLinkNode));
    if (tmp == NULL) {
        printf("Stack overflow \n");
        return false;
    }
    tmp->dat = value;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;
    return true;
}
T popOneLinkStack(OneLinkList *stack) {
    if (stack->size == 0) {
        printf("Stack is empty \n");
        return -1;
    }
    OneLinkNode *tmp = stack->head;
    T data = stack->head->dat;
    stack->head = stack->head->next;
    free(tmp);
    stack->size--;
    return data;
}

// 1. Написать программу, которая определяет, является ли введенная скобочная последовательность правильной. 
//     Примеры правильных скобочных выражений: 
//     (), ([])(), {}(), ([{}]), 
//     неправильных — )(, ())({), (, ])}), )([(] для скобок [,(,{. 
//     Например: (2+(2*2)) или [2/{5*(4+7)}]

int inSet(char smbl, char *ptr, size_t sz){
    for (int i = 0; i < sz; i++) {
        if (ptr[i] == smbl) return i;
    }
    return -1;
}

void strToStack(OneLinkList *st, char *str) {
    char pattern[] = {'(', '[', '{', '}', ']', ')'};
    for (int i = 0; str[i] != '\0'; i++) {
        int idxStr = inSet(str[i], pattern, 6);
        int idxSt;
        if (idxStr > -1) {
            if (idxStr < 3) pushOneLinkStack(st, pattern[idxStr]);
            else if(st->size > 0 && (idxSt = inSet(st->head->dat, pattern, 6))  == abs(idxStr - 5)) popOneLinkStack(st);
            else {
                printf("Ошибка: в строке %s\nв позиции № %d%cожидается %c\n", str, i + 1, ' ', pattern[abs(idxSt - 5)]);
                while(st->size) popOneLinkStack(st); 
                return;
            }
        }
    }
    if(st->size) {
        printf("Ошибка: в строке %s\nскобки в количестве: %d шт:\n", str, st->size);
        char *clrTail = (char*) calloc(st->size + 1, sizeof(char));
        for(int i = st->size - 1; i >= 0; i--) clrTail[i] = popOneLinkStack(st);
        printf("%s\nсовершенно ни к чему\n", clrTail);
        free(clrTail);
        }
    else {
        printf("В строке %s\nскобки расставлены правильно\n", str);
        return;
    } 
}
void clrLst(OneLinkList *st){
    OneLinkNode *tmp, *current = st->head;
    st->head = NULL;
    st->size = 0;
    while (tmp = current) {
        current = current->next;
        free(tmp);
    }
}
// 2. Создать функцию, копирующую односвязный список (без удаления первого списка).
void printOneLinkIntNode(OneLinkNode *n) {
    if (n == NULL) {
        printf("[]");
        return;
    }
    printf("[%d]", n->dat);
}
void printOneLinkIntList(OneLinkList *lst) {
    OneLinkNode *current = lst->head;
    if (current == NULL) {
        printOneLinkIntNode(current);
    } else {
        do {
            printOneLinkIntNode(current);
            current = current->next;
        } while (current != NULL);
    }
    printf(" Size: %d \n", lst->size);
}
void insert(OneLinkList *lst, int data) {
   OneLinkNode *new = (OneLinkNode*) malloc(sizeof(OneLinkNode));
   new->dat = data;
   new->next = NULL;

   OneLinkNode *current = lst->head;
   if (current == NULL) {
       lst->head = new;
       lst->size++;
   } else {
       while (current->next != NULL) {
           current = current->next;
       }
       current->next = new;
       lst->size++;
   }
}

int randInRange(size_t mn, size_t mx) { // Случайное число в заданном диапазоне
    return mn + rand() % ((mx - mn) + 1);
}
OneLinkList* cpOneLinkLst(OneLinkList *st){                         //Полная копия данных старого списка в новый список
    OneLinkList *cp = (OneLinkList*) malloc(sizeof(OneLinkList));   //Формально можно просто завести еще одну ссылку OneLinkList *cp = st
    initOneLinkList(cp);                                            //и работать с одним списком через оба этих адреса
    OneLinkNode *current = st->head;
    if (current != NULL) {
        do {
            insert(cp, current->dat);
            current = current->next;
        } while (current != NULL);
    }
    return cp;
}

// 3. Реализуйте алгоритм, который определяет, отсортирован ли связный список.

int sgn(int a, int b) {
    return a==b ? 0 : (b - a)/abs(b - a);
}

void srtLst(OneLinkList *st) {
    OneLinkNode *current = st->head;
    int flag = 0;
    while (current && current->next) {
        int s = sgn(current->dat, current->next->dat);
        if(s == -1 && flag == 1 || s == 1 && flag == -1) {
            printf("Список не отсортирован\n");
            return;
        }
        else if(!s && !flag || s > -1 && flag == 1 || s < 1 && flag == -1) current = current->next;
        else if(!flag && s) {
            flag = s;
            current = current->next;
        }
    }
    if (flag == 1) printf("Список отсортирован по возрастанию\n");
    else if (flag == -1) printf("Список отсортирован по убыванию\n");
    else printf("Список состоит из одинаковых элементов\n");
    return;
} 

int main() {
    srand(time(NULL));
    OneLinkList *st = (OneLinkList*) malloc(sizeof(OneLinkList));
    OneLinkList *cpLst;
    initOneLinkList(st);

    //№ 1
    char line[] = "[2/{{a[6]+8}-5*(4+7)}][}56{()";
    strToStack(st, line);
    clrLst(st);



    // № 2
    for (int i = 0; i < 30; i++) insert(st, randInRange(-50, 50));
    printOneLinkIntList(st);
    printOneLinkIntList(cpLst = cpOneLinkLst(st));
    clrLst(cpLst);
    free(cpLst);

    // № 3   
    srtLst(st);
    clrLst(st);

    for (int i = 0; i < 30; insert(st, i++));
    printOneLinkIntList(st);
    srtLst(st);
    clrLst(st);
    
    for (int i = 29; i >= 0; insert(st, i--));
    printOneLinkIntList(st);
    srtLst(st);
    clrLst(st);

    for (int i = 0; i < 30; i++) insert(st, 35);
    printOneLinkIntList(st);
    srtLst(st);
    clrLst(st);

    for (int i = 0; i < 10; insert(st, i++));
    for (int i = 0; i < 10; i++) insert(st, 9);
    for (int i = 9; i >= 0; insert(st, i--));
    printOneLinkIntList(st);
    srtLst(st);
    clrLst(st);

    free(st);
    return 0;
}
