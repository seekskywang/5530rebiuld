/******************************************************************/
/* 名称：                                                  				*/
/* 效果：                                                        */
/* 内容：内阻仪界面                                              */
/* 作者：zhan                                                  */
/* 联系方式QQ:363116119                                        */


#include "MainTask.h"
#include  "gui.h"
#include "DIALOG.h"
#include "my_register.h" 
#include "tm1650.h"
#include "stdio.h"
#include "stdlib.h"
#include "key.h"
#include "string.h"
#include "beep.h"


WM_HWIN hWinR;
void OC_ADD(void); 
void test_r(void);
vu8 bit = 1;
vu8 dot_flag = 0;
vu8 page_sw = face_r;
vu8 para_set1;
vu8 para_set2 = set_2_on;
vu8 para_set3;
vu8 para_set4 = set_4_off;
vu8 r_stable = 0;
float gate_v = 0;
vu8 oct_sw = oct_off;
vu8 lang;
vu8 finish = 0;
vu8 set_sw;
char set_limit[5];
vu16 stable_time;
vu8 rpow;
////////////////////////////////////////////////////////

vu16 dis_gate_v;
float DISS_R;//内阻
extern vu8 page_sw;
static vu8 oc_sw = set_20;
float oc_data;
static vu16 r;
vu16 s_time;
vu8 wait_flag;
vu8 test_num = 0;
vu8 con_flag = 0;
vu8 short_flag = 0;
vu16 short_start;
vu16 short_time;
vu8 short_finish = 0;
float v;
//vu16 stable_time;
float time1;
vu16 steptime = 1;
vu8 test_finish = 0;
int test_ftime;
extern vu8 t_onoff;
extern vu8 LOAD_t;
extern vu8 status_flash;
extern vu8 pass;
extern vu8 track;
extern vu8 clear_flag1;
extern float clear_v;
extern vu8 clear_r;
extern vu8 r_test;
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_1     (GUI_ID_USER + 0x12)
#define ID_TEXT_0     	(GUI_ID_USER + 0x13)
#define ID_TEXT_1     	(GUI_ID_USER + 0x14)
#define ID_TEXT_3     	(GUI_ID_USER + 0x15)
#define ID_TEXT_4     	(GUI_ID_USER + 0x16)
#define ID_TEXT_6     	(GUI_ID_USER + 0x17)
#define ID_TEXT_43    	(GUI_ID_USER + 0x68)
#define ID_TEXT_44    	(GUI_ID_USER + 0x69)
#define ID_TEXT_45    	(GUI_ID_USER + 0x6A)
#define ID_TEXT_46    	(GUI_ID_USER + 0x6B)
#define ID_TEXT_47    	(GUI_ID_USER + 0x6C)
#define ID_TEXT_80   	(GUI_ID_USER + 0x8D)
#define ID_TEXT_81   	(GUI_ID_USER + 0x8E)
#define ID_TEXT_82      (GUI_ID_USER + 0x8F)
#define ID_TEXT_83      (GUI_ID_USER + 0x90)
#define ID_TEXT_96     	(GUI_ID_USER + 0x0104)
#define ID_TEXT_97     	(GUI_ID_USER + 0x0105)
#define ID_TEXT_98     	(GUI_ID_USER + 0x0106)
#define ID_TEXT_117     (GUI_ID_USER + 0x30C)
#define ID_TEXT_118     (GUI_ID_USER + 0x30D)
#define ID_TEXT_122     (GUI_ID_USER + 0x311)
#define ID_BUTTON_12    (GUI_ID_USER + 0x18)
#define ID_BUTTON_13    (GUI_ID_USER + 0x19)
#define ID_BUTTON_14    (GUI_ID_USER + 0x1A)
#define ID_BUTTON_15   	(GUI_ID_USER + 0x1B)
#define ID_BUTTON_16   	(GUI_ID_USER + 0x1C)
#define ID_BUTTON_17    (GUI_ID_USER + 0x1D)


#define ID_TimerTime    1
// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "R", ID_WINDOW_1, 0, 0, 480, 272, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_0, 28, 50, 64, 32, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_1, 28, 120, 64, 32, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_3, 217, 50, 32, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_4, 239, 121, 32, 32, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_6, 217, 128, 32, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_43, 300, 150, 100, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_44, 300, 60, 100, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_45, 300, 90, 100, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_46, 400, 60, 57, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_47, 400, 90, 57, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_80, 95, 48, 150, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_81, 95, 116, 150, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_82, 95, 184, 150, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_83, 400, 175, 57, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_96, 300, 5, 120, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_97, 400, 120, 60, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_98, 405, 5, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_117, 400, 200, 60, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_118, 300, 120, 100, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_122, 400, 150, 60, 20, 0, 0x0, 0 },
//   { BUTTON_CreateIndirect, "Button", ID_BUTTON_12, 3, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_13, 83, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_14, 163, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_15, 243, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_16, 323, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_17, 403, 226, 77, 45, 0, 0x0, 0 }
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
    WM_HWIN hItem;
//    int     NCode;
//    int     Id;
    
    char  buf[5];
    float dis_init_c = (float)set_init_c/100;
    float dis_sbs_c = (float)set_sbs_c/100;
    static float short1,short2;


  // USER START (Optionally insert additional variables)
  // USER END
