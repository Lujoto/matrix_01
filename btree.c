#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "btree.h"




int main() {


node* root = malloc(sizeof(*root));
root->val = 4;
insert(root, 5);
insert(root, 2);
insert(root, 7);
insert(root, 9);

node* p = root;
while (p != NULL) {
    printf("\n%d", p->val);
    p = p->right;
}

node* found = find_by_val(root, 5);
if (found != NULL) { printf("\n Found Value: %d\n", found->val); }


printf("\nthe root node has values l:%d and r:%d\n", root->left->val, root->right->val);





    
}