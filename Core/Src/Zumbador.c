#include "Zumbador.h"

extern TIM_HandleTypeDef htim3;

static BuzzerModo modo_actual = BUZZER_IDLE;
static uint32_t tick_inicio = 0;
static uint8_t paso = 0;

static void Buzzer_On(uint16_t duty)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, duty);
}

static void Buzzer_Off(void)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
}


void Zumbador_Init(void) {
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	Buzzer_Off();
	modo_actual = BUZZER_IDLE;
}

void Zumbador_SetModo(BuzzerModo modo){
    modo_actual = modo;
    tick_inicio = HAL_GetTick();
    paso = 0;
}

void Zumbador_Update(void) {
	uint32_t ahora = HAL_GetTick();

	    switch (modo_actual)
	    {
	    case BUZZER_IDLE:
	        Buzzer_Off();
	        break;

	    case BUZZER_VICTORIA:
	        if (paso < 6)
	        {
	            if ((ahora - tick_inicio) > 200)
	            {
	                tick_inicio = ahora;
	                paso++;

	                if (paso % 2 == 0)
	                    Buzzer_On(500);
	                else
	                    Buzzer_Off();
	            }
	        }
	        else
	        {
	            modo_actual = BUZZER_IDLE;
	        }
	        break;

	    case BUZZER_DERROTA:
	        if (paso == 0)
	        {
	            Buzzer_On(700);
	            tick_inicio = ahora;
	            paso = 1;
	        }
	        else if ((ahora - tick_inicio) > 1000)
	        {
	            Buzzer_Off();
	            modo_actual = BUZZER_IDLE;
	        }
	        break;
	    }
}

