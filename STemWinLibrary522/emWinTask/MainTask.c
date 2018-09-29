/******************************************************************/
/* 名称：                                                  				*/
/* 效果：                                                        */
/* 内容：内阻仪界面                                              */
/* 作者：zhan                                                  */
/* 联系方式QQ:363116119                                        */

#include "MainTask.h"
#include  "gui.h"
#include  "adc.h"
#include  "tim2.h"
#include  "key.h"
#include  "beep.h"
#include "my_register.h"
#include "stm32f4xx_dac.h"
#include "modbus.h"
#include "ssd1963.h"
#include "tm1650.h"
extern struct bitDefine
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

extern GUI_CONST_STORAGE GUI_FONT GUI_FontHZ16;
extern WM_HWIN CreateWindow(void);
extern WM_HWIN CreateR(void);
extern vu8 resetflag;
/**********************************************************************************************************
*	�� �� ��: MainTask
*	����˵��: GUI������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void MainTask(void) 
{ 
    static resetcount;
    static read1963;
    static scancount;
//	unsigned char  ucKeyCode;
	GUI_Init();
	WM_SetDesktopColor(GUI_BLUE);  
	GUI_Clear();//清屏
	WM_SetCreateFlags(WM_CF_MEMDEV);
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
    CreateSTARTER();
//	CreateR();//开机进入内阻测试界面
	Flag_Swtich_ON=0;
	while (1)
	{
//         TM1650_SET_LED(0x68,0x70);//FAIL灯
//         GPIO_SetBits(GPIOD,GPIO_Pin_12);//
        if(page_sw != face_starter)
        {
            if(scancount == 10)
            {
                sLCD_WR_REG(0xf1);
                read1963 =sLCD_Read_Data();
                scancount = 0;
            }else{
                scancount++;
            }
             if(read1963 != 0x03)
             {
                 resetflag = 1;               
             }else{
                 resetflag = 0; 
             }
         }
		DAC_SetChannel1Data(DAC_Align_12b_R,Contr_Laod);//负载DAC控制
		TIM_SetCompare1(TIM2,Contr_Current);//电源电流控制
		TIM_SetCompare2(TIM2,Contr_Voltage);//电源电压控制
		if(Flag_DAC_OFF==0)
		{
			Transformation_ADC();
		}
		if(Flag_ADC_Full==1)
		{
			Flag_ADC_Full=0;
			ADC_CH_Scan();//ADC扫描
		}
		if(UART_Buffer_Rece_flag==1)
		{
			UART_Buffer_Rece_flag=0;
			UART_Action();
		}
		if(Flag_Key_Scan==1)
		{
			Flag_Key_Scan=0;
			NewKey=TM1650_Read_KEY();
			Flag_Key_Scan = 1;
		}
		Key_Funtion();//按键处理
		Temp_Comapre();//风扇控制
		BEEP_Ring();//蜂鸣器控制
		GUI_Delay(2);//GUI刷新
	}
  
}
/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
