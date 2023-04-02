#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ptr.h"



int main() {

inode* i = malloc(sizeof(*i));
i->val = 99;
i->next = NULL;

int x = 5;
int y = 8; 
int* a = &x;
int* b = &y;
int** c = &a;
int** d = &b;

printf("\nFrom outside the function scope: a = %p, b = %p", a, b);
swappp(c, d);
printf("\nFrom outside the function scope (after swap): a = %p, b = %p", a, b);

}