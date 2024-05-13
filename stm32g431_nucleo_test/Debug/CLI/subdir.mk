################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CLI/cli_interface.c 

OBJS += \
./CLI/cli_interface.o 

C_DEPS += \
./CLI/cli_interface.d 


# Each subdirectory must supply rules for building sources it contributes
CLI/%.o CLI/%.su CLI/%.cyclo: ../CLI/%.c CLI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/USER/Downloads/240509_ST_Advanced_Tranning/stm32g431_nucleo/stm32g431_nucleo_test/CLI" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CLI

clean-CLI:
	-$(RM) ./CLI/cli_interface.cyclo ./CLI/cli_interface.d ./CLI/cli_interface.o ./CLI/cli_interface.su

.PHONY: clean-CLI

