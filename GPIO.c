#include "GPIO.h"


uint32_t port_picker(uint8_t port){
	uint32_t port_offset = 0;
	switch(port){
		case PORT_A:
			port_offset = 0;
			break;
		case PORT_B:
			port_offset = 0x1000;
			break;
		case PORT_C:
			port_offset = 0x2000;
			break;
		case PORT_D:
			port_offset = 0x3000;
			break;
		case PORT_E:
			port_offset = 0x20000;
			break;
		case PORT_F:
			port_offset = 0x21000;
			break;
	}
	return port_offset;
}



void GPIO_init_port(uint8_t port, uint8_t dir){
	
	uint32_t port_offset = port_picker(port);
	uint32_t gpio = GPIO_BASE + port_offset; // GOT MY PORT -> PORT_F 0x40025000
	SYSCTL_RCGCGPIO_R |= ( 1 << port);
	while((SYSCTL_PRGPIO_R&(1 << port) == 0));
	
	GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_LOCK_OFFSET) = 0x4C4F434B;
	GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_CR_OFFSET) = 0xFF; // 0b11111111
	GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_AMSEL_OFFSET) = 0;
	GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_PUR_OFFSET) = 0xFF;
	if(dir == OUTPUT){ // Output
		GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_DIR_OFFSET) = 0xFF;
	}
	else{
		GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_DIR_OFFSET) = 0;
	}
	GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_DEN_OFFSET) = 0xFF;
}



void GPIO_write(uint8_t port, uint8_t data){
	uint32_t port_offset = port_picker(port);
	uint32_t gpio = GPIO_BASE + port_offset;
	GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_DATA_OFFSET) = data;
}

uint8_t GPIO_read(uint8_t port){

  uint8_t bot;
	uint32_t port_offset = port_picker(port);
	uint32_t gpio = GPIO_BASE + port_offset;
	
bot= GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_DATA_OFFSET);

return bot; 
}



void GPIO_init_pin(uint8_t port, uint8_t pin, uint8_t dir){
    uint32_t port_offset = port_picker(port);
    uint32_t gpio = GPIO_BASE + port_offset;

    SYSCTL_RCGCGPIO_R |= (1 << port);
    while ((SYSCTL_PRGPIO_R & (1 << port)) == 0);

    GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_LOCK_OFFSET) = 0x4C4F434B;
    GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_CR_OFFSET) |= (1 << pin);
    GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_AMSEL_OFFSET) &= ~(1 << pin);
    GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_PUR_OFFSET) |= (1 << pin);

    if (dir == OUTPUT) {
        GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_DIR_OFFSET) |= (1 << pin);
    } else {
        GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_DIR_OFFSET) &= ~(1 << pin);
    }

    GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_DEN_OFFSET) |= (1 << pin);
}




void GPIO_write_pin(uint8_t port, uint8_t pin, uint8_t value){
    uint32_t port_offset = port_picker(port);
    uint32_t gpio = GPIO_BASE + port_offset;
    uint32_t mask_offset = (1 << pin) << 2;

    GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_DATA_OFFSET + mask_offset) = value ? (1 << pin) : 0;
}


uint8_t GPIO_read_pin(uint8_t port, uint8_t pin){
    uint32_t port_offset = port_picker(port);
    uint32_t gpio = GPIO_BASE + port_offset;
    uint32_t mask_offset = (1 << pin) << 2;

    return (GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_DATA_OFFSET + mask_offset) & (1 << pin)) ? 1 : 0;
}



void GPIO_init_port_range(uint8_t port, uint8_t from_pin, uint8_t to_pin, uint8_t dir){
    uint8_t mask = 0;
		uint8_t pin;
		uint32_t port_offset = port_picker(port);
    uint32_t gpio = GPIO_BASE + port_offset;

    SYSCTL_RCGCGPIO_R |= (1 << port);
    while ((SYSCTL_PRGPIO_R & (1 << port)) == 0);

    GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_LOCK_OFFSET) = 0x4C4F434B;

    for (pin = from_pin; pin <= to_pin; ++pin) {
        mask |= (1 << pin);
    }

    GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_CR_OFFSET)    |= mask;
    GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_AMSEL_OFFSET) &= ~mask;
    GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_PUR_OFFSET)   |= mask;
    
    if (dir == OUTPUT) {
        GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_DIR_OFFSET) |= mask;
    } else {
        GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_DIR_OFFSET) &= ~mask;
    }

    GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_DEN_OFFSET) |= mask;
}




void GPIO_write_range(uint8_t port, uint8_t from_pin, uint8_t to_pin, uint8_t data){
		uint8_t i;
		uint8_t mask = 0;
    uint32_t port_offset = port_picker(port);
    uint32_t gpio = GPIO_BASE + port_offset;
    uint8_t current = GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_DATA_OFFSET);

    // Create a bitmask from from_pin to to_pin
    
    for(i = from_pin; i <= to_pin; ++i){
        mask |= (1 << i);
    }

    // Clear the target bits and set them according to `data`
    current &= ~mask;                 // Clear bits in range
    current |= (data << from_pin) & mask; // Set bits from shifted data
    GPIO_REGISTER_WITH_OFFSET(gpio, GPIO_DATA_OFFSET) = current;
}



