/********************************
Author: Sravanthi Kota Venkata
********************************/


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "globals.h"
#include <fstream>
#define CHECK
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



#include "texture.h"

int WIDTHin,HEIGHTin;
F2D *target, *result;
int WIDTH,HEIGHT;
int localx, localy,targetin=0;
int *atlas;
//int *xloopin, *yloopin;
int *xloopout, *yloopout;

int  main(int argc, char **argv)
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

    
    params* data;
    I2D *im;
    F2D* image;
    unsigned int *start, *end, *elapsed;

    data = malloc(sizeof(params));
    im = parse_flags(argc, argv);
    image = fiDeepCopy(im);
    init_params(data);

    start = photonStartTiming();
    create_texture(image, data);
    end = photonEndTiming();
    elapsed = photonReportTiming(start, end);

#ifdef CHECK
{
    int ret=0;
#ifdef GENERATE_OUTPUT
    fWriteMatrix(result, argv[1]);
#endif
    ret = fSelfCheck(result, argv[1], 1.0);
    if(ret < 0)
        printf("Error in Texture Synthesis\n");
}
#endif
    photonPrintTiming(elapsed);
    
    iFreeHandle(im);
    fFreeHandle(image);
    free(start);
    free(end);
    free(elapsed);
    free(data);

    fFreeHandle(target);
    fFreeHandle(result);
    free(atlas);
//    free(xloopout);
//    free(yloopout);
    
    //--- calc energy and writing it to a file 
    float energy_value_aggreagate = 0;
    for (int i =0; i<add_long_long_energy_counters.size(); i++) {
        energy_value_aggreagate += add_long_long_energy_counters[i]*add_long_long_energy_vals[i];
        energy_value_aggreagate += add_long_int_energy_counters[i]*add_long_int_energy_vals[i];
        energy_value_aggreagate += add_int_int_energy_counters[i]*add_int_int_energy_vals[i];
        energy_value_aggreagate += add_float_float_energy_counters[i]*add_float_float_energy_vals[i];
        energy_value_aggreagate += mul_long_long_energy_counters[i]*mul_long_long_energy_vals[i];
        energy_value_aggreagate += mul_long_int_energy_counters[i]*mul_long_int_energy_vals[i];
        energy_value_aggreagate += mul_int_int_energy_counters[i]*mul_int_int_energy_vals[i];
        energy_value_aggreagate += mul_float_float_energy_counters[i]*mul_float_float_energy_vals[i];
    }
    
    ofstream energy_result;
    energy_result.open((resultFolderName + "/energy_result.txt").c_str());
    //energy_result<<energy_value<<endl; 
    energy_result<<energy_value_aggreagate<<endl; 
    //cout <<"EN value:"<<energy_value<<endl<<std::flush; 
    cout <<"EN value with counters: " <<energy_value_aggreagate<<endl; 
    energy_result.close();

    exit(0);
	return 0;
}

I2D* parse_flags(int argc, char ** argv)
{
    int i, tsx,tsy;
    I2D* image;
    char fileNm[256];

    sprintf(fileNm, "%s/%s", argv[1], argv[4]);
    image = readImage(fileNm);
    WIDTHin = image->width;
    HEIGHTin = image->height;

    localx = 3;
    localy = 3;

#ifdef test
    WIDTH = WIDTHin*2;
    HEIGHT = HEIGHTin*2;
    localx = 2;
    localy = 2;
#endif
#ifdef sim_fast
    WIDTH = WIDTHin*2;
    HEIGHT = HEIGHTin*2;
    localx = 3;
    localy = 3;
#endif
#ifdef sim
    WIDTH = WIDTHin*3;
    HEIGHT = HEIGHTin*3;
    localx = 2;
    localy = 2;
#endif
#ifdef sqcif
    WIDTH = WIDTHin*6;
    HEIGHT = HEIGHTin*6;
    localx = 2;
    localy = 2;
#endif
#ifdef qcif
    WIDTH = WIDTHin*10;
    HEIGHT = HEIGHTin*10;
    localx = 2;
    localy = 2;
#endif
#ifdef cif
    WIDTH = WIDTHin*10;
    HEIGHT = HEIGHTin*10;
    localx = 3;
    localy = 3;
#endif
#ifdef vga
    WIDTH = WIDTHin*20;
    HEIGHT = HEIGHTin*20;
    localx = 3;
    localy = 3;
#endif
#ifdef fullhd
    WIDTH = WIDTHin*20;
    HEIGHT = HEIGHTin*20;
    localx = 15;
    localy = 15;
#endif
#ifdef wuxga
    WIDTH = WIDTHin*20;
    HEIGHT = HEIGHTin*20;
    localx = 5;
    localy = 5;
#endif
    printf("Input size\t\t- (%dx%d)\n", HEIGHTin, WIDTHin);

//    xloopin = malloc(2*WIDTHin*sizeof(int));
//    yloopin = malloc(2*HEIGHTin*sizeof(int));
//
//    for(i=-WIDTHin/2;i<WIDTHin+WIDTHin/2;i++)
//    {
//        arrayref(xloopin,i+WIDTHin/2) = (WIDTHin+i)%WIDTHin;
//    }
//
//    for(i=-HEIGHTin/2;i<HEIGHTin+HEIGHTin/2;i++)
//    {
//        arrayref(yloopin,i+HEIGHTin/2) = (HEIGHTin+i)%HEIGHTin;
//    }
//    xloopin += WIDTHin/2; yloopin += HEIGHTin/2;

    result = fMallocHandle(1,HEIGHT*WIDTH);
    target = fMallocHandle(1, WIDTH*HEIGHT);
 
    atlas = malloc(2*WIDTH*HEIGHT*sizeof(int));
    xloopout = malloc(2*WIDTH*sizeof(int));
    yloopout = malloc(2*HEIGHT*sizeof(int));
    
    for(i=-WIDTH/2;i<WIDTH+WIDTH/2;i++)
    {
        arrayref(xloopout,i+WIDTH/2) = (WIDTH+i)%WIDTH;
    }
    for(i=-HEIGHT/2;i<HEIGHT+HEIGHT/2;i++)
    {
        arrayref(yloopout,i+HEIGHT/2) = (HEIGHT+i)%HEIGHT;
    }
    xloopout += WIDTH/2; yloopout += HEIGHT/2;

    if (result == NULL)
    {
        printf("Can't allocate %dx%d image. Exiting.\n",WIDTH,HEIGHT);
        exit(1);
    }

    return image;
}

void init_params(params *data)
{
    int i,j;
    data->localx = localx; data->localy = localy;
    data->widthin = WIDTHin; data->widthout = WIDTH;
    data->heightin = HEIGHTin; data->heightout = HEIGHT;


    if(!targetin)
    {
        for(i=0;i<data->heightout;i++)
        {
            for(j=0;j<data->widthout;j++)
            {
                asubsref(target,a(j,i,data->widthout)+R) = 1.0;
//                asubsref(target,a(j,i,data->widthout)+G) = 1.0;
//                asubsref(target,a(j,i,data->widthout)+B) = 1.0;
            }
        }
    }
 
    for(i=0;i<data->heightout;i++)
    {
        for(j=0;j<data->widthout;j++)
        {
            asubsref(result,a(j,i,data->widthout)+R)  = 1.0;
//            asubsref(result,a(j,i,data->widthout)+G)  = 1.0;
//            asubsref(result,a(j,i,data->widthout)+B)  = 1.0;
        }
    }
}
