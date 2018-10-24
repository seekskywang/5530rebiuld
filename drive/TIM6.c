/******************************************************************/
/* ���ƣHTIM3 PWM                                                */
/* Ч����                                                        */
/* ���ݣ�����һ��200HZ ��ռ�ձȣ�60.9% ��ռ�ձȣ�30.9%��PWM      */
/* ���ߣ�����                                                    */
/* ��ϵ��ʽ��QQ:363116119                                        */
/******************************************************************/
#include "my_register.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx.h"
#include "tim6.h"
vu8 resetflag;
/*****************************************************************/
/*****************************************************************/
// void TIM6_Config(void)
// {
// 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
// 	/* TIM3 ������ ---------------------------------------------------
//    TIM3 ����ʱ��(TIM3CLK) ����Ϊ APB2 ʱ�� (PCLK2)    
//     => TIM3CLK = PCLK2 = SystemCoreClock
//    TIM3CLK = SystemCoreClock, Prescaler = 0, TIM3 counter clock = SystemCoreClock
//    SystemCoreClock Ϊ48 MHz */
//   /* TIM16 ʱ��ʹ�� */
//   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
// 	
//   /* Time ��ʱ��������*/
//   TIM_TimeBaseStructure.TIM_Prescaler = 2;//ʱ��Ԥ��Ƶ
//   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  /* Time ��ʱ����Ϊ�����ؼ���ģʽ*/
//   TIM_TimeBaseStructure.TIM_Period = 0;
//   TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//   TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

//   TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);
// 	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);//������ʱ�������ж�
// 	TIM_SetAutoreload(TIM6, 0xFF);//����PWM�ֱ���
// 	TIM6_NVIC_Config();
//   /* TIM3 ������ʹ��*/
//   TIM_Cmd(TIM6, ENABLE);
// }
// /***********************************************************************/
// static void TIM6_NVIC_Config(void)
// {
// 	NVIC_InitTypeDef NVIC_InitStructure; 
// 	
// 	/* Enable the USART1 Interrupt */
// 	NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;	 
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
// 	NVIC_Init(&NVIC_InitStructure);
// }




void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //ÙʹŜ TIM3 ʱד
    TIM_TimeBaseInitStructure.TIM_Period = arr; //ؔ֯טװ՘ֵ
    TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //֨ʱǷؖƵ
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //вʏ݆˽ģʽ
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);// ÚԵʼۯ֨ʱǷ TIM3
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //ÛՊѭ֨ʱǷ 3 ټтא׏
    NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //֨ʱǷ 3 א׏
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //ȀռԅЈܶ 1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //ЬӦԅЈܶ 3
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);// ÜԵʼۯ NVIC
    TIM_Cmd(TIM3,ENABLE); //ÝʹŜ֨ʱǷ 3
}
//֨ʱǷ 3 א׏ؾϱگ˽
void TIM3_IRQHandler(void)
{
    static vu16 count1ms;
    static resetcount;
    static read1963;
    static scancount;
    
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //ӧԶא׏
    {
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //ȥԽא׏Ҫ־λ
        
        if(page_sw != face_starter)
        {
             if(resetflag == 1)
             {
                 if(resetcount == 1000)
                 {
                     LCD_Initializtion();
                     GUI_Init();
                     if(page_sw == face_menu)
                     {
                         ResetPow();
                     }else if(page_sw == face_cdc){
                         ResetCDC();
                     }else if(page_sw == face_r){
                         ResetR();
                     }else if(page_sw == face_load){
                         ResetLoad();
                     }else if(page_sw == face_graph){
                         ResetG();
                     }else if(page_sw == face_set){
                         ResetSET();
                     }
                     resetcount = 0;
                 }else{
                     resetcount++;
                 }                
             }
         }
        switch(page_sw)
        {
            case face_menu:
            {                
                if(pow_sw == pow_on)
                {
                    count1ms++;
                    if(count1ms == 1000)
                    {
                        bc_raw += DISS_POW_Current * 1000 * 1/3600;
                        count1ms = 0;
                    }
                }else{
                    bc_raw = 0;
                    count1ms = 0;
                }
            }break;
            case face_cdc:
            {
                if(mode_sw == mode_pow && cdc_sw == cdc_on)
                {
                    count1ms++;
                    if(count1ms == 1000)
                    {
                        bc_raw += DISS_POW_Current * 1000 * 1/3600;
                        count1ms = 0;
                    }
                }else if(cdc_sw == cdc_off){
                    bc_raw = 0;
                    count1ms = 0;
                }
            }break;
            case face_load:
            {
                if(load_sw == load_on)
                {
                    count1ms++;
                    if(count1ms == 1000)
                    {
                        bc_raw += DISS_Current * 1000 * 1/3600;
                        count1ms = 0;
                    }
                }else{
                    bc_raw = 0;
                    count1ms = 0;
                }
            }break;
            case face_graph:
            {
                if(mode_sw == mode_pow)
                {
                    if(pow_sw == pow_on)
                    {
                        count1ms++;
                        if(count1ms == 1000)
                        {
                            bc_raw += DISS_POW_Current * 1000 * 1/3600;
                            count1ms = 0;
                        }
                    }else if(mode_sw == mode_pow && cdc_sw == cdc_on)
                    {
                        count1ms++;
                        if(count1ms == 1000)
                        {
                            bc_raw += DISS_POW_Current * 1000 * 1/3600;
                            count1ms = 0;
                        }
                    }
                    else{
                        bc_raw = 0;
                        count1ms = 0;
                    }
                }               
                
                if(mode_sw == mode_load)
                {
                    if(load_sw == load_on)
                    {
                        count1ms++;
                        if(count1ms == 1000)
                        {
                            GPIO_ResetBits(GPIOC,GPIO_Pin_1);
                            bc_raw += DISS_Current * 1000 * 1/3600;
                            count1ms = 0;
                        }
                    }else{
                        bc_raw = 0;
                        count1ms = 0;
                    }
                }
            }break;
            case face_r:
            {                     
                if(oct_sw == oct_on && para_set2 == set_2_on)
                {
                    count1ms ++;
                    if(count1ms == steptime)
                    {
                        OC_ADD();
                        count1ms = 0;
                    }
                }
            }break;
        }
    }    
    
}
