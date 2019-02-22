/******************** (C) COPYRIGHT 2014 KUNKIN********************
 * 文件名  :MODBUS.C
 * 作者   :
 * 描述    :MODBUS?????
 * 内容    :KL220A_Master
 * 硬件连接: 485
 * 修改日期:2014-12-22
********************************************************************/
#include "my_register.h" 
#include "usart.h" 
#include "modbus.h" 
#include "flash.h"
#include "stm32f4xx_gpio.h"
//===================================================================//
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
/*************************校准参数************************************/
vu16 ADJ_Write;//校准时需写入的实际值
vu8 DAC_Flag;//DAC是否加载标志
vu16 Modify_A_READ;
vu16 Modify_C_READ;
vu16 Modify_A_ACT;
	
vu16 Modify_B_READ;
vu16 Modify_D_READ;
vu16 Modify_B_ACT;
vu16 Correct_Parametet[14];//校准参数
vu32 Correct_Strong[10];//校准系数
/*************************变量定义***********************************/
vu16 Run_Control[43];
vu8 ADDR;
extern struct MODS_T g_tModS;
//============================函数声明===============================//
vu16 Hardware_CRC(vu8 *p_buffer,vu8 count);
//===========================MODBUS协议=============================//
void UART_Action(void)
{//RUT格式：
	//ADDR  命令码  读寄存器的起始地址高   读寄存器的起始地址低  读数据字个数高字节   读数据个数低字节  CRC高 CRC低
	//返回格式：ADDR 命令码 返回数据字节数  数据高  数据低 ..... CRC高  CRC低
	if (g_tModS.RxBuf[0] == ADDR)
	{
		if (g_tModS.RxBuf[1] == (0x03))	//命令3 读数据   
		{																		 
			vu8 i;
			vu16 crc_result;
			crc_result = (g_tModS.RxBuf[6] << 8) + g_tModS.RxBuf[7];
			if ((crc_result == Hardware_CRC(g_tModS.RxBuf,6)) ||(crc_result == 0) )
			{
				if (g_tModS.RxBuf[3] < 0x07)    								//如果寄存器在可读范围内
				{
					if ((g_tModS.RxBuf[3] + g_tModS.RxBuf[5]) < 0x0F)		//如果最后一个读取的寄存器地址在可读范围内
					{							
						UART_Buffer_Send[0] = ADDR;
						UART_Buffer_Send[1] = 0x03;
						UART_Buffer_Send[2] = g_tModS.RxBuf[5]*2;
						for (i=0;i<UART_Buffer_Send[2];i++)
						{
							if ((i % 2) == 0) UART_Buffer_Send[3 + i] = Run_Control[g_tModS.RxBuf[3] + i / 2] >> 8;
							else UART_Buffer_Send[3 + i] = Run_Control[g_tModS.RxBuf[3] + i / 2];														
						}
						crc_result = Hardware_CRC(UART_Buffer_Send,UART_Buffer_Send[2] + 3);
						UART_Buffer_Send[3 + UART_Buffer_Send[2]] = crc_result >> 8;
						UART_Buffer_Send[4 + UART_Buffer_Send[2]] = crc_result;
						Transmit_BUFFERsize = UART_Buffer_Send[2] + 5;
						UART_SEND_flag=1;
					}
				}
			}	
		}
	} 
//===============================写寄存器=================================
	if ((g_tModS.RxBuf[0] == 0) || (g_tModS.RxBuf[0] == ADDR) || (g_tModS.RxBuf[0] == ((ADDR-1)/4+100)))	 
	{
		vu8 var8;
		vu8 a=0;
		vu16 var16;
		vu16 crc_result;
//=========================以下命令6 写单个寄存器===========================
		if (g_tModS.RxBuf[1] == 6)                                 //判断第二个字节是否为命令6
		{
			if (g_tModS.RxBuf[3] < 0x05)							  //判断需要写的地址是否在可写范围内
			{
				crc_result = (g_tModS.RxBuf[6] << 8) + g_tModS.RxBuf[7];
				if ((crc_result == Hardware_CRC(g_tModS.RxBuf,6)) ||(crc_result == 0) )		  //检查CRC
				{
					var16 = (g_tModS.RxBuf[4] << 8) + g_tModS.RxBuf[5];	//第5 6个字节为要写入的数据
					var8 = g_tModS.RxBuf[3];	        						//第3 4个字节为要写入的地址
					Run_Control[var8] = var16;			    //将数据写入指定的地址

					if (g_tModS.RxBuf[0] == ADDR)							//广播模式下不返回数据
					{
						for (a=0;a<8;a++)
						{UART_Buffer_Send[a] = g_tModS.RxBuf[a];}
						Transmit_BUFFERsize = 8;						//原样数据返回，不计算CRC
						UART_SEND_flag=1;
					}
				}
			}
		}
//=======================================以下是命令16，连写寄存器===========================================
//功能码16格式:
//     地址 命令 写入起始地址高  写入起始地址低 写入字数高  写入字数低 写入字节数  数据高 数据低 ......CRC高 CRC低
//返回数据格式:
//     地址 命令 写入起始地址高  写入起始地址低  写入字节数高 写入字节数低  CRC高  CRC低 
		if (g_tModS.RxBuf[1] == 16)										  
		{	
			if ((g_tModS.RxBuf[6] == 6) && (g_tModS.RxBuf[3] == 0x00))	//规定连写寄存器的个数
			{
				crc_result = (g_tModS.RxBuf[13] << 8) + g_tModS.RxBuf[14];
				if ((crc_result == Hardware_CRC(g_tModS.RxBuf,13)) ||(crc_result == 0) )	   //检查CRC
				{												
					for (var8=0;var8<3;var8++) Run_Control[var8] = (g_tModS.RxBuf[var8*2+7] << 8) + g_tModS.RxBuf[var8*2+8];

					if (g_tModS.RxBuf[0] == ADDR)					  //广播模式不返回数据
					{
						UART_Buffer_Send[0] = ADDR;
						UART_Buffer_Send[1] = 16;
						UART_Buffer_Send[2] = g_tModS.RxBuf[2];
						UART_Buffer_Send[3] = g_tModS.RxBuf[3];
						UART_Buffer_Send[4] = g_tModS.RxBuf[4];
						UART_Buffer_Send[5] = g_tModS.RxBuf[5];
						crc_result = Hardware_CRC(UART_Buffer_Send,6);	 //计算CRC码
						UART_Buffer_Send[6] = crc_result>>8;
						UART_Buffer_Send[7] = crc_result;				 
						Transmit_BUFFERsize = 8;					     //设置发送字节数长度
						UART_SEND_flag=1;
					}
				}
			}			 
		}
	}
//===================================================================================
    if (((g_tModS.RxBuf[0] == 0x01)&&(g_tModS.RxBuf[2] == 0xA5))||(flag_ADJ_ON==1))			   //电压校准
	{
		if(g_tModS.RxBuf[1] == 0x01)
			{
				flag_ADJ_VL=0;
				Modify_A_READ = Vmon_value;//测量电压值
				Modify_A_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];//读取低段
			}
			if (g_tModS.RxBuf[1] == 0x02)			   //电压测量校准完成
			{
				vu32 var16;
				vu32 var32a;
				vu32 var32b;
				
				vu32 var16a;
				vu32 var32c;
				vu32 var32d;
				Modify_B_READ =Vmon_value;//测量电压值
				Modify_B_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];//读取高段
				var32a = Modify_B_ACT;
				var32a = var32a - Modify_A_ACT;
				var32a = var32a << 12;
				var16 = Modify_B_READ - Modify_A_READ;
				var32a = var32a / var16;
				REG_CorrectionV = var32a;
				var32a=0;
				var32a = Modify_B_ACT;
				var32a = var32a << 12;
				var32b = Modify_B_READ;
				var32b = var32b * REG_CorrectionV;
				if (var32a < var32b)
				{
					var32b = var32b - var32a;
					REG_ReadV_Offset = var32b;
					Polar |= 0x01;
				}
				else 
				{
					var32a = var32a - var32b;
					REG_ReadV_Offset = var32a;
					Polar &= ~0x01;
				}			
				Flash_Write_all();	//参数写进FLASH
				Flag_DAC_OFF=0;
			}
