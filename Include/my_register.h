/******************** (C) COPYRIGHT 2014 KUNKIN********************
 * ÎÄ¼şÃû  £ºmy_register
 * ×÷Õß    £ºÀîÕñ
 * ÃèÊö    £º¿âº¯Êı°æ
 * ÄÚÈİ    £ºDefine register¶¨ÒåÏµÍ³Ê¹ÓÃµÄ¼Ä´æÆ÷£¬È«¾Ö±äÁ¿
 * ×¢Òâ		 £ºÍ·ÎÄ¼şÖĞÖ»ÄÜÓĞÉùÃ÷£¬²»ÄÜÓĞ¶¨Òå
 * ĞŞ¸ÄÈÕÆÚ£º2014-12-9
*********************************************************************/

#include "STM32F4xx.h"
#ifndef __my_register_h__
#define __my_register_h__
//=============================================================================
void Write_Limits(void);
void Wrtite_step(void);
void OC_ADD(void);
void Wrtite_S(void);
void Write_oct(void);
void Write_alarm(void);
void Write_btype(void);
void Write_info(void);
void INPUT_POW(char* num);  
void INPUT_NUM(char* num); 
void INPUT_CDC(char* num); 
void INPUT_C(char* num);  
void INPUT_LOAD(char* num);  
void INPUT_INFO(vu8 num);  
void Rlow_cal(u8 step);
void short_test(void);

//=============================================================================
#define NOP   __nop();	  //¿ÕÖ¸Áî

//============================================================================
extern struct bitDefine flagA,flagB,flagC,flagD,flagE,flagF,flagG;
#define   Flag_ADC_Full             (flagA.bit1)//DMA´«ÊäÍê³É±êÖ¾Î» 
#define   Flag_BEEP						    	(flagA.bit2)//·äÃùÆ÷´¥·¢±êÖ¾
#define   Flag_Key_Scan							(flagA.bit3)//°´¼ü¶¨Ê±É¨Ãè±êÖ¾
#define   UART_SEND_flag						(flagA.bit4)//´®¿Ú·¢ËÍÍê³É±êÖ¾
#define   UART_Buffer_Rece_flag			(flagA.bit5)//´®¿Ú½ÓÊÕÍê³É±êÖ¾
#define   Flag_Swtich_ON      			(flagA.bit6)//Æô¶¯°´¼ü´¦ÓÚON±êÖ¾
#define   Flag_0_5S      		      	(flagA.bit7)//ÏÔÊ¾ÉèÖÃµçÑ¹ÉÁË¸±êÖ¾

#define   Flag_1S      		         	(flagB.bit0)//ÏÔÊ¾ÉèÖÃµçÁ÷ÉÁË¸±êÖ¾
#define   Flag_5S      		        	(flagB.bit1)//ÍË³öÉèÖÃ×´Ì¬±êÖ¾
#define   Flag_Long                 (flagB.bit2)//°´¼ü³¤°´±êÖ¾
#define   Flag_DAC_OFF              (flagB.bit3)//æ˜¯å¦è½¬æ¢DACæ§åˆ¶å€¼æ ‡å¿—
#define   Flag_SetA                 (flagB.bit5)//½øÈëÉèÖÃµçÁ÷±êÖ¾Î»
#define   Flag_SetV                 (flagB.bit6)//½øÈëÉèÖÃµçÑ¹±êÖ¾Î» 
#define   Flag_DisSet               (flagB.bit7)//ÏÔÊ¾ÉèÖÃµçÑ¹ºÍµçÁ÷±êÖ¾Î»

#define   Flag_GE                   (flagC.bit0)//¸öÎ»ÉÁË¸±êÖ¾
#define   Flag_SHI                  (flagC.bit1)//Ê®Î»ÉÁË¸±êÖ¾
#define   Flag_BAI                  (flagC.bit2)//°ÙÎ»ÉÁË¸±êÖ¾
#define   Flag_QIAN                 (flagC.bit3)//Ç§Î»ÉÁË¸±êÖ¾
#define   Flag_Beep_OFF             (flagC.bit6)//·äÃùÆ÷¹Ø±Õ±êÖ¾

