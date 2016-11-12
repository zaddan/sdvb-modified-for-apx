/********************************
Author: Sravanthi Kota Venkata
********************************/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "globals.h"
#include <fstream>

extern hw_ac **myOp;   
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


using namespace std;



#include <stdio.h>
#include <stdlib.h>
#include "segment.h"

int main(int argc, char* argv[])
{
    // Added by Behzad for apxation 
    string resultFolderName; 
    string resultFileName; 
    string operatorFileName;
    
    //string exe_annex; 
    std::string exe_annex(argv[3]);
    //cout<<"exe_annex is :"<<exe_annex<<endl;
    resultFolderName= "/home/local/bulkhead/behzad/usr/local/apx_tool_chain/generated_text";
    resultFileName = "/home/local/bulkhead/behzad/usr/local/apx_tool_chain/generated_text/csource_output_folder/csource_output"+exe_annex+".txt";
    operatorFileName = "operator_sample" + exe_annex + ".txt";
    string resultFileNameCompleteAddress = resultFileName;
    ofstream resultFile;

    resultFile.open(resultFileNameCompleteAddress.c_str(), ios_base::app);
    assign_global_variables(resultFolderName, operatorFileName);
    //end of Added by Behzad


    
    float sigma = 0.6;
    float k = 4;
    int min_size = 10;
    char im1[256];
    int num_ccs[1] = {0};
    I2D *out;
    I2D* im;
    I2D* seg;
    unsigned int* start, *endC, *elapsed;
    int ret;

    if(argc < 2)
    {
        printf("We need input image path and output path\n");
        return -1;
    }

    sprintf(im1, "%s/%s", argv[1], argv[4]);
    im = readImage(im1);
    
    printf("Input size\t\t- (%dx%d)\n", im->height, im->width);

    start = photonStartTiming();
    seg = segment_image(im, sigma, k, min_size, num_ccs);
    endC = photonEndTiming();
    elapsed = photonReportTiming(start, endC);
    out = seg;

    writeMatrix_to_output(out, (char*) resultFileName.c_str());

#ifdef CHECK   
    /** Self checking - use expected.txt from data directory  **/
    {
        int ret=0;
        float tol = 0;
        
#ifdef GENERATE_OUTPUT
        writeMatrix(out, argv[1]);
#endif
 
    ret = selfCheck(out, argv[1], tol);
    if(ret < 0)
        printf("Error in Multi N Cut\n");
    }
#endif

    photonPrintTiming(elapsed);
  
    iFreeHandle(im); 
    free(start);
    free(endC);
    free(elapsed);
    iFreeHandle(seg);
    
    //--- calc energy and writing it to a file 
    float energy_value_aggreagate = 0;
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

    cout<<"end of multi_ncut"<<endl;    
     return 0;
}


