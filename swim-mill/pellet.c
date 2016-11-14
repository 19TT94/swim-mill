//
//  pellet.c
//  swim-mill
//
//  Created by Taylor Tobin on 10/19/16.
//  Copyright © 2016 Taylor Tobin. All rights reserved.
//

#include "include.h"

void sharedMem();

int main(int argc, const char * argv[]) {

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
