#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

//     1. Реализовать шаблон класса Pair1, который позволяет пользователю передавать данные 
//     одного типа парами.
// Следующий код:
// int main()
// {
//     Pair1<int> p1(6, 9);
//     cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

//     const Pair1<double> p2(3.4, 7.8);
//     cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

//     return 0;
// }
// … должен производить результат:
// Pair: 6 9
// Pair: 3.4 7.8

template <class T> class Pair1 {
        const T frst;
        const T scnd;
    public:
        Pair1(const T& f, const T& s): frst(f), scnd(s) {}
        T first() const {return frst;}
        T second() const {return scnd;}
};


//     2. Реализовать класс Pair, который позволяет использовать разные типы данных 
//     в передаваемых парах.
// Следующий код:
// int main()
// {
//     Pair<int, double> p1(6, 7.8);
//     cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

//     const Pair<double, int> p2(3.4, 5);
//     cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

//     return 0;
// }

// … должен производить следующий результат:
// Pair: 6 7.8
// Pair: 3.4 5
// Подсказка: чтобы определить шаблон с использованием двух разных типов, 
// просто разделите параметры типа шаблона запятой.

template <class T1, class T2> class Pair {
    protected:
        const T1 frst;
        const T2 scnd;
    public:
        Pair(const T1& f, const T2& s): frst(f), scnd(s) {}
        T1 first() const {return frst;}
        T2 second() const {return scnd;}
};

//     3. Написать шаблон класса StringValuePair, в котором первое значение всегда типа string, 
//     а второе — любого типа. Этот шаблон класса должен наследовать частично специализированный 
//     класс Pair, в котором первый параметр — string, а второй — любого типа данных.

// Следующий код:
// int main()
// {
//     StringValuePair<int> svp("Amazing", 7);
//     std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
//     return 0;
// }

// … должен производить следующий результат:
// Pair: Amazing 7
// Подсказка: при вызове конструктора класса Pair из конструктора класса StringValuePair 
// не забудьте указать, что параметры относятся к классу Pair.

template <class T> 
class Pair<string,T> {
    protected:
        const string frst;
        const T scnd;
    public:
       Pair(const string& f, const T& s): frst(f), scnd(s){} 
};

template <class T> 
class StringValuePair: public Pair<string, T> {
        // const string frst;
        // const T scnd;
    public:
        StringValuePair(const string& f, const T& s): Pair<string, T>(f, s) {}
        const string first() const {return Pair<string, T>::frst;}
        const T second() const {return Pair<string, T>::scnd;}
};



//     4. Согласно иерархии классов, которая представлена в методичке к уроку 3, от класса Hand 
//     наследует класс GenericPlayer, который обобщенно представляет игрока, ведь у нас будет 
//     два типа игроков - человек и компьютер. Создать класс GenericPlayer, в который добавить 
//     поле name - имя игрока. Также добавить 3 метода:
//     • IsHitting() - чисто виртуальная функция, возвращает информацию, нужна ли игроку еще 
//     одна карта.
//     • IsBoosted() - возвращает bool значение, есть ли у игрока перебор
//     • Bust() - выводит на экран имя игрока и объявляет, что у него перебор.

enum Suit { 
    Hearts,
    Diamonds, 
    Clubs, 
    Spades
};
enum Rank { 
    Two, 
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
};
class Card {
    private:
        Suit const m_Suit;
        Rank const m_Rank;
        bool m_IsFaceUp;
    public:
        Card(Suit s, Rank r): m_Suit(s), m_Rank(r), m_IsFaceUp(false) {}
        void Flip() { m_IsFaceUp = !m_IsFaceUp; }
        int GetValue() const {
            return (int[13]){2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 1}[m_Rank];
        }
        // int GetRank() const { return m_Rank; }
        // int GetSuite() const { return m_Suit; }
};

class Hand {
    protected:
        vector<Card*> m_Cards;
    public:
        void Add(Card* pCard) {m_Cards.push_back(pCard);}
        void Clear() {
            for(vector<Card*>::iterator itr = m_Cards.begin(); 
                 itr != m_Cards.end(); ++itr) {
                    delete *itr;
                    *itr = NULL;
                }
            m_Cards.clear();
        }
        int GetTotal() {
            int total = 0;
            bool ace = false;
            int val;
            for(vector<Card*>::const_iterator itr = m_Cards.cbegin(); 
                itr != m_Cards.cend(); itr++) {
                    val = (*itr)->GetValue();
                    if (val == 1) ace = true;
                    total += val;
            };
            if(ace && total < 12) return total += 10;
            return total;
        }
        virtual ~Hand() {Clear();}
};

class GenericPlayer: public Hand {
    protected:
        const string name;
    public:
        GenericPlayer(const string& n = "") : name(n) {}
        // virtual ~GenericPlayer();
        virtual bool IsHitting() = 0;
        bool IsBoosted() {return GetTotal() > 21;}
        void Bust() {
            cout << "The player " << name << " is bust" << endl;
        }
};


int main()
{
    cout << "=== № 1 ===" << endl << endl;
    {
        Pair1<int> p1(6, 9);
        cout << "Pair: " << p1.first() << ' ' << p1.second() << endl;

        const Pair1<double> p2(3.4, 7.8);
        cout << "Pair: " << p2.first() << ' ' << p2.second() << endl << endl;
    }


    cout << "=== № 2 ===" << endl << endl;

    {
        Pair<int, double> p1(6, 7.8);
        cout << "Pair: " << p1.first() << ' ' << p1.second() << endl;

        const Pair<double, int> p2(3.4, 5);
        cout << "Pair: " << p2.first() << ' ' << p2.second() << endl<< endl;
    }


    cout << "=== № 3 ===" << endl << endl;

    StringValuePair<int> svp("Amazing", 7);
    cout << "Pair: " << svp.first() << ' ' << svp.second() << endl << endl;

    cout << "=== № 3 ===" << endl << endl;

    // GenericPlayer p("Вася");
    // p.Add(new Card(Diamonds, Two));
    // p.Add(new Card(Hearts, Ace));
    // p.Add(new Card(Clubs, Four));
    // cout << p.GetTotal() << endl;
    // p.Add(new Card(Spades, Ace));
    // cout << p.GetTotal() << endl;
    // p.Add(new Card(Hearts, King));
    // p.Add(new Card(Clubs, Ten));
    // if (p.IsBoosted()) p.Bust();
    // cout << p.GetTotal() << endl << endl;
    
    cout << "=== The End ===" << endl << endl;


    return 0;
}