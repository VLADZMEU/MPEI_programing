#include <stdio.h>
#include "functions.h"

int main()
{
    float **A, **B, **C;
    float *R;
    float a;

    int mA, nA, mB, nB, mC, nC;
    int i, kR = 0;

    FILE *fp = fopen("1.txt", "r");
    FILE *out = fopen("output.txt", "w");

    fscanf(fp, "%d %d %d %d %d %d %f",
        &mA, &nA, &mB, &nB, &mC, &nC, &a);

    A = (float**)malloc(mA * sizeof(float*));
    B = (float**)malloc(mB * sizeof(float*));
    C = (float**)malloc(mC * sizeof(float*));

    for (i = 0; i < mA; i++)
        VvodVect(&A[i], nA, fp);

    for (i = 0; i < mB; i++)
        VvodVect(&B[i], nB, fp);

    for (i = 0; i < mC; i++)
        VvodVect(&C[i], nC, fp);

    fclose(fp);

    R = (float*)malloc((mA + mB + mC) * sizeof(float));

    ObrabotkaMatrix(A, mA, nA, a, R, &kR, out);
    ObrabotkaMatrix(B, mB, nB, a, R, &kR, out);
    ObrabotkaMatrix(C, mC, nC, a, R, &kR, out);

    FreeMemoryVector(A, mA);
    FreeMemoryVector(B, mB);
    FreeMemoryVector(C, mC);

    free(R);

    fclose(out);

    return 0;
}