#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

// количество строк
#define M 600

// максимальная длина строки, учитывая 0 в конце
#define N 20

// предельное значение хеш-функции+1
#define K 4096

char strings[M][N];

unsigned hash(unsigned result, unsigned char *string, int size)
{
    int i;
    for (i = 0; i < size; i++)
        result += (result << 3) + string[i];
    return result;
}

uint64_t salt = 0;

int main()
{
    int i, j, len, regenerate, collision;
    unsigned hash1, hash2;

    // генерация случайных строк
    for (i = 0; i < M; i++) {

        // случайная длина строки
        len = 1 + random() % (N-1);

        char tmpstr[N];

        // генерация случайной строки
        for (j = 0; j < len; j++)
            tmpstr[j] = 'a' + random() % 26;
        tmpstr[len] = 0;

        // проверка, нет ли уже такой строки
        regenerate = 0;
        for (j = 0; j < i; j++) {
            if (strcmp(tmpstr, strings[j]) != 0) continue;
            regenerate = 1;
            break;
        }

        if (regenerate) {
            // такая строка уже есть; начать этот шаг цикла повторно
            i--;
            continue;
        } else {
            // записать новую строку в массив
            strcpy(strings[i], tmpstr);
        }

        // найти salt, при котором нет коллизий
        do {
            // хеш сгенерированной строки
            hash1 = hash(0, (unsigned char*)&salt, sizeof(salt));
            hash1 = hash(hash1, (unsigned char*)tmpstr, len);
            hash1 %= K;

            // проверка, нет ли уже строки с таким хеш-значением
            collision = 0;
            for (j = 0; j < i; j++) {
                // хеш строки из массива
                hash2 = hash(0, (unsigned char*)&salt, sizeof(salt));
                hash2 = hash(hash2, (unsigned char*)strings[j], strlen(strings[j]));
                hash2 %= K;
                if (hash1 != hash2) continue;
                collision = 1;
                printf("COLLISION: %s[%d] (%u) %s[%d] (%u)\n", tmpstr, i, hash1, strings[j], j, hash2);
                salt++;
                break;
            }
        } while (collision);
    }

    return 0;
}