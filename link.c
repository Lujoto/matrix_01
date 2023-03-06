#include <stdio.h>
#include "link.h"


int main() {

head = malloc(sizeof(*head));
head->contents = 1.000;
head->key = 0;
head->next = NULL;
current = head;

for(int i = 0; i < 10; i++) {
  node* n = insert(2.03*i);
}


delete(4);
delete(0);
delete(20);

printlist(head);

freelist(head);

}