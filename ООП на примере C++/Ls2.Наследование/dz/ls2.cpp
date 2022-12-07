#include <iostream>
using namespace std;

// 1. Создать класс Person (человек) с полями: имя, возраст, пол и вес. 
// Определить методы переназначения имени, изменения возраста и веса. 
// Создать производный класс Student (студент), имеющий поле года обучения. 
// Определить методы переназначения и увеличения этого значения. 
// Создать счетчик количества созданных студентов. В функции main() создать
// несколько студентов. По запросу вывести определенного человека.

class Person {
        const char* name;
        u_short age;
        u_short weight;
    public:
        Person(const char* nm, u_short ag, u_short wght) 
            : name(nm), age(ag), weight(wght){}
        void setName(const char* nm){name = nm;}
        void setAge(u_short ag){age = ag;}
        void setWeight(u_short wght){weight = wght;}
        const char* getName(){return name;}
        u_short getAge(){return age;}
        u_short getWeight(){return weight;}        
};

class Student : public Person {
        u_short yearStudy;
    public:
        Student(const char* nm, u_short ag, u_short wght, u_short year = 1) 
            : yearStudy(year), Person(nm, ag, wght){}
        void setYear(u_short year){yearStudy = year;}
        void icrYear(){++yearStudy;}
        u_short getYear(){return yearStudy;}
};

u_short counter(Student **students){
    u_short cntr = 0;
    for ( ;students[cntr]; cntr++ );
    return cntr;
}

void print(const char* student, Student** students){
    for ( size_t i = 0; students[i]; i++ ) {
        if ( students[i]->getName() == student) {
            cout << "Найден: " << students[i]->getName() << endl
                << "Возраст: " << students[i]->getAge() << endl
                << "Вес: " << students[i]->getWeight() << endl
                << "Год обучения: " << students[i]->getYear() << endl << endl;
                return;
        }
    }
    cout << student << " в списках не числится" << endl << endl;
}

// 2. Создать классы Apple (яблоко) и Banana (банан), которые наследуют класс Fruit 
// (фрукт). У Fruit есть две переменные-члена: name (имя) и color (цвет). 
// Добавить новый класс GrannySmith, который наследует класс Apple.

class Fruit {
        const char* color;
        const char* name;
    public:
        Fruit(const char* clr, const char* nm) : color(clr), name(nm) {}
        const char* getName() { return name; }
        const char* getColor() { return color; }
};

class Apple: public Fruit {
    public:
        Apple(const char* color, const char* name = "apple") : Fruit(color, name) {}
};

class Banana: public Fruit {
    public:
        Banana() : Fruit("yellow", "banana") {}
};

class GrannySmith: public Apple {
    public:
        GrannySmith() : Apple("green", "Granny Smith apple") {}
};

// 3. Изучить правила игры в Blackjack. Подумать, как написать данную игру на С++, 
// используя объектно-ориентированное программирование. Сколько будет классов 
// в программе? Какие классы будут базовыми, а какие производными? 
// Продумать реализацию игры с помощью классов и записать результаты.

class Card {};
class Chip {};
class DeckOfCard: public Card {};
class Hand: public Card {};
class Shoe: public DeckOfCard{};
class Player: public Hand, public Chip{};
class Dealer: public Player{};


int main() {
    // № 1
    Student* students[10] = {0};
    students[0] = new Student("Иванов", 18, 70 , 1);
    students[1] = new Student("Петров", 19, 76 , 2);
    cout << "Числится " << counter(students) << " студентов" << endl;
    students[2] = new Student("Баширов", 20, 80 , 2);
    students[3] = new Student("Сидоров", 17, 100 , 1);
    students[4] = new Student("Иванько", 25, 86 , 3);
    cout << "Числится " << counter(students) << " студентов" << endl << endl;
    print("Петров", students);
    print("Баширов", students);
    print("Стефанчук", students);

    // № 2
    Apple a("red");
    Banana b;
    GrannySmith c;
    cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    cout << "My " << c.getName() << " is " << c.getColor() << ".\n";



    return 0;
}
// Код, приведенный выше, должен давать следующий результат:
// My apple is red.
// My banana is yellow.
// My Granny Smith apple is green.
