/******************************************************************/
/* ĻԆú                                                  				*/
/* Чڻú                                                        */
/* ŚɝúȺПͼާĦ                                             */
/* ط֟ú                                                 */
/* jϵ׽ʽQQ:                                        */


#include "MainTask.h"
#include  "gui.h"
#include "DIALOG.h"
#include "my_register.h" 
#include "my_register.h" 
#include "tm1650.h"
#include "stdio.h"
#include "stdlib.h"
#include "key.h"
#include "string.h"
#include "beep.h"

WM_HWIN hWincdc;

//extern vu8 double_sw;
vu8 set_loop_count = 1;
static vu8 second = 0;
static vu8 minute = 0;
static vu8 hour = 0;
static vu16 cutoff_time;
vu8 cutoff_flag = 0;
extern char set_limit[5];
extern vu8 dot_flag;
vu8 cdc_sw = cdc_off;
vu8 c_sw = c_on;
vu8 timer_sw = 1;

vu8 c_sum = 0;
vu8 count = 1;
vu8 status_flash = 0;
vu8 pause_flag = 0;
vu8 paused = 0;
vu16 pause_time;
vu16 restart_time;
vu8 pow_step;
vu8 cur_step;
vu8 coffv_step;
vu8 coffc_step;
vu8 charge_step;
vu16 coff[6];
int count_num(int data);
extern vu8 pass;
extern vu8 track;
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_5     (GUI_ID_USER + 0x2A)
#define ID_BUTTON_24    (GUI_ID_USER + 0x2B)
#define ID_BUTTON_25    (GUI_ID_USER + 0x2C)
#define ID_BUTTON_26    (GUI_ID_USER + 0x2D)
#define ID_BUTTON_27   	(GUI_ID_USER + 0x2E)
#define ID_BUTTON_28   	(GUI_ID_USER + 0x2F)
#define ID_BUTTON_29    (GUI_ID_USER + 0x30)
#define ID_TEXT_17     	(GUI_ID_USER + 0x31)
#define ID_TEXT_18     	(GUI_ID_USER + 0x32)
#define ID_TEXT_19     	(GUI_ID_USER + 0x33)
#define ID_TEXT_20    	(GUI_ID_USER + 0x34)
#define ID_TEXT_50    	(GUI_ID_USER + 0x6F)
#define ID_TEXT_51    	(GUI_ID_USER + 0x70)
#define ID_TEXT_52    	(GUI_ID_USER + 0x71)
#define ID_TEXT_53    	(GUI_ID_USER + 0x72)
#define ID_TEXT_54    	(GUI_ID_USER + 0x73)
#define ID_TEXT_55    	(GUI_ID_USER + 0x74)
#define ID_TEXT_56    	(GUI_ID_USER + 0x75)
#define ID_TEXT_57    	(GUI_ID_USER + 0x76)
#define ID_TEXT_58    	(GUI_ID_USER + 0x77)
#define ID_TEXT_59    	(GUI_ID_USER + 0x78)
#define ID_TEXT_60    	(GUI_ID_USER + 0x79)
#define ID_TEXT_61    	(GUI_ID_USER + 0x7A)
#define ID_TEXT_62    	(GUI_ID_USER + 0x7B)
#define ID_TEXT_63    	(GUI_ID_USER + 0x7C)
#define ID_TEXT_64    	(GUI_ID_USER + 0x7D)
#define ID_TEXT_65    	(GUI_ID_USER + 0x7E)
#define ID_TEXT_66    	(GUI_ID_USER + 0x7F)
#define ID_TEXT_67    	(GUI_ID_USER + 0x80)
#define ID_TEXT_68    	(GUI_ID_USER + 0x81)
#define ID_TEXT_69    	(GUI_ID_USER + 0x82)
#define ID_TEXT_70   	(GUI_ID_USER + 0x83)
#define ID_TEXT_71   	(GUI_ID_USER + 0x84)
#define ID_TEXT_72   	(GUI_ID_USER + 0x85)
#define ID_TEXT_73   	(GUI_ID_USER + 0x86)
#define ID_TEXT_74   	(GUI_ID_USER + 0x87)
#define ID_TEXT_75   	(GUI_ID_USER + 0x88)
#define ID_TEXT_76   	(GUI_ID_USER + 0x89)
#define ID_TEXT_77   	(GUI_ID_USER + 0x8A)
#define ID_TEXT_78   	(GUI_ID_USER + 0x8B)
#define ID_TEXT_79   	(GUI_ID_USER + 0x8C)
#define ID_TEXT_119     (GUI_ID_USER + 0x30E)


