#include "Orden_Juego.h"
#include "Inputs.h"

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
	    EventoInput ev = GetEvento();
	    if (ev != NONE)		//para comprobar el flujo del codigo. HABRA QUE CAMBIARLO OJO!!!!
	        estado_ronda = FIN_RONDA;
		break;

	case FIN_RONDA:
		break;
	}
}

int Orden_Juego_Terminado(void){
	return (estado_ronda == FIN_RONDA);
}

