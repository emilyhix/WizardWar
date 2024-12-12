///////////////////////////////////////////////////////
// CS 120B Custom Lab Project Demo #2 - ehix001_main.cpp
// Author: Emily Hix
// 12/4/2024
// Video Demo 1 Link: https://youtu.be/SvAbyeLqzjc
// Video Demo 2 Link: https://youtu.be/ZwP4u5FAlhQ
///////////////////////////////////////////////////////
#include "timerISR.h"
#include "helper.h"
#include "periph.h"
#include "spiAVR.h"
#include "LCD.h"
#include "ehix001_screenPrint.h"
#include "serialATmega.h"
#include "ehix001_queue.h"

bool reset = 0;
bool select = 0;
bool lose = 0;
bool blueWizard = 1;
bool redWizard = 1;
uint8_t gameMode = 0; // 0 - title, 1 - room 1 (BLUE), 2 - room 2 (RED), 3 - combat BLUE, 4 - combat RED, 5 - you win, 6 - you lose
uint8_t playerX = 2;
uint8_t playerY = 5;
uint8_t cursor = 1; // 1 - EARTH, 2 - WATER
struct Queue* up = createQueue(2);
struct Queue* down = createQueue(2);
struct Queue* left = createQueue(2);
struct Queue* right = createQueue(2);
struct Queue* changeRoom = createQueue(2);
struct Queue* cursorUp = createQueue(2);
struct Queue* cursorDown = createQueue(2);

#define NUM_TASKS 10

int TickFct_PrintScreen(int);
int TickFct_SelectButton(int);
int TickFct_JoystickInput(int);
int TickFct_PlayerCoords(int);
int TickFct_UpdateMode(int);
int TickFct_BuzzerMusic(int);
int TickFct_TextLCD(int);
int TickFct_CursorPrint(int);
int TickFct_Battle(int);
int TickFct_ResetButton(int);

enum States_PrintScreen {INIT_PS, IDLE_PS, TITLE_PS, ROOM1_PS, ROOM2_PS, COMBAT1_PS, COMBAT2_PS};
enum States_SelectButton {INIT_SB, PRESS_SB};
enum States_JoystickInput {INIT_JI, WAIT};
enum States_PlayerCoords {UPDATE_PC};
enum States_CursorPrint {UPDATE_CURSOR};
enum States_UpdateMode{INIT_UM, TITLE, OVERWORLD, COMBAT1, COMBAT2, END};
enum States_BuzzerMusic{OFF, NOTE1, NOTE2, NOTE3, NOTE4, LOSE1, LOSE2, LOSE3, WIN1, WIN2, WIN3};
enum States_TextLCD{INIT_LCD, IDLE_LCD, DEFEATED, COMBAT1_LCD, COMBAT2_LCD, WS_LCD, ES_LCD, WIN_LCD, LOSE_LCD};
enum States_Battle {INIT_BATTLE};
enum States_ResetButton {INIT_RB, PRESS_RB};

const unsigned long PrintScreenPeriod = 200;
const unsigned long SelectButtonPeriod = 200;
const unsigned long ResetButtonPeriod = 200;
const unsigned long JoystickInputPeriod = 200;
const unsigned long PlayerCoordsPeriod = 200;
const unsigned long CursorPrintPeriod = 200;
const unsigned long UpdateModePeriod = 200;
const unsigned long BuzzerMusicPeriod = 1;
const unsigned long TextLCDPeriod = 200;
const unsigned long BattlePeriod = 100;
const unsigned long GCD_PERIOD = 1;

typedef struct _task{
	signed 	 char state; 		//Task's current state
	unsigned long period; 		//Task period
	unsigned long elapsedTime; 	//Time elapsed since last task tick
	int (*TickFct)(int); 		//Task tick function
} task;

task tasks[NUM_TASKS];

void TimerISR() {
	for ( unsigned int i = 0; i < NUM_TASKS; i++ ) {
		if (tasks[i].elapsedTime == tasks[i].period ) {
			tasks[i].state = tasks[i].TickFct(tasks[i].state);
			tasks[i].elapsedTime = 0;
		}
		tasks[i].elapsedTime += GCD_PERIOD;
	}
}