#define ID_TimerTime4    5

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
static const GUI_WIDGET_CREATE_INFO _aDialogCreate4[] = {
  { WINDOW_CreateIndirect, "G", ID_WINDOW_5, 0, 0, 480, 272, 0, 0x0, 0 },
//   { BUTTON_CreateIndirect, "Button", ID_BUTTON_24, 3, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_25, 83, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_26, 163, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_27, 243, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_28, 323, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_29, 403, 226, 77, 45, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_17, 28, 50, 64, 32, 0, 0x64, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_18, 28, 120, 64, 32, 0, 0x64, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_19, 217, 50, 32, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_20, 217, 121, 32, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_50, 320, 30, 90, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_51, 320, 55, 90, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_58, 320, 80, 90, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_59, 320, 105, 90, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_52, 320, 142, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_60, 320, 167, 80, 20, 0, 0x0, 0 },
//   { TEXT_CreateIndirect,   "Text",   ID_TEXT_61, 320, 180, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_53, 320, 205, 95, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_54, 425, 30, 53, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_55, 425, 55, 53, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_56, 425, 142, 53, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_57, 425, 205, 26, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_62, 425, 80, 53, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_63, 425, 105, 53, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_64, 425, 167, 53, 20, 0, 0x0, 0 },
//   { TEXT_CreateIndirect,   "Text",   ID_TEXT_65, 410, 180, 53, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_66, 95, 48, 150, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_67, 95, 116, 150, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_68, 95, 184, 150, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_69, 270, 32, 33, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_119, 260, 56, 50, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_70, 270, 142, 33, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_71, 385, 4, 100, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_72, 250, 4, 33, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_73, 280, 4, 33, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_74, 310, 4, 33, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_75, 275, 3, 10, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_76, 305, 3, 10, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_77, 440, 203, 20, 23, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_78, 465, 203, 20, 23, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_79, 444, 205, 40, 20, 0, 0x0, 0 },

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
  
  char buf[5];    
  
  float dis_load_c = (float)SET_Current_Laod/100;
  float dis_output_v = (float)SET_Voltage/100;
  float dis_output_c = (float)SET_Current/1000;
  float dis_c_cutoff_v = (float)cov1/100;
  float dis_c_cutoff_c = (float)coc1/1000;
  float dis_dc_cutoff_v = (float)set_dc_cutoff_v/100;
  float dis_dc_cutoff_c = (float)set_dc_cutoff_c/100;


  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
		
	case WM_PAINT:

        GUI_SetColor(GUI_WHITE);//ʨ׃ۭҊҕɫ
        GUI_FillRect(0,25,480,26);//ۭһ͵ʵП
        GUI_SetColor(GUI_ORANGE);
        GUI_SetFont(&GUI_Fontsymbol);
        GUI_UC_SetEncodeUTF8();
        GUI_SetTextMode(GUI_TM_TRANS);//ʨ׃τѾģʽΪ֗ɫ͸ķ
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
        GUI_SetColor(GUI_WHITE);//ʨ׃ǰްɫΪїɫ
        GUI_SetFont(&GUI_Font24_1);
        

        GUI_SetFont(&GUI_FontEN40);
        GUI_SetColor(GUI_LIGHTGRAY);
        GUI_DispStringAt("C:", 28, 190);
        GUI_SetColor(GUI_LIGHTGRAY);
        GUI_DispStringAt("m", 217, 196);
        GUI_DispStringAt("AH", 238, 187);
    
    
	break;
	case WM_TIMER://֨ʱģࠩлϢ
	if(WM_GetTimerId(pMsg->Data.v) == ID_TimerTime4)
	{
        if(mode_sw == mode_pow && cdc_sw == cdc_on){
            
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_66);
            sprintf(buf,"%.2f",DISS_Voltage);       
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_67);
            sprintf(buf,"%.2f",DISS_POW_Current);
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_77);
            TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,"(");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_78);
            TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,")");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_79);
            TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
            sprintf(buf,"%2d",count);
            TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_69);
            TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_70);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_72);        
            TEXT_SetText(hItem,"");

            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_73);     
            TEXT_SetText(hItem,"");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_74);      
            TEXT_SetText(hItem,"");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_75);      
            TEXT_SetText(hItem,"");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_76);      
            TEXT_SetText(hItem,"");
            
            battery_c = (int)bc_raw;
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_68);
            sprintf(buf,"%05d",battery_c);
            TEXT_SetText(hItem,buf);
            
            if(charge_step == 1)
            {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_119);
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"步骤1");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Step1");
                }
            }else if(charge_step == 2){
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_119);
                if(lang == 0)
                {
                    TEXT_SetText(hItem,"步骤2");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Step2");
                }
            }else if(charge_step == 3){
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_119);
                if(lang == 0)
                {
                    TEXT_SetText(hItem,"步骤3");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Step3");
                }
            }
            
            if(status_flash == 0){
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_71);
                TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
                if(lang == 0)
                {
                    TEXT_SetFont(hItem,&GUI_FontHZ16);//设定文本字体
                    GUI_UC_SetEncodeUTF8();
                    TEXT_SetText(hItem,"充电中");
                }else{
                    TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
                    GUI_UC_SetEncodeUTF8();
                    TEXT_SetText(hItem,"Charging");
                }
                status_flash = 1;
            }else{
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_71);
                TEXT_SetText(hItem,"");
                status_flash = 0;
            }
            if(opv2 == 0 && opv3 == 0 && opc2 == 0 && opc3 == 0)
            {
                if(cov1 == 0 || coc1 == 0)
                {
                    if(((DISS_Voltage >= (float)cov1/100 && cov1 != 0) || DISS_POW_Current < (float)coc1/1000) && cutoff_flag == 0){//判断电流是否小于截止电流，并记录时间
                        cutoff_time = GUI_GetTime()/500;
                        cutoff_flag = 1;
                    }
                    if(((DISS_Voltage >= (float)cov1/100 && cov1 != 0) || DISS_POW_Current < (float)coc1/1000) && (GUI_GetTime()/500 - cutoff_time) >= 10 )//若测量电流小于截止电流
                    {
                        if(mode_sw == mode_pow){
                            start_time = GUI_GetTime()/500;//记录开始时间
                        }
                        cutoff_flag = 0;
                        Mode_SW_CONT(0x02);//切换至负载模式
                        GPIO_ResetBits(GPIOC,GPIO_Pin_1);//开启负载
                    }
                }else{
                    if(((DISS_Voltage >= (float)cov1/100 && cov1 != 0) && DISS_POW_Current < (float)coc1/1000) && cutoff_flag == 0){//判断电流是否小于截止电流，并记录时间
                        cutoff_time = GUI_GetTime()/500;
                        cutoff_flag = 1;
                    }
                    if(((DISS_Voltage >= (float)cov1/100 && cov1 != 0) && DISS_POW_Current < (float)coc1/1000) && (GUI_GetTime()/500 - cutoff_time) >= 10 )//若测量电流小于截止电流
                    {
                        if(mode_sw == mode_pow){
                            start_time = GUI_GetTime()/500;//记录开始时间
                        }
                        cutoff_flag = 0;
                        Mode_SW_CONT(0x02);//切换至负载模式
                        GPIO_ResetBits(GPIOC,GPIO_Pin_1);//开启负载
                    }
                }
            }else if(opv3 == 0 && opc3 == 0){
                if(cov1 == 0 || coc1 == 0)
                { 
                    if(((DISS_Voltage >= (float)cov1/100 && cov1 != 0) || DISS_POW_Current < (float)coc1/1000) && cutoff_flag == 0 && charge_step == 1)
                    {//判断电流是否小于截止电流，并记录时间
                        SET_Voltage = opv2;
                        SET_Current = opc2;
                        charge_step = 2;
                    }
                }else{
                    if(((DISS_Voltage >= (float)cov1/100 && cov1 != 0) && DISS_POW_Current < (float)coc1/1000) && cutoff_flag == 0 && charge_step == 1)
                    {//判断电流是否小于截止电流，并记录时间
                        SET_Voltage = opv2;
                        SET_Current = opc2;
                        charge_step = 2;
                    }
                }
                if(cov2 == 0 || coc2 == 0)
                {
                    if(((DISS_Voltage >= (float)cov2/100 && cov2 != 0) || DISS_POW_Current < (float)coc2/1000) && cutoff_flag == 0 && charge_step == 2){//判断电流是否小于截止电流，并记录时间
                        cutoff_time = GUI_GetTime()/500;
                        cutoff_flag = 1;
                    }
                    if(((DISS_Voltage >= (float)cov2/100 && cov2 != 0) || DISS_POW_Current < (float)coc2/1000) && (GUI_GetTime()/500 - cutoff_time) >= 10 && charge_step == 2)//若测量电流小于截止电流
                    {
                        if(mode_sw == mode_pow){
                            start_time = GUI_GetTime()/500;//记录开始时间
                        }
                        cutoff_flag = 0;
                        Mode_SW_CONT(0x02);//切换至负载模式
                        GPIO_ResetBits(GPIOC,GPIO_Pin_1);//开启负载
                    }
                }else{
                    if(((DISS_Voltage >= (float)cov2/100 && cov2 != 0) && DISS_POW_Current < (float)coc2/1000) && cutoff_flag == 0 && charge_step == 2){//判断电流是否小于截止电流，并记录时间
                        cutoff_time = GUI_GetTime()/500;
                        cutoff_flag = 1;
                    }
                    if(((DISS_Voltage >= (float)cov2/100 && cov2 != 0) && DISS_POW_Current < (float)coc2/1000) && (GUI_GetTime()/500 - cutoff_time) >= 10 && charge_step == 2)//若测量电流小于截止电流
                    {
                        if(mode_sw == mode_pow){
                            start_time = GUI_GetTime()/500;//记录开始时间
                        }
                        cutoff_flag = 0;
                        Mode_SW_CONT(0x02);//切换至负载模式
                        GPIO_ResetBits(GPIOC,GPIO_Pin_1);//开启负载
                    }
                }
            }else if((opv1 != 0 || opc1 != 0) && (opv2 != 0 || opc2 != 0) && (opv3 != 0 || opc3 != 0)){
                if(cov1 == 0 || coc1 == 0)
                { 
                    if(((DISS_Voltage >= (float)cov1/100 && cov1 != 0) || DISS_POW_Current < (float)coc1/1000) && cutoff_flag == 0 && charge_step == 1)
                    {//判断电流是否小于截止电流，并记录时间
                        SET_Voltage = opv2;
                        SET_Current = opc2;
                        charge_step = 2;
                    }
                }else{
                    if(((DISS_Voltage >= (float)cov1/100 && cov1 != 0) && DISS_POW_Current < (float)coc1/1000) && cutoff_flag == 0 && charge_step == 1)
                    {//判断电流是否小于截止电流，并记录时间
                        SET_Voltage = opv2;
                        SET_Current = opc2;
                        charge_step = 2;
                    }
                }
                
                if(cov2 == 0 || coc2 == 0)
                {
                    if(((DISS_Voltage > (float)cov2/100 && cov2 != 0) || DISS_POW_Current < (float)coc2/1000) && cutoff_flag == 0 && charge_step == 2)
                    {//判断电流是否小于截止电流，并记录时间
                        SET_Voltage = opv3;
                        SET_Current = opc3;
                        charge_step = 3;
                    }
                }else{
                    if(((DISS_Voltage > (float)cov2/100 && cov2 != 0) && DISS_POW_Current < (float)coc2/1000) && cutoff_flag == 0 && charge_step == 2)
                    {//判断电流是否小于截止电流，并记录时间
                        SET_Voltage = opv3;
                        SET_Current = opc3;
                        charge_step = 3;
                    }
                }
                if(cov3 == 0 || coc3 == 0)
                {
                    if(((DISS_Voltage > (float)cov3/100 && cov3 != 0) || DISS_POW_Current < (float)coc3/1000) && cutoff_flag == 0 && charge_step == 3){//判断电流是否小于截止电流，并记录时间
                        cutoff_time = GUI_GetTime()/500;
                        cutoff_flag = 1;
                    }
                    if(((DISS_Voltage > (float)cov3/100 && cov3 != 0) || DISS_POW_Current < (float)coc3/1000) && (GUI_GetTime()/500 - cutoff_time) >= 10 && charge_step == 3)//若测量电流小于截止电流
                    {
                        if(mode_sw == mode_pow){
                            start_time = GUI_GetTime()/500;//记录开始时间
                        }
                        cutoff_flag = 0;
                        Mode_SW_CONT(0x02);//切换至负载模式
                        GPIO_ResetBits(GPIOC,GPIO_Pin_1);//开启负载
                    }
                }else{
                    if(((DISS_Voltage > (float)cov3/100 && cov3 != 0) && DISS_POW_Current < (float)coc3/1000) && cutoff_flag == 0 && charge_step == 3){//判断电流是否小于截止电流，并记录时间
                        cutoff_time = GUI_GetTime()/500;
                        cutoff_flag = 1;
                    }
                    if(((DISS_Voltage > (float)cov3/100 && cov3 != 0) && DISS_POW_Current < (float)coc3/1000) && (GUI_GetTime()/500 - cutoff_time) >= 10 && charge_step == 3)//若测量电流小于截止电流
                    {
                        if(mode_sw == mode_pow){
                            start_time = GUI_GetTime()/500;//记录开始时间
                        }
                        cutoff_flag = 0;
                        Mode_SW_CONT(0x02);//切换至负载模式
                        GPIO_ResetBits(GPIOC,GPIO_Pin_1);//开启负载
                    }
                }
            }
            
