################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Boot/common.c \
../Boot/flash_if.c \
../Boot/menu.c \
../Boot/xmodem.c \
../Boot/ymodem.c 

OBJS += \
./Boot/common.o \
./Boot/flash_if.o \
./Boot/menu.o \
./Boot/xmodem.o \
./Boot/ymodem.o 

C_DEPS += \
./Boot/common.d \
./Boot/flash_if.d \
./Boot/menu.d \
./Boot/xmodem.d \
./Boot/ymodem.d 


# Each subdirectory must supply rules for building sources it contributes
Boot/%.o Boot/%.su Boot/%.cyclo: ../Boot/%.c Boot/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/USER/Downloads/240509_ST_Advanced_Tranning/stm32g431_nucleo_boot/CLI" -I"C:/Users/USER/Downloads/240509_ST_Advanced_Tranning/stm32g431_nucleo_boot/Boot" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Boot

clean-Boot:
	-$(RM) ./Boot/common.cyclo ./Boot/common.d ./Boot/common.o ./Boot/common.su ./Boot/flash_if.cyclo ./Boot/flash_if.d ./Boot/flash_if.o ./Boot/flash_if.su ./Boot/menu.cyclo ./Boot/menu.d ./Boot/menu.o ./Boot/menu.su ./Boot/xmodem.cyclo ./Boot/xmodem.d ./Boot/xmodem.o ./Boot/xmodem.su ./Boot/ymodem.cyclo ./Boot/ymodem.d ./Boot/ymodem.o ./Boot/ymodem.su

.PHONY: clean-Boot

