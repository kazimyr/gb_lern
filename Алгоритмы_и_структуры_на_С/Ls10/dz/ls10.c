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

void clearIntArray(int* arr, const int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = 0;
    }
}

void printIntArray(int* array, int size, int offset) {
    char format[7];
    sprintf(format, "%%%dd", offset);
    for (int i = 0; i < size; ++i) {
        printf(format, array[i]);
        if (i != size - 1)
            printf("\t");
    }
    printf("\n");
}

// 1. Реализовать обход в ГЛУБИНУ с использованием стека

void depthTravers(const int n, int matrix[][n], int visited[], int st) {
    // int *visitedDepth = calloc(n, sizeof(int));
    OneLinkList *stck = (OneLinkList*)malloc(sizeof(OneLinkList));
    initOneLinkList(stck);
    int flag = 1;
    printf("%c ", st + 'A');
    pushOneLinkStack(stck, st);
    visited[st] = 1;
    do {
        st = stck->head->dat;
        for (int r = 0; r < n; ++r) {
            if (flag = (matrix[st][r] && !visited[r])) {
                printf("%c ", r + 'A');
                pushOneLinkStack(stck, r);
                visited[r] = 1;
                break;
            }
        }
        if (!flag) popOneLinkStack(stck);
    } while (stck->size);
    clearIntArray(visited, n);
    printf("\n");
}


// 2. Моделируем робот поисковой системы. Дан готовый простой граф с циклическими связями. 
// Нужно обойти этот граф двумя способами и подсчитать количество ссылок на каждый из узлов графа 
// (полустепень захода):
// 2.1 обход графа РЕКУРСИВНОЙ ФУНКЦИЕЙ (с подсчётом только смежных со стартовой вершин)

void traversalCount (const int size, int matrix[][size], int vstd[], int trvrsLnk[], int start) {
    vstd[start] = 1;
    for (int i = 0; i < size; ++i) {
        if (matrix[i][start] == 1) {
            trvrsLnk[start]++;
            if (!vstd[i]) traversalCount (size, matrix, vstd, trvrsLnk, i);
        }
    }
}


// 2.2 обход графа по матрице смежности (с подсчётом всех вершин графа) 
// В конце обхода вывести два получившихся списка всех узлов В ПОРЯДКЕ УМЕНЬШЕНИЯ количества ссылок на них.

void adjacencyCount (const int size, int matrix[][size], int trvrsLnk[]) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[j][i] == 1)
                trvrsLnk[i]++;
        }
    }
}

int main(){

    int mtrx[14][14] = {
            {0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
            {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, 
            {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, 
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, 
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
            {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}
    };
    // не стал исправлять ориентированное ребро B->K: (1,10)=0 (10,1)=1
    // учтены петли, поскольку полустепень захода
    // по определению - общее количество входящих ребер
    // поэтому результаты отличаются от ваших


    int visited[14] = {0};
    // № 1    
    depthTravers(14, mtrx, visited, 0);
    depthTravers(14, mtrx, visited, 1);
    depthTravers(14, mtrx, visited, 10);
    depthTravers(14, mtrx, visited, 4);
    depthTravers(14, mtrx, visited, 5);
    depthTravers(14, mtrx, visited, 8);

    // № 2
    int traversalLinks[14] = {0};
    printf("\n\n");
    for(int i=0; i< 14; i++) printf("%c\t", i + 'A');
    printf("\n");
    adjacencyCount(14, mtrx, traversalLinks);
    printIntArray(traversalLinks, 14, 0);
    clearIntArray(traversalLinks, 14);
    traversalCount (14, mtrx, visited, traversalLinks, 0);
    printIntArray(traversalLinks, 14, 0);
    printf("\n");
    return 0;
}