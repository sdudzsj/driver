/*
 * @Author: luxun59 luxun59@126.com
 * @Date: 2022-11-27 20:47:01
 * @LastEditors: luxun59 luxun59@126.com
 * @LastEditTime: 2022-12-02 23:05:31
 * @FilePath: \undefinedc:\Users\14913\Desktop\c2000\driver\ADS1115\ads1115.h
 * @Description: 
 * 
 * Copyright (c) 2022 by luxun59 luxun59@126.com, All Rights Reserved. 
 */
/*
 * ads1115.h
 *
 *  Created on: 2022年8月11日
 *      Author: 14913
 */
#ifndef APP_INC_ADS1115_H_
#define APP_INC_ADS1115_H_


#include "include.h"





void delay_1115(void);
void ads1115_start(void);
void ads1115_stop(void);
void ads1115_mack(void);
void ads1115_mnack(void);
void ads1115_ack();
void ads1115_write1(void);
void ads1115_write0(void);
void ads1115_write1byte(uint16_t wdata);
uint16_t ads1115_read1byte(void);
void ads1115_Confige1115(uint16_t channel);
uint16_t ads1115_read1115();
uint16_t  go_1115(uint16_t temp);
void ads1115_init(void);


void ads1115_sda_setin();
void ads1115_sda_setout();



#endif /* APP_INC_ADS1115_H_ */
