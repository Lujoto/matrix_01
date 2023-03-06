#ifndef LINK_H
#define LINK_H

#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
#include <string.h> 

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
node* insert(float);
void delete(int);
void freelist(node*);



// Print the list from a node to the tail //
void printlist(node* n) {
    if (n != NULL) {
        while (n != NULL) {
        printf("\n(%d, %f)\n", n->key, n->contents);
        n = n->next;
    } 
  } else {
    printf("\n%s\n", "No list to print. ");
  }
}

// Insert a node at the head of the list //
node* insert(float contents) {
    if (head != NULL) {
        node* new = malloc(sizeof(*new)); 
        new->contents = contents;
        new->key = head->key+1;   
        new->next = head;
        head = new;
        return head;
    } else { 
        printf("\n%s\n", "No list to push to...");
        return NULL;
    }
}

void delete(int k) {
    if (head == NULL) {
        printf("\n%s\n", "No nodes to delete.");
        return;
    }
    node* curr = head;
    current = head;  
    node* prev = NULL;
    if (k == 0) {
       head = head->next;
       free(curr);
       return;
    }
    for (int i = 0; i < k; i++) {
        if (current->next != NULL) {
            current = curr->next;
            prev = curr;
            curr = curr->next; 
        } else {
            printf("\n%s %d\n", "Delete: Index out of range:", k);
            return;
        }
    }
   prev->next = current->next;
   free(current);
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


