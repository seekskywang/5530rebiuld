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
#include "tm1650.h"
#include "stdio.h"
#include "stdlib.h"
#include "key.h"
#include "string.h"
#include "beep.h"

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
} flagA,flagB,flagC,flagD,flagE,flagG;


WM_HWIN hWinsysinfo;
extern GUI_CONST_STORAGE GUI_BITMAP bmOPSCRENN;
vu8 info_set = set_48;
vu16 year1 = 0;
vu16 year2 = 0;
vu16 year3 = 0;
vu16 year4 = 0;
vu8 month1 = 0;
vu8 month2 = 0;
vu8 day1 = 0;
vu8 day2 = 0;
vu8 admin = 0;
vu8 code1 = 0;
vu8 code2 = 0;
vu8 code3 = 0;
vu8 code4 = 0;
vu8 code5 = 0;
vu8 code6 = 0;
vu8 code7 = 0;
vu8 code8 = 0;
vu8 cal = 0;
extern vu8 pass;
extern vu16 Modify_A_READ;
extern vu16 Modify_C_READ;
extern vu16 Modify_A_ACT;
	
extern vu16 Modify_B_READ;
extern vu16 Modify_D_READ;
extern vu16 Modify_B_ACT;

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_8     (GUI_ID_USER + 0x98)
#define ID_TEXT_99      (GUI_ID_USER + 0x99)
#define ID_TEXT_100     (GUI_ID_USER + 0x9A)
#define ID_TEXT_101     (GUI_ID_USER + 0x9B)
#define ID_TEXT_102    	(GUI_ID_USER + 0x9C)
#define ID_TEXT_103    	(GUI_ID_USER + 0x9D)
#define ID_TEXT_104    	(GUI_ID_USER + 0x9E)
#define ID_TEXT_105    	(GUI_ID_USER + 0x300)
#define ID_TEXT_106   	(GUI_ID_USER + 0x301)
#define ID_TEXT_107    	(GUI_ID_USER + 0x302)
#define ID_TEXT_108    	(GUI_ID_USER + 0x303)
#define ID_TEXT_109    	(GUI_ID_USER + 0x304)
#define ID_TEXT_110    	(GUI_ID_USER + 0x305)
#define ID_TEXT_111    	(GUI_ID_USER + 0x306)
#define ID_TEXT_112    	(GUI_ID_USER + 0x307)
#define ID_TEXT_113    	(GUI_ID_USER + 0x308)
#define ID_TEXT_114    	(GUI_ID_USER + 0x309)
#define ID_TEXT_123    	(GUI_ID_USER + 0x312)

