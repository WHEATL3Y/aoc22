// Advent of Code 2022
// Day 3
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

    int answer1;
    int answer2;

    FILE *f = fopen("sample.txt", "r");
    char *buffer;
    size_t bufsize = 32;
    size_t length;
    char *elves[3];
    int ep = 0;
    unsigned i;
    unsigned j;
    unsigned long mask;
    unsigned long a;
    unsigned long b;

    buffer = (char *) malloc(bufsize * sizeof(char));

    while ((length = getline(&buffer, &bufsize, f)) != -1) {

        elves[ep] = (char *) malloc((length + 1) * sizeof(char));
        strcpy(elves[ep++], buffer);
        if (ep == 2) {
            ep = 0;
            printf("%s", elves[0]);
            printf("%s", elves[1]);
            /* printf("%s", elves[2]); */
            free(elves[0]);
            free(elves[1]);
            free(elves[2]);
        }
        i = 0;
        j = length;
        mask = 0;
        a = 0;
        b = 0;
    }



    return EXIT_SUCCESS;
}
