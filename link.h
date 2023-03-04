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
node* insert(int, float);
void delete(int);



// Print the list from the head to the tail //
void printlist(node* n) {
    while (n != NULL) {
        printf("(%d, %f)", n->key, n->contents);
        n = n->next;
    }
}

// Insert a node at the head of the list //
node* insert(int key, float contents) {

   node *new = malloc(sizeof(*new)); 
   new->contents = contents;
   new->key = head->key+1;   
   new->next = head;
   head = new;
   return new;

}

void delete(int k) {
    if (head == NULL) {
        return; 
    }  
    node* curr = head;
    node* prev = NULL;  
    while (curr->next != NULL) {
        if (curr->key == k) {
            prev->next = curr->next; // link the previous and next nodes
            free(curr);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}
 
void freelist(node* h) {
    while (h->next != NULL) {
        node* curr = h; //point to the current node
        h = h->next; //inc h
        free(curr); //free the pointed to node
    }
    free(h); // free the last element
      
}

#endif