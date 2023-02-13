#include "prime.h"
#include <stdlib.h>
#include <stdio.h>

#define N 100
#define K 1

int main() {


int *p = factors(10, K);

for (int i = 0; i < K; i++) {
        printf(" %d ", p[i] );
}

free(p);

/*  for (int i = 0; i < N; i++) {
        if (isPrime(i)) {
           printf(" %d ", i);
        }
    } */
}