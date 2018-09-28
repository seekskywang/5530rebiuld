/******************************************************************/
/* ���ƣ�                                                  				*/
/* Ч����                                                        */
/* ���ݣ�����ͼ����                                             */
/* ���ߣ�                                                 */
/* ��ϵ��ʽQQ:                                        */


#include "MainTask.h"
#include  "gui.h"
#include "DIALOG.h"
#include "my_register.h" 
#include "tm1650.h"

WM_HWIN hWinG;
void DrawGraph(void);
extern vu8 pass;
extern vu8 track;
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_3     (GUI_ID_USER + 0x22)
#define ID_BUTTON_18    (GUI_ID_USER + 0x23)
#define ID_BUTTON_19    (GUI_ID_USER + 0x24)
#define ID_BUTTON_20    (GUI_ID_USER + 0x25)
#define ID_BUTTON_21   	(GUI_ID_USER + 0x26)
#define ID_BUTTON_22   	(GUI_ID_USER + 0x27)
#define ID_BUTTON_23    (GUI_ID_USER + 0x28)
#define ID_GRAPH_0      (GUI_ID_USER + 0x29)

#define ID_TimerTime3    4
// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static GRAPH_SCALE_Handle hScaleV; //--------------（1）
static GRAPH_SCALE_Handle hScaleH;
static GRAPH_DATA_Handle VData;
static GRAPH_DATA_Handle IData;
//static GRAPH_DATA_Handle  ahData;
// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate3[] = {
  { WINDOW_CreateIndirect, "G", ID_WINDOW_3, 0, 0, 480, 272, 0, 0x0, 0 },
//  { TEXT_CreateIndirect, "Text", ID_TEXT_0, 28, 74, 64, 32, 0, 0x64, 0 },
//  { TEXT_CreateIndirect, "Text", ID_TEXT_1, 28, 144, 64, 32, 0, 0x64, 0 },
//  { TEXT_CreateIndirect, "Text", ID_TEXT_3, 217, 74, 32, 30, 0, 0x0, 0 },
//  { TEXT_CreateIndirect, "Text", ID_TEXT_4, 239, 145, 32, 32, 0, 0x0, 0 },
//  { TEXT_CreateIndirect, "Text", ID_TEXT_6, 217, 152, 32, 20, 0, 0x0, 0 },
  
//   { BUTTON_CreateIndirect, "Button", ID_BUTTON_18, 3, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_19, 83, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_20, 163, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_21, 243, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_22, 323, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_23, 403, 226, 77, 45, 0, 0x0, 0 },
  { GRAPH_CreateIndirect,  "Graph",  ID_GRAPH_0,   100, 31, 350, 193, 0, 0x0, 0 }
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
	GUI_SetColor(GUI_WHITE);//���û�����ɫ
	GUI_FillRect(0,25,480,26);//��һ��ʵ��
    GUI_SetColor(GUI_GREEN);
    GUI_FillRect(50,75,75,76);
    GUI_SetColor(GUI_RED);
    GUI_FillRect(50,120,75,121);
    GUI_SetColor(GUI_ORANGE);
	GUI_SetFont(&GUI_Fontsymbol);
	GUI_UC_SetEncodeUTF8();
	GUI_SetTextMode(GUI_TM_TRANS);//�����ı�ģʽΪ��ɫ͸��
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
    GUI_DispStringAt("V(V)", 5,65);
    GUI_DispStringAt("I(A)", 5,110);
    
    
	break;
	case WM_TIMER://��ʱģ����Ϣ
	if(WM_GetTimerId(pMsg->Data.v) == ID_TimerTime3)
	{
        
        DrawGraph();
		WM_RestartTimer(pMsg->Data.v, 200);//��λ��ʱ����ֵԽ��ˢ��ʱ��Խ��
	}
	break;
    
		
    case WM_INIT_DIALOG:
    //
    // Initialization of 'R'
	
    //
        hItem = pMsg->hWin;
        WINDOW_SetBkColor(hItem, GUI_BLACK);
		WM_CreateTimer(hItem,ID_TimerTime3,1000,0);//���������ڶ�ʱ��
    //

    //    
