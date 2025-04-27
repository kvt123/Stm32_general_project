/**
  ******************************************************************************
  * @file    USART/Interrupt/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"


/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_Interrupt
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// extern uint8_t TxBuffer1[]; 
// extern uint8_t TxBuffer2[]; 
// extern uint8_t RxBuffer1[];
// extern uint8_t RxBuffer2[];
// extern __IO uint8_t TxCounter1;
// extern __IO uint8_t TxCounter2;
// extern __IO uint8_t RxCounter1; 
// extern __IO uint8_t RxCounter2;
// extern uint8_t NbrOfDataToTransfer1;
// extern uint8_t NbrOfDataToTransfer2;
// extern uint8_t NbrOfDataToRead1;
// extern uint8_t NbrOfDataToRead2;
extern __IO uint8_t Timeout;
extern __IO uint16_t* DataWritePointer;
extern __IO uint16_t* DataReadPointer;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles USARTy global interrupt request.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{


}

/**
  * @brief  This function handles USARTz global interrupt request.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{

}



void DMA1_Channel6_IRQHandler(void)
{
  /* Check if the DMA transfer is complete */ 
  if(DMA_GetFlagStatus(I2C_DMA_FLAG_TX_TC) != RESET)
  {  
    /* Disable the DMA Tx Channel and Clear all its Flags */  
    DMA_Cmd(I2C_DMA_CHANNEL_TX, DISABLE);
    DMA_ClearFlag(I2C_DMA_FLAG_TX_GL);

    /*!< Wait till all data have been physically transferred on the bus */
    Timeout = I2C_TIMEOUT;
    while(!I2C_GetFlagStatus(LCD_I2C, I2C_FLAG_BTF))
    {
      if((Timeout--) == 0) TIMEOUT_UserCallback();
    }
    
    /*!< Send STOP condition */
    I2C_GenerateSTOP(LCD_I2C, ENABLE);
    
    /* Perform a read on SR1 and SR2 register to clear eventualaly pending flags */
    (void)LCD_I2C->SR1;
    (void)LCD_I2C->SR2;
    
    /* Reset the variable holding the number of data to be written */
    *DataWritePointer = 0;  
  }
}

/**
  * @brief  This function handles the DMA Rx Channel interrupt Handler.
  * @param  None
  * @retval None
  */
void DMA1_Channel7_IRQHandler(void)
{
  /* Check if the DMA transfer is complete */
  if(DMA_GetFlagStatus(I2C_DMA_FLAG_RX_TC) != RESET)
  {      
    /*!< Send STOP Condition */
    I2C_GenerateSTOP(LCD_I2C, ENABLE);    
    
    /* Disable the DMA Rx Channel and Clear all its Flags */  
    DMA_Cmd(I2C_DMA_CHANNEL_RX, DISABLE);
    DMA_ClearFlag(I2C_DMA_FLAG_RX_GL);
    
    /* Reset the variable holding the number of data to be read */
    *DataReadPointer = 0;
  }
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
