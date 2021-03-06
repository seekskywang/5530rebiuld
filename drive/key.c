/******************** (C) COPYRIGHT 2015 AVER********************
 * 文件名  ：KEY.C
 * 作者    ：李振
 * 描述    ：3*2矩阵键盘扫描
 * 内容    ：扫描完成后出键值
 * 硬件连接：一路3*2矩阵键盘  一路编码器独立按键
 * 修改日期：2015-08-18
********************************************************************/
#include "my_register.h"
#include "beep.h"
#include "flash.h"
#include "gpio.h"
#include "key.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include  "gui.h"
#include "MainTask.h"
#include "ssd1963.h"

extern WM_HWIN CreateR(void);
extern WM_HWIN CreateWindow2(void);
extern WM_HWIN CreateWindow(void);
extern WM_HWIN CreateG(void);
extern WM_HWIN CreateSET(void);
extern WM_HWIN ResetPow(void);
extern WM_HWIN hWinWind;
extern WM_HWIN hWinR;
extern WM_HWIN load_wind;//璐熻浇鐣岄潰鍙ユ焺
extern WM_HWIN hWinG;
extern WM_HWIN hWinset;
extern WM_HWIN hWincdc;
extern WM_HWIN hWinsysinfo;
//=================================================================
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
//====================================================================

vu8 t_KeyScan;
vu8 NewKey;
vu8 t_wei;
vu8 t_beep;
vu8 t_Str;
vu8 t_lock;
vu8 t_onoff;
vu8 t_doub;
vu8 t_key_step;//閿洏鎵弿璁℃暟鍣�
vu16 KeyCounter;
vu8 OFFSET_Zore;//零点值
vu8 pass = 0;
vu8 LOAD_t;
vu8 track;
vu8 clear_flag1 = 0;
vu8 clear_flag2 = 0;
vu8 clear_flag3 = 0;
vu16 menu_time;
vu16 load_time;
vu8 r_test = 0;
float clear_v = 0;
//float clear_pv = 0;
float clear_lv = 0;
vu8 clear_r = 0;
vu8 mode_sw;
extern vu8 admin;
extern vu8 cal;

vu32 Key_Scan(void);
void Lift_Move(void);
void Right_Move(void);
void Setvalue_Add(void);
/* 閿�煎畾涔� */
#define        KEY_1                		 0X4E     //
#define        KEY_2                		 0X56     //
#define        KEY_3                		 0X5E     //
#define        KEY_4                		 0X57      //
#define        KEY_5                		 0X5F      //
#define        KEY_6                		 0X76      //
#define        KEY_7                		 0X67     //
#define        KEY_8                		 0X6F      //
#define        KEY_9                		 0X77     //
#define        KEY_0                		 0X5D      //
#define        KEY_dian              		 0X65     //
#define        KEY_ESC              		 0X6D     //

#define        ENTER                     0X4D    //
#define        PUSH_Lift                 0X45     //
#define        PUSH_Right                0X55      //
#define        PUSH_Up                   0X46      //
#define        PUSH_Down                 0X74      //
#define        PUSH_DISP                 0X47      //
#define        PUSH_SETUP                0X4F     //

#define        KEY_Lock                  0X75     //
#define        KEY_BIAS                  0X6E      //
#define        KEY_Reset                 0X66      //
#define        KEY_TRIG                  0X75      //

#define        KEY_Powe                  0X6C     //
#define        KEY_Face1                 0X64      //
#define        KEY_Face2                 0X5c      //
#define        KEY_Face3                 0X54      //
#define        KEY_Face4                 0X4c      //
#define        KEY_Face5                 0X44      //

/* 瀹氫箟鎸夐敭鍔ㄤ綔 */
#define        KEY_NULL_VALUE             0X00    //无动作
#define        KEY_PRESS                  0X10    //单击
#define        KEY_LONG                   0X20    //长按
#define        KEY_CONTINUE               0X40    //连击
#define        KEY_UP                     0X80    //按键抬起
/*瀹氫箟鎸夐敭澶勭悊姝ラ*/
#define        KEY_INIT_STATE               0      //初态
#define        KEY_WOBBLE_STATE             1      //消抖
#define        KEY_PRESS_STATE              2      //触发单键
#define        KEY_LONG_STATE               3      //长按触发
#define        KEY_CONTINUE_STATE           4      //连续触发
#define        KEY_RELEASE_STATE            5      //恢复初态
/* 闀挎寜鏃堕棿 */
#define         KEY_LONG_PERIOD             50                /* 长按时间1S */
#define        KEY_CONTINUE_PERIOD          10                /* 双击时间500ms */

