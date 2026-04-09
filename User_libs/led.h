#ifndef LED_H
#define LED_H

#include "stm32l4xx_hal.h"
#include <stdbool.h>

typedef enum
{
	RED = 0,
	GREEN,
	BLUE,
	WHITE,
	YELLOW,
	PURPLE,
	OFF,
	
} Color ;

typedef struct 
{
	GPIO_TypeDef* GPIO_red;
	GPIO_TypeDef* GPIO_green;
	GPIO_TypeDef* GPIO_blue;
	
	uint8_t num_of_led;
	uint16_t red_pin;
	uint16_t green_pin;
	uint16_t blue_pin;
	
	bool  state;
	bool red_state;
	bool green_state;
	bool blue_state;
	uint32_t last_time_on;
	uint32_t tick1;
	uint32_t tick2;
	Color color;
} RGB;

void rgb_init(RGB *rgb, GPIO_TypeDef *gpio_port, uint16_t pins[]);
void rgb_setColor (RGB *rgb, Color color);
void rgb_toggle(RGB *rgb, Color color);
void rgb_blink(RGB *rgb, Color color, uint16_t blink_time);

void rgb_addColor(RGB *rgb, Color color);
void rgb_removeColor(RGB *rgb, Color color);
void rgb_multiToggle(RGB *rgb, Color color);
void rgb_nonBlockingBlink(RGB *rgb, uint16_t blink_time1, uint16_t blink_time2, Color color1, Color color2);
#endif