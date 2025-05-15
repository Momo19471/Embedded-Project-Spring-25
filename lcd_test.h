#ifndef LCD_TEST_H
#define LCD_TEST_H

#include <stdint.h>
#include "systick.h"


#define LCD_RS  (1U << 5)  // PB5
#define LCD_EN  (1U << 6)  // PB6
#define LCD_DATA_PINS 0x0F // PB0–PB3

void LCD_Init(void);
void LCD_Command(uint8_t cmd);
void LCD_Data(uint8_t data);
void LCD_Print(char *str);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);

#endif
