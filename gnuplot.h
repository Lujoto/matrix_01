#ifndef GNUPLOT_H
#define GNUPLOT_H
#include <stdio.h>
#include <stdlib.h>


FILE* createPipe() {
   FILE* pipe = popen("gnuplot -persist", "w"); 
   return pipe;
}


 FILE*  plotXY_csv(FILE* results, char *filename, char* fmt, char* xr, char* yr) {

    results = fopen("bTreeResults.csv", "r");
    FILE* pipe = popen("gnuplot -persist", "w");
                     fprintf(pipe, "set terminal dumb\n");
                     fprintf(pipe, "set datafile sep \',\'\n");
                     fprintf(pipe, "set xrange [%s]\n", xr);
                     fprintf(pipe, "set yrange [%s]\n", yr);
                     fprintf(pipe, "plot \"bTreeResults.csv\" using %s with lines\n", fmt);
                     fprintf(pipe, "exit\n");
    
    pclose(pipe);
    fclose(results);
    return results;

  }



#endif