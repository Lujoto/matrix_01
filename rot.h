#ifndef ROT_H
#define ROT_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define MX_2D 5

double* rotx(double*, double);
double* rv(double);

double* rv(double th) {
    double* dd = (double*)malloc(sizeof(*dd)*MX_2D);
    dd[0] = cos(th);
    dd[1] = -1*sin(th);
    dd[2] = sin(th);
    dd[3] = cos(th);
    //dd[4] = NULL;
    return dd;
}    


double* rotx(double* v, double theta)    {

    if (v = NULL) {
        exit(EXIT_FAILURE);
    }

    double* rt = rv(theta);

    for (int i = 0; i < MX_2D; i++) {
    v[i/2] += rt[i]*v[i/2];  
    }

    free(rt);

    return v;

}


#endif