//             if(DISS_POW_Current < dis_c_cutoff_c && cutoff_flag == 0){//判断电流是否小于截止电流，并记录时间
//                 cutoff_time = GUI_GetTime()/500;
//                 cutoff_flag = 1;
//             }
//             if(((DISS_Voltage >= dis_c_cutoff_v && dis_c_cutoff_v != 0) || DISS_POW_Current < dis_c_cutoff_c) && (GUI_GetTime()/500 - cutoff_time) >= 10 )//若测量电流小于截止电流
//             {
//                 if(mode_sw == mode_pow){
//                     start_time = GUI_GetTime()/500;//记录开始时间
//                 }
//                 cutoff_flag = 0;
//                 Mode_SW_CONT(0x02);//切换至负载模式
//                 GPIO_ResetBits(GPIOC,GPIO_Pin_1);//开启负载
//             }          
        }else if(mode_sw == mode_load && cdc_sw == cdc_on){
            charge_step = 1;
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_119);
            TEXT_SetText(hItem,"");
            if(paused == 0){
                second = (GUI_GetTime()/500-start_time)%60;//秒
                minute = ((GUI_GetTime()/500-start_time)/60)%60;//分
                hour   = (GUI_GetTime()/500-start_time)/3600;//时
            }else{
                second = (GUI_GetTime()/500-restart_time + pause_time)%60;//秒 
                minute = ((GUI_GetTime()/500-restart_time + pause_time)/60)%60;//分
                hour = ((GUI_GetTime()/500-restart_time) + pause_time)/3600;//时
            }
            
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_72);
            sprintf(buf,"%02d",hour);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
            GUI_UC_SetEncodeUTF8();        
            TEXT_SetText(hItem,buf);

            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_73);
            sprintf(buf,"%02d",minute);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
            GUI_UC_SetEncodeUTF8();        
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_74);
            sprintf(buf,"%02d",second);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
            GUI_UC_SetEncodeUTF8();        
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_75);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
            GUI_UC_SetEncodeUTF8();        
            TEXT_SetText(hItem,":");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_76);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
            GUI_UC_SetEncodeUTF8();        
            TEXT_SetText(hItem,":");
            
            
            
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_66);
            sprintf(buf,"%.2f",DISS_Voltage);       
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_67);
            sprintf(buf,"%.2f",DISS_Current);       
            TEXT_SetText(hItem,buf);
            
            battery_c = (int)(((float)(second + minute*60 + hour * 3600)/3600 * dis_load_c)*1000);
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_68);
            sprintf(buf,"%05d",battery_c);
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_69);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_70);
            TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
            
            if(status_flash == 0){
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_71);
                TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
                if(lang == 0)
                {
                    TEXT_SetFont(hItem,&GUI_FontHZ16);//设定文本字体
                    GUI_UC_SetEncodeUTF8();        
                    TEXT_SetText(hItem,"放电中");
                }else{
                    TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
                    GUI_UC_SetEncodeUTF8();        
                    TEXT_SetText(hItem,"Discharging");
                }
                status_flash = 1;
            }else{
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_71);
                TEXT_SetText(hItem,"");
                status_flash = 0;
            }
            if(pause_flag == 1){
                GPIO_SetBits(GPIOC,GPIO_Pin_1);//关闭负载
                cdc_sw = cdc_off;
                paused = 1;
                
                pause_time = second + minute*60 + hour*3600;
            }
            
            if(DISS_Voltage < dis_dc_cutoff_v && cutoff_flag == 0)
            {
                cutoff_time = GUI_GetTime()/500;
                cutoff_flag = 1;
            }
            
            if(DISS_Voltage < dis_dc_cutoff_v && (GUI_GetTime()/500 - cutoff_time) >= 10)//若测量电压小于截止电压
            {
                if(mode_sw == mode_load){
                    end_time = GUI_GetTime()/500;//记录结束时间
                    count++;
                }
                        
                GPIO_SetBits(GPIOC,GPIO_Pin_1);//关闭负载
                if(count > set_loop_count){
                    cdc_sw = cdc_off;//关闭充放电模式
                    battery_c = (c_sum + (int)(((float)(end_time - start_time)/3600 * dis_load_c)*1000))/set_loop_count;                    
                    count = 1;
                    
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_68);
                    sprintf(buf,"%05d",battery_c);
                    TEXT_SetText(hItem,buf);
                    
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_71);
                    TEXT_SetText(hItem,"");
                    
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_72);       
                    TEXT_SetText(hItem,"");

                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_73);     
                    TEXT_SetText(hItem,"");
                    
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_74);      
                    TEXT_SetText(hItem,"");
                    
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_75);       
                    TEXT_SetText(hItem,"");
                    
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_76);       
                    TEXT_SetText(hItem,"");
                    
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_77);
                    TEXT_SetText(hItem,"");
                        
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_78);
                    TEXT_SetText(hItem,"");
                    
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_79);
                    TEXT_SetText(hItem,"");
                    
                }else{
                    c_sum = c_sum + (int)(((float)(end_time - start_time)/3600 * dis_load_c)*1000);
                    Mode_SW_CONT(0x03);//切换至电源模式
//                     hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_68);
//                     sprintf(buf,"%05d",battery_c);
//                     TEXT_SetText(hItem,buf);
                    GPIO_SetBits(GPIOB,GPIO_Pin_13);//打开稳压电源输出
                    cutoff_flag = 0;                           
                }
            }
        }else if(pause_flag == 1 && battery_c != 0){
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_66);
            sprintf(buf,"%.2f",0.00);       
            TEXT_SetText(hItem,buf);
                
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_67);
            sprintf(buf,"%.2f",0.00);       
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_69);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_70);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色   
                
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_71);
            TEXT_SetText(hItem,"");
            
        }else if(cdc_sw == cdc_off){
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_66);
            sprintf(buf,"%.2f",0.00);       
            TEXT_SetText(hItem,buf);
                
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_67);
            sprintf(buf,"%.2f",0.00);       
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_119);
            TEXT_SetText(hItem,"");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_69);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_70);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_71);
            TEXT_SetText(hItem,"");
        }            
		WM_RestartTimer(pMsg->Data.v, 497);//شλ֨ʱǷ˽ֵԽճˢтʱݤԽ׌
	}
	break;
    
		
  case WM_INIT_DIALOG:
    //
    // Initialization of 'R'
	
    //
        hItem = pMsg->hWin;
        WINDOW_SetBkColor(hItem, GUI_BLACK);
		WM_CreateTimer(hItem,ID_TimerTime4,500,0);//ԴݨѾ԰ࠚ֨ʱǷ

        if(lang ==0)
        {
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_25);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//ʨ֨дťτѾؖͥ
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"内阻测试");
        
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_26);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//ʨ֨дťτѾؖͥ
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"程控负载");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_27);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//ʨ֨дťτѾؖͥ
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"程控电源");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_28);
            BUTTON_SetPressed(hItem,1);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//ʨ֨дťτѾؖͥ
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"充放电");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_29);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
            BUTTON_SetFont      (hItem,&GUI_FontHZ16);//ʨ֨дťτѾؖͥ
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"曲线");
        }else{
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_25);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//ʨ֨дťτѾؖͥ
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"I.R. TEST");
        
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_26);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//ʨ֨дťτѾؖͥ
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"LOAD");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_27);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//ʨ֨дťτѾؖͥ
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"POWER");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_28);
            BUTTON_SetPressed(hItem,1);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//ʨ֨дťτѾؖͥ
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"C&DC");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_29);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
            BUTTON_SetFont      (hItem,&GUI_Font16B_ASCII);//ʨ֨дťτѾؖͥ
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"GRAPH");
        }
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_17);
		TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontEN40);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"V:");
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_18);
		TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontEN40);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"I:");
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_19);
		TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontEN40);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"V");
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_20);
		TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontEN40);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"A");
        
        if(lang == 0)
        {
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_50);
            TEXT_SetTextColor(hItem, GUI_BLACK);//设置字体颜色
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
            GUI_UC_SetEncodeUTF8(); 
            TEXT_SetText(hItem,"输出电压1");        
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_51);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,"限制电流1");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_58);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,"截止电压1");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_59);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,"截止电流1");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_52);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,"负载电流");

            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_60);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,"截止电压");
            
    //         hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_61);
    // 		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
    //         TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
    // 		GUI_UC_SetEncodeUTF8();
    // 		TEXT_SetText(hItem,"截止电流");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_53);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,"循环次数");
        }else{
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_50);
            TEXT_SetTextColor(hItem, GUI_BLACK);//设置字体颜色
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
            GUI_UC_SetEncodeUTF8(); 
            TEXT_SetText(hItem,"Output V1");        
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_51);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,"Limiting C1");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_58);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,"Cutoff V1");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_59);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,"Cutoff C1");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_52);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,"Load C");

            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_60);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,"Cutoff V");
            
    //         hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_61);
    // 		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
    //         TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
    // 		GUI_UC_SetEncodeUTF8();
    // 		TEXT_SetText(hItem,"截止电流");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_53);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,"Cycle times");
        }
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_54);
        sprintf(buf,"%.2f",dis_output_v);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_55);
        sprintf(buf,"%.2f",dis_output_c);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_56);
        sprintf(buf,"%.2f",dis_load_c);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_57);
        sprintf(buf,"%2d",set_loop_count);
        TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
        GUI_UC_SetEncodeUTF8();        
        TEXT_SetText(hItem,buf);            


        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_62);
        sprintf(buf,"%.2f",dis_c_cutoff_v);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_63);
        sprintf(buf,"%.2f",dis_c_cutoff_c);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_64);
        sprintf(buf,"%.2f",dis_dc_cutoff_v);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);
        
