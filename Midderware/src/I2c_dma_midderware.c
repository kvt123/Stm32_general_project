

#include "i2c_dma_midderware.h"


__IO uint16_t* DataReadPointer;  
__IO uint16_t* DataWritePointer;  

__IO uint16_t Timeout = I2C_TIMEOUT;

void TIMEOUT_UserCallback(void);
static void HAL_Delay_ms(uint16_t delay);

static void I2C_DMA_LowLevel_Init(void)
{

  RCC_HCLKConfig(RCC_SYSCLK_Div2);
  RCC_PCLK1Config(RCC_HCLK_Div1);
    
  /*!< I2C_SCL_GPIO_CLK and I2C_SDA_GPIO_CLK Periph clock enable */
  RCC_APB2PeriphClockCmd(I2C_SCL_GPIO_CLK | I2C_SDA_GPIO_CLK, ENABLE);

  /*!< I2C Periph clock enable */
  RCC_APB1PeriphClockCmd(I2C_CLK, ENABLE);
    
  /*!< GPIO configuration */  
  GPIO_I2C_Init();
 /* config interrupt TX, RX DMA for i2c */
  Nvic_I2C_DMA();
  
  /*!< I2C DMA TX and RX channels configuration */
  /* Enable the DMA clock */
  RCC_AHBPeriphClockCmd(I2C_DMA_CLK, ENABLE);
  /* config DMA TX, RX channnel*/
  DMA_I2C_Init(); 
}


void I2c_Midderware_Init(void)
{
    I2C_InitTypeDef  I2C_InitStructure;
  
    I2C_DMA_LowLevel_Init();
    
    /*!< I2C configuration */
    /* I2C configuration */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = I2C_SLAVE_ADDRESS7;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = I2C_SPEED;
    
    /* I2C Peripheral Enable */
    I2C_Cmd(LCD_I2C, ENABLE);
    /* Apply I2C configuration after enabling it */
    I2C_Init(LCD_I2C, &I2C_InitStructure);

    /* Enable the I2C peripheral DMA requests */
    I2C_DMACmd(LCD_I2C, ENABLE);
    /* clear BUS ERROR FLAG*/
    I2C_ClearFlag(LCD_I2C, I2C_FLAG_BERR);

}



