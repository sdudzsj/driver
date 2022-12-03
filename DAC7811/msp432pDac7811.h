/*
 * @Author: luxun59 luxun59@126.com
 * @Date: 2022-11-27 17:31:59
 * @LastEditors: luxun59 luxun59@126.com
 * @LastEditTime: 2022-12-03 20:16:25
 * @FilePath: \driver\DAC7811\msp432pDac7811.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
 * dac7811.h
 *
 *  Created on: 2022年7月8日
 *      Author: 14913
 */

#ifndef HARDWARE_INC_DAC7811_H_
#define HARDWARE_INC_DAC7811_H_


#include <stdint.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

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



