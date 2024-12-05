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
// #include "serialATmega.h"
#include "ehix001_queue.h"

uint8_t gameMode = 0; // 0 - title, 1 - room1, 2 - room2, 3 - room3
uint8_t playerX = 2;
uint8_t playerY = 5;
unsigned char playerHealth = 50;
struct Queue* up = createQueue(10);
struct Queue* down = createQueue(10);
struct Queue* left = createQueue(10);
struct Queue* right = createQueue(10);

#define NUM_TASKS 7

int TickFct_PrintScreen(int);
int TickFct_SelectButton(int);
int TickFct_JoystickInput(int);
int TickFct_PlayerCoords(int);
int TickFct_UpdateMode(int);
int TickFct_BuzzerMusic(int);
int TickFct_TextLCD(int);

enum States_PrintScreen {INIT_PS, WAIT1, WAIT2, WAIT3};
enum States_SelectButton {INIT_SB, PRESS};
enum States_JoystickInput {INIT_JI, WAIT};
enum States_PlayerCoords {UPDATE_PC};
enum States_UpdateMode{INIT_UM};
enum States_BuzzerMusic{INIT_BM, OFF, NOTE1, NOTE2, NOTE3, NOTE4};
enum States_TextLCD{INIT_LCD, IDLE, ROOM1, ROOM2, ROOM3, YOU_WON};

const unsigned long PrintScreenPeriod = 200;
const unsigned long SelectButtonPeriod = 200;
const unsigned long JoystickInputPeriod = 500;
const unsigned long PlayerCoordsPeriod = 200;
const unsigned long UpdateModePeriod = 200;
const unsigned long BuzzerMusicPeriod = 1;
const unsigned long TextLCDPeriod = 500;
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
    DDRC = 0x08;
    PORTC = 0xF7;
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
    tasks[i].state = INIT_BM;
    tasks[i].period = BuzzerMusicPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_BuzzerMusic;
    ++i;
    tasks[i].state = INIT_LCD;
    tasks[i].period = TextLCDPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_TextLCD;

    TimerSet(GCD_PERIOD);
    TimerOn();

    while (1) {}

    return 0;
}

