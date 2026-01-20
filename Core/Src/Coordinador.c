//se encarga de la maquina de estados global del proyecto
#include "Coordinador.h"

#define MAX_INTENTOS 8

static volatile FSM_JUEGO estado_actual;
static ModoJuego modo_juego;

static uint8_t intentos;

static uint8_t entrar_victoria = 0;	//flags victoria/derrota
static uint8_t entrar_derrota = 0;

static uint8_t entrada_seleccion=1;



EventoInput event=NONE;


void Coordinador_Init(void)
{
	estado_actual=INICIO;
	modo_juego = MODO_PvPC;
	intentos = 0;
	entrada_seleccion=1;
}


void Coordinador_Update(void)
{

	if (event == INPUT_RESET)
	{
		MAX7219_Clear();
		Coordinador_Init();
		LEDRGB_Off();
		LEDRGB_FeedbackOff();
		Inputs_Init();
		Orden_Juego_Init();




		entrar_victoria = 0;
		entrar_derrota = 0;
		return;
	}

	switch (estado_actual)
	{
	case INICIO:
		Orden_Juego_Init();
		intentos = 0;
		entrar_victoria = 0;
		entrar_derrota = 0;
		estado_actual = SELECCION_MODO;
		break;


	case SELECCION_MODO:

		if(entrada_seleccion){
			ArcoirisFeedback_Init();
			entrada_seleccion=0;
		}
		ArcoirisFeedback_Update();
		Inputs_Update_pot();
		event=GetEvento();

		if(event == INPUT_POTEN_PvP)
		{
			modo_juego = MODO_PvP;
			estado_actual=SET_SECUENCIA;
			LEDRGB_FeedbackOff();
			entrada_seleccion=1;
		}
		else if (event == INPUT_POTEN_PvPC)
		{
			modo_juego = MODO_PvPC;
			estado_actual=SET_SECUENCIA;
			LEDRGB_FeedbackOff();
			entrada_seleccion=1;
		}

		break;


	case SET_SECUENCIA:

		if (modo_juego == MODO_PvPC){
			SecuenciaRandom();
			//Orden_Juego_ResetPartida();//Para la matriz
			Orden_Juego_Init();
			OJ_SetModo(ADIVINAR_SECUENCIA);
			estado_actual = ADIVINAR;
		}else{
			OJ_SetModo(CREAR_SECUENCIA);
			Inputs_Update_boton();
			event = GetEvento();
			//Orden_Juego_ResetPartida();//Para la matriz
			Orden_Juego_Update(event);

			if(Orden_Juego_Terminado()){
				Orden_Juego_Init();
				OJ_SetModo(ADIVINAR_SECUENCIA);
				estado_actual = ADIVINAR;
			}
		}
		break;


	case ADIVINAR:
		Inputs_Update_boton();
		event = GetEvento();

		Orden_Juego_Update(event);
		if(Orden_Juego_Terminado())	//si se han hecho todos los intentos del turno
		{
			 if (OJ_VerificacionPartida())   // secuencia correcta
			 {
				 entrar_victoria = 1;
				 estado_actual = VICTORIA;
			 }
			 else
			 {
				 intentos++;
				 if (intentos >= MAX_INTENTOS)
				 {
					 entrar_derrota = 1;
					 estado_actual = DERROTA;
				 }
				 else
					 Orden_Juego_Init();
			 }
		}
		break;


	case VICTORIA:
		if (entrar_victoria)
		    {
		        Zumbador_SetModo(BUZZER_VICTORIA);
		        entrar_victoria = 0;
		        MAX7219_Victoria();
		    }
		Zumbador_Sonar();
		 if (Zumbador_FIN()==1)
			 estado_actual = INICIO;

		break;


	case DERROTA:
		if (entrar_derrota)
		    {
		        Zumbador_SetModo(BUZZER_DERROTA);
		        entrar_derrota = 0;
		        MAX7219_Derrota();
		    }
		Zumbador_Sonar();
		 if (Zumbador_FIN()==1)
			estado_actual = INICIO;
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
