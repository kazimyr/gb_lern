#include <iostream>
#include <cmath>
#include <string>

// 1. Написать программу, проверяющую что сумма двух (введенных с клавиатуры) чисел лежит в пределах от 10 до 20 (включительно), 
// если да – вывести строку "true", в противном случае – "false";

// 2. Написать программу, выводящую на экран строку “true”, если две целочисленные константы, объявленные в её начале либо обе равны 
// десяти сами по себе, либо их сумма равна десяти. Иначе "false".

// 3. Написать программу которая выводит на экран список всех нечетных чисел он 1 до 50. Например: "Your numbers: 1 3 5 7 9 11 13 …". 
// Для решения используйте любой С++ цикл.

// 4*.Написать программу, проверяющую, является ли некоторое число - простым. Простое число — это целое положительное число, 
// которое делится без остатка только на единицу и себя само.

// 5*.Пользователь вводит с клавиатуры число (год): от 1 до 3000. Написать программу, которая определяет является ли этот год високосным. 
// Каждый 4-й год является високосным, кроме каждого 100-го, при этом каждый 400-й – високосный. 
// Вывести результаты работы программы в консоль. 

// Замечание: 
// Можно сделать в одном проекте (например разместить разные задания в разных функциях). 
// Или в разных проектах если это кажется удобнее.

void ex1() {
    int a, b, sum;
    std::cout << "Enter two numbers: ";
    std::cin>>a>>b;
    sum = a + b;
    std::cout << a << " + " << b << " = " << sum << std::endl << "Sum between 10 and 20?" << std::endl;
    if (sum < 10 || sum >20) {
        std::cout << "It's false" << std::endl << std::endl;
    }
    else {
        std::cout << "It's true" << std::endl << std::endl;
    }
}

void ex2(){
    const int A = 7;
    const int B = 3;
    std::cout << " A = " << A << " B = " << B << " and SUM =" << A + B << std::endl;
    if (A == 10 && B == 10 || A + B == 10) {
        std::cout << "Condition fulfilled. True" << std::endl << std::endl;
    }
    else {
        std::cout << "Condition not met. False" << std::endl << std::endl;
    }

}

void ex3(){
    const int MX = 50;
    std::cout << " Odd numbers from 1 to " << MX << std::endl;
    for (size_t i = 1; i <= MX; i += 2) {
        std::cout << " " << i;
        if (i % 10 == 9) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl; 
}

void ex4(){
    int num;
    bool flag = true;
    std::cout << "Enter number: "; // << std::endl;
    std::cin >> num;
    const int SQRT = sqrt(num);
    std::cout <<  num << " is  ";
    for (size_t i = 2; i <= SQRT && (flag = num % i); i++);
    // for (size_t i = 2; i <= SQRT; i++) {
    //     if (num % i == 0) {
    //         flag = false;
    //         break;
    //     }
    // }
    if (flag) {
        std::cout << "PRIME" << std::endl << std::endl;
    }
    else {
        std::cout << "NOT PRIME" << std::endl << std::endl;
    }
}

void ex5(){
    int year;
    std::string answer = " is not a leap year";

    std::cout <<  " Enter year: "; 
    std::cin >> year;

    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0 )) {
        answer = " is leap year";
    }
    std::cout << year << answer << std::endl;
}

int main() {
    ex1();
    ex2();
    ex3();
    ex4();
    ex5();
    return 0;
}