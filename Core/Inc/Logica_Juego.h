//se define la secuencia secreta, se compara el color y posicion, contadores de turno y posiciones, condiciones de victoria... SOLO LOGICA DE CODIGO

#ifndef INC_LOGICA_JUEGO_H_
#define INC_LOGICA_JUEGO_H_

#include "TiposJuego.h"
#include "Inputs.h"

#define MAX_PULSACIONES 5
void Logica_Juego_Comparar(EventoInput objetivo[], EventoInput intento[], Resultado resultado[]);


#endif /* INC_LOGICA_JUEGO_H_ */

