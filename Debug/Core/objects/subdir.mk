################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/objects/input.cpp \
../Core/objects/screen.cpp 

OBJS += \
./Core/objects/input.o \
./Core/objects/screen.o 

CPP_DEPS += \
./Core/objects/input.d \
./Core/objects/screen.d 


# Each subdirectory must supply rules for building sources it contributes
Core/objects/%.o Core/objects/%.su Core/objects/%.cyclo: ../Core/objects/%.cpp Core/objects/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/jarom/OneDrive/Desktop/Fall_2023/ECEN260/STM/Final_OOP/Core/objects" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-objects

clean-Core-2f-objects:
	-$(RM) ./Core/objects/input.cyclo ./Core/objects/input.d ./Core/objects/input.o ./Core/objects/input.su ./Core/objects/screen.cyclo ./Core/objects/screen.d ./Core/objects/screen.o ./Core/objects/screen.su

.PHONY: clean-Core-2f-objects

