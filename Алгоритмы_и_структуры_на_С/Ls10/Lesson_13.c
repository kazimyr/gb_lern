
#include "geek.h"

boolean visit[14] = {0};

int getUnvisitedVertex (int** matrix, int ver, int size) {
    for (int i = 0; i < size; i++) {
        if (get2dInt(matrix, ver, i) == 1 && !visit[i])
            return i;
    }
    return -1;
}

void depthTraversStack(int** matrix, int size) {
    OneLinkList* stack = (OneLinkList*) malloc(sizeof(OneLinkList));
    initOneLinkList(stack);

    visit[0] = true;
    printf("%c\t", 0 + 65);
    pushOneLinkStack(stack, 0);

    while (stack->size) {
        int v = getUnvisitedVertex(matrix, stack->head->dat, size);
        if (v == -1) {
            popOneLinkStack(stack);
        } else {
            visit[v] = true;
            printf("%c\t", v + 65);
            pushOneLinkStack(stack, v);
        }
    }
    clearIntArray(visit, size);
    printf("\n");
}

int traversalLinks[14] = {0};
int adjacencyLinks[14] = {0};

void adjacencyCount (int** matrix, const int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[j][i] == 1)
                if (i != j) adjacencyLinks[i]++;
        }
    }
}

void traversalCount (int** matrix, int start, const int size) {
    TwoLinkList* queue = (TwoLinkList*) malloc(sizeof(TwoLinkList));
    initTwoLinkList(queue);
    clearIntArray(visit, size);
    TwoLinkEnqueue(queue, start);
    while (queue->size > 0) {
        int indx = TwoLinkDequeue(queue);
        if (visit[indx]) continue;
        visit[indx] = true;
        for (int i = 0; i < size; ++i) {
            if (get2dInt(matrix, indx, i) == 1) {
                if (i != indx)
                    traversalLinks[i]++;
                if (!visit[i])
                    TwoLinkEnqueue (queue, i);
            }
        }
    }
    clearIntArray(visit, size);
}

void lesson_13() {
    int** adj = init2dIntArray(adj, 14, 14);
    setLineValues(adj, 14,  0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0);
    setLineValues(adj, 14,  1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
    setLineValues(adj, 14,  2, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    setLineValues(adj, 14,  3, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1);
    setLineValues(adj, 14,  4, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0);
    setLineValues(adj, 14,  5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    setLineValues(adj, 14,  6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0);
    setLineValues(adj, 14,  7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
    setLineValues(adj, 14,  8, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0);
    setLineValues(adj, 14,  9, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
    setLineValues(adj, 14, 10, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0);
    setLineValues(adj, 14, 11, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0);
    setLineValues(adj, 14, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1);
    setLineValues(adj, 14, 13, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
    depthTraversStack (adj, 14);


    printf("\n");
    for(int i=0; i< 14; i++)
    {
        printf("%c\t", i + 65);
    }
    printf("\n");
    adjacencyCount(adj, 14);
    printIntArray(adjacencyLinks, 14, 0);

    traversalCount(adj, 0, 14);
    printIntArray(traversalLinks, 14, 0);
}