#include "rot.h"


int main() {



    double a[3] = {0.0, 1.0, 0.0}; 
    //double* temp = rot3Dx(a, PI/3);
    //temp = rot3Dz(temp, PI/6);

//neat, this works. Can consolidate the rotation functions now, maybe pass
//the desired axis of rotation as an argument
//still need to figure out if this is about a fixed axis or intrinsic
//rotations. 
//    double* temp = rot3Dx(rot3Dz(a, PI/3), PI/6);
    
    for(int i = 0; i < 3; i++) {
        printf("%s\n", "rotation temp");
        printf("%lf\n\n", temp[i]);
    } 



    printf("\n%lf is the angle between \n", angbet(temp, a));




    free(temp);





    return 0;
}