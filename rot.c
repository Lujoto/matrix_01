#include "rot.h"

#define MECHANICAL_LIMIT 64.3
#define MAX_ANTENNA_ANGLE_RAD 1.122
#define ELECTRICAL_LIMIT_RAD 1.122
#define EL 60
#define AZ 30
#define TO_RAD .017453292519943 
#define MAX_MECH_AZ 60
#define MAX_MECH_EL 60
#define STEP_DEG 1

//#define ROLLED
//#define ELEC_LIMITS
#define ROM_TRANSFORM
#define MECHANICAL_LIMIT_CIRCLE
#define SCAN
#define SCAN_AZ 20
#define SCAN_EL 0
#define ORIGIN


int main() {


    double a[3] = {1.000, 0.0, 0.0}; 
    //double* temp = rot3Dx(a, PI/3);
    //temp = rot3Dz(temp, PI/6);




    FILE* antenna = fopen("antenna.txt", "w");
    FILE* reference_points = fopen("reference_points.txt", "w");
    FILE* mech_lim_circle = fopen("mech_lim_circle.txt", "w");
    FILE* rom_transform = fopen("rom_transform.txt", "w");
    FILE* origin = fopen("origin.txt", "w");
    FILE* scan = fopen("scan.txt", "w");

  
//Origin FILE input
#ifdef ORIGIN
fprintf(origin, "%lf,%lf,%lf\n", 0.0, 0.0, 0.0);
#endif

//Reference points file
 double *ref1 = rot3Dz(rot3Dy(a, -PI/3), PI/6);
 double *ref2 =  rot3Dz(rot3Dy(a, PI/3), -PI/6);
 double *ref3 =  rot3Dy(rot3Dz(a, PI/6), -PI/3);
 double *ref4 =  rot3Dy(rot3Dz(a, PI/3), -PI/6);
 double *ref5 =  rot3Dy(rot3Dz(a, PI/3), -PI/6);

 //fprintf(reference_points, "%lf,%lf,%lf\n", ref1[0], ref1[1], ref1[2]);
 //fprintf(reference_points, "%lf,%lf,%lf\n", ref2[0], ref2[1], ref2[2]);
 //fprintf(reference_points, "%lf,%lf,%lf\n", ref3[0], ref3[1], ref3[2]);
 //fprintf(reference_points, "%lf,%lf,%lf\n", ref4[0], ref4[1], ref4[2]);
 //fprintf(reference_points, "%lf,%lf,%lf\n", ref5[0], ref5[1], ref5[2]);


//Original orientation Range of motion plot, 
//with either Mechanical or Electrical Limits.
    double b[3] = {1.0, 0.0, 0.0}; // unit vector in the +X direction 
    for (double i = -MAX_MECH_AZ*TO_RAD; i < MAX_MECH_AZ*TO_RAD; i+=STEP_DEG*TO_RAD) {
        for (double j = -MAX_MECH_EL*TO_RAD; j < MAX_MECH_EL*TO_RAD; j+=STEP_DEG*TO_RAD) {
            #ifdef ROLLED
                double* temp = rot3Dy(rot3Dz(b, j), i); // extrinsic y after z 
                #else
                double* temp = rot3Dz(rot3Dy(b, i), j); // extrinsic 30 z after 60 y (or intrinsic 60 y after 30 z)
            #endif 
            #ifdef ELEC_LIMITS
                    if (sqrt(i*i+j*j) < ELECTRICAL_LIMIT_RAD) {
                        fprintf(antenna, "%lf,%lf,%lf\n",temp[0], temp[1], temp[2]);
                    }
                #else 
                    if (angbet(temp, b) < MECHANICAL_LIMIT) {
                        fprintf(antenna, "%lf,%lf,%lf\n",temp[0], temp[1], temp[2]);
                    }
                #endif
                
        }
    }

// Antenna limit circle
#ifdef MECHANICAL_LIMIT_CIRCLE
    for (double i = 0.0; i < 2*PI; i+=PI/90) {
        double* temp = rot3Dx(rot3Dy(a, 1.122247), i);
        fprintf(mech_lim_circle, "%lf,%lf,%lf\n", temp[0], temp[1], temp[2]);

    }
#endif

// scan from 0 to 30
#ifdef SCAN
    for (double i = 0.0; i < PI/6; i+=PI/180) {
        double* temp = rot3Dz(a, i);
        double* temp2 = rot3Dy(rot3Dz(a, SCAN_AZ*TO_RAD), i);
        fprintf(scan, "%lf,%lf,%lf\n", temp2[0], temp2[1], temp2[2]);
        //fprintf(scan, "%lf,%lf,%lf\n", temp2[0], temp2[1], temp2[2]);
    }
#endif

// rotations of the antenna surface 
#ifdef ROM_TRANSFORM
fclose(antenna);
fopen("antenna.txt", "r");
        double buffer[3] = {0.0,0.0,0.0};
            while (!feof(antenna)) {
                fscanf(antenna, "%lf,%lf,%lf\n", &buffer[0], &buffer[1], &buffer[2]);
                if (buffer[2]>0) {
                    double* temp1 = rot3Dy(buffer, EL*TO_RAD);  
                    double* temp = rot3Dz(temp1, AZ*TO_RAD);
                    fprintf(rom_transform, "%lf,%lf,%lf\n", temp[0], temp[1], temp[2]); 
                }
            }
#endif 


    fclose(antenna);
    fclose(mech_lim_circle);
    fclose(reference_points);
    fclose(rom_transform);
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

    fprintf(pipe, "set terminal pdf size 9,9 background rgb \"black\" \n");
    fprintf(pipe, "set datafile sep \',\'\n");
    fprintf(pipe, "set view 80,70\n");
    fprintf(pipe, "set xrange [-1:1]\n");
    fprintf(pipe, "set yrange [-1:1]\n");
    fprintf(pipe, "set zrange [-1:1]\n");
    fprintf(pipe, "set xlabel \"X - Roll \" tc rgb \'white\'\n");
    fprintf(pipe, "set border lc rgb \'white\'\n");
    fprintf(pipe, "set ylabel \"Y - El \" tc rgb \'white\'\n");
    fprintf(pipe, "set zlabel \"Z - Az \" tc rgb \'white\'\n");
    //fprintf(pipe, "set style function lp\n");
    //fprintf(pipe, "set dgrid3d\n"); //idk what this does but it screwed me on a spherical surface
    //fprintf(pipe, "set contour surface\n");
    //fprintf(pipe, "set cntrparam bspline\n");
    fprintf(pipe, "set output \"rot_g.pdf\"\n");
    fprintf(pipe, "set multiplot\n");

    fprintf(pipe, "splot \"antenna.txt\" using 1:2:3 w p pt 7 ps 0.25 lt rgb \"grey\"\n");
    //fprintf(pipe, "splot \"antenna_rolled.txt\" using 1:2:3 w p pt 7 ps 0.2 lt rgb \"grey\"\n");
    fprintf(pipe, "splot \"mech_lim_circle.txt\" using 1:2:3 w p pt 12 ps 0.35 lt rgb \"purple\"\n");
    //fprintf(pipe, "splot \"reference_points.txt\" using 1:2:3 w p pt 6 ps 0.35 lt rgb \"red\"\n");
    fprintf(pipe, "splot \"rom_transform.txt\" using 1:2:3 w p pt 6 ps 0.25 lt rgb \"green\"\n");
    //fprintf(pipe, "splot \"blue.txt\" using 1:2:3 w p pt 6 ps 0.25 lt rgb \"cyan\"\n");
    //fprintf(pipe, "splot \"red.txt\" using 1:2:3 w p pt 6 ps 0.25 lt rgb \"cyan\"\n");
    fprintf(pipe, "splot \"origin.txt\" using 1:2:3 w p pt 7 ps 0.55 lt rgb \"red\"\n");
    fprintf(pipe, "splot \"scan.txt\" using 1:2:3 w p pt 6 ps 0.75 lt rgb \"blue\"\n");



    fprintf(pipe, "set nomultiplot\n");




   fprintf(pipe, "exit\n");





pclose(pipe);



    return 0;
}