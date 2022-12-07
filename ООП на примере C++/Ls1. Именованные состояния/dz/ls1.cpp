#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdint>

using namespace std;

// 1. Создать класс Power, который содержит два вещественных числа. Этот класс должен иметь
// две переменные-члена для хранения этих вещественных чисел. Еще создать два метода:
// один с именем set, который позволит присваивать значения переменным, второй — calculate,
// который будет выводить результат возведения первого числа в степень второго числа. Задать
// значения этих двух чисел по умолчанию.


class Power {
private:
    double val = 1.;
    double pwr = 1.;
public:
    void setValue(double vl, double pw) {
        val = vl;
        pwr = pw;
    }
    double calculate() { return pow(val, pwr); }
};

// 2. Написать класс с именем RGBA, который содержит 4 переменные-члена типа std::uint8_t:
// m_red, m_green, m_blue и m_alpha (#include cstdint для доступа к этому типу). Задать 0 в
// качестве значения по умолчанию для m_red, m_green, m_blue и 255 для m_alpha. Создать
// конструктор со списком инициализации членов, который позволит пользователю передавать
// значения для m_red, m_blue, m_green и m_alpha. Написать функцию print(), которая будет
// выводить значения переменных-членов.

class RGBA {
private:
    uint8_t m_red = 0;
    uint8_t m_green = 0;
    uint8_t m_blue = 0;
    uint8_t m_alpha = 255;
public:
    RGBA() {};
    RGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) 
    : m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) {

    }
    void print() {
        cout << "Красный: " << (int)m_red << "\t"
             << "Зеленый: " << (int)m_green << "\t"
             << "Синий: " << (int)m_blue << "\t"
             << "Прозрачность: " << (int)m_alpha
        << endl;
    }
};

//3. Написать класс, который реализует функциональность стека. Класс Stack должен иметь:
// ● private-массив целых чисел длиной 10;
// ● private целочисленное значение для отслеживания длины стека;
// ● public-метод с именем reset(), который будет сбрасывать длину и все значения
// элементов на 0;
// ● public-метод с именем push(), который будет добавлять значение в стек. push()
// должен возвращать значение false, если массив уже заполнен, и true в противном
// случае;
// ● public-метод с именем pop() для вытягивания и возврата значения из стека. Если в
// стеке нет значений, то должно выводиться предупреждение;
// ● public-метод с именем print(), который будет выводить все значения стека.

class Stack {
private:
    const int m_length;
    int *stackArray;
    int head = -1; 
public:
    Stack(int length) : m_length(length) {
        assert(length > 0);
        stackArray = new int[length];
    }
    ~Stack() {
        delete[] stackArray ;
    }
    
    void reset() {
        for (size_t i = 0; i < m_length; stackArray[i++] = 0);
        head = -1;
        }
    
    bool push(int data) {
            if (head < m_length) {
                stackArray[++head] = data;
                return true;
            } else {
                cout << "Stack overflow" << endl;
                return false;
            }
        }
    
    int pop() {
        if (head != -1) {
            return stackArray[head--];
        } else {
            cout << "Stack is empty" << endl;
            return -1;
        }
    }

    void print() {
        cout << "( ";
        for (int i = 0; i <= head; cout << stackArray[i++] << " "); 
        cout << ")" << endl;
    }
};

int main() {

    // № 1
    Power pwr;
    cout << pwr.calculate() << endl;
    pwr.setValue(3.14, 2.7);
    cout << pwr.calculate() << endl << endl << endl;

    // № 2
    RGBA pic1;
    RGBA pic2(100,200,50,125);
    pic1.print();
    pic2.print();
    cout << endl << endl;

    // № 3
    Stack stack(10);
    stack.reset();
    stack.print();
    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();
    stack.pop();
    stack.print();
    stack.pop();
    stack.pop();
    stack.print();
    cout << endl << endl;
    return 0;
}

// ( )
// ( 3 7 5 )
// ( 3 7 )
// ( )