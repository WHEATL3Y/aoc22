// Advent of Code 2022
// Day 7
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN   255
#define MAX_NAME    255
#define MAX_DIR     100

#define CMD         255
#define CHANGE      256
#define LIST        257
#define DIR         258
#define F_SIZE      259
#define DIR_NAME    260
#define F_NAME      261

typedef struct file {
    int size;
    char name[MAX_NAME];
} file;

typedef struct dir {
    char name[MAX_NAME];
    unsigned fp;
    unsigned cp;
    struct dir *parent;
    struct file *files[MAX_DIR];
    struct dir *children[MAX_DIR];
} dir;

int getToken(FILE *);
int mkdir(char *, dir *);

static unsigned token[MAX_TOKEN];

int getToken(FILE *f) {

    int c;

    while ((c = getc(f))) {

    }
    return 0;
}

int mkdir(char *name, dir *parent) {
   
    int size = parent->cp;

    if (size < MAX_DIR) {
        dir newDir = {.parent = parent};
        strcpy(newDir.name, "test");
        parent->children[size] = &newDir;
        printf("newDir address: %p\n", &newDir);
        printf("newDir name: %s\n", newDir.name);

        return EXIT_SUCCESS;
    }
    else {
        printf("Error: Too many children");
        return EXIT_FAILURE;
    }

}

int main(void) {

    int answer1;
    int answer2;
    
    FILE *f = fopen("sample.txt", "r");

    // Create root directory
    dir root = {.parent = &root, .cp = 0};
    strcpy(root.name, "/");
    
    // Testing
    mkdir("test", &root);
    printf("Root name: %s, Root size: %d\n", root.name, root.cp);
    printf("Child1 name: %p, Child1 addr: %p\n", root.children[root.cp]->name, root.children[root.cp]);

    return EXIT_SUCCESS;
}
