//
//  fish.c
//  swim-mill
//
//  Created by Taylor Tobin on 10/19/16.
//  Copyright © 2016 Taylor Tobin. All rights reserved.
//

#include "include.h"

//current fish location
int current = (river_length/2);

// count of eaten pellets
int count = 0;

int * findPellet();
bool eaten(int, int);
void moveFishRight();
void moveFishLeft();

int main() {
    printf("PID %d (fish) executing\n", getpid());
    
    //set up signal to kill child process
    signal(SIGINT, catchKill);
    
    //attach process to shared memory
    attachMem();
    
    printf("Fish process started\n");
    (*river)[river_height-1][river_length/2] = f;
    while(1) {
    
        int * pellet = findPellet();
    
        int x = *pellet;
        int y = *(pellet+1);
        while(eaten(x,y) == false /* and while the pellet is still in the river*/) {
            sleep(1);
            // check for pellet above fish
            if (y == current) { // fish is above of pellet
                //do nothing
            }
            else if(y > current) { // fish is to the left of pellet
                moveFishRight();
            }
            else {
                moveFishLeft();
            }
        }
    }
    
    return 0;
}

int * findPellet() {
    int loc[2];
    for(int i=0; i < river_height; i++) {
        for(int j=0; j < river_length; j++ ) {
            if((*river)[i][j] == p) {
                loc[0] = i;
                loc[1] = j;
                return loc;
            }
        }
    }
    return 0;
}


bool eaten(int x, int y) {
    if(y == current && x == (river_height-1)) {
        count++;
        (*river)[current][river_height]; //make sure fish isn't overridden
        return true;
    }
    return false;
}

void moveFishRight() {
    (*river)[9][current] = water;
    current += current;
    (*river)[9][current] = f;
    
}

void moveFishLeft() {
    (*river)[9][current] = water;
    current += current;
    (*river)[9][current] = f;
}
