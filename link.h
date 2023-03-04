#ifndef LINK_H
#define LINK_H

#include <stdio.h> 
#include <math.h>
#include <stdlib.h>


// struct typedef //
typedef struct node {
int key;
struct node* next;
float contents;
} node;

// these are my global nodes I want to use in the node functions //
node *head = NULL;
node *current = NULL;

// PROTOTYPES //
void printlist(node*);
void insert(int, float);
void delete(node*);



// Print the list from the head to the tail //
void printlist(node* n) {
    while (n != NULL) {
        printf("(%d, %f)", n->key, n->contents);
        n = n->next;
    }
}

// Insert a node at the head of the list //
void insert(int key, float contents) {
   node *new = malloc(sizeof(*new)); 
   new->contents = contents;
   new->key = head->key+1;   
   new->next = head;
   head = new;
}



#endif