//    int i;
        


  switch (pMsg->MsgId) {
		
	case WM_PAINT:
	GUI_SetColor(GUI_WHITE);//设置画笔颜色
	GUI_FillRect(0,25,480,26);//画一条实线
    GUI_SetColor(GUI_ORANGE);
	GUI_SetFont(&GUI_Fontsymbol);
	GUI_UC_SetEncodeUTF8();
	GUI_SetTextMode(GUI_TM_TRANS);//设置文本模式为底色透明
	GUI_DispStringAt("Jinko", 5, 1);//SET
    if(lang == 0)
    {
        GUI_SetColor(GUI_WHITE);
        GUI_SetFont(&GUI_FontHZ20S);
        GUI_UC_SetEncodeUTF8();
        GUI_SetTextMode(GUI_TM_TRANS);//设置文本模式为底色透明
        GUI_DispStringAt("测量显示", 130, 3);//SET
    }else{
        GUI_SetColor(GUI_WHITE);
        GUI_SetFont(&GUI_Font20_ASCII);
        GUI_DispStringAt("DISPLAY", 130, 3);
    }
    GUI_SetFont(&GUI_Font24_1);


    switch(para_set2){
            case set_2_on:
            {
//                 GUI_SetFont(&GUI_FontD24x32);
//                 GUI_GotoXY(95,184);//
//                 GUI_DispFloatFix(DISS_Current,5,2);
                GUI_SetFont(&GUI_FontEN40);
                GUI_SetColor(GUI_LIGHTGRAY);
                GUI_DispStringAt("I:", 28, 190);
                GUI_SetColor(GUI_LIGHTGRAY);
                GUI_DispStringAt("A", 217, 187);
                GUI_SetFont(&GUI_Font24_1);
                GUI_SetColor(GUI_WHITE);
                GUI_DispStringAt("A",460,60);
                GUI_DispStringAt("A",460,90);
                GUI_DispStringAt("V",460,120);
                GUI_DispStringAt("ms",450,150);
                GUI_DispStringAt("A",460,175);
                GUI_DispStringAt("ms",450,200);                
                if(lang == 0)
                {
                    GUI_SetFont(&GUI_Fontset_font);
                    GUI_DispStringAt("电流", 300, 175);
                    GUI_DispStringAt("短路时间", 300, 200);//SET
                    GUI_DispStringAt("过流测试", 340, 30);//SET
                }else{
                    GUI_SetFont(&GUI_Font20_ASCII);
                    GUI_DispStringAt("Current", 300, 170);
                    GUI_DispStringAt("Short Time", 300, 200);//SET
                    GUI_DispStringAt("Overflow test", 340, 30);//SET
                }
                break;
            }
            case set_2_off:
            {
                break;
            }
    }
	break;
	case WM_TIMER://定时模块消息
	if(WM_GetTimerId(pMsg->Data.v) == ID_TimerTime)
	{
        
        if(para_set2 == set_2_on)
        {
            if(short_finish == 1 && test_finish == 1)
            {
                if(gate_v == 0)
                {
                    if(GUI_GetTime()/500 - test_ftime == 2)
                    {
                        GPIO_ResetBits(GPIOB,GPIO_Pin_13);
                        Mode_SW_CONT(0x01);
                    }
                    if(/*mode_sw == mode_pow && */DISS_Voltage < 0.3  && GUI_GetTime()/500 - test_ftime > 2 /*&&                         < 50*/)
                    {
                        GPIO_ResetBits(GPIOB,GPIO_Pin_13);
                        Mode_SW_CONT(0x01);
                        finish = 0;
                        con_flag = 0;
                        short_finish = 0;
                        test_finish = 0;
                        r_test = 0;
                        v = 0;
                    }
                }else{
                    if(GUI_GetTime()/500 - test_ftime == 2)
                    {
                        GPIO_ResetBits(GPIOB,GPIO_Pin_13);
                        Mode_SW_CONT(0x01);
                    }
                    if(/* mode_sw == mode_pow && */(r_test == 0 || DISS_Voltage < gate_v) && GUI_GetTime()/500 - test_ftime > 1/*&& R_VLUE < 50*/)
                    { 
                        GPIO_ResetBits(GPIOB,GPIO_Pin_13);
                        Mode_SW_CONT(0x01);
                        finish = 0;
                        con_flag = 0;
                        short_finish = 0;
                        test_finish = 0;
                        r_test = 0;
                        v = 0;
                    }
                }                    
            }else{
                if(para_set2 == set_2_on)
                {
                    if(gate_v == 0)
                    {
                        if(DISS_Voltage > 1 && R_VLUE > 50 && con_flag == 0 && finish == 0)
                        {
                            con_flag = 1;
                            time1 = (float)GUI_GetTime()/500.0;
                        }
                        
                        if(con_flag == 1 && oct_sw == oct_off && finish == 0)
                        {
                            if((float)(GUI_GetTime()/500.0 - time1) > 0.8)
                            {
                                r = R_VLUE;
//                                v = DISS_Voltage;
                                oct_sw = oct_on;
                                clear_flag1 = 0;
                            }else{
                                if(v < DISS_Voltage)
                                {
                                    v = DISS_Voltage;
                                }
                            }
                        }
                    }else{
                        if(DISS_Voltage > gate_v && R_VLUE > 50 && con_flag == 0 && finish == 0 && r_test == 1)
                        {
                            con_flag = 1;
                            time1 = (float)GUI_GetTime()/500.0;
                            
                        }
                        if(con_flag == 1 && oct_sw == oct_off && finish == 0)
                        {
                            if((float)(GUI_GetTime()/500.0 - time1) > 0.8)
                            {
                                r = R_VLUE;
//                                v = DISS_Voltage;
                                oct_sw = oct_on;
                                clear_flag1 = 0;
                            }else{
                                if(v < DISS_Voltage)
                                {
                                    v = DISS_Voltage;
                                }
                            }
                        }
                    }
                }
                
            }
            
            
            
            if(oct_sw == oct_on && para_set2 == set_2_on)
            {
                Mode_SW_CONT(0x02);
                GPIO_ResetBits(GPIOC,GPIO_Pin_1);
//                OC_ADD();
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
                TEXT_SetFont(hItem,&GUI_FontD24x32);
                sprintf(buf,"%4d",r);       
                TEXT_SetText(hItem,buf);
                
    //             if(status_flash == 0){

                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_98);
                TEXT_SetTextColor(hItem, GUI_RED);
                if(lang == 0)
                {
                    GUI_SetFont(&GUI_Fontset_font);
                    TEXT_SetText(hItem, "测试中");
                    status_flash = 1;
                }else{
                    GUI_SetFont(&GUI_Font20_ASCII);
                    TEXT_SetText(hItem, "Testing");
                    status_flash = 1;
                }
                    
    //             }else{
    //                 hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_98);
    //                 TEXT_SetText(hItem,"");
    //                 status_flash = 0;
    //             }
                
            }else
            {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_98);
                TEXT_SetTextColor(hItem, GUI_WHITE);
                
                
                if(lang == 0)
                {
                    GUI_SetFont(&GUI_Fontset_font);
                    TEXT_SetText(hItem, "未测试");
                }else{
                    GUI_SetFont(&GUI_Font20_ASCII);
                    TEXT_SetText(hItem, "Untested");
                }
            }
            
            if(oct_sw == oct_off && finish == 0)
            {
                if(DISS_Voltage > 1 && r_stable == 0)
                {
                    r_stable = 1;
                    stable_time = GUI_GetTime()/500;
                }else if(DISS_Voltage < 1){
                    r_stable = 0;
                }                    
                if(DISS_Voltage <= 0.1)
                {
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_80);
                    sprintf(buf,"%.2f",0.00);       
                    TEXT_SetText(hItem,buf);
                }else{
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_80);
                    sprintf(buf,"%.2f",DISS_Voltage);       
                    TEXT_SetText(hItem,buf);
                }
                if(clear_flag1 == 1 && R_VLUE <= clear_r)
                {
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
                    sprintf(buf,"%4d",0);       
                    TEXT_SetText(hItem,buf);
                }
