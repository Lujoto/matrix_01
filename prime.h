#ifndef PRIME_
#define PRIME_
#include <stdlib.h> 
#include <stdbool.h>
#include <math.h>
#include <stdio.h>  

#define N 100

// PROTOTYPES

int *reallocate(int*, size_t n);
int *factors(int, size_t);
bool isCoprime(int, int);
bool isPrime(int);

// coprime: find all smaller numbers that share no common factors. "Relatively Prime"
int* coprimes(int a, size_t n) {

    int* p = calloc(n, sizeof(int)); // if you use malloc here, valgrind will whine that 
    size_t c = 0;                   // you're using uninitialized memory. Use calloc to 
    for (int i = 2; i < a; i++) {   // set all blocks to 0. 

        if (isCoprime(i, a)) {
           p[c] = i; 
           c++;
        }

        if (c == n) { //this needs work
            n *= 2;
            p = reallocate(p, n);
        }
        
    }

    return p;

}


int* reallocate(int* p, size_t n)  {
    
        p = realloc(p, n * sizeof(*p)); 

        return p;
    }
 
    


// find the factors of a number, provide a size to allocate.
int* factors(int a, size_t n) {
    int *p = malloc(sizeof(*p) * n);
    size_t c = 0;
    for (int i = 1; i <= (a/2); i++) {
        if (c >= n) {
            p = realloc(p, (c+3) * sizeof(*p)); // c+1 is necessary, c+2 is used for 0 termination below. 
            // you can assume the block of memory is 0-terminated, but you can ensure this by padding.
        }
        // if a % i == 0, add the factor to the array, and increment the number of factors
        if (a%i == 0) {
           p[c] = i; 
           c++;
        }
    }
    p[c] = a; // add the number itself as a factor
    p[c+1] = 0; // zero termination
    return p;
}

// return true if a and b are coprime. 
bool isCoprime(int a, int b) {

    printf(" %d and %d are being compared... \n", a, b);

    int* af = factors(a, N); // we don't return these two pointers!!! these are never 
    int* bf = factors(b, N); // freed. Memory leak!

    for (size_t j = 1; af[j] != 0; j++) {
        for (size_t k = 1; bf[k] != 0; k++) {
            if (af[j] == bf[k]) {
                free(af);
                free(bf);
                return false;
            }
        }
    }
free(af);
free(bf);
return true;
        
}

// return true if arg is prime, false if not. 
bool isPrime(int a) {
    if (a%2 == 0)   {
        return false;   
    } else {
        for (int j = 3; j < (a/2); j++) { 
            if (a%j == 0) { return false; } 
        } return true; 
    } 
}

//          on malloc/realloc: 
// 1. don't use casts, unless you are using a c++ compiler, even then do more research .
// 2. using sizeof(type) is not necessary, and forces you to repeat yourself. Use the dereferenced
//      pointer which will point to the allocated memory: int* p = malloc(sizeof(*p)*size_t)); 
//      this also means if you change the type of the pointer, you won't have to modify the malloc 
//      argument. 
// 3. sizeof(int) = 4, sizeof(int*) = 8. Why?  int* is an address. on 64-bit machines, an address
//      is 8 integer digits. 
// 4. you can realloc a pointer to itself, or to another pointer. 
// 








#endif