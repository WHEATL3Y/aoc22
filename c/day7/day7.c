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
    unsigned size;
    char name[MAX_NAME];
} file;

typedef struct dir {
    char name[MAX_NAME];
    unsigned numFiles;
    unsigned numDirs;
    int size;
    struct dir *parent;
    struct file *files[MAX_DIR];
    struct dir *children[MAX_DIR];
} dir;

int getToken(FILE *);
int mkdir(char *, dir *, dir *);
int mkfile(char *, unsigned, dir *, file *);
int cd(char *);
int ls(void);
int getDirSize(dir *);

static char token[MAX_TOKEN];
static dir *pwd;
static dir *root;
static int mode;
static int a1Pointer = 0;

dir *a1Dirs[MAX_DIR];

int getToken(FILE *f) {

    int c;
    int i = 0; 
    int returnValue;

    while ((c = getc(f))) {
        if (c == ' ' || c == '\n') {
            token[i] = '\0';
            /* printf("%s\n", token); */
            return 0;
        }
        else if (c == EOF) {
            return 1;
        }
        else {
            token[i++] = c;
        }
    }

    return 1;

}

int mkdir(char *name, dir *parent, dir *newDir) {
   
    if (parent->numDirs < MAX_DIR) {
        strcpy(newDir->name, name);
        newDir->parent = parent;
        newDir->numDirs = 0;
        newDir->numFiles = 0;
        newDir->size = -1;
        parent->children[parent->numDirs] = newDir;
        parent->numDirs++;
        printf("Created new directory (%s) in %s, %s now contains %u dirs and %u files\n", name, parent->name, parent->name,  parent->numDirs, parent->numFiles);

        return EXIT_SUCCESS;
    }
    else {
        printf("Error: Too many children");
        return EXIT_FAILURE;
    }

}

int mkfile(char *name, unsigned size, dir *parent, file *newFile) {
    
    if (parent->numFiles < MAX_DIR) {
        strcpy(newFile->name, name);
        newFile->size = size;
        parent->files[parent->numFiles] = newFile;
        parent->numFiles++;
        printf("Created new file (%s) in %s, %s now contains %u dirs and %u files\n", name, parent->name, parent->name,  parent->numDirs, parent->numFiles);

        return EXIT_SUCCESS;
    }
    else {
        printf("Error: Too many files\n");
        return EXIT_FAILURE;
    }
}

int cd(char *to) {

    int i = 0;

    if (!strcmp("/", to)) {
        pwd = root;
        printf("Changed dir to %s\n", pwd->name);
        return EXIT_SUCCESS;
    }
    if (!strcmp("..", to)) {
        pwd = pwd->parent;
        printf("Changed dir to %s\n", pwd->name);
        return EXIT_SUCCESS;
    }
    while (i < pwd->numDirs) {
        if (!strcmp(to, (pwd->children[i])->name)) {
            pwd = pwd->children[i];
            printf("Changed dir to %s\n", to);
            return EXIT_SUCCESS;
        }
        else {
            i++;
        }
    } 

    printf("No such directory, %s\n", to);
    return EXIT_FAILURE;

}

int ls(void) {

    int i = 0;
    while (i < pwd->numDirs && pwd->numDirs) {
        printf("dir %s\n", pwd->children[i]->name);
        i++;
    }
    i = 0;
    while (i < pwd->numFiles && pwd->numFiles) {
        printf("%s %u\n", pwd->files[i]->name, pwd->files[i]->size);
        i++;
    }

    return EXIT_SUCCESS;

}

int getDirSize(dir *directory) {

    int i;
    int size = 0;

    for (i = 0; i < directory->numDirs; i++) {
       size += getDirSize(directory->children[i]); 
       if (size <= 100000) {
            a1Dirs[a1Pointer++] = directory->children[i];        
       }
    }

    for (i = 0; i < directory->numFiles; i++) {
       size += directory->files[i]->size; 
    }

    return size; 
}

int main(void) {

    int answer1;
    int answer2;

    FILE *f = fopen("input.txt", "r");

    // Create root directory
    root = (dir *) malloc(sizeof(dir));
    /* printf("root: %p\n", root); */
    root->parent = root;
    root->numDirs = 0;
    root->numFiles = 0;
    root->size = -1;
    pwd = root;
    strcpy(root->name, "/");
    
    while (getToken(f) == 0) {
        /* printf("%s: %p\n", pwd->name, pwd); */
        if (!strcmp(token, "$")){
            getToken(f);
            if (!strcmp(token, "ls")){
                mode = LIST;
                continue;
            }
            if (!strcmp(token, "cd")) {
                getToken(f);
                cd(token);
                mode = 0;
                continue;
            }
        }
        if (mode == LIST) {
            if (!strcmp(token, "dir")) {
                getToken(f);
                dir *newDir;
                newDir = (dir *) malloc(sizeof(dir));
                mkdir(token, pwd, newDir);
                continue;
            }
            else {
                unsigned size = atoi(token);
                file *newFile;
                newFile = (file *) malloc(sizeof(file)); 
                getToken(f);
                mkfile(token, size, pwd, newFile);
                continue;
            } 
        }
    }
  
    // Answer Part 1


    
    // Interactive Pseudo-shell
    printf("--------------------\n");
    while (1) {
        printf("$ ");
        getToken(stdin);
        if (!strcmp(token, "ls")) {
            ls();
        }
        else if (!strcmp(token, "cd")) {
            getToken(stdin);
            cd(token);
        }
        else if (!strcmp(token, "pwd")) {
            printf("%s\n", pwd->name);
        }
        else if (!strlen(token)) {
            printf("\n");
        }
        else if (!strcmp(token, "exit")) {
            return EXIT_SUCCESS;
        }
        else {
            printf("Invalid Command: %s\n", token);
        }
    }

    return EXIT_SUCCESS;
}