#define ID_TimerTime7    8
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
static const GUI_WIDGET_CREATE_INFO _aDialogCreate7[] = {
  { WINDOW_CreateIndirect, "SYSINFO", ID_WINDOW_8, 0, 0, 480, 272, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_99, 180, 125, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_100, 192, 125, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_101, 204, 125, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_102, 216, 125, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_103, 240, 125, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_104, 252, 125, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_105, 276, 125, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_106, 288, 125, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_107, 216, 150, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_108, 228, 150, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_109, 240, 150, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_110, 252, 150, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_111, 264, 150, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_112, 276, 150, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_113, 180, 150, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_114, 192, 150, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_123, 192, 200, 80, 20, 0, 0x0, 0 },
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
    static char buf[5];


    
  
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
            GUI_SetTextMode(GUI_TM_TRANS);//ʨ׃τѾģʽΪ֗ɫ͸ķ
            GUI_DispStringAt("系统信息", 130, 3);//SET
            GUI_SetColor(GUI_LIGHTBLUE);
            GUI_SetFont(&GUI_Fontset_font);
            GUI_DispStringAt("仪器型号", 30, 50);
            GUI_DispStringAt("软件版本", 30, 75);
            GUI_DispStringAt("硬件版本", 30, 100);
            GUI_DispStringAt("生产日期", 30, 125);
            GUI_DispStringAt("仪器编号", 30, 150);
        }else{
            GUI_SetColor(GUI_WHITE);
            GUI_SetFont(&GUI_Font20_ASCII);
            GUI_UC_SetEncodeUTF8();
            GUI_SetTextMode(GUI_TM_TRANS);//ʨ׃τѾģʽΪ֗ɫ͸ķ
            GUI_DispStringAt("System Information", 130, 3);//SET
            GUI_SetColor(GUI_LIGHTBLUE);
            GUI_SetFont(&GUI_Font20_ASCII);
            GUI_DispStringAt("Instrument Model", 30, 50);
            GUI_DispStringAt("Software Version", 30, 75);
            GUI_DispStringAt("Hardware Version", 30, 100);
            GUI_DispStringAt("Production Date", 30, 125);
            GUI_DispStringAt("Serial NO.", 30, 150);
        }
        GUI_SetColor(0x00BFFFFF);
        GUI_SetFont(&GUI_Font24_1);
        GUI_DispStringAt("JK5530", 180, 50);
        GUI_DispStringAt("Ver:2.6", 180, 75);
        //1.7版本修改内阻测试判断测试结束与下一次测试开始的逻辑
        //1.8版本修正内阻测试短路后激活电池问题，添加手动测试功能，修正内阻显示不稳定问题
        //2.0版本添加英文
        //2.1版本添加步进时间设置
        //2.6添加上位机通信协议
        GUI_DispStringAt("Ver:1.0", 180, 100);
        GUI_DispStringAt("-", 231, 125);
        GUI_DispStringAt("-", 267, 125);
        GUI_DispStringAt("A", 204, 150);
	break;
	case WM_TIMER:
	if(WM_GetTimerId(pMsg->Data.v) == ID_TimerTime7)
	{
        if(pass == 14)
        {
            admin = 1;
        }else if(pass == 10){
            cal = 1;
        }else{
            admin = 0;
            cal = 0;
        }
        
        if(cal ==  1)
        {
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_123);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            sprintf(buf,"%4d",R_VLUE);
            TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
            GUI_UC_SetEncodeUTF8();        
            TEXT_SetText(hItem,buf);
        }else{
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_123);
            TEXT_SetText(hItem, "");
            TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
        }
		WM_RestartTimer(pMsg->Data.v,500);//شλ֨ʱǷ˽ֵԽճˢтʱݤԽ׌                
	}
	break;
    
		
  case WM_INIT_DIALOG:
      hItem = pMsg->hWin;
      WINDOW_SetBkColor(hItem, GUI_BLACK);
      WM_CreateTimer(hItem,ID_TimerTime7,20,0);
  
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_99);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",year1);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
	
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_100);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",year2);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_101);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",year3);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_102);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",year4);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
      
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_103);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",month1);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
	
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_104);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",month2);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_105);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",day1);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_106);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",day2);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
	
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_107);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",code3);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_108);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",code4);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
      
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_109);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",code5);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_110);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",code6);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
      
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_111);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",code7);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_112);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",code8);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
      
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_113);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",code1);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_114);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",code2);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
      


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
WM_HWIN Createsysinfo(void);
WM_HWIN Createsysinfo(void) {
  hWinsysinfo  = GUI_CreateDialogBox(_aDialogCreate7, GUI_COUNTOF(_aDialogCreate7), _cbDialog, WM_HBKWIN, 0, 0);
  pass = 0;
  page_sw = face_sys_info;
  load_sw = load_off;
  pow_sw == pow_off;
  GPIO_ResetBits(GPIOB,GPIO_Pin_13);
  info_set = set_48;
  return hWinsysinfo;
}


