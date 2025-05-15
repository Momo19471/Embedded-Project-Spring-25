#ifndef systick_h
#define systick_h

#include <stdint.h>
#include "tm4c123gh6pm.h"
#define RELOAD_VALUE 16000000  // For 1 second if system clock is 16 MHz



extern volatile uint32_t g_systick_count;  // Extern declaration of the global counter


void SysTick_Init(void);

void SysTick_DeInit(void);

void SysTick_msDelay(uint32_t delay_ms);

void systic_unit (unsigned long tdelay);


#endif
