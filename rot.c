#include "rot.h"

#define MAX_ANTENNA_ANGLE 64.3
#define MAX_ANTENNA_ANGLE_RAD 1.122

int main() {



    double a[3] = {1.0, 0.0, 0.0}; 
    //double* temp = rot3Dx(a, PI/3);
    //temp = rot3Dz(temp, PI/6);





    FILE* xyz = fopen("xyz.txt", "w");
    FILE* xyy = fopen("xyy.txt", "w");
    FILE* x = fopen("x.txt", "w");
  

    for (double i = -PI/3; i < PI/3; i+=PI/35) {
        for (double j = -PI/3; j < PI/3; j+=PI/35) {
            double b[3] = {1.0, 0.0, 0.0};
// you need the z component of the vector returned by the rotation operation
            double* temp = rot3Dy(rot3Dz(b, i), j); 
            double* temp2 = rot3Dz(rot3Dy(b, i), j);
            printf("%lf - ", angbet(temp, b)); 
            if (angbet(temp, b) < MAX_ANTENNA_ANGLE) {
                printf("%s\n", "printed this one");
                fprintf(xyz, "%lf,%lf,%lf\n",temp[0], temp[1], temp[2]);
                fprintf(xyy, "%lf,%lf,%lf\n",temp2[0], temp2[1], temp2[2]);
                
                //printf("%lf,%lf,%lf\n", temp[0], temp[1], temp[2]); 
            }
 
        }
    }

    for (double i = 0.0; i < 2*PI; i+=PI/90) {
        double* temp = rot3Dx(rot3Dy(a, 1.122247), i);
        fprintf(xyz, "%lf,%lf,%lf\n", temp[0], temp[1], temp[2]);

    }

    
        double* temp = rot3Dx(rot3Dy(a, PI/3), PI/6);
         
//    for (double i = 0.0; i < PI/3; i+=PI/180) {
        //for (double j = 0.0; j < PI/3; j+=PI/180) {
            //double b[3] = {1.0, 0.0, 0.0};
//// you need the z component of the vector returned by the rotation operation
            //double* temp = rot3Dy(rot3Dz(b, i), j);    
            //fprintf(xyz, "%lf,%lf,%lf\n",temp[0], temp[1], temp[2]);
            //printf("%lf,%lf,%lf\n", temp[0], temp[1], temp[2]); 
    ////        printf("%lf\n", magn(temp));



        //}
    //} 
                double *temp = rot3Dy(rot3Dz(a, PI/3), PI/3);

                printf("the angle between is: %lf\n", angbet(temp, a));




    fclose(xyz);
    fclose(xyy);





//neat, this works. Can consolidate the rotation functions now, maybe pass
//the desired axis of rotation as an argument
//still need to figure out if this is about a fixed axis or intrinsic
//rotations. 
    
    //for(int i = 0; i < 3; i++) {
        //printf("%s\n", "rotation temp");
        //printf("%lf\n\n", temp[i]);
    //} 

 //a^   FILE* f = fopen("rotResults.csv", "w");

    //for (double i = 0.0; i < PI; i+=(PI/50)) { 
        //double* temp = rot3Dx(rot3Dz(a, i), PI/3);
        //double t = angbet(temp, a);
        //fprintf(f, "%lf, %lf\n", i, t);
        //free(temp);
    //}



    //fclose(f);






FILE* pipe = popen("gnuplot -persist", "w");

    fprintf(pipe, "set terminal pdf size 9,9\n");
   // fprintf(pipe, "set terminal gif animate delay 5 loop 0 optimize\n");
    fprintf(pipe, "set datafile sep \',\'\n");
    fprintf(pipe, "set view 60,30\n");
    fprintf(pipe, "set xrange [0:1]\n");
    fprintf(pipe, "set yrange [-1:1]\n");
    fprintf(pipe, "set zrange [-1:1]\n");
    //fprintf(pipe, "set style function lp\n");
    //fprintf(pipe, "set dgrid3d\n"); //idk what this does but it screwed me on a spherical surface
    //fprintf(pipe, "set contour surface\n");
    //fprintf(pipe, "set cntrparam bspline\n");
    fprintf(pipe, "set output \"rot.pdf\"\n");
    fprintf(pipe, "set multiplot\n");

    fprintf(pipe, "splot \"xyz.txt\" using 1:2:3 lt rgb \"blue\"\n");
    fprintf(pipe, "splot \"xyy.txt\" using 1:2:3 lt rgb \"red\"\n");


    fprintf(pipe, "set nomultiplot\n");




   fprintf(pipe, "exit\n");





pclose(pipe);



    return 0;
}