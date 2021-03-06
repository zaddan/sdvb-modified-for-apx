/********************************
Author: Sravanthi Kota Venkata
********************************/

#include <stdio.h>
#include <stdlib.h>
#include "sift.h"
#include "globals.h"
#include <fstream>
extern hw_ac **myOp;   
using namespace std;
extern bool results_tainted;
//#define GENERATE_OUTPUT
#define CHECK
void normalizeImage(F2D* image)
{
	int i;
	int rows;
	int cols;
    int tempMin = 10000, tempMax = -1;
	rows = image->height;
	cols = image->width;

    for(i=0; i<(rows*cols); i++)
        if(tempMin > asubsref(image,i))
            tempMin = asubsref(image,i);

    for(i=0; i<(rows*cols); i++)
        asubsref(image,i) = asubsref(image,i) - tempMin;

    for(i=0; i<(rows*cols); i++)
        if(tempMax < asubsref(image,i))
            tempMax = asubsref(image,i);

    for(i=0; i<(rows*cols); i++)
        asubsref(image,i) = ( asubsref(image,i) / (tempMax+0.0) );
}

int main(int argc, char* argv[])
{
    
    // Added by Behzad for apxation 
    string resultFolderName; 
    string resultFileName; 
    string operatorFileName;
    
    
    std::string exe_annex(argv[3]);
    
    resultFolderName= "/home/local/bulkhead/behzad/usr/local/apx_tool_chain/generated_text";
    resultFileName = "/home/local/bulkhead/behzad/usr/local/apx_tool_chain/generated_text/csource_output_folder/csource_output"+exe_annex+".txt";
    
    operatorFileName = "operator_sample" + exe_annex + ".txt";
    string resultFileNameCompleteAddress = resultFileName;
    ofstream resultFile;

    resultFile.open(resultFileNameCompleteAddress.c_str(), ios_base::app);
    assign_global_variables(resultFolderName, operatorFileName);
    //end of Added by Behzad
    
    I2D* im;
    F2D *image;
    int rows, cols, i, j;
    F2D* frames;
    unsigned int* startTime, *endTime, *elapsed;    
    
    char imSrc[100];
    
    if(argc < 2)
    {
        printf("We need input image path\n");
        return -1;
    }
    printf("%s\n", argv[1]); 
    sprintf(imSrc, "%s/1.bmp", argv[1]);
    im = readImage(imSrc);
    image = fiDeepCopy(im);
    iFreeHandle(im);
    rows = image->height;
    cols = image->width;

    startTime = photonStartTiming();
    /** Normalize the input image to lie between 0-1 **/
	normalizeImage(image);
    /** Extract sift features for the normalized image **/
    frames = sift(image);
    
    if (results_tainted) {
        frames = fMallocHandle(4, 1);
        populate_matrix_with_infinity(frames);
        asubsref(frames, 3) = 1;
    }
    
    endTime = photonEndTiming();
    printf("Input size\t\t- (%dx%d)\n", rows, cols);
    writeMatrix_to_output(frames, (char*) resultFileName.c_str());


#ifdef CHECK   
    {
        int ret=0;
        float tol = 0.2;
#ifdef GENERATE_OUTPUT
        fWriteMatrix(frames, argv[1]);
#endif
        ret = fSelfCheck(frames, argv[1], tol);
        if (ret == -1)
            printf("Error in SIFT\n");
    }
#endif    

    elapsed = photonReportTiming(startTime, endTime);
    photonPrintTiming(elapsed);
    free(startTime);
    free(endTime);
    free(elapsed);

    fFreeHandle(frames);

    return 0;
}