bool validMovement(unsigned char direction) {
    // 1 - up
    // 2 - down
    // 3 - left
    // 4 - right
    if ((playerX <= 0) && (direction == 3)) {
        return false;
    }
    else if ((playerX >= 5) && (direction == 4)) {
        return false;
    }
    else if ((playerY <= 0) && (direction == 1)) {
        return false;
    }
    else if ((playerY >= 5) && (direction == 2)) {
        return false;
    }
    else return true;
}

int main(void) {

    //Initialize PORTC
    DDRC = 0x09;
    PORTC = 0xF6;
    //Initialize PORTD as output
    DDRD = 0xFF;
    PORTD = 0x00;
    //Initialize PORTB as output
    DDRB = 0xFF;
    PORTB = 0x00;

    ADC_init();
    // serial_init(9600);
    SPI_INIT();
    ST7735_init();
    lcd_init();
    lcd_send_command(LCD_CMD_DISPLAY_NO_CURSOR);

    TCCR1A |= (1 << WGM11) | (1 << COM1A1); //COM1A1 sets it to channel A
    TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11); //CS11 sets the prescaler to be 8
    //WGM11, WGM12, WGM13 set timer to fast pwm mode

    ICR1 = 39999; //20ms pwm period
    OCR1A =  39999;

    unsigned char i = 0;
    tasks[i].state = INIT_PS;
    tasks[i].period = PrintScreenPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_PrintScreen;
    ++i;
    tasks[i].state = INIT_SB;
    tasks[i].period = SelectButtonPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_SelectButton;
    ++i;
    tasks[i].state = INIT_JI;
    tasks[i].period = JoystickInputPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_JoystickInput;
    ++i;
    tasks[i].state = UPDATE_PC;
    tasks[i].period = PlayerCoordsPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_PlayerCoords;
    ++i;
    tasks[i].state = INIT_UM;
    tasks[i].period = UpdateModePeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_UpdateMode;
    ++i;
    tasks[i].state = OFF;
    tasks[i].period = BuzzerMusicPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_BuzzerMusic;
    ++i;
    tasks[i].state = INIT_LCD;
    tasks[i].period = TextLCDPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_TextLCD;
    ++i;
    tasks[i].state = UPDATE_CURSOR;
    tasks[i].period = CursorPrintPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_CursorPrint;
    ++i;
    tasks[i].state = INIT_BATTLE;
    tasks[i].period = BattlePeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_Battle;
    ++i;
    tasks[i].state = INIT_RB;
    tasks[i].period = ResetButtonPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_ResetButton;

    TimerSet(GCD_PERIOD);
    TimerOn();

    while (1) {}

    return 0;
}

int TickFct_PrintScreen(int state) {
    static uint8_t localState;

    switch (state) {
        //STATE TRANSITIONS
        case INIT_PS:
            state = TITLE_PS;
            break;

        case IDLE_PS:
            if (localState != gameMode) {
                localState = gameMode;
                if ((localState == 0) || (localState == 5) || (localState == 6)) {
                    state = TITLE_PS;
                }
                if (localState == 1) {
                    state = ROOM1_PS;
                }
                if (localState == 2) {
                    state = ROOM2_PS;
                }
                if (localState == 3) {
                    state = COMBAT1_PS;
                }
                if (localState == 4) {
                    state = COMBAT2_PS;
                }
            }
            else {
                state = IDLE_PS;
            }
            break;

        case TITLE_PS:
            state = IDLE_PS;
            break;

        case ROOM1_PS:
            state = IDLE_PS;
            break;

        case ROOM2_PS:
            state = IDLE_PS;
            break;

        case COMBAT1_PS:
            state = IDLE_PS;
            break;

        case COMBAT2_PS:
            state = IDLE_PS;
            break;

        default:
            state = INIT_PS;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case INIT_PS:
            localState = gameMode;
            break;
        
        case IDLE_PS:
            break;

        case TITLE_PS:
            fillScreen(0x0000); //clear screen
            //printTitle
            state = IDLE_PS;
            break;

        case ROOM1_PS:
            fillScreen(0x0000); //clear screen
            if (blueWizard) {
                printPlayer(2,5,0);
                printWizard(0,1);
            }
            else {
                printPlayer(playerX, playerY, 0);
            }
            break;

        case ROOM2_PS:
            fillScreen(0x0000); //clear screen
            if (redWizard) {
                printPlayer(2,5,0);
                printWizard(0,2);
            }
            else {
                printPlayer(playerX, playerY, 0);
            }
            break;
        
        case COMBAT1_PS:
            fillScreen(0x0000); //clear screen
            printWizard(1,1);
            printSpells();
            printCursor(0, 0);
            break;

        case COMBAT2_PS:
            fillScreen(0x0000); //clear screen
            printWizard(1,2);
            printSpells();
            printCursor(0, 0);
            break;

        default:
            break;
    }
    return state;
}

