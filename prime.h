#ifndef PRIME_
#define PRIME_
#include <stdlib.h> 
#include <stdbool.h>
#include <math.h>
#include <stdio.h>  

#define N 100

// coprime: find all smaller numbers that share no common factors. "Relatively Prime"
int* coprimes(int a, size_t n) {

    int* p = malloc(sizeof(int)*n);

    for (int i = 2; i < a; i++) {
    
    }

    return p;

}

// find the factors of a number, provide a size to allocate.
int* factors(int a, size_t n) {
    int *p = malloc(sizeof(*p) * n);
    size_t c = 0;
    for (int i = 1; i <= (a/2); i++) {
        if (c >= n) {
            p = realloc(p, (c+2) * sizeof(*p)); // c+1 is necessary, c+2 is used for 0 termination below. 
            // you can assume the block of memory is 0-terminated, but you can ensure this by padding.
        }
        // if a % i == 0, add the factor to the array, and increment the number of factors
        if (a%i == 0) {
           p[c] = i; // ***getting an invalid write size 4 here. 
           c++;
        }
    }
    p[c] = 0;
    return p;
}

// return true if a and b are coprime. 
bool isCoprime(int a, int b) {

    printf(" %d and %d are being compared... \n", a, b);

    int* af = factors(a, N);
    int* bf = factors(b, N);

    for (size_t j = 1; af[j] != 0; j++) {
        for (size_t k = 1; bf[k] != 0; k++) {
            if (af[j] == bf[k]) {
                return false;
            }
        }
    }

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

// trying to figure out how realloc/malloc works. 
// 1. don't use casts, unless you are using a c++ compiler, even then do more research .
// 2. using sizeof(type) is not necessary, and forces you to repeat yourself. Use the dereferenced
//      pointer which will point to the allocated memory: int* p = malloc(sizeof(*p)*size_t)); 
//      this also means if you change the type of the pointer, you won't have to modify the malloc 
//      argument. 
// 3. sizeof(int) = 4, sizeof(int*) = 8. Why?  int* is an address. on 64-bit machines, an address
//      is 8 integer digits. 
// 4. you can realloc a pointer to itself, or to another pointer. 
// 

int* alloc(size_t a) {
    int* p = malloc(sizeof(*p)*a);
    for (int i = 0; i < a+1; i++) { 
        p[i] = i;
        printf(" %d ", p[i]);
    }

    printf("   size of int* %c %lu %c", '\n', sizeof(int), '\n');

    //p = (int*)realloc(p, a+1);
    int* j = realloc(p, sizeof(int)*(a+1));

    for (int i = 0; i < a+2; i++) {
        j[i] = i;
        printf(" %d ", j[i]);
    }       

    printf("%c", '\n');


    return p;
}










#endif