int TickFct_PrintScreen(int state) {
    switch (state) {
        //STATE TRANSITIONS
        case INIT_PS:
            if (gameMode == 1) {
                printPlayer(2,5);
                printWizard(1);
                state = WAIT1;
            }
            break;

        case WAIT1:
            state = WAIT1;
            break;
        
        case WAIT2:
            break;

        case WAIT3:
            break;
        
        default:
            state = INIT_PS;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case INIT_PS:
            break;
        
        case WAIT1:
            printWizard(gameMode);
            break;

        case WAIT2:
            break;

        case WAIT3:
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
                state = PRESS;
            }
            else {
                state = INIT_SB;
            }
            break;
        
        case PRESS:
            if ((PINC>>1) & 0x01) {
                state = PRESS;
            }
            else {
                if (gameMode == 0) {
                    gameMode = 1;
                }
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
        
        case PRESS:
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
            if (ADC_read(4) > 700) {
                enqueue(down, 1);
                state = WAIT;
            }
            if (ADC_read(4) < 400) {
                enqueue(up, 1);
                state = WAIT;
            }
            if (ADC_read(5) > 700) {
                enqueue(left, 1);
                state = WAIT;
            }
            if (ADC_read(5) < 400) {
                enqueue(right, 1);
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
            if (!(isEmpty(up))) {
                if (validMovement(1)) {
                    removePlayer(playerX, playerY);
                    --playerY;
                    printPlayer(playerX, playerY);
                }
                else {
                    ++gameMode;
                    playerX = 2;
                    playerY = 5;
                    fillScreen(0x0000);
                    printPlayer(playerX, playerY);
                    printWizard(gameMode);
                }
                dequeue(up);
            }
            if (!(isEmpty(down))) {
                if (validMovement(2)) {
                    removePlayer(playerX, playerY);
                    ++playerY;
                    printPlayer(playerX, playerY);
                }
                dequeue(down);
            }
            if (!(isEmpty(left))) {
                if (validMovement(3)) {
                    removePlayer(playerX, playerY);
                    --playerX;
                    printPlayer(playerX, playerY);
                }
                dequeue(left);
            }
            if (!(isEmpty(right))) {
                if (validMovement(4)) {
                    removePlayer(playerX, playerY);
                    ++playerX;
                    printPlayer(playerX, playerY);
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
            break;
        default:
            state = INIT_UM;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case INIT_UM:
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
        case INIT_BM:
            if (count < musicTime) {
                ICR1 = 7661; //130Hz ~ C3
                OCR1A =  ICR1/2;
                state = INIT_BM;
            }
            else {
                count = 0;
                state = NOTE1;
            }
            break;
            
        case NOTE1:
            if (count < musicTime) {
                ICR1 = 6078; //196Hz ~ G3
                OCR1A =  ICR1/2;
                state = NOTE1;
            }
            else {
                count = 0;
                state = NOTE2;
            }
            break;

        case NOTE2:
            if (count < musicTime) {
                ICR1 = 5101; //261Hz ~ C4
                OCR1A =  ICR1/2;
                state = NOTE2;
            }
            else {
                count = 0;
                state = NOTE3;
            }
            break;

        case NOTE3:
            if (count < musicTime) {
                ICR1 = 5730;
                OCR1A =  ICR1/2;
                state = NOTE3;
            }
            else {
                count = 0;
                state = NOTE4;
            }
            break;

        case NOTE4:
            if (count < musicTime) {
                ICR1 = 6078; //OFF
                OCR1A =  ICR1/2;
                state = NOTE4;
            }
            else {
                count = 0;
                state = INIT_BM;
            }
            break;

        default:
            state = INIT_BM;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case INIT_BM:
            if (gameMode == 1) {
                musicTime = 400;
            }
            else if (gameMode == 2) {
                musicTime = 150;
            }
            ++count;
            break;

        case NOTE1:
            if (gameMode == 1) {
                musicTime = 400;
            }
            else if (gameMode == 2) {
                musicTime = 150;
            }
            ++count;
            break;

        case NOTE2:
            if (gameMode == 1) {
                musicTime = 400;
            }
            else if (gameMode == 2) {
                musicTime = 150;
            }
            ++count;
            break;

        case NOTE3:
            if (gameMode == 1) {
                musicTime = 450;
            }
            else if (gameMode == 2) {
                musicTime = 150;
            }
            ++count;
            break;
        
        case NOTE4:
            if (gameMode == 1) {
                musicTime = 400;
            }
            else if (gameMode == 2) {
                musicTime = 150;
            }
            ++count;
            break;
            
        default:
            break;
    }
    return state;
}

int TickFct_TextLCD(int state) {
    static uint8_t localState;
    static char startText1[50];
    static char startText2[50];
    static char CastleEntrance[50];
    static char HP[50];
    static char PotionsRoom[50];
    static char Observatory[50];
    sprintf(startText1, "Press the select");
    sprintf(startText2, "button to start.");
    sprintf(CastleEntrance, "Castle Entrance");
    sprintf(HP, "HP:");
    sprintf(PotionsRoom, "Potions Room");
    sprintf(Observatory, "Observatory");

    switch(state) {
        //STATE TRANSITIONS
        case INIT_LCD:
            lcd_goto_xy(0,0);
            lcd_write_str(startText1);
            lcd_goto_xy(1,0);
            lcd_write_str(startText2);
            state = IDLE;
            break;
        
        case IDLE:
            if (localState != gameMode) {
                localState = gameMode;
                lcd_clear();
                if (localState == 0) {
                    //title
                    state = INIT_LCD;
                }
                if (localState == 1) {
                    // room 1
                    state = ROOM1;
                }
                if (localState == 2) {
                    // room 1
                    state = ROOM2;
                }
                if (localState == 3) {
                    // room 1
                    state = ROOM3;
                }
            }
            break;

        case ROOM1:
            lcd_goto_xy(0,0);
            lcd_write_str(CastleEntrance);
            lcd_goto_xy(1,0);
            lcd_write_str(HP);
            if (playerHealth >= 10) {
                lcd_write_character(playerHealth/10+48);
                lcd_write_character(playerHealth % 10+48);
            }
            else {
                lcd_write_character(playerHealth+48);
            }
            lcd_send_command(LCD_CMD_DISPLAY_NO_CURSOR);
            state = IDLE;
            break;

        case ROOM2:
            lcd_goto_xy(0,0);
            lcd_write_str(PotionsRoom);
            lcd_goto_xy(1,0);
            lcd_write_str(HP);
            if (playerHealth >= 10) {
                lcd_write_character(playerHealth/10+48);
                lcd_write_character(playerHealth % 10+48);
            }
            else {
                lcd_write_character(playerHealth+48);
            }
            lcd_send_command(LCD_CMD_DISPLAY_NO_CURSOR);
            state = IDLE;
            break;

        case ROOM3:
            lcd_goto_xy(0,0);
            lcd_write_str(Observatory);
            lcd_goto_xy(1,0);
            lcd_write_str(HP);
            if (playerHealth >= 10) {
                lcd_write_character(playerHealth/10+48);
                lcd_write_character(playerHealth % 10+48);
            }
            else {
                lcd_write_character(playerHealth+48);
            }
            lcd_send_command(LCD_CMD_DISPLAY_NO_CURSOR);
            state = IDLE;
            break;

        case YOU_WON:
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

        case IDLE:
            break;

        case ROOM1:
            break;

        case ROOM2:
            break;

        case ROOM3:
            break;

        case YOU_WON:
            break;

        default:
            break;
    }
    return state;
}