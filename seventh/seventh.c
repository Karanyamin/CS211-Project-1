#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

    char result[argc];
    int ptr = 0;
    for (int i = 1; i < argc; i++){
        char* string = argv[i];
        int j = 0;
        while (*(string + j) != '\0'){
            j++;
        }
        char c = *(string + j - 1);
        result[ptr] = c;
        ptr++;
    }
    result[ptr] = '\0';
    printf("%s", result);
    return 0;
    
}
