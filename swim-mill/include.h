//
//  include.h
//  swim-mill
//
//  Created by Taylor Tobin on 11/13/16.
//  Copyright © 2016 Taylor Tobin. All rights reserved.
//

#ifndef include_h
#define include_h


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
const int river_height = 10, river_length = 10;
// for shared memory
const key_t key = 1694;
int sharedMemoryID;

// 2-D array to simulate river
char (*river)[river_height][river_length];

const char f = 'V';
pid_t fish;

const char p = 'o';
pid_t pellet;

void attachMem() {
    // Create shared memory ID segment
    if((sharedMemoryID = shmget(key, sizeof(river), 0666)) < 0) {
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

#endif /* include_h */
