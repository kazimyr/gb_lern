#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
} TreeNode;

TreeNode *treeInsert (TreeNode *t, int data)
{
    TreeNode *newNode;
    newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;

    TreeNode *current = t;
    TreeNode *parent = t;

    if (t==NULL)
        t= newNode;
    else
    {
        while (current->key!=data)
        {
            parent = current;
            if (current->key >data )
            {
                current = current->left;
                if (current == NULL)
                {
                    parent->left = newNode;
                    return t;
                }
            } else
            {
                current = current->right;
                if(current==NULL)
                {
                    parent->right = newNode;
                    return t;
                }
            }
        }
    }
    return t;
}

void printTree (TreeNode *root)
{
    if (root)
    {
        printf ("%d ", root->key);
        if(root->left || root->right)
        {
            printf("(");
            if (root->left)
                printTree(root->left);
            else
                printf("NULL");
            printf(",");

            if (root->right)
                printTree(root->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}

// Переменная flag хранит в себе информацию о том сбалансировано ли дерево.

void inOrderTravers(TreeNode *root, int *flag) {

    if (*flag == 0)
        return;

    if (root) {

        inOrderTravers(root->left, flag);

        if ( (root->left != NULL && root -> right == NULL) || (root->right != NULL && root -> left == NULL) )
          {
              printf (" Not balanced ");
              *flag = 0;
              return;
          }

        //printf("%2d ", root->key);

        inOrderTravers(root->right, flag);


        if ( (root->left != NULL && root -> right == NULL) || (root->right != NULL && root -> left == NULL) )
        {
            printf(" Not balanced ");
            *flag = 0;
            return;
        }

    }

}

void DeletePostOrderTravers(TreeNode *root) {
    if (root) {
        DeletePostOrderTravers(root->left);
        DeletePostOrderTravers(root->right);
        root->key = 0;
        root->left = NULL;
        root->right = NULL;
    }
}


int main()
{
    int i, j;
    int CountOfBalanced = 0;
    int flag;

    for (j =0; j<50; j++)
    {
        TreeNode *tree = NULL;

        for (i=0; i<100; i++)
           {
                 tree = treeInsert(tree, rand()%100 );
            }

        //printTree(tree);
        //printf(" \n");
        flag = 1;
        inOrderTravers(tree, &flag);
        if (flag == 1)
            CountOfBalanced +=1;
        //printf("\n %d ", flag);
         //printf(" \n");
        DeletePostOrderTravers(tree);
        //printTree(tree);

    }

    printf("\n %d", CountOfBalanced);


    return 0;
}
