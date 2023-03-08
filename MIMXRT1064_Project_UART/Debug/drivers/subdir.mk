################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_cache.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_semc.c \
../drivers/fsl_usdhc.c 

C_DEPS += \
./drivers/fsl_cache.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_semc.d \
./drivers/fsl_usdhc.d 

OBJS += \
./drivers/fsl_cache.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_semc.o \
./drivers/fsl_usdhc.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MIMXRT1064DVL6A -DCPU_MIMXRT1064DVL6A_cm7 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DPRINTF_FLOAT_ENABLE=1 -DSDK_DEBUGCONSOLE_UART -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\freertos\freertos_kernel\include" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\drivers" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\device" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\CMSIS" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\component\serial_manager" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\component\uart" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\utilities" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\component\lists" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\board" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\source" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\fatfs\source" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\fatfs\source\fsl_mmc_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\fatfs\source\fsl_nand_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\fatfs\source\fsl_sd_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\fatfs\source\fsl_usb_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\usb\host" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\usb\include" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\sdmmc\inc" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\usb\phy" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\usb\host\class" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\sdmmc\host" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\sdmmc\osa" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\fatfs\source\fsl_ram_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\nand_flash" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\component\osa" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\sdmmc\template\usdhc" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\source\generated" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\freertos\freertos_kernel\include" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\drivers" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\device" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\CMSIS" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\component\serial_manager" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\component\uart" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\utilities" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\component\lists" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\board" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\source" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\fatfs\source" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\fatfs\source\fsl_mmc_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\fatfs\source\fsl_nand_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\fatfs\source\fsl_sd_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\fatfs\source\fsl_usb_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\usb\host" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\usb\include" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\sdmmc\inc" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\usb\phy" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\usb\host\class" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\sdmmc\host" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\sdmmc\osa" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\fatfs\source\fsl_ram_disk" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\nand_flash" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\component\osa" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\sdmmc\template\usdhc" -I"D:\Personal projects\Drum project\Desarrollo\RT1064\code\MIMXRT1064_Project_UART\source\generated" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_cache.d ./drivers/fsl_cache.o ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o ./drivers/fsl_semc.d ./drivers/fsl_semc.o ./drivers/fsl_usdhc.d ./drivers/fsl_usdhc.o

.PHONY: clean-drivers

