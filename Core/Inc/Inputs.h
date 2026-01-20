//lee hardware y convierte la info
#include "stm32f4xx_hal.h"
#include "main.h"

#ifndef INC_INPUTS_H_
#define INC_INPUTS_H_
#define ADC_POTEN_CHANNEL   ADC_CHANNEL_1
#define ADC_BOTON_CHANNEL   ADC_CHANNEL_2
#include <stdint.h>

extern volatile uint8_t flag_reset;

typedef enum{		//colocamos eventos es enum
	NONE,
	INPUT_ROJO,
	INPUT_VERDE,
	INPUT_AZUL,
	INPUT_AMARILLO,
	INPUT_BLANCO,
	INPUT_POTEN_PvP,
	INPUT_POTEN_PvPC,
}EventoInput;

void Inputs_Init(void);
void Inputs_Update_pot(void);
void Inputs_Update_boton(void);


EventoInput GetEvento(void);
uint16_t GetValorPoten(void);		//solo potenciometro pq es valor continuo


#endif
