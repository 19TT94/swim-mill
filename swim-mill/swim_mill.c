//
//  main.c
//  swim-mill
//
//  Created by Taylor Tobin on 10/19/16.
//  Copyright © 2016 Taylor Tobin. All rights reserved.
//

#include "include.h"

// Method Prototypes
void sharedMem();
void genRiver();
void printRiver();


int main(int argc, const char * argv[]) {
    printf("This Program simulates a Swim Mill with multiple processes.");
    
    //Generate River
    sharedMem();
    genRiver();
    printRiver();
    
    // Start child processes
    if((fish = fork()) == 0) {
        static char *argv[] = {"","",NULL};
        execv("/Users/TT/Desktop/", argv);
    }
    
    return 0;
}

// function that populates the river array with water
void genRiver() {
    for(int i=0; i < river_height; i++) {
        for(int j=0; j < river_length; j++) {
            (*river)[i][j] = water;
        }
    }
}

// function that prints river array
void printRiver() {
    for(int i=0; i < river_height; i++) {
        for(int j=0; j < river_length; j++ ) {
            printf("%c", *river[i][j]);
        }
        printf("\n");
    }
}

// Funciton to establish shared memory
void sharedMem() {
    // Create shared memory ID segment
    if((sharedMemoryID = shmget(key, sizeof(river), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    
    // Attach shared memory ID to data space
    if ((river = (char(*)[river_height][river_length])shmat(sharedMemoryID, NULL, 0)) == (char(*)[river_height][river_length]) -1) {
        perror("shmat");
        exit(1);
    }
}


