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
	(*rgb).last_time_on = 0;
	(*rgb).color = OFF;
}
void rgb_setcolor (RGB *rgb, Color color)
{
	rgb->color = color;
	switch (rgb->color)
  {
  	case RED:
			HAL_GPIO_WritePin(rgb->GPIO_red, rgb->red_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(rgb->GPIO_green, rgb->green_pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(rgb->GPIO_blue, rgb->blue_pin, GPIO_PIN_RESET);
  		break;
  	case GREEN:
			HAL_GPIO_WritePin(rgb->GPIO_red, rgb->red_pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(rgb->GPIO_green, rgb->green_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(rgb->GPIO_blue, rgb->blue_pin, GPIO_PIN_RESET);
  		break;
		case BLUE:
			HAL_GPIO_WritePin(rgb->GPIO_red, rgb->red_pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(rgb->GPIO_green, rgb->green_pin, GPIO_PIN_RESET);
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
			HAL_GPIO_WritePin(rgb->GPIO_blue, rgb->blue_pin, GPIO_PIN_RESET);
  		break;
		case PURPLE:
			HAL_GPIO_WritePin(rgb->GPIO_red, rgb->red_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(rgb->GPIO_green, rgb->green_pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(rgb->GPIO_blue, rgb->blue_pin, GPIO_PIN_SET);
  		break;
  	default:
			HAL_GPIO_WritePin(rgb->GPIO_red, rgb->red_pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(rgb->GPIO_green, rgb->green_pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(rgb->GPIO_blue, rgb->blue_pin, GPIO_PIN_RESET);
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
	HAL_Delay(1000);
}
void rgb_blink(RGB *rgb, Color color, uint16_t blink_time)
{
	
}