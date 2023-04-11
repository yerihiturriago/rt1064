################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sdmmc/osa/fsl_sdmmc_osa.c 

C_DEPS += \
./sdmmc/osa/fsl_sdmmc_osa.d 

OBJS += \
./sdmmc/osa/fsl_sdmmc_osa.o 


# Each subdirectory must supply rules for building sources it contributes
sdmmc/osa/%.o: ../sdmmc/osa/%.c sdmmc/osa/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DFSL_OSA_TASK_ENABLE=1 -DCPU_MIMXRT1064DVL6A -DSDK_DEBUGCONSOLE=0 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DXIP_BOOT_HEADER_DCD_ENABLE=1 -DFSL_SDK_ENABLE_DRIVER_CACHE_CONTROL=1 -DDEBUG_CONSOLE_TRANSFER_NON_BLOCKING -DSD_ENABLED -DSERIAL_PORT_TYPE_UART=1 -DSDK_OS_FREE_RTOS -DMCUXPRESSO_SDK -DCPU_MIMXRT1064DVL6A_cm7 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\drivers" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\sdmmc\inc" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\sdmmc\host" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\gpio" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\fatfs\source" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\fatfs\source\fsl_sd_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\device" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\utilities" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\uart" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\serial_manager" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\lists" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\xip" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\silicon_id" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\CMSIS" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\sdmmc\osa" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\osa" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\freertos\freertos_kernel\include" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\board" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\source" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\sdmmc\template\usdhc" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\fatfs\source\fsl_ram_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\drivers" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\sdmmc\inc" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\sdmmc\host" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\gpio" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\fatfs\source" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\fatfs\source\fsl_sd_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\device" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\utilities" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\uart" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\serial_manager" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\lists" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\xip" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\silicon_id" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\CMSIS" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\sdmmc\osa" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\component\osa" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\freertos\freertos_kernel\include" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\board" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\source" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\sdmmc\template\usdhc" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\fatfs\source\fsl_ram_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\sdcard_fatfs_freertos\evkmimxrt1064\sdmmc_examples\sdcard_fatfs_freertos" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-sdmmc-2f-osa

clean-sdmmc-2f-osa:
	-$(RM) ./sdmmc/osa/fsl_sdmmc_osa.d ./sdmmc/osa/fsl_sdmmc_osa.o

.PHONY: clean-sdmmc-2f-osa

