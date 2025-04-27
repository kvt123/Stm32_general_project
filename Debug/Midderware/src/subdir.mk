################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Midderware/src/Dma_midderware.c \
../Midderware/src/Gpio_midderware.c \
../Midderware/src/I2c_Lcd.c \
../Midderware/src/I2c_dma_midderware.c \
../Midderware/src/Nvic_midderware.c 

OBJS += \
./Midderware/src/Dma_midderware.o \
./Midderware/src/Gpio_midderware.o \
./Midderware/src/I2c_Lcd.o \
./Midderware/src/I2c_dma_midderware.o \
./Midderware/src/Nvic_midderware.o 

C_DEPS += \
./Midderware/src/Dma_midderware.d \
./Midderware/src/Gpio_midderware.d \
./Midderware/src/I2c_Lcd.d \
./Midderware/src/I2c_dma_midderware.d \
./Midderware/src/Nvic_midderware.d 


# Each subdirectory must supply rules for building sources it contributes
Midderware/src/%.o Midderware/src/%.su Midderware/src/%.cyclo: ../Midderware/src/%.c Midderware/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I../Inc -I"D:/KhanhTV6/STM32F103/project/STM32CubeIDE/workspace_1.17.0/Lcd_I2c_dma/Drivers/include" -I"D:/KhanhTV6/STM32F103/project/STM32CubeIDE/workspace_1.17.0/Lcd_I2c_dma/Midderware/include" -I"D:/KhanhTV6/STM32F103/project/STM32CubeIDE/workspace_1.17.0/Lcd_I2c_dma/App/LCD" -I"D:/KhanhTV6/STM32F103/project/STM32CubeIDE/workspace_1.17.0/Lcd_I2c_dma/Interrupt" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Midderware-2f-src

clean-Midderware-2f-src:
	-$(RM) ./Midderware/src/Dma_midderware.cyclo ./Midderware/src/Dma_midderware.d ./Midderware/src/Dma_midderware.o ./Midderware/src/Dma_midderware.su ./Midderware/src/Gpio_midderware.cyclo ./Midderware/src/Gpio_midderware.d ./Midderware/src/Gpio_midderware.o ./Midderware/src/Gpio_midderware.su ./Midderware/src/I2c_Lcd.cyclo ./Midderware/src/I2c_Lcd.d ./Midderware/src/I2c_Lcd.o ./Midderware/src/I2c_Lcd.su ./Midderware/src/I2c_dma_midderware.cyclo ./Midderware/src/I2c_dma_midderware.d ./Midderware/src/I2c_dma_midderware.o ./Midderware/src/I2c_dma_midderware.su ./Midderware/src/Nvic_midderware.cyclo ./Midderware/src/Nvic_midderware.d ./Midderware/src/Nvic_midderware.o ./Midderware/src/Nvic_midderware.su

.PHONY: clean-Midderware-2f-src

