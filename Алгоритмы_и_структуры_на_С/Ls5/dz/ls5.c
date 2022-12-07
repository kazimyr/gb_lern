#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int get2dInt(int** array, const size_t row, const size_t col) {
    return *((*(array + row)) + col);

}

void set2dInt(int** array, const size_t row, const size_t col, int value) {
    *((*(array + row)) + col) = value;
}

int** init2dIntArray(int** array, const size_t row, const size_t col) {
    array = (int**) calloc(row, sizeof(int*));
    for (size_t i = 0; i < row; *(array + i++) = (int*) calloc(col, sizeof(int)));
    return array;
}

void free2dIntArray(int** array, const size_t row) {
        for (size_t i = 0; i < row; free(*(array + i++)));
        free(array);  
}

void print2dIntArray(int** array, const size_t row, const size_t col, int offset) {
    char format[7];
    sprintf(format, "%%-%dd", offset);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf(format, get2dInt(array, i, j));
        }
        printf("\n");
    }
    printf("\n");
}

void fill2dIntArray(int** array, const size_t row, const size_t col) {
    srand(time(NULL));
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            set2dInt(array, i, j, rand() % 100);
        }
    }
}

void swapInt(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void sortInt2dBubble(int** ar, const size_t row, const size_t col) {
    for (size_t i = 0, leni = row * col; i < leni; i++)
        for (size_t r, r1, c, c1, j = 0, lenj = leni - i - 1; j < lenj; j++) {
            r = j / col, c = j % col;
            r1 = (j + 1) / col, c1 = (j + 1) % col;
            if (get2dInt(ar, r, c) > get2dInt(ar, r1, c1)) swapInt(*(ar + r) + c, *(ar + r1) + c1);
        }
}


// 1. Реализовать пузырьковую сортировку двумерного массива например, массив

// 1,9,2
// 5,7,6
// 4,3,8
// должен на выходе стать
// 1,2,3
// 4,5,6
// 7,8,9



// 2.Описать подробную блок-схему алгоритма Трабба-Прадо-Кнута и реализовать его в коде на языке С:

// 1 - запросить у пользователя 11 чисел и записать их в последовательность П
// 2 - инвертировать последовательность П
// 3 - для каждого элемента последовательности П произвести вычисление по формуле sqrt(fabs(Х)) + 5 * pow(Х, 3) 
//     и если результат вычислений превышает 400 - проинформировать пользователя.

void tpk(double *arr, int len) {
    double y;
    printf("Введите последовательность из %d чисел:\n", len);
    for (int i = len - 1; i >= 0; scanf("%lf", arr + i--)); //Совмещаем запись последовательности и ее инвертирование
    printf("\nРезультат:\n");
    for (int i = 0; i < len; i++) {                         // Печатаем результат в неинвертированном виде
        printf("%3d - %10.6g - ", i + 1, *(arr + i));
        y = sqrt(fabs(*(arr + i)) + 5 * pow(*(arr + i), 3));
        if (y > 400)
            printf("Слишком большое\n");
        else
            printf("%10.6g\n", y);
    }
    printf("\n");
}

int main() {

    // № 1
    int len = 11;
    double arr[len];
    tpk(arr, len);

    // № 2
    size_t n = 3, m = 5;
    int** matrix = init2dIntArray(matrix, n, m);
    fill2dIntArray(matrix, n, m);
    print2dIntArray(matrix, n, m, 6);

    sortInt2dBubble(matrix, n, m);
    print2dIntArray(matrix, n, m, 6);

    free2dIntArray(matrix, n);
}