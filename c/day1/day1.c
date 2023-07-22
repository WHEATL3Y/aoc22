// Advent of Code 2022
// Day 1
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END -1
#define MAXELVES 10000
#define BUFSIZE 10

int main(void) {

    FILE *f = fopen("input.txt", "r");
    char *buffer;
    size_t length;
    int max = 0;
    int elfNumber = 0;
    int elfInventory;
    int elves[MAXELVES];

    while (getline(&buffer, &length, f) != EOF) {

        if (buffer[0] == '\n') {
            elfInventory += atoi(buffer);
            elves[elfNumber++] = elfInventory;
            elfInventory = 0;
            continue;
        }
        else {
            elfInventory += atoi(buffer);
        }
    }

    while (elfNumber-- >= 0) {
        
        if (elves[elfNumber] > max) {
            max = elves[elfNumber];
        }

    }

    printf("%d\n", max);

    free(buffer);

    return EXIT_SUCCESS;

}
