#include "LedRGB.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim4;


#define PWM_MAX 999

static void PWM_Set1(uint16_t r, uint16_t g, uint16_t b)
{
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, r);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, g);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, b);
}


static void PWM_Set2(uint16_t r, uint16_t g, uint16_t b)
{
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, r);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, g);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, b);
}

void LEDRGB_Init(void) {
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);

    PWM_Set1(0,0,0); //inicializamos a 0
    PWM_Set2(0,0,0);
}


void LEDRGB_Off(void){
	PWM_Set1(0,0,0);
}

void LEDRGB_FeedbackOff(void){
	PWM_Set2(0,0,0);
}



void LEDRGB_SetColor1(LED_Color color){
	switch (color)
	    {
	        case LEDRGB_OFF: PWM_Set1(0, 0, 0); break;

	        case LEDRGB_ROJO: PWM_Set1(PWM_MAX, 0, 0); break;

	        case LEDRGB_VERDE: PWM_Set1(0, PWM_MAX, 0); break;

	        case LEDRGB_AZUL: PWM_Set1(0, 0, PWM_MAX); break;

	        case LEDRGB_AMARILLO: PWM_Set1(PWM_MAX, 650, 0); break;

	        case LEDRGB_BLANCO: PWM_Set1(PWM_MAX, 800, 750); break;

	        default: PWM_Set1(0, 0, 0); break;
	   }
}



void LEDRGB_SetFeedback(LED_Feedback feedback){
	switch (feedback)
	    {
			case FEEDBACK_OFF: PWM_Set2(0,0,0);  break;

	        case FEEDBACK_VERDE: PWM_Set2(0, PWM_MAX, 0); break;

	        case FEEDBACK_AMARILLO: PWM_Set2(PWM_MAX, 650, 0); break;

	        case FEEDBACK_ROJO:

	        default: PWM_Set2(PWM_MAX, 0, 0); break;

	    }
}

