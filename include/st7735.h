#ifndef ST7735_H
#define ST7735_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "helper.h"
#include "spiAVR.h"

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

void setColumnAddress(uint8_t columnStart, uint8_t columnEnd) {
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

void setRowAddress(uint8_t rowStart, uint8_t rowEnd) {
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

void createPixel(uint8_t x, uint8_t y, uint16_t colorVal) {
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
        SendData(color >> 8);
        SendData(color & 0xFF);
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
    SendData(0x05); // 16 BIT COLOR MODE
    _delay_ms(10);
    fillScreen(0x0000);
    //DISPON - Display on
    SendCommand(0x29);
    _delay_ms(200);
}

#endif