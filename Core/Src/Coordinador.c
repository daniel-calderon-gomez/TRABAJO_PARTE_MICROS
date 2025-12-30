//se encarga de la maquina de estados global del proyecto
#include "Coordinador.h"
#include "TiposJuego.h"

static FSM_JUEGO estado_actual;
static ModoJuego modo_juego;

void Coordinador_Init(void)
{
	estado_actual=INICIO;
	 modo_juego = MODO_PvPC;
}
void Coordinador_Update(void)
{
	switch (estado_actual){
	case INICIO:
		 estado_actual = SELECCION_MODO;
		 break;
	case SELECCION_MODO:
		//  leeremos potenciómetro + pulsador
		break;

	case SET_SECUENCIA:
		//  PC random o jugador define secuencia
		break;

	case ADIVINAR:
		// aquí irá la lógica del juego
		break;

	case VICTORIA:
		// estado final
		break;

	case DERROTA:
		// estado final
		break;

	default:

		break;
	}
}

FSM_JUEGO Coordinador_GetEstado(void)
{
    return estado_actual;
}
