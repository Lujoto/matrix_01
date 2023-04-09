#ifndef ROT_H
#define ROT_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 2
#define A 3
#define MX_2D 4
#define MX_3D 9
#define PI 3.14159

double* rotx(double*, double);
double* crm2(double);
double magn(double*);
double dotp(double*, double*);
double angbet(double*, double*);





//use size N to dot product two single dimension arrays
double dotp(double* p, double* v) {
    double ret = 0.0;
    for (size_t i = 0; i < N; i++) {
        ret += p[i]*v[i];
    }
    return ret;
}


double magn(double* vector) {
    //check for valid vector
    if (vector ==NULL ) {
        exit(EXIT_FAILURE);
    }
   //add up the squares of the components 
    double temp = 0.0;
    for (size_t i = 0; i < N; i++)  {
        temp += pow(vector[i], 2); //could change this to a single flop
    }
   //take the square root 
    double ret = sqrt(temp); 
    return ret;
}



double angbet(double* p, double* v) {
    double temp1 = dotp(p, v);
    double mag1 = magn(p)*magn(v);
    double res = acos(temp1/mag1);
    double res2 = 180*res/PI;
    return res2;

}


double* crm2(double th) {
    double* dd = (double*)malloc(sizeof(*dd)*MX_2D);
    dd[0] = cos(th);
    dd[1] = -1*sin(th);
    dd[2] = sin(th);
    dd[3] = cos(th);
    //dd[4] = NULL;
    return dd;
}    


double* rotx(double* v, double theta)    {
    if (v == NULL) {
        exit(EXIT_FAILURE);
    }

    double* rt = crm2(theta);
    double* temp = calloc(2, sizeof(*temp));

    for (int i = 0; i < MX_2D; i++) {
        temp[i/N] += rt[i]*v[i%N];  
    }

    v = temp;
    free(rt);
    return v;

}




#endif