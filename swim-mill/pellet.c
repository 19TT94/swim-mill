//
//  pellet.c
//  swim-mill
//
//  Created by Taylor Tobin on 10/19/16.
//  Copyright © 2016 Taylor Tobin. All rights reserved.
//

#include "include.h"

int main() {
    printf("PID %d (pellet) executed\n", getpid());
    
    //set up signal to kill child process
    signal(SIGINT, catchKill);
    
    //attach process to shared memory
    attachMem();
    
    printf("Pellet process started\n");
    
    (*river)[0][1] = p;
    
    return 0;
}