//                 else if(R_VLUE >= 1000)
//                 {
//                     hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
//                     TEXT_SetFont(hItem,&GUI_FontEN40);//设定文本字体
//                     TEXT_SetText(hItem,"");
//                 }
                else{
                        if(GUI_GetTime()/500 - stable_time == 1 && r_stable == 1)
                        {
                            r = R_VLUE;
                            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
                            TEXT_SetFont(hItem,&GUI_FontD24x32);
                            sprintf(buf,"%4d",r);       
                            TEXT_SetText(hItem,buf);
                        }else if(r_stable == 0)
                        {
                            if(DISS_Voltage < 0.3)
                            {
                                if(para_set1 == set_1_on)
                                {
                                    TM1650_SET_LED(0x68,0x70);
                                    GPIO_ResetBits(GPIOD,GPIO_Pin_12);//灭灯
                                }
                                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
                                TEXT_SetFont(hItem,&GUI_FontD24x32);
                                TEXT_SetTextColor(hItem, GUI_GREEN);
                                sprintf(buf,"%4d",0);       
                                TEXT_SetText(hItem,buf);
                            }else{
                                
//                                 hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
//                                 TEXT_SetFont(hItem,&GUI_FontD24x32);
//                                 
//                                 sprintf(buf,"%4d",R_VLUE);       
//                                 TEXT_SetText(hItem,buf);
                            }
//                              hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
//                                 TEXT_SetFont(hItem,&GUI_FontD24x32);
//                                 
//                                 sprintf(buf,"%4d",R_VLUE);       
//                                 TEXT_SetText(hItem,buf);
                        }                        
                }
                short_time = 0;
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_117);
                sprintf(buf,"%4d",short_time);
                TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体      
                TEXT_SetText(hItem,buf);
                
                oc_data = 0;
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_82);
                sprintf(buf,"%.2f",oc_data);
                TEXT_SetText(hItem,buf);
            }else{
                if(para_set2 == set_2_on)
                {
//                     hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_80);
//                     sprintf(buf,"%.2f",v);       
//                     TEXT_SetText(hItem,buf);
//                     
//                     hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
//                     TEXT_SetFont(hItem,&GUI_FontD24x32);
//                     sprintf(buf,"%4d",r);       
//                     TEXT_SetText(hItem,buf);
//                     
//                     hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_117);
//                     sprintf(buf,"%4d",short_time);
//                     TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体      
//                     TEXT_SetText(hItem,buf);
//                     
//                     if(short_finish == 0 ){
//                         if(DISS_Voltage < 1 && short_flag == 0 && oct_sw == oct_off)
//                         {
//                             SET_Voltage =1000;
//                             SET_Current = 1000;
//                             Mode_SW_CONT(0x03);
//                             GPIO_SetBits(GPIOB,GPIO_Pin_13);
//                             //GPIO_ResetBits(GPIOB,GPIO_Pin_13);
//                         }else if(oct_sw == oct_off && short_flag == 0){
//                             Mode_SW_CONT(0x02);
//                             SET_Current_Laod = 1000;
//                             short_flag =1;
//                             short_start = GUI_GetTime()*2;
//                         }
//                         if(short_flag == 1)
//                         {
//                             GPIO_ResetBits(GPIOC,GPIO_Pin_1);
//                             if(DISS_Voltage < 1){
//                                 SET_Current_Laod = set_init_c;
//                                 short_time = GUI_GetTime()*2 - short_start;
//                                 short_flag = 0;
//                                 short_finish = 1;
//                                 hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_117);
//                                 sprintf(buf,"%4d",short_time);     
//                                 TEXT_SetText(hItem,buf);
//                             }
//                         }
//                     }
                    if(short_finish == 1 && test_finish == 0)
                    {
                        GPIO_SetBits(GPIOC,GPIO_Pin_1);
                        Mode_SW_CONT(0x03);
                        SET_Voltage = 2000;
                        SET_Current = 1000;
                        GPIO_SetBits(GPIOB,GPIO_Pin_13);
                        
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_117);
                        sprintf(buf,"%4d",short_time);     
                        TEXT_SetText(hItem,buf);
//                         GPIO_ResetBits(GPIOB,GPIO_Pin_13);                                                
//                         Mode_SW_CONT(0x01);
                        
                        test_ftime = GUI_GetTime()/500;
                        test_finish = 1;
                    } 
                }
                
                
                
    //             if(R_VLUE >= 1000)
    //             {
    //                 hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
    //                 TEXT_SetFont(hItem,&GUI_FontEN40);//设定文本字体
    //                 TEXT_SetText(hItem,"");
    //             }else{
                    
    //             }
            }
            
            
            
            
                    
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_82);
            sprintf(buf,"%.2f",oc_data);
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_83);
            sprintf(buf,"%.2f",DISS_Current);
            TEXT_SetText(hItem,buf); 
        }else{
            
            if(DISS_Voltage > 1 && r_stable == 0)
            {
                r_stable = 1;
                stable_time = GUI_GetTime()/500;
            }else if(DISS_Voltage < 1){
                r_stable = 0;
            }
                
            if(clear_flag1 == 1 && DISS_Voltage <= clear_v)
                {
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_80);
                    sprintf(buf,"%.2f",0.00);       
                    TEXT_SetText(hItem,buf);
                }else{
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_80);
                    sprintf(buf,"%.2f",DISS_Voltage);       
                    TEXT_SetText(hItem,buf);
                }
                if(clear_flag1 == 1 && R_VLUE <= clear_r)
                {
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
                    sprintf(buf,"%4d",0);       
                    TEXT_SetText(hItem,buf);
                }
                else if(R_VLUE >= 1000 && DISS_Voltage > 1)
                {
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
                    TEXT_SetFont(hItem,&GUI_FontEN40);//设定文本字体
                    TEXT_SetText(hItem,"");
                }else{
                    if(GUI_GetTime()/500 - stable_time == 1 && r_stable == 1)
                    {
                        r = R_VLUE;
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
                        TEXT_SetFont(hItem,&GUI_FontD24x32);
                        sprintf(buf,"%4d",r);       
                        TEXT_SetText(hItem,buf);
                    }else if(r_stable == 0)
                    {
                        if(DISS_Voltage < 0.3)
                            {
                                if(para_set1 == set_1_on)
                                {
                                    TM1650_SET_LED(0x68,0x70);
                                    GPIO_ResetBits(GPIOD,GPIO_Pin_12);//灭灯
                                }
                                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
                                TEXT_SetFont(hItem,&GUI_FontD24x32);
                                TEXT_SetTextColor(hItem, GUI_GREEN);
                                sprintf(buf,"%4d",0);       
                                TEXT_SetText(hItem,buf);
                            }else{
                                   
//                                 hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
//                                 TEXT_SetFont(hItem,&GUI_FontD24x32);
//                                 
//                                 sprintf(buf,"%4d",R_VLUE);       
//                                 TEXT_SetText(hItem,buf);
                            }
//                              hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
//                                 TEXT_SetFont(hItem,&GUI_FontD24x32);
//                                 
//                                 sprintf(buf,"%4d",R_VLUE);       
//                                 TEXT_SetText(hItem,buf);
                    }                 
                }
            
        }
               
        
        if(para_set1 == set_1_on && oct_sw == oct_off && DISS_Voltage > 1)
        {
             test_r();
        }else
        {
            TM1650_SET_LED(0x68,0x70);
            GPIO_ResetBits(GPIOD,GPIO_Pin_12);//灭灯
//            led_sw = 1;
        }
