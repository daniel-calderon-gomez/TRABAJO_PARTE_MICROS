//lee hardware y convierte la info

#ifndef INC_INPUTS_H_
#define INC_INPUTS_H_
#define ADC_POTEN_CHANNEL   ADC_CHANNEL_1
#define ADC_BOTON_CHANNEL   ADC_CHANNEL_2
#include <stdint.h>

typedef enum{		//colocamos eventos es enum
	NONE,
	INPUT_ROJO,
	INPUT_VERDE,
	INPUT_AZUL,
	INPUT_AMARILLO,
	INPUT_BLANCO,
	INPUT_POTEN_PvP,
	INPUT_POTEN_PvPC,
	INPUT_RESET
}EventoInput;

void Inputs_Init(void);
void Inputs_Update_pot(void);
void Inputs_Update_boton(void);


EventoInput GetEvento(void);
uint16_t GetValorPoten(void);		//solo potenciometro pq es valor continuo


#endif
