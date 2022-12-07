#include <stdio.h>
#include <stdlib.h>



void fillIntRandom(int* array, int size, int border) {
    for (int i = 0; i < size; ++i)
        *(array + i) = rand() % border;
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

void swapInt(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void sortInserts(int* arr, int len) {
   int temp, pos;
   for (int i = 1; i < len; ++i) {
       temp = arr[i];
       pos = i - 1;
       while (pos >= 0 && arr[pos] > temp) {
           arr[pos + 1] = arr[pos];
           pos--;
       }
       arr[pos + 1] = temp;
   }
}

// 1. Описать в коде улучшенный алгоритм быстрой сортировки (Смесь сортировки Хоара и сортировки вставками)
int median(int* arr, int first, int last) {
    int m = (first + last--) / 2;
    if (arr[first] > arr[m] && arr[first] < arr[last]) 
        swapInt(arr + first, arr + m);
    if (arr[last] > arr[m] && arr[last] < arr[first]) 
        swapInt(arr + last, arr + m);
    return m;
}

void bestQs(int* arr, int first, int last, int len) {

    int i = first;
    int j = last;
    int x = arr[median(arr, first, last)];

    do {
        while (arr[i] < x) i++;
        while (arr[j] > x) j--;

        if (i <= j) {
            swapInt(arr + i, arr + j);
            i++;
            j--;
        }
    } while (i <= j);

    if (last - i > len) 
        bestQs(arr, i, last, len);
    else 
        sortInserts(arr + i, last - i + 1);
    if (j - first > len) 
        bestQs(arr, first, j, len + 1);
    else 
        sortInserts(arr + first, j - first);
}

// 2. Сортировать в массиве целых положительных чисел только чётные числа, нечётные оставив на своих местах при 
// помощи алгоритма блочной сортировки, то есть массив вида [0 2 8 3 4 6 5 9 8 2 7 3] превратить в [0 2 2 3 4 6 5 9 8 8 7 3]

void bucketSort(int* arr, int len) {
   const int max = len;
   const int b = 10;

   int buckets[b][max+1];
   for (int i = 0; i < b; ++i) {
       buckets[i][max] = 0;
   }

   for (int digit = 1; digit < 1000000000; digit*=10) {
        for (int i = 0; i < max; ++i) {
            int d = (arr[i] / digit) % b;
            buckets[d][buckets[d][max]++] = arr[i];
       }
       int idx = 0;
       for (int i = 0; i < b; ++i) {
           for (int j = 0; j < buckets[i][max]; ++j) {
                arr[idx++] = buckets[i][j];
           }
           buckets[i][max] = 0;
       }
   }
}

int main() {

    // № 1
    printf("Смесь сортировки Хоара и сортировки вставками\n");
    const int SZ = 30;
    int arr[SZ];
    fillIntRandom(arr, SZ, 100);
    printIntArray(arr, SZ, 3);
    bestQs(arr, 0, SZ - 1, 10); // Последний аргумент - длина массива, 
                                // при достижении которой переключаемся с сортировки Хоара на сортировку вставками
    printIntArray(arr, SZ, 3);

    // № 2
    printf("\n\n Блочная сортировка четных элементов массива\n");
    fillIntRandom(arr, SZ, 100);
    printIntArray(arr, SZ, 3);
    int tmp[SZ];
    int idx = 0;
    for (int i = 0; i < SZ; i++) if (!(arr[i] % 2)) tmp[idx++] = arr[i];
    bucketSort(tmp, idx);
    for (int i = 0, idx = 0; i < SZ; i++) if (!(arr[i] % 2)) arr[i] = tmp[idx++];
    printIntArray(arr, SZ, 3);



    return 0;
}