#include "rot2.h"

//use size N to dot product two single dimension arrays
double dotp(double* p, double* v) {
    double ret = 0.0;
    for (size_t i = 0; i < A; i++) {
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
    for (size_t i = 0; i < A; i++)  {
        temp += pow(vector[i], 2); //could change this to a single flop
    }
   //take the square root 
    double ret = sqrt(temp); 
    return ret;
}



double angbet(double* p, double* v) { // arccos{ P dot Q / mag(P)*mag(Q) }
    double temp1 = dotp(p, v);
    double mag1 = magn(p)*magn(v);
    double res = acos(temp1/mag1);
    double res2 = 180*res/PI;
    return res2;

}


double* crm2(double th) {
    double dd[MX_2D];
    dd[0] = cos(th); dd[1] = -1*sin(th);
    dd[2] = sin(th); dd[3] = cos(th);
    return dd;
}    
    



//2D rotate a vector about x-axis
double* rotx(double* v, double th)    {
    if (v == NULL) {
        exit(EXIT_FAILURE);
    }
    double dd[MX_2D];
    dd[0] = cos(th); dd[1] = -1*sin(th);
    dd[2] = sin(th); dd[3] = cos(th);
 
    double temp[N] = {0,0,0};

    for (int i = 0; i < MX_2D; i++) {
        temp[i/N] += dd[i]*v[i%N];  
    }

    for (int i =0; i < N; i++) {
        v[i] = temp[i];
    }

    return v;

}

//3D rotation transformation about x-axis
double* rot3Dx(double *v, double th) {
    if (v == NULL) {
        exit(EXIT_FAILURE);
    }
    double dd[MX_3D]; 
    dd[0] = 1; dd[1] = 0;       dd[2] = 0;
    dd[3] = 0; dd[4] = cos(th); dd[5] = (-1)*sin(th);
    dd[6] = 0; dd[7] = sin(th); dd[8] = cos(th);


    double temp[A] = {0,0,0};

   for (int i = 0; i < MX_3D; i++) {
        temp[i/A] += dd[i]*v[i%A];  
    }

    for (int i = 0; i < A; i++) {
        v[i] = temp[i];
    }

    return v;

}


//3D rotation transformation about y-axis
double* rot3Dy(double *v, double th) { //double* 3D vector, double angle in rads. 
    if (v == NULL) {
        exit(EXIT_FAILURE);
    }

    double dd[MX_3D];
        dd[0] = cos(th);      dd[1] = 0;       dd[2] = sin(th);
        dd[3] = 0;            dd[4] = 1;       dd[5] = 0;
        dd[6] = (-1)*sin(th); dd[7] = 0;       dd[8] = cos(th);


    double temp[A] = {0,0,0};

    for (int i = 0; i < MX_3D; i++) {
        temp[i/A] += dd[i]*v[i%A];  
    }

    for(int i = 0; i < A; i++) {
        v[i] = temp[i];
    }
    
    return v;

}

//3D rotation transformation about z-axis
double* rot3Dz(double *v, double th) {
    if (v == NULL) {
        exit(EXIT_FAILURE);
    }
    double dd[MX_3D];
        dd[0] = cos(th); dd[1] = -1*sin(th);  dd[2] = 0;
        dd[3] = sin(th); dd[4] = cos(th);     dd[5] = 0;
        dd[6] = 0;       dd[7] = 0;           dd[8] = 1;
    
    double temp[3] = {0,0,0};

    for (int i = 0; i < MX_3D; i++) {
        temp[i/A] += dd[i]*v[i%A];  
    }
    for (int i = 0; i < A; i ++) {
        v[i] = temp[i];
    }
    
    return v;

}



