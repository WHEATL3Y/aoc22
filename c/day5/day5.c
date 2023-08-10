// Advent of Code 2022
// Day 5
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
    int size;
    char values[100];
} Stack; 

void reverse(Stack *);
void move(int, Stack *, Stack *);

void reverse(Stack *s) {

    char t;
    int stackSize;
    int stackMin;

    for (stackSize = s->size, stackMin = 0; stackSize >= stackMin; stackSize--, stackMin++) {
        t = s->values[stackMin];
        s->values[stackMin] = s->values[stackSize];
        s->values[stackSize] = t;
    }
}

void move(int n, Stack *from, Stack *to) {
    
    for (; n > 0; n--) {
        from->size--;
        to->values[to->size + 1] = from->values[from->size + 1];
        to->size++;
    }

}

void moveall(int n, Stack *from, Stack *to) {

    int nCopy = n;
    for (; n > 0; n--) {
        to->values[to->size + (n)] = from->values[from->size];
        from->size--;
    }
    to->size += nCopy;
}

int main(void) {
   
    FILE *f = fopen("input.txt", "r");
    char c;
    char c1;
    char d[3];
    char t;
    unsigned char numCols = 0;
    unsigned char col = 0;
    unsigned char p = 0;
    int n;
    int from;
    int to;

    Stack stacks[10] = {0};
    Stack stacks1[10] = {0};

    // Read in stacks
    while ((c = getc(f))) {
      
        if (c >= 'A' && c <= 'Z') {
            stacks[col / 4].values[stacks[col / 4].size++] = c;
            col++;
            continue;
        }
        else if (c == '[' || c == ']' || c == ' ') {
            col++;
            continue;
        }
        else if (c == '\n') {
            numCols = numCols ? numCols : col / 4;
            col = 0;
            continue;
        }
        else {
            break;
        }
    }

    // Skip column numbers and whitespace before directions
    while((c = getc(f))) {
        if (c != 'm') {
            continue;
        }
        else {
            break;
        } 
    }

    // Reverse all stacks
    for (col = 0; col <= numCols; col++) {
        reverse(&stacks[col]);
    }

    memcpy(stacks1, stacks, sizeof(stacks));

    /* for (int i = 0; i <= numCols; i++) { */
    /*     printf("%d: ", stacks[i].size); */
    /*     for (int j = 0; j <= stacks[i].size; j++) { */
    /*         printf("%c", stacks[i].values[j]); */
    /*     } */
    /*     printf("\n"); */
    /* } */

    // Moves
    while((c = getc(f))) {

        if (c >= '0' && c <= '9') {
            d[0] = c;
            c1 = getc(f);
            if (c1 < '0' || c1 > '9') {
                ungetc(c1, f);
                d[1] = '\0';
            }
            else {
                d[1] = c1;
                d[2] = '\0';
            }

            if (p == 0) {
                n = atoi(d);
            }
            else if (p == 1) {
                from = atoi(d);
            }
            else if (p == 2) {
                to = atoi(d);
            }
            p++;
        }
        else if (c == '\n') {
            p = 0;
            move(n, &stacks[from - 1], &stacks[to - 1]); 
            moveall(n, &stacks1[from - 1], &stacks1[to - 1]);
        }
        else if (c != EOF){
            continue;
        }
        else {
            break;
        }
    }

    for (col = 0; col <= numCols; col++) {
        printf("%c", stacks[col].values[stacks[col].size]);
    } 
    printf("\n");

    for (col = 0; col <= numCols; col++) {
        printf("%c", stacks1[col].values[stacks1[col].size]);
    } 
    printf("\n");

    // TEMPORARY Testing
    /* for (int i = 0; i <= numCols; i++) { */
    /*     printf("%d: ", stacks[i].size); */
    /*     for (int j = 0; j <= stacks[i].size; j++) { */
    /*         printf("%c", stacks[i].values[j]); */
    /*     } */
    /*     printf("\n"); */
    /* } */

    return EXIT_SUCCESS;
}
