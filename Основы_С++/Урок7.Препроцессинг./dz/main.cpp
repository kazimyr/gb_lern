#include <iostream>
#include "mylib.h"
using namespace my;
using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
// 1. Создайте проект из 2х cpp файлов и заголовочного (main.cpp,
// mylib.cpp, mylib.h) во втором модуле mylib объявить 3 функции:
// для инициализации массива (типа float), печати его на экран и
// подсчета количества отрицательных и положительных
// элементов. Вызывайте эти 3-и функции из main для работы с
// массивом.
// 5. * Сделайте задание 1 добавив свой неймспейс во втором
// модуле (первое задание тогда можно не делать).

    cout << "Ex 1, 5" << endl << endl;
    float Arr[50]; 
    initArr(50, Arr);
    printArray(50, Arr);
    countArr(50, Arr);
    cout << endl << endl;

// 2. Описать макрокоманду (через директиву define),
// проверяющую, входит ли переданное ей число (введенное с
// клавиатуры) в диапазон от нуля (включительно) до переданного
// ей второго аргумента (исключительно) и возвращает true или
// false, вывести на экран «true» или «false».

    cout << "Ex 2" << endl << endl;
# define PrntDiapFrom0ToP(x, p) cout<<x<<" in [0, "<<p<<"): its "<<((x>=0&&x<p)?"true":"false")<<endl;
    int x = gtNmbr(), p = rand() % 100 + 1;
    PrntDiapFrom0ToP(x, p);
    cout << endl << endl;


// 3. Задайте массив типа int. Пусть его размер задается через
// директиву препроцессора #define. Инициализируйте его через
// ввод с клавиатуры. Напишите для него свою функцию
// сортировки (например Пузырьком). Реализуйте перестановку
// элементов как макрокоманду SwapINT(a, b). Вызывайте ее из
// цикла сортировки.

    cout << "Ex 3" << endl << endl;
#define ArSize 10
    if (int *arr = new (nothrow) int[ArSize]) {
        cout << "Filling the array..." << endl;
        for (size_t i = 0; i < ArSize; i++){
            arr[i]  = gtNmbr();
        }
        sortArr(ArSize, arr);
        cout << "Sorted array:" << endl;
        printArray(ArSize, arr);
        delete [] arr;
        arr = nullptr;
    } else cout << "Error! Can not allocate memory for array!";
    cout << endl << endl;


// 4. * Объявить структуру Сотрудник с различными полями.
// Сделайте для нее побайтовое выравнивание с помощью
// директивы pragma pack. Выделите динамически переменную
// этого типа. Инициализируйте ее. Выведите ее на экран и ее
// размер с помощью sizeof. Сохраните эту структуру в текстовый
// файл.

    cout << "Ex 4" << endl << endl;

if(Employee *em = new(nothrow) Employee) {

    em -> id = 3258475927945667;
    em -> age = 37;
    em -> salary = 80000.20;
    printStruct(em);
    printStruct(em, "mystruct.txt");

    delete em;
    em = nullptr;
} else cout << "Error! Can not allocate memory for structure!";
    cout << endl << endl;
    return 0;
}