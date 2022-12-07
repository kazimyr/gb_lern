#include <iostream>
#include <iomanip>
#include <chrono>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

// 1. Создайте класс Date с полями день, месяц, год и методами доступа к этим полям. Перегрузите оператор вывода для данного класса. 
// Создайте два "умных" указателя today и date. Первому присвойте значение сегодняшней даты. Для него вызовите по отдельности методы 
// доступа к полям класса Date, а также выведите на экран данные всего объекта с помощью перегруженного оператора вывода. 
// Затем переместите ресурс, которым владеет указатель today в указатель date. Проверьте, являются ли нулевыми указатели today и date 
// и выведите соответствующую информацию об этом в консоль.

template<class T>
class A_ptr {
        T* m_ptr;
    public:
        A_ptr(T* ptr = nullptr): m_ptr(ptr) {}
        ~A_ptr() {delete m_ptr;}
        A_ptr(A_ptr& x): m_ptr(x.m_ptr) { // Конструктор с копированием
            m_ptr = new T;
            *m_ptr = *x.m_ptr;
        } 
        A_ptr(A_ptr&& x): m_ptr(x.m_ptr) {x.m_ptr = nullptr;} // Конструктор с перемещением

        A_ptr& operator=(A_ptr &x) {  // Оператор присваивания копированием
            if (&x == this)
                return *this;
            delete m_ptr;
            m_ptr = new T;
            *m_ptr = *x.m_ptr;
            return *this;
        }
        A_ptr& operator^=(A_ptr& x) { // Оператор присваивания с перемещением
            if (&x == this)
                return *this;
            delete m_ptr; 
            m_ptr = x.m_ptr;
            x.m_ptr = nullptr;
            return *this;
        }
        A_ptr& operator=(A_ptr&& x) { // Оператор присваивания с перемещением для r-value
            if (&x == this)
                return *this;
            delete m_ptr; 
            m_ptr = x.m_ptr;
            x.m_ptr = nullptr;
            return *this;
        }
        T& operator*() const { return *m_ptr; }
        T* operator->() const { return m_ptr; }
        bool isNull() const { return m_ptr == nullptr; }
};

class Date {
        unsigned int day, month;
        int year;
    public:
        static string today() {
            time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
            stringstream s; 
            s << put_time(localtime(&now), "%F");
        return s.str();
        }
               
        Date(string s = today()) {
            unsigned int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            try {
                for(int i = 0; i < s.length(); i++) {
                    if(!isdigit(s[i]) && s[i] != '/' && s[i] != '.' && s[i] != '-') throw invalid_argument("");
                }
                size_t first, second;
                if((first = s.find_first_of("/-.")) == string::npos) throw runtime_error("year");
                char token = s[first];
                year = stoi(s.substr(0,first));
                if((second = s.find(token, first + 1)) == string::npos) throw runtime_error("month");                
                month = stoul(s.substr(first + 1,second - first - 1));
                if (month < 1 || month > 12) throw 0;
                day = stoul(s.substr(second + 1));
                if(month == 2 && day == 29 && (year % 4 != 0 || year % 100 == 0 && year % 400 != 0 )) throw 1;
                else if((day < 1 || day > months[month - 1]) && (month != 2 || day != 29)) throw 1;
            }
            catch(runtime_error &e) {
                cout << "Wrong " << e.what() << " in date" << endl;
                cout << "Wrong date format.\nShould be\n\"YYYY.MM.DD\"\nor\n\"YYYY/MM/DD\"\nor\n\"+YYYY-MM-DD\"" << endl;
                exit(1);
            }
            catch(invalid_argument &e) {
                cout << "Wrong date format.\nShould be\n\"YYYY.MM.DD\"\nor\n\"YYYY/MM/DD\"\nor\n\"+YYYY-MM-DD\"" << endl;
                exit(1);
            }
            catch(int const &e) {
                switch(e) {
                    case 0: cout << "The month can be from 1 to 12" << endl; break;
                    case 1: cout << "In  " << year << ", the " << month << "th month is missing the " << day << "th day" << endl;
                }
                exit(1);
            }
        }

        Date(int y, unsigned int m, unsigned int d): Date(to_string(y) + "/" + to_string(m) + "/" + to_string(d)) {}

        unsigned int getDay() { return day; }
        unsigned int getMonth() { return month; }
        int getYear() { return year; }
        
        friend ostream& operator<<(ostream &stream, const Date &date) {
            stream << date.year << "." << date.month << "." << date.day;
            return stream;
        }
};