/************************************???·????У?*****************************************************************/
		if (g_tModS.RxBuf[1] == 0x03)			   //CC??У?
		{
			Modify_A_READ = Imon1_value;//
			Modify_C_READ = Contr_Laod;//
			Modify_A_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];
			Flag_DAC_OFF=1;//
		}

		if (g_tModS.RxBuf[1] == 0x04)			   //
		{
			vu32 var16;
			vu32 var32a;
			vu32 var32b;
			
			vu32 var16a;
			vu32 var32c;
			vu32 var32d;
			
			Modify_B_READ = Imon1_value;
			Modify_D_READ = Contr_Laod;
			Modify_B_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];
			
			var32a = Modify_B_ACT;
			var32a = var32a - Modify_A_ACT;
			var32a = var32a << 12;
			var16 = Modify_B_READ - Modify_A_READ;
			var32a = var32a / var16;
			REG_CorrectionA1 = var32a;
			var32a = Modify_B_ACT;
			var32a = var32a << 12;
			var32b = Modify_B_READ;
			var32b = var32b * REG_CorrectionA1;
			if (var32a < var32b)
			{
				var32b = var32b - var32a;
				REG_ReadA1_Offset = var32b;
				Polar1 |= 0x01;
			}
			else 
			{
				var32a = var32a - var32b;
				REG_ReadA1_Offset = var32a;
				Polar1 &= ~0x01;					
			}
