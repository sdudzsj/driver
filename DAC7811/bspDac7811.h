/*
 * @Author: luxun59 luxun59@126.com
 * @Date: 2022-12-03 16:43:46
 * @LastEditors: luxun59 luxun59@126.com
 * @LastEditTime: 2022-12-03 19:01:02
 * @FilePath: \driver\DAC7811\bspDac7811.h
 * @Description: 
 * 
 * Copyright (c) 2022 by luxun59 luxun59@126.com, All Rights Reserved. 
 */

#ifndef BSPDAC7811_H


#define BSPDAC7811_H

#include <stdint.h>



#define    STM32    1
#define    STM32HAL 2
#define    MSP430   3
#define    MSP432P  4
#define    MSP432E  5
#define    C2000    6


#define SOFTWARE -1
#define HARDWARE -2

//mcu 型号
#define MCUTYPE STM32

#define TRANSFER_METHOD SOFTWARE





#if MCUTYPE==STM32


#elif MCUTYPE==STM32HAL


#elif MCUTYPE==MSP432P


#elif MCUTYPE==MSP432E


#elif MCUTYPE==C2000

#endif






#if TRANSFER_METHOD == SOFTWARE

void DAC7811_Soft_Write(uint16_t da);

void DAC7811_Soft_Init(void);

#else

#endif

void dac7811_dataprocess(uint16_t *adcdata,uint16_t *dacdata,uint32_t num,uint8_t space );



#endif /*BSPDAC7811_H*/
