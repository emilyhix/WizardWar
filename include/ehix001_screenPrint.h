///////////////////////////////////////////////////////
// CS 120B Custom Lab Project Final Demo - ehix001_screenPrint.h
// Author: Emily Hix
// 12/11/2024
// Video Demo 1 Link: https://youtu.be/SvAbyeLqzjc
// Video Demo 2 Link: https://youtu.be/ZwP4u5FAlhQ
// Final Video Demo Link: https://youtu.be/S7kRFLz4B54
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

void printPlayer(uint8_t playerX, uint8_t playerY, uint8_t remove) {
    // remove = 0 --> color
    // remove = 1 --> black
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
            if (!remove) {
                createPixel(DRx+xBuffer,DRy+yBuffer, DARK_PURPLE);
            }
            else {
                createPixel(DRx+xBuffer,DRy+yBuffer, BLACK);
            }
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
            if (!remove) {
                createPixel(LRx+xBuffer,LRy+yBuffer, LIGHT_PURPLE);
            }
            else {
                createPixel(LRx+xBuffer,LRy+yBuffer, BLACK);
            }
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
            if (!remove) {
                createPixel(Sx+xBuffer,Sy+yBuffer, SKIN_COLOR);
            }
            else {
                createPixel(Sx+xBuffer,Sy+yBuffer, BLACK);
            }
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
            if (!remove) {
                createPixel(Bx+xBuffer,By+yBuffer, GREY);
            }
            else {
                createPixel(Bx+xBuffer,By+yBuffer, BLACK);
            }
        }

    // // ------------------------

    // // ------------------------ EYE UP
        
        uint8_t eyeUp[1][2] = {{51,114}};

        int EUx = eyeUp[1][1];
        int EUy = eyeUp[1][0];
        if (!remove) {
            createPixel(EUx+xBuffer,EUy+yBuffer, UP_EYE);
        }
        else {
            createPixel(EUx+xBuffer,EUy+yBuffer, BLACK);
        }
        
    // // ------------------------

    // // ------------------------ EYE DOWN

        uint8_t eyeDown[1][2] = {{51,115}};

        int EDx = eyeDown[1][1];
        int EDy = eyeDown[1][0];
        if (!remove) {
            createPixel(EDx+xBuffer,EDy+yBuffer, DOWN_EYE);
        }
        else {
            createPixel(EDx+xBuffer,EDy+yBuffer, BLACK);
        }
    // ------------------------

    // ------------------------ STAFF LIGHT

        uint8_t staffLight[12][2] = {{58, 109},{58, 111},{57, 112},{57, 113},{57, 114},
                                    {57, 115},{57, 118},{57, 119},{57, 121},{57, 122},
                                    {57, 123},{57, 124}};

        for (int i = 0; i < 12; ++i) {
            int SLx = staffLight[i][1];
            int SLy = staffLight[i][0];
            if (!remove) {
                createPixel(SLx+xBuffer,SLy+yBuffer, LIGHT_BROWN);
            }
            else {
                createPixel(SLx+xBuffer,SLy+yBuffer, BLACK);
            }
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
            if (!remove) {
                createPixel(SDx+xBuffer,SDy+yBuffer, DARK_BROWN);
            }
            else {
                createPixel(SDx+xBuffer,SDy+yBuffer, BLACK);
            }
        }

    // ------------------------
}