//---------------------------------------------------------------------------------//
			var32c = Modify_B_ACT; 
			var32c = var32c - Modify_A_ACT;
			var32c = var32c << 12;
			var16a=Modify_D_READ-Modify_C_READ;
			var16a=var16a*2;
			var32c=var32c/var16a;
			SET_CorrectionA1 = var32c;
			var32c = Modify_B_ACT;
			var32c = var32c << 12;
			var32d = SET_CorrectionA1;
			var32d = var32d * (Modify_D_READ*2);
			if (var32c < var32d)
			{
				var32d = var32d - var32c;
				SET_ReadA1_Offset = var32d;
				Polar1 |= 0x04;
			}
			else 
			{
				var32c = var32c - var32d;
				SET_ReadA1_Offset = var32c;
				Polar1 &= ~0x04;
			}
			Flash_Write_all ();	
			Flag_DAC_OFF =0;
		}
				/*******************************电源电压控制和测量校准******************************************/	
			if (g_tModS.RxBuf[1] == 0x0B)			   //电流测量校准
			{
				Modify_A_READ = Vmon1_value;//测量电流
				Modify_C_READ = Contr_Voltage;//设置电流
				Modify_A_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];
			}

			if (g_tModS.RxBuf[1] == 0x0C)			   //电流测量校准完成
			{
				vu32 var16;
				vu32 var32a;
				vu32 var32b;
				
				vu32 var16a;
				vu32 var32c;
				vu32 var32d;
				Modify_D_READ = Contr_Voltage;
				Modify_B_READ = Vmon1_value;
				Modify_B_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];//读取高段
				var32a = Modify_B_ACT;
				var32a = var32a - Modify_A_ACT;
				var32a = var32a << 14;
				var16 = Modify_B_READ - Modify_A_READ;
				var32a = var32a / var16;
				REG_CorrectionV1 = var32a;
				var32a=0;
				var32a = Modify_B_ACT;
				var32a = var32a << 14;
				var32b = Modify_B_READ;
				var32b = var32b * REG_CorrectionV1;
				if (var32a < var32b)
				{
					var32b = var32b - var32a;
					REG_ReadV1_Offset = var32b;
					Polar2 |= 0x01;
				}
				else 
				{
					var32a = var32a - var32b;
					REG_ReadV1_Offset = var32a;
					Polar2 &= ~0x01;
				}			
				
