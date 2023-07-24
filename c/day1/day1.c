// Advent of Code 2022
// Day 1
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXELVES 1000

int cmp(const void *, const void *);

int cmp(const void *a, const void *b) {

    return *(int*)a < *(int*)b ? 1 : -1;

}

int main(void) {

    FILE *f = fopen("input.txt", "r");
    char *buffer;
    size_t length;
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

    free(buffer);
    qsort(elves, elfNumber, sizeof(int), cmp);

    printf("%d\n", elves[0]);
    printf("%d\n", elves[0] + elves[1] + elves[2]);

    return EXIT_SUCCESS;

}
