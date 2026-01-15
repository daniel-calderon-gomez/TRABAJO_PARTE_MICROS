
#include "Logica_Juego.h"

void Logica_Juego_Comparar(EventoInput objetivo[], EventoInput intento[], Resultado resultado[])
{
    for (int i = 0; i < MAX_PULSACIONES; i++){
    	if (intento[i] == objetivo[i])
    		resultado[i] = RES_ESTA_CORRECTO;

        else
        {
            int encontrado = 0;

            for (int j = 0; j < MAX_PULSACIONES; j++)	//corregir que un verde anterior o posterior puede dar amarillo en otra pposicion
            {
            	if (intento[i] == objetivo[j])
                {
                	encontrado = 1;
                    break;
                }
            }

            if (encontrado)
                resultado[i] = RES_ESTA_OTRA_POS;
            else
            	resultado[i] = RES_NO_ESTA;
        }
    }
}
