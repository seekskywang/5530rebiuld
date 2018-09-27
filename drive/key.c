/******************** (C) COPYRIGHT 2015 AVER********************
 * ÎÄ¼şÃû  £ºKEY.C
 * ×÷Õß    £ºÀîÕñ
 * ÃèÊö    £º3*2¾ØÕó¼üÅÌÉ¨Ãè
 * ÄÚÈİ    £ºÉ¨ÃèÍê³Éºó³ö¼üÖµ
 * Ó²¼şÁ¬½Ó£ºÒ»Â·3*2¾ØÕó¼üÅÌ  Ò»Â·±àÂëÆ÷¶ÀÁ¢°´¼ü
 * ĞŞ¸ÄÈÕÆÚ£º2015-08-18
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
extern WM_HWIN hWinWind;
extern WM_HWIN hWinR;
extern WM_HWIN load_wind;//è´Ÿè½½ç•Œé¢å¥æŸ„
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
vu8 t_key_step;//é”®ç›˜æ‰«æè®¡æ•°å™¨
vu16 KeyCounter;
 vu8 OFFSET_Zore;//ÁãµãÖµ

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
float clear_pv = 0;
float clear_lv = 0;
vu8 clear_r = 0;
vu8 mode_sw;


vu32 Key_Scan(void);
void Lift_Move(void);
void Right_Move(void);
void Setvalue_Add(void);
/* é”®å€¼å®šä¹‰ */
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

