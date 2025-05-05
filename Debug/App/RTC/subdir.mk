################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/RTC/RTC.c 

OBJS += \
./App/RTC/RTC.o 

C_DEPS += \
./App/RTC/RTC.d 


# Each subdirectory must supply rules for building sources it contributes
App/RTC/%.o App/RTC/%.su App/RTC/%.cyclo: ../App/RTC/%.c App/RTC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I../Inc -I"D:/KhanhTV6/STM32F103/project/STM32CubeIDE/workspace_1.17.0/Lcd_I2c_dma/Drivers/include" -I"D:/KhanhTV6/STM32F103/project/STM32CubeIDE/workspace_1.17.0/Lcd_I2c_dma/Midderware/include" -I"D:/KhanhTV6/STM32F103/project/STM32CubeIDE/workspace_1.17.0/Lcd_I2c_dma/App/LCD" -I"D:/KhanhTV6/STM32F103/project/STM32CubeIDE/workspace_1.17.0/Lcd_I2c_dma/Interrupt" -I"D:/KhanhTV6/STM32F103/project/STM32CubeIDE/workspace_1.17.0/Lcd_I2c_dma/App/RTC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-RTC

clean-App-2f-RTC:
	-$(RM) ./App/RTC/RTC.cyclo ./App/RTC/RTC.d ./App/RTC/RTC.o ./App/RTC/RTC.su

.PHONY: clean-App-2f-RTC