//         hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_65);
//         sprintf(dc_cutoff_c,"%.2f",dis_dc_cutoff_c);
// 		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
//         TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
// 		GUI_UC_SetEncodeUTF8();        
// 		TEXT_SetText(hItem,dc_cutoff_c);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_66);
        sprintf(buf,"%.2f",0.00);
        TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontD24x32);//设定文本字体
        GUI_UC_SetEncodeUTF8();        
        TEXT_SetText(hItem,buf);
            
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_67);
        sprintf(buf,"%.2f",0.00);
        TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontD24x32);//设定文本字体
        GUI_UC_SetEncodeUTF8();        
        TEXT_SetText(hItem,buf);    
            
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_68);
        sprintf(buf,"%05d",0);
        TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontD24x32);//设定文本字体
        GUI_UC_SetEncodeUTF8();        
        TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_69);
        TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        if(lang == 0)
        {
            TEXT_SetFont(hItem,&GUI_FontHZ16);//设定文本字体
            GUI_UC_SetEncodeUTF8();        
            TEXT_SetText(hItem,"充电");
        }else{
            TEXT_SetFont(hItem,&GUI_FontHZ16);//设定文本字体
            GUI_UC_SetEncodeUTF8();        
            TEXT_SetText(hItem,"Charge");
        }
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_77);
        TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
        GUI_UC_SetEncodeUTF8();
        TEXT_SetText(hItem,"");
            
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_78);
        TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
        GUI_UC_SetEncodeUTF8();
        TEXT_SetText(hItem,"");
            
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_79);
        TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
        GUI_UC_SetEncodeUTF8();
        TEXT_SetText(hItem,"");
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_119);
        TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
        GUI_UC_SetEncodeUTF8();        
        TEXT_SetText(hItem,"");
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_70);
        TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        if(lang == 0)
        {
            TEXT_SetFont(hItem,&GUI_FontHZ16);//设定文本字体
            GUI_UC_SetEncodeUTF8();        
            TEXT_SetText(hItem,"放电");
        }else{
            TEXT_SetFont(hItem,&GUI_FontHZ16);//设定文本字体
            GUI_UC_SetEncodeUTF8();        
            TEXT_SetText(hItem,"Discharge");
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
WM_HWIN CreateCDC(void);
WM_HWIN CreateCDC(void) {
  page_sw = face_cdc;
  set_sw = set_26;
  pass = 0;
  track = face_cdc;
  SET_Voltage = opv1;
  SET_Current = opc1;
  SET_Current_Laod = cdc_dc;
  load_sw = load_off;
  pow_sw = pow_off;
  TM1650_SET_LED(0x68,0x70);
  GPIO_ResetBits(GPIOD,GPIO_Pin_12);//���
  GPIO_ResetBits(GPIOB,GPIO_Pin_13);
    GPIO_SetBits(GPIOC,GPIO_Pin_1);//OFF
//  double_sw = face_cdc;
  hWincdc = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbDialog, WM_HBKWIN, 0, 0);
  return hWincdc;
}

