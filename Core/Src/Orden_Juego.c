#include "Orden_Juego.h"


#include <stdlib.h>

#define LUZFEEDBACK_ON 1000
#define LUZFEEDBACK_OFF 300


static FSM_RondasPartida estado_ronda;
static ModoOrdenJuego modo;

static EventoInput secuencia_obj[MAX_PULSACIONES];
static EventoInput secuencia_intento[MAX_PULSACIONES];
static Resultado resultados[MAX_PULSACIONES];

static uint8_t pulsaciones_color=0;
static uint8_t ronda_correcta=1; //si la secuencia es correcta 1
static uint8_t ronda_terminada = 0; //flag para que el coordinador sepa que terminó

static uint8_t index_feedback = 0;
static uint32_t tiempo_feedback = 0;
static uint32_t tiempo_led = 0;

static uint8_t numero_intento = 0;

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
		index_feedback=0;
		tiempo_feedback=0;
		estado_ronda = INPUTS_ESPERA;
		if(OJ_EsColor(event))
					OJ_ProcesarColor(event);
		break;


	case INPUTS_ESPERA:
		if(OJ_EsColor(event))
			OJ_ProcesarColor(event);
		/*if (tiempo_led > 0 && (HAL_GetTick() - tiempo_led) >= 300) { // 300ms
		        LEDRGB_SetColor1(LEDRGB_OFF);
		        tiempo_led = 0; // Resetear para no entrar siempre
		    }*/
		    break;


	case FIN_RONDA:

		if (modo==CREAR_SECUENCIA){
			for (int i=0;i<MAX_PULSACIONES;i++)
				secuencia_obj[i]=secuencia_intento[i];

			ronda_terminada=1;
			MAX7219_Clear();
			LEDRGB_SetColor1(LEDRGB_OFF);

			estado_ronda = RONDA_INICIAL;
		}

		else{
			numero_intento++;
			Logica_Juego_Comparar(secuencia_obj, secuencia_intento, resultados);

			index_feedback =0;
			tiempo_feedback = HAL_GetTick();
			LEDRGB_SetColor1(LEDRGB_OFF);

			estado_ronda = MOSTRAR_FEEDBACK;
		 }
		break;

	case MOSTRAR_FEEDBACK:
	{
		switch(resultados[index_feedback]){
			case RES_ESTA_CORRECTO:
				LEDRGB_SetFeedback(FEEDBACK_VERDE);
				break;
			case RES_ESTA_OTRA_POS:
				LEDRGB_SetFeedback(FEEDBACK_AMARILLO);
				break;
			case RES_NO_ESTA:
			default:
				LEDRGB_SetFeedback(FEEDBACK_ROJO);
				break;
		}

		if((HAL_GetTick()-tiempo_feedback) >= LUZFEEDBACK_ON){	//si pasa el tiempo que tiene q estar encendido
			LEDRGB_SetFeedback(FEEDBACK_OFF);
			tiempo_feedback= HAL_GetTick();
			estado_ronda = FEEDBACK_PAUSA;
		}
	}
	break;


	case FEEDBACK_PAUSA:
	{
		if ((HAL_GetTick()-tiempo_feedback) >= LUZFEEDBACK_OFF){
			index_feedback++;
			if(index_feedback>=MAX_PULSACIONES){
				ronda_terminada=1;
				estado_ronda=RONDA_INICIAL;
			}else {
				tiempo_feedback= HAL_GetTick();
				estado_ronda = MOSTRAR_FEEDBACK;
			}
		}
	}
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


static void OJ_EvColor(EventoInput e){
	switch (e) {
	   case INPUT_ROJO:     LEDRGB_SetColor1 (LEDRGB_ROJO); break;
	   case INPUT_VERDE:    LEDRGB_SetColor1 (LEDRGB_VERDE);break;
	   case INPUT_AZUL:     LEDRGB_SetColor1 (LEDRGB_AZUL);break;
	   case INPUT_AMARILLO: LEDRGB_SetColor1 (LEDRGB_AMARILLO);break;
	   case INPUT_BLANCO:   LEDRGB_SetColor1 (LEDRGB_BLANCO);break;
	   default:             LEDRGB_SetColor1 (LEDRGB_OFF);break;
	    }
}

void OJ_ProcesarColor(EventoInput event)
{
    secuencia_intento[pulsaciones_color] = event;
    OJ_EvColor(event);
    tiempo_led=HAL_GetTick();


    if (modo == ADIVINAR_SECUENCIA)
    {
        MAX7219_Update(numero_intento, pulsaciones_color);
        if (event != secuencia_obj[pulsaciones_color])
            ronda_correcta = 0;
    }

    pulsaciones_color++;

    if (pulsaciones_color >= MAX_PULSACIONES)
        estado_ronda = FIN_RONDA;
}


int OJ_EsColor(EventoInput event)
{
    return (event == INPUT_ROJO || event == INPUT_VERDE || event == INPUT_AZUL ||
            event == INPUT_AMARILLO || event == INPUT_BLANCO);
}

void Orden_Juego_ResetPartida(void)//para la matriz
{
    numero_intento = 0;
    MAX7219_Init();
    MAX7219_Clear();
    Orden_Juego_Init();
}
