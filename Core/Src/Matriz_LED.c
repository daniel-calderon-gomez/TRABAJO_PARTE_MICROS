

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
static uint8_t matrix_buffer[8] = {0};

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
