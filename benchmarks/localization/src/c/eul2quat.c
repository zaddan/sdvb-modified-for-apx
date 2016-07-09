/********************************
Author: Sravanthi Kota Venkata
********************************/

#include <stdio.h>
#include <stdlib.h>
#include "localization.h"

F2D* eul2quat(F2D* angle)
{
    F2D *ret;
    F2D *x, *y, *z;
    int k, i, j;
    int rows, cols;

    rows = angle->height;
    cols = angle->width;

    x = fDeepCopyRange(angle, 0, angle->height, 0, 1);
    y = fDeepCopyRange(angle, 0, angle->height, 1, 1);
    z = fDeepCopyRange(angle, 0, angle->height, 2, 1);

    ret = fSetArray(x->height, 4, 0);
    
    for(i=0; i<rows; i++)
    {
        float xi, yi, zi;
        k = 0;
        xi = asubsref(x,i);
        yi = asubsref(y,i);
        zi = asubsref(z,i);

        float tempVar[8];
        //subsref(ret,i,k) = cos(xi/2)*cos(yi/2)*cos(zi/2)+sin(xi/2)*sin(yi/2)*sin(zi/2);
        tempVar[0] = cos(xi/2)*cos(yi/2); //MultiplicationOp
        tempVar[0] = tempVar[0]*cos(zi/2); //MultiplicationOp
        tempVar[1] =  sin(xi/2)*sin(yi/2); //MultiplicationOp
        tempVar[1] = tempVar[1]*sin(zi/2); //MultiplicationOp
        subsref(ret,i,k) = tempVar[0] + tempVar[1]; //AdditionOp
        k++;
        
        //subsref(ret,i,k) = sin(xi/2)*cos(yi/2)*cos(zi/2)-cos(xi/2)*sin(yi/2)*sin(zi/2);
        tempVar[2] = sin(xi/2)*cos(yi/2); //MultiplicationOp
       tempVar[2] = tempVar[2]*cos(zi/2); //MultiplicationOp 
        tempVar[3] =  cos(xi/2)*sin(yi/2); //MultiplicationOp
        tempVar[3] = tempVar[3]*sin(zi/2); //MultiplicationOp
        subsref(ret,i,k) = tempVar[2] - tempVar[3]; //AdditionOp
        k++;
        
        //subsref(ret,i,k) = cos(xi/2)*sin(yi/2)*cos(zi/2)+sin(xi/2)*cos(yi/2)*sin(zi/2);
        tempVar[4] = cos(xi/2)*sin(yi/2); //MultiplicationOp
        tempVar[4] = tempVar[4] * cos(zi/2); //MultiplicationOp
        tempVar[5] =  sin(xi/2)*cos(yi/2); //MultiplicationOp
        tempVar[5] = tempVar[5]*sin(zi/2); //MultiplicationOp
        subsref(ret,i,k) = tempVar[4] + tempVar[5]; //AdditionOp
        k++;
        
        
        //subsref(ret,i,k) = cos(xi/2)*cos(yi/2)*sin(zi/2)-sin(xi/2)*sin(yi/2)*cos(zi/2);
        tempVar[6] = cos(xi/2)*cos(yi/2); //MultiplicationOp
        tempVar[6] = tempVar[6] * sin(zi/2); //MultiplicationOp
        tempVar[7] =  sin(xi/2)*sin(yi/2); //MultiplicationOp
        tempVar[7] = tempVar[7]*cos(zi/2); //MultiplicationOp
        subsref(ret,i,k) = tempVar[6] - tempVar[7]; //AdditionOp
    }

    fFreeHandle(x);
    fFreeHandle(y);
    fFreeHandle(z);

    return ret;
}



