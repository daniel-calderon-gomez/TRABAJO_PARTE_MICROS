//se encarga de la maquina de estados global del proyecto
#include "Coordinador.h"
#include "TiposJuego.h"
#include "Inputs.h"
#include "Orden_Juego.h"

static FSM_JUEGO estado_actual;
static ModoJuego modo_juego;
static uint8_t intentos;
#define MAX_INTENTOS 5


void Coordinador_Init(void)
{
	estado_actual=INICIO;
	modo_juego = MODO_PvPC;
	intentos = 0;
}


void Coordinador_Update(void)
{
	EventoInput event = GetEvento();

	switch (estado_actual)
	{
	case INICIO:
		 estado_actual = SELECCION_MODO;
		 break;


	case SELECCION_MODO:
		if(event==INPUT_RESET){
			estado_actual=INICIO;
			break;
		}

		if(event == INPUT_POTEN_PvP)
		{
			modo_juego = MODO_PvP;
			OJ_SetModo(CREAR_SECUENCIA);
			Orden_Juego_Init();
			estado_actual=SET_SECUENCIA;
		}
		else if (event == INPUT_POTEN_PvPC)
		{
			modo_juego = MODO_PvPC;
			OJ_SetModo(ADIVINAR_SECUENCIA);
			SecuenciaRandom();
			Orden_Juego_Init();
			estado_actual=ADIVINAR;
		}

		break;


	case SET_SECUENCIA:
		Orden_Juego_Update();
		if(Orden_Juego_Terminado()){
			Orden_Juego_Init();
			estado_actual = ADIVINAR;
		}
		break;


	case ADIVINAR:
		Orden_Juego_Update();
		if(Orden_Juego_Terminado())	//si se han hecho todos los intentos del turno
		{
			 if (OJ_Verificacion())   // secuencia correcta
			 {
				 estado_actual = VICTORIA;
			 }
			 else
			 {
				 intentos++;
				 if (intentos >= MAX_INTENTOS)
				 {
					 estado_actual = DERROTA;
				 }
				 else
				 {
					 Orden_Juego_Init();
				 }
			 }
		}
		break;


	case VICTORIA:
		if(event==INPUT_RESET)
		{
			intentos=0;
			estado_actual=INICIO;
		// estado final
		}
		break;


	case DERROTA:
		if(event==INPUT_RESET)
		{
			 intentos = 0;
			estado_actual=INICIO;
		// estado final
		}
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
