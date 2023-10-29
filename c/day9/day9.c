// Advent of Code 2022
// Day 9
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    char direction;
    int distance;
} Move;

int moveHead(Point*, char, int);
int getMove(FILE*, Move*);

int moveHead(Point *position, char direction, int distance) {
  
    if (direction <= 90 && direction >= 65) {
        direction += 32;
    } 

    switch (direction) {
        case 'L': position->x -= distance; break;
        case 'R': position->x += distance; break;
        case 'U': position->y += distance; break;
        case 'D': position->y -= distance; break;
        default: return 1;
    }

    return EXIT_SUCCESS;

}

int getMove(FILE *f, Move *move) {

    printf("%p\n", &move);
    int c;
    short i = 0;
    char distance[3];
   
    c = getc(f);
    move->direction = 82;
    // Account for space in input
    getc(f);

    while ((c = getc(f)) != ' ' && c != '\n') {

        if (c == EOF) return EXIT_FAILURE;

        distance[i++] = c;
    }
   
    distance[i] = '\0';
    move->distance = atoi(distance);
   
    return EXIT_SUCCESS;

}

int main(void) {

    printf("test");
    unsigned answer1 = 0;
    unsigned answer2 = 0;

    FILE *f;
    Move *currentMove;
    Point *currentPoint = {0};

    f = fopen("sample.txt", "r");

    // Testing
    while (getMove(f, currentMove) != EXIT_FAILURE) {
        moveHead(currentPoint, currentMove->direction, currentMove->distance);
        printf("%d, %d", currentPoint->x, currentPoint->y);
    }

    return EXIT_SUCCESS;
}