// 2. По условию предыдущей задачи создайте два умных указателя date1 и date2. 
//     • Создайте функцию, которая принимает в качестве параметра два умных указателя типа Date и сравнивает их между собой (сравнение 
//     происходит по датам). Функция должна вернуть более позднюю дату.
//     • Создайте функцию, которая обменивает ресурсами (датами) два умных указателя, переданных в функцию в качестве параметров.
// Примечание: обратите внимание, что первая функция не должна уничтожать объекты, переданные ей в качестве параметров.

A_ptr<Date> compareDate(A_ptr<Date> &p1, A_ptr<Date> &p2) {
	try {
        if(p1.isNull() || p2.isNull()) throw 0;
        if(p1->getYear() > p2->getYear()) return p1;
        else if(p1->getYear() < p2->getYear()) return p2;
        else if(p1->getMonth() > p2->getMonth()) return p1;
        else if(p1->getMonth() < p2->getMonth()) return p2;
        else if(p1->getDay() > p2->getDay()) return p1;
        else if(p1->getDay() < p2->getDay()) return p2;
        else throw 1;
    }
    catch(int const &e) {
        switch(e) {
            case 0: cout << "Can't compare date not specified" << endl; break;
            case 1: cout << "Two dates are the same: cannot be compared" << endl;
        }
        exit(1);
    }
}

void swap(A_ptr<Date> &p1, A_ptr<Date> &p2) {
    A_ptr<Date> pTmp;
    pTmp = p1;
    p1 = p2;
    p2 = pTmp;
}

// 3. Создать класс Deck, который наследует от класса Hand и представляет собой колоду карт. Класс Deck имеет 4 метода:
//     • vold Populate() - Создает стандартную колоду из 52 карт, вызывается из конструктора.
//     • void Shuffle() - Метод, который тасует карты, можно использовать функцию из алгоритмов STL random_shuffle
//     • vold Deal (Hand& aHand) - метод, который раздает в руку одну карту
//     • void AdditionalCards (GenericPlayer& aGenerlcPlayer) - раздает игроку дополнительные карты до тех пор, пока он может и хочет их 
//     получать
// Обратите внимание на применение полиморфизма. В каких методах применяется этот принцип ООП?

// 4. Реализовать класс Game, который представляет собой основной процесс игры. У этого класса будет 3 поля:
//     • колода карт
//     • рука дилера
//     • вектор игроков.
// Конструктор класса принимает в качестве параметра вектор имен игроков и создает объекты самих игроков. В конструкторе создается колода 
// карт и затем перемешивается. 
// Также класс имеет один метод play(). В этом методе раздаются каждому игроку по две стартовые карты, а первая карта дилера прячется. 
// Далее выводится на экран информация о картах каждого игрока, в т.ч. и для дилера. Затем раздаются игрокам дополнительные карты. 
// Потом показывается первая карта дилера и дилер набирает карты, если ему надо. После этого выводится сообщение, кто победил, а кто проиграл. 
// В конце руки всех игроков очищаются.

