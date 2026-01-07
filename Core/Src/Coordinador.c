//se encarga de la maquina de estados global del proyecto
#include "Coordinador.h"
#include "TiposJuego.h"
#include "Inputs.h"
#include "Orden_Juego.h"

#define MAX_INTENTOS 8

static FSM_JUEGO estado_actual;
static ModoJuego modo_juego;

static uint8_t intentos;


void Coordinador_Init(void)
{
	estado_actual=INICIO;
	modo_juego = MODO_PvPC;
	intentos = 0;
}


void Coordinador_Update(void)
{
	EventoInput event = GetEvento();

	if (event == INPUT_RESET)
	    {
	        Orden_Juego_Init();
	        intentos = 0;
	        estado_actual = INICIO;
	        return;
	    }

	switch (estado_actual)
	{
	case INICIO:
		 estado_actual = SELECCION_MODO;
		 break;


	case SELECCION_MODO:
		if(event == INPUT_POTEN_PvP)
		{
			modo_juego = MODO_PvP;
			estado_actual=SET_SECUENCIA;
		}
		else if (event == INPUT_POTEN_PvPC)
		{
			modo_juego = MODO_PvPC;
			estado_actual=SET_SECUENCIA;
		}

		break;


	case SET_SECUENCIA:
		if (modo_juego == MODO_PvPC){
			SecuenciaRandom();
			Orden_Juego_Init();
			estado_actual = ADIVINAR;
		}else{
			OJ_SetModo(CREAR_SECUENCIA);
			Orden_Juego_Update(event);

			if(Orden_Juego_Terminado()){
				Orden_Juego_Init();
				estado_actual = ADIVINAR;
			}
		}
		break;


	case ADIVINAR:
		Orden_Juego_Update(event);
		if(Orden_Juego_Terminado())	//si se han hecho todos los intentos del turno
		{
			 if (OJ_VerificacionPartida())   // secuencia correcta
				 estado_actual = VICTORIA;
			 else
			 {
				 intentos++;
				 if (intentos >= MAX_INTENTOS)
					 estado_actual = DERROTA;
				 else
					 Orden_Juego_Init();
			 }
		}
		break;


	case VICTORIA:

		//funcion para zumbido
		//funcion matriz
		//estado_actual = INICIO
		break;


	case DERROTA:

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