void SYS_INFO_RIGHT(void);
void SYS_INFO_RIGHT(void)
{
    WM_HWIN hItem;
    switch(info_set)
    {
        case set_48:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_100);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_49;
            break;
        }
        case set_49:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_100);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_101);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_50;
            break;
        }
        case set_50:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_101);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_102);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_51;
            break;
        }
        case set_51:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_102);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_103);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_52;
            break;
        }
        case set_52:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_103);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_104);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_53;
            break;
        }
        case set_53:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_104);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_105);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_54;
            break;
        }
        case set_54:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_105);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_106);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_55;
            break;
        }
        case set_55:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_106);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_62:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_114);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_63;
            break;
        }
        case set_63:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_114);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_107);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_56;
            break;
        }
        case set_56:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_107);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_108);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_57;
            break;
        }
        case set_57:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_108);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_109);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_58;
            break;
        }
        case set_58:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_109);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_110);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_59;
            break;
        }
        case set_59:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_110);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_111);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_60;
            break;
        }
        case set_60:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_111);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_112);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_61;
            break;
        }
        case set_61:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_112);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
    }
    
}


void SYS_INFO_LEFT(void);
void SYS_INFO_LEFT(void)
{
    WM_HWIN hItem;
    switch(info_set)
    {
        case set_48:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_106);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_55;
            break;
        }
        case set_49:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_100);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_50:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_101);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_100);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_49;
            break;
        }
        case set_51:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_102);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_101);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_50;
            break;
        }
        case set_52:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_103);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_102);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_51;
            break;
        }
        case set_53:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_104);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_103);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_52;
            break;
        }
        case set_54:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_105);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_104);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_53;
            break;
        }
        case set_55:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_106);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_105);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_54;
            break;
        }
        case set_62:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_112);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_61;
            break;
        }
        case set_63:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_114);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_56:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_107);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_114);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_63;
            break;
        }
        case set_57:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_108);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_107);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_56;
            break;
        }
        case set_58:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_109);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_108);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_57;
            break;
        }
        case set_59:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_110);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_109);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_58;
            break;
        }
        case set_60:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_111);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_110);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_59;
            break;
        }
        case set_61:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_112);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_111);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_60;
            break;
        }
    }
    
}


void SYS_INFO_UP(void);
void SYS_INFO_UP(void)
{
    WM_HWIN hItem;
    switch(info_set)
    {
        case set_48:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_49:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_100);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_50:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_101);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_51:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_102);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_52:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_103);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_53:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_104);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_54:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_105);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_55:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_106);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_56:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_107);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_62:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_63:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_114);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_57:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_108);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_58:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_109);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_59:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_110);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_60:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_111);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_61:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_112);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
    }
    
}


void SYS_INFO_DOWN(void);
void SYS_INFO_DOWN(void)
{
    WM_HWIN hItem;
    switch(info_set)
    {
        case set_48:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_49:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_100);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_50:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_101);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_51:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_102);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_52:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_103);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_53:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_104);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_54:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_105);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_55:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_106);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_62:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_63:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_114);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_56:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_107);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_57:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_108);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_58:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_109);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_59:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_110);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_60:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_111);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_61:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_112);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
    }
    
}


          
void INPUT_INFO(vu8 num){
    static char buf[5];
    WM_HWIN hItem;
    switch(info_set)
    {
        case set_48:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            year1 = num;
            Write_info();
            break;
        }
        case set_49:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_100);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            year2= num;
            Write_info();
            break;
        }
        case set_50:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_101);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            year3= num;
            Write_info();
            break;
        }
        case set_51:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_102);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            year4= num;
            Write_info();
            break;
        }
        case set_52:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_103);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            month1 = num;
            Write_info();
            break;
        }
        case set_53:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_104);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            month2 = num;
            Write_info();
            break;
        }
        case set_54:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_105);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            day1 = num;
            Write_info();
            break;
        }
        case set_55:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_106);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            day2 = num;
            Write_info();
            break;
        }
        case set_56:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_107);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            code3 = num;
            Write_info();
            break;
        }
        case set_57:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_108);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            code4 = num;
            Write_info();
            break;
        }
        case set_58:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_109);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            code5 = num;
            Write_info();
            break;
        }
        case set_59:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_110);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            code6 = num;
            Write_info();
            break;
        }
        case set_60:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_111);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            code7 = num;
            Write_info();
            break;
        }
        case set_61:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_112);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            code8 = num;
            Write_info();
            break;
        }
        case set_62:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            code1 = num;
            Write_info();
            break;
        }
        case set_63:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_114);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            code2 = num;
            Write_info();
            break;
        }
        
    }
}

