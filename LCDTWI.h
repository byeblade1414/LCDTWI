#ifndef _LCD_TWI_H
#define _LCD_TWI_H

#ifndef _TWI_H
#include "TWI.h"
#endif

#ifndef _AVR_ATMEGA32A_H_INCLUDED
#include <avr/io.h>
#endif

#ifndef _UTIL_DELAY_H_
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>
#endif

#define _4_BIT_MoDE 0x02  // 4 bit mode selector
#define INIT_OF_4_BIT_MODE 0x28  // 2 line,5x8 dot for each character
#define DISP_ON_CURSOR_OFF 0x0c
#define CUR_AUTO_INC 0x06
#define CLEAR_SCREEN 0x01
#define CURSOR_HOME_POS 0x80
#define FIRST_LINE CURSOR_HOME_POS
#define SECOND_LINE (CURSOR_HOME_POS+64)

//pin definitions ( data pins 4 - 7 pins are connected to data lines of lcd, first pin is considered as #0 )
#define EN_LCD 3
#define RS 2		// for command register 0, data register 1

#define _TIME_DELAY 2

void sendCommand_4_bit(unsigned char command);
void sendCharacter(unsigned char character);
void initLCD();
void setCursor(unsigned char pos);
void sendString(char *str);
void clearScreen();
void goSecondLine();


#endif