#ifndef PR_3
#define PR_3

int heigth (FILE* input);
int* length (FILE* input, m);
double** make_mat (int m, int* n, FILE* input);
int search (int m, int* n, double** matrix);
int del_string(double** matrix, int f, int m, int* n);
int print_mat(FILE* output, double** matrix, int m, int* n);
int autotest1(void);
int autotest2(void);

#endif
