#include <iostream>
#include <fstream>

namespace my {
using namespace std;

#pragma pack(push,1)
    struct Employee {
        long id;
        unsigned short age;
        double salary;
    };
#pragma pack(pop)

void initArr(const size_t SIZE, float *arr){
    
    for (size_t i = 0; i < SIZE; i++) {
        arr[i] = (static_cast<float>(rand() % 100) - 50.0)/(static_cast<float>((rand() % 10)) + 1.0);
    }
}

void printArray(const size_t SIZE, const int *ar) {
    for (size_t i = 0; i < SIZE; ++i) std::cout << ar[i] << " ";
    std::cout << std::endl;
}

void printArray(const size_t SIZE, const float *arr) {
    for (size_t i = 0; i < SIZE; ++i) {
        cout << arr[i];
        (i + 1) % 10 ? cout << " " : cout << endl;
    }
}

void countArr(const size_t SIZE, const float *arr) {
    int count[2] = {0, 0};
    for (size_t i =0; i < SIZE; i++){
        arr[i] < 0 ? count[0]++ : count[1]++;
    }
    cout << "Negative nambers: " << count[0] << endl;
    cout << "Positive nambers: " << count[1] << endl;
}

int gtNmbr() {
    int n;
    cout << "Enter an integer number: ";
    while (cin >> n, cin.fail() || n < 0) {
        cout << "Error. Please enter an integer number!" << endl;
        cin.clear();
        cin.ignore(32767, '\n');
    }
    return n;
}


inline void SwapINT(int& a, int& b){
    a ^= b ^= a ^= b;
}

void sortArr(const size_t SIZE, int *ar){
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - i - 1; j++) {
            if (ar[j] > ar[j + 1]) {
                SwapINT(ar[j], ar[j + 1]);
            }
        }
    }
}

#define printstructure(stream) \
    stream << "em -> id = " << s -> id << endl;\
    stream << "em -> age = " << s -> age << endl;\
    stream << "em -> salary = " << s -> salary << endl;

void printStruct(Employee *s){
    printstructure(cout);
    cout << "Size of structure em = " << sizeof(s) << endl;

    }

void printStruct(Employee *s, const char* str){
    ofstream fout(str);
    printstructure(fout);
    }

}