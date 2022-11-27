/*
 * dac7811.c
 *
 *  Created on: 2022年7月10日
 *      Author: 14913
 */

#include "DAC7811.h"


#define SCLK_Clock RCC_APB2Periph_GPIOA
#define SCLK_Port GPIOA
#define SCLK_Pin  GPIO_Pin_0
#define SYNC_Clock RCC_APB2Periph_GPIOA
#define SYNC_Port GPIOA
#define SYNC_Pin  GPIO_Pin_1
#define SDIN_Clock RCC_APB2Periph_GPIOA
#define SDIN_Port GPIOA
#define SDIN_Pin  GPIO_Pin_2

//GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);

#define SPI_SCLK_L    GPIO_ResetBits(SCLK_Port,SCLK_Pin)
#define SPI_SCLK_H    GPIO_SetBits(SCLK_Port,SCLK_Pin)
#define SPI_SYNC_L    GPIO_ResetBits(SYNC_Port,SYNC_Pin)
#define SPI_SYNC_H    GPIO_SetBits(SYNC_Port,SYNC_Pin)
#define SPI_SDIN_L    GPIO_ResetBits(SDIN_Port,SDIN_Pin)
#define SPI_SDIN_H    GPIO_SetBits(SDIN_Port,SDIN_Pin)


uint16_t g_u16dacdata[DACNUM];





void DAC7811_Soft_Init(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(SCLK_Clock, ENABLE);	 //使能A端口时钟
	GPIO_InitStructure.GPIO_Pin = SCLK_Pin;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(SCLK_Port, &GPIO_InitStructure);	  //初始化

    GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(SYNC_Clock, ENABLE);	 //使能A端口时钟
	GPIO_InitStructure.GPIO_Pin = SYNC_Pin;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(SYNC_Port, &GPIO_InitStructure);	  //初始化

    GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(SDIN_Clock, ENABLE);	 //使能A端口时钟
	GPIO_InitStructure.GPIO_Pin = SDIN_Pin;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(SDIN_Port, &GPIO_InitStructure);	  //初始化
	
    SPI_SCLK_H;
    SPI_SYNC_H;
    SPI_SDIN_H;
}



void DAC7811_Soft_Write(uint16_t da) //DAC7811 12bits
{
    u8 i;
    da|=0x1000;//bit12=1
    da&=0x1FFF;//bit15、14、13=0
    SPI_SCLK_H;
    SPI_SYNC_H;
    SPI_SYNC_L;
    for(i=0; i<16; i++)
    {
        SPI_SCLK_H;
        if(da & 0x8000) SPI_SDIN_H;
        else SPI_SDIN_L;
        SPI_SCLK_L;
        da<<=1;
    }
    SPI_SCLK_H;
    SPI_SDIN_H;
    SPI_SYNC_H;
}



void dac7811_dataprocess(uint16_t *adcdata,uint16_t *dacdata,uint32_t num,uint8_t space )
{
    uint32_t i=0;
    for(i=0;i<num;i+=space)
    {
        dacdata[i] = adcdata[i] | 0x1000;
        dacdata[i] &= 0x1FFF;
    }
}


/*
 *
 *          dac7811_dataprocess(g_u16adcBuffer,g_u16dacdata,DACNUM);
 *          uint16_t txdata = 0x13Cf;
            //1. hardware
            SPI_MASter_config();
            DAC7811_TIME1_INT_Config();
            MAP_TimerEnable(TIMER1_BASE, TIMER_A);

            //MAP_SSIDataPut(SSI0_BASE, txdata);

            //2. software
            DAC7811_Soft_Init();

            //DAC7811_Soft_Write(txdata);
 *
 *
 *
 * */












