#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>

void swapInt(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void printIntArray(int* array, int size, int offset) {
    char format[7];
    sprintf(format, "%%%dd", offset);
    for (int i = 0; i < size; ++i) {
        printf(format, array[i]);
        if (i != size - 1)
            printf(",");
    }
    printf("\n");
}

void fillIntRandom(int* array, int size, int border) {
    for (int i = 0; i < size; ++i)
        *(array + i) = rand() % border;
}

void qs(int* arr, int first, int last) {
    int i = first;
    int j = last;

    int x = arr[(first + last) / 2];

    do {
        while (arr[i] < x) i++;
        while (arr[j] > x) j--;

        if (i <= j) {
            swapInt(&arr[i], &arr[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last) qs(arr, i, last);
    if (first < j) qs(arr, first, j);
}

void qsL(int* arr, int first, int last) {
    if (first < last) {
        int x = arr[last];
        int i = first;
        int j;
        for (j = first; j <= last - 1; j++) {
            if (arr[j] <= x) {
                swapInt(&arr[i], &arr[j]);
                i++;
            }
        }
        swapInt(&arr[i], &arr[last]);
        qsL(arr, first, i - 1);
        qsL(arr, i + 1, last);
    }
}

void qsL2(int* arr, int first, int last) {
    if (first < last) {
        int x = arr[last];
        int i = last;
        int j;
        for (j = last - 1; j >= first; j--) {
            if (arr[j] >= x) {
                swapInt(&arr[i], &arr[i-1]);
                //swapInt(&arr[i], &arr[j]);
                printIntArray(arr, 10, 3);
                i--;
            }
        }
        //swapInt(&arr[i], &arr[last]);
        qsL2(arr, first, i - 1);
        qsL2(arr, i + 1, last);
    }
}

void main() {
    const int SZ = 10;
    int arr[SZ];
    fillIntRandom(arr, SZ, 10);
    printIntArray(arr, SZ, 3);
    qsL(arr, 0, SZ - 1);
    printIntArray(arr, SZ, 3);
    printf("Сортировка чет/нечет \n");
    fillIntRandom(arr, SZ, 10);
    printIntArray(arr, SZ, 3);
    qsL2(arr, 0, SZ - 1);
    printIntArray(arr, SZ, 3);
}