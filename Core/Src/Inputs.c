#include "Inputs.h"

#define SIN_BOTON 100
#define BOTON_ROJO_MIN 2000
#define BOTON_ROJO_MAX 2729
#define BOTON_VERDE_MIN 2830
#define BOTON_VERDE_MAX 3039
#define BOTON_AZUL_MIN 3040
#define BOTON_AZUL_MAX 3279
#define BOTON_AMARILLO_MIN 3280
#define BOTON_AMARILLO_MAX 3567
#define BOTON_BLANCO_MIN 3570
#define BOTON_BLANCO_MAX 4000



static volatile EventoInput eventoActual = NONE;
volatile uint8_t flag_reset=0;

static EventoInput ultimoBoton = NONE;
static EventoInput ultimoPoten = NONE;


static uint16_t valorPoten=0;
static uint16_t valorBoton=0;

uint32_t ultimo_tiempo_reset=0;

void Inputs_Init(void) {
	eventoActual = NONE;
	valorPoten=0;
	valorBoton=0;
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
    HAL_ADC_PollForConversion(&hadc1, 10);

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
	if (GPIO_PIN == GPIO_PIN_0){
		flag_reset=1;
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	}
}


EventoInput GetEvento(void){
	__disable_irq();
	EventoInput Evento=eventoActual;
	eventoActual=NONE;		//cuando acaba un evento hay que actualizar el enum
	__enable_irq();
	return Evento;
}


uint16_t GetValorPoten(void)	{return valorPoten;}
