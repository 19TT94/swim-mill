//
//  fish.c
//  swim-mill
//
//  Created by Taylor Tobin on 10/19/16.
//  Copyright © 2016 Taylor Tobin. All rights reserved.
//

#include "include.h"

int * findPellet();

int main() {
    printf("PID %d (fish) executing\n", getpid());
    
    //set up signal to kill child process
    signal(SIGINT, catchKill);
    
    //attach process to shared memory
    attachMem();
    
    printf("Fish process started\n");
    
    while(1) {
        sleep(1);
        int * pellet = findPellet();
        printf("loc1 %d", pellet);
        printf("loc2 %d", (pellet+1));
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
