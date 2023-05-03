/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v12.0
processor: MIMXRT1064xxxxA
package_id: MIMXRT1064DVL6A
mcu_data: ksdk2_0
processor_version: 13.0.2
board: MIMXRT1064-EVK
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: 9c26c193-63df-444a-9eeb-45c3b55218bf
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system_54b53072540eeeb8f8e9343e71f28176'
- global_system_definitions:
  - user_definitions: ''
  - user_includes: ''
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'uart_cmsis_common'
- type_id: 'uart_cmsis_common_9cb8e302497aa696fdbb5a4fd622c2a8'
- global_USART_CMSIS_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'gpio_adapter_common'
- type_id: 'gpio_adapter_common_57579b9ac814fe26bf95df0a384c36b6'
- global_gpio_adapter_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * DMA0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'DMA0'
- type: 'edma'
- mode: 'basic'
- custom_name_enabled: 'false'
- type_id: 'edma_46976c94302ab714c0d335f519487c8a'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'DMA0'
- config_sets:
  - fsl_edma:
    - common_settings:
      - enableMinorLoopMapping: 'true'
      - enableContinuousLinkMode: 'true'
      - enableHaltOnError: 'true'
      - ERCA: 'fixedPriority'
      - enableDebugMode: 'false'
    - dma_table:
      - 0: []
    - edma_channels: []
    - errInterruptConfig:
      - enableErrInterrupt: 'false'
      - errorInterrupt:
        - IRQn: 'DMA_ERROR_IRQn'
        - enable_interrrupt: 'enabled'
        - enable_priority: 'false'
        - priority: '0'
        - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const edma_config_t DMA0_config = {
  .enableContinuousLinkMode = true,
  .enableHaltOnError = true,
  .enableRoundRobinArbitration = false,
  .enableDebugMode = false
};

static void DMA0_init(void) {
  /* DMA0 minor loop mapping */
  EDMA_EnableMinorLoopMapping(DMA0_DMA_BASEADDR, true);
}

/***********************************************************************************************************************
 * NVIC initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'NVIC'
- type: 'nvic'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'nvic_57b5eef3774cc60acaede6f5b8bddc67'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'NVIC'
- config_sets:
  - nvic:
    - interrupt_table:
      - 0: []
    - interrupts:
      - 0:
        - channelId: 'int_0'
        - interrupt_t:
          - IRQn: 'DMA0_DMA16_IRQn'
          - enable_interrrupt: 'enabled'
          - enable_priority: 'true'
          - priority: '4'
          - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void NVIC_init(void) {
} */

