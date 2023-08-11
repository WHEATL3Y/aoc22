// Advent of Code 2022
// Day 6
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>

int checkDistinct(unsigned, int);

int checkDistinct(unsigned value, int n) {

    while (n > 0) {
        value &= value - 1;
        n--;
        if (value == 0 && n != 0) {
            return 0;
        }
        else if (value == 0 && n == 0) {
            return 1;
        }
        else {
            continue;
        }
    }

    return 0;

}

int main(void) {

    int answer1;
    int answer2;

    FILE *f = fopen("sample.txt", "r");
    int *string;
    int size;
    int c;

    int low = 0;
    int high = 3;
    unsigned mask = 0;
    unsigned value = 0;
  
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);

    string = malloc(size * sizeof(int));

    while ((c = getc(f)) != EOF) {
        *string++ = c - 'a';
    }

    printf("TEST size: %d\n", size);
    printf("TEST checkDistinct: %d\n", checkDistinct(778, 4));
    return EXIT_SUCCESS;
}
