#include "UART.h"
#include "tm4c123gh6pm.h"
#include <stdio.h> 
#include <stdint.h>

void UART0_Init(void) {
    SYSCTL_RCGCUART_R |= 0x0001;      // Enable UART0
    SYSCTL_RCGCGPIO_R |= 0x0001;      // Enable GPIOA
    UART0_CTL_R &= ~0x0001;           // Disable UART0

		UART0_IBRD_R = 104;
		UART0_FBRD_R = 11; // int(0.166 * 64 + 0.5)
    UART0_LCRH_R = 0x70;              // 8-bit, FIFO enabled
    UART0_CTL_R = 0x0301;             // Enable UART0, TXE and RXE

    GPIO_PORTA_AFSEL_R |= 0x03;       // Enable alt functions on PA0, PA1
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x00000011;
    GPIO_PORTA_DEN_R |= 0x03;         // Digital enable on PA0, PA1
    GPIO_PORTA_AMSEL_R &= ~0x03;      // Disable analog on PA0, PA1
}

void UART1_Init(void) {
    SYSCTL_RCGCUART_R |= 0x0002;      // Enable UART1
    SYSCTL_RCGCGPIO_R |= 0x0002;      // Enable GPIOB
    UART1_CTL_R &= ~0x0001;           // Disable UART1

    UART1_IBRD_R = 104;               // Integer part of baud rate divisor (16 MHz / (16 * 9600) = 104)
    UART1_FBRD_R = 11;                // Fractional part of baud rate (fractional part * 64 = 0.166 * 64 = 11)
    UART1_LCRH_R = 0x70;              // 8-bit, FIFO enabled
    UART1_CTL_R = 0x0301;             // Enable UART1, TXE and RXE

    GPIO_PORTB_AFSEL_R |= 0x03;       // Alt functions on PB0, PB1
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFFFF00) | 0x00000011;
    GPIO_PORTB_DEN_R |= 0x03;
    GPIO_PORTB_AMSEL_R &= ~0x03;
}

void UART_TX(uint8_t UART_sel, uint8_t data) {
    switch (UART_sel) {
        case PORT_A:
            while ((UART0_FR_R & 0x20) != 0);  // Wait until TX FIFO not full
            UART0_DR_R = data;
            break;

        case PORT_B:
            while ((UART1_FR_R & 0x20) != 0);
            UART1_DR_R = data;
            break;
				case 3 :
					 while ((UART3_FR_R & 0x20) != 0);
            UART3_DR_R = data;
				

        default:
            // Invalid port
            break;
    }
}

uint8_t UART_RX(uint8_t UART_sel) {
    switch (UART_sel) {
        case PORT_A:
            while ((UART0_FR_R & 0x10) != 0);  // Wait until RX FIFO not empty
            return (char) (UART0_DR_R&0xFF);

        case PORT_B:
            while ((UART1_FR_R & 0x10) != 0);
            return (char) (UART1_DR_R&0xFF);
				case 2:
            while ((UART2_FR_R & 0x10) != 0);
            return (char) (UART2_DR_R&0xFF);
				case 3:
						while ((UART3_FR_R & 0x10) != 0);
            return (char) (UART3_DR_R&0xFF);
						

        default:
            return 0;  // Invalid port
    }
}

void UART_SendString(uint8_t UART_sel, const char* str) {
		for(int i = 0; str[i] != '\0'; i++){
			 UART_TX(UART_sel, str[i]);
		}
			UART_TX(UART_sel, '\0');
}

void UART_Forward(uint8_t fromUART, uint8_t toUART) {
    char c = UART_RX(fromUART);
    UART_TX(toUART, c);
}

void UART_SendFloat(uint8_t UART_sel, float value) {
    char buffer[20];  // Buffer to hold the string representation of the float

    // Convert the float to string with 2 decimal places
    sprintf(buffer, "%.2f", value);  // Adjust the precision as needed (e.g., %.2f, %.4f)

    // Send the string byte by byte
    for(int i = 0; buffer[i] != '\0'; i++) {
        UART_TX(UART_sel, buffer[i]);  // Send each character
    }

    UART_TX(UART_sel, '\0');  // Send the null terminator (optional but good practice)
}








void UART2_Init(void) {
    // 1. Enable clocks for UART2 and Port D
    SYSCTL_RCGCUART_R |= (1 << 2);    // Enable UART2 clock
    SYSCTL_RCGCGPIO_R |= (1 << 3);    // Enable Port D clock
    while ((SYSCTL_PRGPIO_R & (1 << 3)) == 0) {}
    UART2_CTL_R &= ~0x0001;
    // 4. Set baud rate for 9600 (assuming 16 MHz clock)
    UART2_IBRD_R = 104;   // Integer part (16,000,000 / (16 * 9600) = 104.166...)
    UART2_FBRD_R = 11;    // Fractional part (0.166 * 64 + 0.5 ˜ 11)

    // 5. Configure UART Line Control: 8-bit, no parity, one stop bit, FIFO
    UART2_LCRH_R = 0x0070;

    // 6. Enable UART2, TX, and RX
    UART2_CTL_R = 0x0301;

    // 7. Configure PD6 (RX) and PD7 (TX) for UART
    GPIO_PORTD_AFSEL_R |= 0xC0;      // Enable alt func on PD6, PD7
    GPIO_PORTD_PCTL_R &= ~0xFF000000;
    GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0xFFFFFF00) + 0x11000000; // Configure PD6, PD7 for UART
    GPIO_PORTD_DEN_R |= 0xC0;        // Enable digital I/O on PD6, PD7
    GPIO_PORTD_AMSEL_R &= ~0xC0;     // Disable analog on PD6, PD7
}





void UART3_Init(void) {
    SYSCTL_RCGCUART_R |= 0x08;         // activate UART3 (bit 3)
    SYSCTL_RCGCGPIO_R |= 0x04;         // activate port C (bit 2)
    while ((SYSCTL_PRGPIO_R & 0x04) == 0) {}; // allow time for GPIOC to be ready

    UART3_CTL_R &= ~0x0001;            // disable UART3
    UART3_IBRD_R = 104;                 // IBRD = int(80,000,000/(16*115,200)) = 43
    UART3_FBRD_R = 11;                 // FBRD = round(0.40278 * 64) = 26
    UART3_LCRH_R = 0x70;               // 8-bit, no parity, 1-stop bit, FIFO enabled
    UART3_CTL_R |= 0x0301;             // enable UART3, TXE, RXE

    GPIO_PORTC_AFSEL_R |= 0xC0;        // enable alt function on PC6-7
    GPIO_PORTC_DEN_R |= 0xC0;          // digital enable on PC6-7
    GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & 0x00FFFFFF) | 0x11000000; // PC6=U3RX, PC7=U3TX
    GPIO_PORTC_AMSEL_R &= ~0xC0;       // disable analog on PC6-7
}