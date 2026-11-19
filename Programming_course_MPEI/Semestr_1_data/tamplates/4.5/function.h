#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void VvodVect(float **x, int nx, FILE *fp)
{
    *x = (float*)malloc(nx * sizeof(float));

    for (int i = 0; i < nx; i++)
    {
        fscanf(fp, "%f", &(*x)[i]);
    }
    return;
}


float Sum(float *x, int nx)
{
    float s=0;
    for (int i=0; i<nx; i++)
        s+=x[i];
    return s;
}

int CountNegative(float *x, int nx)
{
    int k=0;
    for (int i=0; i<nx; i++)
        if (x[i]<0) k++;
    return k;
}
int Countpositive(float *x, int nx)
{
    int k=0;
    for (int i=0; i<nx; i++)
        if (x[i]>0) k++;
    return k;
}
void ViewSum(float *A, int nA, int kA, float *B, int nB, int kB, float *C, int nC, int kC, FILE *out,bool type)
{
    int kmax=kA;
    if (type ==0){
        if (kB>kmax) kmax=kB;
        if (kC>kmax) kmax=kC;
    }
    else{
        if (kB<kmax) kmax=kB;
        if (kC<kmax) kmax=kC;
    }
    

    if (kA==kB || kA==kC || kB==kC)
    {
        if (kA==kB && kA==kC)
            fprintf(out,"A = B = C\n");
        else
        {
            if (kA==kB)
                fprintf(out,"A = B\n");
            else if (kA==kC)
                fprintf(out,"A = C\n");
            else if (kB==kC)
                fprintf(out,"B = C\n");
        }
    }
    else
    {
        if (kmax==0)
            fprintf(out,"No negative elements\n");
        else
        {
            if (kA==kmax)
                fprintf(out,"A mean = %f\n",Sum(A,nA)/nA);
            else if (kB==kmax)
                fprintf(out,"B mean = %f\n",Sum(B,nB)/nB);
            else if (kC==kmax)
                fprintf(out,"C mean = %f\n",Sum(C,nC)/nC);
        }
    }

    return;
}

void FreeMemoryVector(float **x)
{
    free(*x);
    *x=NULL;
}

#endif