//         if(para_set2 == set_2_on)
//         {
//             if(para_set1 == set_1_on && oct_sw == oct_off && finish == 1)
//             {
//                  test_r();
//             }else
//             {
//                 TM1650_SET_LED(0x68,0x70);
//                 GPIO_ResetBits(GPIOD,GPIO_Pin_12);//灭灯
//             }
//         }else{
//             if(para_set1 == set_1_on && DISS_Voltage > 1)
//             {
//                  test_r();
//             }else
//             {
//                 TM1650_SET_LED(0x68,0x70);
//                 GPIO_ResetBits(GPIOD,GPIO_Pin_12);//灭灯
//             }
//         }

        
        if(oct_sw == oct_off)
        {
            switch(b_type)
            {
                case Lion:
                {
                    if(R_VLUE != 0  && DISS_Voltage >= 3.4 && DISS_Voltage <= 4.2)
                    {
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_96);
                        TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色      
                        if(lang == 0)
                        {
                            TEXT_SetFont(hItem,&GUI_Fontset_font);
                            TEXT_SetText(hItem,"锂电池");
                        }else{
                            TEXT_SetFont(hItem,&GUI_Font20_ASCII);
                            TEXT_SetText(hItem,"Lion");
                        }
                    }else{
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_96);
                        TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色      
                        TEXT_SetText(hItem,"");
                    }
                    break;
                }
                case NiMH:
                {
                    if(R_VLUE != 0  && DISS_Voltage >= 0.9 && DISS_Voltage <= 1.4)
                    {
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_96);
                        TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色      
                        if(lang == 0)
                        {
                            TEXT_SetFont(hItem,&GUI_Fontset_font);
                            TEXT_SetText(hItem,"镍氢电池");
                        }else{
                            TEXT_SetFont(hItem,&GUI_Font20_ASCII);
                            TEXT_SetText(hItem,"NiMH");
                        }
                    }else{
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_96);
                        TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色      
                        TEXT_SetText(hItem,"");
                    }
                    break;
                }
                case NiCd:
                {
                    if(R_VLUE != 0 && DISS_Voltage >= 0.9 && DISS_Voltage <= 1.4)
                    {
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_96);
                        TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色      
                        if(lang == 0)
                        {
                            TEXT_SetFont(hItem,&GUI_Fontset_font);
                            TEXT_SetText(hItem,"镍镉电池");
                        }else{
                            TEXT_SetFont(hItem,&GUI_Font20_ASCII);
                            TEXT_SetText(hItem,"NiCd");
                        }
                    }else{
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_96);
                        TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色      
                        TEXT_SetText(hItem,"");
                    }
                    break;
                }
                case SLA:
                {
                    if(R_VLUE != 0  && DISS_Voltage >= 1.8 && DISS_Voltage <= 2.4)
                    {
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_96);
                        TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色      
                        if(lang == 0)
                        {
                            TEXT_SetFont(hItem,&GUI_Fontset_font);
                            TEXT_SetText(hItem,"小型铅酸电池");
                        }else{
                            TEXT_SetFont(hItem,&GUI_Font20_ASCII);
                            TEXT_SetText(hItem,"SLA");
                        }
                    }else{
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_96);
                        TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色      
                        TEXT_SetText(hItem,"");
                    }
                    break;
                }
                case LiMH:
                {
                    if(R_VLUE != 0  && DISS_Voltage >= 2.8 && DISS_Voltage <= 3.3)
                    {
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_96);
                        TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色      
                        if(lang == 0)
                        {
                            TEXT_SetFont(hItem,&GUI_Fontset_font);
                            TEXT_SetText(hItem,"锂锰电池");
                        }else{
                            TEXT_SetFont(hItem,&GUI_Font20_ASCII);
                            TEXT_SetText(hItem,"LiMH");
                        }
                    }else{
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_96);
                        TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色      
                        TEXT_SetText(hItem,"");
                    }
                    break;
                }
            }
        }
 		WM_RestartTimer(pMsg->Data.v, 20);//复位定时器数值越大刷新时间越短
	}
	break;
    		
  case WM_INIT_DIALOG:
    //
    // Initialization of 'R'
	
    //
        hItem = pMsg->hWin;
        WINDOW_SetBkColor(hItem, GUI_BLACK);
		WM_CreateTimer(hItem,ID_TimerTime,500,0);//创建本窗口定时器  

	
        if(lang == 0)
        {
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_13);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetPressed(hItem,1);
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"内阻测试");
        
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_14);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"程控负载");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_15);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"程控电源");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_16);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"充放电");
            
            
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_17);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,&GUI_FontHZ16);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"曲线");
        }else{
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_13);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetPressed(hItem,1);
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"I.R. TEST");
        
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_14);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"LOAD");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_15);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"POWER");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_16);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"C&DC");
            
            
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_17);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,&GUI_Font16B_ASCII);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"GRAPH");           
        }
		
    // Initialization of 'Text'
    //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
        TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);
        TEXT_SetFont(hItem,&GUI_FontEN40);//设定文本字体
        GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"V:");
    //
    // Initialization of 'Text'
    //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
        GUI_UC_SetEncodeUTF8();
        TEXT_SetText(hItem, "R:");
        TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);
        TEXT_SetFont(hItem,&GUI_FontEN40);//设定文本字体
    //
    // Initialization of 'Text'
    //
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
		TEXT_SetText(hItem, "V");
        TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);
        TEXT_SetFont(hItem, &GUI_FontEN40);
    //
    // Initialization of 'Text'
    //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem, "Ω");
        TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);
		TEXT_SetFont(hItem,&GUI_FontHZ32);//设定按钮文本字体
    //
    // Initialization of 'Text'
    //		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
        GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem, "m");
        TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);
		TEXT_SetFont(hItem, &GUI_FontEN40);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_80);
        TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontD24x32);//设定文本字体
        GUI_UC_SetEncodeUTF8();        
        TEXT_SetText(hItem,"0.00");
            
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
        sprintf(buf,"%04d",0);
        TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontD24x32);//设定文本字体
        GUI_UC_SetEncodeUTF8();        
        TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_96);
        TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
        GUI_UC_SetEncodeUTF8();        
        TEXT_SetText(hItem,"");
        
        switch(para_set2){
            case set_2_on:
            {
                if(lang == 0)
                {
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_43);
                    GUI_UC_SetEncodeUTF8();
                    TEXT_SetText(hItem, "步进时间");
                    TEXT_SetTextColor(hItem, GUI_WHITE);
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_44);
                    GUI_UC_SetEncodeUTF8();
                    TEXT_SetText(hItem, "起始电流");
                    TEXT_SetBkColor(hItem,0x00BFFFFF);
                    TEXT_SetTextColor(hItem, GUI_BLACK);
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_45);
                    GUI_UC_SetEncodeUTF8();
                    TEXT_SetText(hItem, "步进电流");
                    TEXT_SetTextColor(hItem, GUI_WHITE);
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_118);
                    GUI_UC_SetEncodeUTF8();
                    TEXT_SetText(hItem, "门槛电压");
                    TEXT_SetTextColor(hItem, GUI_WHITE);
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                }else{
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_43);
                    GUI_UC_SetEncodeUTF8();
                    TEXT_SetText(hItem, "Step time");
                    TEXT_SetTextColor(hItem, GUI_WHITE);
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);

                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_44);
                    GUI_UC_SetEncodeUTF8();
                    TEXT_SetText(hItem, "Starting C");
                    TEXT_SetBkColor(hItem,0x00BFFFFF);
                    TEXT_SetTextColor(hItem, GUI_BLACK);
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_45);
                    GUI_UC_SetEncodeUTF8();
                    TEXT_SetText(hItem, "Stepping C");
                    TEXT_SetTextColor(hItem, GUI_WHITE);
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_118);
                    GUI_UC_SetEncodeUTF8();
                    TEXT_SetText(hItem, "Threshlod V");
                    TEXT_SetTextColor(hItem, GUI_WHITE);
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                }
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_97);
                sprintf(buf,"%.2f",gate_v);
                TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
                TEXT_SetText(hItem,buf);
                TEXT_SetTextColor(hItem, GUI_WHITE);
                
                if(lang == 0)
                {
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_98);
                    GUI_UC_SetEncodeUTF8();
                    TEXT_SetText(hItem, "未测试");
                    TEXT_SetTextColor(hItem, GUI_WHITE);
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                }else{
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_98);
                    GUI_UC_SetEncodeUTF8();
                    TEXT_SetText(hItem, "Untested");
                    TEXT_SetTextColor(hItem, GUI_WHITE);
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                }
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_46);
                sprintf(buf,"%.2f",dis_init_c);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,buf);
                SET_Current_Laod = set_init_c;

                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_47);
                sprintf(buf,"%.2f",dis_sbs_c);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,buf);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_82);
                TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_FontD24x32);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,"0.00");
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_83);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,"0.00");
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_117);
                sprintf(buf,"%4d",short_time);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,buf);
                
                hItem = WM_GetDialogItem(pMsg->hWin,ID_TEXT_122);
                sprintf(buf,"%4d",steptime);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,buf);
                
                
                break;
            }
            case set_2_off:
            {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_43);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_44);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
               
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_45);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_46);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_47);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_97);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_118);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_98);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_117);
                TEXT_SetText(hItem, "");      
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_122);
                TEXT_SetText(hItem, "");      
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                break;
            }
        }
        
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
        break;
        
  // USER START (Optionally insert additional message handling)
  // USER END
    default:
        WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateR
