/*
 * @Author: luxun59 luxun59@126.com
 * @Date: 2022-12-03 16:43:00
 * @LastEditors: luxun59 luxun59@126.com
 * @LastEditTime: 2022-12-03 19:00:39
 * @FilePath: \driver\DAC7811\bspDac7811.c
 * @Description: 
 * 
 * Copyright (c) 2022 by luxun59 luxun59@126.com, All Rights Reserved. 
 */


#include "bspDac7811.h"





#if TRANSFER_METHOD == SOFTWARE

//# software
//## Definition 在此处修改引脚     <<<<<<<<----------
#if MCUTYPE==STM32

#define DAC7811_SCLK_Clock RCC_APB2Periph_GPIOA
#define DAC7811_SCLK_Port GPIOA
#define DAC7811_SCLK_Pin  GPIO_Pin_0
#define DAC7811_SYNC_Clock RCC_APB2Periph_GPIOA
#define DAC7811_SYNC_Port GPIOA
#define DAC7811_SYNC_Pin  GPIO_Pin_1
#define DAC7811_SDIN_Clock RCC_APB2Periph_GPIOA
#define DAC7811_SDIN_Port GPIOA
#define DAC7811_SDIN_Pin  GPIO_Pin_2

#define DAC7811_SPI_SCLK_L    GPIO_ResetBits(DAC7811_SCLK_Port,DAC7811_SCLK_Pin)
#define DAC7811_SPI_SCLK_H    GPIO_SetBits(DAC7811_SCLK_Port,DAC7811_SCLK_Pin)
#define DAC7811_SPI_SYNC_L    GPIO_ResetBits(DAC7811_SYNC_Port,DAC7811_SYNC_Pin)
#define DAC7811_SPI_SYNC_H    GPIO_SetBits(DAC7811_SYNC_Port,DAC7811_SYNC_Pin)
#define DAC7811_SPI_SDIN_L    GPIO_ResetBits(DAC7811_SDIN_Port,DAC7811_SDIN_Pin)
#define DAC7811_SPI_SDIN_H    GPIO_SetBits(DAC7811_SDIN_Port,DAC7811_SDIN_Pin)

#elif MCUTYPE==STM32HAL


#define DAC7811_SCLK_Port GPIOA
#define DAC7811_SCLK_Pin  GPIO_PIN_0
#define DAC7811_SYNC_Port GPIOA
#define DAC7811_SYNC_Pin  GPIO_PIN_1
#define DAC7811_SDIN_Port GPIOA
#define DAC7811_SDIN_Pin  GPIO_PIN_2

#define DAC7811_SCLK_Clock_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()
#define DAC7811_SYNC_Clock_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()
#define DAC7811_SDIN_Clock_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()

#define DAC7811_SPI_SCLK_L    HAL_GPIO_WritePin(DAC7811_SCLK_Port,DAC7811_SCLK_Pin,GPIO_PIN_RESET)
#define DAC7811_SPI_SCLK_H    HAL_GPIO_WritePin(DAC7811_SCLK_Port,DAC7811_SCLK_Pin,GPIO_PIN_SET)
#define DAC7811_SPI_SYNC_L    HAL_GPIO_WritePin(DAC7811_SYNC_Port,DAC7811_SYNC_Pin,GPIO_PIN_RESET)
#define DAC7811_SPI_SYNC_H    HAL_GPIO_WritePin(DAC7811_SYNC_Port,DAC7811_SYNC_Pin,GPIO_PIN_SET)
#define DAC7811_SPI_SDIN_L    HAL_GPIO_WritePin(DAC7811_SDIN_Port,DAC7811_SDIN_Pin,GPIO_PIN_RESET)
#define DAC7811_SPI_SDIN_H    HAL_GPIO_WritePin(DAC7811_SDIN_Port,DAC7811_SDIN_Pin,GPIO_PIN_SET)


#elif MCUTYPE==MSP432P

