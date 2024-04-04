#include <stdio.h>
#include <stdlib.h>

void runSAXPYInC(int n, float a, float* x, float* y, float* z) {
    for (int i = 0; i < n; i++) {
        z[i] = a * x[i] + y[i];
        //printf("%dth run: %.1lf * %.1lf + %.1lf = %.1lf\n", i, a, x[i], y[i], z[i]); // Correctness check
    }
}