#include "MainTask.h"
#include  "gui.h"
#include "DIALOG.h"
#include "my_register.h"


WM_HWIN hWinsysinfo;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHZ16;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHZ12;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHZ20S;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontEN40;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHZ32;
extern GUI_CONST_STORAGE GUI_FONT GUI_Fontsymbol;
extern GUI_CONST_STORAGE GUI_FONT GUI_Fontset_font;
extern GUI_CONST_STORAGE GUI_BITMAP bmOPSCRENN;


/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_9     (GUI_ID_USER + 0x0107)
#define ID_BUTTON_36    (GUI_ID_USER + 0x0108)
#define ID_BUTTON_37    (GUI_ID_USER + 0x0109)
#define ID_BUTTON_38    (GUI_ID_USER + 0x9B)
#define ID_BUTTON_39   	(GUI_ID_USER + 0x9C)
#define ID_BUTTON_40   	(GUI_ID_USER + 0x9D)


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
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_36, 83, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_37, 163, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_38, 243, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_39, 323, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_40, 403, 226, 77, 45, 0, 0x0, 0 },
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
        GUI_SetColor(0x00BFFFFF);
        GUI_SetFont(&GUI_Font24_1);
        GUI_DispStringAt("JK5530", 140, 50);
        GUI_DispStringAt("Ver:1.3", 140, 75);
        GUI_DispStringAt("Ver:0.0", 140, 100);
        GUI_DispStringAt("0000-00-00", 140, 125);
        GUI_DispStringAt("18A000000", 140, 150);
	break;
	case WM_TIMER:
	if(WM_GetTimerId(pMsg->Data.v) == ID_TimerTime7)
	{
		WM_RestartTimer(pMsg->Data.v,500);//شλ֨ʱǷ˽ֵԽճˢтʱݤԽ׌
	}
	break;
    
		
  case WM_INIT_DIALOG:
      hItem = pMsg->hWin;
      WINDOW_SetBkColor(hItem, GUI_BLACK);
      WM_CreateTimer(hItem,ID_TimerTime7,20,0);
  
      hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_36);
	  BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
      BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//ʨ֨дťτѾؖͥ
	  GUI_UC_SetEncodeUTF8();
	  BUTTON_SetText(hItem,"内阻测试");
	
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_37);
	  BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
	  BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//ʨ֨дťτѾؖͥ
	  GUI_UC_SetEncodeUTF8();
	  BUTTON_SetText(hItem,"程控负载");
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_38);
	  BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
	  BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//ʨ֨дťτѾؖͥ
	  GUI_UC_SetEncodeUTF8();
	  BUTTON_SetText(hItem,"程控电源");
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_39);
	  BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
	  BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//ʨ֨дťτѾؖͥ
	  GUI_UC_SetEncodeUTF8();
	  BUTTON_SetText(hItem,"充放电");
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_40);
	  BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
	  BUTTON_SetFont      (hItem,&GUI_FontHZ16);//ʨ֨дťτѾؖͥ
	  GUI_UC_SetEncodeUTF8();
	  BUTTON_SetText(hItem,"曲线");

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
  return hWinsysinfo;
}
