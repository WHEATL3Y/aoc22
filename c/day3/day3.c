// Advent of Code 2022
// Day 3
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findDuplicate(char *, char *);
void splitString(char *, char *, char *, int);
int findCommon(char *[3]);

int findDuplicate(char *s1, char *s2) {

    // Finds the duplicate value in strings of equal length (l)
    // Returns the pritority value
    // a-z = 1-26, A-Z = 27-52
    // Error = -1

    unsigned long mask = 1;
    unsigned long a = 0;
    unsigned long b = 0;
    unsigned long match;
    unsigned i = 0;
    int priority = 0;
    char c1;
    char c2;

    while ((c1 = s1[i]) != '\0') {
        
        c2 = s2[i++];
        c1 = c1 <= 90 ? c1 - 38 : c1 - 96;  
        c2 = c2 <= 90 ? c2 - 38 : c2 - 96;

        mask <<= c1 - 1;
        a |= mask;

        mask = 1;
        mask <<= c2 - 1;
        b |= mask;

        if ((match = a & b) > 0) {
            while (match > 0) {
                match >>= 1;
                priority++;
            }
            
            return priority;

        }
        else {
            mask = 1;
            continue;
        }
    }

    return -1;

}

void splitString(char *s, char *s1, char *s2, int l) {

    // Splits the contents of s in 2, places one half in s1 and the other in s2
    // l = length of s not including null

    int half = (l / 2);
    int i;

    for (i = 0; i < half; i++) {
        s1[i] = s[i];
    }
    s1[i] = '\0';

    for (; (s2[i - half] = s[i]) != '\n'; i++) {
        ;
    }
    s2[i - half] = '\0';
}

int findCommon(char *list[3]) {
    
    unsigned long mask = 1;
    unsigned long bitValues[3] = {0};
    unsigned long match;
    char c;
    unsigned i;
    unsigned lp;
    int priority = 0;

    for (lp = 0; lp < 3; lp++) {
       
        for (i = 0; (c = list[lp][i]) != '\n'; i++) {
            c = c <= 90 ? c - 38 : c - 96;
            mask <<= c - 1;
            bitValues[lp] |= mask;
            mask = 1;
        }
    }

    match = bitValues[0] & bitValues[1] & bitValues[2];
    while (match > 0) {
        match >>= 1;
        priority++;
    }

    return priority;

}

int main(void) {

    int answer1 = 0;
    int answer2 = 0;

    FILE *f = fopen("input.txt", "r");
    char *buffer;
    char *s1;
    char *s2;
    size_t bufsize = 32;
    size_t length;
    char *elves[3];
    int ep = 0;
    unsigned i;
    unsigned j;

    buffer = (char *) malloc(bufsize * sizeof(char));

    while ((length = getline(&buffer, &bufsize, f)) != -1) {

        // Part 1
        length--;       // Don't count newline
        s1 = (char *) malloc((length / 2 + 2) * sizeof(char));
        s2 = (char *) malloc((length / 2 + 2) * sizeof(char));
        splitString(buffer, s1, s2, length);

        answer1 += findDuplicate(s1, s2);
        free(s1);
        free(s2);

        // Part 2
        elves[ep] = (char *) malloc((length + 1) * sizeof(char));
        strcpy(elves[ep++], buffer);
        
        if (ep == 3) {
            ep = 0;
            answer2 += findCommon(elves);
            free(elves[0]);
            free(elves[1]);
            free(elves[2]);
        }
    }

    printf("%d\n%d\n", answer1, answer2);

    return EXIT_SUCCESS;
}
