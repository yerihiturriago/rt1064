################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sdmmc/template/usdhc/sdmmc_config.c 

C_DEPS += \
./sdmmc/template/usdhc/sdmmc_config.d 

OBJS += \
./sdmmc/template/usdhc/sdmmc_config.o 


# Each subdirectory must supply rules for building sources it contributes
sdmmc/template/usdhc/%.o: ../sdmmc/template/usdhc/%.c sdmmc/template/usdhc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MIMXRT1064DVL6A -DSD_ENABLED -DCPU_MIMXRT1064DVL6A_cm7 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DPRINTF_FLOAT_ENABLE=1 -DSDK_DEBUGCONSOLE_UART -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\freertos\freertos_kernel\include" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\drivers" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\device" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\CMSIS" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\component\serial_manager" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\component\uart" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\utilities" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\fatfs\source\fsl_sd_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\fatfs\source" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\fatfs\source\fsl_ram_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\component\lists" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\board" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\source" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\component\osa" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\sdmmc\inc" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\sdmmc\host" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\sdmmc\osa" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\sdmmc\template\usdhc" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\freertos\freertos_kernel\include" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\drivers" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\device" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\CMSIS" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\component\serial_manager" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\component\uart" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\utilities" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\fatfs\source\fsl_sd_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\fatfs\source" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\fatfs\source\fsl_ram_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\component\lists" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\board" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\source" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_SD\component\osa" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-sdmmc-2f-template-2f-usdhc

clean-sdmmc-2f-template-2f-usdhc:
	-$(RM) ./sdmmc/template/usdhc/sdmmc_config.d ./sdmmc/template/usdhc/sdmmc_config.o

.PHONY: clean-sdmmc-2f-template-2f-usdhc

