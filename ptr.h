#ifndef PTR_H
#define PTR_H
#include <stdlib.h>
#include <stdio.h>




typedef struct inode {
    int val;
    struct inode* next;
} inode;


inode* createNode(inode*, int);

void swapp(int* a, int* b) {
    
    printf("\nFrom inside the function scope: a = %p, b = %p", a, b);
    int* temp = a; 
    a = b;
    b = temp;
    printf("\nFrom inside the function scope (after swap): a = %p, b = %p", a, b);
    return;

}

void swappp(int** a, int** b) {
    printf("\nFrom inside the function scope: a = %p, b = %p", a, b);
    int* temp = *a; 
    *a = *b;
    *b = temp;
    printf("\nFrom inside the function scope (after swap): a = %p, b = %p", a, b);
    return;
}


void mod(int* a, int v) {
    *a = v;
    return;
}


inode* createNode(inode* i, int v) {
   if (i != NULL) {
    inode* p = malloc(sizeof(*i));
    i->next = p;
    p->val = v;
    return p;
   } else {return NULL;} 
}









#endif