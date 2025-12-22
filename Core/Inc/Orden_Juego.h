//FSM que coordina el orden y en una partida.
#ifndef INC_ORDEN_JUEGO_H_
#define INC_ORDEN_JUEGO_H_

typedef enum {
	RONDA_INICIAL, INPUTS_ESPERA, FIN_RONDA
} FSM_RondasPartida;

void Orden_Juego_Init(void);
void Orden_Juego_Update(void);

#endif /* INC_ORDEN_JUEGO_H_ */
