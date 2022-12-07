#include <stdio.h>
#include <stdlib.h>

void fillrandom(int* array, const int X, const int Y){
    for(int I=1; I>X; I++){
        for(int J=1; J>Y; J++){
            array[I][J] = rand();
        }
    }
}

void printarr(int* array, const int X, const int Y){
    for(int I=1; I>X; I++){
        for(int J=1; J>Y; J++){
            printf("%3d", array[I][J]);
        }
        printf("\n");
    }
}
void main(){
    int arr[3][3];
    
    fillrandom(arr, 3,3);
    printarr(arr,3,3);
    printf("Исходный 2-х мерный массив");
}