WM_HWIN ResetCDC(void) {
  hWincdc = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbDialog, WM_HBKWIN, 0, 0);
  return hWincdc;
}


void CDC_OP_DOWN(void);
void CDC_OP_DOWN(void)
{
    switch(set_sw)
    {
        case set_26:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_50);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_51);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            
            set_sw = set_27;
            break;
        }
        case set_27:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_51);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_58);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_28;
            break;
        }
        case set_28:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_58);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_59);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_29;
            break;
        }
        case set_29:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_59);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_52);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_34;
            break;
        }
        case set_34:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_52);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_60);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_35;
            break;
        }
        case set_35:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_60);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_53);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_37;
            break;
        }
//         case set_36:
//         {
//             WM_HWIN hItem;
//             WM_InvalidateWindow(hWincdc);
//             hItem = WM_GetDialogItem(hWincdc, ID_TEXT_61);
//             TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
//                
//             hItem = WM_GetDialogItem(hWincdc, ID_TEXT_53);
//             TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色

//             set_sw = set_37;
//             break;
//         }
        case set_37:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_53);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_50);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_26;
            break;
        }
        default: break;
    }
}

void CDC_OP_UP(void);
void CDC_OP_UP(void)
{
    switch(set_sw)
    {
        case set_26:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_50);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_53);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_37;
            break;
        }
        case set_27:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_51);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_50);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_26;
            break;
        }
        case set_28:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_58);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_51);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_27;
            break;
        }
        case set_29:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_59);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_58);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_28;
            break;
        }
        case set_34:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_52);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_59);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_29;
            break;
        }
        case set_35:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_60);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_52);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_34;
            break;
        }
//         case set_36:
//         {
//             WM_HWIN hItem;
//             WM_InvalidateWindow(hWincdc);
//             hItem = WM_GetDialogItem(hWincdc, ID_TEXT_61);
//             TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
//                
//             hItem = WM_GetDialogItem(hWincdc, ID_TEXT_60);
//             TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色

//             set_sw = set_35;
//             break;
//         }
        case set_37:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_53);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_60);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_35;
            break;
        }
        default: break;
    }
}

void CDC_OP_LEFT(void);
void CDC_OP_LEFT(void)
{
    float buffer;
    char buf[5];
    WM_HWIN hItem;
    switch(set_sw)
    {
        case set_26:
        {
            
            if(pow_step == step2)
            {
                buffer = (float)opv1/100;
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_50);
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"输出电压1");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Output V1");
                }
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_54);
                sprintf(buf,"%.2f",buffer);
                TEXT_SetText(hItem,buf);
                pow_step = step1;
            }else if(pow_step == step3){
                buffer = (float)opv2/100;
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_50);
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"输出电压2");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Output V2");
                }
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_54);
                sprintf(buf,"%.2f",buffer);
                TEXT_SetText(hItem,buf);
                pow_step = step2;
            }
        }break;
        case set_27:
        {
            if(cur_step == step3)
            {
                buffer = (float)opc2/1000;
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_51);
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"限制电流2");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Limiting C2");
                }
                
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_55);
                sprintf(buf,"%.2f",buffer);
                TEXT_SetText(hItem,buf);
                
                cur_step = step2;
            }else if(cur_step == step2){
                buffer = (float)opc1/1000;
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_51);
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"限制电流1");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Limiting C1");
                }
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_55);
                sprintf(buf,"%.2f",buffer);
                TEXT_SetText(hItem,buf);
                cur_step = step1;
            }
        }break;
        case set_28:
        {
            
            if(coffv_step == step3)
            {
                buffer = (float)cov2/100;
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_58);
                
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"截止电压2");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Cutoff V2");
                }
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_62);
                sprintf(buf,"%.2f",buffer);
                TEXT_SetText(hItem,buf);
                coffv_step = step2;
            }else if(coffv_step == step2){
                buffer = (float)cov1/100;
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_58);
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"截止电压1");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Cutoff V1");
                }
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_62);
                sprintf(buf,"%.2f",buffer);
                TEXT_SetText(hItem,buf);
                coffv_step = step1;
            }
        }break;
        case set_29:
        {
            
            if(coffc_step == step3)
            {
                buffer = (float)coc2/1000;
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_59);
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"截止电流2");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Cutoff C2");
                }
                
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_63);
                sprintf(buf,"%.2f",buffer);
                TEXT_SetText(hItem,buf);
                coffc_step = step2;
            }else if(coffc_step == step2){
                buffer = (float)coc1/1000;;
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_59);
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"截止电流1");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Cutoff C1");
                }
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_63);
                sprintf(buf,"%.2f",buffer);
                TEXT_SetText(hItem,buf);
                coffc_step = step1;
            }
        }break;
    }
}

void CDC_OP_RIGHT(void);
void CDC_OP_RIGHT(void)
{
    float buffer;
    char buf[5];
    WM_HWIN hItem;
    switch(set_sw)
    {
        case set_26:
        {
            
            if(pow_step == step1)
            {
                buffer = (float)opv2/100;
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_50);
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"输出电压2");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Output V2");
                }
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_54);
                sprintf(buf,"%.2f",buffer);
                TEXT_SetText(hItem,buf);
                pow_step = step2;
            }else if(pow_step == step2){
                buffer = (float)opv3/100;
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_50);
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"输出电压3");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Output V3");
                }
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_54);
                sprintf(buf,"%.2f",buffer);
                TEXT_SetText(hItem,buf);
                pow_step = step3;
            }
        }break;
        case set_27:
        {
            
            if(cur_step == step1)
            {
                buffer = (float)opc2/1000;
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_51);
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"限制电流2");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Limiting C2");
                }
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_55);
                sprintf(buf,"%.2f",buffer);
                TEXT_SetText(hItem,buf);
                cur_step = step2;
            }else if(cur_step == step2){
                buffer = (float)opc3/1000;
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_51);
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"限制电流3");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Limiting C3");
                }
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_55);
                sprintf(buf,"%.2f",buffer);
                TEXT_SetText(hItem,buf);
                cur_step = step3;
            }
        }break;
        case set_28:
        {
            
            if(coffv_step == step1)
            {
                buffer = (float)cov2/100;
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_58);
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"截止电压2");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Cutoff V2");
                }
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_62);
                sprintf(buf,"%.2f",buffer);
                TEXT_SetText(hItem,buf);
                coffv_step = step2;
            }else if(coffv_step == step2){
                buffer = (float)cov3/100;
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_58);
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"截止电压3");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Cutoff V3");
                }
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_62);
                sprintf(buf,"%.2f",buffer);
                TEXT_SetText(hItem,buf);
                coffv_step = step3;
            }
        }break;
        case set_29:
        {
            
            if(coffc_step == step1)
            {
                buffer = (float)coc2/1000;
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_59);
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"截止电流2");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Cutoff C2");
                }
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_63);
                sprintf(buf,"%.2f",buffer);
                TEXT_SetText(hItem,buf);
                coffc_step = step2;
            }else if(coffc_step == step2){
                buffer = (float)coc3/1000;
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_59);
                if(lang == 0)
                {
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                    TEXT_SetText(hItem,"截止电流3");
                }else{
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                    TEXT_SetText(hItem,"Cutoff C3");
                }
                hItem = WM_GetDialogItem(hWincdc, ID_TEXT_63);
                sprintf(buf,"%.2f",buffer);
                TEXT_SetText(hItem,buf);
                coffc_step = step3;
            }
        }break;
    }
}

