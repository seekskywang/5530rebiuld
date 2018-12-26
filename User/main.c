/******************************************************************/
/* 名称：main                                                    */
/* 效果：                                                        */
/* 内容：                                                       */
/* 作者：zhan                                                  */
/* 联系方式QQ:363116119                                        */
/******************************************************************/
#include "my_register.h"
#include "stm32f4xx.h"
#include "clock.h"
#include "tim6.h"
#include "tim1.h"
#include "tim2.h"
#include "dac.h"
#include "adc.h"
#include "clock.h"
#include "gpio.h"
#include "bsp_SysTick.h"
#include "usart.h"
#include "ssd1963.h"
#include "iwdg.h"
#include "MainTask.h"
#include "IIC_24C01.h"
#include "flash.h"
#include "tm1650.h"

float DISS_Voltage;//负载电压
float DISS_POW_Voltage;//稳压电源电压
float DISS_Current;//负载电流
float DISS_POW_Current;//稳压电源电流


struct bitDefine
{
    unsigned bit0: 1;
    unsigned bit1: 1;
    unsigned bit2: 1;
    unsigned bit3: 1;
    unsigned bit4: 1;
    unsigned bit5: 1;
    unsigned bit6: 1;
    unsigned bit7: 1;
} flagA, flagB,flagC,flagD,flagE,flagF,flagG;

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);//开启CRC时钟，STEMWIN授权使用
	RCC_Configuration();
	SysTick_Init();
	GPIO_Conf();
	TIM1_PWM_Config();
	TIM2_PWM_Config();
//    TIM5_Int_Init(100-1,8400-1);
//	TIM6_Config();
    TIM3_Int_Init(10-1,8400-1);
	ADC1_DMA_Init();
	DAC_Config();
	USART_Configuration();
	i2c_CfgGpio();//24C01引脚初始化
	TM1650_GPIO_INT();		/*TM1650引脚初始化 */
	LCD_Initializtion();//液晶屏初始化
	EEPROM_READ_Coeff();//读取校准参数
	//IWDG_Inte();
	MainTask();
}


/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/
