################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SL/Tmu.c \
../SL/Tmu_Lcfg.c 

OBJS += \
./SL/Tmu.o \
./SL/Tmu_Lcfg.o 

C_DEPS += \
./SL/Tmu.d \
./SL/Tmu_Lcfg.d 


# Each subdirectory must supply rules for building sources it contributes
SL/%.o: ../SL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

