#include <iostream>
#include <cstdlib>
using namespace std;

// 1. Создать абстрактный класс Figure (фигура). Его наследниками являются классы Parallelogram 
// (параллелограмм) и Circle (круг). Класс Parallelogram — базовый для классов Rectangle 
// (прямоугольник), Square (квадрат), Rhombus (ромб). Для всех классов создать конструкторы. 
// Для класса Figure добавить чисто виртуальную функцию area() (площадь). Во всех остальных классах 
// переопределить эту функцию, исходя из геометрических формул нахождения площади.

class Figure {
    protected:
        double x, y;
    public:
        Figure(double i, double j = 0): x(i), y(j) {}
        virtual void area() = 0; 
};

class Circle : public Figure {
  public:
        Circle(double i): Figure(i) {}
        void area() {
            cout << "Circle with radius ";
            cout << x;
            cout << " has an area of ";
            cout << 3.14 * x * x << ".\n";
        }
};

class Parallelogram : public Figure {
    public:
        Parallelogram(double i, double j = 0): Figure(i, j) {}
        void area() {
            cout << "Parallelogram with height ";
            cout << x << " and base " << y;
            cout << " has an area of ";
            cout << x * y << ".\n";
        }
};

class Rhombus : public Parallelogram {
    public:
        Rhombus(double i, double j): Parallelogram(i, j) {}
        void area() {
            cout << "Rhombus with diagonals ";
            cout << x << "x" << y;
            cout << " has an area of ";
            cout << x * y << ".\n";
        }
};

class Rectangle : public Parallelogram {
    public:
        Rectangle(double i, double j): Parallelogram(i, j) {}
        void area() {
            cout << "Rectangle with dimensions ";
            cout << x << "x" << y;
            cout << " has an area of ";
            cout << x * y << ".\n";
        }
};

class Square : public Parallelogram {
    public:
        Square(double i): Parallelogram(i) {}
        void area() {
            cout << "Square with dimension ";
            cout << x;
            cout << " has an area of ";
            cout << x * x << ".\n";
        }
};



// 2. Создать класс Car (автомобиль) с полями company (компания) и model (модель). 
// Классы-наследники: PassengerCar (легковой автомобиль) и Bus (автобус). От этих классов наследует 
// класс Minivan (минивэн). Создать конструкторы для каждого из классов, чтобы они выводили данные 
// о классах. Создать объекты для каждого из классов и посмотреть, в какой последовательности 
// выполняются конструкторы. Обратить внимание на проблему «алмаз смерти». 
// Примечание: если использовать виртуальный базовый класс, то объект самого "верхнего" 
// базового класса создает самый "дочерний" класс.

class Car {
    protected:
        string company;
        string model;
    public:
        Car(const string &c = "", const string &m = ""): company(c), model(m) {
            cout << "Class Car" << endl
            << "Company: " << company << endl
            << "Model: " << model << endl << endl;
        }
};

class PassengerCar: virtual public Car {
    public:
        PassengerCar(const string &c = "", const string &m = ""): Car(c, m) {
            cout << "Class PassengerCar"<< endl
            << "Company: " << company << endl
            << "Model: " << model << endl << endl;
        }
};

class Bus: virtual public Car {
    public:
        Bus(const string &c = "", const string &m = ""): Car(c, m) {
            cout << "Class Bus: " << endl
            << "Company: " << company << endl
            << "Model: " << model << endl << endl;
        }
};

class Minivan: public PassengerCar, public Bus {
    public:
        Minivan(const string &c, const string &m): Car(c, m) {
            cout << "Class Minivan: " << endl
            << "Company: " << company << endl
            << "Model: " << model << endl << endl
            << "Ужас, какой расход памяти!!!" << endl << ":-(" << endl;
        }
};

// 3. Создать класс: Fraction (дробь). Дробь имеет числитель и знаменатель (например, 3/7 или 9/2). 
// Предусмотреть, чтобы знаменатель не был равен 0. Перегрузить:
// • математические бинарные операторы (+, -, *, /) для выполнения действий с дробями
// • унарный оператор (-)
// • логические операторы сравнения двух дробей (==, !=, <, >, <=, >=). 
// Примечание: Поскольку операторы < и >=, > и <= — это логические противоположности, попробуйте 
// перегрузить один через другой.
// Продемонстрировать использование перегруженных операторов.

class Fraction {
        int numerator = 0;
        int denominator = 1;
        int gcd(int a, int b) {
            for(int t; t = a % b; a = b, b = t);
            return b;
        }
    public:
        Fraction() {}
        Fraction(int n, int d) {
            if(!d) {
                cout << "Denominator mast be not 0" << endl;
                exit(EXIT_FAILURE);
            } else if (d < 0) {
                d = -d;
                n = -n;
            }
            int x = gcd(n, d);
            if(x > 1) {
                n /= x;
                d /= x;
            };
            
            numerator = n; 
            denominator = d;
        }
        string showF() {return to_string(numerator) + "/" + to_string(denominator);}

        Fraction operator + (Fraction f) {
            return Fraction(numerator * f.denominator + f.numerator * denominator,
                            denominator * f.denominator);
        }
        
