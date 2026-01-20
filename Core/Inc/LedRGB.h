#ifndef INC_LEDRGB_H_
#define INC_LEDRGB_H_

#include <stdint.h>
#include "TiposJuego.h"

typedef enum {
    LEDRGB_OFF,
    LEDRGB_ROJO,
    LEDRGB_VERDE,
    LEDRGB_AZUL,
    LEDRGB_AMARILLO,
    LEDRGB_BLANCO
} LED_Color;

typedef enum {
	FEEDBACK_OFF,
    FEEDBACK_ROJO,
    FEEDBACK_AMARILLO,
    FEEDBACK_VERDE
} LED_Feedback;

void LEDRGB_Init(void);
void LEDRGB_Off(void);
void LEDRGB_FeedbackOff(void);

void LEDRGB_SetColor1(LED_Color color);
void LEDRGB_SetFeedback(LED_Feedback feedback);

void ArcoirisFeedback_Init(void);
void ArcoirisFeedback_Update(void);


#endif /* INC_LEDRGB_H_ */
