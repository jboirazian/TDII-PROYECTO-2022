################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/displayModule/api_ili9341.c \
../Core/Src/displayModule/displayModuleTasks.c \
../Core/Src/displayModule/drv_ili9341.c 

OBJS += \
./Core/Src/displayModule/api_ili9341.o \
./Core/Src/displayModule/displayModuleTasks.o \
./Core/Src/displayModule/drv_ili9341.o 

C_DEPS += \
./Core/Src/displayModule/api_ili9341.d \
./Core/Src/displayModule/displayModuleTasks.d \
./Core/Src/displayModule/drv_ili9341.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/displayModule/%.o: ../Core/Src/displayModule/%.c Core/Src/displayModule/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I"C:/Users/Administrator/STM32CubeIDE/workspace_1.6.1/rfid/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

