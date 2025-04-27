
#ifndef __STM32_I2C_DMA_H
#define __STM32_I2C_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif


#include "Gpio_midderware.h"
#include "Nvic_midderware.h"
#include "Dma_midderware.h"
#include "stm32f10x_i2c.h"


/**
  * @}
  */

/** @addtogroup STM32_I2C
  */
/**
  * @brief  I2C Interface
  */  

 #define LCD_I2C             I2C1

#define I2C_TIMEOUT         ((uint32_t)(100000))


#define I2C_SPEED               200000
#define I2C_SLAVE_ADDRESS7      0x4E

#define STATUS_OK               0
#define STATUS_FALSE            1

typedef enum
{
  Addr_8bit,
  Addr_16bit,
}RegAddrType;


void I2c_Midderware_Init(void);
void I2C_Read_Buffer(uint8_t* pBuffer, uint16_t RegAddr, RegAddrType NumberOfBitAddr, uint16_t NumByteToRead);
void I2C_write_Buffer(uint8_t* pBuffer, uint16_t RegAddr, RegAddrType NumberOfBitAddr, uint16_t NumByteToRead);
void I2C_write_LCD(uint8_t* pBuffer, uint16_t NumByteToWrite);
void TIMEOUT_UserCallback(void);

#ifdef __cplusplus
}
#endif

#endif