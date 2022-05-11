/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v9.0
processor: MKL46Z256xxx4
package_id: MKL46Z256VLL4
mcu_data: ksdk2_0
processor_version: 9.0.0
board: FRDM-KL46Z
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: 962c729f-7c4f-4d37-a8b4-b95fd526fa87
  called_from_default_init: true
  selectedCore: core0
- name: BOARD_InitButtonsPeripheral
  UUID: 5b9c9fa2-e424-421a-8f1c-15658683fded
  id_prefix: BOARD_
  selectedCore: core0
- name: BOARD_InitLEDsPeripheral
  UUID: 660184d9-5686-4c66-8dfe-4b27b768582f
  id_prefix: BOARD_
  selectedCore: core0
- name: BOARD_InitACCELPeripheral
  UUID: 9f60ba85-b3b8-4e3a-8424-ab6c840e2f42
  id_prefix: BOARD_
  selectedCore: core0
- name: BOARD_InitMAGPeripheral
  UUID: 41e66dcb-7603-4a22-aa22-aefb05d7c7d6
  selectedCore: core0
- name: BOARD_InitDEBUG_UARTPeripheral
  UUID: 13c960f5-1285-4e05-81b8-d64ad4bc8b29
  id_prefix: BOARD_
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system'
- global_system_definitions:
  - user_definitions: ''
  - user_includes: ''
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
    - interrupt_table: []
    - interrupts: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void NVIC_init(void) {
} */

/***********************************************************************************************************************
 * BOARD_InitButtonsPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * SW1_SW3 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'SW1_SW3'
- type: 'gpio'
- mode: 'GPIO'
- custom_name_enabled: 'true'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitButtonsPeripheral'
- peripheral: 'GPIOC'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTC_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

static void BOARD_SW1_SW3_init(void) {
  /* Make sure, the clock gate for port C is enabled (e. g. in pin_mux.c) */
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
- functional_group: 'BOARD_InitButtonsPeripheral'
- peripheral: 'NVIC'
- config_sets:
  - nvic:
    - interrupt_table: []
    - interrupts: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void BOARD_NVIC_init(void) {
} */

/***********************************************************************************************************************
 * BOARD_InitLEDsPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * LED_RED initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LED_RED'
- type: 'gpio'
- mode: 'GPIO'
- custom_name_enabled: 'true'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitLEDsPeripheral'
- peripheral: 'GPIOE'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTE_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

static void BOARD_LED_RED_init(void) {
  /* Make sure, the clock gate for port E is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * LED_GREEN initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LED_GREEN'
- type: 'gpio'
- mode: 'GPIO'
- custom_name_enabled: 'true'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitLEDsPeripheral'
- peripheral: 'GPIOD'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTD_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

static void BOARD_LED_GREEN_init(void) {
  /* Make sure, the clock gate for port D is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * NVIC_2 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'NVIC_2'
- type: 'nvic'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'nvic_57b5eef3774cc60acaede6f5b8bddc67'
- functional_group: 'BOARD_InitLEDsPeripheral'
- peripheral: 'NVIC'
- config_sets:
  - nvic:
    - interrupt_table: []
    - interrupts: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void BOARD_NVIC_2_init(void) {
} */

/***********************************************************************************************************************
 * BOARD_InitACCELPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * ACCEL_I2C initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'ACCEL_I2C'
- type: 'i2c'
- mode: 'I2C_Polling'
- custom_name_enabled: 'true'
- type_id: 'i2c_2566d7363e7e9aaedabb432110e372d7'
- functional_group: 'BOARD_InitACCELPeripheral'
- peripheral: 'I2C0'
- config_sets:
  - fsl_i2c:
    - i2c_mode: 'kI2C_Master'
    - clockSource: 'BusInterfaceClock'
    - clockSourceFreq: 'GetFreq'
    - i2c_master_config:
      - enableMaster: 'true'
      - enableStopHold: 'false'
      - baudRate_Bps: '100000'
      - glitchFilterWidth: '0'
    - quick_selection: 'QS_I2C_1'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const i2c_master_config_t BOARD_ACCEL_I2C_config = {
  .enableMaster = true,
  .enableStopHold = false,
  .baudRate_Bps = 100000UL,
  .glitchFilterWidth = 0U
};

static void BOARD_ACCEL_I2C_init(void) {
  /* Initialization function */
  I2C_MasterInit(BOARD_ACCEL_I2C_PERIPHERAL, &BOARD_ACCEL_I2C_config, BOARD_ACCEL_I2C_CLK_FREQ);
}

