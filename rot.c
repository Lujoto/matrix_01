#include "rot2.h"

#define ANTENNA_ROM_PLOT
//#define ROLLED
//#define ELEC_LIMITS
//#define REF_POINTS
#define ROM_TRANSFORM
#define MECHANICAL_LIMIT_CIRCLE
#define SCAN
#define SCAN_START 0
#define SCAN_END 10
#define ORIGIN
//#define SWITCH_TRANSFORM_ORDER
#define MECHANICAL_LIMIT 64.3
#define ELECTRICAL_LIMIT 64.3
#define EL 60
#define AZ 30
#define TO_RAD .017453292519943 
#define MAX_MECH_AZ 60
#define MAX_MECH_EL 60
#define STEP_DEG 1.25



int main() {

double a[3] = {1.0,0.0,0.0};
  
//Origin FILE input
#ifdef ORIGIN
    FILE* origin = fopen("origin.txt", "w");
    fprintf(origin, "%lf,%lf,%lf\n", 0.0, 0.0, 0.0);
    fclose(origin);
#endif

//Reference points file
#ifdef REF_POINTS
FILE* reference_points = fopen("reference_points.txt", "w");
 double *ref1 =  rot3Dz(rot3Dy(a, -PI/3), PI/6);
 double *ref2 =  rot3Dz(rot3Dy(a, PI/3), -PI/6);
 double *ref3 =  rot3Dy(rot3Dz(a, PI/6), -PI/3);
 double *ref4 =  rot3Dy(rot3Dz(a, PI/3), -PI/6);
 double *ref5 =  rot3Dy(rot3Dz(a, PI/3), -PI/6);

 //fprintf(reference_points, "%lf,%lf,%lf\n", ref1[0], ref1[1], ref1[2]);
 //fprintf(reference_points, "%lf,%lf,%lf\n", ref2[0], ref2[1], ref2[2]);
 //fprintf(reference_points, "%lf,%lf,%lf\n", ref3[0], ref3[1], ref3[2]);
 //fprintf(reference_points, "%lf,%lf,%lf\n", ref4[0], ref4[1], ref4[2]);
 //fprintf(reference_points, "%lf,%lf,%lf\n", ref5[0], ref5[1], ref5[2]);
 fclose(reference_points);
#endif

//Original orientation Range of motion plot, 
//with either Mechanical or Electrical Limits.
#ifdef ANTENNA_ROM_PLOT
    FILE* antenna = fopen("antenna.txt", "w");
    //double b[3] = {1.0, 0.0, 0.0}; // unit vector in the +X direction 
    for (double i = -MAX_MECH_AZ*TO_RAD; i < MAX_MECH_AZ*TO_RAD; i+=STEP_DEG*TO_RAD) {
        for (double j = -MAX_MECH_EL*TO_RAD; j < MAX_MECH_EL*TO_RAD; j+=STEP_DEG*TO_RAD) {
            double b[3] = {1.0, 0.0, 0.0};
            #ifdef ROLLED
                rot3Dy(rot3Dz(b, j), i); // extrinsic y after z 
                #else
                rot3Dz(rot3Dy(b, i), j); // extrinsic 30 z after 60 y (or intrinsic 60 y after 30 z)
            #endif 
            #ifdef ELEC_LIMITS
                    if (sqrt(i*i+j*j) < ELECTRICAL_LIMIT*TO_RAD) {
                        fprintf(antenna, "%lf,%lf,%lf\n",b[0], b[1], b[2]);
                    }
                #else 
                    if (angbet(b, a) < MECHANICAL_LIMIT) {
                        fprintf(antenna, "%lf,%lf,%lf\n",b[0], b[1], b[2]);
                    }
                #endif
        }
    }
    fclose(antenna);
#endif

// Antenna limit circle
#ifdef MECHANICAL_LIMIT_CIRCLE
    FILE* mech_lim_circle = fopen("mech_lim_circle.txt", "w");
    for (double i = 0.0; i < 2*PI; i+=PI/90) {
        double b[3] = {1.0, 0.0, 0.0};
        double* temp = rot3Dx(rot3Dy(b, MECHANICAL_LIMIT*TO_RAD), i);
        fprintf(mech_lim_circle, "%lf,%lf,%lf\n", temp[0], temp[1], temp[2]);
    }
    fclose(mech_lim_circle);
#endif

// scan from 0 to 30
#ifdef SCAN
    FILE* scan = fopen("scan.txt", "w");
        for (double i = SCAN_START*TO_RAD; i < SCAN_END*TO_RAD; i+=PI/180) {

            double b[3] = {1.0, 0.0, 0.0};
            rot3Dz(b, i);
            fprintf(scan, "%lf,%lf,%lf\n", b[0], b[1], b[2]);
        }
    fclose(scan);
#endif

// rotations of the antenna surface 
#ifdef ROM_TRANSFORM
    FILE* rom_transform = fopen("rom_transform.txt", "w"); 
    antenna = fopen("antenna.txt", "r");
                while (!feof(antenna)) {

                    double buffer[3] = {0.0,0.0,0.0};
                    fscanf(antenna, "%lf,%lf,%lf\n", &buffer[0], &buffer[1], &buffer[2]);
                    if (buffer[2]>0) {
                       #ifdef SWITCH_TRANSFORM_ORDER
                        rot3Dy(rot3Dz(buffer, AZ*TO_RAD), EL*TO_RAD);
                        fprintf(rom_transform, "%lf,%lf,%lf\n", buffer[0], buffer[1], buffer[2]); 
                        #else
                        rot3Dz(rot3Dy(buffer, EL*TO_RAD), AZ*TO_RAD);
                        fprintf(rom_transform, "%lf,%lf,%lf\n", buffer[0], buffer[1], buffer[2]); 
                        #endif
                    }
                }
    fclose(rom_transform);
    fclose(antenna);

#endif 


    


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
    fprintf(pipe, "set view 90,90\n");
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
    fprintf(pipe, "set output \"rot2.pdf\"\n");
    fprintf(pipe, "set multiplot\n");


    #ifdef ANTENNA_ROM_PLOT
    fprintf(pipe, "splot \"antenna.txt\" using 1:2:3 w p pt 7 ps 0.20 lt rgb \"grey\"\n");
    #endif
    #ifdef MECHANICAL_LIMIT_CIRCLE
    fprintf(pipe, "splot \"mech_lim_circle.txt\" using 1:2:3 w p pt 12 ps 0.35 lt rgb \"purple\"\n");
    #endif
    #ifdef ROM_TRANSFORM
    fprintf(pipe, "splot \"rom_transform.txt\" using 1:2:3 w p pt 6 ps 0.25 lt rgb \"green\"\n");
    #endif
    #ifdef ORIGIN
    fprintf(pipe, "splot \"origin.txt\" using 1:2:3 w p pt 7 ps 0.55 lt rgb \"red\"\n");
    #endif
    #ifdef SCAN
    fprintf(pipe, "splot \"scan.txt\" using 1:2:3 w p pt 6 ps 0.75 lt rgb \"blue\"\n");
    #endif

    fprintf(pipe, "set nomultiplot\n");




   fprintf(pipe, "exit\n");





pclose(pipe);



    return 0;
}