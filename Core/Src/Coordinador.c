//se encarga de la maquina de estados global del proyecto
#include "Coordinador.h"

static FSM_JUEGO estado;

void Coordinador_Init(void) {
	estado=INICIO;
}
void Coordinador_Update(void) {
	switch (estado){	//completar segun avancemos
	case INICIO:
		break;
	default:
		break;
	}
}
