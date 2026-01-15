
#ifndef INC_MAX7219_MATRIX_H_
#define INC_MAX7219_MATRIX_H_

#include "stm32f4xx_hal.h"

// Definimos el spi1
extern SPI_HandleTypeDef hspi1;
#define MAX7219_SPI &hspi1

//Definimos pin y puerto de CS
#define MAX7219_CS_PORT GPIOA
#define MAX7219_CS_PIN  GPIO_PIN_4

void MAX7219_Init(void);
void MAX7219_Clear(void);
void MAX7219_SetPixel(uint8_t row, uint8_t col);
void MAX7219_Update(uint8_t intento, uint8_t paso);

#endif /* INC_MAX7219_MATRIX_H_ */
