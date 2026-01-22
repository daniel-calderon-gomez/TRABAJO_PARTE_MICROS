#include "Zumbador.h"

extern TIM_HandleTypeDef htim3;

static BuzzerModo modo_actual = BUZZER_IDLE;
static uint32_t tick_inicio = 0;
static uint8_t paso = 0;
static uint8_t zumbador_fin=0;

 void Buzzer_On(uint16_t duty)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, duty);
}

 void Buzzer_Off(void)
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
    zumbador_fin=0;
}
void Zumbador_Sonar(void) {

    switch (modo_actual)
    {
    case BUZZER_IDLE:
        Buzzer_Off();
        zumbador_fin=1;
        break;

    case BUZZER_VICTORIA:
        if (paso < 10)
        {
            if ((HAL_GetTick() - tick_inicio) > 200)
            {
                tick_inicio = HAL_GetTick();
                paso++;

                if (paso % 2 == 0)
                    Buzzer_On(500);
                else
                    Buzzer_Off();

            }
        }
        else
            modo_actual = BUZZER_IDLE;

        break;

    case BUZZER_DERROTA:
        if (paso == 0)
        {
            Buzzer_On(700);
            tick_inicio = HAL_GetTick();
            paso = 1;
        }
        else if ((HAL_GetTick() - tick_inicio) > 1000)
        {
            Buzzer_Off();
            modo_actual = BUZZER_IDLE;
        }
        break;
    }
}
int Zumbador_FIN(void) {
	return zumbador_fin;
}


