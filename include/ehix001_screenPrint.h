///////////////////////////////////////////////////////
// CS 120B Custom Lab Project Demo #2 - ehix001_screenPrint.h
// Author: Emily Hix
// 12/4/2024
// Video Demo 1 Link: https://youtu.be/SvAbyeLqzjc
// Video Demo 2 Link: https://youtu.be/ZwP4u5FAlhQ
///////////////////////////////////////////////////////
#ifndef SCREENPRINT_H
#define SCREENPRINT_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ehix001_st7735.h"

#define WHITE 0xFFFF
#define LIGHT_PURPLE 0x500F
#define DARK_PURPLE 0x3009
#define SKIN_COLOR 0xD655
#define DARK_BROWN 0x098C
#define LIGHT_BROWN 0x1231
#define UP_EYE 0x7B0A
#define DOWN_EYE 0x8BED
#define GREY 0x7BCF
#define BLACK 0x0000
#define DARK_BLUE 0x60E2
#define LIGHT_BLUE 0x7103
#define EVIL_UP_EYE 0x78C3
#define EVIL_DOWN_EYE 0xE0E3
#define DARK_RED 0x31B0
#define LIGHT_RED 0x4A96
#define DARK_GREEN 0x1CA9
#define LIGHT_GREEN 0x1EA9

