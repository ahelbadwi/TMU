################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Simulation/subdir.mk
-include SL/subdir.mk
-include McAl/subdir.mk
-include App/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Tmu.lss \

FLASH_IMAGE += \
Tmu.hex \

EEPROM_IMAGE += \
Tmu.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Tmu.elf secondary-outputs

# Tool invocations
Tmu.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Tmu.map -mmcu=atmega16 -o "Tmu.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Tmu.lss: Tmu.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Tmu.elf  >"Tmu.lss"
	@echo 'Finished building: $@'
	@echo ' '

Tmu.hex: Tmu.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Tmu.elf  "Tmu.hex"
	@echo 'Finished building: $@'
	@echo ' '

Tmu.eep: Tmu.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Tmu.elf  "Tmu.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Tmu.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 Tmu.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Tmu.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