int TickFct_SelectButton(int state) {
    switch (state) {
        //STATE TRANSITIONS
        case INIT_SB:
            if ((PINC>>1) & 0x01) {
                state = PRESS_SB;
            }
            else {
                state = INIT_SB;
            }
            break;
        
        case PRESS_SB:
            if ((PINC>>1) & 0x01) {
                state = PRESS_SB;
            }
            else {
                select = 1;
                state = INIT_SB;
            }
            break;
        
        default:
            state = INIT_SB;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case INIT_SB:
            break;
        
        case PRESS_SB:
            break;
        
        default:
            break;
    }
    return state;
}

int TickFct_JoystickInput(int state) {
    switch (state) {
        //STATE TRANSITIONS
        case INIT_JI:
            if (reset) {
                cursor = 1;
            }
            if (ADC_read(4) > 700) {
                if ((gameMode == 1) || (gameMode == 2)) {
                    enqueue(down, 1);
                }
                if ((gameMode == 3) || (gameMode == 4)) {
                    enqueue(cursorDown, 1);
                    cursor = 2;
                }
                state = WAIT;
            }
            if (ADC_read(4) < 400) {
                if ((gameMode == 1) || (gameMode == 2)) {
                    enqueue(up, 1);
                }
                if ((gameMode == 3) || (gameMode == 4)) {
                    enqueue(cursorUp, 1);
                    cursor = 1;
                }
                state = WAIT;
            }
            if (ADC_read(5) > 700) {
                if ((gameMode == 1) || (gameMode == 2)) {
                    enqueue(left, 1);
                }
                state = WAIT;
            }
            if (ADC_read(5) < 400) {
                if ((gameMode == 1) || (gameMode == 2)) {
                    enqueue(right, 1);
                }
                state = WAIT;
            }
            break;

        case WAIT:
            if (ADC_read(4) > 700 || ADC_read(4) < 400 || ADC_read(5) > 700 || ADC_read(5) < 400) {
                state = WAIT;
            }
            else {
                state = INIT_JI;
            }
            break;

        default:
            state = INIT_JI;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case INIT_JI:
            break;
        
        case WAIT:
            break;

        default:
            break;
    }
    return state;
}

int TickFct_PlayerCoords(int state) {
    switch (state) {
        //STATE TRANSITIONS
        case UPDATE_PC:
            if (reset) {
                playerX = 2;
                playerY = 5;
                if (!isEmpty(changeRoom)) {
                    dequeue(changeRoom);
                }
            }
            if (!(isEmpty(up))) {
                if (validMovement(1)) {
                    printPlayer(playerX, playerY, 1);
                    --playerY;
                    printPlayer(playerX, playerY, 0);
                }
                else {
                    if (isEmpty(changeRoom)) {
                        enqueue(changeRoom, 1);
                        playerX = 2;
                        playerY = 5;
                    }
                }
                dequeue(up);
            }
            if (!(isEmpty(down))) {
                if (validMovement(2)) {
                    printPlayer(playerX, playerY, 1);
                    ++playerY;
                    printPlayer(playerX, playerY, 0);
                }
                dequeue(down);
            }
            if (!(isEmpty(left))) {
                if (validMovement(3)) {
                    printPlayer(playerX, playerY, 1);
                    --playerX;
                    printPlayer(playerX, playerY, 0);
                }
                dequeue(left);
            }
            if (!(isEmpty(right))) {
                if (validMovement(4)) {
                    printPlayer(playerX, playerY, 1);
                    ++playerX;
                    printPlayer(playerX, playerY, 0);
                }
                dequeue(right);
            }
            break;

        default:
            state = UPDATE_PC;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case UPDATE_PC:
            break;

        default:
            break;
    }
    return state;
}

