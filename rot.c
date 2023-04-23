#include "rot.h"

#define MAX_ANTENNA_ANGLE 64.3
#define MAX_ANTENNA_ANGLE_RAD 1.122

int main() {



    double a[3] = {1.000, 0.0, 0.0}; 
    //double* temp = rot3Dx(a, PI/3);
    //temp = rot3Dz(temp, PI/6);





    FILE* antenna = fopen("antenna.txt", "w");
    FILE* xyy = fopen("xyy.txt", "w");
    FILE* x = fopen("x.txt", "w");
    FILE* y = fopen("y.txt", "w");
    FILE* z = fopen("z.txt", "w");
    FILE* origin = fopen("origin.txt", "w");
    FILE* scan = fopen("scan.txt", "w");

  
//Origin FILE input
fprintf(origin, "%lf,%lf,%lf\n", 0.0, 0.0, 0.0);
//Reference points file
 double *ref1 = rot3Dz(rot3Dy(a, -PI/3), PI/6);
 double *ref2 =  rot3Dz(rot3Dy(a, PI/3), -PI/6);
 double *ref3 =  rot3Dy(rot3Dz(a, PI/6), -PI/3);
 double *ref4 =  rot3Dy(rot3Dz(a, PI/3), -PI/6);

 double *ref5 =  rot3Dy(rot3Dz(a, PI/3), -PI/6);

 //fprintf(x, "%lf,%lf,%lf\n", ref1[0], ref1[1], ref1[2]);
 //fprintf(x, "%lf,%lf,%lf\n", ref2[0], ref2[1], ref2[2]);
 //fprintf(x, "%lf,%lf,%lf\n", ref3[0], ref3[1], ref3[2]);
 //fprintf(x, "%lf,%lf,%lf\n", ref4[0], ref4[1], ref4[2]);
 //fprintf(x, "%lf,%lf,%lf\n", ref5[0], ref5[1], ref5[2]);



    for (double i = -PI/3; i < PI/3; i+=PI/120) {
        for (double j = -PI/3; j < PI/3; j+=PI/120) {
            double b[3] = {1.0, 0.0, 0.0};
            double* temp = rot3Dz(rot3Dy(b, i), j); // extrinsic 30 z after 60 y (or intrinsic 60 y after 30 z)
            double* temp2 = rot3Dy(rot3Dz(b, j), i); // extrinsic y after z 
            //double* temp2 = rot3Dx(temp, j); this is cool
            //printf("%lf - ", angbet(temp, b)); 
            if (angbet(temp, b) < MAX_ANTENNA_ANGLE) {
                fprintf(antenna, "%lf,%lf,%lf\n",temp[0], temp[1], temp[2]);
                fprintf(xyy, "%lf,%lf,%lf\n",temp2[0], temp2[1], temp2[2]);
                
                //printf("%lf,%lf,%lf\n", temp[0], temp[1], temp[2]); 
            }

        }
    }

// Antenna limit circle
    for (double i = 0.0; i < 2*PI; i+=PI/90) {
        double* temp = rot3Dx(rot3Dy(a, 1.122247), i);
        fprintf(y, "%lf,%lf,%lf\n", temp[0], temp[1], temp[2]);

    }

// scan from 0 to 30
    for (double i = 0.0; i < PI/6; i+=PI/180) {
        double* temp = rot3Dz(a, i);
        double* temp2 = rot3Dz(rot3Dy(a, -PI/3), i);
        fprintf(scan, "%lf,%lf,%lf\n", temp[0], temp[1], temp[2]);
        fprintf(scan, "%lf,%lf,%lf\n", temp2[0], temp2[1], temp2[2]);
    }

// rotations of the antenna surface 
fclose(antenna);
fopen("antenna.txt", "r");
        double buffer[3] = {0.0,0.0,0.0};
            while (!feof(antenna)) {
            fscanf(antenna, "%lf,%lf,%lf\n", &buffer[0], &buffer[1], &buffer[2]);
            //double* temp2 = rot3Dx(buffer, PI/2); // this rolls the antenna
           if (buffer[2] > 0) { 
            double* temp1 = rot3Dy(buffer, PI/3); // this 
            double* temp = rot3Dz(temp1, PI/6);
            fprintf(z, "%lf,%lf,%lf\n", temp[0], temp[1], temp[2]); }
        }    
        
            


    fclose(antenna);
    fclose(xyy);
    fclose(y);
    fclose(x);
    fclose(z);
    fclose(origin);
    fclose(scan);




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
    fprintf(pipe, "set view 90,90\n");
    fprintf(pipe, "set xrange [-1:1]\n");
    fprintf(pipe, "set yrange [-1:1]\n");
    fprintf(pipe, "set zrange [-1:1]\n");
    fprintf(pipe, "set xlabel \"X\"\n");
    fprintf(pipe, "set ylabel \"Y\"\n");
    fprintf(pipe, "set zlabel \"Z\"\n");
    //fprintf(pipe, "set style function lp\n");
    //fprintf(pipe, "set dgrid3d\n"); //idk what this does but it screwed me on a spherical surface
    //fprintf(pipe, "set contour surface\n");
    //fprintf(pipe, "set cntrparam bspline\n");
    fprintf(pipe, "set output \"rot.pdf\"\n");
    fprintf(pipe, "set multiplot\n");

    fprintf(pipe, "splot \"antenna.txt\" using 1:2:3 w p pt 7 ps 0.25 lt rgb \"purple\"\n");
    //fprintf(pipe, "splot \"xyy.txt\" using 1:2:3 w p pt 7 ps 0.2 lt rgb \"cyan\"\n");
    fprintf(pipe, "splot \"y.txt\" using 1:2:3 w p pt 12 ps 0.35 lt rgb \"purple\"\n");
    fprintf(pipe, "splot \"x.txt\" using 1:2:3 w p pt 6 ps 0.35 lt rgb \"red\"\n");
    fprintf(pipe, "splot \"z.txt\" using 1:2:3 w p pt 6 ps 0.15 lt rgb \"red\"\n");
    fprintf(pipe, "splot \"origin.txt\" using 1:2:3 w p pt 7 ps 0.55 lt rgb \"green\"\n");
    fprintf(pipe, "splot \"scan.txt\" using 1:2:3 w p pt 7 ps 0.35 lt rgb \"blue\"\n");



    fprintf(pipe, "set nomultiplot\n");




   fprintf(pipe, "exit\n");





pclose(pipe);



    return 0;
}