#ifndef ROT2_H
#define ROT2_H
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
double* rot3Dx(double*, double);
double* rot3Dy(double*, double);
double* rot3Dz(double*, double);



#endif