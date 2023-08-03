// Advent of Code 2022
// Day 5
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>

int main(void) {
   
    FILE *f = fopen("sample.txt", "r");
    char c;
    unsigned char inputtingStack = 1;
    unsigned char col = 0;

    struct Stack {
        int size;
        char values[100];
    } stacks[10] = {0};

    while ((c = getc(f))) {
        
        if (c >= 'A' || c <= 'Z') {
            stacks[col / 4].values[stacks[col / 4].size++] = c;
        }
        else if (c == '[' || c == ']' || c == ' ') {
            col++;
        }
        else if (c == '\n') {
            col = 0;
        }
    }
    return EXIT_SUCCESS;
}
