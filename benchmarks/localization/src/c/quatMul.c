/********************************
Author: Sravanthi Kota Venkata
********************************/

#include <stdio.h>
#include <stdlib.h>
#include "localization.h"

F2D* quatMul(F2D* a, F2D* b)
{
    int ra, ca, rb, cb;
    F2D *ret;
    int i, j, k=0;

    ra = a->height;
    ca = a->width;

    rb = b->height;
    cb = b->width;

    ret = fSetArray(ra, 4, 0);

    j = 0;
    for(i=0; i<ra; i++)
    {
        k = 0;
        float ai0, ai1, ai2, ai3;
        float bj0, bj1, bj2, bj3;

        ai0 = subsref(a,i,0);
        ai1 = subsref(a,i,1);
        ai2 = subsref(a,i,2);
        ai3 = subsref(a,i,3);
        
        bj0 = subsref(b,j,0);
        bj1 = subsref(b,j,1);
        bj2 = subsref(b,j,2);
        bj3 = subsref(b,j,3);
        
        float tempVar[16]; 
        //subsref(ret,i,k++) = ai0*bj0 - ai1*bj1 - ai2*bj2 - ai3*bj3;
        tempVar[0] = ai0*bj0; //MultiplicationOp
        tempVar[1] = ai1*bj1; //MultiplicationOp
        tempVar[2] = ai2*bj2; //MultiplicationOp
        tempVar[3] = ai3*bj3; //MultiplicationOp
        subsref(ret,i,k) =  tempVar[0] - tempVar[1]; //AdditionOp
        subsref(ret,i,k) = subsref(ret,i,k)  - tempVar[2]; //AdditionOp
        subsref(ret,i,k) = subsref(ret,i,k)  - tempVar[3]; //AdditionOp
        k++;


        //subsref(ret,i,k++) = ai0*bj1 + ai1*bj0 + ai2*bj3 - ai3*bj2;
        tempVar[4] =  ai0*bj1; //MultiplicationOp
        tempVar[5] =  ai1*bj0;  //MultiplicationOp
        tempVar[6] = ai2*bj3; //MultiplicationOp
        tempVar[7] = ai3*bj2; //MultiplicationOp
        
        subsref(ret,i,k) =  tempVar[4] + tempVar[5]; //AdditionOp
        subsref(ret,i,k) = subsref(ret,i,k)  + tempVar[6]; //AdditionOp
        subsref(ret,i,k) = subsref(ret,i,k)  - tempVar[7]; //AdditionOp
        k++;
        
        //subsref(ret,i,k++) = ai0*bj2 - ai1*bj3 + ai2*bj0 + ai3*bj1;
        tempVar[8] = ai0*bj2; //MultiplicationOp
        tempVar[9] = ai1*bj3; //MultiplicationOp
        tempVar[10] = ai2*bj0; //MultiplicationOp
        tempVar[11] = ai3*bj1; //MultiplicationOp
        subsref(ret,i,k) =  tempVar[8] - tempVar[9]; //AdditionOp 
        subsref(ret,i,k) = subsref(ret,i,k)  + tempVar[10]; //AdditionOp
        subsref(ret,i,k) = subsref(ret,i,k)  + tempVar[11]; //AdditionOp
        k++;
        
        //subsref(ret,i,k++) = ai0*bj3 + ai1*bj2 - ai2*bj1 + ai3*bj0;
        tempVar[12] =  ai0*bj3; //MultiplicationOp
        tempVar[13] = ai1*bj2; //MultiplicationOp
        tempVar[14] = ai2*bj1; //MultiplicationOp
        tempVar[15] = ai3*bj0; //MultiplicationOp
        subsref(ret,i,k) =  tempVar[12] + tempVar[13]; //AdditionOp
        subsref(ret,i,k) = subsref(ret,i,k)  - tempVar[14]; //AdditionOp
        subsref(ret,i,k) = subsref(ret,i,k) + tempVar[15]; //AdditionOp
        k++;
        
        if(rb == ra)
            j++;
    }

    return ret;
}





