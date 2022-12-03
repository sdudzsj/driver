/*
 * @Author: luxun59 luxun59@126.com
 * @Date: 2022-11-27 17:31:59
 * @LastEditors: luxun59 luxun59@126.com
 * @LastEditTime: 2022-12-03 20:16:59
 * @FilePath: \driver\DAC7811\msp432pDac7811.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "msp432pDac7811.h"




#define Set_Bit(val, bitn) (val |= (/*1 <<*/ (bitn))) //置1
#define Clr_Bit(val, bitn) (val &= ~(/*1<<*/ (bitn))) //置0
#define Get_Bit(val, bitn) (val & (1 << (bitn)))      //获取电平

#if TRANSFER_METHOD == SOFTWARE
//# 软件模拟spi

//dac7811 SPI SCL P1.0
#define DAC7811_SCLK_Pin (BIT0)
#define DAC7811_SCLK_Dir P1DIR
#define DAC7811_SCLK_Port P1OUT

#define DAC7811_SYNC_Pin (BIT1)
#define DAC7811_SYNC_Dir P1DIR
#define DAC7811_SYNC_Port P1OUT

#define DAC7811_SDIN_Pin (BIT2)
#define DAC7811_SDIN_Dir P1DIR
#define DAC7811_SDIN_Port P1OUT


#define DAC7811_SPI_SCLK_IO_INIT (Set_Bit(DAC7811_SCLK_Dir, DAC7811_SCLK_Pin))
#define DAC7811_SPI_SYNC_IO_INIT (Set_Bit(DAC7811_SYNC_Dir, DAC7811_SYNC_Pin))
#define DAC7811_SPI_SDIN_IO_INIT (Set_Bit(DAC7811_SDIN_Dir, DAC7811_SDIN_Pin))

#define DAC7811_SPI_SCLK_H (Set_Bit(DAC7811_SCLK_Port, DAC7811_SCLK_Pin))
#define DAC7811_SPI_SCLK_L (Clr_Bit(DAC7811_SCLK_Port, DAC7811_SCLK_Pin))
#define DAC7811_SPI_SYNC_H (Set_Bit(DAC7811_SYNC_Port, DAC7811_SYNC_Pin))
#define DAC7811_SPI_SYNC_L (Clr_Bit(DAC7811_SYNC_PORT, DAC7811_SYNC_Pin))
#define DAC7811_SPI_SDIN_H (Set_Bit(DAC7811_SDIN_Port, DAC7811_SDIN_Pin))
#define DAC7811_SPI_SDIN_L (Clr_Bit(DAC7811_SDIN_Port, DAC7811_SDIN_Pin))


//## soft init 一般无需修改
/**
 * @description: gpio软件模拟初始化设置，此函数一般无需修改
 * @return {*}
 */
void DAC7811_Soft_Init(void)
{
    DAC7811_SPI_SCLK_IO_INIT;
    DAC7811_SPI_SYNC_IO_INIT;
    DAC7811_SPI_SDIN_IO_INIT;
}



/**
 * @description: 将数据写入dac7811，采用gpio软件模拟方式进行。
 * @param: 想要写入的数据，有效位数12位。
 * @return {*}
 */
void DAC7811_Soft_Write(uint16_t da) //DAC7811 12bits
{
    uint16_t i;
    da|=0x1000;//bit12=1
    da&=0x1FFF;//bit15、14、13=0
    DAC7811_SPI_SCLK_H;
    DAC7811_SPI_SYNC_H;
    DAC7811_SPI_SYNC_L;
    for(i=0; i<16; i++)
    {
        DAC7811_SPI_SCLK_H;
        if(da & 0x8000) 
            DAC7811_SPI_SDIN_H;
        else 
            DAC7811_SPI_SDIN_L;
        DAC7811_SPI_SCLK_L;
        da<<=1;
    }
    DAC7811_SPI_SCLK_H;
    DAC7811_SPI_SDIN_H;
    DAC7811_SPI_SYNC_H;
}




#else

//# 硬件spi

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




void DAC7811_SPI_MASter_config(void)
{
        
}




/**
 * @description: 将数据写入dac7811，采用硬件ssi使用spi协议方式进行。
 * @param: 想要写入的数据，有效位数12位。
 * @return {*}
 */
void DAC7811_Hard_Write(uint16_t da)

{
    da|=0x1000;//bit12=1
    da&=0x1FFF;//bit15、14、13=0 

}

#endif 



/**
 * @description: 将数据写入dac7811
 * @param {uint16_t} da:想要写入的数据，有效位数12位。
 * @return {*}
 */
void DAC7811_SPI_Write(uint16_t da)
{
    #if TRANSFER_METHOD == SOFTWARE

    DAC7811_Soft_Write(da);

    #else
    DAC7811_Hard_Write(da);

    #endif

}




















