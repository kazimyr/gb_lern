#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T int
#define SZ 14

#include "Arrays.h"
//#include "Stacks.h"
//#include "Queues.h"
#include "Lists.h"
//#include "2.h"
//#include "3.h"

bool visit[SZ]={false};

int checkVisitVertrex(int **matix, int ver){
    for(int i=0; i<SZ; i++){
        if(get2dElem(matix, ver, i) == 1 && !visit[i]){
            return i;
        }
    }
    return -1;
}

void depthTraversWStack(int **matix){
    OLList *st=initOLList(st);
    visit[0]=true;
    printf(" %3c ", 0 + 65);
    pushOLListSt(st, 0);
    while(st->size){
        int v=checkVisitVertrex(matix, st->head->data);
        if(v == -1){
            popOLListSt(st);
        }else{
            visit[v]=true;
            printf(" %3c ", v + 65);
            pushOLListSt(st, v);
        }
    }
    clearArray(visit);
    printf("\n");
}

int traversalLinks[SZ] = {0};
int adjacencyLinks[SZ] = {0};

void adjacencyCount (int** matrix) {
    for (int i = 0; i < SZ; ++i) {
        for (int j = 0; j < SZ; ++j) {
            if (matrix[j][i] == 1)
                if (i != j) adjacencyLinks[i]++;
        }
    }
}

void traversalCount (int** matrix, int start) {
    TLList *queue = initTLList(queue);
    clearArray(visit);
    pushBackTL(queue, start);
    while (queue->size > 0) {
        int indx = popFrontTL(queue);
        if (visit[indx]) continue;
        visit[indx] = true;
        for (int i = 0; i < SZ; ++i) {
            if (get2dElem(matrix, indx, i) == 1) {
                if (i != indx)
                    traversalLinks[i]++;
                if (!visit[i])
                    pushBackTL (queue, i);
            }
        }
    }
    clearArray(visit);
}

int main(){
    int **satrix=init2dArray(satrix, SZ, SZ);
    set2dElem(satrix, 0, 1, 1);
    set2dElem(satrix, 0, 6, 1);
    set2dElem(satrix, 0, 7, 1);

    set2dElem(satrix, 1, 0, 1);
    set2dElem(satrix, 1, 2, 1);
    set2dElem(satrix, 1, 6, 1);
    set2dElem(satrix, 1, 10, 1);

    set2dElem(satrix, 2, 1, 1);
    set2dElem(satrix, 2, 2, 1);
    set2dElem(satrix, 2, 3, 1);

    set2dElem(satrix, 3, 2, 1);
    set2dElem(satrix, 3, 9, 1);
    set2dElem(satrix, 3, 13, 1);

    set2dElem(satrix, 4, 8, 1);

    set2dElem(satrix, 6, 0, 1);
    set2dElem(satrix, 6, 1, 1);
    set2dElem(satrix, 6, 10, 1);
    set2dElem(satrix, 6, 11, 1);

    set2dElem(satrix, 7, 0, 1);
    set2dElem(satrix, 7, 11, 1);

    set2dElem(satrix, 8, 4, 1);
    set2dElem(satrix, 8, 8, 1);

    set2dElem(satrix, 9, 3, 1);
    set2dElem(satrix, 9, 9, 1);


    set2dElem(satrix, 10, 1, 1);
    set2dElem(satrix, 10, 6, 1);
    set2dElem(satrix, 10, 11, 1);
    set2dElem(satrix, 10, 12, 1);

    set2dElem(satrix, 11, 6, 1);
    set2dElem(satrix, 11, 7, 1);
    set2dElem(satrix, 11, 10, 1);
    set2dElem(satrix, 11, 12, 1);

    set2dElem(satrix, 12, 10, 1);
    set2dElem(satrix, 12, 11, 1);
    set2dElem(satrix, 12, 13, 1);

    set2dElem(satrix, 13, 3, 1);
    set2dElem(satrix, 13, 12, 1);

    depthTraversWStack(satrix);

    adjacencyCount(satrix);
    printArray(adjacencyLinks,' ', ' ');

    traversalCount(satrix, 0);
    printArray(traversalLinks, ' ', ' ');

    return 0;
}
