/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v12.0
processor: MIMXRT1064xxxxA
package_id: MIMXRT1064DVL6A
mcu_data: ksdk2_0
processor_version: 12.0.1
pin_labels:
- {pin_num: F14, pin_signal: GPIO_AD_B0_09, label: LED_F14, identifier: LED_F14}
- {pin_num: P2, pin_signal: GPIO_SD_B1_04, label: SD_CD, identifier: SD_CD}
- {pin_num: K10, pin_signal: GPIO_AD_B1_07, label: SD_PWREN, identifier: SD_PWREN}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 * 
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 * 
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void) {
    BOARD_InitPins();
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: J4, peripheral: USDHC1, signal: usdhc_cmd, pin_signal: GPIO_SD_B0_00, slew_rate: Fast}
  - {pin_num: J3, peripheral: USDHC1, signal: usdhc_clk, pin_signal: GPIO_SD_B0_01, slew_rate: Fast}
  - {pin_num: J1, peripheral: USDHC1, signal: 'usdhc_data, 0', pin_signal: GPIO_SD_B0_02, slew_rate: Fast}
  - {pin_num: K1, peripheral: USDHC1, signal: 'usdhc_data, 1', pin_signal: GPIO_SD_B0_03, slew_rate: Fast}
  - {pin_num: H2, peripheral: USDHC1, signal: 'usdhc_data, 2', pin_signal: GPIO_SD_B0_04, slew_rate: Fast}
  - {pin_num: J2, peripheral: USDHC1, signal: 'usdhc_data, 3', pin_signal: GPIO_SD_B0_05, slew_rate: Fast}
  - {pin_num: F14, peripheral: GPIO6, signal: 'gpio_io, 09', pin_signal: GPIO_AD_B0_09, direction: OUTPUT}
  - {pin_num: L14, peripheral: LPUART1, signal: RX, pin_signal: GPIO_AD_B0_13}
  - {pin_num: K14, peripheral: LPUART1, signal: TX, pin_signal: GPIO_AD_B0_12}
  - {pin_num: P2, peripheral: GPIO3, signal: 'gpio_io, 04', pin_signal: GPIO_SD_B1_04, direction: OUTPUT}
  - {pin_num: K10, peripheral: GPIO1, signal: 'gpio_io, 23', pin_signal: GPIO_AD_B1_07, direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           

  /* GPIO configuration of SD_PWREN on GPIO_AD_B1_07 (pin K10) */
  gpio_pin_config_t SD_PWREN_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_AD_B1_07 (pin K10) */
  GPIO_PinInit(GPIO1, 23U, &SD_PWREN_config);

  /* GPIO configuration of SD_CD on GPIO_SD_B1_04 (pin P2) */
  gpio_pin_config_t SD_CD_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_SD_B1_04 (pin P2) */
  GPIO_PinInit(GPIO3, 4U, &SD_CD_config);

  /* GPIO configuration of LED_F14 on GPIO_AD_B0_09 (pin F14) */
  gpio_pin_config_t LED_F14_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_AD_B0_09 (pin F14) */
  GPIO_PinInit(GPIO6, 9U, &LED_F14_config);

  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_GPIO1_IO09, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_LPUART1_TX, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_LPUART1_RX, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_GPIO1_IO23, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_00_USDHC1_CMD, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_01_USDHC1_CLK, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_02_USDHC1_DATA0, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_03_USDHC1_DATA1, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_04_USDHC1_DATA2, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_05_USDHC1_DATA3, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_GPIO3_IO04, 0U); 
  IOMUXC_GPR->GPR26 = ((IOMUXC_GPR->GPR26 &
    (~(BOARD_INITPINS_IOMUXC_GPR_GPR26_GPIO_MUX1_GPIO_SEL_MASK))) 
      | IOMUXC_GPR_GPR26_GPIO_MUX1_GPIO_SEL(0x0200U) 
    );
  IOMUXC_GPR->GPR28 = ((IOMUXC_GPR->GPR28 &
    (~(BOARD_INITPINS_IOMUXC_GPR_GPR28_GPIO_MUX3_GPIO_SEL_MASK))) 
      | IOMUXC_GPR_GPR28_GPIO_MUX3_GPIO_SEL(0x00U) 
    );
  IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_00_USDHC1_CMD, 0x10B1U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_01_USDHC1_CLK, 0x10B1U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_02_USDHC1_DATA0, 0x10B1U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_03_USDHC1_DATA1, 0x10B1U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_04_USDHC1_DATA2, 0x10B1U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_05_USDHC1_DATA3, 0x10B1U); 
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
