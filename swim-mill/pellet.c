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
        
        //get inital value for pellet
        int x = rand()%8+1;
        int y = rand()%8+1;
        printf("\nploc1 %i", x);
        printf("\nploc2 %i", y);
        //make sure pellet can be placed at this place in the river
        //while((*river)[x][y] != water) {
            //x = rand()%8+1;
           // y = rand()%8+1;
        //}
        
        printf("\nploc3 %i", x);
        printf("\nploc4 %i", y);
        
        //take random location created and create pellet threads
        int loc[2] = {x,y};
        pthread_create(&pool[i], NULL, pellets, loc);
    }
    
    printf("\ncheck 1: hello pellet\n");
    
    pthread_join(pool[max-1], NULL);
    shmdt(river);
    
    printf("hello pellet\n");
    
    return 0;
}

static void *pellets(int *loc) {
    //get pellet position
    int x = *loc;
    int y = *(loc + 1);
    
    //drop pellet
    (*river)[x][y] = p;
    sleep(1);
    
    // move the pellet down the river
    while(y < river_height) {
        // update previous pellet location
        (*river)[x][y] = water;
        //move pellet down river
        y++;
        (*river)[x][y] = p;
    }
    //should be void but ...
    return 0;
}
