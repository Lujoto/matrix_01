#include "prime.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 100
#define K 1

int main() {


//int *p = factors(10, K);
size_t t = 1;
//int *p = factors(24, t);

int j = 100;
int l = 12;
int d = 8;
int f = 18;
int m = 9;

bool q = isCoprime(j, l);

printf("the two ints %s coprime. \n", q ? "are" : "are not");



//for (int i = 0; p[i] != 0; i++) {
 //       printf(" %d ", p[i]);
//}


/*for (int i = 0; i < sizeof(p)/sizeof(*p); i++) {
        sum = p[i];
        printf(" %d ", sum );
        }
*/

//free(p);

/*printf("%cthe size of int is %lu %cthe size of int* is %lu%c", 
        '\n', sizeof(int), '\n', sizeof(int*), '\n');
*/
/*  for (int i = 0; i < N; i++) {
        if (isPrime(i)) {
           printf(" %d ", i);
        }
    } */
}