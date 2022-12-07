#include <iostream>
#include <iomanip>

using namespace std;

    // 1. Написать шаблонную функцию div, которая должна вычислять результат деления двух параметров и запускать исключение DivisionByZero, 
    // если второй параметр равен 0. В функции main выводить результат вызова функции div в консоль, а также ловить исключения. 

template<typename T> 
T diV(const T &numerator, const T &denominator){
    if (!denominator) throw runtime_error("DivisionByZero");
    return numerator / denominator;
}


    // 2. Написать класс Ex, хранящий вещественное число x и имеющий конструктор по вещественному числу, инициализирующий x значением параметра. 
    // Написать класс Bar, хранящий вещественное число y (конструктор по умолчанию инициализирует его нулем) и имеющий метод set с единственным 
    // вещественным параметром a. Если y + a > 100, возбуждается исключение типа Ex с данными a*y, иначе в y заносится значение a. 
    // В функции main завести переменную класса Bar и в цикле в блоке try вводить с клавиатуры целое n. Использовать его в качестве параметра 
    // метода set до тех пор, пока не будет введено 0. В обработчике исключения выводить сообщение об ошибке, содержащее данные объекта 
    // исключения.

class Ex{
        double x;
    public:
        Ex(double param): x(param) {}
        double getValue(){ return x;}
};

class Bar{
        double y;
    public:
        Bar():y(0.) {}
        void set(double const &a) { 
            if(y + a > 100) throw Ex(a * y);
            y = a;
        }
};

int getNumber() {
    int n;
    // cout << "Enter an integer number: ";
    while (cin >> n, cin.fail() || cin.peek() != '\n') {   // peek - на случай, если строка начинается с цифры
        cout << "Error. Please enter an integer number: "; // например, из строки "123kjhdskj" "123" попадает в переменную
        cin.clear();                                       // "kjhdskj" - остается в буфере без ошибки
        cin.ignore(32767, '\n');
    }
    return n;
}

    // 3. Написать класс «робот», моделирующий перемещения робота по сетке 10x10, у которого есть метод, означающий задание переместиться 
    // на соседнюю позицию. Эти методы должны запускать классы-исключения OffTheField, если робот должен уйти с сетки, и IllegalCommand, 
    // если подана неверная команда (направление не находится в нужном диапазоне). Объект исключения должен содержать всю необходимую 
    // информацию — текущую позицию и направление движения. Написать функцию main, пользующуюся этим классом и перехватывающую все исключения 
    // от его методов, а также выводящую подробную информацию о всех возникающих ошибках.

class OffTheField {
        int pointX, pointY, offsetX, offsetY;
    public:
        OffTheField(int &x, int &y, int ox, int oy): pointX(x), pointY(y), offsetX(ox), offsetY(oy) {}
    friend ostream& operator<<(ostream &stream, const OffTheField &otf) {
        stream << "Error. Trying to go outside the field." << endl 
            << "Robot coordinates: (" << otf.pointX << ", " << otf.pointY << ")" << endl
            << "Trying to go to: (" << otf.pointX + otf.offsetX << ", " << otf.pointY + otf.offsetY << ")" << endl;
        return stream;
    }
};

class IllegalCommand {
        int pointX, pointY, offsetX, offsetY;
    public:
        IllegalCommand(int &x, int &y, int ox, int oy): pointX(x), pointY(y), offsetX(ox), offsetY(oy) {}
    friend ostream& operator<<(ostream &stream, const IllegalCommand &otf) {
        stream << "Error. Wrong command issued." << endl 
            << "Robot coordinates: (" << otf.pointX << ", " << otf.pointY << ")" << endl
            << "Trying to go to: (" << otf.pointX + otf.offsetX << ", " << otf.pointY + otf.offsetY << ")" << endl;
        return stream;
    }
};

class Robot {
        int pointX, pointY;
        const int sizeOfField;
    public:
        Robot(int &x, int &y, int sz): pointX(x), pointY(y), sizeOfField(sz) {}
        void goTo(int const offsetX, int const offsetY) {
            if(abs(offsetX) > 1 || abs(offsetY) > 1) throw IllegalCommand(pointX, pointY, offsetX, offsetY);
            int nx = pointX + offsetX;
            int ny = pointY + offsetY;
            if( nx< 1 || nx > sizeOfField || ny < 1 || ny > sizeOfField) throw OffTheField(pointX, pointY, offsetX, offsetY);
            pointX = nx;
            pointY = ny;
        }
        friend ostream& operator<<(ostream &stream, const Robot &coordinates) {
            stream << "Robot coordinates: (" << coordinates.pointX << ", " << coordinates.pointY << ")" << endl;
            return stream;
        }
};

int main() {
    try {
    cout << endl << "=== № 1 ===" << endl;
        cout << diV(17., 5.) << endl;
        cout << diV(12, 3) << endl;
        // cout << diV(17., 0.) << endl;

    cout << endl << "=== № 2 ===" << endl;
        Bar param;
        while (int n = getNumber()) param.set(static_cast<double>(n));
        
    cout << endl << "=== № 3 ===" << endl;
        cout << "Enter size of field: ";
        int sz = getNumber();
        int x, y;    
        cout << "Initial position of the robot" << endl
        << "Enter two integer coordinates from 1 to " << sz << ", separated by a space: ";
        while (cin >> x, cin >> y, cin.fail() || x < 1 || x > sz || y < 1 || y > sz ) {
            cout << "Error. Enter two integer coordinates from 1 to " << sz << ", separated by a space: ";
            cin.clear();
            cin.ignore(32767, '\n');
        }

        Robot r1(x, y, sz);

        cout << "Enter two integer offsets from the current position, separated by a space: ";
        while (cin >> x, cin >> y, cin.fail()) {
            cout << "Error. Enter two integer offsets from the current position, separated by a space: ";
            cin.clear();
            cin.ignore(32767, '\n');
        }

        r1.goTo(x, y);
        cout << r1 << endl;
    }
    
    catch(runtime_error &e) {
        cout << e.what() << endl;
    }
    catch(Ex &e){
        cout << "Error: " << e.getValue() << endl;
    }
    catch(IllegalCommand &e) {
        cout << e << endl;
    }
    catch(OffTheField &e) {
        cout << e << endl;
    }

    return 0;
}