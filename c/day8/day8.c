// Advent of Code 2022
// Day 8
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>

int getGridDimensions(FILE *, int *);
int loadGrid(FILE *, int **);
int **createGrid(int, int);
int getVisible(int**, int*);
int checkIfVisible(int**, int, int, int, int);

static int answer1 = 0;
static int answer2 = 0;

int getGridDimensions(FILE *f, int *dimensions) {

    int i;
    int c;

    for (i = 0; (c = getc(f)) != '\n'; i++) {
        ;
    }
    dimensions[0] = i;

    fseek(f, 0, SEEK_END);
    dimensions[1] = (ftell(f) - 1) / dimensions[0];
    fseek(f, 0, SEEK_SET);

    return EXIT_SUCCESS;

}

int loadGrid(FILE *f, int **grid) {

    int x = 0;
    int y = 0;
    int c;

    while ((c = getc(f)) != EOF) {

        if (c == '\n') {
            x = 0;
            y++;
            continue;
        }
        grid[x++][y] = c - '0';
    }

    return EXIT_SUCCESS;
}

int **createGrid(int x, int y) {

    // Create a 2d array y tall and x wide

    int i;
    int **grid = (int **) malloc(y * sizeof(int *));

    for (i = 0; i < y; i++) {
        grid[i] = (int *) malloc(x * sizeof(int));
    }

    return grid;

}

int getVisible(int **grid, int *dimensions) {

    int numVisible = 0;
    int x = 0;
    int y = 0;
    int xLimit = dimensions[1] - 1;
    int yLimit = dimensions[0] - 1;

    while (1) {
       answer1 += checkIfVisible(grid, x++, y, xLimit, yLimit);
       if (y >= yLimit && x > xLimit) {
           return 0;
       }
       if (x > xLimit) {
           x = 0;
           y++;
       }
    }
    return 0;

}

int checkIfVisible(int **grid, int x, int y, int xLimit, int yLimit) {
   
    // Check if point (x, y) is visible, return 1 if yes 0 otherwise

    int currentValue = grid[y][x];
    int singleVisible = 1;
    int visible = 0;
    int singleView = 0;
    int view = 0;

    int x1 = x;
    int y1 = y;

    if (x == 0 || y == 0 || x == xLimit || y == yLimit) {
        visible = 1;
        return visible;
    }
    
    x1--;
    while (x1 >= 0) {
        singleView++;
        if (grid[y1][x1--] >= currentValue) {
            singleVisible = 0;
            break;
        }
    }
    if (singleVisible) {
        visible = 1;
    }
    view = view ? view * singleView : singleView;
    singleView = 0;
    x1 = x;
    singleVisible = 1;

    x1++;
    while (x1 <= xLimit) {
        singleView++;
        if (grid[y1][x1++] >= currentValue) {
            singleVisible = 0;
            break;
        }
    }
    if (singleVisible) {
        visible = 1;
    }
    view = view ? view * singleView : singleView;
    singleView = 0;
    x1 = x;
    singleVisible = 1;

    y1--;
    while (y1 >= 0) {
        singleView++;
        if (grid[y1--][x1] >= currentValue) {
            singleVisible = 0;
            break;
        }
    }
    if (singleVisible) {
        visible = 1;
    }
    view = view ? view * singleView : singleView;
    singleView = 0;
    y1 = y;
    singleVisible = 1;

    y1++;
    while (y1 <= yLimit) {
        singleView++;
        if (grid[y1++][x1] >= currentValue) {
            singleVisible = 0;
            break;
        }
    }
    view = view ? view * singleView : singleView;
    singleView = 0;
    if (singleVisible) {
        visible = 1;
    }

    answer2 = answer2 > view ? answer2 : view;
    return visible;

}

int main(void) {

    FILE *f = fopen("input.txt", "r");  
    int dimensions[2];
    int **grid;

    getGridDimensions(f, dimensions);
    grid = createGrid(dimensions[0], dimensions[1]);
    loadGrid(f, grid);
    getVisible(grid, dimensions);

    printf("%d\n%d\n", answer1, answer2);

    return EXIT_SUCCESS;
}
