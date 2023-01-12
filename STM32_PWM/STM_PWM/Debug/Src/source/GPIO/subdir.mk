################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/source/GPIO/gpio.c 

OBJS += \
./Src/source/GPIO/gpio.o 

C_DEPS += \
./Src/source/GPIO/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
Src/source/GPIO/%.o Src/source/GPIO/%.su: ../Src/source/GPIO/%.c Src/source/GPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-source-2f-GPIO

clean-Src-2f-source-2f-GPIO:
	-$(RM) ./Src/source/GPIO/gpio.d ./Src/source/GPIO/gpio.o ./Src/source/GPIO/gpio.su

.PHONY: clean-Src-2f-source-2f-GPIO