void printWizard(uint8_t combat, uint8_t whichWizard) {
    //combat = 0 --> overworld
    //combat = 1 --> combat

    uint16_t lightRobeColor = 0;
    uint16_t darkRobeColor = 0;
    int xBuffer = 0;
    int yBuffer = 0;

    // OVERWORLD WIZARDS
    if ((combat == 0) && (whichWizard == 1)) {
        // blue wizard
        lightRobeColor = LIGHT_BLUE;
        darkRobeColor = DARK_BLUE;
        yBuffer = -21;
        xBuffer = -63;
    }
    if ((combat == 0) && (whichWizard == 2)) {
        // red wizard
        lightRobeColor = LIGHT_RED;
        darkRobeColor = DARK_RED;
        yBuffer = 42;
        xBuffer = -21;
    }


    //COMBAT WIZARDS
    if ((combat == 1) && (whichWizard == 1)) {
        // blue wizard
        lightRobeColor = LIGHT_BLUE;
        darkRobeColor = DARK_BLUE;
        xBuffer = -71;
        yBuffer = 13;
    }
    if ((combat == 1) && (whichWizard == 2)) {
        // red wizard
        lightRobeColor = LIGHT_RED;
        darkRobeColor = DARK_RED;
        xBuffer = -71;
        yBuffer = 13;
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

void printCursor(uint8_t which, uint8_t remove) {
    // remove = 0 --> color
    // remove = 1 --> black
    int xBuffer = 0;

    if (which == 1) {
        //water
        xBuffer = 20;
    }

    uint8_t cursor[46][2] = {
        {83, 73}, {83, 74}, {78, 75}, {83, 75}, {88, 75},
        {79, 76}, {83, 76}, {87, 76}, {80, 77}, {83, 77},
        {86, 77}, {81, 78}, {83, 78}, {85, 78}, {82, 79},
        {83, 79}, {84, 79}, {77, 80}, {78, 80}, {79, 80},
        {80, 80}, {81, 80}, {82, 80}, {83, 80}, {84, 80},
        {85, 80}, {86, 80}, {87, 80}, {88, 80}, {89, 80},
        {82, 81}, {83, 81}, {84, 81}, {81, 82}, {83, 82},
        {85, 82}, {80, 83}, {83, 83}, {86, 83}, {79, 84},
        {83, 84}, {87, 84}, {78, 85}, {83, 85}, {88, 85},
        {83, 86}
    };

    for (int i = 0; i < 46; ++i) {
        int DRx = cursor[i][1];
        int DRy = cursor[i][0];
        if (!remove) {
            createPixel(DRx+xBuffer,DRy, WHITE);
        }
        else {
            createPixel(DRx+xBuffer,DRy, BLACK);
        }
    }
}

void printE(uint8_t water) {
    uint8_t bufferX = 0;
    uint8_t bufferY = 0;

    if (water) {
        bufferX = 20;
        bufferY = 35;
    }

    uint8_t E[31][2] = {
    {17, 74}, {18, 74}, {19, 74}, {20, 74}, {21, 74}, {22, 74}, {23, 74},
    {17, 75}, {17, 76}, {17, 77}, {17, 78}, {17, 79}, {17, 80}, {18, 80},
    {19, 80}, {20, 80}, {21, 80}, {22, 80}, {23, 80}, {17, 81}, {17, 82},
    {17, 83}, {17, 84}, {17, 85}, {17, 86}, {18, 86}, {19, 86}, {20, 86},
    {21, 86}, {22, 86}, {23, 86}
    };

    for (int i = 0; i < 31; ++i) {
        uint8_t DRx = E[i][1];
        uint8_t DRy = E[i][0];
        createPixel(DRx+bufferX,DRy+bufferY,WHITE);
    }
}

void printA(uint8_t water) {
    uint8_t bufferX = 0;
    uint8_t bufferY = 0;

    if (water) {
        bufferX = 20;
        bufferY = 5;
    }

    uint8_t A[38][2] = {
    {26, 74}, {27, 74}, {28, 74}, {29, 74}, {30, 74}, {31, 74}, {32, 74}, {33, 74},
    {26, 75}, {33, 75}, {26, 76}, {33, 76}, {26, 77}, {33, 77}, {26, 78}, {33, 78},
    {26, 79}, {33, 79}, {26, 80}, {27, 80}, {28, 80}, {29, 80}, {30, 80}, {31, 80},
    {32, 80}, {33, 80}, {26, 81}, {33, 81}, {26, 82}, {33, 82}, {26, 83}, {33, 83},
    {26, 84}, {33, 84}, {26, 85}, {33, 85}, {26, 86}, {33, 86}
    };

    for (int i = 0; i < 38; ++i) {
        uint8_t DRx = A[i][1];
        uint8_t DRy = A[i][0];
        createPixel(DRx+bufferX,DRy+bufferY,WHITE);
    }
}

void printR(uint8_t water) {
    uint8_t bufferX = 0;
    uint8_t bufferY = 0;

    if (water) {
        bufferX = 20;
        bufferY = 25;
    }

    uint8_t R[38][2] = {
    {36, 74}, {37, 74}, {38, 74}, {39, 74}, {40, 74}, {41, 74}, {42, 74}, {43, 74},
    {36, 75}, {43, 75}, {36, 76}, {43, 76}, {36, 77}, {43, 77}, {36, 78}, {43, 78},
    {36, 79}, {37, 79}, {38, 79}, {39, 79}, {40, 79}, {41, 79}, {42, 79}, {43, 79},
    {36, 80}, {37, 80}, {36, 81}, {38, 81}, {36, 82}, {39, 82}, {36, 83}, {40, 83},
    {36, 84}, {41, 84}, {36, 85}, {42, 85}, {36, 86}, {43, 86}
    };

    for (int i = 0; i < 38; ++i) {
        uint8_t DRx = R[i][1];
        uint8_t DRy = R[i][0];
        createPixel(DRx+bufferX,DRy+bufferY,WHITE);
    }

}

void printT(uint8_t water) {
    uint8_t bufferX = 0;
    uint8_t bufferY = 0;

    if (water) {
        bufferX = 20;
        bufferY = -4;
    }

    uint8_t T[21][2] = {
    {46, 74}, {47, 74}, {48, 74}, {49, 74}, {50, 74}, {51, 74}, {52, 74},
    {53, 74}, {54, 74}, {50, 75}, {50, 76}, {50, 77}, {50, 78}, {50, 79},
    {50, 80}, {50, 81}, {50, 82}, {50, 83}, {50, 84}, {50, 85}, {50, 86}
    };

    for (int i = 0; i < 21; ++i) {
        uint8_t DRx = T[i][1];
        uint8_t DRy = T[i][0];
        createPixel(DRx+bufferX,DRy+bufferY,WHITE);
    }
}

void printH() {
    uint8_t H[32][2] = {
        {57, 74}, {64, 74}, {57, 75}, {64, 75}, {57, 76}, {64, 76}, {57, 77}, {64, 77}, 
        {57, 78}, {64, 78}, {57, 79}, {64, 79}, {57, 80}, {58, 80}, {59, 80}, {60, 80}, 
        {61, 80}, {62, 80}, {63, 80}, {64, 80}, {57, 81}, {64, 81}, {57, 82}, {64, 82}, 
        {57, 83}, {64, 83}, {57, 84}, {64, 84}, {57, 85}, {64, 85}, {57, 86}, {64, 86}
    };

    for (int i = 0; i < 32; ++i) {
        uint8_t DRx = H[i][1];
        uint8_t DRy = H[i][0];
        createPixel(DRx,DRy,WHITE);
    }

}

void printW() {
    uint8_t W[40][2] = {
        {17, 94}, {28, 94}, {17, 95}, {28, 95}, {17, 96}, {28, 96}, {17, 97}, {18, 97}, {27, 97}, {28, 97},
        {18, 98}, {27, 98}, {18, 99}, {27, 99}, {18, 100}, {27, 100}, {18, 101}, {19, 101}, {22, 101}, {23, 101},
        {26, 101}, {27, 101}, {19, 102}, {22, 102}, {23, 102}, {26, 102}, {19, 103}, {21, 103}, {22, 103}, {23, 103},
        {24, 103}, {26, 103}, {19, 104}, {21, 104}, {24, 104}, {26, 104}, {20, 105}, {25, 105}, {20, 106}, {25, 106}
    };

    for (int i = 0; i < 40; ++i) {
        uint8_t DRx = W[i][1];
        uint8_t DRy = W[i][0];
        createPixel(DRx,DRy,WHITE);
    }
}

void printSpells() {
    printE(0);
    printA(0);
    printR(0);
    printT(0);
    printH();
    printW();
    printA(1);
    printT(1);
    printE(1);
    printR(1);
}

#endif