/***********************************************************************************************************************
 * SAI1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'SAI1'
- type: 'sai'
- mode: 'edma'
- custom_name_enabled: 'false'
- type_id: 'sai_d277a9f96e6a702cd0cbe3311dc8aff9'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'SAI1'
- config_sets:
  - fsl_sai:
    - usage: 'playback'
    - signal_config:
      - 0:
        - sourceTx: 'Tx'
      - 1:
        - sourceTx: 'Tx'
    - syncSwapI: []
    - bclkTxSetting: []
    - syncTxSetting: []
    - whole:
      - tx_group:
        - sai_transceiver:
          - bitClock:
            - modeM: 'master'
            - bitClockSource: 'kSAI_BclkSourceBusclk'
            - bitClockSourceFreq: 'ClocksTool_DefaultInit'
            - bclkPolarityM: 'kSAI_PolarityActiveLow'
            - bclkInputDelayM: 'false'
          - frameSync:
            - modeM: 'master'
            - frameSyncWidthM: '16'
            - frameSyncPolarityM: 'kSAI_PolarityActiveLow'
            - frameSyncEarlyM: 'true'
            - frameSyncGenerateOnDemandM: 'false'
          - sampleRate_Hz: 'kSAI_SampleRate48KHz'
          - channelMask: 'kSAI_Channel0Mask'
          - serialData:
            - dataMode: 'kSAI_DataPinStateTriState'
            - differentFirstWord: 'false'
            - sameDataWordLengthM: 'kSAI_WordWidth16bits'
            - dataOrder: 'kSAI_DataMSB'
            - dataFirstBitShiftedM: '16'
            - dataWordNumM: '2'
            - dataMasked_config:
              - dataMasked_L:
                - 0: 'false'
                - 1: 'false'
                - 2: 'false'
                - 3: 'false'
                - 4: 'false'
                - 5: 'false'
                - 6: 'false'
                - 7: 'false'
                - 8: 'false'
                - 9: 'false'
                - 10: 'false'
                - 11: 'false'
                - 12: 'false'
                - 13: 'false'
                - 14: 'false'
                - 15: 'false'
              - dataMasked_H:
                - 0: 'false'
                - 1: 'false'
                - 2: 'false'
                - 3: 'false'
                - 4: 'false'
                - 5: 'false'
                - 6: 'false'
                - 7: 'false'
                - 8: 'false'
                - 9: 'false'
                - 10: 'false'
                - 11: 'false'
                - 12: 'false'
                - 13: 'false'
                - 14: 'false'
                - 15: 'false'
          - fifo:
            - fifoWatermarkM: '16'
            - fifoCombine: 'kSAI_FifoCombineDisabled'
            - fifoPacking: 'kSAI_FifoPackingDisabled'
            - fifoContinueOneError: 'false'
        - edma_group:
          - enable_edma_channel: 'true'
          - edma_channel:
            - uid: '1681340540130'
            - eDMAn: '0'
            - eDMA_source: 'kDmaRequestMuxSai1Tx'
            - enableTriggerPIT: 'false'
            - init_channel_priority: 'false'
            - edma_channel_Preemption:
              - enableChannelPreemption: 'false'
              - enablePreemptAbility: 'false'
              - channelPriority: '0'
            - enable_custom_name: 'false'
          - sai_edma_handle:
            - enable_custom_name: 'false'
            - placement:
              - section: 'cacheable'
              - zeroInitialize: 'false'
              - align: '32'
            - init_callback: 'false'
            - callback_fcn: ''
            - user_data: ''
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
/* SAI1 Tx configuration */
sai_transceiver_t SAI1_Tx_config = {
  .masterSlave = kSAI_Master,
  .bitClock = {
    .bclkSrcSwap = false,
    .bclkSource = kSAI_BclkSourceBusclk,
    .bclkPolarity = kSAI_PolarityActiveLow,
    .bclkInputDelay = false
  },
  .frameSync = {
    .frameSyncWidth = 16U,
    .frameSyncPolarity = kSAI_PolarityActiveLow,
    .frameSyncEarly = true,
    .frameSyncGenerateOnDemand = false
  },
  .syncMode = kSAI_ModeAsync,
  .channelMask = kSAI_Channel0Mask,
  .startChannel = 0U,
  .endChannel = 0U,
  .channelNums = 1U,
  .serialData = {
    .dataMode = kSAI_DataPinStateTriState,
    .dataWord0Length = (uint8_t)kSAI_WordWidth16bits,
    .dataWordNLength = (uint8_t)kSAI_WordWidth16bits,
    .dataWordLength = (uint8_t)kSAI_WordWidth16bits,
    .dataOrder = kSAI_DataMSB,
    .dataFirstBitShifted = 16U,
    .dataWordNum = 2U,
    .dataMaskedWord = 0x0U
  },
  .fifo = {
    .fifoWatermark = 16U,
    .fifoCombine = kSAI_FifoCombineDisabled,
    .fifoPacking = kSAI_FifoPackingDisabled,
    .fifoContinueOneError = false
  }
};
edma_handle_t SAI1_TX_Handle;
sai_edma_handle_t SAI1_SAI_Tx_eDMA_Handle;

