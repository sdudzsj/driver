/*
 * @Author: luxun59 68161305+luxun59@users.noreply.github.com
 * @Date: 2022-11-24 19:04:18
 * @LastEditors: luxun59 68161305+luxun59@users.noreply.github.com
 * @LastEditTime: 2022-11-24 19:20:38
 * @FilePath: \undefinedc:\Users\14913\Desktop\新建文件夹 (3)\dac7811.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
 * dac7811.h
 *
 *  Created on: 2022年7月10日
 *      Author: 14913
 */

#ifndef DAC7811_H_
#define DAC7811_H_


#include "stdint.h"
#include "include.h"


#define u8  unsigned char
#define u16 unsigned short int
#define u32 unsigned int



#define DACNUM 256


void DAC7811_Soft_Init(void);
void DAC7811_Soft_Write(u16 da);

extern uint16_t g_u16dacdata[DACNUM];



#endif /* DAC7811_H_ */




