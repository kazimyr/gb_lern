#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

boolean pushOneLinkStack(OneLinkList *stack, int value) {
    OneLinkNode *tmp = (OneLinkNode*) malloc(sizeof(OneLinkNode));
    if (tmp == NULL) {
        printf("Stack overflow \n");
        return 0;
    }
    tmp->dat = value;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;
    return true;
}

int popOneLinkStack(OneLinkList *stack) {
    if (stack->size == 0) {
        printf("Stack is empty \n");
        return -1;
    }
    OneLinkNode *tmp = stack->head;
    int data = stack->head->dat;
    stack->head = stack->head->next;
    free(tmp);
    stack->size--;
    return data;
}

// 1. Реализовать простейшую хеш-функцию. На вход функции подается строка, на выходе сумма кодов символов.

long int hash(const char * str) {
    int sum = 0;
    for (int i = 0; str[i]; sum += str[i++]);
    return sum;
}

// 2. Имеются монеты номиналом 50, 10, 5, 2, 1 коп. Напишите функцию которая минимальным количеством монет 
//     наберет сумму 98 коп. Для решения задачи используйте “жадный” алгоритм.

int sumStack(OneLinkList *stck){
    int sum = 0;
    OneLinkNode *tmp = stck->head;
    while(tmp) {
        sum += tmp->dat;
        tmp = tmp->next;
    }
    return sum;
}

boolean coinSet(int sum, int *coins, int sz, OneLinkList * stck, int coin) {
    int i = (sum - sumStack(stck))/coins[coin];
    for (int k = i ; k > 0; k--) pushOneLinkStack(stck, coins[coin]);
    if (sumStack(stck) == sum) return true;
    else if ((coin + 1) >= sz) {
        for (int k = i ; k > 0; k--) popOneLinkStack(stck);
        return false;
    }
    while(!coinSet(sum, coins, sz, stck, coin + 1)) {
        if(i-- > 0) popOneLinkStack(stck);
        else if(i < 0) return false;
        
        
    }
    return true;
}



int main() {
    // № 1 
    printf("\n\t%ld\n", hash("Imperiocriticism"));
    printf("\n\t%ld\n", hash("Existentialism"));
    printf("\n\t%ld\n", hash("Insanity"));

    // № 2
    OneLinkList *stck = (OneLinkList*)malloc(sizeof(OneLinkList));
    initOneLinkList(stck);
    int coins[] = {50, 10, 5, 2, 1}; //98
    int fund = 98, qnty = 5; // Для теста: искомая сумма и количество первых монет в массиве
                             // например для fund = 96, qnty = 3; решения нет
                             // а для fund = 98, qnty = 4; требуются  9 монет: 2 2 2 2 10 10 10 10 50
    if (coinSet(fund, coins, qnty, stck, 0)) {
        printf("\nУдача!\nНужно %d монет:\n", stck->size);
        for(OneLinkNode *tmp = stck->head; tmp; tmp = tmp->next) printf("%d ", tmp->dat);
        printf("\n");
    }
    else {
        printf("\nИз набора монет:");
        for(int i = 0; i < qnty; printf("%d ", coins[i++]));
        printf("\nне удается получить сумму %d\n", fund);
    }   
    

    return 0;
}