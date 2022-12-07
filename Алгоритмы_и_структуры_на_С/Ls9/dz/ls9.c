#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} BinTreeIntNode;

BinTreeIntNode* treeInsert(BinTreeIntNode *t, int data) {
    BinTreeIntNode *newNode;
    newNode = (BinTreeIntNode*) malloc(sizeof(BinTreeIntNode));
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    BinTreeIntNode *current = t;
    BinTreeIntNode *parent = t;
    if (t == NULL) {
        t = newNode;
    } else {
        while (current->key != data) {
            parent = current;
            if (current->key > data) {
                current = current->left;
                if (current == NULL) {
                    parent->left = newNode;
                    return t;
                }
            } else {
                current = current->right;
                if (current == NULL) {
                    parent->right = newNode;
                    return t;
                }
            }
        }
    }
    return t;
}
void printBinTree(BinTreeIntNode *root) {
    if (root) {
        printf("%d", root->key);
        if (root->left || root->right) {
            printf("(");
            if (root->left)
                printBinTree(root->left);
            else
                printf("NULL");
            printf(",");
            if (root->right)
                printBinTree(root->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}

// 1. Написать функцию проверяющую является ли переданное в неё бинарное дерево сбалансированным 
//    и написать программу, которая:
//    - создаст [50] деревьев по [10000] узлов и заполнит узлы случайными целочисленными значениями;
//    - рассчитает, какой процент из созданных деревьев является сбалансированными.

int findDepthTree(BinTreeIntNode *root) {
    if(!root) return 0;
    int nr = findDepthTree(root->right);
    int nl = findDepthTree(root->left);
    return (nr > nl ? nr : nl) + 1;
}

int blnsTree(BinTreeIntNode *t) {
    if(t) return abs(findDepthTree(t->right) - findDepthTree(t->left)) < 2 ? 1: 0;
    return 0;
}

int randInRange(int mn, int mx) { 
    return mn + rand() % ((mx - mn) + 1);
}

// 2. Написать рекурсивную функцию бинарного поиска в дереве хранящемся в узлах, а не в массиве.

int recSrchBinTree(BinTreeIntNode *root, int val){
    if (root == NULL) return 0;
    if (root->key == val) return 1;
    if(root->key < val) return recSrchBinTree(root->right, val);
    return recSrchBinTree(root->left, val);
}

int main() {
    // № 1
    const int sz = 10000, vl = 50000, qnty = 100;
    srand(time(NULL));
    int s = 0, fnd = 0, srch = -5;//randInRange(0, vl);
    for (int k = 0; k < qnty; k++) {
        BinTreeIntNode *tree = treeInsert(tree, vl / 2);
        for(int i = 1; i < sz; i++) treeInsert(tree, randInRange(0, vl));
        if(blnsTree(tree)) s++;
         
        if(recSrchBinTree(tree, srch)) {
            printf("В дереве № %d найдено поисковое число %d\n", k, srch);
            fnd++;
        }
    }
    printf("\nЧисло %d найдено %d раз", srch, fnd);
    printf("\n%d%% balanced trees\n\n", s*100/qnty);

    return 0;    
    
    // printBinTree(tree);
    // printf("\n%d\n", findDepthTree(tree));
    // printf("\n%s\n", blnsTree(tree) ? "Дерево сбалансировано":"Дерево не сбалансировано");
    // BinTreeIntNode *tree = treeInsert(tree, 50);
    // srand(time(NULL));
    // for(int i = 0; i < sz; i++) treeInsert(tree, randInRange(0, vl));
    // printBinTree(tree);
    // printf("%d\n%d\n", findDepthTree(tree), blnsTree(tree));

}