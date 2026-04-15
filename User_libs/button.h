#ifndef BUTTON_H
#define BUTTON_H

#include "stm32l4xx_hal.h"
#include "led.h"
typedef enum
{
	STATE0 = 0,
	STATE1,
	STATE2,
	STATE3,
	STATE4,
	
} State ;

typedef struct 
{
	GPIO_TypeDef* GPIO_btn1;
	GPIO_TypeDef* GPIO_btn2;
	
	uint16_t btn1_Pin;
	uint16_t btn2_Pin;
	
	State state;
	
	uint32_t time_start_press;
	uint32_t is_pressed_btn1;
	bool preState_btn1;
	bool curState_btn1;
	bool is_debouncing_btn1;
	
} BTN;

void btn_init(BTN *btn, GPIO_TypeDef* port, uint16_t pins[]);
void btn_handle(BTN *btn, RGB *rgb);
void btn_set_state(BTN *btn);
void btn_handle_state(BTN *btn, RGB *rgb);
void btn1_handle_debounce(BTN *btn);
void btn_setColor(BTN *btn, RGB *rgb, Color color1, Color color2);
void btn_toggle1hz(BTN *btn, RGB *rgb, Color color);
void btn_toggle5hz(BTN *btn, RGB *rgb, Color color);
void btn_toggle10hz(BTN *btn, RGB *rgb, Color color);
void btn_hold_toggle1hz(GPIO_TypeDef* port, uint16_t pin, BTN *btn, RGB *rgb, Color color);
void btn_hold_toggle5hz(GPIO_TypeDef* port, uint16_t pin, BTN *btn, RGB *rgb, Color color);
void btn_hold_toggle10hz(GPIO_TypeDef* port, uint16_t pin, BTN *btn, RGB *rgb, Color color);

#endif