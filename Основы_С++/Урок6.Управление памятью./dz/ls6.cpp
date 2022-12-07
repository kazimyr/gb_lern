#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <filesystem>

struct ourArr {
    int SIZE;
    int *arr;
    void (*func)(int, int*);
};

void printArray(const size_t SIZE, const double *ar) {
    for (size_t i = 0; i < SIZE; ++i) std::cout << ar[i] << " ";
    std::cout << std::endl;
}

void printArray(const size_t SIZE, const int *ar) {
    for (size_t i = 0; i < SIZE; ++i) std::cout << ar[i] << " ";
    std::cout << std::endl;
}

int gtNmbr() {
    int n;
    std::cout << "Enter an positive integer number!";
    while (std::cin >> n, std::cin.fail() || n < 0) {
        std::cout << "Error. Please enter an positive integer number!" << std::endl;
        std::cin.clear();
        std::cin.ignore(32767, '\n');
    }
    return n;
}

void powerOf2(const int SIZE, int *arr){
    arr[0] = 1;
    for (size_t i = 1; i < SIZE; i++) {
        arr[i] = arr[i - 1] * 2;
    }
}

void rndm(const int SIZE, int *arr){
    
    for (size_t i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100;
    }
}

void initAr(ourArr * str) {
    str->func(str->SIZE, str->arr);
}

ourArr* createArr(const int n, void (*initFunc)(int, int*)){
    ourArr* ptrStruc = new(std::nothrow) ourArr;
    if(ptrStruc) {

        if ((ptrStruc->arr = new (std::nothrow) int[n]) != nullptr) {
            ptrStruc->SIZE = n;
            ptrStruc->func = initFunc;

            return ptrStruc;

        } else {
            std::cout << "Error! Can not allocate memory for array!";
            return nullptr;
        }
    } else  {
        std::cout << "Error! Can not allocate memory for structure!";
        return nullptr;
    }
}

void deleteArr(ourArr *ptrStruc) {
    delete[] ptrStruc->arr;
    ptrStruc->arr = nullptr;
    delete ptrStruc;
    ptrStruc = nullptr;
}
std::ofstream createFile(int i, std::string *fname){
    
    std::cout << std::endl << "Enter file name for " << i << " file: " << std::endl;
    std::cin >> *fname;
    *fname += ".txt";
    std::ofstream fout (*fname);
    return fout;
}

void initFl(std::ofstream *fout){
    for (size_t r = rand() % 50 + 50, k = 0; k < r; k++){
        std::string str = "";
        for (size_t j = 0; j < 79; j++){
            str += static_cast<char>(rand() % 95 + 32);
        }
    *fout << str + "\n";
    }
}


int main() {
    srand(static_cast<unsigned int>(time(0)));
// 1. Выделить в памяти динамический одномерный массив типа int. Размер массива запросить у пользователя.
// Инициализировать его числами степенями двойки: 1, 2, 4, 8, 16, 32, 64, 128 ... 
// Вывести массив на экран. Не забыть освободить память. =) Разбить программу на функции.
    std::cout << "Ex 1" << std::endl << std::endl;
    std::cout << "Enter size of your array: " << std::endl;
    ourArr* Strc = createArr(gtNmbr(), powerOf2);
    if(Strc) {
        initAr(Strc);
        printArray(Strc->SIZE, Strc->arr);
        deleteArr(Strc);
    } else std::cout << "Error. Unfortunately";
    std::cout << std::endl << std::endl;

// 2. Динамически выделить матрицу 4х4 типа int. Инициализировать ее псевдослучайными числами через функцию rand. 
// Вывести на экран. Разбейте вашу программу на функции которые вызываются из main.
    std::cout << "Ex 2" << std::endl << std::endl;
    const size_t m = 4; 
    const size_t n = 4;
    ourArr **ptrArr = new(std::nothrow) ourArr* [m];
    
    for (size_t i = 0; i < m; i++){
        
        if (ptrArr[i] = createArr(n, rndm)) {
            
            initAr(ptrArr[i]);
            printArray(ptrArr[i]->SIZE, ptrArr[i]->arr);
        } else std::cout << "Error! Can not allocate memory for " << i << "line";
    }
    for (size_t i = 0; i < m; i++) {
        delete ptrArr[i];
    }
    delete[] ptrArr;
    ptrArr = nullptr;
    std::cout << std::endl << std::endl;


// 3. Написать программу c 2-я функциями, которая создаст два текстовых файла (*.txt),
// примерно по 50-100 символов в каждом (особого значения не имеет с каким именно содержимым). 
// Имена файлов запросить у польлзователя.
    std::cout << "Ex 3" << std::endl;
    std::string str, fln, fl[3];
    for (size_t i = 0; i < 2; i++) {
        std::ofstream fu = createFile(i + 1, &fln);
        initFl(&fu);
        std::cout << "File " << fln << " created" << std::endl;
        fu.close();        
    }
    std::cout << std::endl << std::endl;

// 4. * Написать функцию, «склеивающую» эти файлы в третий текстовый файл (имя файлов спросить у пользователя).
    std::cout << "Ex 4" << std::endl << std::endl;
    std::cout << std::endl << "Enter file name for result of merge" << std::endl;
    std::cin >> fl[2];
    fl[2] += ".txt";
    std::ofstream fu (fl[2]);    
    for (size_t i = 0; i < 2; i++) {
        std::cout << std::endl << "Enter " << i + 1 << " file name for merge" << std::endl;
        std::cin >> fl[i];
        fl[i] += ".txt";

        while(!std::filesystem::exists(fl[i])) {
            std::cout << std::endl << "File " << fl[i] << " is not exist" << std::endl;
            std::cout << std::endl << "Enter correct " << i + 1 << " file name for merge" << std::endl;
            std::cin >> fl[i];
            fl[i] += ".txt";
        }
        std::ifstream fi (fl[i]);

        while(std::getline(fi, str)) fu << str + "\n";
        fi.close();
    }
    fu.close();

    std::cout << std::endl << std::endl;    
// 5. * Написать программу, которая проверяет присутствует ли указанное пользователем при запуске
// программы слово в указанном пользователем файле (для простоты работаем только с латиницей).
    std::cout << "Ex 4" << std::endl << std::endl;

    std::cout << std::endl << "Enter a search word" << std::endl;
    std::cin >> str;
    std::ifstream fi (fl[2]);
    int sum = 0;
    while (std::getline(fi, fln)) {
        for (int pos = 0; pos = fln.find(str, pos) + 1; sum++);
    }
    std::cout << "Word \"" << str << "\" appears " << sum << " times in the " << fl[2] << " file"; 

    std::cout << std::endl << std::endl;
    return 0;
}