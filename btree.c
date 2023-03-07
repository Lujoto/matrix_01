#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "btree.h"




int main() {


node* root = malloc(sizeof(*root));
root->val = 4;
insert(root, 5);
insert(root, 1);
insert(root, 3);
insert(root, 2);
insert(root, 7);
insert(root, 9);
insert(root, 6);

node* p = root;
while (p != NULL) {
    printf("\n%d", p->val);
    p = p->right;
}

node* found = find_by_val(root, 5);
if (found != NULL) { printf("\n Found Value: %d\n", found->val); }

printTree(root, 0);





    
}