#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;


// 1. Добавить в контейнерный класс, который был написан в этом уроке, методы:
// ● для удаления последнего элемента массива (аналог функции pop_back() в векторах)
// ● для удаления первого элемента массива (аналог pop_front() в векторах)
// ● для сортировки массива
// ● для вывода на экран элементов.

#include <cassert> // для assert()

class ArrayInt {
private:
    int m_length;
    int *m_data;

public:
    ArrayInt() : m_length(0), m_data(nullptr) {}
    ArrayInt(int length) : m_length(length) {
        assert(length >= 0);
        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }
    ~ArrayInt() {
        delete[] m_data;
    }
    void erase() {
        delete[] m_data;
            m_data = nullptr;
        m_length = 0;
    }

    int size() const { return m_length;}

    int &operator[](int index) {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    void resize(int newLength) {
        if (newLength == m_length)
            return;
        if (newLength <= 0) {
            erase();
            return;
        }
        int *data = new int[newLength];
        if (m_length > 0)
        {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;
            for (int index = 0; index < elementsToCopy; ++index)
                data[index] = m_data[index];
        }
        delete[] m_data;
        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index) {
        assert(index >= 0 && index <= m_length);
        int *data = new int[m_length + 1];
        for (int before = 0; before < index; ++before)
            data[before] = m_data[before];
        data[index] = value;
        for (int after = index; after < m_length; ++after)
            data[after + 1] = m_data[after];
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void del(int index) {
        assert(index >= 0 && index < m_length);
        int *data = new int[m_length - 1];
        for (int before = 0; before < index; ++before)
            data[before] = m_data[before];
        for (int after = index + 1; after < m_length; ++after)
            data[after - 1] = m_data[after];
        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void push_back(int value) { insertBefore(value, m_length); }

    void pop_back() { del(m_length - 1); }

    void pop_front() { del(0); }

    bool empty() const { return !m_length;}

    void clear() { resize(0);}

    void sortIntInserts() {
        int temp, pos;
        for (int i = 1; i < m_length; ++i) {
            temp = m_data[i];
            pos = i - 1;
            while (pos >= 0 && m_data[pos] > temp) {
                m_data[pos + 1] = m_data[pos];
                pos--;
            }
            m_data[pos + 1] = temp;
        }
}

    void print() const {
        cout << "The length is: " << size() << endl;
        if (empty()) cout << "Vector is empty.\n";
        else for (int i=0; i< size(); i++) cout << m_data[i] << ' ';
        cout << endl << endl;
    }
};

int randInRange(size_t mn, size_t mx) { // Случайное число в заданном диапазоне
    return mn + rand() % ((mx - mn) + 1);
}

// 2. Дан вектор чисел, требуется выяснить, сколько среди них различных. Постараться
// использовать максимально быстрый алгоритм.

int countInt(ArrayInt &a) {
    if (!a.size()) return 0;
    int count = 1;
    a.sortIntInserts();
    for (int i = 1; i < a.size(); i++) {
        if (a[i] == a[i - 1]) continue;
        count++;
    }
    return count;
}

// 3. Реализовать класс Hand, который представляет собой коллекцию карт. В классе будет одно
// поле: вектор указателей карт (удобно использовать вектор, т.к. это по сути динамический
// массив, а тип его элементов должен быть - указатель на объекты класса Card). Также в классе
// Hand должно быть 3 метода:
// ● метод Add, который добавляет в коллекцию карт новую карту, соответственно он
// принимает в качестве параметра указатель на новую карту
// ● метод Clear, который очищает руку от карт
// ● метод GetValue, который возвращает сумму очков карт руки (здесь предусмотреть
// возможность того, что туз может быть равен 11).

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


int main() {
    cout << "=== № 1 ===" << endl << endl;

    srand(time(NULL));
    ArrayInt array(35);
    for (int i=0; i < array.size(); i++) array[i] = randInRange(0, 100);
    array.print();
    array.push_back(4);
    array.print();
    array.sortIntInserts();
    array.print();
    array.pop_back();
    array.print();
    array.pop_front();
    array.print();
    array.clear();
    array.print();

    cout << "=== № 2 ===" << endl << endl;

    for (int i=0; i < 38; i++) array.push_back(randInRange(0, 100));
    array.print();
    cout << "Различных элементов в массиве: " << countInt(array) << endl << endl; 
    array.print();

    cout << "=== № 3 ===" << endl << endl;

    Hand h;
    h.Add(new Card(Diamonds, Two));
    h.Add(new Card(Hearts, Ace));
    h.Add(new Card(Clubs, Four));
    cout << h.GetTotal() << endl;
    h.Add(new Card(Spades, Ace));
    cout << h.GetTotal() << endl;
    h.Clear();
    cout << h.GetTotal() << endl;
    h.Add(new Card(Hearts, Ace));
    cout << h.GetTotal() << endl << endl;

    return 0;
}