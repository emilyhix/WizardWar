#include "timerISR.h"
#include "helper.h"
#include "periph.h"
#include "spiAVR.h"
#include "st7735.h"
#include "screenPrint.h"

#include "serialATmega.h"

uint8_t gameMode = 0; // 0 - title, 1 - walking, 2 - interaction, 3 - game over
uint8_t roomNumber = 0; // 0 - main, 1 - , 2 - , 3 - 
bool select = 0;

#define NUM_TASKS 5

int TickFct_PrintScreen(int);
int TickFct_SelectButton(int);
int TickFct_JoystickInput(int);
int TickFct_PlayerCoords(int);
int TickFct_UpdateMode(int);

enum States_PrintScreen {INIT_PS, WAIT};
enum States_SelectButton {INIT_SB};
enum States_JoystickInput {INIT_JI};
enum States_PlayerCoords {INIT_PC};
enum States_UpdateMode{INIT_UM};

const unsigned long PrintScreenPeriod = 200;
const unsigned long SelectButtonPeriod = 200;
const unsigned long JoystickInputPeriod = 500;
const unsigned long PlayerCoordsPeriod = 200;
const unsigned long UpdateModePeriod = 200;
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
    //Initialize PORTD
    DDRD = 0b00001000;
    PORTD = 0b11110111;
    //Initialize PORTB as output
    DDRB = 0xFF;
    PORTB = 0x00;

    // ADC_init();
    serial_init(9600);
    SPI_INIT();
    ST7735_init();

    //Initialize Buzzer
    // OCR0A = 128; //sets duty cycle to 50% since TOP is always 256
    // TCCR0A |= (1 << COM0A1);// use Channel A
    // TCCR0A |= (1 << WGM01) | (1 << WGM00);// set fast PWM Mode

    //TODO: Initialize the servo timer/pwm(timer1)
    // TCCR1A |= (1 << WGM11) | (1 << COM1A1); //COM1A1 sets it to channel A
    // TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11); //CS11 sets the prescaler to be 8
    // ICR1 = 39999; //20ms pwm period

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

    TimerSet(GCD_PERIOD);
    TimerOn();

    while (1) {}

    return 0;
}

int TickFct_PrintScreen(int state) {
    switch (state) {
        //STATE TRANSITIONS
        case INIT_PS:
            state = WAIT;
            break;

        case WAIT:
            state = WAIT;
            break;

        default:
            state = INIT_PS;
            break;
    }
    switch(state) {
        //STATE ACTIONS
        case INIT_PS:
            printTitle();
            break;
        
        case WAIT:
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
            //title screen
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

        default:
            break;
    }
    return state;
}