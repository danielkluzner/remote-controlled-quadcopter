#ifndef __STM32L476G_DISCOVERY_nRF24L01
#define __STM32L476G_DISCOVERY_nRF24L01

#include "stm32l476xx.h"

#define nRF24L01_CONFIG         0x00    // Configuration
#define nRF24L01_STATUS         0x04    // Status Register

/* Multiple byte read/write command */ 
#define MULTIPLEBYTE_CMD        ((uint8_t)0x40)

// PE12 = TRX_CSN (Deselect = Chip Select NOT high)
#define nRF24L01_CSN_LOW		GPIOE->ODR &= ~(1U << 12);
#define nRF24L01_CSN_HIGH		GPIOE->ODR |=  (1U << 12);

// PE11 = TRX_CE (Chip enable)
#define nRF24L01_CE_ON			GPIOE->ODR |=  (1U << 11);
#define nRF24l01_CE_OFF			GPIOE->ODR &= ~(1U << 11);

void TRX_Init(void);
void TRX_IO_Init(void);
void TRX_IO_Write(uint8_t *pBuffer, uint8_t WriteAddr, uint8_t NumByteToWrite);
void TRX_IO_Read(uint8_t *pBuffer, uint8_t ReadAddr, uint8_t NumByteToRead);
void nRF24L01_Init(void);

#endif /* __STM32L476G_DISCOVERY_L3GD20_H */
