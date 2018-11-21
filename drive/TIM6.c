/******************************************************************/
/* 名称TIM3 PWM                                                */
/* 效果：                                                        */
/* 内容：产生一个200HZ 正占空比：60.9% 负占空比：30.9%的PWM      */
/* 作者：李振                                                    */
/* 联系方式：QQ:363116119                                        */
/******************************************************************/
#include "my_register.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx.h"
#include "tim6.h"
void MODS_Poll(void);

vu8 resetflag;
extern u8 g_mods_timeout;
extern struct MODS_T g_tModS;
u32 Tick_10ms=0;
u32 OldTick;
u8 usartocflag = 0;//涓婁綅鏈鸿繃娴佹爣蹇椾綅
u8 usartshortflag = 0;//涓婁綅鏈虹煭璺爣蹇椾綅
/*****************************************************************/
/*****************************************************************/
// void TIM6_Config(void)
// {
// 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
// 	/* TIM3 的配置 ---------------------------------------------------
//    TIM3 输入时钟(TIM3CLK) 设置为 APB2 时钟 (PCLK2)    
//     => TIM3CLK = PCLK2 = SystemCoreClock
//    TIM3CLK = SystemCoreClock, Prescaler = 0, TIM3 counter clock = SystemCoreClock
//    SystemCoreClock 为48 MHz */
//   /* TIM16 时钟使能 */
//   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
// 	
//   /* Time 定时基础设置*/
//   TIM_TimeBaseStructure.TIM_Prescaler = 2;//时钟预分频
//   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  /* Time 定时设置为上升沿计算模式*/
//   TIM_TimeBaseStructure.TIM_Period = 0;
//   TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//   TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

//   TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);
// 	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);//开启定时器更新中断
// 	TIM_SetAutoreload(TIM6, 0xFF);//设置PWM分辨率
// 	TIM6_NVIC_Config();
//   /* TIM3 计算器使能*/
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
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //脵使艤 TIM3 时讚
    TIM_TimeBaseInitStructure.TIM_Period = arr; //財织讟装諛值
    TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //吱时欠貣频
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //胁蕪輪私模式
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);// 脷缘始郫吱时欠 TIM3
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //脹諍循吱时欠 3 偌褌讗讖
    NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //吱时欠 3 讗讖
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //葊占詤袌芏 1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //鞋应詤袌芏 3
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);// 脺缘始郫 NVIC
    TIM_Cmd(TIM3,ENABLE); //脻使艤吱时欠 3
}
//吱时欠 3 讗讖鼐媳诏私
void TIM3_IRQHandler(void)
{
    static vu16 count1ms;
    static resetcount;
    static read1963;
    static scancount;
    
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //缨远讗讖
    {
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //去越讗讖要志位
        
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

void TIM5_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE); //脵使艤 TIM3 时讚
    TIM_TimeBaseInitStructure.TIM_Period = arr; //財织讟装諛值
    TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //吱时欠貣频
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //胁蕪輪私模式
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);// 脷缘始郫吱时欠 TIM3
    TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //脹諍循吱时欠 3 偌褌讗讖
    NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //吱时欠 3 讗讖
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //葊占詤袌芏 1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02; //鞋应詤袌芏 3
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);// 脺缘始郫 NVIC
    TIM_Cmd(TIM5,ENABLE); //脻使艤吱时欠 3
}


void TIM5_IRQHandler(void)
{
    
    if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //缨远讗讖
    {
        TIM_ClearITPendingBit(TIM5,TIM_IT_Update); //娓呴櫎涓柇鏍囧織浣?
        Tick_10ms ++;
        MODS_Poll();
    }
}

void MODS_Poll(void)
{
	uint16_t addr;
	static uint16_t crc1;
    static u32 testi;
	/* 瓒呰繃3.5涓瓧绗︽椂闂村悗鎵цMODH_RxTimeOut()鍑芥暟銆傚叏灞�鍙橀噺 g_rtu_timeout = 1; 閫氱煡涓荤▼搴忓紑濮嬭В鐮?*/
//	if (g_mods_timeout == 0)	
//	{
//		return;								/* 娌℃湁瓒呮椂锛岀户缁帴鏀躲�備笉瑕佹竻闆?g_tModS.RxCount */
//	}

    testi=g_tModS.RxCount;
    testi=g_tModS.RxCount;
    testi=g_tModS.RxCount;
	if(testi>7)				/* 接收到的数据小于4个字节就认为错误 */
	{
		testi=testi;
	}
	testi=g_tModS.RxCount;
    if(testi==8)				/* 接收到的数据小于4个字节就认为错误 */
	{
		testi=testi+1;
	}
	//判断通讯接收是否超时
	if(OldTick!=Tick_10ms)
  	{  
	  OldTick=Tick_10ms;
	   if(g_mods_timeout>0)
      { 
	    g_mods_timeout--;
      }
	  if(g_mods_timeout==0 && g_tModS.RxCount>0)   //有数但超时了
      { 
		// goto err_ret;
	
      }
      else if(g_mods_timeout==0 && g_tModS.RxCount==0) //没数超时了
         return;
      else //没超时了，继续收
         return;
	}
	else   //没有到10ms，不进入解析
		return;
	//g_mods_timeout = 0;	 					/* 清标志 */

	if (g_tModS.RxCount < 4)				/* 接收到的数据小于4个字节就认为错误 */
	{
		goto err_ret;
	}

	/* 计算CRC校验和 */
	crc1 = CRC16(g_tModS.RxBuf, g_tModS.RxCount);
	if (crc1 != 0)
	{
		goto err_ret;
	}

// 	/* 站地址 (1字节） */
// 	addr = g_tModS.RxBuf[0];				/* 第1字节 站号 */
// 	if (addr != SADDR485)		 			/* 判断主机发送的命令地址是否符合 */
// 	{
// 		goto err_ret;
// 	}

	/* 鍒嗘瀽搴旂敤灞傚崗璁?*/
    if(UART_Buffer_Rece[2] == 0xA5)
    {
        UART_Action();
    }else{
        usartocflag = 1;
        RecHandle();
    }
							
	
err_ret:
#if 0										/* 姝ら儴鍒嗕负浜嗕覆鍙ｆ墦鍗扮粨鏋?瀹為檯杩愮敤涓彲涓嶈 */
	g_tPrint.Rxlen = g_tModS.RxCount;
	memcpy(g_tPrint.RxBuf, g_tModS.RxBuf, g_tModS.RxCount);
#endif
	
 	g_tModS.RxCount = 0;					/* 蹇呴』娓呴浂璁℃暟鍣紝鏂逛究涓嬫甯у悓姝?*/
}


