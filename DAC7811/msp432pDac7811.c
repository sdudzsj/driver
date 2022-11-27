/*
 * @Author: luxun59 luxun59@126.com
 * @Date: 2022-11-27 17:31:59
 * @LastEditors: luxun59 luxun59@126.com
 * @LastEditTime: 2022-11-27 17:32:51
 * @FilePath: \undefinedc:\Users\14913\Desktop\c2000\driver\DAC7811\msp432pDac7811.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "msp432pDac7811.h"


/* SPI Configuration Parameter */
const eUSCI_SPI_MasterConfig spi2MasterConfig =
{ EUSCI_A_SPI_CLOCKSOURCE_SMCLK, 48000000, 2000000,
        EUSCI_A_SPI_MSB_FIRST,
        EUSCI_A_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
        EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_HIGH, EUSCI_A_SPI_4PIN_UCxSTE_ACTIVE_LOW };






void my_spi2_master_config(void)
{

    /* Selecting P1.5 P1.6 and P1.7 in SPI mode */
   MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3,
           GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
   MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P4,
              GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
   MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3,
              GPIO_PIN0 , GPIO_PRIMARY_MODULE_FUNCTION);
   MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
               GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);


   /* Configuring SPI in 3wire master mode */
   SPI_initMaster(EUSCI_A2_BASE, &spi2MasterConfig);

   /* Enable SPI module */
   SPI_enableModule(EUSCI_A2_BASE);

   /* Enabling interrupts */
//   SPI_enableInterrupt(EUSCI_B0_BASE, EUSCI_SPI_RECEIVE_INTERRUPT);
//   Interrupt_enableInterrupt(INT_EUSCIB0);
//   Interrupt_enableSleepOnIsrExit();
   //![Simple SPI Example]


}












