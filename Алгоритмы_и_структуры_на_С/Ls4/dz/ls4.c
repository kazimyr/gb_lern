#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 1. Реализовать функцию перевода чисел из десятичной системы в двоичную, используя рекурсию.
size_t i = 0;
void decToBin(int num, char *pn) {
    if (num > 0){
        i++; //Считаем количество значащих двоичных цифр
        decToBin(num / 2, pn - 1);
        *(pn + i) = num % 2 + '0';
    } else if( !i ) {
        *pn = '0';
        *(pn + 1) = '\0';
        } else {
            *pn = '\0';
            i--;
        }
}

// 2. Реализовать функцию возведения числа [a] в степень [b]:
// - Рекурсивно.
// - Рекурсивно, используя свойство чётности степени (то есть, если степень, в которую нужно возвести 
// число, чётная, основание возводится в квадрат, а показатель делится на два, а если степень 
// нечётная - результат умножается на основание, а показатель уменьшается на единицу)

int mix(int a, int b) { 
    if (b == 1) {
        return a;
    } else return a * mix(a, b - 1);
}   

int oddAndEven(int a, int b) {
    if (b % 2) {
        mix(a, b);
    } else {
        if (b == 2) return a*a;
        else return oddAndEven(a * a, b / 2);
    }
    
}

// 3. Реализовать нахождение количества маршрутов шахматного короля с препятствиями (где 
// единица - это наличие препятствия, а ноль - свободная для хода клетка). Король ходит только 
// по прямой, маршруты считаются с клетки (0, 0)

int randInRange(size_t mn, size_t mx) { // Случайное число в заданном диапазоне
    return mn + rand() % ((mx - mn) + 1);
}


void setBoard(int **board, int X, int Y) {
        srand(time(NULL));
        for (size_t k = 0, mx = X * Y / 5; k < mx; k++) 
            board[randInRange(1, X - 1)][randInRange(1, Y - 1)] = 1; // Ставим случайные препятствия
        board[1][1] = 0;                                             //Страховка на случай попадания препятствия в начало маршрута
}

void getBoard(int **board, int X, int Y) {
    printf("Доска с препятствиями\n");
    for (size_t i = 0; i < X; i++){
        for (size_t j = 0; j < Y; j++)
            printf("%6d", board[i][j]);
        printf("\n");
    }
    printf("\n");
}

int routes(int **board, int x, int y) {
    if(x == 0 && y == 0 || board[x][y] == 1) return 0;
    else if (x == 0 && y ==1 || x == 1 && y == 0) return 1;
    else if (x == 0 ^ y == 0) return x == 0 ? routes(board, 0, y -1) : routes(board, x - 1, 0);
    else return routes(board, x, y -1) + routes(board, x - 1, y);
}

int main() {
    // № 1
    int n;
    char binary[64];
    printf("Введите десятичное: ");
    scanf("%d", &n);
    decToBin(n, binary);
    printf("Соответствующее двоичное: %s\n\n", binary);

    // № 2
    int base, degree;
    printf("Введите основание: ");
    scanf("%d", &base);
    printf("Введите степень: ");
    scanf("%d", &degree);
    printf("%d в степени %d равно %d\n\n", base, degree, oddAndEven(base, degree));

    // № 3
    int X, Y;
    int **board;
    printf("Введите размеры доски по горизонтали и вертикали через пробел: ");
    scanf("%d %d", &X, &Y);
    board = (int**) calloc(X, sizeof(int*));
    for (size_t k = 0; k < X; board[k++] = (int*) calloc(Y, sizeof(int))); // Заводим соответствующий массив
    
    setBoard(board, X, Y);
    getBoard(board, X, Y);

    printf("Доска с количеством маршрутов для каждой клетки\n");
    for (size_t x = 0; x < X; x++) {
        for (size_t y = 0; y < Y; y++) {
            printf("%6d", routes (board, x, y));
        }
        printf("\n");
    }

    for (size_t k = 0; k < X; free(board[k++]));    // Освобождаем память 
    free(board);                                    // за ненадобностью
    return 0;
}