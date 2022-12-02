/*
 * @Author: luxun59 luxun59@126.com
 * @Date: 2022-11-27 20:46:52
 * @LastEditors: luxun59 luxun59@126.com
 * @LastEditTime: 2022-12-02 23:05:39
 * @FilePath: \undefinedc:\Users\14913\Desktop\c2000\driver\ADS1115\ads1115.c
 * @Description: 
 * 
 * Copyright (c) 2022 by luxun59 luxun59@126.com, All Rights Reserved. 
 */

#include "ads1115.h"


#define address 0x90//地址
#define config  0x01//选择寄存器
#define conversion 0x00
#define Lsiwei  0xE3//设置速度，比较器模式，报警
#define  channel_0      0                //表示选择通道0,及速度
#define  channel_1      1                //表示选择通道1
#define  channel_2      2                //表示选择通道2
#define  channel_3      3                //表示选择通道2
#define TRUE    1
#define FALSE   0

#define ads1115_SCL_GPIO GPIO_59_GPIO59
#define ads1115_SCL_PIN 59

#define ads1115_SDA_GPIO GPIO_23_GPIO23
#define ads1115_SDA_PIN 23


#define SCL_H GPIO_writePin(ads1115_SCL_PIN, 1)
#define SCL_L GPIO_writePin(ads1115_SCL_PIN, 0)
#define SDA_H GPIO_writePin(ads1115_SDA_PIN, 1)
#define SDA_L GPIO_writePin(ads1115_SDA_PIN, 0)

#define SDA_in  ads1115_sda_setin() //SDA改成输入模式
#define SDA_out   ads1115_sda_setout()//SDA变回输出模式
#define SDA_val GPIO_readPin(ads1115_SDA_PIN)//SDA的位值


void delay_1115(void)
{
    Delay_us(2);
}
/*******************************************
函数名称start
功    能完成IIC的起始条件操作
参    数无
返回值  无
********************************************/
void ads1115_start(void)
{
    SCL_H;
    SDA_H;
    delay_1115();
    SDA_L;
    delay_1115();
    SCL_L;
}
/*******************************************
函数名称stop
功    能完成IIC的终止条件操作
参    数无
返回值  无
********************************************/
void ads1115_stop(void)
{
    SDA_L;
    delay_1115();
    SCL_H;;
    delay_1115();
}

/*******************************************
函数名称mack
功    能完成IIC的主机应答操作
参    数无
返回值  无
********************************************/

void ads1115_mack(void)
{
    SDA_L;
    Delay_us(1);
    SCL_H;
    delay_1115();
    SCL_L;
    Delay_us(1);
    SDA_H;
    delay_1115();
}
/*******************************************
函数名称mnack
功    能完成IIC的主机无应答操作
参    数无
返回值  无
********************************************/
void ads1115_mnack(void)
{
    SDA_H;
    Delay_us(1);
    SCL_H;
    delay_1115();
    SCL_L;
    Delay_us(1);
    SDA_L;
    delay_1115();
}
/**********检查应答信号函数******************/
/*如果返回值为1则证明有应答信号反之没有*/ /*******************************************
函数名称check
功    能检查从机的应答操作
参    数无
返回值  从机是否有应答1--有0--无
********************************************/
void ads1115_ack()
{
    uint16_t i;
    i=0;
    SDA_in;
    SCL_H;
    delay_1115();
    while(SDA_val&&(i<250)) i++;
    SDA_out;
    SCL_L;
    delay_1115();
}

/*******************************************
函数名称write1
功    能向IIC总线发送一个1
参    数无
返回值  无
********************************************/
void ads1115_write1(void)
{
    SDA_H;
    delay_1115();
    SCL_H;
    delay_1115();
    SCL_L;
    delay_1115();
}

/*******************************************
函数名称write0
功    能向IIC总线发送一个0
参    数无
返回值  无
********************************************/
void ads1115_write0(void)
{
    SDA_L;
    delay_1115();
    SCL_H;
    delay_1115();
    SCL_L;
    delay_1115();
}

