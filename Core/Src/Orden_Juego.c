#include "Orden_Juego.h"

static FSM_RondasPartida estado_ronda;


void Orden_Juego_Init(void) {
	estado_ronda = RONDA_INICIAL;
}


void Orden_Juego_Update(void)
{
	switch (estado_ronda)
	{
	case RONDA_INICIAL:
		estado_ronda = INPUTS_ESPERA;
		break;

	case INPUTS_ESPERA:
		break;

	case FIN_RONDA:
		break;
	}
}

int Orden_Juego_Terminado(void){

}

