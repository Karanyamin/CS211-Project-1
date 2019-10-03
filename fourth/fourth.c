#include <stdio.h>
#include <stdlib.h>

void freeMatrix(int** matrix, int m){//m rows
    for (int i = 0; i < m; i++){
        free(matrix[i]);
    }
    free(matrix);
}

int** createMatrix(int m, int n){ // with m rows and n cols
    int** matrix = malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++){
        matrix[i] = malloc(n * sizeof(int));
    }
    return matrix;
}

void populateArray(FILE* ptr, int** matrix, int rows, int cols){//Assume the file is already at the part where we can read the ints
    int temp = 0;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (j != cols - 1){
                fscanf(ptr, "%d\t", &temp);
            } else {
                fscanf(ptr, "%d\n", &temp);
            }
            matrix[i][j] = temp;
        }
    }
}

void printMatrix(int** matrix, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if (j != cols - 1){
                printf("%d\t", matrix[i][j]);
            } else {
                printf("%d\n", matrix[i][j]);
            }
        }
    }
    printf("\n");
}

void multiplyMatrix(int** matrix1, int m1, int n1, int** matrix2, int m2, int n2, int** result){

    for (int row = 0; row < m1; row++){
        for (int col = 0; col < n2; col++){
            int sum = 0;
            for (int i = 0; i < m2; i++){
                sum += matrix1[row][i] * matrix2[i][col];
            }
            result[row][col] = sum;
        }
    }
}


int main(int argc, char** argv) {
    FILE* f = fopen(argv[1], "r");
    if (f == NULL){
        printf("error");
        exit(0);
    }



    int m1 = 0;
    int n1 = 0;

    fscanf(f, "%d\t%d\n", &m1, &n1);

    int** matrix1;

    matrix1 = createMatrix(m1, n1);

    populateArray(f, matrix1, m1, n1);

    int m2 = 0;
    int n2 = 0;

    fscanf(f, "%d\t%d\n", &m2, &n2);

    int** matrix2;

    matrix2 = createMatrix(m2, n2);

    populateArray(f, matrix2, m2, n2);





    if (m2 == n1){
        //result array will be size m1 rows and n2 columns
        int** result;

        result = createMatrix(m1, n2);

        multiplyMatrix(matrix1, m1, n1, matrix2, m2, n2, result);

        printMatrix(result, m1, n2);

        freeMatrix(result, m1);


    } else {
        printf("bad-matrices\n");
    }

    freeMatrix(matrix1, m1);
    freeMatrix(matrix2, m2);

    fclose(f);
    return 0;
}
