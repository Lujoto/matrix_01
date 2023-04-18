#include "rot.h"


int main() {



    //double a[3] = {0.0, 1.0, 0.0}; 
    //double* temp = rot3Dx(a, PI/3);
    //temp = rot3Dz(temp, PI/6);

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






//FILE* pipe = popen("gnuplot -persist", "w");

    //fprintf(pipe, "set terminal jpeg\n");
    //fprintf(pipe, "set datafile sep \',\'\n");
    //fprintf(pipe, "set xrange [-3:3]\n");
    //fprintf(pipe, "set yrange [-2:2]\n");
    //fprintf(pipe, "set zrange [-3:3]\n");
    //fprintf(pipe, "set style function lp\n");
    //fprintf(pipe, "set dgrid3d\n");
    //fprintf(pipe, "set contour surface\n");
    //fprintf(pipe, "set cntrparam bspline\n");
    //fprintf(pipe, "set output \"rot.jpeg\"\n");
    ////fprintf(pipe, "splot \"rotResults.csv\" using 1:2:3\n");
    //fprintf(pipe, "splot cos(x)*sin(y)\n");
    //fprintf(pipe, "exit\n");
//pclose(pipe);








    return 0;
}