#include <iostream>
#include <cmath>
// #include <string>

void printArray(const size_t SIZE, const double *ar) {
    for (size_t i = 0; i < SIZE; std::cout << ar[i] << " ", ++i);
    std::cout << std::endl;
}

void printArray(const size_t SIZE, const int *ar) {
    for (size_t i = 0; i < SIZE; std::cout << ar[i] << " ", ++i);
    std::cout << std::endl;
}

void invert(const size_t SIZE, int *ar) {
    printArray(SIZE, ar);
    for (size_t i = 0; i < SIZE; ar[i] = (ar[i] + 1) % 2, ++i);
    printArray(SIZE, ar);
}

void initial(const size_t SIZE, int *ar) {
    for (size_t i = 0; i < SIZE; ar[i] = 1 + i * 3, i++);
    printArray(SIZE, ar);
}

void cycleShift(int n, const size_t SIZE, int *ar){
    int sgn = ((n > 0) * 2) - 1;
    int idx = n > 0 ? SIZE - 1: 0;
    n = abs(n);
    if (n %= SIZE) {
        int tmp[n];
        for (size_t i = 0; i <  n; idx -= sgn, i++) {
            tmp[i] = ar[idx];
        }

        for (size_t i = 0; i < (SIZE - n); idx -= sgn, i++){
            ar[idx + n* sgn] = ar[idx];
        }

        idx = idx + n * sgn;

        for (size_t i = 0; i < n; idx -= sgn, i++) {
            ar[idx] = tmp[i];
        }
    }
    printArray(SIZE, ar);
}

int lArSum(int idx, int *ar) {
    int sum = 0;
    for (size_t i = 0; i <= idx; sum += ar[i], i++);
    return sum;
}

int rArSum(int idx, const size_t SIZE, int *ar) {
    int sum = 0;
    for (size_t i = idx + 1; i < SIZE; sum += ar[i], i++);
    return sum;
}

bool checkBalance(const size_t SIZE, int *ar) {
    printArray(SIZE, ar);
    for (size_t i = 0; i < SIZE; i++) {
        if (lArSum(i, ar) == rArSum(i, SIZE, ar)) {
            std::cout << "Between elements number " << i + 1 << " and " << i + 2 << " ";
            return true;
        }
    }
    return false;
}

int main() {
// 1. Написать функцию которая выводит массив double чисел
// на экран. Параметры функции это сам массив и его размер.
// Вызвать эту функцию из main.
    std::cout << " Задача 1 " << std::endl;
    double arr1[12] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7, 7.8, 9.10, 10.11, 11.12, 12.13};
    for (size_t i = 1; i < 13; printArray(i, arr1), ++i);
    std::cout << std::endl;

// 2. Задать целочисленный массив, состоящий из элементов 0
// и 1. Например: [ 1, 1, 0, 0, 1, 0, 1, 1, 0, 0 ]. Написать функцию,
// заменяющую в принятом массиве 0 на 1, 1 на 0. Выводить
// на экран массив до изменений и после.
    std::cout << " Задача 2 " << std::endl;
    int Arr2[] = {1, 1, 0, 0, 1, 0, 1, 1, 0, 0};
    invert(sizeof(Arr2)/sizeof(Arr2[0]), Arr2);
    std::cout << std::endl;

// 3. Задать пустой целочисленный массив размером 8.
// Написать функцию, которая с помощью цикла заполнит его
// значениями 1 4 7 10 13 16 19 22. Вывести массив на экран.
    std::cout << " Задача 3 " << std::endl;
    int Arr3[8];
    initial(sizeof(Arr3)/sizeof(Arr3[0]), Arr3);
    std::cout << std::endl;

// 4. * Написать функцию, которой на вход подаётся
// одномерный массив и число n (может быть положительным,
// или отрицательным), при этом метод должен циклически
// сместить все элементы массива на n позиций.
    std::cout << " Задача 4 " << std::endl;
    int shft = -15;
    printArray(sizeof(Arr3)/sizeof(Arr3[0]), Arr3);
    std::cout << "Двигаем на " << shft << std::endl;
    cycleShift(shft, sizeof(Arr3)/sizeof(Arr3[0]), Arr3);
    std::cout << std::endl;
 
 // 5. ** Написать функцию, которой передается не пустой
// одномерный целочисленный массив, она должна вернуть
// истину если в массиве есть место, в котором сумма левой и
// правой части массива равны. Примеры: checkBalance([1, 1,
// 1, || 2, 1]) → true, checkBalance ([2, 1, 1, 2, 1]) → false,
// checkBalance ([10, || 1, 2, 3, 4]) → true. Абстрактная граница
// показана символами ||, эти символы в массив не входят.
    std::cout << " Задача 5 " << std::endl;
    int arr4[] = {10, 1, 2, 3, 4};
    if (checkBalance(sizeof(arr4)/sizeof(arr4[0]), arr4)) {
        std::cout << " → true" << std::endl;
    } else {
        std::cout << " → false" << std::endl;
    }

}