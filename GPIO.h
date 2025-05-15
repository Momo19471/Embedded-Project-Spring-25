#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>
#include "tm4c123gh6pm.h"

#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3
#define PORT_E 4
#define PORT_F 5

#define INPUT 0
#define OUTPUT 1

#define GPIO_BASE 0x40004000
#define GPIO_DATA_OFFSET        0x3FC
#define GPIO_DIR_OFFSET         0x400
#define GPIO_IS_OFFSET          0x404
#define GPIO_IBE_OFFSET         0x408
#define GPIO_IEV_OFFSET         0x40C
#define GPIO_IM_OFFSET          0x410
#define GPIO_RIS_OFFSET         0x414
#define GPIO_MIS_OFFSET         0x418
#define GPIO_ICR_OFFSET         0x41C
#define GPIO_AFSEL_OFFSET       0x420
#define GPIO_DR2R_OFFSET        0x500
#define GPIO_DR4R_OFFSET        0x504
#define GPIO_DR8R_OFFSET        0x508
#define GPIO_ODR_OFFSET         0x50C
#define GPIO_PUR_OFFSET         0x510
#define GPIO_PDR_OFFSET         0x514
#define GPIO_SLR_OFFSET         0x518
#define GPIO_DEN_OFFSET         0x51C
#define GPIO_LOCK_OFFSET        0x520
#define GPIO_CR_OFFSET          0x524
#define GPIO_AMSEL_OFFSET       0x528
#define GPIO_PCTL_OFFSET        0x52C
#define GPIO_ADCCTL_OFFSET      0x530
#define GPIO_DMACTL_OFFSET      0x534

#define GPIO_REGISTER_WITH_OFFSET(GPIO, offset) (*((volatile uint32_t *)((GPIO) + (offset)))) 

void GPIO_init_port(uint8_t port, uint8_t dir);

void GPIO_write(uint8_t port, uint8_t data);

uint8_t GPIO_read(uint8_t port);

void GPIO_init_pin(uint8_t port, uint8_t pin, uint8_t dir);
void GPIO_write_pin(uint8_t port, uint8_t pin, uint8_t value);
uint8_t GPIO_read_pin(uint8_t port, uint8_t pin);

void GPIO_init_port_range(uint8_t port, uint8_t from_pin, uint8_t to_pin, uint8_t dir);

void GPIO_write_range(uint8_t port, uint8_t from_pin, uint8_t to_pin, uint8_t data);

#endif
