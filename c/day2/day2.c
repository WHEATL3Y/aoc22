// Advent of Code 2022
// Day 2
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  
    FILE *f = fopen("input.txt", "r");
    unsigned answer1 = 0;
    unsigned answer2 = 0;
    unsigned char opMove;
    unsigned char myMove;
    unsigned char mvPtr = 0;
    char c;
    int playValues[100];
    playValues['A' - 1] = 3;    // Rollover
    playValues['C' + 1] = 1;
    playValues['A'] = 1;        // Rock
    playValues['X'] = 1;    
    playValues['B'] = 2;        // Paper 
    playValues['Y'] = 2;
    playValues['C'] = 3;        // Scissors
    playValues['Z'] = 3;

    while ((c = getc(f)) != EOF) {

        // Ignore whitespace
        if (c == ' ' || c == '\t') {
            continue;
        }

        if (c == '\n') {
            
            // Part 1
            // Draw
            if (playValues[opMove] == playValues[myMove]) {
                answer1 += playValues[myMove] + 3;
            }
            // Loss
            else if (playValues[opMove - 1] == playValues[myMove]) {
                answer1 += playValues[myMove];
            }
            // Win
            else {
                answer1 += playValues[myMove] + 6;
            }

            // Part 2
            switch (myMove) {
                case 'X': 
                    answer2 += playValues[opMove - 1];
                    break;
                case 'Y':
                    answer2 += playValues[opMove] + 3;
                    break;
                case 'Z':
                    answer2 += playValues[opMove + 1] + 6; 
                    break;
                default:
                    printf("No Match\n");
                    break;
            }

            continue;

        }
        
        if (mvPtr) {
            myMove = c;
            mvPtr--;
        }
        else {
            opMove = c;
            mvPtr++;
        }

    }

    printf("%d\n%d\n", answer1, answer2);

    return EXIT_SUCCESS;

}
