#include <stdio.h>
#include <stdlib.h>

int isRightPrime(int value);
int isPrime(int value);

int main(int argc, char* argv[]){
    FILE* pointer = fopen(argv[1], "r");
    if (pointer == NULL) {
        printf("error");
        exit(0);
    }
    int numberOfElements = 0;
    if(fscanf(pointer, "%d\n", &numberOfElements) == EOF){
        exit(0);
    }
    int i;
    for (i = 0; i < numberOfElements; i++){
        int value;
        fscanf(pointer, "%d\n", &value);
        if (value <= 1){
            printf("no\n");
        } else {
            if(isRightPrime(value) == 1){
                printf("yes\n");
            } else {
                printf("no\n");
            }
        }
    }
    fclose(pointer);
    return 0;
}

int isRightPrime(int value){

    while (value != 0){
        if (isPrime(value) == 1){
            value = value / 10;
        } else {
            return 0;
        }
    }
    return 1;
}

int isPrime(int value){
    if (value == 1) return 0;
    int i;
    for(i = 2; i < value; i++){
        if (value % i == 0){
            return 0;
        }
    }
    return 1;
}
