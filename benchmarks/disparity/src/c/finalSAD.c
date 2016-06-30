/********************************
Author: Sravanthi Kota Venkata
********************************/

#include <stdio.h>
#include <stdlib.h>
#include "disparity.h"
#include "globals.h"
#include <assert.h>
extern hw_ac **myOp;   

void finalSAD(F2D* integralImg, int win_sz, F2D* retSAD)
{
    int endR, endC;
    int i, j, k;
    
    endR = integralImg->height;
    endC = integralImg->width;
    
    k = 0;
    for(j=0; j<(endC-win_sz); j++)
    {
        for(i=0; i<(endR-win_sz); i++)
        {
            
#ifdef APX
            subsref(retSAD,i,j) = myOp[4]->calc(subsref(integralImg,(win_sz+i),(j+win_sz)), subsref(integralImg,(i+1) ,(j+1))); //AdditionOp
            subsref(retSAD,i,j) =  myOp[5]->calc(subsref(retSAD,i,j), -1*subsref(integralImg,(i+1),(j+win_sz))); //AdditionOp
            subsref(retSAD,i,j) = myOp[6]->calc(subsref(retSAD,i,j), -1*subsref(integralImg,(win_sz+i),(j+1))); //AdditionOp

#else
            //subsref(retSAD,i,j) = subsref(integralImg,(win_sz+i),(j+win_sz)) + subsref(integralImg,(i+1) ,(j+1)) - subsref(integralImg,(i+1),(j+win_sz)) - subsref(integralImg,(win_sz+i),(j+1));
            subsref(retSAD,i,j) = subsref(integralImg,(win_sz+i),(j+win_sz)) + subsref(integralImg,(i+1) ,(j+1));
            subsref(retSAD,i,j) =  subsref(retSAD,i,j) - subsref(integralImg,(i+1),(j+win_sz));
            subsref(retSAD,i,j) = subsref(retSAD,i,j)- subsref(integralImg,(win_sz+i),(j+1));
#endif
        }
    }

    return;
}

