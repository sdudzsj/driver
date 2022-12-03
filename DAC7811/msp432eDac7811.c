
#include "msp432eDac7811.h"


// 所用硬件资源定义
#if TRANSFER_METHOD == SOFTWARE
//# 软件模拟spi

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


#else

#define DAC7811_SSI_BASE           SSI0_BASE
#define DAC7811_SSI_INT            INT_SSI0
#define DAC7811_SSI_SYSCTL_PERIPH  SYSCTL_PERIPH_SSI0


#define DAC7811_SSI_SCLK_PORTBASE  GPIO_PORTA_BASE
#define DAC7811_SSI_MTX_PORTBASE   GPIO_PORTA_BASE
#define DAC7811_SSI_MRX_PORTBASE   GPIO_PORTA_BASE
#define DAC7811_SSI_SYNC_PORTBASE  GPIO_PORTA_BASE

#define DAC7811_GPIO_SCLK_SYSCTL   SYSCTL_PERIPH_GPIOA
#define DAC7811_GPIO_MTX_SYSCTL    SYSCTL_PERIPH_GPIOA
#define DAC7811_GPIO_MRX_SYSCTL    SYSCTL_PERIPH_GPIOA
#define DAC7811_GPIO_SYNC_SYSCTL   SYSCTL_PERIPH_GPIOA

#define DAC7811_SSI_SCLK_Pin       GPIO_PIN_2
#define DAC7811_SSI_MTX_Pin        GPIO_PIN_4
#define DAC7811_SSI_MRX_Pin        GPIO_PIN_5
#define DAC7811_SSI_SYNC_Pin       GPIO_PIN_3

#define DAC7811_SSI_SCLK_GPIO      GPIO_PA2_SSI0CLK
#define DAC7811_SSI_MTX_GPIO       GPIO_PA4_SSI0XDAT0
#define DAC7811_SSI_MRX_GPIO       GPIO_PA5_SSI0XDAT1
#define DAC7811_SSI_SYNC_GPIO      GPIO_PA3_SSI0FSS





#endif 


//函数设置


#if TRANSFER_METHOD == SOFTWARE
//## soft init 一般无需修改
/**
 * @description: gpio软件模拟初始化设置，此函数一般无需修改
 * @return {*}
 */