/************************************************************************************************************************/
vu32 Key_Scan(void)
{
	static vu8 KeyState = KEY_INIT_STATE;
	static vu8 IsKeyRelease = 1;

	static vu8 KeyValueTemp = 0;
	vu8 KeyValue ;
	KeyValue= KEY_NULL_VALUE;
	
	if((NewKey>0x37)&&(IsKeyRelease==1))
	{
		if(KeyState == KEY_INIT_STATE)                    /*蠟写菁写袀*/
		{
			KeyState = KEY_WOBBLE_STATE;
			return KEY_NULL_VALUE;
		}
		else if(KeyState == KEY_WOBBLE_STATE)                /* 谢侄 */
		{
			KeyState = KEY_PRESS_STATE;
			return KEY_NULL_VALUE;
		}
		else if(KeyState == KEY_PRESS_STATE)                /* 詯写菁写袀矛椎軜写菁值 */
		{
			KeyValue = NewKey;
			KeyValueTemp = KeyValue;
			KeyState = KEY_CONTINUE_STATE;
			return KeyValue;
		}
		else if(KeyState == KEY_CONTINUE_STATE)           /*双芊写菁*/
		{
			KeyCounter ++;
			if(KeyCounter == KEY_CONTINUE_PERIOD)
			{
				 KeyCounter = 0;
				 KeyState = KEY_LONG_STATE;
			}
		}
		else if(KeyState == KEY_LONG_STATE)                        /* 婴写写菁 */
		{
			KeyCounter ++;
			if(KeyCounter == KEY_LONG_PERIOD)
			{
				KeyCounter = 0;
				Flag_Long=1; //婴写豫注要志位
			}
		}
	}
	else if(NewKey<=0x37)
	{
		KeyState = KEY_INIT_STATE;        /* 铣豫注矛椎軜战缘始状态 */
		IsKeyRelease = 1;
		Flag_Long=0;
	}
	return KEY_NULL_VALUE;
}

