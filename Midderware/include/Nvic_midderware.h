#ifndef __STM32_NVIC_MIDDERWARE_H
#define __STM32_NVIC_MIDDERWARE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "misc.h"
// #include "i2c_dma_midderware.h"


#define I2C_DMA_TX_IRQn              DMA1_Channel6_IRQn
#define I2C_DMA_RX_IRQn              DMA1_Channel7_IRQn
#define I2C_DMA_TX_IRQHandler        DMA1_Channel6_IRQHandler
#define I2C_DMA_RX_IRQHandler        DMA1_Channel7_IRQHandler   
#define I2C_DMA_PREPRIO              15
#define I2C_DMA_SUBPRIO              15   

void Nvic_I2C_DMA(void);


#ifdef __cplusplus
}
#endif

#endif