#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>

void distance_kernel_c(int n, float* x1, float* x2, float* y1, float* y2, float* z) {
    for (int i = 0; i < n; i++) {
        float diff_x = x2[i] - x1[i];
        float diff_y = y2[i] - y1[i];
        z[i] = sqrtf((diff_x * diff_x) + (diff_y * diff_y));
    }
}

int main() {
	// these inputs are just the same as those in the example provided in the specs
	float x1[] = {1.5, 4.0, 3.5, 2.0};
	float x2[] = {3.0, 2.5, 2.5, 1.0};
	float y1[] = {4.0, 3.0, 3.5, 3.0};
	float y2[] = {2.0, 2.5, 1.0, 1.5};
	float z[4];
	int n = 4;

	distance_kernel_c(n, x1, x2, y1, y2, z);

	printf("Result:\n");
	for (int i = 0; i < n; i++) {
		printf("%f\n", z[i]);
	}

	return 0;
}