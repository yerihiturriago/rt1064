################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include usb/phy/subdir.mk
-include usb/host/class/subdir.mk
-include usb/host/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include sdmmc/template/usdhc/subdir.mk
-include sdmmc/src/subdir.mk
-include sdmmc/osa/subdir.mk
-include sdmmc/host/subdir.mk
-include nand_flash/subdir.mk
-include freertos/freertos_kernel/portable/MemMang/subdir.mk
-include freertos/freertos_kernel/portable/GCC/ARM_CM4F/subdir.mk
-include freertos/freertos_kernel/subdir.mk
-include fatfs/source/fsl_usb_disk/subdir.mk
-include fatfs/source/fsl_sd_disk/subdir.mk
-include fatfs/source/fsl_ram_disk/subdir.mk
-include fatfs/source/fsl_nand_disk/subdir.mk
-include fatfs/source/fsl_mmc_disk/subdir.mk
-include fatfs/source/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/subdir.mk
-include component/osa/subdir.mk
-include component/lists/subdir.mk
-include board/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := MIMXRT1064_Project_UART
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: MIMXRT1064_Project_UART.axf

# Tool invocations
MIMXRT1064_Project_UART.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="MIMXRT1064_Project_UART.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -T MIMXRT1064_Project_UART_Debug.ld -o "MIMXRT1064_Project_UART.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) MIMXRT1064_Project_UART.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "MIMXRT1064_Project_UART.axf"; # arm-none-eabi-objcopy -v -O binary "MIMXRT1064_Project_UART.axf" "MIMXRT1064_Project_UART.bin" ; # checksum -p MIMXRT1064xxxxA -d "MIMXRT1064_Project_UART.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
