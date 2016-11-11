//
//  main.c
//  swim-mill
//
//  Created by Taylor Tobin on 10/19/16.
//  Copyright © 2016 Taylor Tobin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <signal.h>

// Constants
const char water = '~';
const int river_height = 20, river_length = 10;
// for shared memory
const key_t key = 1694;
int sharedMemoryID;

// 2-D array to simulate river
char (*river)[river_height][river_length];

// Method Prototypes
void sharedMem();
void genRiver();
void printRiver();


int main(int argc, const char * argv[]) {
    //Generate River
    sharedMem();
    genRiver();
    printRiver();
    
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
    if((river = shmat(sharedMemoryID, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }
}