// 		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_18);
// 		BUTTON_SetTextColor(hItem,0,GUI_BLACK);//����������ɫΪ��ɫ
// 		BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//�趨��ť�ı�����
// 		GUI_UC_SetEncodeUTF8();
// 		BUTTON_SetText(hItem,"充放电");
	
        if(lang == 0)
        {
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_19);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//����������ɫΪ��ɫ
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//�趨��ť�ı�����
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"内阻测试");
        
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_20);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//����������ɫΪ��ɫ
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//�趨��ť�ı�����
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"程控负载");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_21);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//����������ɫΪ��ɫ
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//�趨��ť�ı�����
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"程控电源");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_22);        
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//����������ɫΪ��ɫ
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//�趨��ť�ı�����
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"充放电");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_23);
            BUTTON_SetPressed(hItem,1);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//����������ɫΪ��ɫ
            BUTTON_SetFont      (hItem,&GUI_FontHZ16);//�趨��ť�ı�����
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"曲线");
        }else{
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_19);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//ʨ֨дťτѾؖͥ
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"I.R. TEST");
        
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_20);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//ʨ֨дťτѾؖͥ
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"LOAD");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_21);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//ʨ֨дťτѾؖͥ
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"POWER");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_22);        
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//ʨ֨дťτѾؖͥ
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"C&DC");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_23);
            BUTTON_SetPressed(hItem,1);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
            BUTTON_SetFont      (hItem,&GUI_Font16B_ASCII);//ʨ֨дťτѾؖͥ
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"GRAPH");
        }
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
        GRAPH_SetBorder(hItem, 20, 5, 20, 15);
//        GRAPH_SetVSizeY(hItem,200);
        hScaleV =GRAPH_SCALE_Create(18, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 20);
        GRAPH_AttachScale(hItem,hScaleV);
        hScaleH =GRAPH_SCALE_Create(185, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 50);
        GRAPH_AttachScale(hItem,hScaleH);
        GRAPH_SCALE_SetFactor(hScaleV,0.1);
        VData = GRAPH_DATA_YT_Create(GUI_GREEN, 500, 0, 0);//
        IData = GRAPH_DATA_YT_Create(GUI_RED, 500, 0, 0);//
        GRAPH_AttachData(hItem,VData);
        GRAPH_AttachData(hItem,IData);
        GRAPH_SetGridDistY(hItem, 20);
        GRAPH_SetGridFixedX(hItem,25);
        GRAPH_SetGridVis(hItem, 1);
        
        		
        
		
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
WM_HWIN CreateG(void);
WM_HWIN CreateG(void) {
  page_sw = face_graph;
//  double_sw = face_graph;
  track = face_graph;
  pass = 0;
  TM1650_SET_LED(0x68,0x70);
  GPIO_ResetBits(GPIOD,GPIO_Pin_12);//���
  hWinG = GUI_CreateDialogBox(_aDialogCreate3, GUI_COUNTOF(_aDialogCreate3), _cbDialog, WM_HBKWIN, 0, 0);
  return hWinG;
}

/*********************************************************************
*
*       DrawGraph
*/

void DrawGraph(void){
    if(mode_sw == mode_load)
    {
        GRAPH_DATA_YT_AddValue(VData,DISS_Voltage*10);
        GRAPH_DATA_YT_AddValue(IData,DISS_Current*10);
    }else if(mode_sw == mode_pow){
        GRAPH_DATA_YT_AddValue(VData,DISS_POW_Voltage*10);
        GRAPH_DATA_YT_AddValue(IData,DISS_POW_Current*10);
    }
    
//    GUI_Delay(50);
}
// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
