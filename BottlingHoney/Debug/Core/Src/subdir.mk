################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Button.c \
../Core/Src/Buzzer.c \
../Core/Src/Eeprom.c \
../Core/Src/GFX_BW.c \
../Core/Src/HX711.c \
../Core/Src/Honey_Display.c \
../Core/Src/Honey_StateMachine.c \
../Core/Src/SSD1306_OLED.c \
../Core/Src/Servo.c \
../Core/Src/dma.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/main.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/Button.o \
./Core/Src/Buzzer.o \
./Core/Src/Eeprom.o \
./Core/Src/GFX_BW.o \
./Core/Src/HX711.o \
./Core/Src/Honey_Display.o \
./Core/Src/Honey_StateMachine.o \
./Core/Src/SSD1306_OLED.o \
./Core/Src/Servo.o \
./Core/Src/dma.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/main.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/Button.d \
./Core/Src/Buzzer.d \
./Core/Src/Eeprom.d \
./Core/Src/GFX_BW.d \
./Core/Src/HX711.d \
./Core/Src/Honey_Display.d \
./Core/Src/Honey_StateMachine.d \
./Core/Src/SSD1306_OLED.d \
./Core/Src/Servo.d \
./Core/Src/dma.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/main.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Button.cyclo ./Core/Src/Button.d ./Core/Src/Button.o ./Core/Src/Button.su ./Core/Src/Buzzer.cyclo ./Core/Src/Buzzer.d ./Core/Src/Buzzer.o ./Core/Src/Buzzer.su ./Core/Src/Eeprom.cyclo ./Core/Src/Eeprom.d ./Core/Src/Eeprom.o ./Core/Src/Eeprom.su ./Core/Src/GFX_BW.cyclo ./Core/Src/GFX_BW.d ./Core/Src/GFX_BW.o ./Core/Src/GFX_BW.su ./Core/Src/HX711.cyclo ./Core/Src/HX711.d ./Core/Src/HX711.o ./Core/Src/HX711.su ./Core/Src/Honey_Display.cyclo ./Core/Src/Honey_Display.d ./Core/Src/Honey_Display.o ./Core/Src/Honey_Display.su ./Core/Src/Honey_StateMachine.cyclo ./Core/Src/Honey_StateMachine.d ./Core/Src/Honey_StateMachine.o ./Core/Src/Honey_StateMachine.su ./Core/Src/SSD1306_OLED.cyclo ./Core/Src/SSD1306_OLED.d ./Core/Src/SSD1306_OLED.o ./Core/Src/SSD1306_OLED.su ./Core/Src/Servo.cyclo ./Core/Src/Servo.d ./Core/Src/Servo.o ./Core/Src/Servo.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

