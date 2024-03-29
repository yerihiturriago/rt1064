################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/osa/fsl_os_abstraction_free_rtos.c 

C_DEPS += \
./component/osa/fsl_os_abstraction_free_rtos.d 

OBJS += \
./component/osa/fsl_os_abstraction_free_rtos.o 


# Each subdirectory must supply rules for building sources it contributes
component/osa/%.o: ../component/osa/%.c component/osa/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MIMXRT1064DVL6A -DCPU_MIMXRT1064DVL6A_cm7 -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DXIP_BOOT_HEADER_DCD_ENABLE=1 -DFSL_SDK_ENABLE_DRIVER_CACHE_CONTROL=1 -DDEBUG_CONSOLE_TRANSFER_NON_BLOCKING -DSD_ENABLED -DSERIAL_PORT_TYPE_UART=1 -DSDK_OS_FREE_RTOS -DMCUXPRESSO_SDK -DPRINTF_FLOAT_ENABLE=1 -DSDK_DEBUGCONSOLE_UART -DCR_PRINTF_CHAR -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\fatfs\source\fsl_ram_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\drivers" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\sdmmc\inc" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\sdmmc\host" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\gpio" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\fatfs\source" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\fatfs\source\fsl_sd_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\device" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\utilities" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\uart" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\serial_manager" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\lists" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\xip" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\CMSIS" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\sdmmc\osa" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\osa" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\freertos\freertos-kernel\include" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\freertos\freertos-kernel\portable\GCC\ARM_CM4F" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\source" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\sdmmc\template\usdhc" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\fatfs\source\fsl_ram_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\drivers" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\sdmmc\inc" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\sdmmc\host" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\gpio" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\fatfs\source" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\fatfs\source\fsl_sd_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\device" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\utilities" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\uart" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\serial_manager" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\lists" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\xip" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\CMSIS" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\sdmmc\osa" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\osa" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\freertos\freertos-kernel\include" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\freertos\freertos-kernel\portable\GCC\ARM_CM4F" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\source" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\sdmmc\template\usdhc" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\board" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\evkmimxrt1064\sdmmc_examples\sdcard_fatfs_freertos" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-osa

clean-component-2f-osa:
	-$(RM) ./component/osa/fsl_os_abstraction_free_rtos.d ./component/osa/fsl_os_abstraction_free_rtos.o

.PHONY: clean-component-2f-osa

