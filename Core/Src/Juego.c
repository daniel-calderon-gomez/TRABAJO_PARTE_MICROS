/*
 * Juego.c
 *
 *  Created on: Dec 22, 2025
 *      Author: ariel
 */
#include "Juego.h"
#include "Coordinador.h"


void Juego_Init(void) {
	Coordinador_Init();
}

void Juego_Ejecutar(void) {
	Coordinador_Update();
}

