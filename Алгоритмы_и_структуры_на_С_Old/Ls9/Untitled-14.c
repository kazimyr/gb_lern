#include <stdio.h>
#include <stdlib.h>
#define bool int

  
/* Узел двоичного дерева содержит данные, указатель на левого потомка

   и указатель на правого ребенка */

struct node {

    int data;

    struct node* left;

    struct node* right;

};

  
/* Возвращает высоту двоичного дерева */

int height(struct node* node);

  
/* Возвращает true, если двоичное дерево с корнем в качестве корня сбалансировано по высоте */

bool isBalanced(struct node* root)

{

    int lh; /* для высоты левого поддерева */

    int rh; /* для высоты правого поддерева */

  

    /* Если дерево пусто, вернуть true */

    if (root == NULL)

        return 1;

  

    /* Получить высоту левого и правого поддеревьев */

    lh = height(root->left);

    rh = height(root->right);

  

    if (abs(lh - rh) <= 1 && isBalanced(root->left) && isBalanced(root->right))

        return 1;

  

    /* Если мы достигаем здесь, то дерево не сбалансировано по высоте */

    return 0;

}

  
/* ПОЛЕЗНЫЕ ФУНКЦИИ ДЛЯ ТЕСТИРОВАНИЯ isBalanced () ФУНКЦИЯ */

  
/* возвращает максимум два целых числа */

int max(int a, int b)

{

    return (a >= b) ? a : b;

}

  
/* Функция вычисляет «высоту» дерева. Высота это

    количество узлов вдоль самого длинного пути от корневого узла

    вплоть до самого дальнего листового узла. */

int height(struct node* node)

{

    /* базовое дерево пусто */

    if (node == NULL)

        return 0;

  

    /* Если дерево не пустое, то высота = 1 + максимум слева

      высота и правая высота */

    return 1 + max(height(node->left), height(node->right));

}

  
/* Вспомогательная функция, которая выделяет новый узел с

   данные даны и NULL левый и правый указатели. */

struct node* newNode(int data)

{

    struct node* node = (struct node*)

        malloc(sizeof(struct node));

    node->data = data;

    node->left = NULL;

    node->right = NULL;

  

    return (node);

}

  

int main()

{

    struct node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->left->left->left = newNode(8);

  

    if (isBalanced(root))

        printf("Tree is balanced");

    else

        printf("Tree is not balanced");

  

    getchar();

    return 0;

}