*/
WM_HWIN CreateR(void);
WM_HWIN CreateR(void) {
  set_sw = set_20;
  page_sw = face_r;
  track = face_r;
  con_flag = 0;
  load_sw = load_off;
  pow_sw = pow_off;
  GPIO_ResetBits(GPIOB,GPIO_Pin_13);
    GPIO_SetBits(GPIOC,GPIO_Pin_1);//OFF
  SET_Current_Laod = set_init_c;
  pass = 0;
  hWinR = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWinR;
}

WM_HWIN ResetR(void) {
  hWinR = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWinR;
}


void OC_OP_DOWN(void);
void OC_OP_DOWN(void)
{
    switch(set_sw)
    {
        case set_20:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_44);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_45);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            set_sw = set_21;
            break;
        }
        case set_21:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_45);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_118);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            set_sw = set_64;
            break;
        }
        case set_64:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_118);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_43);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            set_sw = set_67;
            break;
        }
        case set_67:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_43);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_44);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            set_sw = set_20;
            break;
        }
        
    }
    
}

void OC_OP_UP(void);
void OC_OP_UP(void)
{
    switch(set_sw)
    {
        case set_20:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_44);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_43);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            set_sw = set_67;
            break;
        }
        case set_21:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_45);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_44);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            set_sw = set_20;
            break;
        }
        case set_64:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_118);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_45);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            set_sw = set_21;
            break;
        }
        case set_67:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_43);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_118);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            set_sw = set_64;
            break;
        }
        
    }
    
}

