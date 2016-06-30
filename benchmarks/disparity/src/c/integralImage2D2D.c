/********************************
Author: Sravanthi Kota Venkata
********************************/

#include <stdio.h>
#include <stdlib.h>
#include "disparity.h"
#include <assert.h>

#include "globals.h"
extern hw_ac **myOp;   




void integralImage2D2D(F2D* SAD, F2D* integralImg)
{
    int nr, nc, i, j;
    
    nr = SAD->height;
    nc = SAD->width;
    
    for(i=0; i<nc; i++)
        subsref(integralImg,0,i) = subsref(SAD,0,i);
    
    for(i=1; i<nr; i++)
        for(j=0; j<nc; j++)
        {
#ifdef APX
            subsref(integralImg,i,j) = myOp[2]->calc(subsref(integralImg, (i-1), j), subsref(SAD,i,j)); //AdditionOp
#else 
            subsref(integralImg,i,j) = subsref(integralImg, (i-1), j) + subsref(SAD,i,j); 
#endif        
        }

    for(i=0; i<nr; i++)
        for(j=1; j<nc; j++)
        
#ifdef APX
            subsref(integralImg,i,j) = myOp[3]->calc(subsref(integralImg, i, (j-1)),  subsref(integralImg,i,j)); //AdditionOp
#else
            subsref(integralImg,i,j) = subsref(integralImg, i, (j-1)) + subsref(integralImg,i,j);
#endif
    return;
    
}
