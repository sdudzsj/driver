/*
 * @Author: luxun59 luxun59@126.com
 * @Date: 2022-12-03 19:13:21
 * @LastEditors: luxun59 luxun59@126.com
 * @LastEditTime: 2022-12-03 20:17:10
 * @FilePath: \driver\DAC7811\msp432eDac7811.h
 * @Description: 
 * 
 * Copyright (c) 2022 by luxun59 luxun59@126.com, All Rights Reserved. 
 */
/*
 * @Author: luxun59 luxun59@126.com
 * @Date: 2022-12-03 19:13:21
 * @LastEditors: luxun59 luxun59@126.com
 * @LastEditTime: 2022-12-03 19:13:51
 * @FilePath: \driver\DAC7811\msp432eDac7811.h
 * @Description: 
 * 
 * Copyright (c) 2022 by luxun59 luxun59@126.com, All Rights Reserved. 
 */
#ifndef HARDWARE_INC_DAC7811_H_
#define HARDWARE_INC_DAC7811_H_


#include <stdint.h>

#include <ti/devices/msp432e4/driverlib/driverlib.h>

#define SOFTWARE -1
#define HARDWARE -2


//软件模拟方式还是硬件spi形式
#define TRANSFER_METHOD SOFTWARE


#if TRANSFER_METHOD == SOFTWARE

void DAC7811_Soft_Write(uint16_t da);

void DAC7811_Soft_Init(void);

#else

void DAC7811_SPI_MASter_config(void);
void DAC7811_Hard_Write(uint16_t da);

#endif

void DAC7811_SPI_Write(uint16_t da);

#endif /* HARDWARE_INC_DAC7811_H_ */