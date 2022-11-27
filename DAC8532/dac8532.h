/*
 * @Author: luxun59 luxun59@126.com
 * @Date: 2022-11-27 18:55:52
 * @LastEditors: luxun59 luxun59@126.com
 * @LastEditTime: 2022-11-27 21:25:32
 * @FilePath: \driver\DAC8532\dac8532.h
 * @Description: 
 * 
 * Copyright (c) 2022 by luxun59 luxun59@126.com, All Rights Reserved. 
 */

/*
 * dac8532.h
 *
 *  Created on: 2022年8月1日
 *      Author: 14913
 */

#ifndef HARDWARE_INC_DAC8532_H_
#define HARDWARE_INC_DAC8532_H_


#define DAC8532_LOAD_NEWDATA_TO_DACA 0x10
#define DAC8532_LOAD_NEWDATA_TO_DACB 0x20

#define DAC8532_DATA_TO_DATABUFFERA 0x00
#define DAC8532_DATA_TO_DATABUFFERB_AND_LOAD_DAC_AB 0x34

#define DAC8532_POWERDOWN_DACA_TO_HIGH 0x13
#define DAC8532_POWERDOWN_DACB_TO_HIGH 0x23



void  DAC8532_SPI_SW_init(void);
void  DAC8532_SPI_SW_Write(uint8_t mode,uint16_t Data);

#endif /* HARDWARE_INC_DAC8532_H_ */
