#ifndef BUTTON_H
#define BUTTON_H

#include "stm32l4xx_hal.h"
#include "led.h"

typedef struct 
{
	GPIO_TypeDef* GPIO_btn1;
	GPIO_TypeDef* GPIO_btn2;
	
	uint16_t btn1_Pin;
	uint16_t btn2_Pin;
	
} BTN;

void btn_init(BTN *btn, GPIO_TypeDef* port, uint16_t pins[]);
void btn_setColors(BTN *btn, RGB *rgb, Color color1, Color color2);

#endif