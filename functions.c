#include <stdio.h>
#include <stdlib.h>
#include "fun.h"

//Находим количество строк

int heigth (FILE* input) {
    int i = 0;
    char c;
    while (1) {
        c = fgetc(input);
        if (c == '\n' || c == EOF){
            i++;
        }
        if (c == EOF){
            break;
        }
    }
    rewind(input);
    return i;
}

//Находим число элементов в каждой строке

int* length (FILE* input, m) {
    int i = 0;
    int j = 0;
    int n[m];
    char c;
    while (1) {
        c = fgetc(input);
        if (c == ' ' || c == '\n' || c == EOF){
            i++;
        }
        if (c == '\n' || c == EOF) {
            n[j]=i;
            j++;
            i = 0;
        }
        if (c == EOF)
            break;
    }
    rewind(input);
    return n;
}

//Создаем и считываем матрицу нужных размеров

double** make_mat (int m, int* n, FILE* input) {
    double** matrix = (double**)malloc(m*sizeof(double*));
    for (int i = 0; i < m; i++){
        matrix[i] = (double*)malloc(n[i]*sizeof(double));
    }
    for(int i=0; i<m; i++){
        for(int j=0; j<n[i]; j++){
            fscanf(input, "%f", matrix[i][j]);
        }
    }
    return matrix;
}

//Находим строку, каждый элемент которой максимален в своем столбце

int search (int m, int* n, double** matrix){
    int f=0;
    for (int i=1; i<m; i++){
        if(matrix[i][1]>matrix[f][1]){
            f=i;
        }
    }
    for (int i=1; i<m; i++){
        if(i!=f && matrix[i][1]>=matrix[f][1] && matrix[i][1]<=matrix[f][1]){
            return -1;
        }
    }
    for (int i=1; i<n[f]; i++){
        for (int j=0; j<m; j++){
            if (n[j]>i){
                if (j!=f && matrix[j][i]>matrix[f][i]){
                    return -1;
                }
            }
        }
    }
    return f;
}

//Удаляем строку с максимальными элементами

int del_string(double** matrix, int f, int m, int* n){
    for (int i=f; i<m-1; i++){
        matrix[i]=realloc(matrix[i], n[i+1]*sizeof(double));
        for (int j=0; j<n[i+1]; j++){
             matrix[i][j]=matrix[i+1][j];
        }
    }
    free(matrix[m]);
    return 0;
}

//Выводим измененную матрицу
int print_mat(FILE* output, double** matrix, int m, int* n){
    for(int i=0; i<m; i++){
       for(int j=0; j<n[i]; j++){
           fprintf(output, "%f ", matrix[i][j]);
       }
       fprintf(output, "\n");
    }
    return 0;
}


int autotest1(void){
    int p;
    double** arr;
    int m=2;
    int n[2];
    n[0]=3;
    n[1]=2;
    arr=(double**)malloc(2*sizeof(double*));
    arr[0]=(double*)malloc(2*sizeof(double));
    arr[1]=(double*)malloc(2*sizeof(double));
    arr[0][0]=1.0;
    arr[0][1]=1.5;
    arr[1][0]=2.0;
    arr[1][1]=1.0;
    p=search(m, n, arr);
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
    double** arr;
    int m=2;
    int n[2];
    n[0]=2;
    n[1]=2;
    arr=(double**)malloc(2*sizeof(double*));
    arr[0]=(double*)malloc(2*sizeof(double));
    arr[1]=(double*)malloc(2*sizeof(double));
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

