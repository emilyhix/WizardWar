///////////////////////////////////////////////////////
// CS 120B Custom Lab Project Demo #1 - ehix001_main.cpp
// Author: Emily Hix
// 11/22/24
// Video Demo Link: https://youtu.be/SvAbyeLqzjc
///////////////////////////////////////////////////////
#include "timerISR.h"
#include "helper.h"
#include "periph.h"
#include "spiAVR.h"
#include "LCD.h"
#include "ehix001_screenPrint.cpp"

#include "serialATmega.h"

uint8_t gameMode = 0; // 0 - title, 1 - walking, 2 - interaction, 3 - game over
uint8_t roomNumber = 0; // 0 - main, 1 - , 2 - , 3 - 

#define NUM_TASKS 6

int TickFct_PrintScreen(int);
int TickFct_SelectButton(int);
int TickFct_JoystickInput(int);
int TickFct_PlayerCoords(int);
int TickFct_UpdateMode(int);
int TickFct_BuzzerMusic(int);

enum States_PrintScreen {INIT_PS, WAIT, WAIT2, WAIT3};
enum States_SelectButton {INIT_SB};
enum States_JoystickInput {INIT_JI};
enum States_PlayerCoords {INIT_PC};
enum States_UpdateMode{INIT_UM};
enum States_BuzzerMusic{INIT_BM, OFF, NOTE1, NOTE2, NOTE3, NOTE4};

const unsigned long PrintScreenPeriod = 2000;
const unsigned long SelectButtonPeriod = 200;
const unsigned long JoystickInputPeriod = 500;
const unsigned long PlayerCoordsPeriod = 200;
const unsigned long UpdateModePeriod = 200;
const unsigned long BuzzerMusicPeriod = 500;
const unsigned long GCD_PERIOD = 100;

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

int main(void) {

    //Initialize PORTC as output
    DDRC = 0xFF;
    PORTC = 0x00;
    //Initialize PORTD as output
    DDRD = 0xFF;
    PORTD = 0x00;
    //Initialize PORTB as output
    DDRB = 0xFF;
    PORTB = 0x00;

    // ADC_init();
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
    tasks[i].state = INIT_PC;
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

    TimerSet(GCD_PERIOD);
    TimerOn();

    while (1) {}

    return 0;
}

int TickFct_PrintScreen(int state) {
    switch (state) {
        //STATE TRANSITIONS
        case INIT_PS:
            fillScreen(0x000);
            lcd_goto_xy(0,0);
            lcd_write_str("Press the select");
            lcd_goto_xy(1,0);
            lcd_write_str("button to start.");
            printWizard(1);
            state=WAIT;
            break;

        case WAIT:
            state = WAIT2;
            break;
        
        case WAIT2:
            fillScreen(0x000);
            printWizard(3);
            ICR1 = 7999; //20ms pwm period
            OCR1A =  3999;
            state=WAIT3;
            break;

        case WAIT3:
            state= INIT_PS;
            break;
        
        default:
            state = INIT_PS;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case INIT_PS:
            break;
        
        case WAIT:
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
            break;
        default:
            state = INIT_SB;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case INIT_SB:
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
            break;
        default:
            state = INIT_JI;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case INIT_JI:
            break;
        default:
            break;
    }
    return state;
}

int TickFct_PlayerCoords(int state) {
    switch (state) {
        //STATE TRANSITIONS
        case INIT_PC:
            break;
        default:
            state = INIT_PC;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case INIT_PC:
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
    switch (state) {
        //STATE TRANSITIONS
        case INIT_BM:
            ICR1 = 6825; //293Hz ~ D
            OCR1A =  ICR1/2;
            state = NOTE1;
            break;

        case NOTE1:
            ICR1 = 5101; //392Hz ~ G
            OCR1A =  ICR1/2;
            state = NOTE2;
            break;

        case NOTE2:
            ICR1 = 4056; //493Hz ~ B
            OCR1A =  ICR1/2;
            state = NOTE3;
            break;

        case NOTE3:
            ICR1 = 5730; //349Hz ~ F
            OCR1A =  ICR1/2;
            state = NOTE4;
            break;

        case NOTE4:
            ICR1 = 39999; //OFF
            OCR1A =  39999;
            state = INIT_BM;
            break;

        default:
            state = INIT_BM;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case INIT_BM:
            break;

        case NOTE1:
            break;

        case NOTE2:
            break;

        case NOTE3:
            break;
        
        case NOTE4:
            break;
            
        default:
            break;
    }
    return state;
}