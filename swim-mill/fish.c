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

    printf("Memory Attached in Fish\n");
    (*river)[river_height-1][river_length/2] = fish;
    while(1) {
        int * plocation = findPellet();
        if(plocation == 0) {
            sleep(1);
            continue;
        }
        int x = *plocation;
        int y = *(plocation+1);
                
        while(eat(x,y) == false /* and while the pellet is still in the river*/) {
            sleep(1);
            // use position of pellet to determine where the fish goes
            if(y > current) { // fish is to the left of pellet
                moveFishRight();
            }
            else if(y < current) { //fish is to the right of the pellet
                moveFishLeft();
            }
        }
        sleep(1);
        eaten++;
        printf("Pellet Eaten | count: %d\n", eaten);
    }
    
    return 0;
}

int * findPellet() {
    
    static int loc[2];
    for(int i=0; i < river_height; i++) {
        for(int j=0; j < river_length; j++ ) {
            if((*river)[i][j] == pellet) {
                loc[0] = i;
                loc[1] = j;
                return loc;
            }
        }
    }
    return 0;
}


bool eat(int x, int y) {
    //if(x == (river_height-1) && y == current) {
    if((*river)[river_height-2][current] == pellet) {
        (*river)[river_height-1][current] = fish; //make sure fish isn't overridden
        return true;
    }
    return false;
}

void moveFishRight() {
    (*river)[9][current] = water;
    current++;
    (*river)[9][current] = fish;
    
}

void moveFishLeft() {
    (*river)[9][current] = water;
    current--;
    (*river)[9][current] = fish;
}
