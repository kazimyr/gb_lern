#include <iostream>
using namespace std;
class Animal
{
public:
    Animal(char a[])
    {
        cout << a << endl;
    }
};
class Cat : virtual public Animal
{
public:
    Cat(char a[], char c[]) : Animal(a)
    {
        cout << c << endl;
    }
};
class Mouse : virtual public Animal
{
public:
    Mouse(char a[], char m[]) : Animal(a)
    {
        cout << m << endl;
    }
};
class Cartoon : public Cat, public Mouse
{
public:
    Cartoon(char a[], char c[], char m[]) : Cat(a, c), Mouse(a, m), Animal(a)
    {
    }
};

int main()
{
    Cartoon animal("animal", "cat", "mouse");
}