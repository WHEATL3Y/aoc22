// Advent of Code 2022
// Day 6
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>

int checkDistinct(unsigned, int);
int getMarker(int *, int, int);

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

int getMarker(int *buffer, int mSize, int bSize) {

    int low = 0;
    int high = mSize - 1;
    int i = 0;

    unsigned value = 0;
    unsigned mask = 1;

    while (high <= bSize) {

        for (i = low; i <= high; i++) {
            mask <<= buffer[i]; 
            value |= mask;
            mask = 1;
        }
     
        low++;
        high++;

        if (checkDistinct(value, mSize)) {
            return high;
        } 
        else {
            value = 0;
        }

    }

    return 0;

}

int main(void) {

    int answer1;
    int answer2;

    FILE *f = fopen("input.txt", "r");
    int *string;
    int size;
    int c;

    int i = 0;
  
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);

    string = malloc(size * sizeof(int));

    while ((c = getc(f)) != EOF) {
        string[i++] = c - 'a';
    }

    answer1 = getMarker(string, 4, size);
    answer2 = getMarker(string, 14, size);

    /* printf("TEST size: %d\n", size); */
    /* printf("TEST checkDistinct: %d\n", checkDistinct(778, 4)); */

    printf("%d\n%d\n", answer1, answer2);

    return EXIT_SUCCESS;

}
