//lee hardware y convierte la info

#ifndef INC_INPUTS_H_
#define INC_INPUTS_H_
#include <stdint.h>

typedef enum{		//colocamos eventos es enum
	NONE,
	INPUT_ROJO,
	INPUT_VERDE,
	INPUT_AZUL,
	INPUT_AMARILLO,
	INPUT_BLANCO,
	INPUT_PvP,
	INPUT_PvPC,
	INPUT_RESET
}EventoInput;

void Inputs_Init(void);
void Inputs_Update(void);

EventoInput GetEvento(void);
uint16_t GetValorPoten(void);		//solo potenciometro pq es valor continuo


#endif
