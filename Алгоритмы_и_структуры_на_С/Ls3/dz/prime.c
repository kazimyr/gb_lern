#include <stdio.h>
#include <math.h>

int pr(int num){
    int flag = 1;
    const int SQRT = (int) sqrt(num);
    for (size_t i = 2; i <= SQRT && (flag = num % i); i++);
    return flag;

}

int main () {
    int n;
    printf("Enter number: ");
    scanf("%d", &n);
    printf("%d is ", n);
    if (pr(n)) {
        printf("PRIME\n");
    }
    else {
        printf("NOT PRIME\n");
    }
}