#ifndef __STM32_GPIO_MIDDERWARE_H
#define __STM32_GPIO_MIDDERWARE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
// #include "i2c_dma_midderware.h"

#define I2C_CLK                      RCC_APB1Periph_I2C1
#define I2C_SCL_PIN                  GPIO_Pin_6                  /* PB.06 */
#define I2C_SCL_GPIO_PORT            GPIOB                       /* GPIOB */
#define I2C_SCL_GPIO_CLK             RCC_APB2Periph_GPIOB
#define I2C_SDA_PIN                  GPIO_Pin_7                  /* PB.07 */
#define I2C_SDA_GPIO_PORT            GPIOB                       /* GPIOB */
#define I2C_SDA_GPIO_CLK             RCC_APB2Periph_GPIOB


void GPIO_I2C_Init(void);



#ifdef __cplusplus
}
#endif

#endif