/******************** (C) COPYRIGHT 2014 KUNKIN********************
 * ����    :TIM6.h
 * ����    :����
 * ����    :
 * �������:
 * Ӳ������:
 * �޸�����:2015-2-5
*******************************************************************/
	

#ifndef _tim6_h_
#define _tim6_h_

void TIM6_Config(void);
static void TIM6_NVIC_Config(void);
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_IRQHandler(void);
#endif
