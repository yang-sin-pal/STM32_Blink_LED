#include "led.h"


void rgb_init(RGB *rgb, GPIO_TypeDef *gpio_port, uint16_t pins[])
{
	rgb->GPIO_red = gpio_port;
	rgb->GPIO_green = gpio_port;
	rgb->GPIO_blue = gpio_port;
	
	rgb->num_of_led = 3;
	rgb->red_pin = pins[0];
	rgb->green_pin = pins[1];
	rgb->blue_pin = pins[2];
	
	(*rgb).state = true;
	rgb->red_state = false;
	rgb->green_state = false;
	rgb->blue_state = false;
	(*rgb).last_time_on = 0;
	rgb->tick1 = HAL_GetTick();
	rgb->tick2 = HAL_GetTick();
	(*rgb).color = OFF;
}
void rgb_setcolor (RGB *rgb, Color color)
{
	rgb->color = color;
	HAL_GPIO_WritePin(rgb->GPIO_red, rgb->red_pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(rgb->GPIO_green, rgb->green_pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(rgb->GPIO_blue, rgb->blue_pin, GPIO_PIN_RESET);
	switch (color)
  {
  	case RED:
			HAL_GPIO_WritePin(rgb->GPIO_red, rgb->red_pin, GPIO_PIN_SET);
  		break;
		
  	case GREEN:
			HAL_GPIO_WritePin(rgb->GPIO_green, rgb->green_pin, GPIO_PIN_SET);
  		break;
		
		case BLUE:
			HAL_GPIO_WritePin(rgb->GPIO_blue, rgb->blue_pin, GPIO_PIN_SET);
  		break;
		
		case WHITE:
			HAL_GPIO_WritePin(rgb->GPIO_red, rgb->red_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(rgb->GPIO_green, rgb->green_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(rgb->GPIO_blue, rgb->blue_pin, GPIO_PIN_SET);
  		break;
		
		case YELLOW:
			HAL_GPIO_WritePin(rgb->GPIO_red, rgb->red_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(rgb->GPIO_green, rgb->green_pin, GPIO_PIN_SET);
  		break;
		
		case PURPLE:
			HAL_GPIO_WritePin(rgb->GPIO_red, rgb->red_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(rgb->GPIO_blue, rgb->blue_pin, GPIO_PIN_SET);
  		break;
		
		case OFF:
  	default:
  		break;
  }
}
void rgb_toggle(RGB *rgb, Color color)
{
	if (rgb->state)
	{
		rgb_setcolor(rgb, color);
		rgb->state = false;
	}
	else
	{
		rgb_setcolor(rgb, OFF);
		rgb->state = true;
	}
}
void rgb_blink(RGB *rgb, Color color, uint16_t blink_time)
 {
	rgb_toggle(rgb, color);
	HAL_Delay(blink_time);
}

void rgb_addColor(RGB *rgb, Color color)
{
    switch (color)
    {
        case RED:
            HAL_GPIO_WritePin(rgb->GPIO_red, rgb->red_pin, GPIO_PIN_SET);
            rgb->red_state = true;
            break;

        case GREEN:
            HAL_GPIO_WritePin(rgb->GPIO_green, rgb->green_pin, GPIO_PIN_SET);
            rgb->green_state = true;
            break;

        case BLUE:
            HAL_GPIO_WritePin(rgb->GPIO_blue, rgb->blue_pin, GPIO_PIN_SET);
            rgb->blue_state = true;
            break;

        default:
            break;
    }
}
void rgb_removeColor(RGB *rgb, Color color)
{
    switch (color)
    {
        case RED:
            HAL_GPIO_WritePin(rgb->GPIO_red, rgb->red_pin, GPIO_PIN_RESET);
            rgb->red_state = false;
            break;

        case GREEN:
            HAL_GPIO_WritePin(rgb->GPIO_green, rgb->green_pin, GPIO_PIN_RESET);
            rgb->green_state = false;
            break;

        case BLUE:
            HAL_GPIO_WritePin(rgb->GPIO_blue, rgb->blue_pin, GPIO_PIN_RESET);
            rgb->blue_state = false;
            break;

        default:
            break;
    }
}
void rgb_multiToggle(RGB *rgb, Color color)
{
	switch (color)
    {
        case RED:
            if (rgb->red_state)
                rgb_removeColor(rgb, RED);
            else
                rgb_addColor(rgb, RED);
            break;

        case GREEN:
            if (rgb->green_state)
                rgb_removeColor(rgb, GREEN);
            else
                rgb_addColor(rgb, GREEN);
            break;

        case BLUE:
            if (rgb->blue_state)
                rgb_removeColor(rgb, BLUE);
            else
                rgb_addColor(rgb, BLUE);
            break;

        default:
            break;
    }
}
void rgb_nonBlockingBlink(RGB *rgb, uint16_t blink_time1, uint16_t blink_time2, Color color1, Color color2)
{
	uint32_t now = HAL_GetTick();
	rgb_addColor(rgb, color1);
//	if ((now - rgb->tick1) >= blink_time1)
//  {
//		rgb->tick1 = now;
//		rgb_multiToggle(rgb, color1);
//		//HAL_GPIO_TogglePin(rgb->GPIO_red, rgb->red_pin);
//  }
	if ((now - rgb->tick2) >= blink_time2)
   {
			rgb->tick2 = now;
		  rgb_multiToggle(rgb, color2);
			//HAL_GPIO_TogglePin(rgb->GPIO_green, rgb->green_pin);
   }
}