/********************************
Author: Sravanthi Kota Venkata
********************************/
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "globals.h"
extern hw_ac **myOp;   
using namespace std;

#include "mser.h"
#define min(a,b) (a<b)?a:b
#define max(a,b) (a>b)?a:b

int main(int argc, char* argv[])
{
    // Added by Behzad for apxation 
    string resultFolderName; 
    string resultFileName; 
    string operatorFileName;
    resultFolderName= "/home/local/bulkhead/behzad/usr/local/apx_tool_chain/generated_text";
    resultFileName = "/home/local/bulkhead/behzad/usr/local/apx_tool_chain/generated_text/csource_output_folder/csource_output0.txt";
    operatorFileName = "operator_sample.txt";
    string resultFileNameCompleteAddress = resultFileName;
    ofstream resultFile;

    resultFile.open(resultFileNameCompleteAddress.c_str(), ios_base::app);
    assign_global_variables(resultFolderName, operatorFileName);
    //end of Added by Behzad
    int which_image;
    int i, j, k;
    I2D *idx;
    I2D *I;
    I2D *It;
    int rows=196, cols=98;
    int minVal = 1000;
    int maxVal = -1000;
    int lev = 10;

    unsigned int* start, *endC, *elapsed;
    char im1[100], im2[100];
    if(argc < 2)
    {
        printf("We need input image path\n");
        return -1;
    }

    sprintf(im1, "%s/1.bmp", argv[1]);

    I = readImage(im1);
    rows = I->height;
    cols = I->width;

    It = readImage(im1);

    k = 0;
    for(i=0; i<cols; i++)
    {
        for(j=0; j<rows; j++)
        {
            asubsref(It,k++) = subsref(I,j,i);
        }
    }
    
    start = photonStartTiming();
    idx = mser(It, 2);
    endC = photonEndTiming();
    elapsed = photonReportTiming(start, endC);

    printf("Input size\t\t- (%dx%d)\n", rows, cols);
    writeMatrix_to_output(idx, (char*) resultFileName.c_str());
#ifdef CHECK   
    /** Self checking - use expected.txt from data directory  **/
    {
        int tol, ret=0;
        tol = 1;
#ifdef GENERATE_OUTPUT
        writeMatrix(idx, argv[1]);
#endif
        ret = selfCheck(idx, argv[1], tol);
        if (ret == -1)
            printf("Error in MSER\n");
    }
    /** Self checking done **/
#endif    
    photonPrintTiming(elapsed);
   
    free(start); 
    free(endC); 
    free(elapsed); 
    iFreeHandle(idx);
    iFreeHandle(I);
    iFreeHandle(It);
    
    return 0;
}

