#include "button.h"

void btn_init(BTN *btn, GPIO_TypeDef* port, uint16_t pins[])
{
	btn->GPIO_btn1 = port;
	btn->GPIO_btn2 = port;
	
	btn->btn1_Pin = pins[0];
	btn->btn2_Pin = pins[1];
}

void btn_setColors(BTN *btn, RGB *rgb, Color color1, Color color2)
{
	rgb_setColor (rgb, OFF);
	if (!HAL_GPIO_ReadPin(btn->GPIO_btn1, btn->btn1_Pin))
	{
		rgb_setColor (rgb, color1);
	}
	if (!HAL_GPIO_ReadPin(btn->GPIO_btn2, btn->btn2_Pin))
	{
		rgb_setColor (rgb, color2);
	}
		
}
