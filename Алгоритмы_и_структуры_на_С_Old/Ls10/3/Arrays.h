#pragma once
#include <malloc.h>
#include <time.h>
//=
void clearArray(int *arr) {
    for (int i=0; i<SZ; ++i) {
        arr[i]=NULL;
    }
}
T* initArray(T *array){
    //array = (T*) calloc(sizeof(T), size);
    array=(T*)malloc(SZ*sizeof(T));
    clearArray(array);
    return array;
}
//=
void fillArrayRandom(T *array, const int bord){
    srand(time(NULL));
    for (int i=0; i<SZ; ++i){
            array[i]=rand()%bord;
        }
}
//=

//=
void printArray(T *array, char start, char end){
    for (int i=0; i<SZ; ++i) {
            printf("%c%3i%c", start, array[i], end);
    }
    printf("\n");
}
//==
T** init2dArray(T **array, const int row, const int col) {
    //array=(A**)calloc(sizeof(A*), row);
    array=(T**)malloc(row*sizeof(T*));
    for (int i=0; i<row; ++i) {
        //*(array+i)=(T*)calloc(sizeof(T), col);
        *(array+i)=(T*)malloc(col*sizeof(T));
    }
    return array;
}
//==
void fill2dArrayRandom(T** array, const int row, const int col, const int bord) {
    srand(time(NULL));
    for (int i=0; i<row; ++i){
        for (int j=0; j<col; ++j){
            array[i][j]=rand()%bord;
        }
    }
}
//==
void print2dArray(T** array, const int row, const int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("[%3d]", *((*(array + i)) + j));
        }
        printf("\n");
    }
    //printf("\n");
}
//==
int get2dElem(int** array, const int row, const int col) {
    return *((*(array + row)) + col);

}

void set2dElem(int** array, const int row, const int col, int value) {
    *((*(array + row)) + col) = value;
}

//==
void testArray(){
    printf("Array:\n");
    T *ar=initArray(ar);
    fillArrayRandom(ar, 100);
    printArray(ar, '[', ']');
    free(ar);
    printf("2dArray:\n");
    T **arr=init2dArray(arr, SZ, SZ);
    fill2dArrayRandom(arr, SZ, SZ, 100);
    print2dArray(arr, SZ, SZ);
    free(arr);
}
