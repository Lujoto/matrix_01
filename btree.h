#ifndef BTREE_H
#define BTREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <time.h> 
#include <math.h> 
#include <stdint.h> 
#include <stddef.h>
#include <sys/time.h>

typedef struct node {
    float val;
    struct node* left;
    struct node* right;
} node;

uint64_t nanos();
node* createRoot(int);
node* insert(node*, float);
node* createNode(float);
node* find_by_val(node*, float);
node* findBottomR(node*);
node* findBottomL(node*);
node* deleteNode(node*, float);
void printTree(node*, size_t);
void freeTree(node*, int);


uint64_t nanos() {
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
   // printf("\n %ld tv sec \n %ld tv nsec \n", start.tv_sec, start.tv_nsec);
    return (uint64_t)start.tv_sec*1e9 + (uint64_t)start.tv_nsec;
}

node* createNode(float val) {
    node* new = malloc(sizeof(*new));
    new->val = val;
    new->left = NULL;
    new->right = NULL;
    return new;
}

node* insert(node* n, float v) {
    if (n == NULL) {
       n = createNode(v);
       return n;
    } 
    if (n->val <= v) { // bias right when new value is equal to node->val
        n->right = insert(n->right, v);
    } else if (n->val > v) {
        n->left = insert(n->left, v);
    }
    return n;
}

node* find_by_val(node* n, float v) {
    if (n == NULL) {
        printf("\n%s\n", "find_by_val: The search is over!");
        return n;
    } else if (n->val == v) {      
            return n;
    } 
   //printf("\n searching for value %d: %d", v, n->val);
    if (n->val < v) {
        find_by_val(n->right, v);
    } else if (n->val > v) {
        find_by_val(n->left, v);
    }

}
//find lowest right pointed to node given any node. 
node* findBottomR(node* n) {
    if (n->right != NULL) {
        findBottomR(n->right);
    } else { return n; }
}

//find lowest left pointed to node given any node. 
node* findBottomL(node* n) {
    if (n->left != NULL) { 
        findBottomL(n->left);
    } else { return n; }
}



node* deleteNode(node* n, float v) {
    if (n == NULL)
        return NULL;
    if (n->val == v) {              // if we find a matching node: 
        if (n->left == NULL && n->right == NULL) { // if it's a leaf node:
            free(n);
            return NULL;
        } else if (n->left == NULL) {               // if it's a right subtree only:
            node* temp = n->right;
            free(n);
            return temp;
        } else if (n->right == NULL) {              // if it's a left subtree only: 
            node* temp = n->left; 
            free(n);
            return temp;
        } else {                                    // must be a branch node: 
            node* temp = findBottomR(n->left);
            n->val = temp->val;
            n->left = temp->left;
            free(temp);
            return n;
        }
        // By returning a node* here, we can maintain the link between the parent and child,
        // we store the successor in temp and are able to free the block pointed to the node*
        // argument, then return the successor and assign to the parent of the deleted node.
    } else if (n->val < v) {                        // if the value does not match, traverse
        n->right = deleteNode(n->right, v); 
    } else { 
        n->left = deleteNode(n->left, v);
    }
    return n; // without this, you'll assign the wrong pointer each step out of
                // the recursion
   }



void printTree(node* n, size_t level) {
    if (n == NULL) {
        return;
    }
    char spc = ' ';
    for (int i = 0; i < level; i++) {
        printf("%c", ' ');
        
    }
    
    printf("-%f-%lu\n", n->val, level);
    printTree(n->left, level+1);
    printTree(n->right, level+1);
    
}

void freeTree(node* n, int lvl) {
    if (n == NULL) 
        return;
   // example of post order traversal, needed for memory deallocation.
   // recursion CAN lead to stack overflow. iterative method increases time
   // complexity. 
    freeTree(n->left, lvl+1);
    freeTree(n->right, lvl+1);
    free(n);
}




#endif