#define SIN_BOTON 200
#define BOTON_ROJO_MIN 300
#define BOTON_ROJO_MAX 700
#define BOTON_VERDE_MIN 800
#define BOTON_VERDE_MAX 1200
#define BOTON_AZUL_MIN 1300
#define BOTON_AZUL_MAX 1700
#define BOTON_AMARILLO_MIN 1800
#define BOTON_AMARILLO_MAX 2200
#define BOTON_BLANCO_MIN 2300
#define BOTON_BLANCO_MAX 2700

#include "Inputs.h"
#include "main.h"



static EventoInput eventoActual = NONE;

static EventoInput ultimoBoton = NONE;
static EventoInput ultimoPoten = NONE;


static uint16_t valorPoten=0;
static uint16_t valorBoton=0;



void Inputs_Init(void) {
	eventoActual = NONE;
	valorPoten=0;
}

static uint16_t LecturaADC(uint32_t canal)	//cambio de canal en la lectura del ADC
{
	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = canal;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    HAL_ADC_Start(&hadc1);

    //bloquea la ejecucion hasta que ADC finalice
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

    uint16_t valor = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

    return valor;
}

void Inputs_Update_pot(void) {

	//lectura potenciometro
	valorPoten = LecturaADC(ADC_POTEN_CHANNEL);
	EventoInput potenDetectado = NONE;

	if (valorPoten>100){
		if (valorPoten<2048)
			potenDetectado = INPUT_POTEN_PvP;
		else
			potenDetectado = INPUT_POTEN_PvPC;
	}else 	potenDetectado = NONE;

	if(potenDetectado != NONE && ultimoPoten ==NONE)
		eventoActual=potenDetectado;

	ultimoPoten= potenDetectado;

}


void Inputs_Update_boton(void) {
	//lectura botones
	valorBoton = LecturaADC(ADC_BOTON_CHANNEL);

	EventoInput botonPulsando=NONE;

	if (valorBoton > BOTON_ROJO_MIN && valorBoton < BOTON_ROJO_MAX)
		botonPulsando = INPUT_ROJO;
	else if (valorBoton > BOTON_VERDE_MIN && valorBoton < BOTON_VERDE_MAX)
		botonPulsando = INPUT_VERDE;
	else if (valorBoton > BOTON_AZUL_MIN && valorBoton < BOTON_AZUL_MAX)
		botonPulsando = INPUT_AZUL;
	else if (valorBoton > BOTON_AMARILLO_MIN && valorBoton < BOTON_AMARILLO_MAX)
		botonPulsando = INPUT_AMARILLO;
	else if (valorBoton > BOTON_BLANCO_MIN && valorBoton < BOTON_BLANCO_MAX)
		botonPulsando = INPUT_BLANCO;
	else
		botonPulsando = NONE;

	if (botonPulsando != NONE && ultimoBoton == NONE)	//detecta flanco
	    eventoActual = botonPulsando;

	ultimoBoton = botonPulsando;

}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN){
	if (GPIO_PIN == RESET_Pin)	eventoActual=INPUT_RESET;
}


EventoInput GetEvento(void){
	EventoInput Evento=eventoActual;
	eventoActual=NONE;		//cuando acaba un evento hay que actualizar el enum
	return Evento;
}


uint16_t GetValorPoten(void)	{return valorPoten;}
