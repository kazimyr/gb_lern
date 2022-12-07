#include "geek.h"
#include <locale.h>

boolean vizited[14] = {0};
int links_num[14] = {0}; // полустепень захода для каждого узла
int nexts_num[14] = {0}; // количество смежных вершин для каждой

int visitedDepth[14] = {0};

int find_next_unvizited(int** matrix, int versh, int size) {
  for(int i = 0; i < size; i++) 
    if((get2dInt(matrix, versh, i) == 1) && (vizited[i] == 0)) return i;
  return -1;
}

void depthStackTravers(int** matrix, int size) {
  OneLinkList* stack = (OneLinkList*) malloc(sizeof(OneLinkList));
  initOneLinkList(stack);
  vizited[0] = 1; printf("%c   ", 'A');
  pushOneLinkStack(stack, 0);
  while(stack->size) {
    int tmp = find_next_unvizited(matrix, stack->head->dat, size);
    if(tmp != -1) {
      vizited[tmp] = 1;
      printf("%c   ", tmp + 'A');
      pushOneLinkStack(stack, tmp);
    } else popOneLinkStack(stack);
  }
  clearIntArray(vizited, size);
  printf("\n");
}

void nexts_tops(int** matrix, const int size) {
  for(int i = 0; i < size; ++i) {
    for(int j = 0; j < size; ++j) {
      if((matrix[j][i]==1) && (i!=j)) nexts_num[i]++;
    }
  }
}

void nexts_rec_tops(int** matrix, int st, const int size) {
  visitedDepth[st] = 1;
  for(int r = 0; r < size; ++r) {
    if(matrix[st][r] == 1 ) {
      if(visitedDepth[r] == 0) nexts_rec_tops(matrix, r, size);
      if(st!=r) links_num[r]++;
    }
  }
}

void printRnjArray(int* array, int size) {
    /*
    char format[7];
    sprintf(format, "%%%dd", offset);
    for (int i = 0; i < size; ++i) {
        printf(format, array[i]);
        if (i != size - 1)
            printf(",");
    }
    printf("\n");*/
  int tmp; int ind = 0;
  //tmp = array[0];
  for(int i = 0; i < size; ++i) {
    tmp = array[i]; ind = i;
    for(int j = i; j < size; ++j) {
      if((array[j] > tmp) && (j!=ind)) { tmp = array[j]; ind = j; }
    }
    printf("%c   ", ind + 'A');
    //if(tmp == array[i]) tmp = array[i++];
  }
}

void main() {
  setlocale(LC_ALL, "Rus");
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
  printf("Stack travers: ");
  depthStackTravers(adj, 14);
  nexts_tops(adj, 14);
  printf("Nexts tops: ");
  printIntArray(nexts_num, 14, 3);
  printf("Links count [recurs]: ");
  nexts_rec_tops(adj, 0, 14);
  printIntArray(links_num, 14, 3);
  printRnjArray(nexts_num, 14);
}