//FSM que coordina el orden y en una partida.
#ifndef INC_ORDEN_JUEGO_H_
#define INC_ORDEN_JUEGO_H_
#include "Inputs.h"
#include "Logica_Juego.h"

#define MAX_PULSACIONES 5

typedef enum {
	RONDA_INICIAL, INPUTS_ESPERA, FIN_RONDA
} FSM_RondasPartida;

typedef enum {		//este enum para gestionar al final que hacer con los inputs
    CREAR_SECUENCIA, ADIVINAR_SECUENCIA
} ModoOrdenJuego;

void Orden_Juego_Init(void);
void Orden_Juego_Update(EventoInput event);
int Orden_Juego_Terminado(void);

void OJ_SetModo(ModoOrdenJuego modo);
int OJ_Verificacion(void);
void SecuenciaRandom(void);
Resultado* OJ_GetResultados(void);

#endif /* INC_ORDEN_JUEGO_H_ */
