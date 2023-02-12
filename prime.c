#include "prime.h"
#include <stdlib.h>
#include <stdio.h>

#define N 100

int main() {

    for (int i = 0; i < N; i++) {
        if (isPrime(i)) {
           printf(" %d ", i);
        }
    }
}