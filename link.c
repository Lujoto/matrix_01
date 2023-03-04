#include <stdio.h>
#include "link.h"


int main() {

node *head = malloc(sizeof(*head));
node *sec = malloc(sizeof(*sec));

head->key = 0;
head->contents = 3.14;
sec->key = 1;
sec->contents = 4.44;
head->next = sec;

printlist(head);


free(head);
free(sec);

}