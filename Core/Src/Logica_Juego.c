
#include "Logica_Juego.h"

void Logica_Juego_Comparar(EventoInput objetivo[], EventoInput intento[], Resultado resultado[])
{
	uint8_t objetivo_contado[MAX_PULSACIONES]={0};
	uint8_t intento_contado[MAX_PULSACIONES]={0};

    for (int i = 0; i < MAX_PULSACIONES; i++){	//check verde
    	if (intento[i] == objetivo[i]){
    		resultado[i] = RES_ESTA_CORRECTO;
    		objetivo_contado[i]=1;
    		intento_contado[i]=1;
    	} else resultado[i]=RES_NO_ESTA;
    }

     for (int i = 0; i < MAX_PULSACIONES; i++){
    	 if(intento_contado[i]) continue;

            for (int j = 0; j < MAX_PULSACIONES; j++)
            {
            	if(objetivo_contado[i]) continue;

            	if(intento[i]==objetivo[j]){
            		resultado[i]=RES_ESTA_OTRA_POS;
            		objetivo_contado[i]=1;
            		intento_contado[i]=1;
            		break;
            	}
            }
     }
}




