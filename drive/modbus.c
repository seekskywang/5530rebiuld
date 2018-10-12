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
vu16 Correct_Parametet[13];//У׼����
vu32 Correct_Strong[9];//У׼ϵ��
/*************************��������***********************************/
vu16 Run_Control[43];
vu8 ADDR;
//============================��������===============================//
vu16 Hardware_CRC(vu8 *p_buffer,vu8 count);
//===========================MODBUSЭ��=============================//
void UART_Action(void)
{//RUT��ʽ��
	//ADDR  ������  ���Ĵ�������ʼ��ַ��   ���Ĵ�������ʼ��ַ��  �������ָ������ֽ�   �����ݸ������ֽ�  CRC�� CRC��
	//���ظ�ʽ��ADDR ������ ���������ֽ���  ���ݸ�  ���ݵ� ..... CRC��  CRC��
	if (UART_Buffer_Rece[0] == ADDR)
	{
		if (UART_Buffer_Rece[1] == (0x03))	//����3 ������   
		{																		 
			vu8 i;
			vu16 crc_result;
			crc_result = (UART_Buffer_Rece[6] << 8) + UART_Buffer_Rece[7];
			if ((crc_result == Hardware_CRC(UART_Buffer_Rece,6)) ||(crc_result == 0) )
			{
				if (UART_Buffer_Rece[3] < 0x07)    								//����Ĵ����ڿɶ���Χ��
				{
					if ((UART_Buffer_Rece[3] + UART_Buffer_Rece[5]) < 0x0F)		//������һ����ȡ�ļĴ�����ַ�ڿɶ���Χ��
					{							
						UART_Buffer_Send[0] = ADDR;
						UART_Buffer_Send[1] = 0x03;
						UART_Buffer_Send[2] = UART_Buffer_Rece[5]*2;
						for (i=0;i<UART_Buffer_Send[2];i++)
						{
							if ((i % 2) == 0) UART_Buffer_Send[3 + i] = Run_Control[UART_Buffer_Rece[3] + i / 2] >> 8;
							else UART_Buffer_Send[3 + i] = Run_Control[UART_Buffer_Rece[3] + i / 2];														
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
	if ((UART_Buffer_Rece[0] == 0) || (UART_Buffer_Rece[0] == ADDR) || (UART_Buffer_Rece[0] == ((ADDR-1)/4+100)))	 
	{
		vu8 var8;
		vu8 a=0;
		vu16 var16;
		vu16 crc_result;
//=========================��������6 д�����Ĵ���===========================
		if (UART_Buffer_Rece[1] == 6)                                 //�жϵڶ����ֽ��Ƿ�Ϊ����6
		{
			if (UART_Buffer_Rece[3] < 0x05)							  //�ж���Ҫд�ĵ�ַ�Ƿ��ڿ�д��Χ��
			{
				crc_result = (UART_Buffer_Rece[6] << 8) + UART_Buffer_Rece[7];
				if ((crc_result == Hardware_CRC(UART_Buffer_Rece,6)) ||(crc_result == 0) )		  //���CRC
				{
					var16 = (UART_Buffer_Rece[4] << 8) + UART_Buffer_Rece[5];	//��5 6���ֽ�ΪҪд�������
					var8 = UART_Buffer_Rece[3];	        						//��3 4���ֽ�ΪҪд��ĵ�ַ
					Run_Control[var8] = var16;			    //������д��ָ���ĵ�ַ

					if (UART_Buffer_Rece[0] == ADDR)							//�㲥ģʽ�²���������
					{
						for (a=0;a<8;a++)
						{UART_Buffer_Send[a] = UART_Buffer_Rece[a];}
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
		if (UART_Buffer_Rece[1] == 16)										  
		{	
			if ((UART_Buffer_Rece[6] == 6) && (UART_Buffer_Rece[3] == 0x00))	//�涨��д�Ĵ����ĸ���
			{
				crc_result = (UART_Buffer_Rece[13] << 8) + UART_Buffer_Rece[14];
				if ((crc_result == Hardware_CRC(UART_Buffer_Rece,13)) ||(crc_result == 0) )	   //���CRC
				{												
					for (var8=0;var8<3;var8++) Run_Control[var8] = (UART_Buffer_Rece[var8*2+7] << 8) + UART_Buffer_Rece[var8*2+8];

					if (UART_Buffer_Rece[0] == ADDR)					  //�㲥ģʽ����������
					{
						UART_Buffer_Send[0] = ADDR;
						UART_Buffer_Send[1] = 16;
						UART_Buffer_Send[2] = UART_Buffer_Rece[2];
						UART_Buffer_Send[3] = UART_Buffer_Rece[3];
						UART_Buffer_Send[4] = UART_Buffer_Rece[4];
						UART_Buffer_Send[5] = UART_Buffer_Rece[5];
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
    if (((UART_Buffer_Rece[0] == 0x01)&&(UART_Buffer_Rece[2] == 0xA5))||(flag_ADJ_ON==1))			   //��ѹУ׼
	{
        /*************************************����У׼**************************************************************************/
		if(UART_Buffer_Rece[1] == 0x07||flag_ADJ_VL==1)
		{
			Modify_A_READ = Rmon_value;//������ѹֵ
			Modify_A_ACT = (UART_Buffer_Rece[3] << 8) + UART_Buffer_Rece[4];//��ȡ�Ͷ�
		}
		if (UART_Buffer_Rece[1] == 0x08||flag_ADJ_VH==1)			   //��ѹ����У׼���
		{
			vu16 var16;
			vu32 var32a;
			vu32 var32b;
			
			vu16 var16a;
			vu32 var32c;
			vu32 var32d;
			Modify_B_READ =Rmon_value;//������ѹֵ
			flag_OverV=1;
			Modify_B_ACT = (UART_Buffer_Rece[3] << 8) + UART_Buffer_Rece[4];//��ȡ�߶�
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
    }
}
//===============================ADֵת���ɲ���ֵ============================================//
void Transformation_ADC(void)  
{
	vu32 var32;
	vu32 var32a;
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
	if ((Polar3 & 0x01) == 0x01)		  
	{
		if (var32 < REG_ReadV1_Offset) 
		{
			var32 = 0;
		}
		else var32 = var32 - REG_ReadV1_Offset;
	}
	else var32 = var32 + REG_ReadV1_Offset;
	var32 = var32 >> 14;
	if (var32 < 5) var32 = 0;				  //40mV��������
	POW_Voltage = var32;
	DISS_POW_Voltage=POW_Voltage;
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
	if ((Polar1 & 0x04) == 0x04)		  
	{
		if (var32 < REG_ReadR_Offset) 
		{
			var32 = 0;
		}
		else var32 = var32 - REG_ReadR_Offset;
	}
	else var32 = var32 + REG_ReadR_Offset;
	var32 = var32 >> 12;
	if (var32 < 5) var32 = 0;				  //40mV��������
	R_VLUE = var32;
	var32 = 0;	
    
/*****************************��ѹ��Դ��������ת��*******************************************/
	var32 = Imon_value;
	var32 = var32 * CON_CorrectionA;	   
	if ((Polar2 & 0x01) == 0x01)			   
	{
		if (var32 < CON_ReadA_Offset) var32 = 0;
		else var32 = var32 - CON_ReadA_Offset;
	}
	else
	{
		var32 = var32 + CON_ReadA_Offset;
	}	
	var32 = var32 >> 12;
	Current = var32;;
	DISS_POW_Current=Current;
	DISS_POW_Current=DISS_POW_Current/1000;//������ʾ����
/**************************��ѹ��Դ���õ�ѹת��******************************************/
	var32 = SET_Voltage;
	var32=var32<<14;   
	if ((Polar1 & 0x01) == 0)			   
	{
		if (var32 < SET_ReadV_Offset) var32 = 0;
		else var32 = var32 - SET_ReadV_Offset;
	}
	else var32 = var32 + SET_ReadV_Offset;
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

