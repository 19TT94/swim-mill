//
//  main.c
//  swim-mill
//
//  Created by Taylor Tobin on 10/19/16.
//  Copyright © 2016 Taylor Tobin. All rights reserved.
//

#include <stdio.h>

// Constants
const char water = '~';
const int river_length = 10;
const int river_width = 10;

// 2-D array to simulate river
char river[river_length][river_width];

// Method Prototypes
void genRiver();
void printRiver();

int main(int argc, const char * argv[]) {
    //Generate River
    genRiver();
    
    printRiver();
    
    return 0;
}

// function that populates the river array with water
void genRiver() {
    for(int i=0; i < river_length; i++) {
        for(int j=0; j < river_width; j++) {
            (river)[i][j] = water;
        }
    }
}

// function that prints river array
void printRiver() {
    for(int i=0; i < river_length; i++) {
        for(int j=0; j < river_width; j++ ) {
            printf("%c", river[i][j]);
        }
        printf("\n");
    }
}




