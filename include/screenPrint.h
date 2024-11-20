#ifndef SCREENPRINT_H
#define SCREENPRINT_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "st7735.h"

#define WHITE 0xFFFF
#define LIGHT_PURPLE 0x780B
#define DARK_PURPLE 0x4806
#define SKIN_COLOR 0x9558
#define DARK_BROWN 0x21EB
#define LIGHT_BROWN 0x2AAF
#define UP_EYE 0x530F
#define DOWN_EYE 0x6BF1
#define GREY 0x8410
#define BLACK 0x0000
#define DARK_RED 0x18EC
#define LIGHT_RED 0x192E
#define EVIL_UP_EYE 0x18CC
#define EVIL_DOWN_EYE 0x3A1F
#define DARK_BLUE 0x5A44
#define LIGHT_BLUE 0x7305
#define DARK_GREEN 0x4343
#define LIGHT_GREEN 0x5CE4

void printTitle() {
    //use this function to print to the entire screen (use sparingly)
    uint16_t pixels[1024] = {

    };
    uint16_t bitShifter = 0b1000000000000000;
    uint8_t bitShiftCount = 0;
    uint8_t col = 0;
    uint8_t row = 0;
    uint8_t count = 0;

    for (int i = 0; i < 1024; i++) {
        bitShifter = 0b1000000000000000;
        bitShiftCount = 0;
        for (int j = 0; j < 16; j++) {
            if (pixels[i] & bitShifter) {
                createPixel(row*16+bitShiftCount, col, WHITE);
            }
            bitShifter = bitShifter >> 1;
            ++bitShiftCount;
        }
        ++count;
        if (count > 7) {
            count = 0;
            row = 0;
            ++col;
        }
        else {
            ++row;
        }
    }
}

void printOther() {
    // use this function to print only certain coordinates of the screen
    uint8_t coordinates[10][2] = {};
    // coordinates[numb of total pixels][2]
    
    for (int i = 0; i < 10; ++i) {
        //ADJUST LENGTH BASED ON NUMBER OF PIXELS
        uint8_t x = coordinates[i][1];
        uint8_t y = coordinates[i][0];
        createPixel(x,y, WHITE);
    }
}

#endif