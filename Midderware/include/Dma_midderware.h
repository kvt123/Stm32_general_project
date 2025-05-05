#ifndef __STM32_DMA_MIDDERWARE_H
#define __STM32_DMA_MIDDERWARE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x_dma.h"
#include "stm32f10x_rcc.h"
// #include "i2c_dma_midderware.h"

#define I2C_DMA                      DMA1   
#define I2C_DMA_CHANNEL_TX           DMA1_Channel6
#define I2C_DMA_CHANNEL_RX           DMA1_Channel7
#define I2C_DMA_FLAG_TX_TC           DMA1_IT_TC6   
#define I2C_DMA_FLAG_TX_GL           DMA1_IT_GL6 
#define I2C_DMA_FLAG_RX_TC           DMA1_IT_TC7 
#define I2C_DMA_FLAG_RX_GL           DMA1_IT_GL7    
#define I2C_DMA_CLK                  RCC_AHBPeriph_DMA1
#define I2C_DR_Address               ((uint32_t)0x40005410)

#define DIRECTION_TX                 0
#define DIRECTION_RX                 1  

void LowLevel_DMAConfig(uint32_t* pBuffer, uint32_t BufferSize, uint32_t Direction);
void DMA_I2C_Init(void);



#ifdef __cplusplus
}
#endif

#endif