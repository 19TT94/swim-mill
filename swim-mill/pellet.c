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
    printf("Memory Attached in Pellet\n");
    
    // random seed
    srand(time(NULL));
    
    // generate pellet threads
    pthread_t pool[max];
    
    int i;
    for(i=0; i < max; i++) {
        sleep(1);
        
        //get inital value for pellet
        int x = rand()%8+1;
        int y = rand()%8+1;
        //make sure pellet can be placed at this place in the river
        while((*river)[x][y] != water) {
            x = rand()%8+1;
            y = rand()%8+1;
        }
        
        //printf("x,y: %d,%d\n", x,y);
        
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
    (*river)[x][y] = pellet;
    
    // move the pellet down the river
    while(x < (river_height-1)) {
        sleep(1);
        // update previous pellet location
        (*river)[x][y] = water;
        
        //move pellet down river
        x++;
        if((*river)[x][y] != fish) {
            (*river)[x][y] = pellet;
        }
    }
    
    sleep(1);
    if((*river)[x][y] != fish) {
        (*river)[x][y] = water;
    }
    
    return 0;
}
