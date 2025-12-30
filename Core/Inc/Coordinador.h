/*
 * Coordinador.h
 *
 *  Created on: Dec 22, 2025
 *      Author: ariel
 */

#ifndef INC_COORDINADOR_H_
#define INC_COORDINADOR_H_

typedef enum {
	INICIO, SELECCION_MODO, SET_SECUENCIA, ADIVINAR, VICTORIA, DERROTA
} FSM_JUEGO;

void Coordinador_Init(void);
void Coordinador_Update(void);
FSM_JUEGO Coordinador_GetEstado(void);

#endif /* INC_COORDINADOR_H_ */
