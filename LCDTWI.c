#include "LCDTWI.h"


void initLCD()
{
	cursor_pos = CURSOR_HOME_POS;
	_delay_ms(15); // wait for some time to first power
	enableTWI();
	sendCommand_4_bit(_4_BIT_MoDE);
	sendCommand_4_bit(INIT_OF_4_BIT_MODE);
	sendCommand_4_bit(DISP_ON_CURSOR_OFF);
	sendCommand_4_bit(CUR_AUTO_INC);
	sendCommand_4_bit(CLEAR_SCREEN);
	sendCommand_4_bit(CURSOR_HOME_POS);
}

void sendCommand_4_bit(unsigned char command)
{
	unsigned char all_bits = (command & 0xf0) | ((1 << EN_LCD) & ~(1 << RS));
	TWISend(SLA_W,all_bits);
	_delay_ms(_TIME_DELAY);
	all_bits &= ~(1 << EN_LCD);
	TWISend(SLA_W,all_bits);
	_delay_ms(_TIME_DELAY);
	//
	all_bits = ((command << 4) & 0xf0) | ((1 << EN_LCD) & ~(1 << RS));
	TWISend(SLA_W,all_bits);
	_delay_ms(_TIME_DELAY);
	all_bits &= ~(1 << EN_LCD);
	TWISend(SLA_W,all_bits);
	_delay_ms(_TIME_DELAY);
}

void sendCharacter(unsigned char character)
{
	unsigned char all_bits = (character & 0xf0) | ((1 << EN_LCD) | (1 << RS));
	TWISend(SLA_W,all_bits);
	_delay_ms(_TIME_DELAY);
	all_bits &= ~(1 << EN_LCD);
	TWISend(SLA_W,all_bits);
	_delay_ms(_TIME_DELAY);
	//
	all_bits = ((character << 4) & 0xf0) | ((1 << EN_LCD) | (1 << RS));
	TWISend(SLA_W,all_bits);
	_delay_ms(_TIME_DELAY);
	all_bits &= ~(1 << EN_LCD);
	TWISend(SLA_W,all_bits);
	_delay_ms(_TIME_DELAY);
	
	cursor_pos++;
	
	if(cursor_pos == (CURSOR_HOME_POS+16))
	{
		setCursor(SECOND_LINE);
	}
}

void setCursor(unsigned char pos)
{
	sendCommand_4_bit(pos);
}

void sendString(char *str)
{
	for(unsigned char i = 0 ; *(str+i) != '\0' ; i++)
	{
		sendCharacter(*(str+i));
	}
}

void clearScreen()
{
	sendCommand_4_bit(CLEAR_SCREEN);
	cursor_pos = CURSOR_HOME_POS;
}

void goSecondLine()
{
	setCursor(SECOND_LINE);
}