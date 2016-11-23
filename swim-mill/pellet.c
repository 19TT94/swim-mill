//
//  pellet.c
//  swim-mill
//
//  Created by Taylor Tobin on 10/19/16.
//  Copyright © 2016 Taylor Tobin. All rights reserved.
//

#include "include.h"

static void *pellets(int*);
static int max = 20, active = 15;

int main() {
    printf("PID %d (pellet) executing\n", getpid());
    
    //set up signal to kill child process
    signal(SIGINT, catchKill);
    
    //attach process to shared memory
    attachMem();
    
    printf("Pellet process started\n");
    
    // random seed
    srand(time(NULL));
    
    // generate pellet threads
    pthread_t pool[max];
    
    for(int i=0; i < max; i++) {
        sleep(1);
        
        int x = 0;
        int y = 0;
        while((*river)[x][y] != 'o') {
            x = rand()%8+1;
            x = rand()%8+1;
        }
        
        //take random location created and create pellet threads
        int loc[2] = {x,y};
        pthread_create(&pool[i], NULL, pellets, loc);
    }
    
    pthread_join(pool[max-1], NULL);
    shmdt(river);
    
    exit(0);
}

static void *pellets(int *loc) {
    //get pellet position
    int x = *loc;
    int y = *(loc + 1);
    
    // check if pellet has been eaten
    while(x != river_height || (*river)[river_length][river_height] == f) {
        // drop pellet in river
        (*river)[x][y] = p;
        //wait and move pellet down river
        sleep(1);
        y++;
        
        //update contents of previous index
        if((*river)[x][y] != f) {
            (*river)[x][y] = water;
        }
    }
    return 0;
}
