//Среднее арифмитеческое где мин положительеых

#include <stdio.h>
#include "function.h"

int main()
{
    float *A,*B,*C;
    int nA,nB,nC;
    int kA,kB,kC;
    int kmA,kmB,kmC;

    
    FILE *fp=fopen("1.txt","r");
    FILE *out=fopen("output.txt","w");

    fscanf(fp, "%i %i %i", &nA, &nB, &nC);

    VvodVect(&A,nA,fp);
    VvodVect(&B,nB,fp);
    VvodVect(&C,nC,fp);

    fclose(fp);

    kA=CountNegative(A,nA);
    kB=CountNegative(B,nB);
    kC=CountNegative(C,nC);

    ViewSum(A,nA,kA,B,nB,kB,C,nC,kC,out,0);

    kmA=Countpositive(A,nA);
    kmB=Countpositive(B,nB);
    kmC=Countpositive(C,nC);

    ViewSum(A,nA,kmA,B,nB,kmB,C,nC,kmC,out,1);

    FreeMemoryVector(&A);
    FreeMemoryVector(&B);
    FreeMemoryVector(&C);

    fclose(out);

    return 0;
}