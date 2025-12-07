#include "Button.h"

//------------------variable------------------//
uint8_t pre_state = 0;
uint8_t pre_abs_state = 0;
uint32_t time;
uint32_t time_quick_pressing;
uint32_t time_press_and_wait;
uint8_t bouncing;
uint8_t abs_state;
uint8_t press_and_wait;
//---------------------------phase of button----------------------------//
__weak void pressing(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{

}

__weak void release(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{

}

__weak void quick_release(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{

}

__weak void long_pressing(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{

}


//---------------------------------------------------------------//
void button(Button_typedef *ButtonX)
{	
uint8_t state = HAL_GPIO_ReadPin(ButtonX->GPIOx, ButtonX->GPIO_Pin);            //---------init button-------//
//-------------------------------filter-------------------------//	
if (state != ButtonX->pre_state){
	ButtonX->pre_state = state;
	ButtonX->time = HAL_GetTick();
	ButtonX->bouncing = 1;
}
//-------------------------------absolute state-------------------------//	
if (ButtonX->bouncing && HAL_GetTick()-ButtonX->time >15){
	ButtonX->bouncing = 0;
	ButtonX->abs_state = ButtonX->pre_state;
}

//-------------------------------button function-------------------------//	


if (ButtonX->abs_state != ButtonX->pre_abs_state){                                  //press//
	
	if(ButtonX->abs_state == 0){
		ButtonX->time_quick_pressing = HAL_GetTick();	
		ButtonX->time_press_and_wait = HAL_GetTick();
		pressing(ButtonX->GPIOx, ButtonX->GPIO_Pin);
		ButtonX->press_and_wait = 1;
	}

else{                                                             //release//
	if (HAL_GetTick() - ButtonX->time_quick_pressing <= 500){
			quick_release(ButtonX->GPIOx, ButtonX->GPIO_Pin);                                      //quick_release//
	}
	else if(ButtonX->press_and_wait && ButtonX->time_press_and_wait - HAL_GetTick() >= 2000){
			long_pressing(ButtonX->GPIOx, ButtonX->GPIO_Pin);
			ButtonX->press_and_wait = 0;                                   //long release// 
	}	    
	else{
			release(ButtonX->GPIOx, ButtonX->GPIO_Pin);
	}
}

	ButtonX->pre_abs_state = ButtonX->abs_state ;
}	
}	

void button_init(Button_typedef *ButtonX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	ButtonX->GPIOx = GPIOx;
	ButtonX->GPIO_Pin = GPIO_Pin;
}	

