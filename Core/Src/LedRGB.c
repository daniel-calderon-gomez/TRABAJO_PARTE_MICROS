#include "LedRGB.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim4;


#define PWM_MAX 999
#define Paso_Arcoiris 20

static uint16_t angulo_arcoiris = 0;
static uint32_t inicio_arcoiris = 0;

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


void ArcoirisFeedback_Init(){
	angulo_arcoiris = 0;
	inicio_arcoiris = HAL_GetTick();
}


void ArcoirisFeedback_Update(){
	if ((HAL_GetTick() - inicio_arcoiris) < Paso_Arcoiris)
	        return;

	    inicio_arcoiris = HAL_GetTick();

	    uint8_t r8, g8, b8;
	    Conversion_Color(angulo_arcoiris, 255, 255, &r8, &g8, &b8);

	    uint16_t r = (uint32_t)r8 * PWM_MAX / 255;
	    uint16_t g = (uint32_t)g8 * PWM_MAX / 255;
	    uint16_t b = (uint32_t)b8 * PWM_MAX / 255;

	    PWM_Set2(r, g, b);

	    angulo_arcoiris++;
	    if (angulo_arcoiris >= 360) angulo_arcoiris = 0;
}


void Conversion_Color(uint16_t ang, uint8_t sat, uint8_t brillo, uint8_t *r, uint8_t *g, uint8_t *b)
{
    uint8_t region = ang / 60;	//6 regiones de color del circulo cromatico
    uint16_t pos_sector = (ang - (region * 60)) * 255 / 60;

    uint8_t p = (uint16_t)brillo * (255 - sat) / 255;	//color base
    uint8_t q = (uint16_t)brillo * (255 - ((uint16_t)sat * pos_sector) / 255) / 255;	//componente creciente
    uint8_t t = (uint16_t)brillo * (255 - ((uint16_t)sat * (255 - pos_sector)) / 255) / 255;	//componente decreciente

    switch (region) {
        case 0: *r = brillo; *g = t; *b = p; break;
        case 1: *r = q; *g = brillo; *b = p; break;
        case 2: *r = p; *g = brillo; *b = t; break;
        case 3: *r = p; *g = q; *b = brillo; break;
        case 4: *r = t; *g = p; *b = brillo; break;
        default:*r = brillo; *g = p; *b = q; break;
    }
}


