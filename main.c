
#define _POSIX_C_SOURCE 199309L
#include <assert.h> 
#include <math.h> 
#include <stdlib.h>
#include <stdio.h> 
#include <string.h> 
#include <time.h>
#include <stdint.h> 
#include <stddef.h>
#include <immintrin.h> 



#define A 1024
#define BLOCK_SIZE 4


#define FAST_01

uint64_t nanos() {
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
   // printf("\n %ld tv sec \n %ld tv nsec \n", start.tv_sec, start.tv_nsec);
    return (uint64_t)start.tv_sec*1e9 + (uint64_t)start.tv_nsec;
}

float a[A][A];
float b[A][A];
float c[A][A];
float t[A][A];


float A1[A*A] __attribute__((aligned (32)));
float B1[A*A] __attribute__((aligned (32)));
float R1[A*A] __attribute__((aligned (32)));

__m256 *Am = (__m256*)A1;
__m256 *Bm = (__m256*)B1;
__m256 *Rm = (__m256*)R1;












int main() {

// seed rand()
    srand(time(0));
    // init
    for (int i = 0; i < A; i++) {
            for (int j = 0; j < A; j++) {
            (a[i][j]) = (1e-9*rand());
            (b[i][j]) = (1e-9*rand());
    //       printf("%f\n",  (a[i][j]) );
        }
    }

    // multiply matrix: N^2 output cells w/ 2N compute each.
    double flop = A * A * 2.0 * A;
    double time_elapsed; 
    printf("%f GFLOP\n ", flop / 1e9);

    // make sure tile size is valid
    assert(A%BLOCK_SIZE == 0);

    // set up, start the timer
    uint64_t start, stop;
    start = nanos();

    // tiling test
    #ifndef FAST_01

    for (int i = 0; i < A; i+= BLOCK_SIZE) {
        for (int j = 0; j < A; j+=BLOCK_SIZE) {
            float tmp[BLOCK_SIZE][BLOCK_SIZE];
            
            for ( int y = 0; y < BLOCK_SIZE; y++) {
                for (int x = 0; x < BLOCK_SIZE; x++) {
                    float acc = 0.0;
                for (int k = 0; k < A; k++) {
                        acc += a[i+y][k]*b[j+x][k];
                } 
                tmp[y][x] = acc; 
                }
            }
        
        
        //store 
            for ( int y = 0; y < BLOCK_SIZE; y++) {
                for (int x = 0; x < BLOCK_SIZE; x++) {
            
            c[i+y][j+x] = tmp[y][x];
                
                }
            }         
        


        }
    }
    #else
    // define slow
    __m256 tc[BLOCK_SIZE];
    for (int by = 0; by < A; by += BLOCK_SIZE) {
        for (int bx = 0; bx < A; bx += BLOCK_SIZE) {
            __m256 tc[BLOCK_SIZE];
            for (int y = 0; y < BLOCK_SIZE; y++) {
                    __m256 tmp;
                    for (int k = 0; k < A; k++) {
                    tmp = __mm256_fmadd_ps(
                        Am[((by+y)*A)/8 + k],
                        Bm[(bx*A)/8 + k], tmp);

                    }          
            } 
        }
    }
 
    #endif

    // end the timer
    stop = nanos();

    // do the matrix multiplication (basic level, super slow. ~0.6 GFLOPS)
    for (int i = 0; i < A; i++) {
        for (int j = 0; j < A; j++) {
            float acc = 0.0;
            for (int k = 0; k < A; k++) {
                acc += a[i][k]*b[j][k]; // this assumes the matrix is transposed, i.e. [i][k], [j][k] instead of [i][k], [k][j]
            }
            t[i][j] = acc;

    // correctness check       
        if (abs(t[i][j] - c[i][j]) > 1e-3) {
                printf("mismatch");
                break;
                
        
        } else {

    //       printf("%f = %f\n", t[i][j], c[i][j]); 

        }

        }
    }



    // calculate time elapsed, GFLOP/S, and print
    time_elapsed = ((double)(stop - start)*1e-9);
    printf(" == Time Elapsed: %lf%c", time_elapsed, '\n');
    float gflops = flop / time_elapsed / 1e9;
    printf("%f  GFLOP/S\n", gflops);

}