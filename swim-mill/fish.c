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
bool eat(int *, int *);
void moveFishRight();
void moveFishLeft();

int main() {
    printf("PID %d (fish) executing\n", getpid());
    
    //set up signal to kill child process
    signal(SIGINT, catchKill);
    
    //attach process to shared memory
    attachMem();
    
    printf("Fish process started\n");
    
    int *x, *y;
    while(1) {
        sleep(1);
        int * pellet = findPellet();
        printf("loc1 %d", pellet);
        printf("loc2 %d", (pellet+1));
        
        x = pellet;
        y = pellet+1;
        
        // check for pellet above fish
        if (x == current) {
            sleep(1);
        }
        else if(x > current) {
            moveFishRight();
        }
        else {
            moveFishLeft();
        }
        
        if(eat(x,y) == true) {
            break;
        }
        
        break;
    }
    
    printf("hello fish");
    
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


//fix
bool eat(int * x, int * y) {
    if((*river)[(int) x][(int) y] == (int) current) {
        count++;
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