//充放电界面设置
void CDC_SET(void);
void CDC_SET(void)
{
    vu8 i;
    char buf[5];
    
    float dis_load_c;
    float dis_output_v;
    float dis_output_c;
    float dis_c_cutoff_v = (float)set_c_cutoff_v/100;
    float dis_c_cutoff_c = (float)set_c_cutoff_c/100;
    float dis_dc_cutoff_v = (float)set_dc_cutoff_v/100;
    float dis_dc_cutoff_c = (float)set_dc_cutoff_c/100;
    switch(set_sw)
    {
        case set_26:
        {
            
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_50);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_54);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);
            for(i=0;i<5;i++)
            {
                set_limit[i] = '\0';
            }
            
            set_sw = set_30;
            bit = 1;
            break;
        }
        case set_30:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_54);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
            if(pow_step == step1)
            {
                SET_Voltage = opv1;
            }else if(pow_step == step2){
                SET_Voltage = opv2;
            }else if(pow_step == step3){
                SET_Voltage = opv3;
            }
//            SET_Voltage = opv1;
            dis_output_v = (float)SET_Voltage/100;
            sprintf(buf,"%.2f",dis_output_v);
            TEXT_SetText(hItem,buf);
            
            
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_50);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_26;
            bit = 1;
            dot_flag = 0;
            Write_Limits();
            break;
        }
        case set_27:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_51);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
            for(i=0;i<5;i++)
            {
                set_limit[i] = '\0';
            }
            
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_55);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_31;
            break;
        }
        case set_31:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_55);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
            if(cur_step == step1)
            {
                SET_Current = opc1;
            }else if(cur_step == step2){
                SET_Current = opc2;
            }else if(cur_step == step3){
                SET_Current = opc3;
            }
//            SET_Current = cdc_cc;
            if(SET_Current > 5000)
            {
                SET_Current = 5000;               
            }
            dis_output_c = (float)SET_Current/1000;
            sprintf(buf,"%.2f",dis_output_c);
            TEXT_SetText(hItem,buf);
            
            
            
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_51);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_27;
            bit = 1;
            dot_flag = 0;
            Write_Limits();
            break;
        }
        case set_28:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_58);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
            for(i=0;i<5;i++)
            {
                set_limit[i] = '\0';
            }
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_62);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_38;
            break;
        }
        case set_38:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_62);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            if(coffv_step == step1)
            {
                dis_c_cutoff_v = (float)cov1/100;
            }else if(coffv_step == step2){
                dis_c_cutoff_v = (float)cov2/100;;
            }else if(coffv_step == step3){
                dis_c_cutoff_v = (float)cov3/100;;
            }
            
            sprintf(buf,"%.2f",dis_c_cutoff_v);
            TEXT_SetText(hItem,buf);
            
            
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_58);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_28;
            bit = 1;
            dot_flag = 0;
            Write_Limits();
            break;
        }
        case set_29:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_59);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
            for(i=0;i<5;i++)
            {
                set_limit[i] = '\0';
            }
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_63);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_39;
            break;
        }
        case set_39:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_63);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            if(coffc_step == step1)
            {
                dis_c_cutoff_c = (float)coc1/1000;
            }else if(coffc_step == step2){
                dis_c_cutoff_c = (float)coc2/1000;
            }else if(coffc_step == step3){
                dis_c_cutoff_c = (float)coc3/1000;
            } 
            
            sprintf(buf,"%.2f",dis_c_cutoff_c);
            TEXT_SetText(hItem,buf);
              
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_59);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_29;
            bit = 1;
            dot_flag = 0;
            Write_Limits();
            break;
        }
        case set_35:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_60);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
            for(i=0;i<5;i++)
            {
                set_limit[i] = '\0';
            }
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_64);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_40;
            break;
        }
        case set_40:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_64);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            sprintf(buf,"%.2f",dis_dc_cutoff_v);
            TEXT_SetText(hItem,buf);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_60);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_35;
            bit = 1;
            dot_flag = 0;
            Write_Limits();
            break;
        }
        case set_36:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_61);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
            for(i=0;i<5;i++)
            {
                set_limit[i] = '\0';
            }
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_65);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_41;
            break;
        }
        case set_41:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_65);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            sprintf(buf,"%.2f",dis_dc_cutoff_c);
            TEXT_SetText(hItem,buf);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_61);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_36;
            bit = 1;
            dot_flag = 0;
            break;
        }
        case set_34:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_52);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
            for(i=0;i<5;i++)
            {
                set_limit[i] = '\0';
            }
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_56);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_32;
            break;
        }
        case set_32:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_56);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
            SET_Current_Laod = cdc_dc;
            if(SET_Current_Laod > 1500){
                SET_Current_Laod = 0;
            }
            dis_load_c = (float)SET_Current_Laod/100;
            sprintf(buf,"%.2f",dis_load_c);
            TEXT_SetText(hItem,buf);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_52);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            set_sw = set_34;
            bit = 1;
            dot_flag = 0;
            Write_Limits();
            break;
        }
        case set_37:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_53);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_57);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);
            

            set_sw = set_33;
            break;
        }
        case set_33:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_57);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
               
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_53);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            set_sw = set_37;
            bit = 1;
            dot_flag = 0;
            Write_Limits();
            break;
        }        
        default: break;
    }
}

//充放电界面数字键盘输入
           