//内阻页面过流设置
void OC_SET(void);
void OC_SET(void) {
    vu8 i;
    char  buf[5];

    float dis_init_c;
    float dis_sbs_c;
    vu16 dis_steptime = steptime;
    switch(set_sw)
    {
        case set_20:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_44);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_46);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            for(i=0;i<5;i++)
            {
                set_limit[i] = '\0';
            }
            set_sw = set_22;
            break;
        }
        case set_22:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_46);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            SET_Current_Laod = set_init_c;
            if(SET_Current_Laod > 1500){
                SET_Current_Laod = 0;
            }
            dis_init_c = (float)set_init_c/100;
            sprintf(buf,"%.2f",dis_init_c);
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_44);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            Write_Limits();
            
            set_sw = set_20;
            bit =1;
            dot_flag = 0;
            break;
        }
        case set_21:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_45);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_47);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            for(i=0;i<5;i++)
            {
                set_limit[i] = '\0';
            }
            
            set_sw = set_23;
            break;
        }
        case set_23:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_47);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            dis_sbs_c = (float)set_sbs_c/100;
            sprintf(buf,"%.2f",dis_sbs_c);
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_45);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            Write_Limits();
            
            set_sw = set_21;
            bit = 1;
            dot_flag = 0;
            break;
        }
        case set_64:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_118);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_97);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            for(i=0;i<5;i++)
            {
                set_limit[i] = '\0';
            }
            
            set_sw = set_65;
            break;
        }
        case set_65:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_97);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            gate_v = (float)dis_gate_v/100;
            sprintf(buf,"%.2f",gate_v);
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_118);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            Write_Limits();
            
            set_sw = set_64;
            bit = 1;
            dot_flag = 0;
            break;
        }
        case set_67:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_43);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_122);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            for(i=0;i<5;i++)
            {
                set_limit[i] = '\0';
            }
            
            set_sw = set_68;
            break;
        }
        case set_68:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_122);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            sprintf(buf,"%4d",dis_steptime);
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_43);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            Write_Limits();
            
            set_sw = set_67;
            bit = 1;
            dot_flag = 0;
            Wrtite_step();
            break;
        }
    }
}

//内阻页面数字输入
          
