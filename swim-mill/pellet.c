//
//  pellet.c
//  swim-mill
//
//  Created by Taylor Tobin on 10/19/16.
//  Copyright © 2016 Taylor Tobin. All rights reserved.
//

#include "include.h"

static int *pellets(int*);
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
    
    for(int i=0; i < 2; i++) {
        sleep(1);
        
        //get inital value for pellet
        int x = rand()%8+1;
        int y = rand()%8+1;
        //make sure pellet can be placed at this place in the river
        while((*river)[x][y] != water) {
            x = rand()%8+1;
            y = rand()%8+1;
        }
        
        //take random location created and create pellet threads
        int loc[2] = {x,y};
        pthread_create(&pool[i], NULL, pellets, loc);
    }
    
    pthread_join(pool[max-1], NULL);
    shmdt(river);
    
    return 0;
}

static int *pellets(int *loc) {
    //get pellet position
    int x = *loc;
    int y = *(loc + 1);

    //drop pellet
    (*river)[x][y] = p;
    sleep(1);
    
    // move the pellet down the river
    while(y < river_length) {
        // update previous pellet location
        (*river)[x][y] = water;
        //move pellet down river
        x++;
        (*river)[x][y] = p;
    }
    return 0;
}