#define   flag_Tim_USART            (flagD.bit0)//´®¿Ú¼ÆËãÇåÁã±êÖ¾
#define   flag_Test                 (flagD.bit1)//×Ô¶¯²âÊÔÆğÍ£±êÖ¾
#define   flag_Test_PASS            (flagD.bit2)//×Ô¶¯²âÊÔPASS±êÖ¾
#define   flag_Test_FAIL            (flagD.bit3)//×Ô¶¯²âÊÔFAIL±êÖ¾
#define   flag_Test_Time            (flagD.bit4)//×Ô¶¯²âÊÔµÈ´ıÊ±¼ä±êÖ¾
#define   flag_Test_Start           (flagD.bit5)//×Ô¶¯²âÊÔ±È½Ï¿ªÊ¼±êÖ¾
#define   flag_Test_Min             (flagD.bit6)//×Ô¶¯²âÊÔÏÂÏŞ±êÖ¾
#define   flag_Test_MAX             (flagD.bit7)//×Ô¶¯²âÊÔÉÏÏŞ±êÖ¾

#define   flag_Test_Door             (flagE.bit0)//×Ô¶¯²âÊÔÃÅ¼÷±êÖ¾
#define   flag_Test_SetTime          (flagE.bit1)//×Ô¶¯²âÊÔÊ±¼ä±êÖ¾ 
#define   flag_OVP                   (flagE.bit2)//OVP±êÖ¾
#define   flag_OCP                   (flagE.bit3)//OCP±êÖ¾
#define   flag_Doub                  (flagE.bit4)//°´¼üË«»÷
#define   flag_t_Doub                (flagE.bit5)//°´¼üË«»÷¼ÆÊ±±êÖ¾
#define   flag_Time_SW               (flagE.bit6)//¶¨Ê±¹¦ÄÜ¿ªÆô±êÖ¾
#define   flag_CC_MODE               (flagE.bit7)//¹¤×÷Ä£Ê½±êÖ¾

#define   flag_Adjust                (flagF.bit0)//æ ¡å‡†æ¨¡å¼æ ‡å¿—ä½
#define   flag_ADJ_ON                (flagF.bit1)//
#define   flag_ADJ_VL                (flagF.bit2)//
#define   flag_ADJ_VH                (flagF.bit3)//
#define   flag_ADJ_ALCC              (flagF.bit4)//
#define   flag_ADJ_AHCC              (flagF.bit5)//
#define   flag_ADJ_ALCV              (flagF.bit6)//
#define   flag_ADJ_AHCV              (flagF.bit7)//

#define   flag_DisVL                 (flagG.bit0)//
#define   flag_OverV                 (flagG.bit1)//
#define   flag_OverACC               (flagG.bit2)//
#define   flag_OverACV               (flagG.bit3)//
#define   flag_Just_Usart            (flagG.bit4)//
#define   flag_FAN_ON                (flagG.bit5)//
#define   flag_ADJ_FAN               (flagG.bit6)//
//=============================================================================
extern vu32 GE_V;
extern vu32 SHI_V;
extern vu32 BAI_V;
extern vu32 QIAN_V;  //ÊıÂë¹ÜÉ¨Ãè¶ÎÂë
extern vu32 GE_A;
extern vu32 SHI_A;
extern vu32 BAI_A;
extern vu32 QIAN_A;
//--------------------------
extern vu8 NewKey;
extern vu8 DAC_Flag;
extern vu8 Beep_Flag;
extern vu8 t_beep;
extern vu8 t_KeyScan;
extern vu8 t_LEDScan;  //¶¨Ê±¼ÆÊıÆ÷
extern vu8 t_KEYON;
extern vu16 t_0_5S;
extern vu16 t_1S;
extern vu16 t_5S;
extern vu16 t_Basket;
extern vu16 Basket_V;
extern vu16 Basket_A;
extern vu16 t_OFF_V;
extern vu16 t_ON_V;
extern vu16 t_OFF_A;
extern vu16 t_ON_A;
extern vu8 t_USART;
extern vu16 ADJ_Write;//Ğ£×¼Ê±ĞèĞ´ÈëµÄÊµ¼ÊÖµ
extern vu8 OFFSET_Zore;//ÁãµãÖµ
extern vu8 ADDR;
extern vu8 t_lock;
extern vu8 t_onoff;
extern vu16 MAX_limit;
extern vu16 MIN_limit;
extern vu16 Test_Time;
extern vu16 Test_Time1;
extern vu16 Time_sw;
extern vu16 Test_Daley;
extern vu16 Test_C_Door;
extern vu16 TEMP_OFFSET;//ÎÂ¶È²¹³¥Öµ
//--------------------------
extern vu8 UART_Buffer_Size;//´®¿Ú½ÓÊÕÊı¾İ³¤¶È
extern vu8 Transmit_BUFFERsize;
//---------------------------
extern vu16 NTC_value;   //ADÖµ
extern vu16 Imon_value;
extern vu16 Imon1_value;
extern vu16 Vmon_value;
extern vu16 Vmon1_value;
extern vu16 Rmon_value;

