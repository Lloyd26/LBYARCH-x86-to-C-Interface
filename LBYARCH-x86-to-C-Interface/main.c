#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define EXP 24 // TO CHANGE for array sizing
#define A_VALUE 2.0
#define TRIAL_RUNS 30

extern void runSAXPYInC(int n, float a, float* x, float* y, float* z);
extern void runSAXPYInNASM(int, float, float*, float*, float*);

void generateInputArrays(int n, float** x, float** y);

// 1 run at a time
int main(void) {
    int n = pow(2, EXP);
    float a = A_VALUE;
    float* x, * y, * z;

    printf("n: 2^%d (%d)\n", EXP, n);
    printf("a: %lf\n\n", a);


    // Generate input arrays
    generateInputArrays(n, &x, &y);
    z = (float*)malloc(n * sizeof(float));

    // Safety check
    if (x == NULL || y == NULL || z == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    /* C KERNEL */
    printf("\033[1;32mLoading C Kernel ...\033[0m\n");

    // Trial Run SAXPY in C
    clock_t start, end;
    double time;
    start = clock();

    runSAXPYInC(n, a, x, y, z);

    end = clock();

    int i;
    for (i = 0; i < 10; i++) {
        printf("Z[%d] = %.2f\n", i, z[i]);
    }

    time = (double)(end - start) * 1000 / CLOCKS_PER_SEC; // converting to milliseconds
    printf("Trial Execution Time: \033[1;31m%lf milliseconds\033[0m\n", time);

    // Run atleast 30 times then avg
    double cAvgRun = 0;

    for (int i = 0; i < TRIAL_RUNS; i++) {
        double time;
        start = clock();

        runSAXPYInC(n, a, x, y, z);

        end = clock();
        time = (double)(end - start) * 1000 / CLOCKS_PER_SEC; // converting to milliseconds
        cAvgRun += time;
    }
    cAvgRun = cAvgRun / TRIAL_RUNS;
    printf("Average Execution Time: \033[1;31m%lf milliseconds\033[0m\n\n", cAvgRun);

    z = (float*)malloc(n * sizeof(float));

    /* NASM KERNEL */
    printf("\033[1;32mLoading NASM Kernel ...\033[0m\n");

    // Trial Run SAXPY in C
    start = clock();

    runSAXPYInNASM(n, a, x, y, z);

    end = clock();

    for (i = 0; i < 10; i++) {
        printf("Z[%d] = %.2f\n", i, z[i]);
    }

    time = (double)(end - start) * 1000 / CLOCKS_PER_SEC; // converting to milliseconds
    printf("Trial Execution Time: \033[1;31m%lf milliseconds\033[0m\n", time);

    // Run atleast 30 times then avg
    double nasmAvgRun = 0;

    for (int i = 0; i < TRIAL_RUNS; i++) {
        double time;
        start = clock();

        runSAXPYInNASM(n, a, x, y, z);

        end = clock();
        time = (double)(end - start) * 1000 / CLOCKS_PER_SEC; // converting to milliseconds
        nasmAvgRun += time;
    }
    nasmAvgRun = nasmAvgRun / TRIAL_RUNS;
    printf("Average Execution Time: \033[1;31m%lf milliseconds\033[0m\n\n", nasmAvgRun);




    // Free dynamically allocated memory
    free(x);
    free(y);
    free(z);

    return 0;
}

void generateInputArrays(int n, float** x, float** y) {
    *x = (float*)malloc(n * sizeof(float));
    *y = (float*)malloc(n * sizeof(float));

    if (*x == NULL || *y == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Generate input values for x and y arrays
    for (int i = 0; i < n; i++) {
        (*x)[i] = i + 1; // start with 1.0
        (*y)[i] = 11 + i; // start with 11.0
    }
}