WM_HWIN CFM_PASS(void);            
WM_HWIN CFM_PASS(void){
    if(admin == 1)
    {
        WM_HWIN hItem;
        hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
        TEXT_SetBkColor(hItem,0x00BFFFFF);
        TEXT_SetTextColor(hItem, GUI_BLACK);
    }else{
        WM_HWIN hItem;
        hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
        TEXT_SetTextColor(hItem, 0x00BFFFFF);
        info_set = set_48;
    }
}

void Rlow_cal(u8 step)
{
    if(step == 1)
    {
        Modify_A_READ = Rmon_value;//测量电压值
		Modify_A_ACT = 0x0A;//读取低段
    }else if(step == 2){
        vu16 var16;
        vu32 var32a;
        vu32 var32b;
        
        vu16 var16a;
        vu32 var32c;
        vu32 var32d;
        Modify_B_READ =Rmon_value;//测量电压值
        flag_OverV=1;
        Modify_B_ACT = 0x64;//读取高段
        if(flag_OverV==1)//只有当有数据写入时才能将校准数据写入FLASH
        {
            var32a = Modify_B_ACT;
            var32a = var32a - Modify_A_ACT;
            var32a = var32a << 12;
            var16 = Modify_B_READ - Modify_A_READ;
            var32a = var32a / var16;
            REG_CorrectionR = var32a;
            var32a=0;
            var32a = Modify_B_ACT;
            var32a = var32a << 12;
            var32b = Modify_B_READ;
            var32b = var32b * REG_CorrectionR;
            if (var32a < var32b)
            {
                var32b = var32b - var32a;
                REG_ReadR_Offset = var32b;
                Polar3 |= 0x01;
            }
            else 
            {
                var32a = var32a - var32b;
                REG_ReadR_Offset = var32a;
                Polar3 &= ~0x01;
            }
//---------------------------------------------------------------------------------------//
            Flash_Write_all();	//参数写进FLASH
            flag_OverV=0;
            Flag_DAC_OFF=0;
        }
        flag_ADJ_VH=0;//清掉标志位防止一直进入
    }
}

void Rhigh_cal(u8 step)
{
    if(step == 3)
    {
        Modify_A_READ = Rmon_value;//测量电压值
		Modify_A_ACT = 0x64;//读取低段
    }else if(step == 4){
        vu16 var16;
        vu32 var32a;
        vu32 var32b;
        
        vu16 var16a;
        vu32 var32c;
        vu32 var32d;
        Modify_B_READ =Rmon_value;//测量电压值
        flag_OverV=1;
        Modify_B_ACT = 0xC8;//读取高段
        if(flag_OverV==1)//只有当有数据写入时才能将校准数据写入FLASH
        {
            var32a = Modify_B_ACT;
            var32a = var32a - Modify_A_ACT;
            var32a = var32a << 12;
            var16 = Modify_B_READ - Modify_A_READ;
            var32a = var32a / var16;
            REG_CorrectionRH = var32a;
            var32a=0;
            var32a = Modify_B_ACT;
            var32a = var32a << 12;
            var32b = Modify_B_READ;
            var32b = var32b * REG_CorrectionRH;
            if (var32a < var32b)
            {
                var32b = var32b - var32a;
                REG_ReadRH_Offset = var32b;
                Polar3 |= 0x01;
            }
            else 
            {
                var32a = var32a - var32b;
                REG_ReadRH_Offset = var32a;
                Polar3 &= ~0x01;
            }
//---------------------------------------------------------------------------------------//
            Flash_Write_all();	//参数写进FLASH
            flag_OverV=0;
            Flag_DAC_OFF=0;
        }
        flag_ADJ_VH=0;//清掉标志位防止一直进入
    }
}