/************************************************************************************************************************/
void Key_Funtion(void)
{
	vu32 KeyValue = 0;
	static vu8 t_KEYON;
	static vu8 a,b;
/****************************************************鐭寜鍔熻兘************************************************************/
	if(Flag_Key_Scan==1)
	{
		Flag_Key_Scan = 0;
		KeyValue = Key_Scan();
		switch(KeyValue)
		{
			case KEY_1 ://
			{
                switch(page_sw){
                    case face_menu: 
                    {
                        INPUT_POW("1");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_set:
                    {
                         INPUT_NUM("1");
                         KeyCounter = 0;
                         BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                         break;
                    }
                    case face_r:
                    {
                        if(para_set2 == set_2_on)
                        {
                            INPUT_C("1");
                            KeyCounter = 0;
                            BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                            break;
                        }
                    }   
                    case face_load:
                    {
                        INPUT_LOAD("1");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_cdc:
                    {
                        INPUT_CDC("1");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_sys_info:
                    {
                        if(admin == 1)
                        {
                            INPUT_INFO(1);    
                        }else if(cal == 1){
                            Rlow_cal(1);
                        }else{
                            pass += 1;
                        }
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }  
                }
			}
			break;
			
			case KEY_2 ://
			{
                 switch(page_sw){
                    case face_menu:  
                    {
                        INPUT_POW("2");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣� 
                    }
                    case face_set:
                    {
                        INPUT_NUM("2");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_r:
                    {
                        if(para_set2 == set_2_on)
                        {
                            INPUT_C("2");
                            KeyCounter = 0;
                            BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                            break;
                        }
                    }
                    case face_load:
                    {
                        INPUT_LOAD("2");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_cdc:
                    {
                        INPUT_CDC("2");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_sys_info:
                    {
                        if(admin == 1)
                        {
                            INPUT_INFO(2);    
                        }else if(cal == 1){
                            Rlow_cal(2);
                        }else{
                            pass += 2;
                        }
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
   
                }
			}
			break;
			
			case KEY_3 ://
			{
				switch(page_sw){
                    case face_menu:  
                    {
                        INPUT_POW("3");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣� 
                    }
                    case face_set:
                    {
                        INPUT_NUM("3");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_r:
                    {
                        if(para_set2 == set_2_on)
                        {
                            INPUT_C("3");
                            KeyCounter = 0;
                            BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                            break;
                        }
                    }
                    case face_load:
                    {
                        INPUT_LOAD("3");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_cdc:
                    {
                        INPUT_CDC("3");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_sys_info:
                    {
                        if(admin == 1)
                        {
                            INPUT_INFO(3);    
                        }else if(cal == 1){
                            Rhigh_cal(3);
                        }else{
                            pass += 3;
                        }
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                }
			}
			break;
			
			case KEY_4 ://
			{
				switch(page_sw){
                    case face_menu:  
                    {
                        INPUT_POW("4");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣� 
                    }
                    case face_set:
                    {
                        INPUT_NUM("4");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_r:
                    {
                        if(para_set2 == set_2_on)
                        {
                            INPUT_C("4");
                            KeyCounter = 0;
                            BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                            break;
                        }
                    }
                    case face_load:
                    {
                        INPUT_LOAD("4");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_cdc:
                    {
                        INPUT_CDC("4");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_sys_info:
                    {
                        if(admin == 1)
                        {
                            INPUT_INFO(4);    
                        }else if(cal == 1){
                            Rhigh_cal(4);
                        }else{
                            pass += 4;
                        }
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                }
			}
			break;
			
			case KEY_5 ://
			{
				switch(page_sw){
                    case face_menu:  
                    {
                        INPUT_POW("5");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣� 
                    }
                    case face_set:
                    {
                        INPUT_NUM("5");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_r:
                    {
                        if(para_set2 == set_2_on)
                        {
                            INPUT_C("5");
                            KeyCounter = 0;
                            BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                            break;
                        }
                    }
                    case face_load:
                    {
                        INPUT_LOAD("5");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_cdc:
                    {
                        INPUT_CDC("5");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_sys_info:
                    {
                        if(admin == 1)
                        {
                            INPUT_INFO(5);    
                        }else{
                            pass += 5;
                        }
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                }
			}
			break;	
			
			case KEY_6 ://
			{
				switch(page_sw){
                    case face_menu:  
                    {
                        INPUT_POW("6");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣� 
                    }
                    case face_set:
                    {
                        INPUT_NUM("6");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_r:
                    {
                        if(para_set2 == set_2_on)
                        {
                            INPUT_C("6");
                            KeyCounter = 0;
                            BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                            break;
                        }
                    }
                    case face_load:
                    {
                        INPUT_LOAD("6");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_cdc:
                    {
                        INPUT_CDC("6");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    } 
                    case face_sys_info:
                    {
                        if(admin == 1)
                        {
                            INPUT_INFO(6);    
                        }
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                }
			}
			break;
			
			case KEY_7 ://
			{
				switch(page_sw){
                    case face_menu:  
                    {
                        INPUT_POW("7");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣� 
                    }
                    case face_set:
                    {
                        INPUT_NUM("7");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_r:
                    {
                        if(para_set2 == set_2_on)
                        {
                            INPUT_C("7");
                            KeyCounter = 0;
                            BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                            break;
                        }
                    }
                    case face_load:
                    {
                        INPUT_LOAD("7");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_cdc:
                    {
                        INPUT_CDC("7");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_sys_info:
                    {
                        if(admin == 1)
                        {
                            INPUT_INFO(7);    
                        }
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                }
			}
			break;
			
			case KEY_8 ://
			{
				switch(page_sw){
                    case face_menu:  
                    {
                        INPUT_POW("8");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣� 
                    }
                    case face_set:
                    {
                        INPUT_NUM("8");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_r:
                    {
                        if(para_set2 == set_2_on)
                        {
                            INPUT_C("8");
                            KeyCounter = 0;
                            BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                            break;
                        }
                    }
                    case face_load:
                    {
                        INPUT_LOAD("8");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_cdc:
                    {
                        INPUT_CDC("8");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_sys_info:
                    {
                        if(admin == 1)
                        {
                            INPUT_INFO(8);    
                        }
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                }
			}
			break;
			
			case KEY_9 ://
			{
				switch(page_sw){
                    case face_menu:  
                    {
                        INPUT_POW("9");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣� 
                    }
                    case face_set:
                    {
                        INPUT_NUM("9");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_r:
                    {
                        if(para_set2 == set_2_on)
                        {
                            INPUT_C("9");
                            KeyCounter = 0;
                            BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                            break;
                        }
                    }
                    case face_load:
                    {
                        INPUT_LOAD("9");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_cdc:
                    {
                        INPUT_CDC("9");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_sys_info:
                    {
                        if(admin == 1)
                        {
                            INPUT_INFO(9);    
                        }
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                }
			}
			break;
			
			case KEY_0 ://
			{
				switch(page_sw){
                    case face_menu:  
                    {
                        INPUT_POW("0");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣� 
                    }
                    case face_set:
                    {
                        INPUT_NUM("0");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_r:
                    {
                        if(para_set2 == set_2_on)
                        {
                            INPUT_C("0");
                            KeyCounter = 0;
                            BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                            break;
                        }
                    }
                    case face_load:
                    {
                        INPUT_LOAD("0");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_cdc:
                    {
                        INPUT_CDC("0");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_sys_info:
                    {
                        if(admin == 1)
                        {
                            INPUT_INFO(0);    
                        }else{
                            pass += 1;
                        }
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }                    
                }
			}
			break;
			
			case KEY_dian ://
			{
                switch(page_sw){
                    case face_menu:
                    {
                        INPUT_POW(".");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_set:
                    {
                        INPUT_NUM(".");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_load:
                    {
                        INPUT_LOAD(".");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_r:
                    {
                        if(para_set2 == set_2_on)
                        {
                            INPUT_C(".");
                            KeyCounter = 0;
                            BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                            break;
                        }
                    }
                    case face_cdc:
                    {
                        INPUT_CDC(".");
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }                     
                }
			}
			break;
			
			case KEY_ESC :
			{
//                LCD_Initializtion();
//                 GUI_Init();
//                 GUI_Clear();//娓呭睆
//                timer_sw = 0;
				KeyCounter = 0;
//				BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
			}
			break;
			
			case PUSH_Lift :
			{
                switch(page_sw){
                    case face_set:  //绯荤粺璁剧疆
                    {
                        SET_OP_LEFT();  //璁剧疆閫夐」鍒囨崲
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_sys_info:
                    {
                        if(admin == 1)
                        {
                            SYS_INFO_LEFT();  //璁剧疆閫夐」鍒囨崲
                        } 
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_cdc:  //绯荤粺璁剧疆
                    {
                        CDC_OP_LEFT();  //璁剧疆閫夐」鍒囨崲
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                }
			}
			break;
			case PUSH_Right :
			{
                switch(page_sw){
                    case face_set:  //绯荤粺璁剧疆
                    {
                        SET_OP_RIGHT();  //璁剧疆閫夐」鍒囨崲
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_sys_info:
                    {
                        if(admin == 1)
                        {
                            SYS_INFO_RIGHT();  //璁剧疆閫夐」鍒囨崲
                        } 
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_cdc:  //绯荤粺璁剧疆
                    {
                        CDC_OP_RIGHT();  //璁剧疆閫夐」鍒囨崲
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                }
			}
			break;
			case PUSH_Up :
			{
                switch(page_sw){
                    case face_menu:
                    {
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        MENU_OP_UP();
                        break;
                    }                    
                    case face_load:
                    {
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
//                        SET_Current_Laod=SET_Current_Laod+1;
                        break;
                    }
                    case face_set:
                    {
                        SET_OP_UP();  //璁剧疆閫夐」鍒囨崲
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_r:
                    {
                        if(para_set2 == set_2_on)
                        {
                            OC_OP_UP();
                            KeyCounter = 0;
                            BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                            break;
                        }

                    }
                    case face_cdc:
                    {
                        CDC_OP_UP();
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_sys_info:
                    {
                        if(admin == 1)
                        {
                            SYS_INFO_UP();  //璁剧疆閫夐」鍒囨崲
                        }                        
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }

                }
			}
			break;
			case PUSH_Down :
			{
                switch(page_sw){
                    case face_menu:
                    {
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        MENU_OP_DOWN();
                        break;
                    }  
                    case face_load:
                    {
                       	KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
//                        SET_Current_Laod=SET_Current_Laod-1;
                        break;
                    }
                    case face_set:  //绯荤粺璁剧疆
                    {
                        SET_OP_DOWN();  //璁剧疆閫夐」鍒囨崲
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_r:
                    {
                        if(para_set2 == set_2_on)
                        {
                            OC_OP_DOWN();
                            KeyCounter = 0;
                            BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                            break;
                        }
                    }
                    case face_cdc:
                    {
                        CDC_OP_DOWN();
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_sys_info:
                    {
                        if(admin == 1)
                        {
                            SYS_INFO_DOWN();  //璁剧疆閫夐」鍒囨崲
                        } 
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
   
                }

			}
			break;
			
			case ENTER ://
			{
                switch(page_sw){
                    case face_menu:
                    {
                        MENU_SET();
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }  
                    case face_set:
                    {
                        PARA_SET();  //鍙傛暟璁剧疆
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;                        
                    }
                    case face_r:
                    {
                        if(para_set2 == set_2_on)
                        {
                            OC_SET();
                            KeyCounter = 0;
                            BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                            break;
                        }
                    }
                    case face_load:
                    {
                        LOAD_SET();
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_cdc:
                    {
                        CDC_SET();
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_sys_info:
                    {
                        CFM_PASS();
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                }
			}
			break;
			case PUSH_DISP :
			{
                switch(track)
                {
                    case face_r:
                    {
                        WM_DeleteWindow(hWinR);
                        WM_DeleteWindow(hWinWind);
                        WM_DeleteWindow(hWinG);
                        WM_DeleteWindow(load_wind);
                        WM_DeleteWindow(hWinsysinfo);
                        WM_DeleteWindow(hWincdc);
                        WM_DeleteWindow(hWinset);                       
                        CreateR();
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_load:
                    {
                        WM_DeleteWindow(hWinR);
                        WM_DeleteWindow(hWinWind);
                        WM_DeleteWindow(hWinG);
                        WM_DeleteWindow(load_wind);
                        WM_DeleteWindow(hWinsysinfo);
                        WM_DeleteWindow(hWincdc);
                        WM_DeleteWindow(hWinset);
                        CreateWindow2();
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_menu:
                    {
                        WM_DeleteWindow(hWinR);
                        WM_DeleteWindow(hWinWind);
                        WM_DeleteWindow(hWinG);
                        WM_DeleteWindow(load_wind);
                        WM_DeleteWindow(hWinsysinfo);
                        WM_DeleteWindow(hWincdc);
                        WM_DeleteWindow(hWinset); 
                        CreateWindow();
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_graph:
                    {
                        WM_DeleteWindow(hWinR);
                        WM_DeleteWindow(hWinWind);
                        WM_DeleteWindow(hWinG);
                        WM_DeleteWindow(load_wind);
                        WM_DeleteWindow(hWinsysinfo);
                        WM_DeleteWindow(hWincdc);
                        WM_DeleteWindow(hWinset); 
                        CreateG();
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_cdc:
                    {
                        WM_DeleteWindow(hWinR);
                        WM_DeleteWindow(hWinWind);
                        WM_DeleteWindow(hWinG);
                        WM_DeleteWindow(load_wind);
                        WM_DeleteWindow(hWinsysinfo);
                        WM_DeleteWindow(hWincdc);
                        WM_DeleteWindow(hWinset);
                        CreateCDC();
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                }
                   
                
			}
			break;
			case PUSH_SETUP :
			{
				WM_DeleteWindow(hWinR);
                WM_DeleteWindow(hWinWind);
                WM_DeleteWindow(hWinG);
                WM_DeleteWindow(load_wind);
                WM_DeleteWindow(hWinsysinfo);
                WM_DeleteWindow(hWincdc);
                WM_DeleteWindow(hWinset); 
                CreateSET();
                KeyCounter = 0;
                BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
			}
			break;
			case KEY_TRIG:
			{
                switch(page_sw){
                    case face_load:
                    {
//                        static vu8 LOAD_t;
//                         LOAD_t++;
//                         if(LOAD_t>1)
//                         {
//                             LOAD_t=0;
//                         }
                        if(load_sw==load_on)
                        {
                            Flag_Swtich_ON=0;
                            GPIO_SetBits(GPIOC,GPIO_Pin_1);//OFF
                            load_sw = load_off;
                        }
                        else if(load_sw==load_off)
                        {
                            Flag_Swtich_ON=1;
                            GPIO_ResetBits(GPIOC,GPIO_Pin_1);//On
                            load_time = GUI_GetTime()/500;
                            load_sw = load_on;
                        }
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_r:
                    {
//                         if(para_set2 == set_2_on)
//                         {
// //                            static vu8 LOAD_t;
//                             Mode_SW_CONT(0x02);
//                             LOAD_t++;
//                             if(LOAD_t>1)
//                             {
//                                 LOAD_t=0;
//                             }
//                             if(LOAD_t==0)
//                             {
//                                 oct_sw = oct_off;
//                                 set_add_c = 0;
//                                 Flag_Swtich_ON=0;
//                                 GPIO_SetBits(GPIOC,GPIO_Pin_1);//OFF
//                                  
//                             }
//                             else if(LOAD_t==1)
//                             {
//                                 oct_sw = oct_on;
//                                 Flag_Swtich_ON=1;
//                                 GPIO_ResetBits(GPIOC,GPIO_Pin_1);//On
//                             }
//                          }
                         if(r_test == 0 && DISS_Voltage > gate_v)
                         {
                            r_test = 1;
                         }else{
                             r_test = 0;
                         }
                         KeyCounter = 0;
                         BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                         break;
                    }
                    case face_cdc:
                    {
                       if(cdc_sw == cdc_off)
                       {
                           SET_Voltage = opv1;
                           SET_Current = opc1;
                           cutoff_flag = 0;
                           Mode_SW_CONT(0x03);
                           
                           charge_step = 1;
                           GPIO_SetBits(GPIOB,GPIO_Pin_13);//鎵撳紑绋冲帇鐢垫簮杈撳嚭
                           cdc_sw = cdc_on;
                       }else{
                           GPIO_ResetBits(GPIOB,GPIO_Pin_13);//鍏抽棴绋冲帇鐢垫簮杈撳嚭
                           cdc_sw = cdc_off;
                           paused = 0;
                           mode_sw = 0;
                       }
                       KeyCounter = 0;
                       BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                       break; 
                    }
                    case face_menu:
                    {
//                         static vu8 POW_t;
//                         POW_t++;
//                         if(POW_t>1)
//                         {
//                             POW_t=0;
//                         }
                        if(pow_sw==pow_on)
                        {
                            GPIO_ResetBits(GPIOB,GPIO_Pin_13);//鍏抽棴绋冲帇鐢垫簮杈撳嚭
                            pow_sw = pow_off;
                        }
                        else if(pow_sw==pow_off)
                        {
                            GPIO_SetBits(GPIOB,GPIO_Pin_13);//鎵撳紑绋冲帇鐢垫簮杈撳嚭
                            pow_sw = pow_on;
                            menu_time = GUI_GetTime()/500;
                        }
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                }
				
			}
			break;
			case KEY_Reset:
			{
                switch(page_sw)
                {
                    case face_r:
                    {
                        clear_flag1 = 1;
                        finish = 0;
//                        short_finish = 0;
                        clear_r = R_VLUE;
                        clear_v = DISS_Voltage;
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_menu:
                    {
                        clear_flag2 = 1;
//                        clear_pv = DISS_POW_Voltage;
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                    case face_load:
                    {
                        clear_flag3 = 1;
                        clear_lv = DISS_Voltage;
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }   
                    case face_cdc:
                    {
                        if(mode_sw == mode_load && pause_flag == 0)
                        {
                            pause_flag = 1;
                        }else{
                            pause_flag = 0;
                            cdc_sw = cdc_on;
                            restart_time = GUI_GetTime()/500;
                            GPIO_ResetBits(GPIOC,GPIO_Pin_1);//On
                        }
                        KeyCounter = 0;
                        BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
                        break;
                    }
                }
				
			}
			break;
			case KEY_Powe :
			{
//                 TM1650_SET_LED(0x48,0x71);
//                 TM1650_SET_LED(0x68,0xF1);
// //  				TM1650_SET_LED(0x6A,0x60);
// //                 TM1650_SET_LED(0x6C,0x60);
// //                 TM1650_SET_LED(0x6E,0x60);
// 				KeyCounter = 0;
// 				BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
			}
			break;
			case KEY_Face1 :
			{                    
                    WM_DeleteWindow(hWinR);
                    WM_DeleteWindow(hWinWind);
                    WM_DeleteWindow(hWinG);
                    WM_DeleteWindow(load_wind);
                    WM_DeleteWindow(hWinsysinfo);
                    WM_DeleteWindow(hWincdc);
                    WM_DeleteWindow(hWinset);
                    CreateR();
//                    double_sw = face_graph;
                    Mode_SW_CONT(0x01);//杩涘叆鍐呴樆娴嬭瘯妯″紡
                    BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
            }
			break;
			case KEY_Face2 :
			{
				WM_DeleteWindow(hWinR);
                WM_DeleteWindow(hWinWind);
                WM_DeleteWindow(hWinG);
                WM_DeleteWindow(load_wind);
                WM_DeleteWindow(hWinsysinfo);
                WM_DeleteWindow(hWincdc);
                WM_DeleteWindow(hWinset);
				CreateWindow2();
//                double_sw = face_graph;
				Mode_SW_CONT(0x02);//杩涘叆璐熻浇妯″紡
//                GPIO_SetBits(GPIOC,GPIO_Pin_1);
				KeyCounter = 0;
				BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
			}
			break;
			case KEY_Face3 :
			{
				WM_DeleteWindow(hWinR);
                WM_DeleteWindow(hWinWind);
                WM_DeleteWindow(hWinG);
                WM_DeleteWindow(load_wind);
                WM_DeleteWindow(hWinsysinfo);
                WM_DeleteWindow(hWincdc);
                WM_DeleteWindow(hWinset);
				CreateWindow();
				Mode_SW_CONT(0x03);//杩涘叆鐢垫簮妯″紡
				KeyCounter = 0;
				BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
			}
			break;
			case KEY_Face4 :
			{

                    WM_DeleteWindow(hWinR);
                    WM_DeleteWindow(hWinWind);
                    WM_DeleteWindow(hWinG);
                    WM_DeleteWindow(load_wind);
                    WM_DeleteWindow(hWinsysinfo);
                    WM_DeleteWindow(hWincdc);
                    WM_DeleteWindow(hWinset);
                    CreateCDC();                
                    KeyCounter = 0;
                    BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
			}
			break;
			case KEY_Face5 :
			{
				    WM_DeleteWindow(hWinR);
                    WM_DeleteWindow(hWinWind);
                    WM_DeleteWindow(hWinG);
                    WM_DeleteWindow(load_wind);
                    WM_DeleteWindow(hWinsysinfo);
                    WM_DeleteWindow(hWincdc);
                    WM_DeleteWindow(hWinset);
                    CreateG();
                    KeyCounter = 0;
                    BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
			}
			break;
            case KEY_BIAS :
			{
				    WM_DeleteWindow(hWinR);
                    WM_DeleteWindow(hWinWind);
                    WM_DeleteWindow(hWinG);
                    WM_DeleteWindow(load_wind);
                    WM_DeleteWindow(hWinsysinfo);
                    WM_DeleteWindow(hWincdc);
                    WM_DeleteWindow(hWinset);
                    Createsysinfo();
                    KeyCounter = 0;
                    BEEP_Tiggr();//瑙﹀彂铚傞福鍣�
			}
			break;
			
			default:
			break;
		}	
	}
}

/********************************************************************************/
void Mode_SW_CONT(vu8 mode)//模式葠刍酄樧�
{
	switch(mode)
	{
		case 0x01 ://艢亘英藬模式
		{
			GPIO_ResetBits(GPIOE,GPIO_Pin_2);
			GPIO_ResetBits(GPIOE,GPIO_Pin_3);
            mode_sw = mode_r;
		}
		break;
		case 0x02 ://睾諛模式
		{
			GPIO_SetBits(GPIOE,GPIO_Pin_2);
			GPIO_ResetBits(GPIOE,GPIO_Pin_3);
            mode_sw = mode_load;
		}
		break;
		case 0x03 ://直路支源模式
		{
			GPIO_ResetBits(GPIOE,GPIO_Pin_2);//
			GPIO_SetBits(GPIOE,GPIO_Pin_3);//
            mode_sw = mode_pow;
		}
		break;
		default:
		break;
	}
}