int TickFct_UpdateMode(int state) {
    switch (state) {
        //STATE TRANSITIONS
        case INIT_UM:
            state = TITLE;
            break;

        case TITLE:
            if (select) {
                gameMode = 1;
                select = 0;
                state = OVERWORLD;
            }
            break;

        case OVERWORLD:
            if (reset) {
                reset = 0;
                gameMode = 0;
                state = TITLE;
            }
            if (!isEmpty(changeRoom)) {
                gameMode = 2;
            }
            if ((playerX == 1) && (playerY == 2) && (gameMode == 1) && (blueWizard)) {
                gameMode = 3;
                state = COMBAT1;
            }
            if ((playerX == 4) && (playerY == 4) && (gameMode == 2) && (redWizard)) {
                gameMode = 4;
                state = COMBAT2;
            }
            if (lose) {
                gameMode = 6;
            }
            break;

        case COMBAT1:
            if (reset) {
                reset = 0;
                gameMode = 0;
                state = TITLE;
            }
            if (!blueWizard) {
                gameMode = 1;
                state = OVERWORLD;
            }
            if (lose) {
                gameMode = 6;
                state = END;
            }
            break;

        case COMBAT2:
            if (reset) {
                reset = 0;
                gameMode = 0;
                state = TITLE;
            }
            if (!blueWizard && !redWizard) {
                gameMode = 5;
                state = END;
            }
            if (lose) {
                gameMode = 6;
                state = END;
            }
            break;

        case END:
            if (reset) {
                reset = 0;
                gameMode = 0;
                state = TITLE;
            }
            break;

        default:
            state = INIT_UM;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case INIT_UM:
            gameMode = 0;
            break;

        case TITLE:
            reset = 0;
            break;

        case OVERWORLD:
            break;

        case COMBAT1:
            break;

        case COMBAT2:
            break;
        
        case END:
            break;

        default:
            break;
    }
    return state;
}

