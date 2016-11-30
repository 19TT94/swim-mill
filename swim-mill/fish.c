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

int * findPellet();
bool eat(int, int);
void moveFishRight();
void moveFishLeft();

int main() {
    printf("PID %d (fish) executing\n", getpid());
    
    //set up signal to kill child process
    signal(SIGINT, catchKill);
    
    //attach process to shared memory
    attachMem();
    
    printf("Fish process started\n");
    printf("hi");
    (*river)[river_height-1][river_length/2] = f;
    printf("hello");
    while(1) {
        printf("hi");
        int * pellet = findPellet();
        printf("bye");
        int x = *pellet;
        int y = *(pellet+1);
        
        printf("hey %i %i\n",x,y);
        
        printf(" lks d ls ds ll sd kd sl\n");
        
        while(eat(x,y) == false && y < (river_height-1)/* and while the pellet is still in the river*/) {
            printf("jslkjfa;ls dfkja;lsd fja;lsdf\n");
            sleep(1);
            // check for pellet above fish
            if (y == current) { // fish is above of pellet
                //do nothing
                printf("hi");
            }
            else if(y > current) { // fish is to the left of pellet
                moveFishRight();
                printf("hey");
            }
            else {
                moveFishLeft();
                printf("hello)");
            }
        }
    }
    
    return 0;
}

int * findPellet() {
    static int loc[2];
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


bool eat(int x, int y) {
    if(y == current && x == (river_height-1)) {
        printf("Pellet Eaten\n");
        eaten++;
        (*river)[current][river_height-1] = f; //make sure fish isn't overridden
        return true;
    }
    return false;
}

void moveFishRight() {
    (*river)[9][current] = water;
    current++;
    (*river)[9][current] = f;
    
}

void moveFishLeft() {
    (*river)[9][current] = water;
    current++;
    (*river)[9][current] = f;
}
