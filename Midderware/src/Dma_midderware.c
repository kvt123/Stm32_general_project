
#include "Dma_midderware.h"


DMA_InitTypeDef   DMA_InitStructure; 

void LowLevel_DMAConfig(uint32_t pBuffer, uint32_t BufferSize, uint32_t Direction)
{ 
  /* Initialize the DMA with the new parameters */
  if (Direction == DIRECTION_TX)
  {
    /* Configure the DMA Tx Channel with the buffer address and the buffer size */
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)pBuffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;    
    DMA_InitStructure.DMA_BufferSize = (uint32_t)BufferSize;  
    DMA_Init(I2C_DMA_CHANNEL_TX, &DMA_InitStructure);  
  }
  else
  { 
    /* Configure the DMA Rx Channel with the buffer address and the buffer size */
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)pBuffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = (uint32_t)BufferSize;      
    DMA_Init(I2C_DMA_CHANNEL_RX, &DMA_InitStructure);    
  }
}

void DMA_I2C_Init(void)
{
  /* I2C TX DMA Channel configuration */
  DMA_DeInit(I2C_DMA_CHANNEL_TX);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)I2C_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)0;   /* This parameter will be configured durig communication */
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;    /* This parameter will be configured durig communication */
  DMA_InitStructure.DMA_BufferSize = 0xFFFF;            /* This parameter will be configured durig communication */
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(I2C_DMA_CHANNEL_TX, &DMA_InitStructure);  
  
  /* I2C RX DMA Channel configuration */
  DMA_DeInit(I2C_DMA_CHANNEL_RX);
  DMA_Init(I2C_DMA_CHANNEL_RX, &DMA_InitStructure);  
  
  /* Enable the DMA Channels Interrupts */
  DMA_ITConfig(I2C_DMA_CHANNEL_TX, DMA_IT_TC, ENABLE);
  DMA_ITConfig(I2C_DMA_CHANNEL_RX, DMA_IT_TC, ENABLE);    
}