//				vu16 var16;
//				vu32 var32a;
//				vu32 var32b;
//				
//				vu16 var16a;
//				vu32 var32c;
//				vu32 var32d;
//				
//				Modify_D_READ = Contr_Voltage;
//				Modify_B_READ = Vmon1_value;
//				Modify_B_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];
//				var32a = Modify_B_ACT;
//				var32a = var32a - Modify_A_ACT;
//				var32a = var32a << 12;
//				var16 = Modify_B_READ - Modify_A_READ;
//				var32a = var32a / var16;
//				REG_CorrectionV1 = var32a;
//				var32a = Modify_B_ACT;
//				var32a = var32a << 12;
//				var32b = Modify_B_READ;
//				var32b = var32b * REG_CorrectionV1;
//				if (var32a < var32b)
//				{
//					var32b = var32b - var32a;
//					REG_ReadV1_Offset = var32b;
//					Polar2 |= 0x01;
//				}
//				else 
//				{
//					var32a = var32a - var32b;
//					REG_ReadV1_Offset = var32a;
//					Polar2 &= ~0x01;					
//				}
		//---------------------------------------------------------------------------------//
				var32c = Modify_B_ACT; //设置电压校准
				var32c = var32c - Modify_A_ACT;
				var32c = var32c << 14;
				var16a=Modify_D_READ-Modify_C_READ;
				var16a=var16a*2;
				var32c=var32c/var16a;
				SET_CorrectionV = var32c;
				var32c = Modify_B_ACT;
				var32c = var32c << 14;
				var32d = SET_CorrectionV;
				var32d = var32d * (Modify_D_READ*2);
				if (var32c < var32d)
				{
					var32d = var32d - var32c;
					SET_ReadV_Offset = var32d;
					Polar2 |= 0x04;
				}
				else 
				{
					var32c = var32c - var32d;
					SET_ReadV_Offset = var32c;
					Polar2 &= ~0x04;
				}
				Flash_Write_all ();	
				Flag_DAC_OFF=0;
			}
			/*******************************电源CC模式电流测量和控制校准******************************************/	
			if (g_tModS.RxBuf[1] == 0x09||flag_ADJ_ALCC==1)			   //电流测量校准
			{
				Modify_A_READ = Imon_value;//测量电流
				Modify_C_READ = Contr_Current;//设置电流
				Modify_A_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];
			}

			if (g_tModS.RxBuf[1] == 0x0A||flag_ADJ_AHCC==1)			   //电流测量校准完成
			{
				vu16 var16;
				vu32 var32a;
				vu32 var32b;
				
				vu16 var16a;
				vu32 var32c;
				vu32 var32d;
				
				Modify_D_READ = Contr_Current;
				Modify_B_READ = Imon_value;
				Modify_B_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];
				var32a = Modify_B_ACT;
				var32a = var32a - Modify_A_ACT;
				var32a = var32a << 12;
				var16 = Modify_B_READ - Modify_A_READ;
				var32a = var32a / var16;
				CON_CorrectionA = var32a;
				var32a = Modify_B_ACT;
				var32a = var32a << 12;
				var32b = Modify_B_READ;
				var32b = var32b * CON_CorrectionA;
				if (var32a < var32b)
				{
					var32b = var32b - var32a;
					CON_ReadA_Offset = var32b;
					Polar2 |= 0x01;
				}
				else 
				{
					var32a = var32a - var32b;
					CON_ReadA_Offset = var32a;
					Polar2 &= ~0x01;					//电流测量系数和零点校准完成
				}
		//---------------------------------------------------------------------------------//
				var32c = Modify_B_ACT; //设置电流校准
				var32c = var32c - Modify_A_ACT;
				var32c = var32c << 14;
				var16a=Modify_D_READ-Modify_C_READ;
				var16a=var16a*2;
				var32c=var32c/var16a;
				SET_CorrectionA = var32c;
				var32c = Modify_B_ACT;
				var32c = var32c << 14;
				var32d = SET_CorrectionA;
				var32d = var32d * (Modify_D_READ*2);
				if (var32c < var32d)
				{
					var32d = var32d - var32c;
					SET_ReadA_Offset = var32d;
					Polar2 |= 0x04;
				}
				else 
				{
					var32c = var32c - var32d;
					SET_ReadA_Offset = var32c;
					Polar2 &= ~0x04;
				}
				Flash_Write_all ();	
				Flag_DAC_OFF=0;
			}
        /*************************************内阻校准**************************************************************************/
		if(g_tModS.RxBuf[1] == 0x07||flag_ADJ_VL==1)
		{
			Modify_A_READ = Rmon_value;//测量电压值
			Modify_A_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];//读取低段
		}
		if (g_tModS.RxBuf[1] == 0x08||flag_ADJ_VH==1)			   //电压测量校准完成
		{
			vu16 var16;
			vu32 var32a;
			vu32 var32b;
			
			vu16 var16a;
			vu32 var32c;
			vu32 var32d;
			Modify_B_READ =Rmon_value;//测量电压值
			flag_OverV=1;
			Modify_B_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];//读取高段
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
/***********??DAC*******************************************/
		if (g_tModS.RxBuf[1] == 0x0F)			   
		{
			Contr_Laod = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];
			Flag_DAC_OFF=1;
		}
		if (g_tModS.RxBuf[1] == 0x20)			   
		{
			Contr_Voltage = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];
			Flag_DAC_OFF=1;
		}
		if (g_tModS.RxBuf[1] == 0x21)			   
		{
			Contr_Current = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];
			Flag_DAC_OFF=1;
		}		
    }
}
//===============================AD值转换成测量值============================================//
void Transformation_ADC(void)  
{
	vu32 var32;
	vu32 var32a;
	float temp;
/*****************************测量电压转换*******************************************/
	var32 = Vmon_value;
	var32 = var32 * REG_CorrectionV;  
	if ((Polar & 0x01) == 0x01)		  
	{
		if (var32 < REG_ReadV_Offset) 
		{
			var32 = 0;
		}
		else var32 = var32 - REG_ReadV_Offset;
	}
	else var32 = var32 + REG_ReadV_Offset;
	var32 = var32 >> 12;
	if (var32 < 5) var32 = 0;				  //40mV以下清零
	Voltage = var32;
	DISS_Voltage=Voltage;
	DISS_Voltage=DISS_Voltage/100;//计算显示电压
	var32 = 0;
/*****************************稳压电源测量电压转换*******************************************/
	var32 = Vmon1_value;
	var32 = var32 * REG_CorrectionV1;  
//	if ((Polar2 & 0x01) == 0x01)		  
//	{
//		if (var32 < REG_ReadV1_Offset) 
//		{
//			var32 = 0;
//		}
//		else var32 = var32 + REG_ReadV1_Offset;
//	}
//	else 
		var32 = var32 - REG_ReadV1_Offset;
//	temp = temp * 0.8191;  
//	temp = temp - 5.2066;
	var32 = var32 >> 14;
	if (temp < 5) temp = 0;				  //40mV以下清零
	POW_Voltage = var32;
//	if(POW_Voltage >= 1600)
//	{
//		DISS_POW_Voltage=POW_Voltage - (vu16)((float)SET_Voltage*0.359);
//	}else if(POW_Voltage >= 300 && POW_Voltage < 1600){
//		DISS_POW_Voltage=POW_Voltage - (vu16)((float)SET_Voltage*0.359);
//	}else{
//		DISS_POW_Voltage=POW_Voltage - (vu16)((float)SET_Voltage*0.36);
//	}
	DISS_POW_Voltage=POW_Voltage;
	if(DISS_POW_Voltage < 0)
	{
		DISS_POW_Voltage = 0;
	}
	if(DISS_POW_Voltage > SET_Voltage - 50 && DISS_POW_Voltage < SET_Voltage + 50)
	{
		DISS_POW_Voltage = SET_Voltage;
	}
	DISS_POW_Voltage=DISS_POW_Voltage/100;//计算显示电压
	var32 = 0;
/*****************************内阻值转换*******************************************/
// 	var32 = Rmon_value;
// 	var32 = var32 * 6040;  
// // 	if ((Polar1 & 0x04) == 0x04)		  
// // 	{
// 		if (var32 < 38926) 
// 		{
// 			var32 = 0;
// 		}
// 		else {
//             var32 = var32 - 38926;
//         }
// // 	}
// // 	else var32 = var32 + REG_ReadR_Offset;
// // 	var32 = var32 >> 12;
// 	if (var32 < 5) var32 = 0;				  //40mV以下清零
// 	R_VLUE = var32/10000;
// 	var32 = 0;	
    var32 = Rmon_value;
	var32 = var32 * REG_CorrectionR;  
//	if ((Polar1 & 0x04) == 0x04)		  
//	{
//		if (var32 < REG_ReadR_Offset) 
//		{
//			var32 = 0;
//		}
//		else var32 = var32 - REG_ReadR_Offset;
//	}
//	else 
		var32 = var32 - REG_ReadR_Offset;
	var32 = var32 >> 12;
	if (var32 < 5) var32 = 0;				  //40mV以下清零
	R_VLUE = var32;
    if(R_VLUE > 100)
    {
        var32 = Rmon_value;
        var32 = var32 * REG_CorrectionRH;  
//        if ((Polar1 & 0x04) == 0x04)		  
//        {
//            if (var32 < REG_ReadRH_Offset) 
//            {
//                var32 = 0;
//            }
//            else var32 = var32 - REG_ReadRH_Offset;
//        }
//        else 
			var32 = var32 - REG_ReadRH_Offset;
        var32 = var32 >> 12;
        if (var32 < 5) var32 = 0;				  //40mV訑袀去拢
        R_VLUE = var32;
    }
	var32 = 0;	
    
/*****************************稳压电源测量电流转换*******************************************/
	var32 = Imon_value;
	var32 = var32 * CON_CorrectionA;	   
//	if ((Polar2 & 0x01) == 0x01)			   
//	{
//		if (var32 < CON_ReadA_Offset) var32 = 0;
//		else var32 = var32 - CON_ReadA_Offset;
//	}
//	else
//	{
//		var32 = var32 + CON_ReadA_Offset;
//	}	
	var32 = var32 - CON_ReadA_Offset;
	var32 = var32 >> 12;
	Current = var32;;
	DISS_POW_Current=Current;
	DISS_POW_Current=DISS_POW_Current/1000;//计算显示电流
	if(DISS_POW_Current > 6)
	{
		DISS_POW_Current = 0;
	}
/**************************稳压电源设置电压转换******************************************/
	var32 = SET_Voltage;
	var32=var32<<14;   
//	if ((Polar1 & 0x01) == 0)			   
//	{
//		if (var32 < SET_ReadV_Offset) var32 = 0;
//		else var32 = var32 - SET_ReadV_Offset;
//	}
//	else 
		var32 = var32 + SET_ReadV_Offset;
	var32 = var32/SET_CorrectionV;
	var32=var32>>1;
	Contr_Voltage = var32;
	if(SET_Voltage==0)
	{
		Contr_Voltage=0;
	}
	var32 = 0;
/**************************稳压电源设置电流转换**************************************/
	var32 = SET_Current;
	var32=var32<<14;   
	if ((Polar1 & 0x08) == 0)			   
	{
		if (var32 < SET_ReadA_Offset) var32 = 0;
		else var32 = var32 - SET_ReadA_Offset;
	}
	else var32 = var32 + SET_ReadA_Offset;
	var32 = var32/SET_CorrectionA;
	var32=var32>>1;
	Contr_Current = var32;
	if(SET_Current==0)
	{
		Contr_Current=0;
	}
	
	var32 = 0;

/*************************负载电流控制转换**************************************/
	var32 = SET_Current_Laod;
	var32=var32<<12;   
	if ((Polar2 & 0x08) == 0)			   
	{
		if (var32 < SET_ReadA1_Offset) var32 = 0;
		else var32 = var32 - SET_ReadA1_Offset;
	}
	else var32 = var32 + SET_ReadA1_Offset;
	var32 = var32/SET_CorrectionA1;
	var32=var32>>1;
	if(Flag_DAC_OFF==0)
	{
		Contr_Laod = var32;
	}
	if(SET_Current_Laod==0)
	{
		Contr_Laod=0;
	}
	
	var32 = 0;
/*******************负载测量电流转换**************************************/
	var32 = Imon1_value;
	var32 = var32 * REG_CorrectionA1;  
	if ((Polar2 & 0x04) == 0x04)		  
	{
		if (var32 < REG_ReadA1_Offset) 
		{
			var32 = 0;
		}
		else var32 = var32 - REG_ReadA1_Offset;
	}
	else var32 = var32 + REG_ReadA1_Offset;
	var32 = var32 >> 12;
	Laod_Current = var32;
	DISS_Current=Laod_Current;
	DISS_Current=DISS_Current/100;//计算显示电流
	var32 = 0;		
	
}
/********************************************************************************
  * 名称 :   MODBUS_Conrtl
  * 作者 :  zhan
  * 版本 :  V1.0
  * 日期 :  2016-xx-xx
  * 作用 :  MODBUS解析函数
  ******************************************************************************/ 
//-----------------------------CRC检测--------------------------------------------//
vu16 Hardware_CRC(vu8 *p_buffer,vu8 count)    //CRC16
{
	vu16 CRC_Result=0xffff;
	vu8 i;
	if(count==0)
	{
		count=1;
	}
	while(count--)
	{
		CRC_Result^=*p_buffer;
		for(i=0;i<8;i++)
		{
			if(CRC_Result&1)
			{
				CRC_Result>>=1;
				CRC_Result^=0xA001;
			}
			else 
			{
				CRC_Result>>=1;
			}
		}
		p_buffer++;
	}
	return CRC_Result;
}

