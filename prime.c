#include "prime.h"
#include <stdlib.h>
#include <stdio.h>

#define N 100
#define K 1

int main() {


//int *p = factors(10, K);
size_t t = 4;
int *p = alloc(t);

/*for (int i = 0; i < K; i++) {
        printf(" %d ", p[i] );
}*/

free(p);

printf("%cthe size of int is %lu %cthe size of int* is %lu%c", 
        '\n', sizeof(int), '\n', sizeof(int*), '\n');

/*  for (int i = 0; i < N; i++) {
        if (isPrime(i)) {
           printf(" %d ", i);
        }
    } */
}