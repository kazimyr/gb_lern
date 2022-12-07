#include "stdio.h"
//#include "conio.h"
//#include "locale.h"

int main(int argc, char* argv[])
{
 //setlocale(0, "rus");
 int a, i, mass[99];
 for (i = 0; i < 99; i++)
 {
 mass[i] = 0;
 }
 printf("Введите число: ");
 scanf("%d", &a);
 i = 0;
 while (a != 0)
 {
 if (a % 2 == 0)
 {
 mass[i] = 0;
 a = a / 2;
 }
 else
 {
 mass[i] = 1;
 a = a / 2;
 }
 i++;
 }
 i = i - 1;
 for (; i >= 0; i--)
 printf("%d", mass[i]);
 //_getch();
 return 0;
}