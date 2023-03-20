#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "btree.h"




int main() {

node* root = createNode(4);

insert(root, 5);
insert(root, 10);
insert(root, 8);
insert(root, 1);
insert(root, 3);
insert(root, 2);
insert(root, 7);
insert(root, 9);
insert(root, 6);

printTree(root, 0);
printf("\n%s\n", "==================================");
deleteNode(root, 1);
printTree(root, 0);
printf("\n%s\n", "==================================");
deleteNode(root, 8);
printTree(root, 0);
printf("\n%s\n", "==================================");

freeTree(root, 0);

    
}