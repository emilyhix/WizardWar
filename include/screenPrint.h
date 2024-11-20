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

void printWizard(uint8_t whichWizard) {
    uint16_t lightRobeColor = 0;
    uint16_t darkRobeColor = 0;
    int xBuffer = 0;
    int yBuffer = 0;

    if (whichWizard == 1) {
        // blue wizard
        lightRobeColor = LIGHT_BLUE;
        darkRobeColor = DARK_BLUE;
        xBuffer = -21;
        yBuffer = -63;
    }
    if (whichWizard == 2) {
        // green wizard
        lightRobeColor = LIGHT_GREEN;
        darkRobeColor = DARK_GREEN;
        xBuffer = 42;
        yBuffer = -84;
    }
    if (whichWizard == 3) {
        // red wizard
        lightRobeColor = LIGHT_RED;
        darkRobeColor = DARK_RED;
        xBuffer = 42;
        yBuffer = -21;
    }

    // ------------------------ DARK ROBE
        
        uint8_t darkRobe[10][2] = {};
        // CHANGE NUMBER OF ELEMENTS, FIRST []

        for (int i = 0; i < 10; ++i) {
        //ADJUST LENGTH BASED ON ELEMENT ABOVE
            uint8_t DRx = darkRobe[i][1];
            uint8_t DRy = darkRobe[i][0];
            createPixel(DRx+xBuffer,DRy+yBuffer, darkRobeColor);
        }

    // ------------------------

    // ------------------------ LIGHT ROBE

        uint8_t lightRobe[10][2] = {};
        // CHANGE NUMBER OF ELEMENTS, FIRST []

        for (int i = 0; i < 10; ++i) {
        //ADJUST LENGTH BASED ON ELEMENT ABOVE
            uint8_t LRx = lightRobe[i][1];
            uint8_t LRy = lightRobe[i][0];
            createPixel(LRx+xBuffer,LRy+yBuffer, lightRobeColor);
        }

    // ------------------------

    // ------------------------ SKIN
        
        uint8_t skin[10][2] = {};
        // CHANGE NUMBER OF ELEMENTS, FIRST []

        for (int i = 0; i < 10; ++i) {
        //ADJUST LENGTH BASED ON ELEMENT ABOVE
            uint8_t Sx = skin[i][1];
            uint8_t Sy = skin[i][0];
            createPixel(Sx+xBuffer,Sy+yBuffer, SKIN_COLOR);
        }

    // ------------------------

    // ------------------------ BEARD
        
        uint8_t beard[10][2] = {};
        // CHANGE NUMBER OF ELEMENTS, FIRST []

        for (int i = 0; i < 10; ++i) {
        //ADJUST LENGTH BASED ON ELEMENT ABOVE
            uint8_t Bx = beard[i][1];
            uint8_t By = beard[i][0];
            createPixel(Bx+xBuffer,By+yBuffer, GREY);
        }

    // ------------------------

    // ------------------------ EYE UP
        
        uint8_t eyeUp[1][2] = {};

        uint8_t EUx = eyeUp[1][1];
        uint8_t EUy = eyeUp[1][0];
        createPixel(EUx+xBuffer,EUy+yBuffer, UP_EYE);
        
    // ------------------------

    // ------------------------ EYE DOWN

        uint8_t eyeDown[1][2] = {};

        uint8_t EDx = eyeDown[1][1];
        uint8_t EDy = eyeDown[1][0];
        createPixel(EDx+xBuffer,EDy+yBuffer, DOWN_EYE);

    // ------------------------

    // ------------------------ STAFF LIGHT

        uint8_t staffLight[10][2] = {};
        // CHANGE NUMBER OF ELEMENTS, FIRST []

        for (int i = 0; i < 10; ++i) {
        //ADJUST LENGTH BASED ON ELEMENT ABOVE
            uint8_t SLx = staffLight[i][1];
            uint8_t SLy = staffLight[i][0];
            createPixel(SLx+xBuffer,SLy+yBuffer, LIGHT_BROWN);
        }

    // ------------------------

    // ------------------------ STAFF DARK
        
        uint8_t staffDark[10][2] = {};
        // CHANGE NUMBER OF ELEMENTS, FIRST []

        for (int i = 0; i < 10; ++i) {
        //ADJUST LENGTH BASED ON ELEMENT ABOVE
            uint8_t SDx = staffDark[i][1];
            uint8_t SDy = staffDark[i][0];
            createPixel(SDx+xBuffer,SDy+yBuffer, DARK_BROWN);
        }

    // ------------------------
}

#endif