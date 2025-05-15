#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "GPIO.h"


// Initialize UART0 and UART1
void UART0_Init(void);
void UART1_Init(void);
void UART2_Init(void);
void UART3_Init(void);
// Send and receive a byte via UART
void UART_TX(uint8_t UART_sel, uint8_t data);
uint8_t UART_RX(uint8_t UART_sel);

void UART_SendString(uint8_t UART_sel, const char* str);
void UART_SendFloat(uint8_t UART_sel, float value);

void UART_Forward(uint8_t fromUART, uint8_t toUART);

#endif