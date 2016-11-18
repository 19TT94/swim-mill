//
//  main.c
//  swim-mill
//
//  Created by Taylor Tobin on 10/19/16.
//  Copyright © 2016 Taylor Tobin. All rights reserved.
//

#include "include.h"

// Method Prototypes
void createMem();
void genRiver();
void printRiver();


int main() {
    printf("Swim Mill Sim\n\n");
    printf("This program simulates a fish swimming through a river with pellets causing it to change course with multiple processes.\n\n");
    
    printf("River's intitial state\n");
    
    //Generate River
    createMem();
    genRiver();
    printRiver();
    
    // Start child processes
    fish = fork();
    if(fish == 0) {
        static char *argv[] = {"","",NULL};
        execv("./fish", argv);
    }
    
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
    (*river)[river_height-1][river_length/2] = f;
}

// function that prints river array
void printRiver() {
    for(int i=0; i < river_height; i++) {
        for(int j=0; j < river_length; j++ ) {
            printf("%c", (*river)[i][j]);
        }
        printf("\n");
    }
}

// Funciton to establish shared memory
void createMem() {
    // Create shared memory ID segment
    if((sharedMemoryID = shmget(key, sizeof(river), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    
    // Attach shared memory ID to data space
    if ((river = shmat(sharedMemoryID, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }
}

void catchKill() {
    //Kill child processes
    kill(fish, SIGINT);
    kill(pellet, SIGINT);
    
    //Detach and deallocate shared memory
    shmdt(river);
    shctl(sharedMemoryID, IPC_RMID, 0);
    
    exit(0);
}


