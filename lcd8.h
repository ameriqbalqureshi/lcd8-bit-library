/*
 * lcd8.h
 *
 *  Created on: Jan 20, 2023
 *      Author: iqbal
 */
#include "stm32f1xx.h"
#ifndef LCD8_H_
#define LCD8_H_
void lcdSetup(GPIO_TypeDef *PORT, uint16_t RS, uint16_t En, uint16_t D0,uint16_t D1,uint16_t D2,uint16_t D3,uint16_t D4,uint16_t D5,uint16_t D6,uint16_t D7 );
void lcdEnable();
void lcdWrite(uint8_t data);
void lcdCommand(uint8_t command);
void lcdInit();
void lcdChar(uint8_t ch);
void lcdString(char * string);
void lcdWriteInt(char * format, uint32_t number );
void lcdWriteFloat(char * format, double number );

void lcdSetCursor(uint8_t row, uint8_t col);

#define lcdClear		0x01
#define lcdCursorOFF	0x0C
#define lcdCursorON		0x0E
#define lcdCursorBlink	0x0F
#define lcdCursorHome	0x02
#define lcdShiftRight	0x1E
#define lcdShiftLeft	0x18
#define lcdOFF			0x08
#define lcdCursorLeft	0x10
#define lcdCursorRight	0x14










#endif /* LCD8_H_ */
