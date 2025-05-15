#include "systick.h"
#include <stdbool.h>



volatile uint32_t g_systick_count = 0;  // Global counter


void SysTick_Init(void) {
    NVIC_ST_CTRL_R = 0;                    // Disable SysTick during setup
    NVIC_ST_RELOAD_R = RELOAD_VALUE - 1;  // Reload value
    NVIC_ST_CURRENT_R = 0;                // Clear current value
    NVIC_ST_CTRL_R = 0x07;                // Enable SysTick with core clock and interrupts
}


void SysTick_DeInit(void) {
		NVIC_ST_CURRENT_R = 0;                // Clear current value
    NVIC_ST_CTRL_R = 0;                    // Disable SysTick during setup
}


void SysTick_msDelay(uint32_t delay_ms){
	  uint32_t i;
    // Reload value for 1 ms = 160,0000 at 16 MHz
    NVIC_ST_CTRL_R = 0;                      // Disable SysTick
    NVIC_ST_RELOAD_R = 16000 - 1;            // 1 ms interval
    NVIC_ST_CURRENT_R = 0;                   // Clear current
    NVIC_ST_CTRL_R = 0x05;                   // Enable SysTick (no interrupt, core clock)

    for(i = 0; i < delay_ms; i++){
        while((NVIC_ST_CTRL_R & 0x00010000) == 0); // Wait until COUNT flag is set
    }

    NVIC_ST_CTRL_R = 0;  // Stop SysTick after delay
}


// SysTick ISR (runs every 1 second)
void SysTick_Handler(void) {
		g_systick_count++;
    // Call GPS read function here
   ///////// Read_GPS();
}
void systic_unit (unsigned long tdelay){
NVIC_ST_CTRL_R=0; //disable timer
NVIC_ST_RELOAD_R=tdelay-1; //number of cycles for delay
NVIC_ST_CURRENT_R=0;
NVIC_ST_CTRL_R=0X05; // enable timer
while((NVIC_ST_CTRL_R&0X00010000)==0);
}