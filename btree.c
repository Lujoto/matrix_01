
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>
#include "btree.h"
#include "gnuplot.h"


#define N 4012

int main() {


FILE *xl;

if ((xl = fopen("bTreeResults.csv", "w")) == NULL) {
    printf("error opening the file; \n");
    exit(-1);
}




srand(time(0));
time_t start, stop;


node* root = createNode(22101.0);

nanos(start);
for (int i = 0; i < N; i++) {
    insert(root, rand()/1e6);
}
for (int i = 0; i < N; i++) {

}

nanos(stop);

//printTree(root, 0);



//countTree
int* countBucket = calloc(100, sizeof(int));
countBucket = countTree(root, 0, countBucket);

char* s[20];
printf("\n%s", ":::LEVEL COUNT:::");
for (int i = 0; i < 100; i++) {
   printf("\n%d - %d", i, countBucket[i]);
   fprintf(xl, "\n%d,%d", i, countBucket[i]); 
}


//double time_el = (double)(stop-start)*1e-9;

//printf("\n\n time elapsed: %lf\n", time_el);

fclose(xl);

//FILE* pipe = popen("gnuplot -persist", "w");
//fprintf(pipe, "set terminal png\n");
//fprintf(pipe, "set datafile sep \',\'\n");
//fprintf(pipe, "set xrange [0:40]\n");
//fprintf(pipe, "set yrange [0:600]\n");
//fprintf(pipe, "plot \"bTreeResults.csv\" using 1:2 with lines\n");
//fprintf(pipe, "exit\n");
//pclose(pipe);



plotXY_csv(xl, "bTreeResults.csv", "2:1", "0:50", "0:500");





free(countBucket);
freeTree(root, 0);


}