/***********************************************************************************************************************
 * INT1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'INT1'
- type: 'gpio'
- mode: 'GPIO'
- custom_name_enabled: 'true'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitACCELPeripheral'
- peripheral: 'GPIOC'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTC_PORTD_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

static void BOARD_INT1_init(void) {
  /* Make sure, the clock gate for port C is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * INT2 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'INT2'
- type: 'gpio'
- mode: 'GPIO'
- custom_name_enabled: 'true'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitACCELPeripheral'
- peripheral: 'GPIOD'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTC_PORTD_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

static void BOARD_INT2_init(void) {
  /* Make sure, the clock gate for port D is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * NVIC_3 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'NVIC_3'
- type: 'nvic'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'nvic_57b5eef3774cc60acaede6f5b8bddc67'
- functional_group: 'BOARD_InitACCELPeripheral'
- peripheral: 'NVIC'
- config_sets:
  - nvic:
    - interrupt_table: []
    - interrupts: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void BOARD_NVIC_3_init(void) {
} */

/***********************************************************************************************************************
 * BOARD_InitMAGPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * MAG_I2C initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'MAG_I2C'
- type: 'i2c'
- mode: 'I2C_Polling'
- custom_name_enabled: 'true'
- type_id: 'i2c_2566d7363e7e9aaedabb432110e372d7'
- functional_group: 'BOARD_InitMAGPeripheral'
- peripheral: 'I2C0'
- config_sets:
  - fsl_i2c:
    - i2c_mode: 'kI2C_Master'
    - clockSource: 'BusInterfaceClock'
    - clockSourceFreq: 'GetFreq'
    - i2c_master_config:
      - enableMaster: 'true'
      - enableStopHold: 'false'
      - baudRate_Bps: '100000'
      - glitchFilterWidth: '0'
    - quick_selection: 'QS_I2C_1'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const i2c_master_config_t MAG_I2C_config = {
  .enableMaster = true,
  .enableStopHold = false,
  .baudRate_Bps = 100000UL,
  .glitchFilterWidth = 0U
};

static void MAG_I2C_init(void) {
  /* Initialization function */
  I2C_MasterInit(MAG_I2C_PERIPHERAL, &MAG_I2C_config, MAG_I2C_CLK_FREQ);
}

/***********************************************************************************************************************
 * INT2 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'INT2'
- type: 'gpio'
- mode: 'GPIO'
- custom_name_enabled: 'true'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitMAGPeripheral'
- peripheral: 'GPIOD'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTC_PORTD_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

static void INT2_init(void) {
  /* Make sure, the clock gate for port D is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * NVIC_2 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'NVIC_2'
- type: 'nvic'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'nvic_57b5eef3774cc60acaede6f5b8bddc67'
- functional_group: 'BOARD_InitMAGPeripheral'
- peripheral: 'NVIC'
- config_sets:
  - nvic:
    - interrupt_table: []
    - interrupts: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void NVIC_2_init(void) {
} */

/***********************************************************************************************************************
 * BOARD_InitDEBUG_UARTPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * LPSCI_1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LPSCI_1'
- type: 'lpsci'
- mode: 'polling'
- custom_name_enabled: 'true'
- type_id: 'lpsci_d7d643c7d665ff9a7a181303138bb697'
- functional_group: 'BOARD_InitDEBUG_UARTPeripheral'
- peripheral: 'UART0'
- config_sets:
  - lpsciConfig_t:
    - lpsciConfig:
      - clockSource: 'UartClock'
      - lpsciSrcClkFreq: 'BOARD_BootClockRUN'
      - baudRate_Bps: '115200'
      - parityMode: 'kLPSCI_ParityDisabled'
      - stopBitCount: 'kLPSCI_OneStopBit'
      - idleLineType: 'kLPSCI_IdleLineStartBit'
      - enableTx: 'false'
      - enableRx: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

static void BOARD_LPSCI_1_init(void) {
  /* Configuration of the component LPSCI_1 of functional group BOARD_InitDEBUG_UARTPeripheral is not valid. */
}

/***********************************************************************************************************************
 * NVIC_4 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'NVIC_4'
- type: 'nvic'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'nvic_57b5eef3774cc60acaede6f5b8bddc67'
- functional_group: 'BOARD_InitDEBUG_UARTPeripheral'
- peripheral: 'NVIC'
- config_sets:
  - nvic:
    - interrupt_table: []
    - interrupts: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void BOARD_NVIC_4_init(void) {
} */

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Initialize components */
}

void BOARD_InitButtonsPeripheral(void)
{
  /* Initialize components */
  BOARD_SW1_SW3_init();
}

void BOARD_InitLEDsPeripheral(void)
{
  /* Initialize components */
  BOARD_LED_RED_init();
  BOARD_LED_GREEN_init();
}

void BOARD_InitACCELPeripheral(void)
{
  /* Initialize components */
  BOARD_ACCEL_I2C_init();
  BOARD_INT1_init();
  BOARD_INT2_init();
}

void BOARD_InitMAGPeripheral(void)
{
  /* Initialize components */
  MAG_I2C_init();
  INT2_init();
}

void BOARD_InitDEBUG_UARTPeripheral(void)
{
  /* Initialize components */
  BOARD_LPSCI_1_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