extern float DISS_Voltage;
extern  float DISS_POW_Voltage;
extern float DISS_Current;
extern float DISS_POW_Current;
extern float DISS_R;
extern float bc_raw;
extern vu16 steptime;
extern vu8 r_stable;
extern vu8 bit1;
extern vu8 dot_flag;
extern vu8 page_sw;
extern vu8 para_set1;
extern vu8 para_set2;
extern vu8 para_set3;
extern vu8 para_set4;
extern vu8 oct_sw;
extern vu8 set_sw;
extern vu8 lang;
extern vu16 battery_c;
extern char set_limit[5];
extern vu8 bit;
extern vu8 track;
extern vu8 mode_sw;
extern vu8 pow_sw;
extern vu8 cdc_sw;
extern vu8 load_sw;
extern vu8 b_type;
extern vu8 buffer;
extern float gate_v;
extern vu8 cutoff_flag;
extern vu8 charge_step;
extern vu8 pause_flag;
extern vu8 paused;
extern vu8 finish;
extern vu16 restart_time;
extern vu8 set_loop_count;
extern vu8 short_flag;


extern vu16 Run_Control[43];	
#define onoff_ch                        Run_Control[0]  //ON/OFF
#define SET_Voltage 	    	        Run_Control[1]  //ç”µæºè®¾ç½®ç”µå‹
#define SET_Current	    	    		Run_Control[2]  //ç”µæºè®¾ç½®ç”µæµ
#define SET_Voltage_Laod 				Run_Control[3]  //ç”µå­è´Ÿè½½è®¾ç½®ç”µå‹
#define SET_Current_Laod				Run_Control[4]  //ç”µå­è´Ÿè½½è®¾ç½®ç”µæµ
#define LOCK_KEY						Run_Control[5]  //
#define BEEP_KEY						Run_Control[6]  //
#define STRONG_KEY						Run_Control[7]  //

#define MODE_Woke						Run_Control[8]  //
#define POW_Voltage	    	            Run_Control[9]  //
#define Voltage	    	                Run_Control[10]  //
#define Current	    	    		    Run_Control[11]  //
#define Laod_Current	    		    Run_Control[12]  //
#define R_VLUE							Run_Control[13]  //
#define set_max_v						Run_Control[14]  //è®¾ç½®æµ‹é‡ç”µå‹ä¸Šé™
#define set_min_v						Run_Control[15]  //è®¾ç½®æµ‹é‡ç”µå‹ä¸‹é™
#define set_max_r						Run_Control[16]  //è®¾ç½®æµ‹é‡å†…é˜»ä¸Šé™
#define set_min_r						Run_Control[17]  //è®¾ç½®æµ‹é‡å†…é˜»ä¸‹é™
#define set_max_c						Run_Control[18]  //è®¾ç½®æµ‹é‡ç”µæµä¸Šé™
#define set_min_c						Run_Control[19]  //è®¾ç½®æµ‹é‡ç”µæµè¥¿çº¿
#define set_output_v					Run_Control[20]  //è®¾ç½®æµ‹é‡è¾“å‡ºç”µå‹
#define set_output_c					Run_Control[21]  //è®¾ç½®æµ‹é‡è¾“å‡ºç”µæµ
#define set_init_c					    Run_Control[22]  //è®¾ç½®æµ‹é‡è¾“å‡ºç”µå‹
#define set_sbs_c					    Run_Control[23]  //è®¾ç½®æµ‹é‡è¾“å‡ºç”µæµ
#define set_add_c					    Run_Control[24]
#define set_c_cutoff_v					Run_Control[25]
#define set_c_cutoff_c					Run_Control[26]
#define set_dc_cutoff_v					Run_Control[27]
#define set_dc_cutoff_c					Run_Control[28]
#define start_time					    Run_Control[29]
#define end_time					    Run_Control[30]
#define opv1    					    Run_Control[31]
#define opv2    					    Run_Control[32]
#define opv3    					    Run_Control[33]
#define opc1    					    Run_Control[34]
#define opc2    					    Run_Control[35]
#define opc3    					    Run_Control[36]
#define load_c    					    Run_Control[37]
#define cdc_cv    					    Run_Control[38]
#define cdc_cc    					    Run_Control[39]
#define pow_v    					    Run_Control[40]
#define cdc_dc    					    Run_Control[41]
#define pow_c    					    Run_Control[42]


extern vu16 coff[6];
#define cov1    					    coff[0]
#define cov2    					    coff[1]
#define cov3    					    coff[2]
#define coc1    					    coff[3]
#define coc2    					    coff[4]
#define coc3    					    coff[5]

