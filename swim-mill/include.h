//
//  include.h
//  swim-mill
//
//  Created by Taylor Tobin on 11/13/16.
//  Copyright © 2016 Taylor Tobin. All rights reserved.
//

#ifndef include_h
#define include_h


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <signal.h>

// Constants
const char water = '~';
const int river_height = 10, river_length = 10;
// for shared memory
const key_t key = 1694;
int sharedMemoryID;

// 2-D array to simulate river
char (*river)[river_height][river_length];

const char pellet = 'p';
const char fish = 'f';

#endif /* include_h */