/* å®šä¹‰æŒ‰é”®åŠ¨ä½œ */
#define        KEY_NULL_VALUE             0X00    //ÎŞ¶¯×÷
#define        KEY_PRESS                  0X10    //µ¥»÷
#define        KEY_LONG                   0X20    //³¤°´
#define        KEY_CONTINUE               0X40    //Á¬»÷
#define        KEY_UP                     0X80    //°´¼üÌ§Æğ
/*å®šä¹‰æŒ‰é”®å¤„ç†æ­¥éª¤*/
#define        KEY_INIT_STATE               0      //³õÌ¬
#define        KEY_WOBBLE_STATE             1      //Ïû¶¶
#define        KEY_PRESS_STATE              2      //´¥·¢µ¥¼ü
#define        KEY_LONG_STATE               3      //³¤°´´¥·¢
#define        KEY_CONTINUE_STATE           4      //Á¬Ğø´¥·¢
#define        KEY_RELEASE_STATE            5      //»Ö¸´³õÌ¬
/* é•¿æŒ‰æ—¶é—´ */
#define         KEY_LONG_PERIOD             50                /* ³¤°´Ê±¼ä1S */
#define        KEY_CONTINUE_PERIOD          10                /* Ë«»÷Ê±¼ä500ms */

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
		if(KeyState == KEY_INIT_STATE)                    /*ÎŞ°´¼ü°´ÏÂ*/
		{
			KeyState = KEY_WOBBLE_STATE;
			return KEY_NULL_VALUE;
		}
		else if(KeyState == KEY_WOBBLE_STATE)                /* Ïû¶¶ */
		{
			KeyState = KEY_PRESS_STATE;
			return KEY_NULL_VALUE;
		}
		else if(KeyState == KEY_PRESS_STATE)                /* ÓĞ°´¼ü°´ÏÂ£¬·µ»Ø°´¼üÖµ */
		{
			KeyValue = NewKey;
			KeyValueTemp = KeyValue;
			KeyState = KEY_CONTINUE_STATE;
			return KeyValue;
		}
		else if(KeyState == KEY_CONTINUE_STATE)           /*Ë«»÷°´¼ü*/
		{
			KeyCounter ++;
			if(KeyCounter == KEY_CONTINUE_PERIOD)
			{
				 KeyCounter = 0;
				 KeyState = KEY_LONG_STATE;
			}
		}
		else if(KeyState == KEY_LONG_STATE)                        /* ³¤°´°´¼ü */
		{
			KeyCounter ++;
			if(KeyCounter == KEY_LONG_PERIOD)
			{
				KeyCounter = 0;
				Flag_Long=1; //³¤°´´¥·¢±êÖ¾Î»
			}
		}
	}
	else if(NewKey<=0x37)
	{
		KeyState = KEY_INIT_STATE;        /* Îó´¥·¢£¬·µ»Øµ½³õÊ¼×´Ì¬ */
		IsKeyRelease = 1;
		Flag_Long=0;
	}
	return KEY_NULL_VALUE;
}
/***************************************************************************************************************************/
void Key_Funtion(void)
{
	vu32 KeyValue = 0;
	static vu8 t_KEYON;
	static vu8 a,b;
/****************************************************çŸ­æŒ‰åŠŸèƒ½************************************************************/
	if(Flag_Key_Scan==1)
	{
		Flag_Key_Scan = 0;
		KeyValue = Key_Scan();
		switch(KeyValue)
		{
			case KEY_1 ://
			{
				SET_Voltage=1000;
				SET_Current=4000;
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			
			case KEY_2 ://
			{
				SET_Voltage=420;
				SET_Current=1000;
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			
			case KEY_3 ://
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			
			case KEY_4 ://
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			
			case KEY_5 ://
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;	
			
			case KEY_6 ://
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			
			case KEY_7 ://
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			
			case KEY_8 ://
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			
			case KEY_9 ://
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			
			case KEY_0 ://
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			
			case KEY_dian ://
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			
			case KEY_ESC :
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			
			case PUSH_Lift :
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			case PUSH_Right :
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			case PUSH_Up :
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
				SET_Current_Laod=SET_Current_Laod+1;
			}
			break;
			case PUSH_Down :
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
				SET_Current_Laod=SET_Current_Laod-1;
			}
			break;
			
			case ENTER ://
			{
                LCD_Initializtion();
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			case PUSH_DISP :
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			case PUSH_SETUP :
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			case KEY_TRIG:
			{
				t_onoff++;
				if(t_onoff>1)
				{
					t_onoff=0;
				}
				if(t_onoff==0)
				{
					Flag_Swtich_ON=0;
					GPIO_SetBits(GPIOC,GPIO_Pin_1);//OFF
					
				}
				else if(t_onoff==1)
				{
					Flag_Swtich_ON=1;
					GPIO_ResetBits(GPIOC,GPIO_Pin_1);//On
				}
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			case KEY_Reset:
			{
				static vu8 POW_t;
				POW_t++;
				if(POW_t>1)
				{
					POW_t=0;
				}
				if(POW_t==0)
				{
					GPIO_ResetBits(GPIOB,GPIO_Pin_13);//å…³é—­ç¨³å‹ç”µæºè¾“å‡º
				}
				else if(POW_t==1)
				{
					GPIO_SetBits(GPIOB,GPIO_Pin_13);//æ‰“å¼€ç¨³å‹ç”µæºè¾“å‡º
				}
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			case KEY_Powe :
			{
				
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			case KEY_Face1 :
			{
				WM_DeleteWindow(hWinWind);
				WM_DeleteWindow(hWinR);
				CreateR();
				Mode_SW_CONT(0x01);//è¿›å…¥å†…é˜»æµ‹è¯•æ¨¡å¼
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			case KEY_Face2 :
			{
				WM_DeleteWindow(hWinR);
				WM_DeleteWindow(hWinWind);
				CreateWindow2();
				Mode_SW_CONT(0x02);//è¿›å…¥è´Ÿè½½æ¨¡å¼
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			case KEY_Face3 :
			{
				WM_DeleteWindow(hWinR);
				WM_DeleteWindow(hWinWind);
				CreateWindow();
				Mode_SW_CONT(0x03);//è¿›å…¥ç”µæºæ¨¡å¼
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			case KEY_Face4 :
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			case KEY_Face5 :
			{
				KeyCounter = 0;
				BEEP_Tiggr();//è§¦å‘èœ‚é¸£å™¨
			}
			break;
			
			default:
			break;
		}	
	}
}
// /***************************************************************************************************************************/
// void Lift_Move(void)
// {
// 	t_wei++;
// 	if(t_wei>3)
// 	{
// 		t_wei=0;
// 	}
// 	if(t_wei==0)
// 	{
// 		Flag_QIAN=1;
// 		Flag_GE=0;
// 		Flag_SHI=0;
// 		Flag_BAI=0;
// 	}
// 	else if(t_wei==1)
// 	{
// 		Flag_GE=1;
// 		Flag_QIAN=0;
// 		Flag_SHI=0;
// 		Flag_BAI=0;
// 	}
// 	else if(t_wei==2)
// 	{
// 		Flag_SHI=1;
// 		Flag_QIAN=0;
// 		Flag_GE=0;
// 		Flag_BAI=0;
// 	}
// 	else if(t_wei==3)
// 	{
// 		Flag_BAI=1;
// 		Flag_QIAN=0;
// 		Flag_GE=0;
// 		Flag_SHI=0;
// 	}
// }
// /***********************************************************************************************************************/
// void Right_Move(void)
// {
// 	t_wei--;
// 	Flag_DisSet=1;//¿ªÆôÉèÖÃÖµÏÔÊ¾
// 	if(t_wei>3)
// 	{
// 		t_wei=3;
// 	}
// 	if(t_wei==0)
// 	{
// 		Flag_QIAN=1;
// 		Flag_GE=0;
// 		Flag_SHI=0;
// 		Flag_BAI=0;
// 	}
// 	else if(t_wei==1)
// 	{
// 		Flag_GE=1;
// 		Flag_QIAN=0;
// 		Flag_SHI=0;
// 		Flag_BAI=0;
// 	}
// 	else if(t_wei==2)
// 	{
// 		Flag_SHI=1;
// 		Flag_QIAN=0;
// 		Flag_GE=0;
// 		Flag_BAI=0;
// 	}
// 	else if(t_wei==3)
// 	{
// 		Flag_BAI=1;
// 		Flag_QIAN=0;
// 		Flag_GE=0;
// 		Flag_SHI=0;
// 	}
// }
// /*************************************************************************************************************************/
// void Setvalue_Add(void)//ÉèÖÃµçÑ¹ºÍµçÁ÷µİÔö
// {
// 	/********µçÑ¹ÉèÖÃ*********************/
// 	if(Flag_GE==1&&Flag_SetV==1)
// 	{
// 		SET_Voltage++;
// 		if(SET_Voltage>MAX_VOL)
// 		{
// 			SET_Voltage=MAX_VOL;
// 		}
// 	}
// 	else if(Flag_SHI==1&&Flag_SetV==1)
// 	{
// 		SET_Voltage=SET_Voltage+10;
// 		if(SET_Voltage>MAX_VOL)
// 		{
// 			SET_Voltage=MAX_VOL;//Èç¹ûÊıÖµ´óÓÚ3000±¾´ÎµİÔöÎŞĞ§
// 		}
// 	}
// 	else if(Flag_BAI==1&&Flag_SetV==1)
// 	{
// 		SET_Voltage=SET_Voltage+100;
// 		if(SET_Voltage>MAX_VOL)
// 		{
// 			SET_Voltage=MAX_VOL;//Èç¹ûÊıÖµ´óÓÚ3000±¾´ÎµİÔöÎŞĞ§
// 		}
// 	}
// 	else if(Flag_QIAN==1&&Flag_SetV==1)
// 	{
// 		SET_Voltage=SET_Voltage+1000;
// 		if(SET_Voltage>MAX_VOL)
// 		{
// 			SET_Voltage=SET_Voltage-1000;//Èç¹ûÊıÖµ´óÓÚ3000±¾´ÎµİÔöÎŞĞ§
// 		}
// 	}
// /**********µçÁ÷ÉèÖÃ*******************/
// 	if(Flag_GE==1&&Flag_SetA==1)
// 	{
// 		if(flag_Test_Min==1)//ÉèÖÃÏÂÏŞÖµ
// 		{
// 			MIN_limit++;
// 			if( MIN_limit>MAX_CUR)
// 			{
// 				 MIN_limit=MAX_CUR;
// 			}
// 		}
// 		else if(flag_Test_MAX==1)//ÉèÖÃÉÏÏŞÖµ
// 		{
// 			MAX_limit++;
// 			if( MAX_limit>MAX_CUR)
// 			{
// 				 MAX_limit=MAX_CUR;
// 			}
// 		}
// 		else if(flag_Test_SetTime==1)//ÉèÖÃ²âÊÔÊ±¼ä
// 		{
// 			Test_Daley++;
// 			if( Test_Daley>9999)
// 			{
// 				Test_Daley=9999;
// 			}
// 		}
// 		else if(flag_Test_Door==1)//ÉèÖÃÃÅ¼÷µçÁ÷
// 		{
// 			Test_C_Door++;
// 			if(Test_C_Door>MAX_CUR)
// 			{
// 				Test_C_Door=MAX_CUR;
// 			}
// 		}
// 		else if(flag_ADJ_ON==1)//½øÈëĞ£×¼Ä£Ê½
// 		{
// 			ADJ_Write++;
// 			if(ADJ_Write>MAX_CUR)
// 			{
// 				ADJ_Write=MAX_CUR;
// 			}
// 		}
// 		else
// 		{
// 			SET_Current++;
// 			if(SET_Current>MAX_CUR)
// 			{
// 				SET_Current=MAX_CUR;
// 			}
// 		}
// 	}
// 	else if(Flag_SHI==1&&Flag_SetA==1)
// 	{
// 		if(flag_Test_Min==1)//ÉèÖÃÏÂÏŞÖµ
// 		{
// 			MIN_limit=MIN_limit+10;
// 			if( MIN_limit>MAX_CUR)
// 			{
// 				 MIN_limit=MIN_limit-10;
// 			}
// 		}
// 		else if(flag_Test_MAX==1)//ÉèÖÃÉÏÏŞÖµ
// 		{
// 			MAX_limit=MAX_limit+10;
// 			if( MAX_limit>MAX_CUR)
// 			{
// 				 MAX_limit=MAX_limit-10;
// 			}
// 		}
// 		else if(flag_Test_SetTime==1)//ÉèÖÃ²âÊÔÊ±¼ä
// 		{
// 			Test_Daley=Test_Daley+10;
// 			if( Test_Daley>9999)
// 			{
// 				Test_Daley=Test_Daley-10;
// 			}
// 		}
// 		else if(flag_Test_Door==1)//ÉèÖÃÃÅ¼÷µçÁ÷
// 		{
// 			Test_C_Door=Test_C_Door+10;
// 			if(Test_C_Door>MAX_CUR)
// 			{
// 				Test_C_Door=Test_C_Door-10;
// 			}
// 		}
// 		else if(flag_ADJ_ON==1)//½øÈëĞ£×¼Ä£Ê½
// 		{
// 			ADJ_Write=ADJ_Write+10;
// 			if(ADJ_Write>MAX_CUR)
// 			{
// 				ADJ_Write=MAX_CUR;//Èç¹ûÊıÖµ´óÓÚ5000±¾´ÎµİÔöÎŞĞ§
// 			}
// 		}
// 		else
// 		{
// 			SET_Current=SET_Current+10;
// 			if(SET_Current>MAX_CUR)
// 			{
// 				SET_Current=MAX_CUR;//Èç¹ûÊıÖµ´óÓÚ5000±¾´ÎµİÔöÎŞĞ§
// 			}
// 		}
// 	}
// 	else if(Flag_BAI==1&&Flag_SetA==1)
// 	{
// 		if(flag_Test_Min==1)//ÉèÖÃÏÂÏŞÖµ
// 		{
// 			MIN_limit=MIN_limit+100;
// 			if( MIN_limit>MAX_CUR)
// 			{
// 				 MIN_limit=MIN_limit-100;
// 			}
// 		}
// 		else if(flag_Test_MAX==1)//ÉèÖÃÉÏÏŞÖµ
// 		{
// 			MAX_limit=MAX_limit+100;
// 			if( MAX_limit>MAX_CUR)
// 			{
// 				 MAX_limit=MAX_limit-100;
// 			}
// 		}
// 		else if(flag_Test_SetTime==1)//ÉèÖÃ²âÊÔÊ±¼ä
// 		{
// 			Test_Daley=Test_Daley+100;
// 			if( Test_Daley>9999)
// 			{
// 				Test_Daley=Test_Daley-100;
// 			}
// 		}
// 		else if(flag_Test_Door==1)//ÉèÖÃÃÅ¼÷µçÁ÷
// 		{
// 			Test_C_Door=Test_C_Door+100;
// 			if(Test_C_Door>MAX_CUR)
// 			{
// 				Test_C_Door=Test_C_Door-100;
// 			}
// 		}
// 		else if(flag_ADJ_ON==1)//½øÈëĞ£×¼Ä£Ê½
// 		{
// 			ADJ_Write=ADJ_Write+100;
// 			if(ADJ_Write>MAX_CUR)
// 			{
// 				ADJ_Write=ADJ_Write-100;
// 			}
// 		}
// 		else
// 		{
// 			SET_Current=SET_Current+100;
// 			if(SET_Current>MAX_CUR)
// 			{
// 				SET_Current=MAX_CUR;//Èç¹ûÊıÖµ´óÓÚ5000±¾´ÎµİÔöÎŞĞ§
// 			}
// 		}
// 	}
// 	else if(Flag_QIAN==1&&Flag_SetA==1)
// 	{
// 		if(flag_Test_Min==1)//ÉèÖÃÏÂÏŞÖµ
// 		{
// 			MIN_limit=MIN_limit+1000;
// 			if( MIN_limit>MAX_CUR)
// 			{
// 				 MIN_limit=MIN_limit-1000;
// 			}
// 		}
// 		else if(flag_Test_MAX==1)//ÉèÖÃÉÏÏŞÖµ
// 		{
// 			MAX_limit=MAX_limit+1000;
// 			if( MAX_limit>MAX_CUR)
// 			{
// 				 MAX_limit=MAX_limit-1000;
// 			}
// 		}
// 		else if(flag_Test_SetTime==1)//ÉèÖÃ²âÊÔÊ±¼ä
// 		{
// 			Test_Daley=Test_Daley+1000;
// 			if( Test_Daley>9999)
// 			{
// 				Test_Daley=Test_Daley-1000;
// 			}
// 		}
// 		else if(flag_Test_Door==1)//ÉèÖÃÃÅ¼÷µçÁ÷
// 		{
// 			Test_C_Door=Test_C_Door+1000;
// 			if(Test_C_Door>MAX_CUR)
// 			{
// 				Test_C_Door=Test_C_Door-1000;
// 			}
// 		}
// 		else if(flag_ADJ_ON==1)//½øÈëĞ£×¼Ä£Ê½
// 		{
// 			ADJ_Write=ADJ_Write+1000;
// 			if(ADJ_Write>MAX_CUR)
// 			{
// 				ADJ_Write=ADJ_Write-1000;//Èç¹ûÊıÖµ´óÓÚ5000±¾´ÎµİÔöÎŞĞ§
// 			}
// 		}
// 		else
// 		{
// 			SET_Current=SET_Current+1000;
// 			if(SET_Current>MAX_CUR)
// 			{
// 				SET_Current=SET_Current-1000;//Èç¹ûÊıÖµ´óÓÚ5000±¾´ÎµİÔöÎŞĞ§
// 			}
// 		}
// 	}
// }
// /***************************************************************************************/
// void Setvalue_Reduction(void)//ÉèÖÃµçÑ¹ºÍµçÁ÷µİ¼õ
// {
// 	/*********************ÉèÖÃµçÑ¹***********************************************/
// 	if(Flag_GE==1&&Flag_SetV==1)
// 	{
// 		SET_Voltage--;
// 		if(SET_Voltage>MAX_VOL)
// 		{
// 			SET_Voltage=0;
// 		}
// 	}
// 	else if(Flag_SHI==1&&Flag_SetV==1)
// 	{
// 		SET_Voltage=SET_Voltage-10;
// 		if(SET_Voltage>MAX_VOL)
// 		{
// 			SET_Voltage=SET_Voltage+10;//Èç¹ûÊıÖµ´óÓÚ3000±¾´Îµİ¼õÎŞĞ§
// 		}
// 	}
// 	else if(Flag_BAI==1&&Flag_SetV==1)
// 	{
// 		SET_Voltage=SET_Voltage-100;
// 		if(SET_Voltage>MAX_VOL)
// 		{
// 			SET_Voltage=SET_Voltage+100;//Èç¹ûÊıÖµ´óÓÚ3000±¾´Îµİ¼õÎŞĞ§
// 		}
// 	}
// 	else if(Flag_QIAN==1&&Flag_SetV==1)
// 	{
// 		SET_Voltage=SET_Voltage-1000;
// 		if(SET_Voltage>MAX_VOL)
// 		{
// 			SET_Voltage=SET_Voltage+1000;//Èç¹ûÊıÖµ´óÓÚ3000±¾´Îµİ¼õÎŞĞ§
// 		}
// 	}
// /******************************ÉèÖÃµçÁ÷******************************************/
// 	if(Flag_GE==1&&Flag_SetA==1)
// 	{
// 		if(flag_Test_Min==1)//ÉèÖÃÏÂÏŞÖµ
// 		{
// 			MIN_limit--;
// 			if( MIN_limit>MAX_CUR)
// 			{
// 				 MIN_limit=0;
// 			}
// 		}
// 		else if(flag_Test_MAX==1)//ÉèÖÃÉÏÏŞÖµ
// 		{
// 			MAX_limit--;
// 			if( MAX_limit>MAX_CUR)
// 			{
// 				 MAX_limit=0;
// 			}
// 		}
// 		else if(flag_Test_SetTime==1)//ÉèÖÃ²âÊÔÊ±¼ä
// 		{
// 			Test_Daley--;
// 			if( Test_Daley>9999)
// 			{
// 				Test_Daley=0;
// 			}
// 		}
// 		else if(flag_Test_Door==1)//ÉèÖÃÃÅ¼÷µçÁ÷
// 		{
// 			Test_C_Door--;
// 			if(Test_C_Door<10)
// 			{
// 				Test_C_Door=10;
// 			}
// 		}
// 		else if(flag_ADJ_ON==1)//½øÈëĞ£×¼Ä£Ê½
// 		{
// 			ADJ_Write--;//ÉèÖÃµçÁ÷Öµ
// 			if(ADJ_Write>MAX_CUR)
// 			{
// 				ADJ_Write=0;
// 			}
// 		}
// 		else
// 		{
// 			SET_Current--;//ÉèÖÃµçÁ÷Öµ
// 			if(SET_Current>MAX_CUR)
// 			{
// 				SET_Current=0;
// 			}
// 		}
// 		
// 	}
// 	else if(Flag_SHI==1&&Flag_SetA==1)
// 	{
// 		if(flag_Test_Min==1)//ÉèÖÃÏÂÏŞÖµ
// 		{
// 			MIN_limit=MIN_limit-10;
// 			if( MIN_limit>MAX_CUR)
// 			{
// 				 MIN_limit=MIN_limit+10;
// 			}
// 		}
// 		else if(flag_Test_MAX==1)//ÉèÖÃÉÏÏŞÖµ
// 		{
// 			MAX_limit=MAX_limit-10;
// 			if( MAX_limit>MAX_CUR)
// 			{
// 				 MAX_limit=MAX_limit+10;
// 			}
// 		}
// 		else if(flag_Test_SetTime==1)//ÉèÖÃ²âÊÔÊ±¼ä
// 		{
// 			Test_Daley=Test_Daley-10;
// 			if( Test_Daley>9999)
// 			{
// 				Test_Daley=Test_Daley+10;
// 			}
// 		}
// 		else if(flag_Test_Door==1)//ÉèÖÃÃÅ¼÷µçÁ÷
// 		{
// 			Test_C_Door=Test_C_Door-10;
// 			if(Test_C_Door>MAX_CUR)
// 			{
// 				Test_C_Door=Test_C_Door+10;
// 			}
// 		}
// 		else if(flag_ADJ_ON==1)//½øÈëĞ£×¼Ä£Ê½
// 		{
// 			ADJ_Write=ADJ_Write-10;
// 			if(ADJ_Write>MAX_CUR)
// 			{
// 				ADJ_Write=ADJ_Write+10;//Èç¹ûÊıÖµ´óÓÚ5000±¾´Îµİ¼õÎŞĞ§
// 			}
// 		}
// 		else
// 		{
// 			SET_Current=SET_Current-10;
// 			if(SET_Current>MAX_CUR)
// 			{
// 				SET_Current=SET_Current+10;//Èç¹ûÊıÖµ´óÓÚ5000±¾´Îµİ¼õÎŞĞ§
// 			}
// 		}
// 	}
// 	else if(Flag_BAI==1&&Flag_SetA==1)
// 	{
// 		if(flag_Test_Min==1)//ÉèÖÃÏÂÏŞÖµ
// 		{
// 			MIN_limit=MIN_limit-100;
// 			if( MIN_limit>MAX_CUR)
// 			{
// 				 MIN_limit=MIN_limit+100;
// 			}
// 		}
// 		else if(flag_Test_MAX==1)//ÉèÖÃÉÏÏŞÖµ
// 		{
// 			MAX_limit=MAX_limit-100;
// 			if( MAX_limit>MAX_CUR)
// 			{
// 				 MAX_limit=MAX_limit+100;
// 			}
// 		}
// 		else if(flag_Test_SetTime==1)//ÉèÖÃ²âÊÔÊ±¼ä
// 		{
// 			Test_Daley=Test_Daley-100;
// 			if( Test_Daley>9999)
// 			{
// 				Test_Daley=Test_Daley+100;
// 			}
// 		}
// 		else if(flag_Test_Door==1)//ÉèÖÃÃÅ¼÷µçÁ÷
// 		{
// 			Test_C_Door=Test_C_Door-100;
// 			if(Test_C_Door>MAX_CUR)
// 			{
// 				Test_C_Door=Test_C_Door+100;
// 			}
// 		}
// 		else if(flag_ADJ_ON==1)//½øÈëĞ£×¼Ä£Ê½
// 		{
// 			ADJ_Write=ADJ_Write-100;
// 			if(ADJ_Write>MAX_CUR)
// 			{
// 				ADJ_Write=ADJ_Write+100;//Èç¹ûÊıÖµ´óÓÚ5000±¾´Îµİ¼õÎŞĞ§
// 			}
// 		}
// 		else
// 		{
// 			SET_Current=SET_Current-100;
// 			if(SET_Current>MAX_CUR)
// 			{
// 				SET_Current=SET_Current+100;//Èç¹ûÊıÖµ´óÓÚ5000±¾´Îµİ¼õÎŞĞ§
// 			}
// 		}
// 	}
// 	else if(Flag_QIAN==1&&Flag_SetA==1)
// 	{
// 		if(flag_Test_Min==1)//ÉèÖÃÏÂÏŞÖµ
// 		{
// 			MIN_limit=MIN_limit-1000;
// 			if( MIN_limit>MAX_CUR)
// 			{
// 				 MIN_limit=MIN_limit+1000;
// 			}
// 		}
// 		else if(flag_Test_MAX==1)//ÉèÖÃÉÏÏŞÖµ
// 		{
// 			MAX_limit=MAX_limit-1000;
// 			if( MAX_limit>MAX_CUR)
// 			{
// 				 MAX_limit=MAX_limit+1000;
// 			}
// 		}
// 		else if(flag_Test_SetTime==1)//ÉèÖÃ²âÊÔÊ±¼ä
// 		{
// 			Test_Daley=Test_Daley-1000;
// 			if( Test_Daley>9999)
// 			{
// 				Test_Daley=Test_Daley+1000;
// 			}
// 		}
// 		else if(flag_Test_Door==1)//ÉèÖÃÃÅ¼÷µçÁ÷
// 		{
// 			Test_C_Door=Test_C_Door-1000;
// 			if(Test_C_Door>MAX_CUR)
// 			{
// 				Test_C_Door=Test_C_Door+1000;
// 			}
// 		}
// 		else if(flag_ADJ_ON==1)//½øÈëĞ£×¼Ä£Ê½
// 		{
// 			ADJ_Write=ADJ_Write-1000;
// 			if(ADJ_Write>MAX_CUR)
// 			{
// 				ADJ_Write=ADJ_Write+1000;//Èç¹ûÊıÖµ´óÓÚ5000±¾´Îµİ¼õÎŞĞ§
// 			}
// 		}
// 		else
// 		{
// 			SET_Current=SET_Current-1000;
// 			if(SET_Current>MAX_CUR)
// 			{
// 				SET_Current=SET_Current+1000;//Èç¹ûÊıÖµ´óÓÚ5000±¾´Îµİ¼õÎŞĞ§
// 			}
// 		}
// 	}
// }
/********************************************************************************/
void Mode_SW_CONT(vu8 mode)//Ä£Ê½ÈÛ»à ˜×†
{
	switch(mode)
	{
		case 0x01 ://ÅšØ¨Ó¢Ë”Ä£Ê½
		{
			GPIO_ResetBits(GPIOE,GPIO_Pin_2);
			GPIO_ResetBits(GPIOE,GPIO_Pin_3);
            mode_sw = mode_r;
		}
		break;
		case 0x02 ://ØºÕ˜Ä£Ê½
		{
			GPIO_SetBits(GPIOE,GPIO_Pin_2);
			GPIO_ResetBits(GPIOE,GPIO_Pin_3);
            mode_sw = mode_load;
		}
		break;
		case 0x03 ://Ö±Â·Ö§Ô´Ä£Ê½
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
