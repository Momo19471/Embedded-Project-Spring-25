#include "lcd_test.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "delay.h" // Make sure this provides delayMs(int)

static void pulse_enable(void) {
    GPIO_PORTB_DATA_R |= LCD_EN;
    SysTick_msDelay(1);
    GPIO_PORTB_DATA_R &= ~LCD_EN;
    SysTick_msDelay(1);
}

static void send_nibble(uint8_t nibble) {
    // Preserve RS and EN, clear data bits, set new nibble
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~(LCD_DATA_PINS)) | (nibble & 0x0F);
    pulse_enable();
}

void LCD_Command(uint8_t cmd) {
    GPIO_PORTB_DATA_R &= ~LCD_RS; // RS = 0 for command
    send_nibble(cmd >> 4);        // High nibble
    send_nibble(cmd & 0x0F);      // Low nibble
    SysTick_msDelay(2);
}

void LCD_Data(uint8_t data) {
    GPIO_PORTB_DATA_R |= LCD_RS;  // RS = 1 for data
    send_nibble(data >> 4);       // High nibble
    send_nibble(data & 0x0F);     // Low nibble
    SysTick_msDelay(1);
}

void LCD_Init(void) {
    SYSCTL_RCGCGPIO_R |= (1U << 1); // Enable clock for Port B
    while ((SYSCTL_PRGPIO_R & (1U << 1)) == 0); // Wait for ready

    // Configure PB0–PB3, PB5, PB6 as output
    GPIO_PORTB_DIR_R |= LCD_DATA_PINS | LCD_RS | LCD_EN;
    GPIO_PORTB_DEN_R |= LCD_DATA_PINS | LCD_RS | LCD_EN;

    SysTick_msDelay(2);  // LCD power-on delay

    LCD_Command(0x28); // 4-bit, 2-line, 5x8 font
    LCD_Command(0x0C); // Display on, cursor off, blink off
    LCD_Command(0x06); // Entry mode, auto increment
    LCD_Command(0x01); // Clear display
    SysTick_msDelay(2);

}

void LCD_Print(char *str) {
    while (*str) {
        LCD_Data(*str++);
    }
}

void LCD_Clear(void) {
    LCD_Command(0x01);
    SysTick_msDelay(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? 0x00 : 0x40;
    address += col;
    LCD_Command(0x80 | address);
}
