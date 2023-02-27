#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#define SIZE 10

void push();
void pop();
void show();

int stack[SIZE];
int top = -1;

int main() {
int x = 0;
while (1) {
printf("\n%s\n", "Choose a stack action brother:");
printf("%s\n%s\n%s\n", "1. push!", "2. pop", "3. show me the stack");
scanf("%d", &x);

switch(x) {
    case 1: push();
    break;
    case 2: pop();
    break;
    case 3: show();
    break;
}

}


}

void push() {
    if (top == SIZE - 1) {
        printf("%s\n", "Overflow!");

    } else {
        
        int j = 0;
        printf("%s\n", "input an integer to push: ");
        scanf("%d", &j);
        top += 1;
        stack[top] =  j;
    }
}

void pop() {
    if (top == -1) {
        printf("\n%s", "nothing to pop!");
    } else {
        printf("\nYou popped this element %d", stack[top]);
        top -= 1;
    }
}

void show() {
    if (top != -1) {
        printf("\n%s\n", "here's your stack bro:");
        for (size_t i = 0; i <= top; i++) {
            printf("\n%d", stack[i]);
    }
    } else {
        printf("\n%s", "there's nothing in your stack bro... ");
    }
}