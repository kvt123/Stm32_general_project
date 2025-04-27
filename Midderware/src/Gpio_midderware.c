#include "Gpio_midderware.h"

void GPIO_I2C_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    /*!< GPIO configuration */  
    /*!< Configure I2C pins: SCL */
    GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure I2C pins: SDA */
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
    GPIO_Init(I2C_SDA_GPIO_PORT, &GPIO_InitStructure); 
}