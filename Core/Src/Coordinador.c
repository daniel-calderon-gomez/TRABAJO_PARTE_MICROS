//se encarga de la maquina de estados global del proyecto
#include "Coordinador.h"
#include "TiposJuego.h"
#include "Inputs.h"
#include "Orden_Juego.h"

static FSM_JUEGO estado_actual;
static ModoJuego modo_juego;


void Coordinador_Init(void)
{
	estado_actual=INICIO;
	modo_juego = MODO_PvPC;
}


void Coordinador_Update(void)
{
	EventoInput ev = GetEvento();

	switch (estado_actual)
	{
	case INICIO:
		 estado_actual = SELECCION_MODO;
		 break;


	case SELECCION_MODO:
		if(ev==INPUT_RESET){
			estado_actual=INICIO;
			break;
		}

		if(ev == INPUT_POTEN_PvP){
			modo_juego = MODO_PvP;
			estado_actual=SET_SECUENCIA;
		}
		else if (ev == INPUT_POTEN_PvPC){
			modo_juego = MODO_PvPC;
			estado_actual=SET_SECUENCIA;
		}

		break;


	case SET_SECUENCIA:
		Orden_Juego_Update();
		if(Orden_Juego_Terminado())
			estado_actual = ADIVINAR;
		break;


	case ADIVINAR:
		Orden_Juego_Update();
		if(Orden_Juego_Terminado())
			//estado_actual = VICTORIA; //o derrota
		break;


	case VICTORIA:
		if(ev==INPUT_RESET)
			estado_actual=INICIO;
		// estado final
		break;


	case DERROTA:
		if(ev==INPUT_RESET)
			estado_actual=INICIO;
		// estado final
		break;

	default:
		estado_actual= INICIO;
		break;
	}
}


FSM_JUEGO Coordinador_GetEstado(void)
{
    return estado_actual;
}
