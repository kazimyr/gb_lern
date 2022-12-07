#include <iostream>
#include <random>
#include <stdlib.h>
#include <chrono>
#include <initializer_list>

using namespace std;

enum Cell {
    CROSS = 'X',
    ZERO = '0',
    EMPTY = '-'
};

enum Progress {
    IN_PROGRESS,
    WON_HUMAN,
    WON_AI,
    DRAW
};

struct Coord {
    size_t y;
    size_t x;
};

struct Field {
    Cell** ppField = nullptr;
    const size_t SIZE = 3;
    Cell human = EMPTY;
    Cell ai = EMPTY;
    size_t turn = 0;
    Progress  progress = IN_PROGRESS;
};

//++++++++++++++++++++++++++++++++++++++++

int32_t getRandomNum(int32_t min, int32_t max) {
    const static auto seed = chrono::system_clock::now().time_since_epoch().count();
    static mt19937_64 generator(seed);
    uniform_int_distribution<int32_t> dis(min, max);
    return dis(generator);
}

void initField(Field& r) {
    r.ppField = new Cell * [r.SIZE];
    for (size_t y = 0; y < r.SIZE; y++) {
        r.ppField[y] = new Cell[r.SIZE];
        for (size_t x = 0; x < r.SIZE; x++) {
            r.ppField[y][x] = EMPTY;
        }
    }
    if (getRandomNum(0, 1000) > 500) {
        r.human = CROSS;
        r.ai = ZERO;
        // r.turn = 0;
    } else {
        r.human = ZERO;
        r.ai = CROSS;
        // r.turn = 1;
    }
}

void deinitField(Field& r){
    for (size_t x = 0; x < r.SIZE; x++) {
        delete [] r.ppField[x];
    }
    delete [] r.ppField;
    r.ppField = nullptr;
}

void printField(const Field& r) {
    cout<< endl << "     ";
    for (size_t x = 0; x < r.SIZE; x++) {
        cout << x + 1 << "   ";
    }
    cout << endl  << "   |   |   |   |" << endl;

    for (size_t y = 0; y < r.SIZE; y++) {
        cout << " " << y + 1 << " | ";
        for (size_t x = 0; x < r.SIZE; x++) {
            cout << static_cast<char>(r.ppField[y][x]) << " | ";
        }
        cout << endl << "   |   |   |   |" << endl;
    }
    cout << endl << "   Human:" << static_cast<char>(r.human) << endl;
    cout << "Computer:" << static_cast<char>(r.ai) << endl << endl;
}

void inline clearScr() {
    system("clear");
}

Progress getWon(const Field &r, size_t y, size_t x) {
    bool won = false;
    if (r.ppField[y][x] != EMPTY) {
        if (r.ppField[y][0] == r.ppField[y][1] && r.ppField[y][1] == r.ppField[y][2]) {
            won = true;
            } else if (r.ppField[0][x] == r.ppField[1][x] && r.ppField[1][x] == r.ppField[2][x]) {
                won = true;
            } else if (x == y && r.ppField[0][0] == r.ppField[1][1] && r.ppField[1][1] == r.ppField[2][2]) {
                won = true;
            } else if ( (x + y) == 2 && r.ppField[0][2] == r.ppField[1][1] && r.ppField[1][1] == r.ppField[2][0]) {
                won = true;
            }
        if (won) {
            if (r.ppField[y][x] == r.human) return WON_HUMAN;
            return WON_AI;
        } else {
            bool draw = true;
            for (size_t i = 0; i < r.SIZE; i++){
                for (size_t j = 0; j < r.SIZE; j++) {
                    if (r.ppField[i][j] == EMPTY) {
                        draw = false;
                        break;
                    }
                }
                if (!draw) break;
            }
            if (draw) return DRAW;
        }
    }
    return IN_PROGRESS;
}

Coord getHumanCoord(const Field& r){
    Coord c;
    cout << "Enter X and Y coordinates:";
    
    while (cin >> c.x, cin >> c.y, cin.fail() || c.x < 1 || c.x > 3 || c.y < 1 || c.y > 3 || r.ppField[c.y - 1][c.x - 1] != EMPTY) {
        cout << "Error. For a blank cell, enter two integer coordinates from 1 to 3, separated by a space:";
        cin.clear();
        cin.ignore(32767, '\n');
    }

    // do {
    //     cout << "Enter X and Y coordinates:"
    //     cin >> c.x;
    //     cin >> c.y;
    // } while (c.x < 1 || c.x > 3 || c.y < 1 || c.y > 3 || r.ppField[c.y - 1][c.x - 1] != EMPTY);
        
    return {--c.y, --c.x};
}

const Coord* angleNotangle(const Field& f,const initializer_list<Coord> &arCells) {
    // const size_t SIZE = arCells.size();
    const Coord* arr[arCells.size()];
    size_t n = 0;
    for (auto &c: arCells) {
        if (f.ppField[c.y][c.x] == EMPTY) arr[n++] = &c;
    }

    if (n > 0) {
        const size_t idx = getRandomNum(0, 1000) % n;
        return arr[idx];
    }
    return nullptr;
}


Coord getAICoord(const Field& r) {

    // if cell for AI or Human is winning
    for (size_t y = 0; y < r.SIZE; y++) {
        for (size_t x = 0; x < r.SIZE; x++) {
            if (r.ppField[y][x] == EMPTY) {
                for (Cell cell: {r.ai, r.human}) {
                    r.ppField[y][x] = cell;
                    Progress won = getWon(r, y, x);
                    if (won == WON_AI || won == WON_HUMAN) {
                        r.ppField[y][x] = EMPTY;
                        return {y, x};
                    }
                    r.ppField[y][x] = EMPTY;
                }
            }
            
        }
    }
    
    //Center
    if (r.ppField[1][1] == EMPTY) return {1, 1};

    //Angles
    if(const Coord* c = angleNotangle(r, {{0, 0}, {0, 2}, {2, 2}, {2, 0}})) return *c;

    return *angleNotangle(r, {{0, 1}, {1, 0}, {1, 2}, {2, 1}});
    
}


void congrats(Progress p){
    switch (p)
    {
    case WON_HUMAN:
        cout << "Human won! :-)" << endl;
        break;

    case WON_AI:
        cout << "Computer won! :-(" << endl;
        break;
    
    case DRAW:
        cout << "DROW! :-|" << endl;
    }
}

int main() {
    Field f;
    initField(f);
    Coord c {0, 0};
    f.turn += (f.human == CROSS);
    while((clearScr(), printField(f), f.progress = getWon(f, c.y, c.x)) == IN_PROGRESS) {
                
        // clearScr();
        // printField(f);

        if (f.turn++ % 2) {
            c = getHumanCoord(f);
            f.ppField[c.y][c.x] = f.human;
        }
        else {
            c = getAICoord(f);
            f.ppField[c.y][c.x] = f.ai;
        }
        
    }
    // clearScr();
    // printField(f);
    congrats(f.progress);
    deinitField(f);
    return 0;
}
