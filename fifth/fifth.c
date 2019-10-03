#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
    FILE* fn = fopen(argv[1], "r");
    if (fn == NULL){
        exit(0);
    }
    int n = 0;
    if (fscanf(fn, "%d\n", &n) == EOF){
        exit(0);
    }

    int matrix[n][n];
    int temp = 0;
    //populate
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (j == n - 1){
                fscanf(fn, "%d\n", &temp);
            } else {
                fscanf(fn, "%d", &temp);
            }
            matrix[i][j] = temp;
        }
    }

    int sum = 0;
    for (int j = 0; j < n; j++){ //Checking the first row as a checker
        sum += matrix[0][j];
    }

    int horizontal = 1;
    int vertical = 1;
    int forwardslash = 1;
    int backslash = 1;
	int distinct = 1;

	//distinct
	//populate array
	int array[n*n];
	int k = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			array[k] = matrix[i][j];
			k++;
		}
	}
	//check if every value in array is distinct
	for (int i = 0; i < n*n; i++){
		for (int j = 0; j < i; j++){
			if (array[j] == array[i]){
				distinct = 0;
			}
		}
	}


    //horizontal
    for (int i = 0; i < n; i++){
        int temp = 0;
        for (int j = 0; j < n; j++){
            temp += matrix[i][j];
        }
        if (temp != sum) horizontal = 0;
    }

    //vertical
    for (int j = 0; j < n; j++){
        int temp = 0;
        for (int i = 0; i < n; i++){
            temp += matrix[i][j];
        }
        if (temp != sum) vertical = 0;
    }

    //diagonal forwardslash
    int temp1 = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i == j){
                temp1 += matrix[i][j];
            }
        }
    }
    if (temp1 != sum) forwardslash = 0;

    //diagonal backslash
    int temp2 = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (j == -i + n - 1){
                temp2 += matrix[i][j];
            }
        }
    }
    if (temp2 != sum) backslash = 0;

    if (horizontal == 1 && vertical == 1 && forwardslash == 1 && backslash == 1 && distinct == 1){
        printf("magic\n");
    } else {
        printf("not-magic\n");
    }

    fclose(fn);
    return 0;
}
