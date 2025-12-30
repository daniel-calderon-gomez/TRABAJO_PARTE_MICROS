/*
 * Inputs.c
 *
 *  Created on: Dec 22, 2025
 *      Author: ariel
 */
#include "Inputs.h"
#include "main.h"

EventoInput Evento;
static EventoInput eventoActual = NONE;
static uint16_t valorPoten=0;


void Inputs_Init(void) {
	eventoActual = NONE;
	valorPoten=0;
}

void Inputs_Update(void) {}

EventoInput GetEvento(void){
	Evento=eventoActual;
	eventoActual=NONE;		//cuando acaba un evento hay que actualizar el enum
	return Evento;
}

uint16_t GetValorPoten(void){
	return valorPoten;
}
