#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>

extern void asmfunc(int n, double* x1, double* x2, double* y1, double* y2, double* z);

void c_kernel(int n, double* x1, double* x2, double* y1, double* y2, double* z) {
    for (int i = 0; i < n; i++) {
        double diff_x = x2[i] - x1[i];
        double diff_y = y2[i] - y1[i];
        z[i] = sqrt((diff_x * diff_x) + (diff_y * diff_y));
    }
}

void initialize_vector(int n, double* vector) {
    for (int i = 0; i < n; i++) {
        // gives a random float between 0.0 and 10.0
        vector[i] = (double)(rand() % 100) / 10.0; 
    }
}

void display_ten(char* version, double* z) {
    printf("%s first 10 results:\n", version);
    for (int i = 0; i < 10; i++) {
        printf("Index %d: %.15lf\n", i, z[i]);
    }
    printf("\n\n");
}

int isCorrect(int n, double* z_c, double* z_asm) {
    int correct = 1;
    for (int i = 0; i < n; i++) {
        // give some tolerance for comparison due to possible floating point differences
        if (fabs(z_c[i] - z_asm[i]) > 0.001) {
            printf("Error: Not equal results\n");
            correct = 0;
            break;
        }
    }
    return correct;
}

int main() {
    // initialize constant values
    const int sizes[] = { 1 << 20, 1 << 24, 1 << 28 }; // 2^20, 2^24, 2^28 (2^30 is too large for some of our machines)
    const int iterations = 30;

    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        size_t bytes = n * sizeof(double); // size_t is usually used for memory sizes

        //allocate memory
        double* x1 = (double*)malloc(bytes);
        double* x2 = (double*)malloc(bytes);
        double* y1 = (double*)malloc(bytes);
        double* y2 = (double*)malloc(bytes);
        double* z_c = (double*)malloc(bytes); // result for C version
        double* z_asm = (double*)malloc(bytes); // result for assembly version

        // initialize vectors with random values
        initialize_vector(n, x1);
        initialize_vector(n, x2);
        initialize_vector(n, y1);
        initialize_vector(n, y2);
        
        if (s == 0) {
            printf("Input Size: 2^20\n", n);
        } else if (s == 1) {
            printf("Input Size: 2^24\n", n);
        } else {
            printf("Input Size: 2^28\n", n);
        }

        // time C version
        printf("Running C Kernel 30 times...\n");
        clock_t start_c = clock(); // returns # of clock ticks since program started
        for (int i = 0; i < iterations; i++) {
            c_kernel(n, x1, x2, y1, y2, z_c);
        }
        clock_t end_c = clock();
        double avg_time_c = ((double)(end_c - start_c) / CLOCKS_PER_SEC) / iterations;
        printf("Average C Time: %.5lf seconds\n", avg_time_c);

        // time x86-64 version
        printf("Running x86-64 Kernel 30 times...\n");
        clock_t start_asm = clock();
        for (int i = 0; i < iterations; i++) {
            asmfunc(n, x1, x2, y1, y2, z_asm);
        }
        clock_t end_asm = clock();
        double avg_time_asm = ((double)(end_asm - start_asm) / CLOCKS_PER_SEC) / iterations;
        printf("Average ASM Time: %.5lf seconds\n", avg_time_asm);

        if (isCorrect(n, z_c, z_asm)) {
            printf("Correctness Test: PASS\n");
        } else {
            printf("Correctness Test: FAIL\n");
        }

        display_ten("C", z_c);
        display_ten("ASM", z_asm);

        // free memory allocated
        free(x1); free(x2); free(y1); free(y2); free(z_c); free(z_asm);
    }
    
    return 0;
}
