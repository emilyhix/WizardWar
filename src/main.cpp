#include "timerISR.h"
#include "helper.h"
#include "periph.h"
#include "spiAVR.h"

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

void SendCommand(char command) {
    // set command mode
    PORTB = SetBit(PORTB, 1, 0);
    // set SS pin to low
    PORTB = SetBit(PORTB, 2, 0);
    //send value
    SPI_SEND(command);
    // set SS pin back to high
    PORTB = SetBit(PORTB, 2, 1);
}

void SendData(char data) {
    // set command mode
    PORTB = SetBit(PORTB, 1, 1);
    // set SS pin to low
    PORTB = SetBit(PORTB, 2, 0);
    //send value
    SPI_SEND(data);
    // set SS pin back to high
    PORTB = SetBit(PORTB, 2, 1);
}

void setColumnAddress(uint16_t columnStart, uint16_t columnEnd) {
    //CASET - Set Column Address
    SendCommand(0x2A);
    // send high byte
    SendData(columnStart >> 8);
    //send low byte
    SendData(columnStart & 0xFF);
    //send high byte
    SendData(columnEnd >> 8);
    //send low byte
    SendData(columnEnd & 0xFF);
}

void setRowAddress(uint16_t rowStart, uint16_t rowEnd) {
    //RASET - Set Row Address
    SendCommand(0x2B);
    // send high byte
    SendData(rowStart >> 8);
    //send low byte
    SendData(rowStart & 0xFF);
    //send high byte
    SendData(rowEnd >> 8);
    //send low byte
    SendData(rowEnd & 0xFF);
}

void createPixel(uint16_t x, uint16_t y, uint16_t colorVal) {
    setRowAddress(y, y);
    setColumnAddress(x, x);
    //RAMWR - Memory Write
    SendCommand(0x2C);
    //send color low byte
    SendData(colorVal & 0xFF);
    //send color high byte
    SendData(colorVal >> 8);
}

void fillScreen(uint16_t color) {
    setColumnAddress(1, 130);
    setRowAddress(1, 130);
    SendCommand(0x2C); // RAMWR - Memory Write
    for (int i = 0; i < 130 * 130; i++) {
        SendData(color >> 8);    // High byte
        SendData(color & 0xFF);  // Low byte
    }
}

void HardwareReset() {
    // set reset pin to low
    PORTB = SetBit(PORTB, 0, 0);
    _delay_ms(200);
    // set reset pin to high
    PORTB = SetBit(PORTB, 0, 1);
    _delay_ms(200);
}

void ST7735_init() {
    HardwareReset();
    //SWRESET - Software Reset
    SendCommand(0x01);
    _delay_ms(150);
    //SLPOUT - Sleep out & booster on
    SendCommand(0x11);
    _delay_ms(200);
    //COLMOD - Interface pixel format
    SendCommand(0x3A);
    SendData(0x05); // 16 BIT COLOR MODE - change to 0x05
    _delay_ms(10);
    SendCommand(0x36);
    SendData(0x00);
    fillScreen(0x0000);
    //DISPON - Display on
    SendCommand(0x29);
    _delay_ms(200);
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

    while (1) {
    }

    return 0;
}