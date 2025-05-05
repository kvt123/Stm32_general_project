################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/src/misc.c \
../Drivers/src/stm32f10x_dma.c \
../Drivers/src/stm32f10x_gpio.c \
../Drivers/src/stm32f10x_i2c.c \
../Drivers/src/stm32f10x_rcc.c 

OBJS += \
./Drivers/src/misc.o \
./Drivers/src/stm32f10x_dma.o \
./Drivers/src/stm32f10x_gpio.o \
./Drivers/src/stm32f10x_i2c.o \
./Drivers/src/stm32f10x_rcc.o 

C_DEPS += \
./Drivers/src/misc.d \
./Drivers/src/stm32f10x_dma.d \
./Drivers/src/stm32f10x_gpio.d \
./Drivers/src/stm32f10x_i2c.d \
./Drivers/src/stm32f10x_rcc.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/src/%.o Drivers/src/%.su Drivers/src/%.cyclo: ../Drivers/src/%.c Drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I../Inc -I"D:/KhanhTV6/STM32F103/project/STM32CubeIDE/workspace_1.17.0/Lcd_I2c_dma/Drivers/include" -I"D:/KhanhTV6/STM32F103/project/STM32CubeIDE/workspace_1.17.0/Lcd_I2c_dma/Midderware/include" -I"D:/KhanhTV6/STM32F103/project/STM32CubeIDE/workspace_1.17.0/Lcd_I2c_dma/App/LCD" -I"D:/KhanhTV6/STM32F103/project/STM32CubeIDE/workspace_1.17.0/Lcd_I2c_dma/Interrupt" -I"D:/KhanhTV6/STM32F103/project/STM32CubeIDE/workspace_1.17.0/Lcd_I2c_dma/App/RTC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-src

clean-Drivers-2f-src:
	-$(RM) ./Drivers/src/misc.cyclo ./Drivers/src/misc.d ./Drivers/src/misc.o ./Drivers/src/misc.su ./Drivers/src/stm32f10x_dma.cyclo ./Drivers/src/stm32f10x_dma.d ./Drivers/src/stm32f10x_dma.o ./Drivers/src/stm32f10x_dma.su ./Drivers/src/stm32f10x_gpio.cyclo ./Drivers/src/stm32f10x_gpio.d ./Drivers/src/stm32f10x_gpio.o ./Drivers/src/stm32f10x_gpio.su ./Drivers/src/stm32f10x_i2c.cyclo ./Drivers/src/stm32f10x_i2c.d ./Drivers/src/stm32f10x_i2c.o ./Drivers/src/stm32f10x_i2c.su ./Drivers/src/stm32f10x_rcc.cyclo ./Drivers/src/stm32f10x_rcc.d ./Drivers/src/stm32f10x_rcc.o ./Drivers/src/stm32f10x_rcc.su

.PHONY: clean-Drivers-2f-src

