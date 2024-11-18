#include "timerISR.h"
#include "helper.h"
#include "periph.h"
#include "spiAVR.h"
#include "st7735.h"

#include "serialATmega.h"

#define NUM_TASKS 3

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

    createPixel(45,8, 0xa6c7);
    createPixel(45,9, 0xa6c7);
    createPixel(45,10, 0xa6c7);
    createPixel(45,11, 0xa6c7);
    createPixel(45,12, 0xa6c7);
    createPixel(45,13, 0xa6c7);
    createPixel(45,14, 0xa6c7);
    createPixel(45,15, 0xa6c7);
    createPixel(45,16, 0xa6c7);

    //Initialize Buzzer
    // OCR0A = 128; //sets duty cycle to 50% since TOP is always 256
    // TCCR0A |= (1 << COM0A1);// use Channel A
    // TCCR0A |= (1 << WGM01) | (1 << WGM00);// set fast PWM Mode

    //TODO: Initialize the servo timer/pwm(timer1)
    // TCCR1A |= (1 << WGM11) | (1 << COM1A1); //COM1A1 sets it to channel A
    // TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11); //CS11 sets the prescaler to be 8
    // ICR1 = 39999; //20ms pwm period

    // unsigned char i = 0;
    // tasks[i].state = AC_INIT;
    // tasks[i].period = AmberCountPeriod;
    // tasks[i].elapsedTime = tasks[i].period;
    // tasks[i].TickFct = &TickFct_AmberCount;
    // ++i;

    // TimerSet(GCD_PERIOD);
    // TimerOn();

    while (1) {}

    return 0;
}