void printPlayer(uint8_t playerX, uint8_t playerY) {
    int xBuffer = 0;
    int yBuffer = 0;

    if (playerX == 0) {
        yBuffer = -42;
    }
    else if (playerX == 1) {
        yBuffer = -21;
    }
    else if (playerX == 3) {
        yBuffer = 21;
    }
    else if (playerX == 3) {
        yBuffer = 21;
    }
    else if (playerX == 4) {
        yBuffer = 42;
    }
    else if (playerX == 5) {
        yBuffer = 63;
    }

    if (playerY == 4) {
        xBuffer = -21;
    }
    else if (playerY == 3) {
        xBuffer = -42;
    }
    else if (playerY == 2) {
        xBuffer = -63;
    }
    else if (playerY == 1) {
        xBuffer = -84;
    }
    else if (playerY == 0) {
        xBuffer = -105;
    }

    // ------------------------ DARK ROBE
        
        uint8_t darkRobe[55][2] = {{46, 105}, {47, 105}, {48, 105}, {45, 106}, {46, 106}, {44, 107}, {45, 107}, 
        {43, 108}, {44, 108}, {45, 108}, {46, 108}, {47, 108}, {42, 109}, {43, 109}, {44, 109}, {47, 109}, {47, 110}, 
        {46, 111}, {47, 111}, {50, 111}, {51, 111}, {46, 112}, {47, 112}, {48, 112}, {49, 112}, {46, 113}, {47, 113}, 
        {47, 118}, {47, 119}, {48, 119}, {49, 119}, {50, 119}, {46, 120}, {47, 120}, {48, 120}, {50, 120}, {46, 121}, 
        {47, 121}, {48, 121}, {54, 121}, {55, 121}, {46, 122}, {47, 122}, {46, 123}, {47, 123}, {45, 124}, {46, 124}, 
        {47, 124}, {48, 124}, {53, 124}, {54, 124}, {47, 125}, {48, 125}, {52, 125}, {53, 125}};

        for (int i = 0; i < 55; ++i) {
            int DRx = darkRobe[i][1];
            int DRy = darkRobe[i][0];
            createPixel(DRx+xBuffer,DRy+yBuffer, DARK_PURPLE);
        }

    // ------------------------

    // ------------------------ LIGHT ROBE

        uint8_t lightRobe[49][2] = {{47, 106},{48, 106},{49, 106},{46, 107},{47, 107},
        {48, 107},{49, 107},{50, 107},{48, 108},{49, 108},{50, 108},{51, 108},{48, 109},
        {49, 109},{50, 109},{51, 109},{48, 110},{49, 110},{50, 110},{51, 110},{48, 111},
        {49, 111},{52, 111},{50, 112},{51, 112},{52, 112},{49, 120},{51, 120},{54, 120},
        {55, 120},{49, 121},{50, 121},{51, 121},{48, 122},{49, 122},{50, 122},{51, 122},
        {52, 122},{48, 123},{49, 123},{50, 123},{51, 123},{52, 123},{53, 123},{54, 123},
        {49, 124},{50, 124},{51, 124},{52, 124}};

        for (int i = 0; i < 49; ++i) {
            int LRx = lightRobe[i][1];
            int LRy = lightRobe[i][0];
            createPixel(LRx+xBuffer,LRy+yBuffer, LIGHT_PURPLE);
        }

    // // ------------------------

    // // ------------------------ SKIN
        
        uint8_t skin[17][2] =  {{48, 113}, {49, 113},{50, 113},{51, 113},{52, 113},
                                {48, 114},{49, 114},{50, 114},{52, 114},{49, 115},
                                {50, 115},{52, 115},{49, 116},{50, 116},{51, 116},
                                {52, 116},{50, 117}};

        for (int i = 0; i < 17; ++i) {
            int Sx = skin[i][1];
            int Sy = skin[i][0];
            createPixel(Sx+xBuffer,Sy+yBuffer, SKIN_COLOR);
        }

    // // ------------------------

    // // ------------------------ BEARD
        
        uint8_t beard[20][2] = {{48, 115}, {48, 116}, {48, 117}, {49, 117}, {51, 117}, 
                                {52, 117}, {48, 118}, {49, 118}, {50, 118}, {51, 118}, 
                                {52, 118}, {53, 118}, {51, 119}, {52, 119}, {53, 119}, 
                                {52, 120}, {53, 120}, {52, 121}, {53, 121}, {53, 122}};

        for (int i = 0; i < 20; ++i) {
            int Bx = beard[i][1];
            int By = beard[i][0];
            createPixel(Bx+xBuffer,By+yBuffer, GREY);
        }

    // // ------------------------

    // // ------------------------ EYE UP
        
        uint8_t eyeUp[1][2] = {{51,114}};

        int EUx = eyeUp[1][1];
        int EUy = eyeUp[1][0];
        createPixel(EUx+xBuffer,EUy+yBuffer, UP_EYE);
        
    // // ------------------------

    // // ------------------------ EYE DOWN

        uint8_t eyeDown[1][2] = {{51,115}};

        int EDx = eyeDown[1][1];
        int EDy = eyeDown[1][0];
        createPixel(EDx+xBuffer,EDy+yBuffer, DOWN_EYE);

    // ------------------------

    // ------------------------ STAFF LIGHT

        uint8_t staffLight[12][2] = {{58, 109},{58, 111},{57, 112},{57, 113},{57, 114},
                                    {57, 115},{57, 118},{57, 119},{57, 121},{57, 122},
                                    {57, 123},{57, 124}};

        for (int i = 0; i < 12; ++i) {
            int SLx = staffLight[i][1];
            int SLy = staffLight[i][0];
            createPixel(SLx+xBuffer,SLy+yBuffer, LIGHT_BROWN);
        }

    // ------------------------

    // ------------------------ STAFF DARK
        
        uint8_t staffDark[29][2] = {{59, 108},{60, 108},{61, 108},{59, 109},
                                    {60, 109},{61, 109},{57, 110},{58, 110},
                                    {59, 110},{61, 110},{56, 111},{57, 111},
                                    {61, 111},{56, 112},{56, 113},{56, 114},
                                    {56, 115},{56, 116},{57, 116},{56, 117},
                                    {57, 117},{56, 118},{56, 119},{56, 120},
                                    {57, 120},{56, 121},{56, 122},{56, 123},
                                    {56, 124}};

        for (int i = 0; i < 29; ++i) {
            int SDx = staffDark[i][1];
            int SDy = staffDark[i][0];
            createPixel(SDx+xBuffer,SDy+yBuffer, DARK_BROWN);
        }

    // ------------------------
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
        xBuffer = -63;
        yBuffer = -21;
    }
    if (whichWizard == 2) {
        // green wizard
        lightRobeColor = LIGHT_GREEN;
        darkRobeColor = DARK_GREEN;
        yBuffer = 42;
        xBuffer = -84;
    }
    if (whichWizard == 3) {
        // red wizard
        lightRobeColor = LIGHT_RED;
        darkRobeColor = DARK_RED;
        yBuffer = 42;
        xBuffer = -21;
    }

    // ------------------------ DARK ROBE
        
        uint8_t darkRobe[55][2] = {{46, 105}, {47, 105}, {48, 105}, {45, 106}, {46, 106}, {44, 107}, {45, 107}, 
        {43, 108}, {44, 108}, {45, 108}, {46, 108}, {47, 108}, {42, 109}, {43, 109}, {44, 109}, {47, 109}, {47, 110}, 
        {46, 111}, {47, 111}, {50, 111}, {51, 111}, {46, 112}, {47, 112}, {48, 112}, {49, 112}, {46, 113}, {47, 113}, 
        {47, 118}, {47, 119}, {48, 119}, {49, 119}, {50, 119}, {46, 120}, {47, 120}, {48, 120}, {50, 120}, {46, 121}, 
        {47, 121}, {48, 121}, {54, 121}, {55, 121}, {46, 122}, {47, 122}, {46, 123}, {47, 123}, {45, 124}, {46, 124}, 
        {47, 124}, {48, 124}, {53, 124}, {54, 124}, {47, 125}, {48, 125}, {52, 125}, {53, 125}};

        for (int i = 0; i < 55; ++i) {
            uint8_t DRx = darkRobe[i][1];
            uint8_t DRy = darkRobe[i][0];
            createPixel(DRx+xBuffer,DRy+yBuffer, darkRobeColor);
        }

    // ------------------------

    // ------------------------ LIGHT ROBE

        uint8_t lightRobe[49][2] = {{47, 106},{48, 106},{49, 106},{46, 107},{47, 107},
        {48, 107},{49, 107},{50, 107},{48, 108},{49, 108},{50, 108},{51, 108},{48, 109},
        {49, 109},{50, 109},{51, 109},{48, 110},{49, 110},{50, 110},{51, 110},{48, 111},
        {49, 111},{52, 111},{50, 112},{51, 112},{52, 112},{49, 120},{51, 120},{54, 120},
        {55, 120},{49, 121},{50, 121},{51, 121},{48, 122},{49, 122},{50, 122},{51, 122},
        {52, 122},{48, 123},{49, 123},{50, 123},{51, 123},{52, 123},{53, 123},{54, 123},
        {49, 124},{50, 124},{51, 124},{52, 124}};

        for (int i = 0; i < 49; ++i) {
            uint8_t LRx = lightRobe[i][1];
            uint8_t LRy = lightRobe[i][0];
            createPixel(LRx+xBuffer,LRy+yBuffer, lightRobeColor);
        }

    // // ------------------------

    // // ------------------------ SKIN
        
        uint8_t skin[17][2] =  {{48, 113}, {49, 113},{50, 113},{51, 113},{52, 113},
                                {48, 114},{49, 114},{50, 114},{52, 114},{49, 115},
                                {50, 115},{52, 115},{49, 116},{50, 116},{51, 116},
                                {52, 116},{50, 117}};

        for (int i = 0; i < 17; ++i) {
            uint8_t Sx = skin[i][1];
            uint8_t Sy = skin[i][0];
            createPixel(Sx+xBuffer,Sy+yBuffer, SKIN_COLOR);
        }

    // // ------------------------

    // // ------------------------ BEARD
        
        uint8_t beard[20][2] = {{48, 115}, {48, 116}, {48, 117}, {49, 117}, {51, 117}, 
                                {52, 117}, {48, 118}, {49, 118}, {50, 118}, {51, 118}, 
                                {52, 118}, {53, 118}, {51, 119}, {52, 119}, {53, 119}, 
                                {52, 120}, {53, 120}, {52, 121}, {53, 121}, {53, 122}};

        for (int i = 0; i < 20; ++i) {
            uint8_t Bx = beard[i][1];
            uint8_t By = beard[i][0];
            createPixel(Bx+xBuffer,By+yBuffer, GREY);
        }

    // // ------------------------

    // // ------------------------ EYE UP
        
        uint8_t eyeUp[1][2] = {{51,114}};

        uint8_t EUx = eyeUp[1][1];
        uint8_t EUy = eyeUp[1][0];
        createPixel(EUx+xBuffer,EUy+yBuffer, EVIL_UP_EYE);
        
    // // ------------------------

    // // ------------------------ EYE DOWN

        uint8_t eyeDown[1][2] = {{51,115}};

        uint8_t EDx = eyeDown[1][1];
        uint8_t EDy = eyeDown[1][0];
        createPixel(EDx+xBuffer,EDy+yBuffer, EVIL_DOWN_EYE);

    // ------------------------

    // ------------------------ STAFF LIGHT

        uint8_t staffLight[12][2] = {{58, 109},{58, 111},{57, 112},{57, 113},{57, 114},
                                    {57, 115},{57, 118},{57, 119},{57, 121},{57, 122},
                                    {57, 123},{57, 124}};

        for (int i = 0; i < 12; ++i) {
            uint8_t SLx = staffLight[i][1];
            uint8_t SLy = staffLight[i][0];
            createPixel(SLx+xBuffer,SLy+yBuffer, LIGHT_BROWN);
        }

    // ------------------------

    // ------------------------ STAFF DARK
        
        uint8_t staffDark[29][2] = {{59, 108},{60, 108},{61, 108},{59, 109},
                                    {60, 109},{61, 109},{57, 110},{58, 110},
                                    {59, 110},{61, 110},{56, 111},{57, 111},
                                    {61, 111},{56, 112},{56, 113},{56, 114},
                                    {56, 115},{56, 116},{57, 116},{56, 117},
                                    {57, 117},{56, 118},{56, 119},{56, 120},
                                    {57, 120},{56, 121},{56, 122},{56, 123},
                                    {56, 124}};

        for (int i = 0; i < 29; ++i) {
            uint8_t SDx = staffDark[i][1];
            uint8_t SDy = staffDark[i][0];
            createPixel(SDx+xBuffer,SDy+yBuffer, DARK_BROWN);
        }

    // ------------------------
}

