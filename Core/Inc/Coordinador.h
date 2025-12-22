/*
 * Coordinador.h
 *
 *  Created on: Dec 22, 2025
 *      Author: ariel
 */

#ifndef INC_COORDINADOR_H_
#define INC_COORDINADOR_H_

typedef enum {
	INICIO, SELECCION_MODO, JUEGO1vs1, JUEGO1vsPC, VICTORIA, DERROTA
} FSM_JUEGO;

void Coordinador_Init(void);
void Coordinador_Update(void);

#endif /* INC_COORDINADOR_H_ */
