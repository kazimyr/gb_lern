#include <stdio.h>
#include <stdlib.h>


// 1. Описать очередь с приоритетным исключением


#define SZ 10

typedef struct {
   int pr;
   int dat;
} Node;

Node* arr[SZ];
int head;
int tail;
int items;

void initQueue() {
   for (int i = 0; i < SZ; ++i) {
       arr[i] = NULL;
   }
   tail = 0;
}

Node* rem() {
    if (tail == 0) {
        return NULL;
    } else {
        int flag = 0;
        for (size_t i = 1; i < tail; ++i) 
            if((arr[i]->pr) < (arr[flag]->pr)) flag = i;
        Node *tmp = arr[flag];
        for (size_t i = flag; i < tail;i++) arr[i] = arr[i + 1];
        
        arr[--tail] = NULL;
        return tmp;
    }    
}

void ins(int pr, int dat) {
    if (tail == SZ) {
        printf("%s \n", "Queue is full");
    } else {
        Node *node = (Node*) malloc(sizeof(Node));
        node->dat = dat;
        node->pr = pr;
        arr[tail++] = node;
   }
}

void printQueue() {
   printf("[ ");
   for (int i = 0; i < SZ; ++i) {
       if (arr[i] == NULL)
           printf("[*, *] ");
       else
           printf("[%d, %d] ", arr[i]->pr, arr[i]->dat);
   }
   printf(" ]\n\n");
}

// 2.Реализовать перевод из десятичной в двоичную систему счисления с использованием стека.
// typedef int boolean;
// #define T char
// #define true 1 == 1
// #define false 1 != 1

// boolean pushStack(T *stack, T data, int *cursor) {
//    if (&cursor < SIZE) {
//        stack[++(&cursor)] = data;
//        return true;
//    } else {
//        printf("%s \n", "Stack overflow");
//        return false;
//    }
// }


struct stack {
    int SIZE;
    char *arr;
    int cursor;
};

struct stack* initStack(int sz) {
    struct stack *st = (struct stack *) malloc(sizeof(struct stack));
    st->arr = (char*) calloc(sz, sizeof(char));
    st->SIZE = sz;
    st->cursor = -1;
    return st;
}


char popStack(struct stack *st) {
        if (st->cursor != -1) {
            return *(st->arr + st->cursor--);
        } else {
            printf("%s \n", "Stack is empty");
            return -1;
    }
}

int pushStack(struct stack *st, char data) {
   if (st->cursor < st->SIZE) {
       *(st->arr + (++st->cursor)) = data;
       return 1;
   } else {
       printf("%s \n", "Stack overflow");
       return 0;
   }
}

void decToBinAcrosStack(int k){
    int i = 1;
    for (int n = k; (n /= 2) > 0; i++);
    struct stack *st = initStack(i);
    do
    {
        pushStack(st, '0' + k % 2);
    } while ( (k /= 2) > 0 );
     printf("Двоичное: ");
    while (st->cursor != -1) {
        printf("%c", popStack(st));
    }
    printf("\n\n");
}

    


int main() {
    // № 1
   initQueue();
   ins(1, 11);
   ins(3, 22);
   ins(4, 33);
   ins(2, 44);
   ins(3, 55);
   ins(4, 66);
   ins(5, 77);
   ins(1, 88);
   ins(2, 99);
   ins(6, 100);
   printQueue();
   for (int i = 0; i < 7; ++i) {
       Node* n = rem();
       printf("pr=%d, dat=%d \n", n->pr, n->dat);
   }
   printQueue();

   ins(1, 110);
   ins(3, 120);
   ins(6, 130);
   printQueue();

   for (int i = 0; i < 5; ++i) {
       Node* n = rem();
       printf("pr=%d, dat=%d \n", n->pr, n->dat);
   }
   printQueue();


// № 2
    // struct stack *st = initStack(6);
    // pushStack(st, 'a');
    // pushStack(st, 'b');
    // pushStack(st, 'c');
    // pushStack(st, 'd');
    // pushStack(st, 'e');
    // pushStack(st, 'f');
    // while (st->cursor != -1) {
    //     printf("%c ", popStack(st));
    // }
    // popStack(st);
    int k;
    printf("Ведите десятичное число: ");
    scanf("%d", &k);
    decToBinAcrosStack(k);
    return 0;
}
