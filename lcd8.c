/*
 * lcd8.c
 *	HD44780 character LCD library for 8 bit data mode
 *	The  Library Assumes All lines including data and control to be on the same GPIO PORT
 *	The RW Pin is Assumed to be tied to GND
 *  Created on: Jan 20, 2023
 *      Author: Amer Iqbal Qureshi
 *      Email: ameriqbalqureshi@yahoo.com
 */
#include "lcd8.h"
#include <stdio.h>
//Global variables for LCD
GPIO_TypeDef	*lcdPort;
uint16_t		lcdRsPin;
uint16_t		lcdEnPin;
uint16_t		lcdDataPin[8];

void lcdSetup(GPIO_TypeDef *PORT, uint16_t RS, uint16_t En, uint16_t D0,uint16_t D1,uint16_t D2,uint16_t D3,uint16_t D4,uint16_t D5,uint16_t D6,uint16_t D7 )
{
// Assign Pin values to global variables
	lcdPort=PORT;
	lcdRsPin=RS;
	lcdEnPin=En;
	lcdDataPin[0]=D0;
	lcdDataPin[1]=D1;
	lcdDataPin[2]=D2;
	lcdDataPin[3]=D3;
	lcdDataPin[4]=D4;
	lcdDataPin[5]=D5;
	lcdDataPin[6]=D6;
	lcdDataPin[7]=D7;

}

void lcdEnable()
{
	// Give a small 0 to 1 and 1 to 0 pulse on Enable pin to transfer port data
	HAL_GPIO_WritePin(lcdPort, lcdEnPin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(lcdPort, lcdEnPin, GPIO_PIN_RESET);

}

void lcdWrite(uint8_t data)
//	Writes one byte of data to the LCD Pins
{
	for(int i=0;i<8;i++)
	{
		if(data & (1<<i))
			HAL_GPIO_WritePin(lcdPort, lcdDataPin[i], GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(lcdPort, lcdDataPin[i], GPIO_PIN_RESET);
	}
	lcdEnable();
}

void lcdCommand(uint8_t command)
{
//	Sends Command data to LCD
	HAL_GPIO_WritePin(lcdPort, lcdRsPin, GPIO_PIN_RESET);	// Set RS to 0 for commands
	lcdWrite(command);
}

void lcdInit()
{
	lcdCommand(0x30); 	//  0 0 1 DL N F — — 0x30= 0011 0000 DL=1 means 8 Bit Mode
	HAL_Delay(10);
	lcdCommand(0x30);
	HAL_Delay(10);
	lcdCommand(0x30);
	HAL_Delay(10);
	lcdCommand(0x38);	// 0 0 0 0 1 DL N F — — 0x38= 0011 1000 N=1 means 2 or more lines
	HAL_Delay(10);
	lcdCommand(0x0E);	// 0 0 0 0 1 D C B		0x0E= 0000 1110 D=1 Display ON, C=1 Cursor ON
	HAL_Delay(10);

}

void lcdChar(uint8_t ch)
{
//	Display One Byte of Data to LCD
	HAL_GPIO_WritePin(lcdPort, lcdRsPin, GPIO_PIN_SET);	// Set RS Pin 1 for Data
	lcdWrite(ch);
}

void lcdString(char * string)
{
//	Display a String of characters
	while(*string)
		lcdChar(*string++);
}

void lcdWriteInt(char * format, uint32_t number )
{
//	Display integer numbers format is standard c printf() like %d etc
	char buffer[20];
	sprintf(buffer,format,number);
	lcdString(buffer);
}

void lcdWriteFloat(char * format, double number )
{
//	Display a floating point number
	char buffer[20];
	sprintf(buffer,format,number);
	lcdString(buffer);
}

void lcdSetCursor(uint8_t row, uint8_t col)
{
//	Sets the cursor position
	HAL_GPIO_WritePin(lcdPort, lcdRsPin, GPIO_PIN_RESET);	// RS=0;
	switch (row)
	{
	case 0:
		lcdWrite(0x80+col); break;
	case 1:
		lcdWrite(0xC0+col); break;
	case 2:
		lcdWrite(0x80+0x14+col); break;
	case 3:
		lcdWrite(0xC0+0x14+col); break;
	}
}
