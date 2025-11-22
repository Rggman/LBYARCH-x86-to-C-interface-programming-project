#include <stdio.h>

extern void asmfunc(int n, double* x1, double* x2, double* y1, double* y2, double* z);

int main() {
    double x1[] = {1.5, 4.0, 3.5, 2.0};
    double x2[] = {3.0, 2.5, 2.5, 1.0};
    double y1[] = {4.0, 3.0, 3.5, 3.0};
    double y2[] = {2.0, 2.5, 1.0, 1.5};
    double z[4];
    int n = 4;

    asmfunc(n, x1, x2, y1, y2, z);

    printf("Result:\n");
    for (int i = 0; i < n; i++)
        printf("The Answer is : %f\n", z[i]);

    return 0;
}
