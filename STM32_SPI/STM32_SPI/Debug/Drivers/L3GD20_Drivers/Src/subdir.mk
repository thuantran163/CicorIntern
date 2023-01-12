################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/L3GD20_Drivers/Src/L3GD20.c 

OBJS += \
./Drivers/L3GD20_Drivers/Src/L3GD20.o 

C_DEPS += \
./Drivers/L3GD20_Drivers/Src/L3GD20.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/L3GD20_Drivers/Src/%.o Drivers/L3GD20_Drivers/Src/%.su: ../Drivers/L3GD20_Drivers/Src/%.c Drivers/L3GD20_Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-L3GD20_Drivers-2f-Src

clean-Drivers-2f-L3GD20_Drivers-2f-Src:
	-$(RM) ./Drivers/L3GD20_Drivers/Src/L3GD20.d ./Drivers/L3GD20_Drivers/Src/L3GD20.o ./Drivers/L3GD20_Drivers/Src/L3GD20.su

.PHONY: clean-Drivers-2f-L3GD20_Drivers-2f-Src