int TickFct_BuzzerMusic(int state) {
    static uint16_t count, musicTime;

    switch (state) {
        //STATE TRANSITIONS
        case OFF:
            if (!((gameMode == 0) || (gameMode == 5) || (gameMode == 6))) {
                count = 0;
                state = NOTE1;
            }
            else {
                ICR1 = 39999;
                OCR1A =  39999;
                state = OFF;
            }
            break;

        case NOTE1:
            if ((gameMode == 0)) {
                ICR1 = 39999;
                OCR1A =  39999;
                state = OFF;
            }
            else if ((gameMode == 5)) {
                ICR1 = 7632; //C4
                OCR1A =  ICR1/2;
                musicTime = 500;
                state = WIN1;
            }
            else if ((gameMode == 6)) {
                ICR1 = 8129; //B3
                OCR1A =  ICR1/2;
                musicTime = 750;
                state = LOSE1;
            }
            else if (count < musicTime) {
                ICR1 = 7632; //C4
                OCR1A =  ICR1/2;
                state = NOTE1;
            }
            else {
                count = 0;
                state = NOTE2;
            }
            break;
            
        case NOTE2:
            if ((gameMode == 0)) {
                ICR1 = 39999;
                OCR1A =  39999;
                state = OFF;
            }
            else if (count < musicTime) {
                ICR1 = 6060; //E4
                OCR1A =  ICR1/2;
                state = NOTE2;
            }
            else {
                count = 0;
                state = NOTE3;
            }
            break;

        case NOTE3:
            if ((gameMode == 0)) {
                ICR1 = 39999;
                OCR1A =  39999;
                state = OFF;
            }
            else if (count < musicTime) {
                ICR1 = 5713; //F4
                OCR1A =  ICR1/2;
                state = NOTE3;
            }
            else {
                count = 0;
                state = NOTE4;
            }
            break;

        case NOTE4:
            if ((gameMode == 0)) {
                ICR1 = 39999;
                OCR1A =  39999;
                state = OFF;
            }
            else if (count < musicTime) {
                ICR1 = 6060; //E4
                OCR1A =  ICR1/2;
                state = NOTE4;
            }
            else {
                count = 0;
                state = NOTE1;
            }
            break;

        case LOSE1:
            if (count < musicTime) {
                state = LOSE1;
            }
            else {
                count = 0;
                ICR1 = 9090; //A3
                OCR1A =  ICR1/2;
                state = LOSE2;
            }
            break;

        case LOSE2:
            if (count < musicTime) {
                state = LOSE2;
            }
            else {
                count = 0;
                ICR1 = 10203; //G3
                OCR1A =  ICR1/2;
                state = LOSE3;
            }
            break;

        case LOSE3:
            if (count < musicTime) {
                state = LOSE3;
            }
            else {
                count = 0;
                ICR1 = 11493; //F3
                OCR1A =  ICR1/2;
                state = OFF;
            }
            break;

        case WIN1:
            if (count < musicTime) {
                state = WIN1;
            }
            else {
                count = 0;
                ICR1 = 6825; //D4
                OCR1A =  ICR1/2;
                state = WIN2;
            }
            break;

        case WIN2:
            if (count < musicTime) {
                state = WIN2;
            }
            else {
                count = 0;
                ICR1 = 6060; //E4
                OCR1A =  ICR1/2;
                state = WIN3;
            }
            break;

        case WIN3:
            if (count < musicTime) {
                state = WIN3;
            }
            else {
                count = 0;
                ICR1 = 5713; //F4
                OCR1A =  ICR1/2;
                state = OFF;
            }
            break;

        default:
            state = OFF;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case OFF:
            break;

        case NOTE1:
            if ((gameMode == 1) || (gameMode == 2)) {
                musicTime = 400;
            }
            else if ((gameMode == 3) || (gameMode == 4)) {
                musicTime = 150;
            }
            ++count;
            break;

        case NOTE2:
            if ((gameMode == 1) || (gameMode == 2)) {
                musicTime = 400;
            }
            else if ((gameMode == 3) || (gameMode == 4)) {
                musicTime = 150;
            }
            ++count;
            break;

        case NOTE3:
            if ((gameMode == 1) || (gameMode == 2)) {
                musicTime = 400;
            }
            else if ((gameMode == 3) || (gameMode == 4)) {
                musicTime = 150;
            }
            ++count;
            break;

        case NOTE4:
            if ((gameMode == 1) || (gameMode == 2)) {
                musicTime = 450;
            }
            else if ((gameMode == 3) || (gameMode == 4)) {
                musicTime = 150;
            }
            ++count;
            break;

        case LOSE1:
            ++count;
            break;

        case LOSE2:
            ++count;
            break;

        case LOSE3:
            ++count;
            break;

        case WIN1:
            ++count;
            break;

        case WIN2:
            ++count;
            break;

        case WIN3:
            ++count;
            break;

        default:
            break;
    }
    return state;
}