static void SAI1_init(void) {
  /* Set the source kDmaRequestMuxSai1Tx request in the DMAMUX */
  DMAMUX_SetSource(SAI1_TX_DMAMUX_BASEADDR, SAI1_TX_DMA_CHANNEL, SAI1_TX_DMA_REQUEST);
  /* Enable the channel 0 in the DMAMUX */
  DMAMUX_EnableChannel(SAI1_TX_DMAMUX_BASEADDR, SAI1_TX_DMA_CHANNEL);
  /* Create the eDMA SAI1_TX_Handle handle */
  EDMA_CreateHandle(&SAI1_TX_Handle, SAI1_TX_DMA_BASEADDR, SAI1_TX_DMA_CHANNEL);
  /* Initialize SAI clock gate */
  SAI_Init(SAI1_PERIPHERAL);
  /* Create the SAI Tx eDMA handle */
  SAI_TransferTxCreateHandleEDMA(SAI1_PERIPHERAL, &SAI1_SAI_Tx_eDMA_Handle, NULL, NULL, &SAI1_TX_Handle);
  /* Configures SAI Tx sub-module functionality */
  SAI_TransferTxSetConfigEDMA(SAI1_PERIPHERAL, &SAI1_SAI_Tx_eDMA_Handle, &SAI1_Tx_config);
  /* Set up SAI Tx bitclock rate by calculation of divider. */
  SAI_TxSetBitClockRate(SAI1_PERIPHERAL, SAI1_TX_BCLK_SOURCE_CLOCK_HZ, SAI1_TX_SAMPLE_RATE, SAI1_TX_WORD_WIDTH, SAI1_TX_WORDS_PER_FRAME);
}

/***********************************************************************************************************************
 * SEMC initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'SEMC'
- type: 'semc'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'semc_84a769c198c91c527e11dcec2f5b4b81'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'SEMC'
- config_sets:
  - fsl_semc:
    - enableDCD: 'true'
    - clockConfig:
      - clockSource: 'kSEMC_ClkSrcPeri'
      - clockSourceFreq: 'ClocksTool_DefaultInit'
    - semc_config_t:
      - dqsMode: 'kSEMC_Loopbackdqspad'
      - cmdTimeoutCycles: '0'
      - busTimeoutCycles: '0'
      - queueWeight:
        - queueaEnable: 'false'
        - queueaWeight:
          - structORvalue: 'structure'
          - queueaConfig:
            - qos: '0'
            - aging: '0'
            - slaveHitSwith: '0'
            - slaveHitNoswitch: '0'
        - queuebEnable: 'false'
        - queuebWeight:
          - structORvalue: 'structure'
          - queuebConfig:
            - qos: '0'
            - aging: '0'
            - slaveHitSwith: '0'
            - weightPagehit: '0'
            - bankRotation: '0'
    - semc_sdram_config_t:
      - csxPinMux: 'kSEMC_MUXCSX0'
      - semcSdramCs: 'kSEMC_SDRAM_CS0'
      - address: '0x80000000'
      - memsize_input: '32MB'
      - portSize: 'kSEMC_PortSize16Bit'
      - burstLen: 'kSEMC_Sdram_BurstLen1'
      - columnAddrBitNum: 'kSEMC_SdramColunm_9bit'
      - casLatency: 'kSEMC_LatencyThree'
      - tPrecharge2Act_Ns: '18'
      - tAct2ReadWrite_Ns: '18'
      - tRefreshRecovery_Ns: '127'
      - tWriteRecovery_Ns: '12'
      - tCkeOff_Ns: '42'
      - tAct2Prechage_Ns: '42'
      - tSelfRefRecovery_Ns: '67'
      - tRefresh2Refresh_Ns: '60'
      - tAct2Act_Ns: '60'
      - tPrescalePeriod_Ns: '160'
      - tIdleTimeout_Ns: '0'
      - refreshPeriod_nsPerRow: '64'
      - refreshUrgThreshold: '64'
      - refreshBurstLen: '1'
    - sdramArray: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void SEMC_init(void) {
} */

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
static void BOARD_InitPeripherals_CommonPostInit(void)
{
  /* Interrupt vector DMA0_DMA16_IRQn priority settings in the NVIC. */
  NVIC_SetPriority(INT_0_IRQN, INT_0_IRQ_PRIORITY);
  /* Enable interrupt DMA0_DMA16_IRQn request in the NVIC. */
  EnableIRQ(INT_0_IRQN);
}

void BOARD_InitPeripherals(void)
{
  /* Global initialization */
  DMAMUX_Init(DMA0_DMAMUX_BASEADDR);
  EDMA_Init(DMA0_DMA_BASEADDR, &DMA0_config);

  /* Initialize components */
  DMA0_init();
  SAI1_init();
  /* Common post-initialization */
  BOARD_InitPeripherals_CommonPostInit();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