        Fraction operator - (Fraction f) {
            return Fraction(numerator * f.denominator - f.numerator * denominator,
                            denominator * f.denominator);
        }

        Fraction operator * (Fraction f) {
            return Fraction(numerator * f.numerator,
                            denominator * f.denominator);
        }

        Fraction operator / (Fraction f) {
            return Fraction(numerator * f.denominator,
                            denominator * f.numerator);
        }

        Fraction operator - () {
            return Fraction(- numerator, denominator);
        }

        bool operator == (Fraction f) {
            return numerator == f.numerator && denominator == f.denominator;
        }

        bool operator != (Fraction f) {
            return numerator != f.numerator || denominator != f.denominator;
        }

        bool operator > (Fraction f) {
            return (numerator * f.denominator - f.numerator * denominator > 0);
        }

        bool operator < (Fraction f) {
            return (numerator * f.denominator - f.numerator * denominator < 0);
        }

        bool operator <= (Fraction f) {
            return !(*this > f);
        }

        bool operator >= (Fraction f) {
            return !(*this < f);
        }
};

// 4. Создать класс Card, описывающий карту в игре БлэкДжек. У этого класса должно быть три поля: 
// масть, значение карты и положение карты (вверх лицом или рубашкой). Сделать поля масть и значение 
// карты типом перечисления (enum). Положение карты - тип bool. Также в этом классе должно быть два 
// метода: 
// • метод Flip(), который переворачивает карту, т.е. если она была рубашкой вверх, то он ее 
// поворачивает лицом вверх, и наоборот.
// • метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.


class Card {
    protected:
        enum Suit { Hearts,
            Diamonds, 
            Clubs, 
            Spades
        } const suit;
        enum Rank { Two, 
                    Three,
                    Four,
                    Five,
                    Six,
                    Seven,
                    Eight,
                    Nine,
                    Ten,
                    Jack,
                    Queen,
                    King,
                    Ace
            } const rank;
        bool position = false;
    public:
    void Flip() { position = !position; }
    int GetValue() const {
        // int value[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 1};
        return (int[13]){2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 1}[rank];
    }
};

int main() {
    // № 1

    Figure *p; 

    Parallelogram prlgrm(20, 10); 
    Circle c(10);
    Rhombus rmb(15, 13);
    Rectangle rctngl(25, 15);
    Square s(20);

    p = &prlgrm;
    p->area();

    p = &c;
    p->area();

    p = &rmb;
    p->area();

    p = &rctngl;
    p->area();

    p = &s;
    p->area();
    
    cout << endl;

    // № 2
    Car car1(); 
    Car car2("NoName", "NoName");
    PassengerCar pcar("Reault","Logan");
    Bus bus("Mercedes-Benz", "Conecto");
    Minivan minivan("Lada", "Largus");
    cout << endl;

    // № 3
    Fraction f1(25, -30);
    Fraction f2(12, 16);
    Fraction f3 = f1;
    cout << "f1 = " << f1.showF() << endl;
    cout << "f2 = " << f2.showF() << endl;
    cout << "f3 = " << f3.showF() << endl;
    cout << f1.showF() << " + " << f2.showF() << " = " << (f1 + f2).showF() << endl;
    cout << f1.showF() << " - " << f2.showF() << " = " << (f1 - f2).showF() << endl;
    cout << f1.showF() << " * " << f2.showF() << " = " << (f1 * f2).showF() << endl;
    cout << f1.showF() << " / " << f2.showF() << " = " << (f1 / f2).showF() << endl;
    cout << "negative(" << f1.showF() << ") = " << (- f1).showF() << endl;
    cout << f1.showF() << " = " << f2.showF() << " it is " << (f1 == f2? "True" : "False") << endl;
    cout << f1.showF() << " = " << f3.showF() << " it is " << (f1 == f3? "True" : "False") << endl;
    cout << f1.showF() << " != " << f2.showF() << " it is " << (f1 != f2? "True" : "False") << endl;
    cout << f1.showF() << " != " << f3.showF() << " it is " << (f1 != f3? "True" : "False") << endl;
    cout << f1.showF() << " > " << f2.showF() << " it is " << (f1 > f2? "True" : "False") << endl;
    cout << f1.showF() << " > " << f3.showF() << " it is " << (f1 > f3? "True" : "False") << endl;
    cout << f1.showF() << " < " << f2.showF() << " it is " << (f1 < f2? "True" : "False") << endl;
    cout << f1.showF() << " < " << f3.showF() << " it is " << (f1 < f3? "True" : "False") << endl;
    cout << f1.showF() << " <= " << f2.showF() << " it is " << (f1 <= f2? "True" : "False") << endl;
    cout << f1.showF() << " <= " << f3.showF() << " it is " << (f1 <= f3? "True" : "False") << endl;
    cout << f1.showF() << " >= " << f2.showF() << " it is " << (f1 >= f2? "True" : "False") << endl;
    cout << f1.showF() << " >= " << f3.showF() << " it is " << (f1 >= f3? "True" : "False") << endl;


    return 0;
}