int TickFct_TextLCD(int state) {
    static uint8_t counter;
    static uint8_t localState;
    static char startText1[17];
    static char startText2[17];
    static char encounter1[17];
    static char encounter2F[13];
    static char encounter2W[14];
    static char chooseSpell[16];
    static char waterSpell[13];
    static char earthSpell[13];
    static char youUsed[13];
    static char playerDied[14];
    static char loseGame[15];
    static char wizardsDead[17];
    static char winGame[15];
    static char defeated[17];
    static char score[8];

    sprintf(startText1, "Press the select");
    sprintf(startText2, "button to start.");
    sprintf(encounter1, "You see the evil");
    sprintf(encounter2F, "Fire Wizard!");
    sprintf(encounter2W, "Water Wizard!");
    sprintf(chooseSpell, "Choose a spell.");
    sprintf(waterSpell, "Water Spell!");
    sprintf(earthSpell, "Earth Spell!");
    sprintf(youUsed, "You used the");
    sprintf(playerDied, "You died! You");
    sprintf(loseGame, "lost the game!");
    sprintf(wizardsDead, "Both wizards are");
    sprintf(winGame, "gone! You won!");
    sprintf(defeated, "Wizard defeated!");
    sprintf(score, "Score: ");

    switch(state) {
        //STATE TRANSITIONS
        case INIT_LCD:
            lcd_goto_xy(0,0);
            lcd_write_str(startText1);
            lcd_goto_xy(1,0);
            lcd_write_str(startText2);
            state = IDLE_LCD;
            break;
        
        case IDLE_LCD:
            if (localState != gameMode) {
                localState = gameMode;
                if (localState == 0) {
                    lcd_clear();
                    state = INIT_LCD;
                }
                if (localState == 1) {
                    lcd_clear();
                }
                if (localState == 2) {
                    lcd_clear();
                }
                if (localState == 3) {
                    lcd_clear();
                    state = COMBAT1_LCD;
                }
                if (localState == 4) {
                    lcd_clear();
                    state = COMBAT1_LCD;
                }
            }
            else {
                state = IDLE_LCD;
            }
            break;

        case DEFEATED:
            if (counter >= 5) {
                lcd_clear();
                counter = 0;
                state = IDLE_LCD;
            }
            break;

        case COMBAT1_LCD:
            if (counter >= 5) {
                counter = 0;
                lcd_clear();
                state = COMBAT2_LCD;
            }
            break;

        case COMBAT2_LCD:
            if (reset) {
                lcd_clear();
                state = IDLE_LCD;
            }
            if ((select) && (cursor == 2)) {
                lcd_clear();
                counter = 0;
                state = WS_LCD;
            }
            if ((select) && (cursor == 1)) {
                lcd_clear();
                counter = 0;
                state = ES_LCD;
            }
            break;

        case WS_LCD:
            if (counter >= 10) {
                lcd_clear();
                counter = 0;
                if (lose) {
                    state = LOSE_LCD;
                }
                else if (!blueWizard && !redWizard) {
                    state = WIN_LCD;
                }
                else {
                    state = DEFEATED;
                }
            }
            break;

        case ES_LCD:
            if (counter >= 10) {
                lcd_clear();
                counter = 0;
                if (lose) {
                    state = LOSE_LCD;
                }
                else if (!blueWizard && !redWizard) {
                    state = WIN_LCD;
                }
                else {
                    state = DEFEATED;
                }
            }
            break;

        case WIN_LCD:
            if (counter >= 10) {
                state = IDLE_LCD;
            }
            break;

        case LOSE_LCD:
            if (counter >= 10) {
                state = IDLE_LCD;
            }
            break;

        default:
            state = INIT_LCD;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case INIT_LCD:
            localState = gameMode;
            break;

        case IDLE_LCD:
            counter = 0;
            break;

        case DEFEATED:
            ++counter;
            lcd_goto_xy(0,0);
            lcd_write_str(defeated);
            lcd_goto_xy(1,0);
            lcd_write_str(score);
            lcd_write_character('5');
            lcd_write_character('0'); 
            break;

        case COMBAT1_LCD:
            ++counter;
            lcd_goto_xy(0,0);
            lcd_write_str(encounter1);
            lcd_goto_xy(1,0);
            if (gameMode == 3) {
                lcd_write_str(encounter2W);
            }
            if (gameMode == 4) {
                lcd_write_str(encounter2F);
            }
            break;

        case COMBAT2_LCD:
            ++counter;
            lcd_goto_xy(0,0);
            lcd_write_str(chooseSpell);
            break;

        case WS_LCD:
            ++counter;
            lcd_goto_xy(0,0);
            lcd_write_str(youUsed);
            lcd_goto_xy(1,0);
            lcd_write_str(waterSpell);
            break;

        case ES_LCD:
            ++counter;
            lcd_goto_xy(0,0);
            lcd_write_str(youUsed);
            lcd_goto_xy(1,0);
            lcd_write_str(earthSpell);
            break;

        case WIN_LCD:
            ++counter;
            if (counter >= 5) {
                lcd_goto_xy(0,0);
                lcd_write_str(wizardsDead);
                lcd_goto_xy(1,0);
                lcd_write_str(winGame);
            }
            else {
                lcd_clear();
                lcd_write_str(score);
                lcd_write_character('1');
                lcd_write_character('0');
                lcd_write_character('0');
                lcd_write_character('!');
                lcd_write_character('!');   
            }
            break;

        case LOSE_LCD:
            ++counter;
            if (counter >= 5) {
                lcd_goto_xy(0,0);
                lcd_write_str(playerDied);
                lcd_goto_xy(1,0);
                lcd_write_str(loseGame);
            }
            else {
                lcd_clear();
                lcd_write_str(score);
                lcd_write_character('0');
                lcd_write_character('!');   
            }
            break;

        default:
            break;
    }
    return state;
}

