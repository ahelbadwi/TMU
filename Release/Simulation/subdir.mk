################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Simulation/App.c \
../Simulation/DIO.c \
../Simulation/Timer.c \
../Simulation/Tmu.c \
../Simulation/Tmu_Lcfg.c \
../Simulation/main.c 

OBJS += \
./Simulation/App.o \
./Simulation/DIO.o \
./Simulation/Timer.o \
./Simulation/Tmu.o \
./Simulation/Tmu_Lcfg.o \
./Simulation/main.o 

C_DEPS += \
./Simulation/App.d \
./Simulation/DIO.d \
./Simulation/Timer.d \
./Simulation/Tmu.d \
./Simulation/Tmu_Lcfg.d \
./Simulation/main.d 


# Each subdirectory must supply rules for building sources it contributes
Simulation/%.o: ../Simulation/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


