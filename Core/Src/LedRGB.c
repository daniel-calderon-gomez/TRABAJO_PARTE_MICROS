#include "LedRGB.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>

extern TIM_HandleTypeDef htim1;

#define PWM_MAX 999

static void PWM_Set(uint16_t r, uint16_t g, uint16_t b)
{
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, r);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, g);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, b);
}


void LEDRGB_Init(void) {
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    PWM_Set(0,0,0); //inicializamos a 0
}


void LEDRGB_Off(void){
	PWM_Set(0,0,0);
}


void LedRGB_Update(void) {}


void LEDRGB_SetColor(LED_Color color){
	switch (color)
	    {
	        case LEDRGB_OFF:
	            PWM_Set(0, 0, 0);
	            break;

	        case LEDRGB_ROJO:
	            PWM_Set(PWM_MAX, 0, 0);
	            break;

	        case LEDRGB_VERDE:
	            PWM_Set(0, PWM_MAX, 0);
	            break;

	        case LEDRGB_AZUL:
	            PWM_Set(0, 0, PWM_MAX);
	            break;
	        case LEDRGB_AMARILLO:
	            PWM_Set(PWM_MAX, PWM_MAX, 0);
	            break;

	        case LEDRGB_BLANCO:
	            PWM_Set(PWM_MAX, PWM_MAX, PWM_MAX);
	            break;

	        default:
	            PWM_Set(0, 0, 0);
	            break;
	   }
}



void LEDRGB_SetFeedback(LED_Feedback feedback){
	switch (feedback)
	    {
	        case FEEDBACK_VERDE:
	            LEDRGB_SetColor(LEDRGB_VERDE);
	            break;

	        case FEEDBACK_AMARILLO:
	            LEDRGB_SetColor(LEDRGB_AMARILLO);
	            break;

	        case FEEDBACK_ROJO:

	        default:
	            LEDRGB_SetColor(LEDRGB_ROJO);
	            break;
	    }
}