int TickFct_CursorPrint(int state) {
    switch(state) {
        //STATE TRANSITIONS
        case UPDATE_CURSOR:
            if ((gameMode == 3) || (gameMode == 4)) {
                if (!isEmpty(cursorDown)) {
                    printCursor(0, 1);
                    printCursor(1, 0);
                    dequeue(cursorDown);
                }
                if (!isEmpty(cursorUp)) {
                    printCursor(1, 1);
                    printCursor(0, 0);
                    dequeue(cursorUp);
                }
            }
            break;

        default:
            state = UPDATE_CURSOR;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case UPDATE_CURSOR:
            break;

        default:
            state = UPDATE_CURSOR;
            break;
    }
    return state;
}

int TickFct_Battle(int state) {
    switch(state) {
        //STATE TRANSITIONS
        case INIT_BATTLE:
            state = INIT_BATTLE;
            break;

        default:
            state = INIT_BATTLE;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case INIT_BATTLE:
            if (reset) {
                PORTC = SetBit(PORTC, 0, 0);
                PORTB = SetBit(PORTB, 4, 0);
                blueWizard = 1;
                redWizard = 1;
                lose = 0;
            }
            if ((select) && ((gameMode == 3) || (gameMode == 4))) {
                select = 0;
                if ((cursor == 1) && (gameMode == 4)) {
                    lose = 1;
                    PORTC = SetBit(PORTC, 0, 0);
                    PORTB = SetBit(PORTB, 4, 0);
                }
                else if ((cursor == 1) && (gameMode == 3)) {
                    blueWizard = 0;
                    PORTC = SetBit(PORTC, 0, 1);
                }
                if ((cursor == 2) && (gameMode == 3)) {
                    lose = 1;
                    PORTC = SetBit(PORTC, 0, 0);
                    PORTB = SetBit(PORTB, 4, 0);
                }
                else if ((cursor == 2) && (gameMode == 4)) {
                    redWizard = 0;
                    PORTB = SetBit(PORTB, 4, 1);

                }
            }
            break;

        default:
            break;
    }
    return state;
}

int TickFct_ResetButton(int state) {
    switch (state) {
            //STATE TRANSITIONS
            case INIT_RB:
                if ((PINC>>2) & 0x01) {
                    state = PRESS_RB;
                }
                else {
                    state = INIT_RB;
                }
                break;
            
            case PRESS_RB:
                if ((PINC>>2) & 0x01) {
                    state = PRESS_RB;
                }
                else {
                    reset = 1;
                    state = INIT_RB;
                }
                break;
            
            default:
                state = INIT_RB;
                break;
        }
        switch(state) {
            //STATE ACTIONS
            case INIT_RB:
                break;
            
            case PRESS_RB:
                break;
            
            default:
                break;
        }
        return state;  
}