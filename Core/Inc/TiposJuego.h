/*
 * TiposJuego.h
 *
 *  Created on: Dec 30, 2025
 *      Author: Daniel-PC
 */

#ifndef INC_TIPOSJUEGO_H_
#define INC_TIPOSJUEGO_H_

typedef enum {
	COLOR_ROJO,
	COLOR_VERDE,
	COLOR_AZUL,
	COLOR_AMARILLO,
	COLOR_BLANCO,
	COLOR_NINGUNO
} Color;

typedef enum {
	MODO_PvP,
	MODO_PvPC
} ModoJuego;

typedef enum {
    RES_NO_ESTA,
    RES_ESTA_OTRA_POS,
    RES_ESTA_CORRECTO
} Resultado;

#endif /* INC_TIPOSJUEGO_H_ */
