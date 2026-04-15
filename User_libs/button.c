#include "button.h"

void btn_init(BTN *btn, GPIO_TypeDef* port, uint16_t pins[])
{
	btn->GPIO_btn1 = port;
	btn->GPIO_btn2 = port;
	
	btn->btn1_Pin = pins[0];
	btn->btn2_Pin = pins[1];
	
	btn->state = STATE0;
	
	btn->preState_btn1 = false;
	btn->curState_btn1 = false;
	btn->is_debouncing_btn1 = false;
	btn->is_pressing_btn1 = false;
}

void btn_handle(BTN *btn, RGB *rgb)
{
	btn_handle_state(btn, rgb);
	btn1_handle_debounce(btn);
}
	
void btn_set_state(BTN *btn)
{
	switch (btn->state)
  {
  	case STATE0:
			btn->state = STATE1;
  		break;
  	case STATE1:
			btn->state = STATE2;
  		break;
		case STATE2:
			btn->state = STATE3;
  		break;
		case STATE3:
			btn->state = STATE0;
  		break;
  	default:
  		break;
  }
	btn->time_after_pressed_btn1 = HAL_GetTick();
}

void btn_handle_state(BTN *btn, RGB *rgb)
{
	switch (btn->state)
  {
  	case STATE0:
			rgb_setColor(rgb, OFF);
  		break;
  	case STATE1:
			btn_toggle1hz(btn,rgb,RED);
  		break;
		case STATE2:
			btn_toggle5hz(btn,rgb,GREEN);
  		break;
		case STATE3:
			btn_toggle10hz(btn,rgb,BLUE);
  		break;
  	default:
  		break;
  }
}
void btn1_handle_debounce(BTN *btn)
{
	btn->curState_btn1 = !HAL_GPIO_ReadPin(btn->GPIO_btn1, btn->btn1_Pin);
	
	if (btn->curState_btn1 != btn->preState_btn1)
  {
		btn->preState_btn1 = btn->curState_btn1;
		btn->is_debouncing_btn1 = true;
		btn->time_start_press = HAL_GetTick();
  }
	
	if (btn->is_debouncing_btn1 && ((HAL_GetTick() - btn->time_start_press) >= 15)) //after debouncing 15ms
  {
		btn->is_debouncing_btn1 = false; 
		
		if (btn->curState_btn1) // check if still pressing
    {
			btn_set_state(btn);
			btn->is_pressing_btn1 = true;
    }
		else
		{
			btn->is_pressing_btn1 = false;
		}
  }
	if (btn->is_pressing_btn1 && ((HAL_GetTick() - btn->time_start_press) >= 3000)) //check if still pressing button for 3s
  {
		btn->state = STATE0;
  }
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

void btn_toggle1hz(BTN *btn, RGB *rgb, Color color)
{
	if ((HAL_GetTick() - btn->time_after_pressed_btn1) >= 1000 )
    {
			rgb_toggle(rgb, color);
			btn->time_after_pressed_btn1 = HAL_GetTick();
    }
}

void btn_toggle5hz(BTN *btn,  RGB *rgb, Color color)
{
	if ((HAL_GetTick() - btn->time_after_pressed_btn1) >= 200 )
    {
			rgb_toggle(rgb, color);
			btn->time_after_pressed_btn1 = HAL_GetTick();
    }
}

void btn_toggle10hz(BTN *btn, RGB *rgb, Color color)
{
	if ((HAL_GetTick() - btn->time_after_pressed_btn1) >= 100 )
    {
			rgb_toggle(rgb, color);
			btn->time_after_pressed_btn1 = HAL_GetTick();
    }
}

void btn_hold_toggle1hz(GPIO_TypeDef* port, uint16_t pin, BTN *btn, RGB *rgb, Color color)
{
	if (!HAL_GPIO_ReadPin(port, pin))
	{
		btn_toggle1hz(btn, rgb,color);
	}
}

void btn_hold_toggle5hz(GPIO_TypeDef* port, uint16_t pin, BTN *btn,  RGB *rgb, Color color)
{
	if (!HAL_GPIO_ReadPin(port, pin))
	{
		btn_toggle5hz(btn, rgb,color);
	}
}

void btn_hold_toggle10hz(GPIO_TypeDef* port, uint16_t pin, BTN *btn, RGB *rgb, Color color)
{
	if (!HAL_GPIO_ReadPin(port, pin))
	{
		btn_toggle10hz(btn,rgb,color);
	}
}


