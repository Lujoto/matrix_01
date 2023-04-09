#include "rot.h"


int main() {

    double a[2] = {1.0, 0.0}; 
    double* temp = rotx(a, PI); 
    
    for(int i = 0; i < 2; i++) {
        printf("%s\n", "rotation temp");
        printf("%lf\n\n", temp[i]);
    } 



    printf("\n%lf is the angle between \n", angbet(temp, a));




    free(temp);





    return 0;
}