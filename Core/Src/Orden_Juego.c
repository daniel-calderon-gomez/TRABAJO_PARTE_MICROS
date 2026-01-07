#include "Orden_Juego.h"
#include <stdlib.h>

static FSM_RondasPartida estado_ronda;
static ModoOrdenJuego modo;

static EventoInput secuencia_obj[MAX_PULSACIONES];
static EventoInput secuencia_intento[MAX_PULSACIONES];
static Resultado resultados[MAX_PULSACIONES];

static uint8_t pulsaciones_color=0;
static uint8_t ronda_correcta=1; //si la secuencia es correcta 1
static uint8_t ronda_terminada = 0; //flag para que el coordinador sepa que terminó



void Orden_Juego_Init(void)
{
	estado_ronda = RONDA_INICIAL;
	pulsaciones_color=0;
	ronda_correcta=1; //solo dice de momento si gano la partida o no. mas adelante enum para encender el RGB en cada intento
	ronda_terminada = 0;
}


void Orden_Juego_Update(EventoInput event)
{
	switch (estado_ronda)
	{
	case RONDA_INICIAL:
		pulsaciones_color=0;
		ronda_correcta=1;
		ronda_terminada = 0;
		estado_ronda = INPUTS_ESPERA;
		break;

	case INPUTS_ESPERA:
	    if (event == INPUT_ROJO || event ==INPUT_VERDE || event ==INPUT_AZUL || event == INPUT_AMARILLO|| event ==INPUT_BLANCO){
	        secuencia_intento[pulsaciones_color]=event;

	        if(modo ==ADIVINAR_SECUENCIA)
	        {
	        	if (event!= secuencia_obj[pulsaciones_color])
	        		ronda_correcta=0;
	        }

	    	pulsaciones_color++;

	        if (pulsaciones_color>=MAX_PULSACIONES)
	        	estado_ronda=FIN_RONDA;
	    }
		break;

	case FIN_RONDA:
		if (modo==CREAR_SECUENCIA){
			for (int i=0;i<MAX_PULSACIONES;i++)
				secuencia_obj[i]=secuencia_intento[i];
		}
		else{
			Logica_Juego_Comparar(secuencia_obj, secuencia_intento, resultados);
			//funcion enciende led correccion
			//funcion matriz led
		 }
		ronda_terminada = 1;
		break;
	}
}

int Orden_Juego_Terminado(void){
	return ronda_terminada;
}


void OJ_SetModo(ModoOrdenJuego nuevoModo){
	modo=nuevoModo;
}


int OJ_VerificacionPartida(void){
	return ronda_correcta;
}


void SecuenciaRandom(void){
	for (int i = 0; i < MAX_PULSACIONES; i++)
	    {
	        int r = rand() % 5;
	        switch (r)
	        {
	        case 0:
	        	secuencia_obj[i] = INPUT_ROJO; 	        break;

	        case 1:
	        	secuencia_obj[i] = INPUT_VERDE; 	    break;

	        case 2:
	        	secuencia_obj[i] = INPUT_AZUL; 	        break;

	        case 3:
	        	secuencia_obj[i] = INPUT_AMARILLO; 	    break;

	        case 4:
	        	secuencia_obj[i] = INPUT_BLANCO; 	    break;
	        }
	    }
}
Resultado* OJ_GetResultados(void)
{
    return resultados;
}