/*******************************************
函数名称write1byte
功    能向IIC总线发送一个字节的数据
参    数wdata--发送的数据
返回值  无
********************************************/
void ads1115_write1byte(uint16_t wdata)
{
    uint16_t i;
    for(i = 8;i > 0;i--)
    {
        if(wdata & 0x0080)
            ads1115_write1();
        else
            ads1115_write0();
        wdata <<= 1;
    }
    SDA_H;
    Delay_us(1);
}

/*******************************************
函数名称read1byte
功    能从IIC总线读取一个字节
参    数无
返回值  读取的数据
********************************************/
uint16_t ads1115_read1byte(void)
{
    uint16_t  rdata = 0x00,i;
    uint16_t flag;
     for(i = 0;i < 8;i++)
     {
        SDA_H;
        SCL_H;
        SDA_in;
        flag = SDA_val;
        rdata <<= 1;
        if(flag)
            rdata |= 0x01;
       SDA_out;
        SCL_L;
     }
    return rdata;
}



void Confige1115(uint16_t channel)
{
    uint16_t a_channel;
    switch (channel)
    {
    case 0:a_channel=0xC2;break;
    case 1:a_channel=0xD2;break;
    case 2:a_channel=0xE2;break;
    case 3:a_channel=0xF2;break;
    default: break;
    }
    ads1115_start();
    ads1115_write1byte(address);
    ads1115_ack();
    ads1115_write1byte(config);
    ads1115_ack();
    ads1115_write1byte(a_channel);
    ads1115_ack();
    ads1115_write1byte(Lsiwei);
    ads1115_ack();
    ads1115_stop();
}

uint16_t ads1115_read1115()
{
    uint16_t result_l,result_h;
    uint16_t result;
    ads1115_start();
    ads1115_write1byte(address);
    ads1115_ack();
    ads1115_write1byte(conversion);
    ads1115_ack();
    ads1115_stop();
    Delay_ms(5);
    ads1115_start();
    ads1115_write1byte(address+1);
    ads1115_ack();
    result_h=ads1115_read1byte();
    ads1115_mack();
    result_l=ads1115_read1byte();
    ads1115_ack();
    ads1115_stop();
    result=result_h*256+result_l;
    return result;
}

uint16_t  go_1115(uint16_t temp)
{
  uint16_t result_gd;
  Confige1115(temp);
  Delay_ms(5);
  result_gd = ads1115_read1115();
  Delay_ms(5);
  return result_gd;
}


void ads1115_init(void)
{
    GPIO_setPinConfig(ads1115_SCL_GPIO);
    GPIO_setDirectionMode(ads1115_SCL_PIN, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(ads1115_SCL_PIN, GPIO_PIN_TYPE_STD);
    GPIO_setMasterCore(ads1115_SCL_PIN, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(ads1115_SCL_PIN, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(ads1115_SDA_GPIO);
    GPIO_setDirectionMode(ads1115_SDA_PIN, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(ads1115_SDA_PIN, GPIO_PIN_TYPE_STD);
    GPIO_setMasterCore(ads1115_SDA_PIN, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(ads1115_SDA_PIN, GPIO_QUAL_SYNC);


      SCL_H;
      SDA_H;
      SDA_out;
}



void ads1115_sda_setin()
{
    GPIO_setPinConfig(ads1115_SDA_GPIO);
    GPIO_setDirectionMode(ads1115_SDA_PIN, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(ads1115_SDA_PIN, GPIO_PIN_TYPE_STD);
    GPIO_setMasterCore(ads1115_SDA_PIN, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(ads1115_SDA_PIN, GPIO_QUAL_SYNC);

}

void ads1115_sda_setout()
{
    GPIO_setPinConfig(ads1115_SDA_GPIO);
    GPIO_setDirectionMode(ads1115_SDA_PIN, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(ads1115_SDA_PIN, GPIO_PIN_TYPE_STD);
    GPIO_setMasterCore(ads1115_SDA_PIN, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(ads1115_SDA_PIN, GPIO_QUAL_SYNC);

}


