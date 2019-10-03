#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isVowel(char c){
    if (c == 'a' || c == 'e' || c == 'i' || c =='o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c =='O' || c == 'U'){
        return 1;
    }
    return 0;
}

void convert(char* string, int current, int argc){
    int length = strlen(string);
    char* result;
    if (isVowel(string[0]) == 1){ //Is a vowel easy work
        result = malloc((length + 4) * sizeof(char));
        for (int i = 0; i < length; i++){
            result[i] = string[i];
        }
        result[length] = 'y';
        result[length + 1] = 'a';
        result[length + 2] = 'y';
        result[length + 3] = '\0';
        if (current == argc - 1){
            printf("%s", result);
        } else {
            printf("%s ", result);
        }
        free(result);
    } else {
        for (int i = 1; i < length; i++){
            if (isVowel(string[i]) == 1){
                char* result = malloc((length + 3) * sizeof(char));
                char* tip = malloc((i + 1) * sizeof(char));
                for (int j = 0; j < i; j++){
                    tip[j] = string[j];
                    if (j == i - 1){
                        tip[j + 1] = '\0';
                    }
                }
                int k = 0;
                for (int j = i; j < length; j++, k++){
                    result[k] = string[j];
                    if (j == length - 1){
                        result[k + 1] = '\0';
                    }
                }
                strcat(result, tip);
                strcat(result, "ay");
                if (current == argc - 1){
                    printf("%s", result);
                } else {
                    printf("%s ", result);
                }
                free(tip);
                free(result);
                break;
            }
        }
    }
}

int main(int argc, char** argv){
    for (int i = 1; i < argc; i++){
        convert(argv[i], i, argc);
    }
    printf("\n");
    return 0;
}
