// Advent of Code 2022
// Day 4
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>

int isFullOverlap(int *);
int isPartialOverlap(int *);

int main(void) {

    int answer1 = 0;
    int answer2 = 0;

    FILE *f = fopen("input.txt", "r");
    int c;
    int dp = 0;
    char d[3];
    int pp = 0;
    int pairs[4];

    while ((c = getc(f)) != EOF) {

        if (c >= '0' && c <= '9') {
            d[dp++] = c - 0;
        }
        
        else if (c == '-' || c == ',' || c == '\n') {
            d[dp] = '\0';
            pairs[pp++] = atoi(d);
            dp = 0;

            if (c == '\n') {
                answer1 += (pairs[0] <= pairs[2] && pairs[1] >= pairs[3]) || (pairs[0] >= pairs[2] && pairs[1] <= pairs[3]);
                answer2 += !(pairs[1] < pairs[2] || pairs[3] < pairs[0]);
                pp = 0;
            }
        }

        else {
            printf("ERROR: bad character %c\n", c);
            return EXIT_FAILURE;
        }

    }

    printf("%d\n%d\n", answer1, answer2);

    return EXIT_SUCCESS;
}
