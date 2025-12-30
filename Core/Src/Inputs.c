/*
 * Inputs.c
 *
 *  Created on: Dec 22, 2025
 *      Author: ariel
 */
#include "Inputs.h"
#include "main.h"

EventoInput Evento;
static EventoInput eventoActual = NONE;
static uint16_t valorPoten=0;


void Inputs_Init(void) {
	eventoActual = NONE;
	valorPoten=0;
}


void Inputs_Update(void) {
	//Lectura potenciometro

	HAL_ADC_Start(&hadc1);

	//bloquea la ejecucion hasta que ADC finalice
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

	valorPoten = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);

}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN){
	if (GPIO_PIN == RESET_Pin)	eventoActual=INPUT_RESET;
}


EventoInput GetEvento(void){
	Evento=eventoActual;
	eventoActual=NONE;		//cuando acaba un evento hay que actualizar el enum
	return Evento;
}


uint16_t GetValorPoten(void)	{return valorPoten;}
