#include "Gpio_midderware.h"

static void I2C_BusRecovery();

void GPIO_I2C_Init(void)
{

    I2C_BusRecovery();
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





void I2C_BusRecovery() {
    // Bước 1: Tắt I2C
    I2C_Cmd(I2C1, DISABLE);
    
    // Bước 2: Lưu trữ cấu hình GPIO gốc
    // GPIO_InitTypeDef original_config;
    // original_config.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    // original_config.GPIO_Mode = GPIO_Mode_AF_OD;
    // original_config.GPIO_Speed = GPIO_Speed_50MHz;
    
    // Bước 3: Chuyển tạm thời sang GPIO Output
    GPIO_InitTypeDef temp_config = {
        .GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7,
        .GPIO_Mode = GPIO_Mode_Out_OD,
        .GPIO_Speed = GPIO_Speed_50MHz
    };
    GPIO_Init(GPIOB, &temp_config);
    
    // Bước 4: Tạo 16 xung clock
    for(uint8_t i=0; i<16; i++) {
        GPIO_SetBits(GPIOB, GPIO_Pin_6);  // SCL high
        Delay(1);
        GPIO_ResetBits(GPIOB, GPIO_Pin_6); // SCL low
        Delay(1);
    }
    
    // Bước 5: Tạo điều kiện STOP
    GPIO_SetBits(GPIOB, GPIO_Pin_7);      // SDA high
    GPIO_SetBits(GPIOB, GPIO_Pin_6);      // SCL high
    Delay(1);
    GPIO_ResetBits(GPIOB, GPIO_Pin_7);    // SDA low
    Delay(1);
    GPIO_ResetBits(GPIOB, GPIO_Pin_6);    // SCL low
    
    // Bước 6: Khôi phục cấu hình GPIO
    // GPIO_Init(GPIOB, &original_config);
    
    // Bước 7: Reset phần cứng I2C
    // RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
    // RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
    // I2C_Init(I2C1, &I2C_InitStructure);
    // I2C_Cmd(I2C1, ENABLE);
}