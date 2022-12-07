#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int randInRange(int mn, int mx) { 
    return mn + rand() % ((mx - mn) + 1);
}

// 1. Реализовать шифрование и расшифровку цезаря с передаваемым в функцию сообщением и ключом

void encryptionCaesar(char *mssg, int key){
    for (int i = 0; mssg[i]; i++) mssg[i] = 'A' + (mssg[i] - 'A' + key) % ('z' - 'A');
    
}

void decryptionCaesar(char *mssg, int key){
    for (int i = 0; mssg[i]; i++) mssg[i] = 'z' - ('z' - mssg[i] + key) % ('z' - 'A');
}

// 2. Реализовать шифрование и расшифровку перестановками с передаваемым в функцию сообщением и количеством столбцов.

void encTransposition(char *mssg, int key){
    int sz = strlen(mssg);
    int str = sz / key;
    char tmp[sz];
    for (int i = 0; i < str; i++)
        for (int j = 0; j < key; j++)
            tmp[j * str + i] = mssg[i * key + j];
    strncpy(mssg, tmp, sz);
}


void decTransposition(char *mssg, int key){
    int sz = strlen(mssg);
    int str = sz / key;
    char tmp[sz];
    for (int i = 0; i < str; i++)
        for (int j = 0; j < key; j++)
            tmp[i * key + j] = mssg[j * str + i];
    strncpy(mssg, tmp, sz);

}

int main() {
    // № 1 
    printf("Шифрование и расшифровка цезаря\n");
    char message1[] = "VeryHighlyClassifiedDataOnTheQuantityOfQuality";
    printf("\nСообщение:\t\t%s\n", message1);
    encryptionCaesar(message1, 27);
    printf("\nШифровка:\t\t%s\n", message1);
    decryptionCaesar(message1, 27);
    printf("\nПолучено сообщение:\t%s\n\n\n", message1);

    // № 2
    printf("Шифрование и расшифровка перестановками\n");
    char messg[] = "Very Highly Classified Data On The Quantity Of Quality";
    srand(time(NULL));
    int key = (int)sqrt((double)strlen(messg));
    int len = (strlen(messg) % key ? strlen(messg) / key + 1 : key) * key + 1;
    
    char message2[len];
    
    strncpy(message2, messg, len);

    for (int i = (len -1) - strlen(messg); i > 0; i--) message2[len - i - 1] = randInRange('A', 'z');

    printf("\nСообщение:\t\t%s\n", messg);
    
    encTransposition(message2, key);
    printf("\nШифровка:\t\t%s\n", message2);

    decTransposition(message2, key);
    printf("\nПолучено сообщение:\t%s\n\n", message2);

    return 0;
}