void DAC7811_Soft_Init(void)
{
    SysCtlPeripheralEnable(DAC7811_SCLK_SYSCTL_PERIPH);
    //
    // Check if the peripheral access is enabled.
    //
    uint32_t gpioInitDelay = 0xffff;
    while(!SysCtlPeripheralReady(DAC7811_SCLK_SYSCTL_PERIPH))
    {
        if(--gpioInitDelay==0)
            break;
    }
    SysCtlPeripheralEnable(DAC7811_SYNC_SYSCTL_PERIPH);
    //
    // Check if the peripheral access is enabled.
    //
    gpioInitDelay = 0xffff;
    while(!SysCtlPeripheralReady(DAC7811_SYNC_SYSCTL_PERIPH))
    {
        if(--gpioInitDelay==0)
            break;
    }
    SysCtlPeripheralEnable(DAC7811_SDIN_SYSCTL_PERIPH);
    //
    // Check if the peripheral access is enabled.
    //
    gpioInitDelay = 0xffff;
    while(!SysCtlPeripheralReady(DAC7811_SDIN_SYSCTL_PERIPH))
    {
        if(--gpioInitDelay==0)
            break;
    }


    //GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(DAC7811_SCLK_Port,DAC7811_SCLK_Pin);
    GPIOPinTypeGPIOOutput(DAC7811_SYNC_Port,DAC7811_SYNC_Pin);
    GPIOPinTypeGPIOOutput(DAC7811_SDIN_Port,DAC7811_SDIN_Pin);
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


/**
 * @description: 硬件ssi使用spi设置。
 * @return {*}
 */
void DAC7811_SPI_MASter_config(void)
{

/* Enable clocks to GPIO Port  and configure pins as SSI */
    MAP_SysCtlPeripheralEnable(DAC7811_GPIO_SCLK_SYSCTL);
    while(!(MAP_SysCtlPeripheralReady(DAC7811_GPIO_SCLK_SYSCTL)))
    {
    }
    MAP_GPIOPinConfigure(DAC7811_SSI_SCLK_GPIO);
    MAP_GPIOPinTypeSSI(DAC7811_SSI_SCLK_PORTBASE, DAC7811_SSI_SCLK_Pin);


    MAP_SysCtlPeripheralEnable(DAC7811_GPIO_MTX_SYSCTL);
    while(!(MAP_SysCtlPeripheralReady(DAC7811_GPIO_MTX_SYSCTL)))
    {
    }
    MAP_GPIOPinConfigure(DAC7811_SSI_MTX_GPIO);
    MAP_GPIOPinTypeSSI(DAC7811_SSI_MTX_PORTBASE, DAC7811_SSI_MTX_Pin);

    MAP_SysCtlPeripheralEnable(DAC7811_GPIO_MRX_SYSCTL);
    while(!(MAP_SysCtlPeripheralReady(DAC7811_GPIO_MRX_SYSCTL)))
    {
    }
    MAP_GPIOPinConfigure(DAC7811_SSI_MRX_GPIO);
    MAP_GPIOPinTypeSSI(DAC7811_SSI_MRX_PORTBASE, DAC7811_SSI_MRX_Pin);

    MAP_SysCtlPeripheralEnable(DAC7811_GPIO_SYNC_SYSCTL);
    while(!(MAP_SysCtlPeripheralReady(DAC7811_GPIO_SYNC_SYSCTL)))
    {
    }
    MAP_GPIOPinConfigure(DAC7811_SSI_SYNC_GPIO);
    MAP_GPIOPinTypeSSI(DAC7811_SSI_SYNC_PORTBASE, DAC7811_SSI_SYNC_Pin);                                                                         

//   SSIClockSourceSet(SSI0_BASE,SSI_CLOCK_SYSTEM);

   /* Enable the clock to SSI-0 module and configure the SSI Master */
   MAP_SysCtlPeripheralEnable(DAC7811_SSI_SYSCTL_PERIPH);
   while(!(MAP_SysCtlPeripheralReady(DAC7811_SSI_SYSCTL_PERIPH)))
   {
   }

   SSIClockSourceSet(DAC7811_SSI_BASE,SSI_CLOCK_SYSTEM); //SSI_CLOCK_SYSTEM SSI_CLOCK_ALTCLK

   MAP_SSIConfigSetExpClk(DAC7811_SSI_BASE, systemClock, SSI_FRF_MOTO_MODE_2,
                          SSI_MODE_MASTER, 30000000, 16);
//   MAP_SSIIntEnable(SSI0_BASE, SSI_TXEOT);
   MAP_SSIEnable(DAC7811_SSI_BASE);

//   SSIDMAEnable(SSI0_BASE,SSI_DMA_TX);

   /* Flush the Receive FIFO */
   while(MAP_SSIDataGetNonBlocking(DAC7811_SSI_BASE, &getResponseData));

   /* Enable the interrupt generation from SSI-0 */
   MAP_IntEnable(DAC7811_SSI_INT);

   //MAP_SSIDataPut(SSI0_BASE, txdata);
}


/**
 * @description: 将数据写入dac7811，采用硬件ssi使用spi协议方式进行。
 * @param: 想要写入的数据，有效位数12位。
 * @return {*}
 */
void DAC7811_Hard_Write(uint16_t da)

{
    da|=0x1000;//bit12=1
    da&=0x1FFF;//bit15、14、13=0 
    MAP_SSIDataPutNonBlocking(SSI0_BASE, da);

}

#endif 



/**
 * @description: 将数据写入dac7811
 * @param {uint16_t} da:想要写入的数据，有效位数12位。
 * @return {*}
 */
void DAC7811_SPI_Write(uint16_t da)
{
    #if TRANSFER_METHOD == SOFTWARE

    DAC7811_Soft_Write(da);

    #else
    DAC7811_Hard_Write(da);

    #endif

}
