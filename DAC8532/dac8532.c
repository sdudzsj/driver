/*
 * @Author: luxun59 luxun59@126.com
 * @Date: 2022-11-27 18:55:47
 * @LastEditors: luxun59 luxun59@126.com
 * @LastEditTime: 2022-11-27 21:26:14
 * @FilePath: \driver\DAC8532\dac8532.c
 * @Description: 
 * 
 * Copyright (c) 2022 by luxun59 luxun59@126.com, All Rights Reserved. 
 */

/*
 * dac8532.c
 *
 *  Created on: 2022年8月1日
 *      Author: 14913
 */

#include "dac8532.h"

#include <stdint.h>

#define DAC8532_SCLK_PORT GPIO_PIN5
#define DAC8532_DIN_PORT  GPIO_PIN6
#define DAC8532_SYNC_PORT GPIO_PIN7

#define DAC8532_SCLK_PIN GPIO_PIN5
#define DAC8532_DIN_PIN  GPIO_PIN6
#define DAC8532_SYNC_PIN GPIO_PIN7

#define DAC8532_SCLK_H GPIO_setOutputHighOnPin(DAC8532_SCLK_PORT, DAC8532_SCLK_PIN)
#define DAC8532_SCLK_L GPIO_setOutputLowOnPin(DAC8532_SCLK_PORT, DAC8532_SCLK_PIN)

#define DAC8532_DIN_H GPIO_setOutputHighOnPin(DAC8532_DIN_PORT, DAC8532_DIN_PIN)
#define DAC8532_DIN_L GPIO_setOutputLowOnPin(DAC8532_DIN_PORT, DAC8532_DIN_PIN)

#define DAC8532_SYNC_H GPIO_setOutputHighOnPin(DAC8532_SYNC_PORT, DAC8532_SYNC_PIN)
#define DAC8532_SYNC_L GPIO_setOutputLowOnPin(DAC8532_SYNC_PORT, DAC8532_SYNC_PIN)





void DAC8532_Delay(uint32_t time)
{
    delay_us(time);
}



/**
 * @description: 初始化引脚
 * @return {*}
 */
void  DAC8532_SPI_SW_init(void)
{
   MAP_GPIO_setAsOutputPin(DAC8532_SCLK_PORT,DAC8532_SCLK_PIN);
   MAP_GPIO_setAsOutputPin(DAC8532_DIN_PORT,DAC8532_DIN_PIN);
   MAP_GPIO_setAsOutputPin(DAC8532_SYNC_PORT,DAC8532_SYNC_PIN);
}





/**
 * @description: dac8532软件模拟时序，写入，包括模式和数据，前八位为模式后16位为数据。
 * @param {uint8_t} mode 模式
 * @param {uint16_t} Data 数据
 * @return {*}
 */
void  DAC8532_SPI_SW_Write(uint8_t mode,uint16_t Data)
{
   uint8_t i=0;
    DAC8532_SYNC_H;
    DAC8532_Delay(2);
    DAC8532_SYNC_L;
   for(i=0;i<8;i++)
   {
     DAC8532_SCLK_L;
     if(mode&0x80)
         DAC8532_DIN_H;
     else
         DAC8532_DIN_L;
     DAC8532_SCLK_H;
     DAC8532_Delay(2);
     mode<<=1;
   }
   for(i=0;i<16;i++)
   {
     DAC8532_SCLK_L;
     if(Data&0x8000)
         DAC8532_DIN_H;
     else
         DAC8532_DIN_L;
     DAC8532_SCLK_H;
     DAC8532_Delay(2);
     Data<<=1;
   }
   DAC8532_Delay(2);
   DAC8532_SYNC_H;
}