extern vu16 Contr_Voltage;//
extern vu16 Contr_Current;//
extern vu16 Contr_Laod;//
extern vu16 Correct_Parametet[13];
#define  REG_CorrectionV   Correct_Parametet[0]
#define  REG_CorrectionA   Correct_Parametet[1]
#define  REG_CorrectionA1  Correct_Parametet[2]
#define  REG_CorrectionR   Correct_Parametet[3]
#define  Polar             Correct_Parametet[4]
#define  SET_CorrectionV   Correct_Parametet[5]
#define  SET_CorrectionA   Correct_Parametet[6]
#define  SET_CorrectionA1  Correct_Parametet[7]
#define  CON_CorrectionA   Correct_Parametet[8]
#define  Polar1            Correct_Parametet[9]
#define  Polar2						 Correct_Parametet[10]
#define  Polar3						 Correct_Parametet[11]
#define  REG_CorrectionV1  Correct_Parametet[12]


extern vu32 Correct_Strong[9];//Ğ£×¼ÏµÊı
#define  REG_ReadV_Offset   Correct_Strong[0]
#define  REG_ReadA_Offset   Correct_Strong[1]
#define  REG_ReadA1_Offset  Correct_Strong[2]
#define  REG_ReadR_Offset   Correct_Strong[3]
#define  SET_ReadV_Offset   Correct_Strong[4]
#define  SET_ReadA_Offset   Correct_Strong[5]
#define  SET_ReadA1_Offset  Correct_Strong[6]
#define  CON_ReadA_Offset   Correct_Strong[7]
#define  REG_ReadV1_Offset  Correct_Strong[8]

/*
************************************************************************
*						é¡µé¢è¯†åˆ«ç¬¦
************************************************************************
*/

#define face_graph      0
#define face_cdc        1
#define face_menu       2
#define face_r          3
#define face_load       4
#define face_set        5
#define face_starter    6
#define face_sys_info   7
/*
************************************************************************
*						è®¾ç½®é€‰é¡¹è¯†åˆ«ç¬¦
************************************************************************
*/

#define set_1           0
#define set_2           1
#define set_3           2
#define set_4           3
#define set_5           4
#define set_6           5
#define set_7           6
#define set_8           7
#define set_9           8
#define set_10          9
#define set_11          10
#define set_12          11
#define set_13          12
#define set_14          13
#define set_15          14
#define set_16          15
#define set_17          16
#define set_18          17
#define set_19          18
#define set_20          19
#define set_21          20
#define set_22          21
#define set_23          22
#define set_24          23
#define set_25          24
#define set_26          25
#define set_27          26
#define set_28          27
#define set_29          28
#define set_30          29
#define set_31          30
#define set_32          31
#define set_33          32
#define set_34          33
#define set_35          34
#define set_36          35
#define set_37          36
#define set_38          37
#define set_39          38
#define set_40          39
#define set_41          40
#define set_42          41
#define set_43          42
#define set_44          43
#define set_45          44
#define set_46          45
#define set_47          46
#define set_48          47
#define set_49          48
#define set_50          49
#define set_51          50
#define set_52          51
#define set_53          52
#define set_54          53
#define set_55          54
#define set_56          55
#define set_57          56
#define set_58          57
#define set_59          58
#define set_60          59
#define set_61          60
#define set_62          61
#define set_63          62
#define set_64          63
#define set_65          64
#define set_66          65
#define set_67          66
#define set_68          67
/*
************************************************************************
*						å‚æ•°è®¾ç½®è¯†åˆ«ç¬¦
************************************************************************
*/

#define set_1_on            0xff
#define set_1_off           0
#define set_2_on            0xff
#define set_2_off           0
#define set_3_on            1
#define set_3_off           0
#define set_4_on            0xff
#define set_4_off           0
#define cdc_on              1
#define cdc_off             0
#define oct_on              1
#define oct_off             0
#define c_on                1
#define c_off               0
#define mode_r              1
#define mode_load           2
#define mode_pow            3
#define load_on             1
#define load_off            0
#define pow_on              1
#define pow_off             0
#define Lion                1
#define NiMH                2
#define NiCd                3
#define SLA                 4
#define LiMH                5
#define step1               0
#define step2               1
#define step3               2

//---------------------------
extern vu16 ADC1_Buffer[300];//ADC×ª»»»º³åÊı×é
extern vu16 ADC_NTC_Filt[50];
extern vu16 ADC_Vmon_Filt[50];
extern vu16 ADC_Imon_Filt[50];
extern vu8 UART_Buffer_Rece[16];
extern vu8 UART_Buffer_Send[20];
//============================================================================= 
#define Receive_BUFFERSIZE   10
//=============================================================================
#endif
/******************* (C) COPYRIGHT 2015 KUNKIN *****END OF FILE*************************/
































