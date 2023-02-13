#ifndef PRIME_
#define PRIME_
#include <stdlib.h> 
#include <stdbool.h>
#include <math.h> 

// coprime: find all smaller numbers that share no common factors. "Relatively Prime"
int* coprimes(int a, size_t n) {

    int* p = malloc(sizeof(int)*n);

    for (int i = 2; i < a; i++) {
    
    }

    return p;

}

// find the factors of a number, provide a size to allocate.
int* factors(int a, size_t n) {
    int *p = malloc(sizeof(int) * n);
    int c = 0;
    for (int i = 1; i < a; i++) {
        if (c > n) {
            p = (int*) realloc(p, sizeof(int)*(c));
        }
        if (a%i == 0) {
           p[c] = i;
           c++; 
        }


    }
   
    //int *l = (int*) realloc (p, sizeof(int)*c);

    return p;
}

// return true if a and b are coprime. 
bool isCoprime(int a, int b) {
    
}

// return true if arg is prime, false if not. 
bool isPrime(int a) {
    if (a%2 == 0)   {
        return false;   
    } else {
        for (int j = 3; j < (a/2); j++) { 
            if (a%j == 0) { return false;   } 
        } return true; 
    } 
}













#endif