// 5. Написать функцию main() к игре Блекджек. В этой функции вводятся имена игроков. Создается объект класса Game и запускается игровой процесс. 
// Предусмотреть возможность повторной игры.
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
        // 11 - макс. кол-во карт с возможной суммой очков 21: 4 туза, 4 двойки, 3 тройки
        Hand() {m_Cards.reserve(11);} 
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
        string mName;
    public:
        GenericPlayer(const string &n) : mName(n) {}
        virtual ~GenericPlayer(){}
        virtual bool IsHitting() const = 0;
        bool IsBusted() {return GetTotal() > 21;}
        void Bust() const {
            cout << "The player " << mName << " is bust" << endl;
        }
        friend ostream& operator<<(ostream &stream,const GenericPlayer &aGenericPlayer) {
            stream << aGenericPlayer.mName << ":\t";
            // vector<Card *>::const_iterator pCard;
            if (!aGenericPlayer.m_Cards.empty()) {
                for (auto pCard = aGenericPlayer.m_Cards.begin();
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
        Player(const string &n = "NoName") : GenericPlayer(n) {}
        virtual ~Player() {}
        virtual bool IsHitting() const {
            cout << mName << ", do you want a hit? (Y/N): ";
            char response;
            cin >> response;
            if(cin.peek() != '\n') cin.ignore(); // если введен символ длинной более 1-го байта, например русский символ
            return (response == 'y' || response == 'Y');
        }
        void FlipAllCards() const {
            if (!m_Cards.empty()) {
                for (auto pCard = m_Cards.begin();
                     pCard != m_Cards.end();
                     ++pCard) {
                    (*pCard)->Flip();
                }
            cout << *this << endl;            
            }
        }
        void Win() const {
            cout << "Winning! ";
            FlipAllCards();
        }
        void Lose() const {
            cout << "Losing... ";
            FlipAllCards();
        }
        void Push() const {
            cout << "Draw. ";
            FlipAllCards();
        }
};

class House : public GenericPlayer{
    public:
        House() : GenericPlayer("HOUSE") {}
        virtual ~House() {}
        virtual bool IsHitting() const {return (GetTotal() <= 16);}
        void FlipFirstCard() {
            if (!(m_Cards.empty())) m_Cards[0]->Flip();
            else cout << "No card to flip!\n";
        }
        // Переворачивает остальные карты
        void FlipOtherCards() {
            if (!m_Cards.empty()) {
                for (auto pCard = m_Cards.begin() + 1;
                     pCard != m_Cards.end();
                     ++pCard) {
                    (*pCard)->Flip();
                }
            cout << *this << endl;    
            }            
        }
};

class Deck : public Hand {
    public:
        Deck() {
            m_Cards.reserve(52);
            Populate();
        }
        virtual ~Deck() {}
        void Populate() {
            Clear();
            for (int s = Hearts; s <= Spades; ++s)
                for (int r = Two; r <= Ace; ++r)
                    Add(new Card(static_cast<Suit>(s), static_cast<Rank>(r)));
        }
        void Shuffle() {random_shuffle(m_Cards.begin(), m_Cards.end());}
        void Deal(Hand& aHand) {
            if (!m_Cards.empty()) {
                aHand.Add(m_Cards.back());
                m_Cards.pop_back();
            }
            else cout << "Out of cards. Unable to deal.";
        }
        void AdditionalCards(GenericPlayer& aGenericPlayer) {
            cout << endl;
            while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting()) {
                Deal(aGenericPlayer);
                cout << aGenericPlayer << endl;
                
                if (aGenericPlayer.IsBusted()) aGenericPlayer.Bust();
            }
        }
};

class Game {
        Deck m_Deck;
        House m_House;
        vector<Player> m_Players;    
    public:
        Game(const vector<string>& names) {
            for (auto pName = names.begin(); pName != names.end(); ++pName)
                m_Players.push_back(Player(*pName));
            srand(static_cast<unsigned int>(time(0)));
            m_Deck.Populate();
            m_Deck.Shuffle();
        }
        ~Game() {}
        void Play() {
            // раздает каждому по две стартовые карты
            vector<Player>::iterator pPlayer;
            for (int i = 0; i < 2; ++i) {
                for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
                    m_Deck.Deal(*pPlayer);
                m_Deck.Deal(m_House);
            }
            // открывает руки всех игроков
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
                cout << *pPlayer << endl;
            // cout << m_House << endl;

            // показывает первую карту дилера
            m_House.FlipFirstCard();
            cout << m_House << endl;

            // раздает игрокам дополнительные карты
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
                m_Deck.AdditionalCards(*pPlayer);

            // раздает дилеру дополнительные карты
            // открывает карты на всех руках  и подводит итог игры
            m_Deck.AdditionalCards(m_House);
            cout << endl <<"Game result:" << endl << endl;

            
            m_House.FlipOtherCards();
            if (m_House.IsBusted()) {
                for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
                    if (!(pPlayer->IsBusted())) pPlayer->Win();
                    else pPlayer->Lose();
            }
            else {
                // сравнивает суммы очков всех оставшихся игроков с суммой очков дилера
                for (pPlayer = m_Players.begin(); pPlayer != m_Players.end();
                    ++pPlayer) {
                    if (!(pPlayer->IsBusted())) {
                        if (pPlayer->GetTotal() > m_House.GetTotal()) pPlayer->Win();
                        else if (pPlayer->GetTotal() < m_House.GetTotal()) pPlayer->Lose();
                        else pPlayer->Push();
                    } else pPlayer->Lose();
                }   
            }
            // очищает руки всех игроков
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
                pPlayer->Clear();
            m_House.Clear();
        }
};


int main() {
    cout << "=== № 1 ===" << endl << endl;
    A_ptr<Date> today(new Date), date(new Date("2020.2.29"));

    cout << *date << "\n" << *today << endl;
    cout << "Year: " << today->getYear() << " Month: " << today->getMonth() << " Day: " << today->getDay() << endl << endl;
    date ^= today; // присваивание с перемещением
    string null = today.isNull()? "NullPtr " : "not Nullptr ";
    cout << "today is " << null << endl;
    null = date.isNull()? "NullPtr" : "not NullPtr";
    cout << "date is " << null << endl << endl;

    cout << "=== № 2 ===" << endl << endl;

    today = new Date(2021, 10, 8);
    cout << *today << "\n" << *date << "\nGreatest date: " << *compareDate(today, date)<< endl << endl;

    swap(today, date);
    cout << *today << "\n" << *date << endl << endl << endl << endl;

    cout << "=== № 3, 4, 5 ===" << endl << endl;
    Game game({"CAT", "DOG", "FOX"});
    game.Play();
    cout << endl << endl;
    return 0;
}
