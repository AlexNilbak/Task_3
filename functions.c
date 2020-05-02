#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//-------------------- FUNCTIONS --------------------//

int heigth(FILE* input);
int* length(FILE* input, int m);
int** make_mat(int m, int* n, FILE* input);
int search(int m, int* n, int** matrix);
int del_string(int** matrix, int f, int m, int* n);
int print_mat(FILE* output, int** matrix, int m, int* n);
int autotest1(void);
int autotest2(void);


//Находим количество строк

int heigth (FILE* input) {
    int i = 0;
    char string[512];
    while (fgets(string, sizeof(string), input) != NULL){
        i++;
    }
    rewind(input);
    return i;
}

//Находим число элементов в каждой строке

int* length (FILE* input, int m) {
    int* n=(int*)malloc(m*sizeof(int));
    char string[512];
    for (int j=0; j<m; j++){
        fgets(string, 512, input);
        n[j]=0;
        if ((strlen(string)==1 && j!=m-1) || string[0] == ' '){
            n[j]=-1;
        }
        else{
            for (int i=0; i<strlen(string); i++){
                if (string[i] == ' ' || i == strlen(string)-1){
                    n[j]++;
                }
            }
        }
    }
    rewind(input);
    return n;
}

//Создаем и считываем матрицу нужных размеров

int** make_mat (int m, int* n, FILE* input) {
    int** matrix = (int**)malloc(m*sizeof(int*));
    for (int i=0; i<m; i++){
        matrix[i] = (int*)malloc(n[i]*sizeof(int));
        for(int j=0; j<n[i]; j++){
            fscanf(input, "%d", &matrix[i][j]);
        }
    }
    return matrix;
}

//Находим строку, каждый элемент которой максимален в своем столбце


int search (int m, int* n, int** matrix){
    int f=0;
    for (int i=1; i<m; i++){
        if(matrix[i][0]>matrix[f][0]){
            f=i;
        }
    }
    for (int i=1; i<m; i++){
        if(i!=f && matrix[i][0]==matrix[f][0]){
            return -1;
        }
    }
    if (n[f]>1){
        for (int i=1; i<n[f]; i++){
            for (int j=0; j<m; j++){
                if (n[j]>i){
                    if (j!=f && matrix[j][i]>matrix[f][i]){
                        return -1;
                    }
                }
            }
        }
    }
    return f;
}

//Удаляем строку с максимальными элементами

int del_string(int** matrix, int f, int m, int* n){
    free(matrix[f]);
    for (int i=f; i<m-1; i++){
        matrix[i]=matrix[i+1];
        n[i]=n[i+1];
    }
    matrix=(int**)realloc(matrix,(m-1)*sizeof(int*));
    n=(int*)realloc(n,(m-1)*sizeof(int));
    return 0;
}

//Выводим измененную матрицу

int print_mat(FILE* output, int** matrix, int m, int* n){
    for(int i=0; i<m; i++){
       for(int j=0; j<n[i]; j++){
           fprintf(output, "%d ", matrix[i][j]);
       }
       fprintf(output, "\n");
    }
    return 0;
}


int autotest1(void){
    int p;
    int** arr;
    int m=2;
    int n[2];
    n[0]=2;
    n[1]=2;
    arr=(int**)malloc(2*sizeof(int*));
    arr[0]=(int*)malloc(2*sizeof(int));
    arr[1]=(int*)malloc(2*sizeof(int));
    arr[0][0]=1.0;
    arr[0][1]=2.5;
    arr[1][0]=2.0;
    arr[1][1]=1.0;
    p = search(m, n, arr);
    free(arr[0]);
    free(arr[1]);
    free(arr);
    if (p == -1){
        printf("Autotest 1 passed\n");
        return 0;
    }
    else{
        printf("Autotest 1 failed\n");
        return 1;
    }
}

int autotest2(void){
    int p;
    int** arr;
    int m=2;
    int n[2];
    n[0]=3;
    n[1]=2;
    arr=(int**)malloc(2*sizeof(int*));
    arr[0]=(int*)malloc(3*sizeof(int));
    arr[1]=(int*)malloc(2*sizeof(int));
    arr[0][0]=1.0;
    arr[0][1]=1.5;
    arr[0][2]=3.5;
    arr[1][0]=2.5;
    arr[1][1]=3.0;
    p=search(m, n, arr);
    free(arr[0]);
    free(arr[1]);
    free(arr);
    if (p == 1){
        printf("Autotest 2 passed\n");
        return 0;
    }
    else{
        printf("Autotest 2 failed\n");
        return 1;
    }
}


//-------------------- MAIN --------------------//

int main(void) {
    int k, f, m, * n;
    int** matrix;
    FILE* input;
    FILE* output;
    input = fopen("data.txt", "r");
    if (!input){
        printf("Cannot open file 'data.txt'\n");
        return -1;
    }
    output = fopen("res.txt", "w");
    if (!output){
        printf("Cannot open file 'res.txt'\n");
        return -1;
    }

    k = autotest1();
    if (k == 1) {
        return 1;
    }

    k = autotest2();
    if (k == 1) {
       return 2;
    }

    m = heigth(input);
    if (m==0){
        printf("Empty file\n");
        return -2;
    }

    n = length(input, m);
    for (int i = 0; i < m; i++) {
        if(n[i]==-1){
            printf("Wrong data\n");
            return -3;
        }
    }

    matrix = make_mat(m, n, input);

    f = search(m, n, matrix);

    if (f != -1) {
        k = del_string(matrix, f, m, n);
        m = m - 1;
    }

    k = print_mat(output, matrix, m, n);

    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);

    fclose(input);
    fclose(output);
    return 0;
}

