#ifndef INC_ZUMBADOR_H_
#define INC_ZUMBADOR_H_
#include "stm32f4xx_hal.h"

typedef enum
{
	BUZZER_IDLE,
    BUZZER_VICTORIA,
    BUZZER_DERROTA
} BuzzerModo;


void Zumbador_Init(void);
void Zumbador_Update(void);
void Zumbador_SetModo(BuzzerModo modo);

#endif /* INC_ZUMBADOR_H_ */
