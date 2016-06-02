/********************************
Author: Sravanthi Kota Venkata
********************************/

#include <stdio.h>
#include <stdlib.h>
#include "sdvbs_common.h"
#include <iostream>
using namespace std;

void writeMatrix_to_output(I2D* input, char* inpath)
{
    FILE* fp;
    int rows,cols, i, j;
    fp = fopen(inpath, "w");

    rows = input->height;
    cols = input->width;

    fprintf(fp, "%s\n", "*********start******");
    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols; j++)
        {
            fprintf(fp, "%d\t", subsref(input, i, j));
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "%s\n", "*********end******");
    fclose(fp);
}



void writeMatrix(I2D* input, char* inpath)
{
    FILE* fp;
    char im[100];
    int rows,cols, i, j;

    sprintf(im, "%s/expected_C.txt", inpath);
    fp = fopen(im, "w");

    rows = input->height;
    cols = input->width;

    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols; j++)
        {
            fprintf(fp, "%d\t", subsref(input, i, j));
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}



