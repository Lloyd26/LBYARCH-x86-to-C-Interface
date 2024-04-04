#include <stdio.h>
#include <stdlib.h>

extern void runSAXPYInNASM(int, float, float*, float*, float*);

int main() {
	int n = 3;
	float A = 2.0;

	float* X = (float*) calloc(n, sizeof(float));
	float* Y = (float*) calloc(n, sizeof(float));
	float* Z = (float*) calloc(n, sizeof(float));

	X[0] = 1.0;
	X[1] = 2.0;
	X[2] = 3.0;

	Y[0] = 11.0;
	Y[1] = 12.0;
	Y[2] = 13.0;

	runSAXPYInNASM(n, A, X, Y, Z);

	int i;
	for (i = 0; i < n; i++) {
		printf("Z[%d] = %.1f\n", i, Z[i]);
	}

	return 0;
}