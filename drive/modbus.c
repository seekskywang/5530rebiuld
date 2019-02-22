/******************** (C) COPYRIGHT 2014 KUNKIN********************
 * �ļ���  :MODBUS.C
 * ����   :
 * ����    :MODBUS?????
 * ����    :KL220A_Master
 * Ӳ������: 485
 * �޸�����:2014-12-22
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
/*************************У׼����************************************/
vu16 ADJ_Write;//У׼ʱ��д���ʵ��ֵ
vu8 DAC_Flag;//DAC�Ƿ���ر�־
vu16 Modify_A_READ;
vu16 Modify_C_READ;
vu16 Modify_A_ACT;
	
vu16 Modify_B_READ;
vu16 Modify_D_READ;
vu16 Modify_B_ACT;
vu16 Correct_Parametet[14];//У׼����
vu32 Correct_Strong[10];//У׼ϵ��
/*************************��������***********************************/
vu16 Run_Control[43];
vu8 ADDR;
extern struct MODS_T g_tModS;
//============================��������===============================//
vu16 Hardware_CRC(vu8 *p_buffer,vu8 count);
//===========================MODBUSЭ��=============================//
void UART_Action(void)
{//RUT��ʽ��
	//ADDR  ������  ���Ĵ�������ʼ��ַ��   ���Ĵ�������ʼ��ַ��  �������ָ������ֽ�   �����ݸ������ֽ�  CRC�� CRC��
	//���ظ�ʽ��ADDR ������ ���������ֽ���  ���ݸ�  ���ݵ� ..... CRC��  CRC��
	if (g_tModS.RxBuf[0] == ADDR)
	{
		if (g_tModS.RxBuf[1] == (0x03))	//����3 ������   
		{																		 
			vu8 i;
			vu16 crc_result;
			crc_result = (g_tModS.RxBuf[6] << 8) + g_tModS.RxBuf[7];
			if ((crc_result == Hardware_CRC(g_tModS.RxBuf,6)) ||(crc_result == 0) )
			{
				if (g_tModS.RxBuf[3] < 0x07)    								//����Ĵ����ڿɶ���Χ��
				{
					if ((g_tModS.RxBuf[3] + g_tModS.RxBuf[5]) < 0x0F)		//������һ����ȡ�ļĴ�����ַ�ڿɶ���Χ��
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
//===============================д�Ĵ���=================================
	if ((g_tModS.RxBuf[0] == 0) || (g_tModS.RxBuf[0] == ADDR) || (g_tModS.RxBuf[0] == ((ADDR-1)/4+100)))	 
	{
		vu8 var8;
		vu8 a=0;
		vu16 var16;
		vu16 crc_result;
//=========================��������6 д�����Ĵ���===========================
		if (g_tModS.RxBuf[1] == 6)                                 //�жϵڶ����ֽ��Ƿ�Ϊ����6
		{
			if (g_tModS.RxBuf[3] < 0x05)							  //�ж���Ҫд�ĵ�ַ�Ƿ��ڿ�д��Χ��
			{
				crc_result = (g_tModS.RxBuf[6] << 8) + g_tModS.RxBuf[7];
				if ((crc_result == Hardware_CRC(g_tModS.RxBuf,6)) ||(crc_result == 0) )		  //���CRC
				{
					var16 = (g_tModS.RxBuf[4] << 8) + g_tModS.RxBuf[5];	//��5 6���ֽ�ΪҪд�������
					var8 = g_tModS.RxBuf[3];	        						//��3 4���ֽ�ΪҪд��ĵ�ַ
					Run_Control[var8] = var16;			    //������д��ָ���ĵ�ַ

					if (g_tModS.RxBuf[0] == ADDR)							//�㲥ģʽ�²���������
					{
						for (a=0;a<8;a++)
						{UART_Buffer_Send[a] = g_tModS.RxBuf[a];}
						Transmit_BUFFERsize = 8;						//ԭ�����ݷ��أ�������CRC
						UART_SEND_flag=1;
					}
				}
			}
		}
//=======================================����������16����д�Ĵ���===========================================
//������16��ʽ:
//     ��ַ ���� д����ʼ��ַ��  д����ʼ��ַ�� д��������  д�������� д���ֽ���  ���ݸ� ���ݵ� ......CRC�� CRC��
//�������ݸ�ʽ:
//     ��ַ ���� д����ʼ��ַ��  д����ʼ��ַ��  д���ֽ����� д���ֽ�����  CRC��  CRC�� 
		if (g_tModS.RxBuf[1] == 16)										  
		{	
			if ((g_tModS.RxBuf[6] == 6) && (g_tModS.RxBuf[3] == 0x00))	//�涨��д�Ĵ����ĸ���
			{
				crc_result = (g_tModS.RxBuf[13] << 8) + g_tModS.RxBuf[14];
				if ((crc_result == Hardware_CRC(g_tModS.RxBuf,13)) ||(crc_result == 0) )	   //���CRC
				{												
					for (var8=0;var8<3;var8++) Run_Control[var8] = (g_tModS.RxBuf[var8*2+7] << 8) + g_tModS.RxBuf[var8*2+8];

					if (g_tModS.RxBuf[0] == ADDR)					  //�㲥ģʽ����������
					{
						UART_Buffer_Send[0] = ADDR;
						UART_Buffer_Send[1] = 16;
						UART_Buffer_Send[2] = g_tModS.RxBuf[2];
						UART_Buffer_Send[3] = g_tModS.RxBuf[3];
						UART_Buffer_Send[4] = g_tModS.RxBuf[4];
						UART_Buffer_Send[5] = g_tModS.RxBuf[5];
						crc_result = Hardware_CRC(UART_Buffer_Send,6);	 //����CRC��
						UART_Buffer_Send[6] = crc_result>>8;
						UART_Buffer_Send[7] = crc_result;				 
						Transmit_BUFFERsize = 8;					     //���÷����ֽ�������
						UART_SEND_flag=1;
					}
				}
			}			 
		}
	}
//===================================================================================
    if (((g_tModS.RxBuf[0] == 0x01)&&(g_tModS.RxBuf[2] == 0xA5))||(flag_ADJ_ON==1))			   //��ѹУ׼
	{
		if(g_tModS.RxBuf[1] == 0x01)
			{
				flag_ADJ_VL=0;
				Modify_A_READ = Vmon_value;//������ѹֵ
				Modify_A_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];//��ȡ�Ͷ�
			}
			if (g_tModS.RxBuf[1] == 0x02)			   //��ѹ����У׼���
			{
				vu32 var16;
				vu32 var32a;
				vu32 var32b;
				
				vu32 var16a;
				vu32 var32c;
				vu32 var32d;
				Modify_B_READ =Vmon_value;//������ѹֵ
				Modify_B_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];//��ȡ�߶�
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
				Flash_Write_all();	//����д��FLASH
				Flag_DAC_OFF=0;
			}
/************************************???��????��?*****************************************************************/
		if (g_tModS.RxBuf[1] == 0x03)			   //CC??��?
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
				/*******************************��Դ��ѹ���ƺͲ���У׼******************************************/	
			if (g_tModS.RxBuf[1] == 0x0B)			   //��������У׼
			{
				Modify_A_READ = Vmon1_value;//��������
				Modify_C_READ = Contr_Voltage;//���õ���
				Modify_A_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];
			}

			if (g_tModS.RxBuf[1] == 0x0C)			   //��������У׼���
			{
				vu32 var16;
				vu32 var32a;
				vu32 var32b;
				
				vu32 var16a;
				vu32 var32c;
				vu32 var32d;
				Modify_D_READ = Contr_Voltage;
				Modify_B_READ = Vmon1_value;
				Modify_B_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];//��ȡ�߶�
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
				var32c = Modify_B_ACT; //���õ�ѹУ׼
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
			/*******************************��ԴCCģʽ���������Ϳ���У׼******************************************/	
			if (g_tModS.RxBuf[1] == 0x09||flag_ADJ_ALCC==1)			   //��������У׼
			{
				Modify_A_READ = Imon_value;//��������
				Modify_C_READ = Contr_Current;//���õ���
				Modify_A_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];
			}

			if (g_tModS.RxBuf[1] == 0x0A||flag_ADJ_AHCC==1)			   //��������У׼���
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
					Polar2 &= ~0x01;					//��������ϵ�������У׼���
				}
		//---------------------------------------------------------------------------------//
				var32c = Modify_B_ACT; //���õ���У׼
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
        /*************************************����У׼**************************************************************************/
		if(g_tModS.RxBuf[1] == 0x07||flag_ADJ_VL==1)
		{
			Modify_A_READ = Rmon_value;//������ѹֵ
			Modify_A_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];//��ȡ�Ͷ�
		}
		if (g_tModS.RxBuf[1] == 0x08||flag_ADJ_VH==1)			   //��ѹ����У׼���
		{
			vu16 var16;
			vu32 var32a;
			vu32 var32b;
			
			vu16 var16a;
			vu32 var32c;
			vu32 var32d;
			Modify_B_READ =Rmon_value;//������ѹֵ
			flag_OverV=1;
			Modify_B_ACT = (g_tModS.RxBuf[3] << 8) + g_tModS.RxBuf[4];//��ȡ�߶�
			if(flag_OverV==1)//ֻ�е�������д��ʱ���ܽ�У׼����д��FLASH
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
				Flash_Write_all();	//����д��FLASH
				flag_OverV=0;
				Flag_DAC_OFF=0;
			}
			flag_ADJ_VH=0;//�����־λ��ֹһֱ����
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
//===============================ADֵת���ɲ���ֵ============================================//
void Transformation_ADC(void)  
{
	vu32 var32;
	vu32 var32a;
	float temp;
/*****************************������ѹת��*******************************************/
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
	if (var32 < 5) var32 = 0;				  //40mV��������
	Voltage = var32;
	DISS_Voltage=Voltage;
	DISS_Voltage=DISS_Voltage/100;//������ʾ��ѹ
	var32 = 0;
/*****************************��ѹ��Դ������ѹת��*******************************************/
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
	if (temp < 5) temp = 0;				  //40mV��������
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
	DISS_POW_Voltage=DISS_POW_Voltage/100;//������ʾ��ѹ
	var32 = 0;
/*****************************����ֵת��*******************************************/
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
// 	if (var32 < 5) var32 = 0;				  //40mV��������
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
	if (var32 < 5) var32 = 0;				  //40mV��������
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
        if (var32 < 5) var32 = 0;				  //40mVӔЂȥ£
        R_VLUE = var32;
    }
	var32 = 0;	
    
/*****************************��ѹ��Դ��������ת��*******************************************/
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
	DISS_POW_Current=DISS_POW_Current/1000;//������ʾ����
	if(DISS_POW_Current > 6)
	{
		DISS_POW_Current = 0;
	}
/**************************��ѹ��Դ���õ�ѹת��******************************************/
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
/**************************��ѹ��Դ���õ���ת��**************************************/
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

/*************************���ص�������ת��**************************************/
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
/*******************���ز�������ת��**************************************/
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
	DISS_Current=DISS_Current/100;//������ʾ����
	var32 = 0;		
	
}
/********************************************************************************
  * ���� :   MODBUS_Conrtl
  * ���� :  zhan
  * �汾 :  V1.0
  * ���� :  2016-xx-xx
  * ���� :  MODBUS��������
  ******************************************************************************/ 
//-----------------------------CRC���--------------------------------------------//
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

