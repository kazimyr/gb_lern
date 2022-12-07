#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>

using namespace std;



// 1. Создать программу, которая считывает целое число типа int. И поставить «защиту от дурака»:
// если пользователь вводит что-то кроме одного целочисленного значения, нужно вывести
// сообщение об ошибке и предложить ввести число еще раз. Пример неправильных введенных
// строк:
// rbtrb
// nj34njkn
// 1n
int getNumber() {
    int n;
    cout << "Enter an positive integer number: ";
    while (cin >> n, cin.fail() || cin.peek() != '\n') {   // peek - на случай, если строка начинается с цифры
        cout << "Error. Please enter an integer number: "; // например, из строки "123kjhdskj" "123" попадает в переменную
        cin.clear();                                       // "kjhdskj" - остается в буфере без ошибки
        cin.ignore(32767, '\n');
    }
    return n;
}

// 2. Создать собственный манипулятор endll для стандартного потока вывода, который выводит
// два перевода строки и сбрасывает буфер.
ostream &endll(ostream &stream) {
    stream.write("\n\n", 2);
    stream.flush();
    // stream.put('\n');
    // stream << endl;
    return stream;
}

// 3. Реализовать класс Player, который наследует от класса GenericPlayer. У этого класса будет 4
// метода:
// ● virtual bool IsHitting() const - реализация чисто виртуальной функции базового
// класса. Метод спрашивает у пользователя, нужна ли ему еще одна карта и возвращает
// ответ пользователя в виде true или false.
// ● void Win() const - выводит на экран имя игрока и сообщение, что он выиграл.
// ● void Lose() const - выводит на экран имя игрока и сообщение, что он проиграл.
// ● void Push() const - выводит на экран имя игрока и сообщение, что он сыграл вничью.
// 4. Реализовать класс House, который представляет дилера. Этот класс наследует от класса
// GenericPlayer. У него есть 2 метода:
// ● virtual bool IsHitting() const - метод указывает, нужна ли дилеру еще одна карта. Если
// у дилера не больше 16 очков, то он берет еще одну карту.
// ● void FlipFirstCard() - метод переворачивает первую карту дилера.
// 5. Написать перегрузку оператора вывода для класса Card. Если карта перевернута рубашкой
// вверх (мы ее не видим), вывести ХХ, если мы ее видим, вывести масть и номинал карты.
// Также для класса GenericPlayer написать перегрузку оператора вывода, который должен
// отображать имя игрока и его карты, а также общую сумму очков его карт.


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
        friend ostream &operator<<(ostream &stream, const Card& card) {
            const array<string, 13> ranks =  { 
                "Two", 
                "Three",
                "Four",
                "Five",
                "Six",
                "Seven",
                "Eight",
                "Nine",
                "Ten",
                "Jack",
                "Queen",
                "King",
                "Ace"
            };
            const array<string, 4> suits = {
                "Hearts",
                "Diamonds", 
                "Clubs", 
                "Spades"
            };
            if (card.m_IsFaceUp) stream << ranks[card.m_Rank] << " " << suits[card.m_Suit];
            else stream << "XX";
            return stream;
        }
};

class Hand {
    protected:
        vector<Card*> m_Cards;
    public:
        void Add(Card* pCard) {m_Cards.push_back(pCard);}
        void Clear() {
            for(auto itr = m_Cards.begin(); 
                 itr != m_Cards.end(); ++itr) {
                    delete *itr;
                    *itr = NULL;
                }
            m_Cards.clear();
        }
        int GetTotal() const {
            int total = 0;
            bool ace = false;
            int val;
            for(auto itr = m_Cards.cbegin(); 
                itr != m_Cards.cend(); itr++) {
                    val = (*itr)->GetValue();
                    if (val == 1) ace = true;
                    total += val;
            };
            if(ace && total < 12) total += 10;  // Если в руке есть туз, а сумма очков всех карт при этом 
            return total;                       // меньше 12, то считаем, что туз оценивается как 11 очков 
        }
        virtual ~Hand() {Clear();}
};

class GenericPlayer: public Hand {
    protected:
        const string name;
    public:
        GenericPlayer(const string& n = "") : name(n) {};
        virtual ~GenericPlayer();
        virtual bool IsHitting() const = 0;
        bool IsBoosted() {return GetTotal() > 21;}
        void Bust() const {
            cout << "The player " << name << " is bust" << endl;
        }
        friend ostream& operator<<(ostream &stream,const GenericPlayer &aGenericPlayer) {
            stream << aGenericPlayer.name << ":\t";
            vector<Card *>::const_iterator pCard;
            if (!aGenericPlayer.m_Cards.empty()) {
                for (pCard = aGenericPlayer.m_Cards.begin();
                     pCard != aGenericPlayer.m_Cards.end();
                     ++pCard) {
                    stream << *(*pCard) << "\t";
                }
                if (aGenericPlayer.GetTotal() != 0) cout << "(" << aGenericPlayer.GetTotal() << ")";
            }
            else stream << "<empty>";
            return stream;
        }
};

class Player : public GenericPlayer {
    public:
        Player(const string &name = "");
        virtual ~Player();
        virtual bool IsHitting() const {
            cout << name << ", do you want a hit? (Y/N): ";
            char response;
            cin >> response;
            return (response == 'y' || response == 'Y');
        }
        void Win() const {cout << name << " wins.\n";    }
        void Lose() const {cout << name << " loses.\n";}
        void Push() const {cout << name << " pushes.\n";}
};

class House : public GenericPlayer{
    public:
        House(const string& name = "House"){};
        virtual ~House();
        virtual bool IsHitting() const {return (GetTotal() <= 16);}
        void FlipFirstCard() {
            if (!(m_Cards.empty())) m_Cards[0]->Flip();
            else cout << "No card to flip!\n";
        }
};

int main() {
    // cout << "=== № 1 ===" << endl << endl;
    int num = getNumber();
    cout << "Your integer number is: " << num << endl << endl;
    
    // cout << "=== № 2 ===" << endl << endl;
    cout << "Bebin" << endll;
    cout << "End" << endl;

    // cout << "=== № 3 ===" << endl << endl;

    
    // cout << "=== № 4 ===" << endl << endl;

    
    // cout << "=== № 5 ===" << endl << endl;

    return 0;
}

template<typename T>
T GetUserInput(const string& prompt) {
    char n;
    cout << prompt << ": ";
    while (cin >> n, n < '0' || n > '9' || cin.peek() != '\n') {  
        cin.clear();
        cin.ignore(32767, '\n');
        cout << "Некорректный ввод.  Попробуйте снова."; 
    }
    return  (T)(n - '0');
}