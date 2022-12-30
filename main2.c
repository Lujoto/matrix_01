#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h> 
#include <memory.h>
#include <time.h> 


#define A 10


int main() {


int (*a) = malloc(sizeof(int)); // looks like these two lines are eq. 
int* b = malloc(sizeof(int)); // == ^

size_t num_chars = A;
char (*c) = (char*)malloc(sizeof(char)*num_chars);  



*a = 1;
*b = 1;

printf("%zu \n", sizeof(int));
printf("%p -  ", a);
printf("%p", &a);
printf("\n%d", *a);



clock_t start, stop;
time_t time_elapsed;

start = clock();


stop = clock(); 
printf("\n%f ---- %f", start*1e6, stop*1e6);
time_elapsed = difftime(stop, start);
printf("\n\n%f sec ", time_elapsed);

}