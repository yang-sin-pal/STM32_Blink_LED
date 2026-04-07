#ifndef LED_H
#define LED_H

#include "stm32l4xx_hal.h"
#include <stdbool.h>

typedef enum
{
	RED,
	GREEN,
	BLUE,
	WHITE,
	YELLOW,
	PURPLE,
	OFF,
	
} Color ;

typedef struct 
{
	GPIO_TypeDef *GPIO_red;
	GPIO_TypeDef *GPIO_green;
	GPIO_TypeDef *GPIO_blue;
	
	uint8_t num_of_led;
	uint16_t red_pin;
	uint16_t green_pin;
	uint16_t blue_pin;
	
	bool  state;
	uint32_t last_time_on;
	Color color;
} RGB;

void rgb_init(RGB *rgb, GPIO_TypeDef *gpio_port, uint16_t pins[]);
void rgb_setcolor (RGB *rgb, Color color);
void rgb_toggle(RGB *rgb, Color color);
void rgb_blink(RGB *rgb, Color color, uint16_t blink_time);



#endif