void INPUT_CDC(char* num){
    char loop_count[2];
    switch(set_sw){
        case set_30:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_54);
            
            switch(bit){
                case 1:
                {
                    if(pow_step == step1)
                    {
                        opv1 = atoi(num) * 100;
                    }else if(pow_step == step2){
                        opv2 = atoi(num) * 100;
                    }else if(pow_step == step3){
                        opv3 = atoi(num) * 100;
                    }
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
                        if(pow_step == step1)
                        {
                            opv1 = opv1 * 10 + atoi(num) * 100;
                        }else if(pow_step == step2){
                            opv2 = opv2 * 10 + atoi(num) * 100;
                        }else if(pow_step == step3){
                           opv3 = opv3 * 10 + atoi(num) * 100;
                        }
                        
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
                            if(pow_step == step1)
                            {
                               opv1 = /*3000*/ 6000;
                            }else if(pow_step == step2){
                                opv2 = /*3000*/ 6000;
                            }else if(pow_step == step3){
                               opv3 =  /*3000*/ 6000;
                            }
                            
                        }
                    }else{
                        if(pow_step == step1)
                            {
                               opv1 = opv1 + atoi(num) * 10;
                            }else if(pow_step == step2){
                                opv2 = opv2 + atoi(num) * 10;
                            }else if(pow_step == step3){
                               opv3 = opv3 + atoi(num) * 10;
                            }
                        
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
                        if(pow_step == step1)
                            {
                               opv1 = /*3000*/ 6000;
                            }else if(pow_step == step2){
                                opv2 = /*3000*/ 6000;
                            }else if(pow_step == step3){
                               opv3 =  /*3000*/ 6000;
                            }
                    }else if(dot_flag == 2){
                        if(pow_step == step1)
                            {
                               opv1 = opv1 + atoi(num) * 10;
                            }else if(pow_step == step2){
                                opv2 = opv2 + atoi(num) * 10;
                            }else if(pow_step == step3){
                               opv3 = opv3 + atoi(num) * 10;
                            }
                    }else{
                        if(pow_step == step1)
                            {
                               opv1 = opv1 + atoi(num);
                            }else if(pow_step == step2){
                                opv2 = opv2 + atoi(num);
                            }else if(pow_step == step3){
                               opv3 = opv3 + atoi(num);
                            }
//                        cdc_cv = cdc_cv + atoi(num);
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
                        if(pow_step == step1)
                            {
                               opv1 = /*3000*/ 6000;
                            }else if(pow_step == step2){
                                opv2 = /*3000*/ 6000;
                            }else if(pow_step == step3){
                               opv3 =  /*3000*/ 6000;
                            }
                    }else if(dot_flag == 1){
                        if(pow_step == step1)
                            {
                               opv1 = opv1;
                            }else if(pow_step == step2){
                                opv2 =opv2;
                            }else if(pow_step == step3){
                               opv3 =  opv3;
                            }
//                        cdc_cv = cdc_cv;
                    }else{
                        if(pow_step == step1)
                            {
                               opv1 = opv1 + atoi(num);
                            }else if(pow_step == step2){
                                opv2 = opv2 + atoi(num);
                            }else if(pow_step == step3){
                               opv3 = opv3 + atoi(num);
                            }
//                        cdc_cv = cdc_cv + atoi(num);
                    }
                                       
                    bit = 1;
                    break;
                }
            }
            break;
        }
        case set_31:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_55);
            switch(bit){
                case 1:
                {
                    if(cur_step == step1)
                    {
                        opc1 = atoi(num) * 1000;
                    }else if(cur_step == step2){
                        opc2 = atoi(num) * 1000;
                    }else if(cur_step == step3){
                        opc3 = atoi(num) * 1000;
                    }
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
                        if(cur_step == step1)
                        {
                            opc1 = opc1 * 10 + atoi(num) * 1000;
                        }else if(cur_step == step2){
                            opc2 = opc2 * 10 + atoi(num) * 1000;
                        }else if(cur_step == step3){
                            opc2 = opc2 * 10 + atoi(num) * 1000;
                        }
//                        opc1 = opc1 * 10 + atoi(num) * 1000;
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
                            if(cur_step == step1)
                            {
                                opc1 = 5000;
                            }else if(cur_step == step2){
                                opc2 = 5000;
                            }else if(cur_step == step3){
                                opc3 = 5000;
                            }
                        }
                    }else{
//                        opc1 = opc1 + atoi(num) * 100;
                        if(cur_step == step1)
                        {
                            opc1 = opc1 + atoi(num) * 100;
                        }else if(cur_step == step2){
                            opc2 = opc2 + atoi(num) * 100;
                        }else if(cur_step == step3){
                            opc3 = opc3 + atoi(num) * 100;
                        }
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
                        if(cur_step == step1)
                        {
                            opc1 = 5000;
                        }else if(cur_step == step2){
                            opc2 = 5000;
                        }else if(cur_step == step3){
                            opc3 = 5000;
                        }
                    }else if(dot_flag == 2){
                        if(cur_step == step1)
                        {
                            opc1 = opc1 + atoi(num) * 100;
                        }else if(cur_step == step2){
                            opc2 = opc2 + atoi(num) * 100;
                        }else if(cur_step == step3){
                            opc3 = opc3 + atoi(num) * 100;
                        }
                    }else{
                        if(cur_step == step1)
                        {
                            opc1 = opc1 + atoi(num) * 10;
                        }else if(cur_step == step2){
                            opc2 = opc2 + atoi(num) * 10;
                        }else if(cur_step == step3){
                            opc3 = opc3 + atoi(num) * 10;
                        }
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
                       if(cur_step == step1)
                        {
                            opc1 = 5000;
                        }else if(cur_step == step2){
                            opc2 = 5000;
                        }else if(cur_step == step3){
                            opc3 = 5000;
                        }
                    }else if(dot_flag == 1){
                        if(cur_step == step1)
                        {
                            opc1 = opc1;
                        }else if(cur_step == step2){
                            opc2 = opc2;
                        }else if(cur_step == step3){
                            opc3 = opc3;
                        }
                    }else{
                       if(cur_step == step1)
                        {
                            opc1 = opc1 + atoi(num) * 10;
                        }else if(cur_step == step2){
                            opc2 = opc2 + atoi(num) * 10;
                        }else if(cur_step == step3){
                            opc3 = opc3 + atoi(num) * 10;
                        }
                    }
                                       
                    bit = 1;
                    break;
                }
            }
            break;
        }
        case set_32:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_56);
            switch(bit){
                case 1:
                {
                    cdc_dc = atoi(num) * 100;
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
                        cdc_dc = cdc_dc * 10 + atoi(num) * 100;
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
                            cdc_dc = 0;
                        }
                    }else{
                        cdc_dc = cdc_dc + atoi(num) * 10;
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
                        cdc_dc = 0;
                    }else if(dot_flag == 2){
                        cdc_dc = cdc_dc + atoi(num) * 10;
                    }else{
                        cdc_dc = cdc_dc + atoi(num);
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
                        cdc_dc = 0;
                    }else if(dot_flag == 1){
                        cdc_dc = cdc_dc;
                    }else{
                        cdc_dc = cdc_dc + atoi(num);
                    }                 
                    bit = 1;
                    break;
                }
            }
            break;
        }
        case set_33:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_57);
            switch(bit){
                case 1:
                {
                    set_loop_count = atoi(num);                    
                    sprintf(loop_count,"%2d",set_loop_count);
                    TEXT_SetText(hItem,loop_count);
                    bit = 2;
                    break;
                }
                case 2:
                {
                    set_loop_count = set_loop_count*10 + atoi(num);                    
                    sprintf(loop_count,"%2d",set_loop_count);
                    TEXT_SetText(hItem,loop_count);
                    bit = 1;
                    break;
                }                
            }
            break;
        }
        case set_38:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_62);
            switch(bit){
                case 1:
                {
                    if(coffv_step == step1)
                    {
                        cov1 = atoi(num) * 100;
                    }else if(coffv_step == step2){
                        cov2 = atoi(num) * 100;
                    }else if(coffv_step == step3){
                        cov3 = atoi(num) * 100;
                    }
//                    set_c_cutoff_v = atoi(num) * 100;
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
                        if(coffv_step == step1)
                        {
                            cov1 = cov1 * 10 + atoi(num) * 100;
                        }else if(coffv_step == step2){
                            cov2 = cov2 * 10 + atoi(num) * 100;
                        }else if(coffv_step == step3){
                            cov3 = cov3 * 10 + atoi(num) * 100;
                        }
//                        cov1 = cov1 * 10 + atoi(num) * 100;
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
                            if(coffv_step == step1)
                            {
                                cov1 =1600;
                            }else if(coffv_step == step2){
                                cov2 = 1600;
                            }else if(coffv_step == step3){
                                cov3 = 1600;
                            }
//                            set_c_cutoff_v = 1600;
                        }
                    }else{
                            if(coffv_step == step1)
                            {
                                cov1 = cov1 + atoi(num) * 10;
                            }else if(coffv_step == step2){
                                cov2 = cov2 + atoi(num) * 10;
                            }else if(coffv_step == step3){
                                cov3 = cov3 + atoi(num) * 10;
                            }
//                        set_c_cutoff_v = set_c_cutoff_v + atoi(num) * 10;
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
                        if(coffv_step == step1)
                        {
                            cov1 =1600;
                        }else if(coffv_step == step2){
                            cov2 = 1600;
                        }else if(coffv_step == step3){
                            cov3 = 1600;
                        }
//                        set_c_cutoff_v = 1600;
                    }else if(dot_flag == 2){
                        if(coffv_step == step1)
                        {
                            cov1 = cov1 + atoi(num) * 10;
                        }else if(coffv_step == step2){
                            cov2 = cov2 + atoi(num) * 10;
                        }else if(coffv_step == step3){
                            cov3 = cov3 + atoi(num) * 10;
                        }
//                        set_c_cutoff_v = set_c_cutoff_v + atoi(num) * 10;
                    }else{
                        if(coffv_step == step1)
                        {
                            cov1 = cov1 + atoi(num);
                        }else if(coffv_step == step2){
                            cov2 = cov2 + atoi(num);
                        }else if(coffv_step == step3){
                            cov3 = cov3 + atoi(num);
                        }
//                        set_c_cutoff_v = set_c_cutoff_v + atoi(num);
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
                        if(coffv_step == step1)
                        {
                            cov1 =1600;
                        }else if(coffv_step == step2){
                            cov2 = 1600;
                        }else if(coffv_step == step3){
                            cov3 = 1600;
                        }
//                        set_c_cutoff_v = 1600;
                    }else if(dot_flag == 1){
                        if(coffv_step == step1)
                        {
                            cov1 =cov1;
                        }else if(coffv_step == step2){
                            cov2 = cov2;
                        }else if(coffv_step == step3){
                            cov3 = cov3;
                        }
//                        set_c_cutoff_v = set_c_cutoff_v;
                    }else{
                        if(coffv_step == step1)
                        {
                            cov1 = cov1 + atoi(num);
                        }else if(coffv_step == step2){
                            cov2 = cov2 + atoi(num);
                        }else if(coffv_step == step3){
                            cov3 = cov3 + atoi(num);
                        }
//                        set_c_cutoff_v = set_c_cutoff_v + atoi(num);
                    }
                                       
                    bit = 1;
                    break;
                }
            }
            break;
        }
        case set_39:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_63);
            switch(bit){
                case 1:
                {
                    if(coffc_step == step1)
                    {
                        coc1 = atoi(num) * 1000;
                    }else if(coffc_step == step2){
                        coc2 = atoi(num) * 1000;
                    }else if(coffc_step == step3){
                        coc3 = atoi(num) * 1000;
                    }  
//                    set_c_cutoff_c = atoi(num) * 100;
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
                        if(coffc_step == step1)
                        {
                            coc1 = coc1 * 10 + atoi(num) * 1000;
                        }else if(coffc_step == step2){
                            coc2 = coc2 * 10 + atoi(num) * 1000;
                        }else if(coffc_step == step3){
                            coc3 = coc3 * 10 + atoi(num) * 1000;
                        }
//                        coc1 = coc1 * 10 + atoi(num) * 100;
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
                            if(coffc_step == step1)
                            {
                                coc1 =5000;
                            }else if(coffc_step == step2){
                                coc2 = 5000;
                            }else if(coffc_step == step3){
                                coc3 = 5000;
                            } 
//                            set_c_cutoff_c = 500;
                        }
                    }else{
                        if(coffc_step == step1)
                        {
                            coc1 = coc1 + atoi(num) * 100;
                        }else if(coffc_step == step2){
                            coc2 = coc2 + atoi(num) * 100;
                        }else if(coffc_step == step3){
                            coc3 = coc3 + atoi(num) * 100;
                        }
//                        set_c_cutoff_c = set_c_cutoff_c + atoi(num) * 10;
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
                        if(coffc_step == step1)
                        {
                            coc1 =5000;
                        }else if(coffc_step == step2){
                            coc2 = 5000;
                        }else if(coffc_step == step3){
                            coc3 = 5000;
                        } 
//                        set_c_cutoff_c = 500;
                    }else if(dot_flag == 2){
                        if(coffc_step == step1)
                        {
                            coc1 = coc1 + atoi(num) * 100;
                        }else if(coffc_step == step2){
                            coc2 = coc2 + atoi(num) * 100;
                        }else if(coffc_step == step3){
                            coc3 = coc3 + atoi(num) * 100;
                        }
//                        set_c_cutoff_c = set_c_cutoff_c + atoi(num) * 10;
                    }else{
                        if(coffc_step == step1)
                        {
                            coc1 = coc1 + atoi(num) * 10;
                        }else if(coffc_step == step2){
                            coc2 = coc2 + atoi(num) * 10;
                        }else if(coffc_step == step3){
                            coc3 = coc3 + atoi(num) * 10;
                        }
//                        set_c_cutoff_c = set_c_cutoff_c + atoi(num);
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
                        if(coffc_step == step1)
                        {
                            coc1 = 5000;
                        }else if(coffc_step == step2){
                            coc2 = 5000;
                        }else if(coffc_step == step3){
                            coc3 = 5000;
                        }
//                        set_c_cutoff_c = 500;
                    }else if(dot_flag == 1){
                        if(coffc_step == step1)
                        {
                            coc1 = coc1;
                        }else if(coffc_step == step2){
                            coc2 = coc2;
                        }else if(coffc_step == step3){
                            coc3 = coc3;
                        }
//                        set_c_cutoff_c = set_c_cutoff_c;
                    }else{
                        if(coffc_step == step1)
                        {
                            coc1 = coc1 + atoi(num) * 10;
                        }else if(coffc_step == step2){
                            coc2 = coc2 + atoi(num) * 10;
                        }else if(coffc_step == step3){
                            coc3 = coc3 + atoi(num) * 10;
                        }
//                        set_c_cutoff_c = set_c_cutoff_c + atoi(num);
                    }
                                       
                    bit = 1;
                    break;
                }
            }
            break;
        }
        case set_40:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_64);
            switch(bit){
                case 1:
                {
                    set_dc_cutoff_v = atoi(num) * 100;
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
                        set_dc_cutoff_v = set_dc_cutoff_v * 10 + atoi(num) * 100;
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
                            set_dc_cutoff_v = 1600;
                        }
                    }else{
                        set_dc_cutoff_v = set_dc_cutoff_v + atoi(num) * 10;
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
                        set_dc_cutoff_v = 1600;
                    }else if(dot_flag == 2){
                        set_dc_cutoff_v = set_dc_cutoff_v + atoi(num) * 10;
                    }else{
                        set_dc_cutoff_v = set_dc_cutoff_v + atoi(num);
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
                        set_dc_cutoff_v = 1600;
                    }else if(dot_flag == 1){
                        set_dc_cutoff_v = set_dc_cutoff_v;
                    }else{
                        set_dc_cutoff_v = set_dc_cutoff_v + atoi(num);
                    }
                                       
                    bit = 1;
                    break;
                }
            }
            break;
        }
        case set_41:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWincdc);
            hItem = WM_GetDialogItem(hWincdc, ID_TEXT_65);
            switch(bit){
                case 1:
                {
                    set_dc_cutoff_c = atoi(num) * 100;
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
                        set_dc_cutoff_c = set_dc_cutoff_c * 10 + atoi(num) * 100;
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
                            set_dc_cutoff_c = 1500;
                        }
                    }else{
                        set_dc_cutoff_c = set_dc_cutoff_c + atoi(num) * 10;
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
                        set_dc_cutoff_c = 1500;
                    }else if(dot_flag == 2){
                        set_dc_cutoff_c = set_dc_cutoff_c + atoi(num) * 10;
                    }else{
                        set_dc_cutoff_c = set_dc_cutoff_c + atoi(num);
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
                        set_dc_cutoff_c = 1500;
                    }else if(dot_flag == 1){
                        set_dc_cutoff_c = set_dc_cutoff_c;
                    }else{
                        set_dc_cutoff_c = set_dc_cutoff_c + atoi(num);
                    }
                                       
                    bit = 1;
                    break;
                }
            }
            break;
        }
        
    }    
}

int count_num(int data)
{
    int count = 0;
    while(data != 0){
        data/=10;
        count++;
    }
    return count;
}




// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
