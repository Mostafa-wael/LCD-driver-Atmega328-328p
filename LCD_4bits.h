#ifndef LCD_4bits
#define LCD_4bits

#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

#include "DIO_def.h"
#include <util/delay.h>
#include "LCD_commands.h"

#ifndef port
	#define port A
#endif
#if port == A
	#define LCD_DDR  DDRA_reg
	#define LCD_PORT PORTA_reg
	#define LCD_PIN  PINA_reg
#elif port == B
	#define LCD_DDR  DDRB_reg
	#define LCD_PORT PORTB_reg
	#define LCD_PIN  PINB_reg
#elif port == C
	#define LCD_DDR  DDRC_reg
	#define LCD_PORT PORTC_reg
	#define LCD_PIN  PINC_reg
#elif port == D
	#define LCD_DDR  DDRD_reg
	#define LCD_PORT PORTD_reg
	#define LCD_PIN  PIND_reg
#endif
// pins 0, 1, 2 of the port are reserved for the control signals 
#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

#ifndef lcdType
	#define lcdType 162 // means 16X2
#endif

void lcdSendCommand (u8 CMD)
{
	LCD_PORT &= ~ (1<<LCD_RS); // RS = 0; dealing with commands
	LCD_PORT &= ~ (1<<LCD_RW); // RW = 0; writing
	
	LCD_PORT = (LCD_PORT & 0x0f) | (CMD & 0xf0); // setting the first nibble to the first nibble of the CMD and all the second nibble is ones
	LCD_PORT |= (1<<LCD_EN); // EN=1; appling high to low pulse
	_delay_us(1); // actually it is 0.45 us
	LCD_PORT &= ~ (1<<LCD_EN); // EN=0;
	
	if (CMD == lcdClear || CMD == lcdHome)
	{
		_delay_ms(2); // after clear or home commands we should wait about 2 ms
	} 
	else
	{
		_delay_us(100); // from the data sheet we should wait 100 us after any command
	}
	
	LCD_PORT = (LCD_PORT & 0x0f) | (CMD <<4); // setting the second nibble to the second nibble of the CMD 
	LCD_PORT |= (1<<LCD_EN); // EN=1; appling high to low pulse
	_delay_us(1); // actually it is 0.45 us
	LCD_PORT &= ~ (1<<LCD_EN); // EN=0;
}
void lcdSendData (u8 data)
{
	LCD_PORT |= (1<<LCD_RS); // RS = 1; dealing with data
	LCD_PORT &= ~ (1<<LCD_RW); // RW = 0; writing
	
	LCD_PORT = (LCD_PORT & 0x0f) | (data & 0xf0); // setting the first nibble to the first nibble of the data and all the second nibble is ones
	LCD_PORT |= (1<<LCD_EN); // EN=1; appling high to low pulse
	_delay_us(1); // actually it is 0.45 us
	LCD_PORT &= ~ (1<<LCD_EN); // EN=0;
	
	_delay_us(100); // from the data sheet we should wait 100 us after any command
	
	LCD_PORT = (LCD_PORT & 0x0f) | (data <<4); // setting the second nibble to the second nibble of the data
	LCD_PORT |= (1<<LCD_EN); // EN=1; appling high to low pulse
	_delay_us(1); // actually it is 0.45 us
	LCD_PORT &= ~ (1<<LCD_EN); // EN=0;
}

void lcdInit()
{
	LCD_DDR = 0xff; // LCD port is output
	LCD_PORT &= ~ (1<<LCD_EN); // LCD enable is low
	_delay_ms(2); // waiting for the power to stabilize
	
	// initialization codes for various types of LCDs
	lcdSendCommand(0x33); // for the 4 bits mode
	_delay_us(100); // after each command we should wait about 100 us
	lcdSendCommand(0x32); // for the 4 bits mode
	_delay_us(100); // after each command we should wait about 100 us
	lcdSendCommand(0x28); // for the 4 bits mode
	_delay_us(100); // after each command we should wait about 100 us
	
	lcdSendCommand(dispayOn_cursorBlinking); // MACRO from LCD_commands.h
	_delay_us(100); // after each command we should wait about 100 us
	
	lcdSendCommand(lcdClear); // MACRO from LCD_commands.h
	_delay_ms(2); // after clear or home commands we should wait about 2 ms
	
	lcdSendCommand(cursorToRight); // MACRO from LCD_commands.h, to right for writing in English!
	_delay_us(100); // after each command we should wait about 100 us
	
}
void lcdReset ()
{
	// clear the display and return the cursor to home
	lcdSendCommand(lcdClear); // MACRO from LCD_commands.h
	_delay_ms(2); // after clear or home commands we should wait about 2 ms
	
	lcdSendCommand(lcdHome); // MACRO from LCD_commands.h
	_delay_ms(2); // after clear or home commands we should wait about 2 ms
	
}
void lcdWritingIn (char language)
{
	// choose the language to set the cursor direction
	// cursor direction is to right by default
	if (language=='a' || language=='A')
	{
		lcdReset();
		lcdSendCommand(cursorToLeft); // MACRO from LCD_commands.h, to left for writing in Arabic!
		_delay_us(100); // after each command we should wait about 100 us
		
	}
	else
	{
		lcdReset();
		lcdSendCommand(cursorToRight); // MACRO from LCD_commands.h, to right for writing in English!
		_delay_us(100); // after each command we should wait about 100 us
		
	}
}

void lcdGotoRowCol(u8 y, u8 x)
{
	// y for the row, x for the column
	#if lcdType == 162
		if (x<=0 || x>16)
			return;
	#elif lcdType == 201 || lcdType == 202 || lcdType == 204
		if (x<=0 || x>20)
			return;
	#elif lcdType == 402 // means 40X2
		if (x<=0 || x>40)
			return;
	#endif
	
	switch (y)
	{
		case 1 : lcdSendCommand(0x80 + x-1); break;
	#if lcdType == 162 || lcdType == 202 || lcdType == 204
		case 2 : lcdSendCommand(0xC0 + x-1); break;
	#endif
	#if lcdType == 402
		case 3 : lcdSendCommand(0x94 + x-1); break;
		case 4 : lcdSendCommand(0xD4 + x-1);break;
	#endif
		
		default: break;
	}
	
}


void lcdWriteChar(char chr)
{
	lcdSendData(chr);
}
void lcdWritenum (u32 num)
{
	/* the algorithm is as follows:
		for n = 2023;
		D0 = n % 10; --> 3
		n /= 10; --> 202 int division
		D1 = n % 10; --> 2
		n /= 10; --> 20 int division
		.
		.
		.
		D3 D2 D1 D0 --> 2 0 2 3
	*/
	u8 numDigits=0;
	u8 digits [10]; // for 'unsigned long' data types maximum number of digits for them is 10 digits --> 4'294'967'295
	
	if (!num)
	{
		lcdWriteChar('0');
		return;
	}
	while (num>0)
	{
		digits[numDigits++] = num % 10; 
		num/=10;
	}
	u8 i;
	for (i=numDigits-1; i>=0; i--)
	{
		lcdWriteChar(digits[i]);
	}
	 
}
void lcdPrint(char* str)
{
	u8 i=0;
	while (str[i] !='\0')
	{
		lcdSendData(str[i++]);
	}
}

#endif