#define Set_Bit(val, bitn) (val |= (/*1 <<*/ (bitn))) //置1
#define Clr_Bit(val, bitn) (val &= ~(/*1<<*/ (bitn))) //置0
#define Get_Bit(val, bitn) (val & (1 << (bitn)))      //获取电平

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


#elif MCUTYPE==MSP432E

#define DAC7811_SCLK_Port GPIO_PORTA_BASE
#define DAC7811_SCLK_Pin  GPIO_PIN_0
#define DAC7811_SYNC_Port GPIO_PORTA_BASE
#define DAC7811_SYNC_Pin  GPIO_PIN_1
#define DAC7811_SDIN_Port GPIO_PORTA_BASE
#define DAC7811_SDIN_Pin  GPIO_PIN_2

#define DAC7811_SCLK_SYSCTL_PERIPH SYSCTL_PERIPH_GPIOA
#define DAC7811_SYNC_SYSCTL_PERIPH SYSCTL_PERIPH_GPIOA
#define DAC7811_SDIN_SYSCTL_PERIPH SYSCTL_PERIPH_GPIOA


#define GPIO_PIN_RESET 0x0

#define DAC7811_SPI_SCLK_L    GPIOPinWrite(DAC7811_SCLK_Port,DAC7811_SCLK_Pin,GPIO_PIN_RESET)
#define DAC7811_SPI_SCLK_H    GPIOPinWrite(DAC7811_SCLK_Port,DAC7811_SCLK_Pin,DAC7811_SCLK_Pin)
#define DAC7811_SPI_SYNC_L    GPIOPinWrite(DAC7811_SYNC_Port,DAC7811_SYNC_Pin,GPIO_PIN_RESET)
#define DAC7811_SPI_SYNC_H    GPIOPinWrite(DAC7811_SYNC_Port,DAC7811_SYNC_Pin,DAC7811_SYNC_Pin)
#define DAC7811_SPI_SDIN_L    GPIOPinWrite(DAC7811_SDIN_Port,DAC7811_SDIN_Pin,GPIO_PIN_RESET)
#define DAC7811_SPI_SDIN_H    GPIOPinWrite(DAC7811_SDIN_Port,DAC7811_SDIN_Pin,DAC7811_SDIN_Pin)



#elif MCUTYPE==C2000

#define DAC7811_SCLK_Port GPIO_59_GPIO59
#define DAC7811_SCLK_Pin 57
#define DAC7811_SYNC_Port GPIO_59_GPIO59
#define DAC7811_SYNC_Pin 58
#define DAC7811_SDIN_Port GPIO_59_GPIO59
#define DAC7811_SDIN_Pin 59

#define DAC7811_SPI_SCLK_H GPIO_writePin(DAC7811_SCLK_Pin, 1)
#define DAC7811_SPI_SCLK_L GPIO_writePin(DAC7811_SCLK_Pin, 0)
#define DAC7811_SPI_SYNC_H GPIO_writePin(DAC7811_SYNC_Pin, 1)
#define DAC7811_SPI_SYNC_L GPIO_writePin(DAC7811_SYNC_Pin, 0)
#define DAC7811_SPI_SDIN_H GPIO_writePin(DAC7811_SDIN_Pin, 1)
#define DAC7811_SPI_SDIN_L GPIO_writePin(DAC7811_SDIN_Pin, 0)

#endif





//## soft init 一般无需修改
/**
 * @description: gpio软件模拟初始化设置，此函数一般无需修改
 * @return {*}
 */
