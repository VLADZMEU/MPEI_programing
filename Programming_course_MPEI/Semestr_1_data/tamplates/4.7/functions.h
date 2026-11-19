#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
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

int ExistGreater(float *x, int nx, float a)
{
    int i = 0;
    int flag = 0;

    while (i < nx && flag == 0)
    {
        if (x[i] > a)
            flag = 1;

        i++;
    }

    return flag;
}

int ExistDop(float *x, int nx, float a)
{
    int i = 0;
    int flag = 0;

    while (i < nx && flag == 0)
    {
        if (x[i]>0)
            flag = 1;

        i++;
    }

    return flag;
}


int CountGreater(float *x, int nx, float a)
{
    int k = 0;

    for (int i = 0; i < nx; i++)
        if (x[i] > a )
            k++;

    return k;
}
int CountDop(float *x, int nx, float a)
{
    int k = 0;

    for (int i = 0; i < nx; i++)
        if (x[i]>0)
            k++;

    return k;
}

float SumGreater(float *x, int nx, float a)
{
    float s = 0;

    for (int i = 0; i < nx; i++)
        if (x[i] > a) 
            s += x[i];

    return s;
}

float SumDop(float *x, int nx, float a)
{
    float s = 0;

    for (int i = 0; i < nx; i++)
        if (x[i]>0)
            s += x[i];

    return s;
}

void VivodResult(float x, int flag, FILE *out)
{
    if (flag == 1)
        fprintf(out, "%f\n", x);
    else
        fprintf(out, "Anomaly: not found element\n");

    return;
}

void ObrabotkaMatrix(float **A, int m, int n, float a, float *R, int *kR, FILE *out)
{
    int i, k;

    for (i = 0; i < m; i++)
    {
        if (ExistGreater(A[i], n, a))
        {
            k = CountGreater(A[i], n, a);
            R[*kR] = SumGreater(A[i], n, a) / k;
            VivodResult(R[*kR], 1, out);
            (*kR)++;
        }
        else
            VivodResult(0, 0, out);
    }

    return;
}

void FreeMemoryVector(float **x, int nx)
{
    int i;
    for (i = 0; i < nx; i++)
        free(x[i]);

    free(x);
    return;
}

#endif