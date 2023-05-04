#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#define SIZE 10

void push();
void pop();
void show();

int stack[SIZE];
int top = -1;
char junk[256];

int main() {
while (1) {

    int x = 0;
    char n;
    printf("\n%s\n", "Choose a stack action brother:");
    printf("%s\n%s\n%s\n%s\n", "1. push!", "2. pop", "3. show me the stack", "4. terminate the program");
//some notes about scanf(): 
//  1. always check return value. It will be 0 if the function fails, for instance
//      by reading input that does not fit the format.
//  2. store the characters read by calling scanf() again, pointing it to a buffer...
//      
    if (scanf("%d", &x) == 0) {
        printf("%s\n", "scanf failed!");
        scanf("%s", junk);
        printf("%s\n", junk);
    }
    
    switch(x) {
        case 1: push();
        break;
        case 2: pop();
        break;
        case 3: show();
        break;
        case 4: exit(EXIT_SUCCESS);
        default: break; 
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