void DAC7811_Soft_Init(void)
{
#if MCUTYPE==STM32
    GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(DAC7811_SCLK_Clock, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = DAC7811_SCLK_Pin;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(DAC7811_SCLK_Port, &GPIO_InitStructure);	  //初始化

    GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(DAC7811_SYNC_Clock, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = DAC7811_SYNC_Pin;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(DAC7811_SYNC_Port, &GPIO_InitStructure);	  //初始化

    GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(DAC7811_SDIN_Clock, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = DAC7811_SDIN_Pin;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(DAC7811_SDIN_Port, &GPIO_InitStructure);	  //初始化
	
#elif MCUTYPE==STM32HAL

    DAC7811_SCLK_Clock_ENABLE;
    DAC7811_SYNC_Clock_ENABLE;
    DAC7811_SDIN_Clock_ENABLE;

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DAC7811_SCLK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DAC7811_SCLK_Port, &GPIO_InitStruct); 

    GPIO_InitStruct.Pin = DAC7811_SYNC_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DAC7811_SYNC_Port, &GPIO_InitStruct); 

    GPIO_InitStruct.Pin = DAC7811_SDIN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DAC7811_SDIN_Port, &GPIO_InitStruct); 


#elif MCUTYPE==MSP432P
    DAC7811_SPI_SCLK_IO_INIT;
    DAC7811_SPI_SYNC_IO_INIT;
    DAC7811_SPI_SDIN_IO_INIT;

#elif MCUTYPE==MSP432E
    SysCtlPeripheralEnable(DAC7811_SCLK_SYSCTL_PERIPH);
    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(DAC7811_SCLK_SYSCTL_PERIPH))
    {
    }
    SysCtlPeripheralEnable(DAC7811_SYNC_SYSCTL_PERIPH);
    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(DAC7811_SYNC_SYSCTL_PERIPH))
    {
    }
    SysCtlPeripheralEnable(DAC7811_SDIN_SYSCTL_PERIPH);
    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(DAC7811_SDIN_SYSCTL_PERIPH))
    {
    }


    //GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(DAC7811_SCLK_Port,DAC7811_SCLK_Pin);
    GPIOPinTypeGPIOOutput(DAC7811_SYNC_Port,DAC7811_SYNC_Pin);
    GPIOPinTypeGPIOOutput(DAC7811_SDIN_Port,DAC7811_SDIN_Pin);


#elif MCUTYPE==C2000

    GPIO_setPinConfig(DAC7811_SCLK_Port);
    GPIO_setDirectionMode(DAC7811_SCLK_Pin, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DAC7811_SCLK_Pin, GPIO_PIN_TYPE_STD);
    GPIO_setMasterCore(DAC7811_SCLK_Pin, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(DAC7811_SCLK_Pin, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(DAC7811_SYNC_Port);
    GPIO_setDirectionMode(DAC7811_SYNC_Pin, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DAC7811_SYNC_Pin, GPIO_PIN_TYPE_STD);
    GPIO_setMasterCore(DAC7811_SYNC_Pin, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(DAC7811_SYNC_Pin, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(DAC7811_SDIN_Port);
    GPIO_setDirectionMode(DAC7811_SDIN_Pin, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DAC7811_SDIN_Pin, GPIO_PIN_TYPE_STD);
    GPIO_setMasterCore(DAC7811_SDIN_Pin, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(DAC7811_SDIN_Pin, GPIO_QUAL_SYNC);


#endif

    DAC7811_SPI_SCLK_H;
    DAC7811_SPI_SYNC_H;
    DAC7811_SPI_SDIN_H;
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
//hardware



#endif









/**
 * @description: 批处理函数，批量将待处理数据加上dac输出控制位并放置到输出缓冲区。
 * @param {uint16_t} *adcdata 待处理数据
 * @param {uint16_t} *dacdata 7811输出缓冲区数据
 * @param {uint32_t} num   处理数量
 * @param {uint8_t} space 间隔数量
 * @return {*}
 */
void dac7811_dataprocess(uint16_t *adcdata,uint16_t *dacdata,uint32_t num,uint8_t space )
{
    uint32_t i=0;
    for(i=0;i<num;i+=space)
    {
        dacdata[i] = adcdata[i] | 0x1000;
        dacdata[i] &= 0x1FFF;
    }
}


