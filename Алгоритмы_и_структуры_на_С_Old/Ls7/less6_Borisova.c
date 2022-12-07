#define NULL 0
typedef struct {
    int pr;
    int dat;
} Node;

#define SZ 20
Node* arr[SZ];
int tail;
int items;
int head;
int i;

void initQueue() {
   for ( i = 0; i < SZ; ++i) {
       arr[i] = NULL;
    }
    head = 0;
    tail = 0;
    items = 0;
}

void ins(int pr, int dat) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->dat = dat;
    node->pr = pr;
    int flag;

    if (items == 0) {
       arr[tail++] = node;
       items++;
    } else if (items == SZ) {
        printf("%s \n", "Queue is full");
        return;
    } else {
        int i = 0;
        int idx = 0;
        Node *tmp;
        for (i = head; i < tail; ++i) {
            idx = i % SZ;
            if (arr[idx]->pr > pr)
                break;
            else
                idx++;
        }
        flag = idx % SZ;
        i++;
        while (i <= tail) {
            idx = i % SZ;
            tmp = arr[idx];
            arr[idx] = arr[flag];
            arr[flag] = tmp;
            i++;
        }
        arr[flag] = node;
        items++;
        tail++;
    }
}

Node* rem() {
    if (items == 0) {
        return NULL;
    } else {
        int idx = head++ % SZ;
        Node *tmp = arr[idx];
        arr[idx] = NULL;
        items--;
        return tmp;
    }
}

void printQueue() {
    printf("[ ");
    for ( i = 0; i < SZ; ++i) {
        if (arr[i] == NULL)
            printf("[*, *] ");
        else
            printf("[%d, %d] ", arr[i]->pr, arr[i]->dat);
    }
    printf(" ]\n");
}


#define T char
#define SIZE 1000
#define true 1 == 1
#define false 1 != 1

typedef int boolean;
int cursor = -1;
T Stack[SIZE];

boolean pushStack(T data) {
    if (cursor < SIZE) {
        Stack[++cursor] = data;
        return true;
    } else {
        printf("%s \n", "Stack overflow");
        return false;
    }
}

T popStack() {
    if (cursor != -1) {
        return Stack[cursor--];
    } else {
        printf("%s \n", "Stack is empty");
        return -1;
    }
}

void decToBin(int a) {
    while (a >= 1) {
        pushStack(a % 2);
        a /= 2;
    }
}

void main() {
        initQueue();
    ins(1, 11);
    ins(3, 22);
    ins(4, 33);
    ins(2, 44);
    ins(3, 55);
    ins(4, 66);
    ins(5, 77);
    ins(1, 88);
    ins(2, 99);
    ins(6, 100);
    printf("*******************Task_1****************************************************\n");
    printQueue();
    for ( i = 0; i < 7; ++i) {
        Node* n = rem();
        printf("pr=%d, dat=%d \n", n->pr, n->dat);
    }
    printQueue();
printf("Insert [1,10], [3,20], [6,130]\n");
    ins(1, 110);
    ins(3, 120);
    ins(6, 130);
    printQueue();


printf("*******************Task_2****************************************************\n");
    decToBin(22);
    int count = cursor;
    for (i = 0; i <= count; ++i) {
        printf("%d", popStack());
    }

}