void INPUT_C(char* num){
    switch(set_sw)
    {
        case set_22:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_46);
            switch(bit){
                case 1:
                {
                    set_init_c = atoi(num) * 100;
                    strcat(set_limit,num);            
                    TEXT_SetText(hItem,set_limit);
                    
                    bit = 2;
                    break;
                }
                case 2:
                {
                    strcat(set_limit,num);            
                    TEXT_SetText(hItem,set_limit);
                    if(set_limit[1] == 0x2e)//判断输入是否为小数点
                    {
                        dot_flag = 1;
                    }else{
                        set_init_c = set_init_c * 10 + atoi(num) * 100;
                    }
                    bit = 3;
                    break;
                }
                case 3:
                {
                    strcat(set_limit,num);
                    TEXT_SetText(hItem,set_limit);
                    if(dot_flag == 0)
                    {
                        if(set_limit[2] == 0x2e)//判断输入是否为小数点
                        {                            
                            dot_flag = 2;
                        }else{
                            set_init_c = 0;
                        }
                    }else{
                        set_init_c = set_init_c + atoi(num) * 10;
                    }                  
                    bit = 4;
                    break;
                }
                case 4:
                {
                    strcat(set_limit,num);
                    TEXT_SetText(hItem,set_limit);
                    if(dot_flag == 0)
                    {
                        SET_Current_Laod = 0;
                    }else if(dot_flag == 2){
                        set_init_c = set_init_c + atoi(num) * 10;
                    }else{
                        set_init_c = set_init_c + atoi(num);
                    }                  
                    bit = 5;
                    break;
                }
                case 5:
                {
                    strcat(set_limit,num);
                    TEXT_SetText(hItem,set_limit);
                    if(dot_flag == 0)
                    {
                        set_init_c = 0;
                    }else if(dot_flag == 1){
                        set_init_c = set_init_c;
                    }else{
                        set_init_c = set_init_c + atoi(num);
                    }                 
                    bit = 1;
                    break;
                }
            }
            break;        
        }
        case set_23:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_47);
            switch(bit){
                case 1:
                {
                    set_sbs_c = atoi(num) * 100;
                    strcat(set_limit,num);            
                    TEXT_SetText(hItem,set_limit);
                    
                    bit = 2;
                    break;
                }
                case 2:
                {
                    strcat(set_limit,num);            
                    TEXT_SetText(hItem,set_limit);
                    if(set_limit[1] == 0x2e)//判断输入是否为小数点
                    {
                        dot_flag = 1;
                    }else{
                        set_sbs_c = set_sbs_c * 10 + atoi(num) * 100;
                    }
                    bit = 3;
                    break;
                }
                case 3:
                {
                    strcat(set_limit,num);
                    TEXT_SetText(hItem,set_limit);
                    if(dot_flag == 0)
                    {
                        if(set_limit[2] == 0x2e)//判断输入是否为小数点
                        {                            
                            dot_flag = 2;
                        }else{
                            set_sbs_c = 0;
                        }
                    }else{
                        set_sbs_c = set_sbs_c + atoi(num) * 10;
                    }                  
                    bit = 4;
                    break;
                }
                case 4:
                {
                    strcat(set_limit,num);
                    TEXT_SetText(hItem,set_limit);
                    if(dot_flag == 0)
                    {
                        set_sbs_c = 0;
                    }else if(dot_flag == 2){
                        set_sbs_c = set_sbs_c + atoi(num) * 10;
                    }else{
                        set_sbs_c = set_sbs_c + atoi(num);
                    }                  
                    bit = 5;
                    break;
                }
                case 5:
                {
                    strcat(set_limit,num);
                    TEXT_SetText(hItem,set_limit);
                    if(dot_flag == 0)
                    {
                        set_sbs_c = 0;
                    }else if(dot_flag == 1){
                        set_sbs_c = set_sbs_c;
                    }else{
                        set_sbs_c = set_sbs_c + atoi(num);
                    }                 
                    bit = 1;
                    break;
                }
            }
            break;        
        }
        case set_65:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_97);
            switch(bit){
                case 1:
                {
                    dis_gate_v = atoi(num) * 100;
                    strcat(set_limit,num);            
                    TEXT_SetText(hItem,set_limit);
                    
                    bit = 2;
                    break;
                }
                case 2:
                {
                    strcat(set_limit,num);            
                    TEXT_SetText(hItem,set_limit);
                    if(set_limit[1] == 0x2e)//判断输入是否为小数点
                    {
                        dot_flag = 1;
                    }else{
                        dis_gate_v = dis_gate_v * 10 + atoi(num) * 100;
                    }
                    bit = 3;
                    break;
                }
                case 3:
                {
                    strcat(set_limit,num);
                    TEXT_SetText(hItem,set_limit);
                    if(dot_flag == 0)
                    {
                        if(set_limit[2] == 0x2e)//判断输入是否为小数点
                        {                            
                            dot_flag = 2;
                        }else{
                            dis_gate_v = 0;
                        }
                    }else{
                        dis_gate_v = dis_gate_v + atoi(num) * 10;
                    }                  
                    bit = 4;
                    break;
                }
                case 4:
                {
                    strcat(set_limit,num);
                    TEXT_SetText(hItem,set_limit);
                    if(dot_flag == 0)
                    {
                        dis_gate_v = 0;
                    }else if(dot_flag == 2){
                        dis_gate_v = dis_gate_v + atoi(num) * 10;
                    }else{
                        dis_gate_v = dis_gate_v + atoi(num);
                    }                  
                    bit = 5;
                    break;
                }
                case 5:
                {
                    strcat(set_limit,num);
                    TEXT_SetText(hItem,set_limit);
                    if(dot_flag == 0)
                    {
                        dis_gate_v = 0;
                    }else if(dot_flag == 1){
                        dis_gate_v = dis_gate_v;
                    }else{
                        dis_gate_v = dis_gate_v + atoi(num);
                    }                 
                    bit = 1;
                    break;
                }
            }
            break;        
        }
        case set_68:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_122);
            switch(bit){
                case 1:
                {
                    steptime = atoi(num);
                    strcat(set_limit,num);            
                    TEXT_SetText(hItem,set_limit);
                    bit = 2;
                    break; 
                }
                case 2:
                {
                    steptime = steptime * 10 + atoi(num);
                    strcat(set_limit,num);            
                    TEXT_SetText(hItem,set_limit);
                    bit = 3;
                    break; 
                }
                case 3:
                {
                    steptime = steptime * 10 + atoi(num);
                    strcat(set_limit,num);            
                    TEXT_SetText(hItem,set_limit);
                    bit = 4;
                    break; 
                }
                case 4:
                {
                    steptime = steptime * 10 + atoi(num);
                    strcat(set_limit,num);            
                    TEXT_SetText(hItem,set_limit);
                    bit = 1;
                    break; 
                }
            }
            break;           
        }
        
    }
}

           
void OC_ADD(void){
    WM_HWIN hItem;
    char sbs_c[5];
    float change_sbs_c;
    static float crec1,crec2;

    if(v - DISS_Voltage > v*0.9 && para_set2 == set_2_on)
    {
//        oc_data = (float)SET_Current_Laod/100;   
        oc_data = crec2;
        SET_Current_Laod = set_init_c;
        hItem = WM_GetDialogItem(hWinR, ID_TEXT_47);
        change_sbs_c = (float)set_sbs_c/100;
        sprintf(sbs_c,"%.2f",change_sbs_c);
        TEXT_SetText(hItem,sbs_c);
        GPIO_SetBits(GPIOC,GPIO_Pin_1);//关闭负载
        LOAD_t = 0;
        oct_sw = oct_off;
        finish = 1;
        crec1 = 0;
        crec2 = 0;
        rpow = 1;
    }else{
        SET_Current_Laod = SET_Current_Laod + set_sbs_c;
        crec2 = crec1;
        crec1 = DISS_Current;
        if(crec1 < crec2)
        {
            oc_data = crec2;
            SET_Current_Laod = set_init_c;
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_47);
            change_sbs_c = (float)set_sbs_c/100;
            sprintf(sbs_c,"%.2f",change_sbs_c);
            TEXT_SetText(hItem,sbs_c);
            GPIO_SetBits(GPIOC,GPIO_Pin_1);//关闭负载
            LOAD_t = 0;
            oct_sw = oct_off;
            finish = 1;
            crec1 = 0;
            crec2 = 0;
            rpow = 1;
        }
    }        
}