void I2C_Read_Buffer(uint8_t* pBuffer, uint16_t RegAddr, RegAddrType NumberOfBitAddr, uint16_t NumByteToRead)
{
    Timeout = I2C_TIMEOUT;
    while(I2C_GetFlagStatus(LCD_I2C, I2C_FLAG_BUSY))
    {
      if((Timeout--) == 0) return TIMEOUT_UserCallback();
    }
      /*!< Send START condition */
    I2C_GenerateSTART(LCD_I2C, ENABLE);
    Timeout = I2C_TIMEOUT;
    while(!I2C_GetFlagStatus(LCD_I2C, I2C_EVENT_MASTER_MODE_SELECT))
    {
      if((Timeout--) == 0) return TIMEOUT_UserCallback();
    }
      /*!< Send EEPROM address for write */
    I2C_Send7bitAddress(LCD_I2C, I2C_LCD_ADDRESS7, I2C_Direction_Transmitter);
    Timeout = I2C_TIMEOUT;
    while(I2C_GetFlagStatus(LCD_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
      if((Timeout--) == 0) return TIMEOUT_UserCallback();
    }

    if(Addr_16bit == NumberOfBitAddr)
    {
        /*!< Send the EEPROM's internal address to read from: MSB of the address first */
        I2C_SendData(LCD_I2C, (uint8_t)((RegAddr & 0xFF00) >> 8));    

        /*!< Test on EV8 and clear it */
        Timeout = I2C_TIMEOUT;
        while(!I2C_CheckEvent(LCD_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        {
            if((Timeout--) == 0) return TIMEOUT_UserCallback();
        }

        /*!< Send the EEPROM's internal address to read from: LSB of the address */
        I2C_SendData(LCD_I2C, (uint8_t)(RegAddr & 0x00FF));   


    }
    else
    {
        /*!< Send the EEPROM's internal address to read from: LSB of the address */
        I2C_SendData(LCD_I2C, (uint8_t)(RegAddr & 0x00FF));   
    }

    Timeout = I2C_TIMEOUT;
    while(I2C_GetFlagStatus(LCD_I2C, I2C_FLAG_BTF) == RESET)
    {
        if((Timeout--) == 0) return TIMEOUT_UserCallback();
    }

      /*!< Send STRAT condition a second time */  
  I2C_GenerateSTART(LCD_I2C, ENABLE);
  
  /*!< Test on EV5 and clear it (cleared by reading SR1 then writing to DR) */
  Timeout = I2C_TIMEOUT;
  while(!I2C_CheckEvent(LCD_I2C, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((Timeout--) == 0) return TIMEOUT_UserCallback();
  } 
  
  /*!< Send EEPROM address for read */
  I2C_Send7bitAddress(LCD_I2C, I2C_LCD_ADDRESS7, I2C_Direction_Receiver);
  /*!< Test on EV6 and clear it */
    Timeout = I2C_TIMEOUT;
    while(!I2C_CheckEvent(LCD_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
      if((Timeout--) == 0) return TIMEOUT_UserCallback();
    }  
    
    /* Configure the DMA Rx Channel with the buffer address and the buffer size */
    LowLevel_DMAConfig((uint32_t)pBuffer, (NumByteToRead), DIRECTION_RX);
    
    /* Inform the DMA that the next End Of Transfer Signal will be the last one */
    I2C_DMALastTransferCmd(LCD_I2C, ENABLE); 
    
    /* Enable the DMA Rx Channel */
    DMA_Cmd(I2C_DMA_CHANNEL_RX, ENABLE);   

    return STATUS_OK;
}


void I2C_write_Buffer(uint8_t* pBuffer, uint16_t RegAddr, RegAddrType NumberOfBitAddr, uint16_t NumByteToWrite)
{
    *DataWritePointer = NumByteToWrite;  
  
  /*!< While the bus is busy */
  Timeout = I2C_TIMEOUT;
  while(I2C_GetFlagStatus(LCD_I2C, I2C_FLAG_BUSY))
  {
    if((Timeout--) == 0) return TIMEOUT_UserCallback();
  }
  
  /*!< Send START condition */
  I2C_GenerateSTART(LCD_I2C, ENABLE);
  
  /*!< Test on EV5 and clear it */
  Timeout = I2C_TIMEOUT;
  while(!I2C_CheckEvent(LCD_I2C, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((Timeout--) == 0) return TIMEOUT_UserCallback();
  }
  
  /*!< Send EEPROM address for write */
  Timeout = I2C_TIMEOUT;
  I2C_Send7bitAddress(LCD_I2C, I2C_LCD_ADDRESS7, I2C_Direction_Transmitter);

  /*!< Test on EV6 and clear it */
  Timeout = I2C_TIMEOUT;
  while(!I2C_CheckEvent(LCD_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if((Timeout--) == 0) return TIMEOUT_UserCallback();
  }

  if(Addr_16bit == NumberOfBitAddr)
  {
      /*!< Send the EEPROM's internal address to write to : only one byte Address */
      I2C_SendData(LCD_I2C, (uint8_t)(RegAddr & 0x00FF));
  }
  else
  {
  
    /*!< Send the EEPROM's internal address to write to : MSB of the address first */
    I2C_SendData(LCD_I2C, (uint8_t)((RegAddr & 0xFF00) >> 8));

    /*!< Test on EV8 and clear it */
    Timeout = I2C_TIMEOUT;  
    while(!I2C_CheckEvent(LCD_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
        if((Timeout--) == 0) return TIMEOUT_UserCallback();
    }  
    
    /*!< Send the EEPROM's internal address to write to : LSB of the address */
    I2C_SendData(LCD_I2C, (uint8_t)(RegAddr & 0x00FF));
  
  }
  
  /*!< Test on EV8 and clear it */
  Timeout = I2C_TIMEOUT; 
  while(!I2C_CheckEvent(LCD_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((Timeout--) == 0) return TIMEOUT_UserCallback();
  }  
  
  /* Configure the DMA Tx Channel with the buffer address and the buffer size */
  LowLevel_DMAConfig((uint32_t)pBuffer, (NumByteToWrite), DIRECTION_TX);
    
  /* Enable the DMA Tx Channel */
  DMA_Cmd(I2C_DMA_CHANNEL_TX, ENABLE);
  
  /* If all operations OK, return STATUS_OK (0) */
  return STATUS_OK;

}


void I2C_write(I2C_TypeDef* i2c, uint8_t Device_Addr,  uint8_t* pBuffer, uint16_t NumByteToWrite)
{
    *DataWritePointer = NumByteToWrite;  
  
  /*!< While the bus is busy */
  Timeout = I2C_TIMEOUT;
  while(I2C_GetFlagStatus(i2c, I2C_FLAG_BUSY))
  {
    if((Timeout--) == 0) return TIMEOUT_UserCallback();
  }
  
  /*!< Send START condition */
  I2C_GenerateSTART(i2c, ENABLE);
  
  /*!< Test on EV5 and clear it */
  Timeout = I2C_TIMEOUT;
  while(!I2C_CheckEvent(i2c, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((Timeout--) == 0) return TIMEOUT_UserCallback();
  }
  
  /*!< Send LCD address for write */
  Timeout = I2C_TIMEOUT;
  I2C_Send7bitAddress(i2c, Device_Addr << 1, I2C_Direction_Transmitter);

  /*!< Test on EV6 and clear it */
  Timeout = I2C_TIMEOUT;
  while(!I2C_CheckEvent(i2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if((Timeout--) == 0) return TIMEOUT_UserCallback();
  }

  
  /* Configure the DMA Tx Channel with the buffer address and the buffer size */
  LowLevel_DMAConfig((uint32_t)pBuffer, (uint8_t)(NumByteToWrite), DIRECTION_TX);
    
  /* Enable the DMA Tx Channel */
  DMA_Cmd(I2C_DMA_CHANNEL_TX, ENABLE);
  
  /* If all operations OK, return STATUS_OK (0) */
  return STATUS_OK;

}



void I2C_Read(I2C_TypeDef* i2c, uint8_t Device_Addr, uint8_t* pBuffer, uint8_t RegAddr, uint16_t NumByteToRead)
{
    Timeout = I2C_TIMEOUT;
    while(I2C_GetFlagStatus(i2c, I2C_FLAG_BUSY))
    {
      if((Timeout--) == 0) return TIMEOUT_UserCallback();
    }
      /*!< Send START condition */
    I2C_GenerateSTART(i2c, ENABLE);
    Timeout = I2C_TIMEOUT;
    while(!I2C_GetFlagStatus(i2c, I2C_EVENT_MASTER_MODE_SELECT))
    {
      if((Timeout--) == 0) return TIMEOUT_UserCallback();
    }
    Delay(1);
      /*!< Send address for write */
    I2C_Send7bitAddress(i2c, Device_Addr << 1, I2C_Direction_Transmitter);
    Timeout = I2C_TIMEOUT;
    while(!I2C_GetFlagStatus(i2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
      if((Timeout--) == 0) return TIMEOUT_UserCallback();
    }

    Delay(1);

    if (I2C_GetFlagStatus(i2c, I2C_FLAG_ADDR)) {
        volatile uint32_t temp = i2c->SR1;
        temp = i2c->SR2;  // Xóa cờ ADDR
    }

    while (!I2C_GetFlagStatus(I2C1, I2C_FLAG_TXE)); // Đợi sẵn sàng


    /*!< Send the RTC's internal address to read from: LSB of the address */
    I2C_SendData(i2c, (uint8_t)(RegAddr & 0xFF));   

    Timeout = I2C_TIMEOUT;
    while(I2C_GetFlagStatus(i2c, I2C_FLAG_BTF) == RESET)
    {
        if((Timeout--) == 0) return TIMEOUT_UserCallback();
    }

      /*!< Send STRAT condition a second time */  
  I2C_GenerateSTART(i2c, ENABLE);
  
  /*!< Test on EV5 and clear it (cleared by reading SR1 then writing to DR) */
  Timeout = I2C_TIMEOUT;
  while(!I2C_CheckEvent(i2c, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((Timeout--) == 0) return TIMEOUT_UserCallback();
  } 
  
  /*!< Send RTC address for read */
  I2C_Send7bitAddress(i2c, Device_Addr << 1, I2C_Direction_Receiver);  


  if (NumByteToRead < 2)
  {
    /* Wait on ADDR flag to be set (ADDR is still not cleared at this level */
    Timeout = I2C_TIMEOUT;
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_ADDR) == RESET)
    {
      if((Timeout--) == 0) return TIMEOUT_UserCallback();
    }     
    
    /*!< Disable Acknowledgement */
    I2C_AcknowledgeConfig(I2C1, DISABLE);   

    /* Call User callback for critical section start (should typically disable interrupts) */
    __disable_irq();  
    
    /* Clear ADDR register by reading SR1 then SR2 register (SR1 has already been read) */
    (void)I2C1->SR2;
    
    /*!< Send STOP Condition */
    I2C_GenerateSTOP(I2C1, ENABLE);
   
    /* Call User callback for critical section end (should typically re-enable interrupts) */
    __enable_irq();
    
    /* Wait for the byte to be received */
    Timeout = I2C_TIMEOUT;
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == RESET)
    {
      if((Timeout--) == 0) return TIMEOUT_UserCallback();
    }
    
    /*!< Read the byte received from the EEPROM */
    *pBuffer = I2C_ReceiveData(I2C1);
    
    /*!< Decrement the read bytes counter */
    (uint16_t)(NumByteToRead)--;        
    
    /* Wait to make sure that STOP control bit has been cleared */
    Timeout = I2C_TIMEOUT;
    while(I2C1->CR1 & I2C_CR1_STOP)
    {
      if((Timeout--) == 0) return TIMEOUT_UserCallback();
    }  
    
    /*!< Re-Enable Acknowledgement to be ready for another reception */
    I2C_AcknowledgeConfig(I2C1, ENABLE);    
  }
  else
  {
    /*!< Test on EV6 and clear it */
    Timeout = I2C_TIMEOUT;
    while(!I2C_CheckEvent(i2c, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
      if((Timeout--) == 0) return TIMEOUT_UserCallback();
    }
    /* Configure the DMA Rx Channel with the buffer address and the buffer size */
    LowLevel_DMAConfig((uint32_t)pBuffer, (NumByteToRead), DIRECTION_RX);
    
    /* Inform the DMA that the next End Of Transfer Signal will be the last one */
    I2C_DMALastTransferCmd(i2c, ENABLE); 
    
    /* Enable the DMA Rx Channel */
    DMA_Cmd(I2C_DMA_CHANNEL_RX, ENABLE);   

  }

    return STATUS_OK;
}


void TIMEOUT_UserCallback(void)
{
    while(1);
}



