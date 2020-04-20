#include <stdio.h>
#include <stdlib.h>
#include "fun.h"

int main(void){
    int k, f, m, *n;
    double** matrix;
    FILE* input;
    FILE* output;
    input = fopen("data.dat", "r");
    output = fopen("data.res", "w");

    k=autotest1();
    if (k==1){
        return 1;
    }

    k=autotest2();
    if (k==1){
        return 1;
    }

    m=heigth(input);

    n=length(input, m);

    matrix=make_mat(m, n, input);

    f=search(m, n, matrix);
    if (f!=-1){
        k=del_string(matrix, f, m, n);
        m=m-1;
    }

    k=print_mat(output, matrix, m, n);

    fclose(input);
    fclose(output);
    for (int i=0; i<m; i++){
        free(matrix[i]);
    }
    free(matrix)
    return 0;
}
















