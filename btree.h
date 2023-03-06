#ifndef BTREE_H
#define BTREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h> 


typedef struct node {
    int val;
    struct node* left;
    struct node* right;
} node;


node* insert(node*, int);
node* createNode(int);
node* find_by_val(node*, int);
void printTree(node*, size_t);

node* createNode(int val) {
    node* new = malloc(sizeof(*new));
    new->val = val;
    return new;
}

node* insert(node* n, int v) {
    if (n == NULL) {
       n = createNode(v);
    } 
    if (n->val < v) {
        n->right = insert(n->right, v);
    } else if (n->val > v) {
        n->left = insert(n->left, v);
    }
    return n;
}

node* find_by_val(node* n, int v) {
    if (n == NULL) {
        printf("\n%s\n", "find_by_val: The search is over!");
        return n;
    } else {      
        if (n->val == v) {
            return n;
        }
    }
    
   printf("\n searching for value %d: %d", v, n->val);
    if (n->val < v) {
        find_by_val(n->right, v);
    } else if (n->val > v) {
        find_by_val(n->left, v);
    }
}

void printTree(node* n, size_t level) {

}



#endif