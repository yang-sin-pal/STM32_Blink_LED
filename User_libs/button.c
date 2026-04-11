#include "button.h"

void btn_init(BTN *btn, GPIO_TypeDef* port, uint16_t pins[])
{
	btn->GPIO_btn1 = port;
	btn->GPIO_btn2 = port;
	
	btn->btn1_Pin = pins[0];
	btn->btn2_Pin = pins[1];
	
	bool is_pressed = false;
}

bool btn_isPressed(BTN *btn)
{
	if (btn->is_pressed)
	{
		btn->is_pressed = false;
	}
	else
	{
		btn->is_pressed = true;
	}
	return btn->is_pressed;
}

void btn_setColor(BTN *btn, RGB *rgb, Color color1, Color color2)
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

void btn_toggle10hz(BTN *btn, RGB *rgb, Color color1, Color color2, uint32_t *lastTime)
{
	if (!HAL_GPIO_ReadPin(btn->GPIO_btn1, btn->btn1_Pin))
	{
		if ((HAL_GetTick() - *lastTime) >= 100 )
    {
			rgb_toggle(rgb, color1);
			*lastTime = HAL_GetTick();
    }
	}
	
	if (!HAL_GPIO_ReadPin(btn->GPIO_btn2, btn->btn2_Pin))
	{  
		if ((HAL_GetTick() - *lastTime) >= 100 )
    {
			rgb_toggle(rgb, color2);
			 *lastTime = HAL_GetTick();
     }
	}
}
