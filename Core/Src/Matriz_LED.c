

#include "Matriz_Led.h"

// Comandos del MAX7219
#define REG_NO_OP       0x00
#define REG_DIGIT_0     0x01
#define REG_DECODE_MODE 0x09
#define REG_INTENSITY   0x0A
#define REG_SCAN_LIMIT  0x0B
#define REG_SHUTDOWN    0x0C
#define REG_DISPLAY_TEST 0x0F

// Buffer para guardar el estado de las 8 filas
uint8_t matrix_buffer[8] = {0};
uint32_t tiempo_pasado_blink;
uint32_t tiempo_pasado_cruz;

static void MAX7219_Write(uint8_t reg, uint8_t data) {
    uint8_t txData[2] = {reg, data};

    HAL_GPIO_WritePin(MAX7219_CS_PORT, MAX7219_CS_PIN, GPIO_PIN_RESET); // CS Low
    HAL_SPI_Transmit(MAX7219_SPI, txData, 2, 100);
    HAL_GPIO_WritePin(MAX7219_CS_PORT, MAX7219_CS_PIN, GPIO_PIN_SET);   // CS High
}

void MAX7219_Init(void) {
    MAX7219_Write(REG_SHUTDOWN, 0x01);    // Salir del modo shutdown
    MAX7219_Write(REG_DISPLAY_TEST, 0x00);// Modo normal (no test)
    MAX7219_Write(REG_DECODE_MODE, 0x00); // Sin decodificación (matriz de puntos)
    MAX7219_Write(REG_SCAN_LIMIT, 0x07);  // Escanear los 8 dígitos (filas)
    MAX7219_Write(REG_INTENSITY, 0x03);   // Brillo medio (0x00 a 0x0F)
    MAX7219_Clear();
}

void MAX7219_Clear(void) {
    for (int i = 0; i < 8; i++) {
        matrix_buffer[i] = 0;
        MAX7219_Write(REG_DIGIT_0 + i, 0);
    }
}

// Enciende un led sin apagar los anteriores
void MAX7219_SetPixel(uint8_t row, uint8_t col) {
    if (row > 7 || col > 7) return;
    matrix_buffer[row] |= (1 << col); //se cambia el buffer

    MAX7219_Write(REG_DIGIT_0 + row, matrix_buffer[row]);
}


void MAX7219_Update(uint8_t intento, uint8_t paso) {
    MAX7219_SetPixel(intento, paso);
}

// Dibuja una carita feliz en la matriz
void MAX7219_Victoria(void) {
    uint8_t feliz_rotada[8] = {
        0x3C, // Fila 0: Marco
        0x42, // Fila 1: Marco
        0x95, // Fila 2: Ojo derecho
        0xA1, // Fila 3: Parte de la sonrisa
        0xA1, // Fila 4: Parte de la sonrisa
        0x95, // Fila 5: Ojo izquierdo
        0x42, // Fila 6: Marco
        0x3C  // Fila 7: Marco
    };

    for (int i = 0; i < 8; i++) {
        matrix_buffer[i] = feliz_rotada[i];
        MAX7219_Write(REG_DIGIT_0 + i, feliz_rotada[i]);
    }
}


void MAX7219_Derrota(void) {
    uint8_t triste_rotada[8] = {
        0x3C, // Fila 0
        0x42, // Fila 1
        0xA5, // Fila 2: Ojo derecho
        0x91, // Fila 3: Mueca triste
        0x91, // Fila 4: Mueca triste
        0xA5, // Fila 5: Ojo izquierdo
		0x42, // Fila 6
		0x3C  // Fila 7
    };

    for (int i = 0; i < 8; i++) {
        matrix_buffer[i] = triste_rotada[i];
        MAX7219_Write(REG_DIGIT_0 + i, triste_rotada[i]);
    }
}

void MAX7219_Parpadeo_total(void) {
	int j = 0;
	uint32_t tiempo_actual_blink = HAL_GetTick();
	if ((tiempo_actual_blink - tiempo_pasado_blink) > 800)
	{
		if(j==1)
			j=0;
		else
			j=1;
		tiempo_pasado_blink = tiempo_actual_blink;
		for (int i = 0; i < 8; i++) {
		        matrix_buffer[i] = j;
		        MAX7219_Write(REG_DIGIT_0 + i, 0);
		    }
	}

}
void MAX7219_Parpadeo_rapido(void) {

    for (int i = 0; i < 8; i++) {
        matrix_buffer[i] = 1;
        MAX7219_Write(REG_DIGIT_0 + i, 0);
    }
    HAL_Delay(300);
    MAX7219_Clear();
}
void MAX7219_Parpadeo_cruz(void) {
	int j = 0;


	uint32_t tiempo_actual_cruz = HAL_GetTick();
	if ((tiempo_actual_cruz - tiempo_pasado_cruz) > 800)
	{
		if(j==1){
			uint8_t cruz[8] = {
					0x81, // Fila 0
					0x42, // Fila 1
					0x24, // Fila 2:
					0x18, // Fila 3:
					0x18, // Fila 4:
					0x24, // Fila 5:
					0x42, // Fila 6
					0x81  // Fila 7
			};
			j=0;
			 for (int i = 0; i < 8; i++) {
				        matrix_buffer[i] = cruz[i];
				        MAX7219_Write(REG_DIGIT_0 + i, cruz[i]);
				    }
		}
		else{
			MAX7219_Clear();
			j=1;
		}
		tiempo_pasado_cruz = tiempo_actual_cruz;
	}
}