void test_r(void)
{
    WM_HWIN hItem;
    if(para_set2 == set_2_off)
    {
        if(R_VLUE > set_max_r || R_VLUE < set_min_r || DISS_Voltage*100 > set_max_v || DISS_Voltage*100 < set_min_v)
        {
            if(para_set4 == set_4_on){
                BEEP_Tiggr();
            }
            TM1650_SET_LED(0x68,0x70);//FAIL灯
            GPIO_SetBits(GPIOD,GPIO_Pin_12);//
            if(R_VLUE > set_max_r || R_VLUE < set_min_r)
            {
                hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
                TEXT_SetTextColor(hItem, GUI_RED);
            }else{
                hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
                TEXT_SetTextColor(hItem, GUI_GREEN);
            }
            if(DISS_Voltage*100 > set_max_v || DISS_Voltage*100 < set_min_v){
                hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
                TEXT_SetTextColor(hItem, GUI_RED);
            }else{
                hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
                TEXT_SetTextColor(hItem, GUI_GREEN);
            }
        }else{
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
            TEXT_SetTextColor(hItem, GUI_GREEN);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
            TEXT_SetTextColor(hItem, GUI_GREEN);
            
            GPIO_ResetBits(GPIOD,GPIO_Pin_12);
            TM1650_SET_LED(0x48,0x71);
            TM1650_SET_LED(0x68,0xF2);//PASS灯
        }
    }else{
        if(finish == 0)
        {
            if(R_VLUE > set_max_r || R_VLUE < set_min_r || DISS_Voltage*100 > set_max_v || DISS_Voltage*100 < set_min_v)
            {
                if(para_set4 == set_4_on){
                    BEEP_Tiggr();
                }
                
                TM1650_SET_LED(0x68,0x70);//FAIL灯
                GPIO_SetBits(GPIOD,GPIO_Pin_12);//
                
                if(R_VLUE > set_max_r || R_VLUE < set_min_r)
                {
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
                    TEXT_SetTextColor(hItem, GUI_RED);
                }else{
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
                    TEXT_SetTextColor(hItem, GUI_GREEN);
                }
                if(DISS_Voltage*100 > set_max_v || DISS_Voltage*100 < set_min_v){
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
                    TEXT_SetTextColor(hItem, GUI_RED);
                }else{
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
                    TEXT_SetTextColor(hItem, GUI_GREEN);
                }
            }else{
                hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
                TEXT_SetTextColor(hItem, GUI_GREEN);
                hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
                TEXT_SetTextColor(hItem, GUI_GREEN);
                
                GPIO_ResetBits(GPIOD,GPIO_Pin_12);
                TM1650_SET_LED(0x48,0x71);
                TM1650_SET_LED(0x68,0xF2);//PASS灯
            }
        }else{
            if(r > set_max_r || r < set_min_r || v*100 > set_max_v || v*100 < set_min_v || oc_data*100 > set_max_c || oc_data*100 < set_min_c)
            {
                if(para_set4 == set_4_on){
                    BEEP_Tiggr();
                }
                TM1650_SET_LED(0x68,0x70);//FAIL灯
                GPIO_SetBits(GPIOD,GPIO_Pin_12);//
                if(r > set_max_r || r < set_min_r)
                {
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
                    TEXT_SetTextColor(hItem, GUI_RED);
                }else{
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
                    TEXT_SetTextColor(hItem, GUI_GREEN);
                }
                if(v*100 > set_max_v || v*100 < set_min_v){
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
                    TEXT_SetTextColor(hItem, GUI_RED);
                }else{
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
                    TEXT_SetTextColor(hItem, GUI_GREEN);
                }
                if(oc_data*100 > set_max_c || oc_data*100 < set_min_c){
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_82);
                    TEXT_SetTextColor(hItem, GUI_RED);
                }else{
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_82);
                    TEXT_SetTextColor(hItem, GUI_GREEN);
                }
            }else{
                hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
                TEXT_SetTextColor(hItem, GUI_GREEN);
                hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
                TEXT_SetTextColor(hItem, GUI_GREEN);
                hItem = WM_GetDialogItem(hWinR, ID_TEXT_82);
                TEXT_SetTextColor(hItem, GUI_GREEN);
                
                GPIO_ResetBits(GPIOD,GPIO_Pin_12);
                TM1650_SET_LED(0x48,0x71);
                TM1650_SET_LED(0x68,0xF2);//PASS灯
            }
        }
               
    }
//     else
//     {
//         TM1650_SET_LED(0x68,0x70);
//         GPIO_ResetBits(GPIOD,GPIO_Pin_12);//灭灯
//     }
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
