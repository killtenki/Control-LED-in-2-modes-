#ifndef BUTTON_H
#define BUTTON_H
#include "main.h"

typedef struct
{
	uint8_t pre_state;
	uint8_t pre_abs_state;
	uint32_t time;
	uint32_t time_quick_pressing;
	uint32_t time_press_and_wait;
	uint8_t bouncing;
	uint8_t abs_state;
	uint8_t press_and_wait;
	GPIO_TypeDef *GPIOx; 
	uint16_t GPIO_Pin;
}Button_typedef;

void button_init(Button_typedef *ButtonX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void button(Button_typedef *ButtonX);
#endif

