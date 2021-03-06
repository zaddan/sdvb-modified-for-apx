/********************************
Author: Sravanthi Kota Venkata
********************************/

#include <stdio.h>
#include <stdlib.h>
#include "disparity.h"
#include <assert.h>
#include "globals.h"
extern hw_ac **myOp;   

void computeSAD(I2D *Ileft, I2D* Iright_moved, F2D* SAD)
{
    int rows, cols, i, j, diff;
    
    rows = Ileft->height;
    cols = Ileft->width;

    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols; j++)
        {
#ifdef APX
            diff = myOp[0]->calc(subsref(Ileft,i,j), -1*subsref(Iright_moved,i,j)); //AdditionOp
            subsref(SAD,i,j) = myOp[1]->calc(diff,diff); //MultiplicationOp
#else
            diff = subsref(Ileft,i,j) -  subsref(Iright_moved,i,j); 
            subsref(SAD,i,j) = diff *diff; 
#endif
        }
    }
    
    return;
}

