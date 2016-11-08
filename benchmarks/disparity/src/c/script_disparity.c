/********************************
Author: Sravanthi Kota Venkata
********************************/

#include <stdio.h>
#include <stdlib.h>
#include "disparity.h"
#include <iostream>
#include "globals.h"
#include <fstream>
#define CHECK_1
extern hw_ac **myOp;   
using namespace std;

extern long double energy_value;
extern vector<int> add_long_long_energy_counters;
extern vector<int> add_long_int_energy_counters;
extern vector<int> add_int_int_energy_counters;
extern vector<int> add_float_float_energy_counters;

extern vector<int> mul_long_long_energy_counters;
extern vector<int> mul_long_int_energy_counters;
extern vector<int> mul_int_int_energy_counters;
extern vector<int> mul_float_float_energy_counters;

extern vector<float> add_long_long_energy_vals;
extern vector<float> add_long_int_energy_vals;
extern vector<float> add_int_int_energy_vals;
extern vector<float> add_float_float_energy_vals;

extern vector<float> mul_long_long_energy_vals;
extern vector<float> mul_long_int_energy_vals;
extern vector<float> mul_int_int_energy_vals;
extern vector<float> mul_float_float_energy_vals;




int main(int argc, char* argv[])
{
    
    // Added by Behzad for apxation 
    string resultFolderName; 
    string resultFileName; 
    string operatorFileName;
    
    //string exe_annex; 
    cout<<"here we go ok"<< argv[3]<<endl;
    std::string exe_annex(argv[3]);
    cout<<"goftam behet"<<exe_annex<<endl;
    resultFolderName= "/home/local/bulkhead/behzad/usr/local/apx_tool_chain/generated_text";
    resultFileName = "/home/local/bulkhead/behzad/usr/local/apx_tool_chain/generated_text/csource_output_folder/csource_output"+exe_annex+".txt";
    operatorFileName = "operator_sample" + exe_annex + ".txt";
    string resultFileNameCompleteAddress = resultFileName;
    ofstream resultFile;

    resultFile.open(resultFileNameCompleteAddress.c_str(), ios_base::app);
    assign_global_variables(resultFolderName, operatorFileName);
    //end of Added by Behzad

    
    
    int rows = 32;
    int cols = 32;
    I2D *imleft, *imright, *retDisparity;

    unsigned int *start, *endC, *elapsed;
    
    int i, j;
    char im1[200], im2[200], timFile[200];
    int WIN_SZ=8, SHIFT=64;
    FILE* fp;
    
    if(argc < 2)
    {
        printf("We need input image path and output path\n");
        return -1;
    }
    printf("getting exe\n"); 
     
    printf("%s\n", argv[3]);
    
    //std::string first_input(argv[4]);
    //std::string second_input(argv[5]);

//    sprintf(im1, "%s/1.bmp", argv[1]);
 //   sprintf(im2, "%s/2.bmp", argv[1]);
      
    sprintf(im1, "%s/%s", argv[1], argv[4]);
    sprintf(im2, "%s/%s", argv[1], argv[5]);

    cout<<im1<<endl;
    cout<<im2<<endl;

    imleft = readImage(im1);
    imright = readImage(im2);

    rows = imleft->height;
    cols = imleft->width;
    printf("=============================>\n");
    printf("here is the rwo size %d\n", rows);
    printf("here is the col size %d\n", cols);
#ifdef test
    WIN_SZ = 2;
    SHIFT = 1;
#endif
#ifdef sim_fast
    WIN_SZ = 4;
    SHIFT = 4;
#endif
#ifdef sim
    WIN_SZ = 4;
    SHIFT = 8;
#endif

    start = photonStartTiming();
    retDisparity = getDisparity(imleft, imright, WIN_SZ, SHIFT);
    endC = photonEndTiming();

    printf("Input size\t\t- (%dx%d)\n", rows, cols);
    writeMatrix_to_output(retDisparity, (char*) resultFileName.c_str());
#ifdef CHECK_1
    /** Self checking - use expected.txt from data directory  **/
    {
        int tol, ret=0;
        tol = 2;
#ifdef GENERATE_OUTPUT
        writeMatrix(retDisparity, argv[1]);
#endif
        ret = selfCheck(retDisparity, argv[1], tol);
        if (ret == -1)
            printf("Error in Disparity Map\n");
    }
    /** Self checking done **/
#endif

    elapsed = photonReportTiming(start, endC);
    photonPrintTiming(elapsed);
    
    iFreeHandle(imleft);
    iFreeHandle(imright);
    iFreeHandle(retDisparity);
    free(start);
    free(endC);
    free(elapsed);
    
    
    //--- calc energy and writing it to a file 
    int energy_value_aggreagate = 0;
    for (int i =0; i<add_long_long_energy_counters.size(); i++) {
        energy_value_aggreagate += add_long_long_energy_counters[i]*int(add_long_long_energy_vals[i]*10000*.3);
        energy_value_aggreagate += add_long_int_energy_counters[i]*int(add_long_int_energy_vals[i]*.3*1000);
        energy_value_aggreagate += add_int_int_energy_counters[i]*int(add_int_int_energy_vals[i]*.3*1000);
        energy_value_aggreagate += add_float_float_energy_counters[i]*int(add_float_float_energy_vals[i]*.3*1000);
        energy_value_aggreagate += mul_long_long_energy_counters[i]*int(mul_long_long_energy_vals[i]*1000);
        energy_value_aggreagate += mul_long_int_energy_counters[i]*int(mul_long_int_energy_vals[i]*1000);
        energy_value_aggreagate += mul_int_int_energy_counters[i]*int(mul_int_int_energy_vals[i]*1000);
        energy_value_aggreagate += mul_float_float_energy_counters[i]*int(mul_float_float_energy_vals[i]*1000);
    }

    ofstream energy_result;
    energy_result.open((resultFolderName + "/energy_result.txt").c_str());
    //energy_result<<energy_value<<endl; 
    energy_result<<energy_value_aggreagate<<endl; 
    //cout <<"EN value:"<<energy_value<<endl<<std::flush; 
    cout <<"EN value with counters: " <<energy_value_aggreagate<<endl; 
    energy_result.close();

    
    cout<<"end of DISPARITY"<<endl;
    return 0;
}