void removePlayer(uint8_t playerX, uint8_t playerY) {
    int xBuffer = 0;
    int yBuffer = 0;

    if (playerX == 0) {
        yBuffer = -42;
    }
    else if (playerX == 1) {
        yBuffer = -21;
    }
    else if (playerX == 3) {
        yBuffer = 21;
    }
    else if (playerX == 3) {
        yBuffer = 21;
    }
    else if (playerX == 4) {
        yBuffer = 42;
    }
    else if (playerX == 5) {
        yBuffer = 63;
    }

    if (playerY == 4) {
        xBuffer = -21;
    }
    else if (playerY == 3) {
        xBuffer = -42;
    }
    else if (playerY == 2) {
        xBuffer = -63;
    }
    else if (playerY == 1) {
        xBuffer = -84;
    }
    else if (playerY == 0) {
        xBuffer = -105;
    }

    // ------------------------ DARK ROBE
        
        uint8_t darkRobe[55][2] = {{46, 105}, {47, 105}, {48, 105}, {45, 106}, {46, 106}, {44, 107}, {45, 107}, 
        {43, 108}, {44, 108}, {45, 108}, {46, 108}, {47, 108}, {42, 109}, {43, 109}, {44, 109}, {47, 109}, {47, 110}, 
        {46, 111}, {47, 111}, {50, 111}, {51, 111}, {46, 112}, {47, 112}, {48, 112}, {49, 112}, {46, 113}, {47, 113}, 
        {47, 118}, {47, 119}, {48, 119}, {49, 119}, {50, 119}, {46, 120}, {47, 120}, {48, 120}, {50, 120}, {46, 121}, 
        {47, 121}, {48, 121}, {54, 121}, {55, 121}, {46, 122}, {47, 122}, {46, 123}, {47, 123}, {45, 124}, {46, 124}, 
        {47, 124}, {48, 124}, {53, 124}, {54, 124}, {47, 125}, {48, 125}, {52, 125}, {53, 125}};

        for (int i = 0; i < 55; ++i) {
            int DRx = darkRobe[i][1];
            int DRy = darkRobe[i][0];
            createPixel(DRx+xBuffer,DRy+yBuffer, BLACK);
        }

    // ------------------------

    // ------------------------ LIGHT ROBE

        uint8_t lightRobe[49][2] = {{47, 106},{48, 106},{49, 106},{46, 107},{47, 107},
        {48, 107},{49, 107},{50, 107},{48, 108},{49, 108},{50, 108},{51, 108},{48, 109},
        {49, 109},{50, 109},{51, 109},{48, 110},{49, 110},{50, 110},{51, 110},{48, 111},
        {49, 111},{52, 111},{50, 112},{51, 112},{52, 112},{49, 120},{51, 120},{54, 120},
        {55, 120},{49, 121},{50, 121},{51, 121},{48, 122},{49, 122},{50, 122},{51, 122},
        {52, 122},{48, 123},{49, 123},{50, 123},{51, 123},{52, 123},{53, 123},{54, 123},
        {49, 124},{50, 124},{51, 124},{52, 124}};

        for (int i = 0; i < 49; ++i) {
            int LRx = lightRobe[i][1];
            int LRy = lightRobe[i][0];
            createPixel(LRx+xBuffer,LRy+yBuffer, BLACK);
        }

    // // ------------------------

    // // ------------------------ SKIN
        
        uint8_t skin[17][2] =  {{48, 113}, {49, 113},{50, 113},{51, 113},{52, 113},
                                {48, 114},{49, 114},{50, 114},{52, 114},{49, 115},
                                {50, 115},{52, 115},{49, 116},{50, 116},{51, 116},
                                {52, 116},{50, 117}};

        for (int i = 0; i < 17; ++i) {
            int Sx = skin[i][1];
            int Sy = skin[i][0];
            createPixel(Sx+xBuffer,Sy+yBuffer, BLACK);
        }

    // // ------------------------

    // // ------------------------ BEARD
        
        uint8_t beard[20][2] = {{48, 115}, {48, 116}, {48, 117}, {49, 117}, {51, 117}, 
                                {52, 117}, {48, 118}, {49, 118}, {50, 118}, {51, 118}, 
                                {52, 118}, {53, 118}, {51, 119}, {52, 119}, {53, 119}, 
                                {52, 120}, {53, 120}, {52, 121}, {53, 121}, {53, 122}};

        for (int i = 0; i < 20; ++i) {
            int Bx = beard[i][1];
            int By = beard[i][0];
            createPixel(Bx+xBuffer,By+yBuffer, BLACK);
        }

    // // ------------------------

    // // ------------------------ EYE UP
        
        uint8_t eyeUp[1][2] = {{51,114}};

        int EUx = eyeUp[1][1];
        int EUy = eyeUp[1][0];
        createPixel(EUx+xBuffer,EUy+yBuffer, BLACK);
        
    // // ------------------------

    // // ------------------------ EYE DOWN

        uint8_t eyeDown[1][2] = {{51,115}};

        int EDx = eyeDown[1][1];
        int EDy = eyeDown[1][0];
        createPixel(EDx+xBuffer,EDy+yBuffer, BLACK);

    // ------------------------

    // ------------------------ STAFF LIGHT

        uint8_t staffLight[12][2] = {{58, 109},{58, 111},{57, 112},{57, 113},{57, 114},
                                    {57, 115},{57, 118},{57, 119},{57, 121},{57, 122},
                                    {57, 123},{57, 124}};

        for (int i = 0; i < 12; ++i) {
            int SLx = staffLight[i][1];
            int SLy = staffLight[i][0];
            createPixel(SLx+xBuffer,SLy+yBuffer, BLACK);
        }

    // ------------------------

    // ------------------------ STAFF DARK
        
        uint8_t staffDark[29][2] = {{59, 108},{60, 108},{61, 108},{59, 109},
                                    {60, 109},{61, 109},{57, 110},{58, 110},
                                    {59, 110},{61, 110},{56, 111},{57, 111},
                                    {61, 111},{56, 112},{56, 113},{56, 114},
                                    {56, 115},{56, 116},{57, 116},{56, 117},
                                    {57, 117},{56, 118},{56, 119},{56, 120},
                                    {57, 120},{56, 121},{56, 122},{56, 123},
                                    {56, 124}};

        for (int i = 0; i < 29; ++i) {
            int SDx = staffDark[i][1];
            int SDy = staffDark[i][0];
            createPixel(SDx+xBuffer,SDy+yBuffer, BLACK);
        }

    // ------------------------
}

#endif