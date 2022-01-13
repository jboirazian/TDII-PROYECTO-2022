################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/sdModule/fatfs_sd.c \
../Core/Src/sdModule/sdModule.c \
../Core/Src/sdModule/sdModuleTasks.c 

OBJS += \
./Core/Src/sdModule/fatfs_sd.o \
./Core/Src/sdModule/sdModule.o \
./Core/Src/sdModule/sdModuleTasks.o 

C_DEPS += \
./Core/Src/sdModule/fatfs_sd.d \
./Core/Src/sdModule/sdModule.d \
./Core/Src/sdModule/sdModuleTasks.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/sdModule/%.o: ../Core/Src/sdModule/%.c Core/Src/sdModule/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I"C:/Users/Administrator/STM32CubeIDE/workspace_1.6.1/rfid/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

