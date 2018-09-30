/******************** (C) COPYRIGHT 2014 KUNKIN********************
 * Œƒº˛√˚  £∫FLASH.C
 * ◊˜’ﬂ    £∫¿Ó’Ò
 * √Ë ˆ    £∫STM8L151K4T6 FLASH”¶”√∫Ø ˝
 * ƒ⁄»›    £∫
 * ”≤º˛¡¨Ω”£∫
 * –ﬁ∏ƒ»’∆⁄£∫2014-12-22
********************************************************************/
#include "my_register.h" //NOP÷∏¡Ó‘⁄’‚
#include "AT24C01.h"

extern vu16 year1;
extern vu16 year2;
extern vu16 year3;
extern vu16 year4;
extern vu8 month1;
extern vu8 month2;
extern vu8 day1;
extern vu8 day2;
extern vu8 code1;
extern vu8 code2;
extern vu8 code3;
extern vu8 code4;
extern vu8 code5;
extern vu8 code6;
extern vu8 code7;
extern vu8 code8;

//================================================================//
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
} flagA, flagB,flagC,flagD;
//==================================================================//
void Flash_Write_all (void)
{
	vu8 data_8bit;
/***********************≤‚¡ø ˝æ›¥Ê¥¢****************************/
  data_8bit = REG_ReadV_Offset >> 24;
	EEPROM_WriteByte(0x01, data_8bit);
	data_8bit = REG_ReadV_Offset >> 16;
	EEPROM_WriteByte(0x02, data_8bit);
	data_8bit = REG_ReadV_Offset >> 8;
	EEPROM_WriteByte(0x03, data_8bit);
	EEPROM_WriteByte(0x04, REG_ReadV_Offset);//≤‚¡øµÁ—π
	
	data_8bit = REG_ReadA_Offset >> 24;
	EEPROM_WriteByte(0x05, data_8bit);
	data_8bit = REG_ReadA_Offset >> 16;
	EEPROM_WriteByte(0x06, data_8bit);
	data_8bit = REG_ReadA_Offset >> 8;
	EEPROM_WriteByte(0x07, data_8bit);
	EEPROM_WriteByte(0x08, REG_ReadA_Offset);//µÁ‘¥µÁ¡˜
	
	data_8bit = REG_ReadA1_Offset >> 24;
	EEPROM_WriteByte(0x33, data_8bit);
	data_8bit = REG_ReadA1_Offset >> 16;
	EEPROM_WriteByte(0x34, data_8bit);
	data_8bit = REG_ReadA1_Offset >> 8;
	EEPROM_WriteByte(0x35, data_8bit);
	EEPROM_WriteByte(0x36, REG_ReadA1_Offset);//∏∫‘ÿµÁ¡˜
	
	data_8bit = REG_ReadR_Offset >> 24;
	EEPROM_WriteByte(0x09, data_8bit);
	data_8bit = REG_ReadR_Offset >> 16;
	EEPROM_WriteByte(0x0A, data_8bit);
	data_8bit = REG_ReadR_Offset >> 8;
	EEPROM_WriteByte(0x0B, data_8bit);
	EEPROM_WriteByte(0x0C, REG_ReadR_Offset);//ƒ⁄◊Ë
	
	data_8bit = REG_ReadV1_Offset >> 24;
	EEPROM_WriteByte(0x40, data_8bit);
	data_8bit = REG_ReadV1_Offset >> 16;
	EEPROM_WriteByte(0x41, data_8bit);
	data_8bit = REG_ReadV1_Offset >> 8;
	EEPROM_WriteByte(0x42, data_8bit);
	EEPROM_WriteByte(0x43, REG_ReadV1_Offset);//µÁ‘¥µÁ—π*
	
	data_8bit=REG_CorrectionV>>8;
	EEPROM_WriteByte(0x0D, data_8bit);
	EEPROM_WriteByte(0x0E, REG_CorrectionV);
	
	data_8bit=REG_CorrectionA>>8;
	EEPROM_WriteByte(0x0F, data_8bit);
	EEPROM_WriteByte(0x10, REG_CorrectionA);
	
	data_8bit=REG_CorrectionA1>>8;
	EEPROM_WriteByte(0x37, data_8bit);
	EEPROM_WriteByte(0x38, REG_CorrectionA1);
	
	data_8bit=REG_CorrectionR>>8;
	EEPROM_WriteByte(0x11, data_8bit);
	EEPROM_WriteByte(0x12, REG_CorrectionR);
	
	data_8bit=REG_CorrectionV1>>8;
	EEPROM_WriteByte(0x44, data_8bit);
	EEPROM_WriteByte(0x45, REG_CorrectionV1);//µÁ‘¥µÁ—π*
	
	EEPROM_WriteByte(0x13,Polar);
	EEPROM_WriteByte(0x46,Polar3);//µÁ‘¥µÁ—π*
/***********************…Ë÷√ ˝æ›¥Ê¥¢****************************/
	data_8bit = SET_ReadV_Offset >> 24;
	EEPROM_WriteByte(0x14, data_8bit);
	data_8bit = SET_ReadV_Offset >> 16;
	EEPROM_WriteByte(0x15, data_8bit);
	data_8bit = SET_ReadV_Offset >> 8;
	EEPROM_WriteByte(0x16, data_8bit);
	EEPROM_WriteByte(0x17, SET_ReadV_Offset);
	
	data_8bit = SET_ReadA_Offset >> 24;
	EEPROM_WriteByte(0x18, data_8bit);
	data_8bit = SET_ReadA_Offset >> 16;
	EEPROM_WriteByte(0x19, data_8bit);
	data_8bit = SET_ReadA_Offset >> 8;
	EEPROM_WriteByte(0x1A, data_8bit);
	EEPROM_WriteByte(0x1B, SET_ReadA_Offset);
	
	data_8bit = SET_ReadA1_Offset >> 24;
	EEPROM_WriteByte(0x39, data_8bit);
	data_8bit = SET_ReadA1_Offset >> 16;
	EEPROM_WriteByte(0x3A, data_8bit);
	data_8bit = SET_ReadA1_Offset >> 8;
	EEPROM_WriteByte(0x3B, data_8bit);
	EEPROM_WriteByte(0x3C, SET_ReadA1_Offset);
	
	data_8bit=SET_CorrectionV>>8;
	EEPROM_WriteByte(0x1C, data_8bit);
	EEPROM_WriteByte(0x1D, SET_CorrectionV);
	
	data_8bit=SET_CorrectionA>>8;
	EEPROM_WriteByte(0x1E, data_8bit);
	EEPROM_WriteByte(0x1F, SET_CorrectionA);
	
	data_8bit=SET_CorrectionA1>>8;
	EEPROM_WriteByte(0x3D, data_8bit);
	EEPROM_WriteByte(0x3E, SET_CorrectionA1);
	
	EEPROM_WriteByte(0x20,Polar1);
/***********************************************************/
	data_8bit=CON_CorrectionA>>8;
	EEPROM_WriteByte(0x21, data_8bit);
	EEPROM_WriteByte(0x22, CON_CorrectionA);
	
	data_8bit = CON_ReadA_Offset >> 24;
	EEPROM_WriteByte(0x23, data_8bit);
	data_8bit = CON_ReadA_Offset >> 16;
	EEPROM_WriteByte(0x24, data_8bit);
	data_8bit = CON_ReadA_Offset >> 8;
	EEPROM_WriteByte(0x25, data_8bit);
	EEPROM_WriteByte(0x26, CON_ReadA_Offset);
	
	EEPROM_WriteByte(0x27,Polar2);
	
	data_8bit=TEMP_OFFSET>>8;
	EEPROM_WriteByte(0x28, data_8bit);
	EEPROM_WriteByte(0x29, TEMP_OFFSET);
}
//===========================================================================//
void EEPROM_READ_Coeff(void)
{
/****************”¢”éÀΩ◊Å»°*********************/
	REG_ReadV_Offset=EEPROM_READ_Byte(0x01);
	REG_ReadV_Offset=REG_ReadV_Offset<<8;
	REG_ReadV_Offset=REG_ReadV_Offset+EEPROM_READ_Byte(0x02);
	REG_ReadV_Offset=REG_ReadV_Offset<<8;
	REG_ReadV_Offset=REG_ReadV_Offset+EEPROM_READ_Byte(0x03);
	REG_ReadV_Offset=REG_ReadV_Offset<<8;
	REG_ReadV_Offset=REG_ReadV_Offset+EEPROM_READ_Byte(0x04);
	
	REG_ReadV1_Offset=EEPROM_READ_Byte(0x40);
	REG_ReadV1_Offset=REG_ReadV1_Offset<<8;
	REG_ReadV1_Offset=REG_ReadV1_Offset+EEPROM_READ_Byte(0x41);
	REG_ReadV1_Offset=REG_ReadV1_Offset<<8;
	REG_ReadV1_Offset=REG_ReadV1_Offset+EEPROM_READ_Byte(0x42);
	REG_ReadV1_Offset=REG_ReadV1_Offset<<8;
	REG_ReadV1_Offset=REG_ReadV1_Offset+EEPROM_READ_Byte(0x43);
	
	REG_ReadA_Offset=EEPROM_READ_Byte(0x05);
	REG_ReadA_Offset=REG_ReadA_Offset<<8;
	REG_ReadA_Offset=REG_ReadA_Offset+EEPROM_READ_Byte(0x06);
	REG_ReadA_Offset=REG_ReadA_Offset<<8;
	REG_ReadA_Offset=REG_ReadA_Offset+EEPROM_READ_Byte(0x07);
	REG_ReadA_Offset=REG_ReadA_Offset<<8;
	REG_ReadA_Offset=REG_ReadA_Offset+EEPROM_READ_Byte(0x08);
	
	REG_ReadA1_Offset=EEPROM_READ_Byte(0x33);
	REG_ReadA1_Offset=REG_ReadA1_Offset<<8;
	REG_ReadA1_Offset=REG_ReadA1_Offset+EEPROM_READ_Byte(0x34);
	REG_ReadA1_Offset=REG_ReadA1_Offset<<8;
	REG_ReadA1_Offset=REG_ReadA1_Offset+EEPROM_READ_Byte(0x35);
	REG_ReadA1_Offset=REG_ReadA1_Offset<<8;
	REG_ReadA1_Offset=REG_ReadA1_Offset+EEPROM_READ_Byte(0x36);
	
	REG_ReadR_Offset=EEPROM_READ_Byte(0x09);
	REG_ReadR_Offset=REG_ReadR_Offset<<8;
	REG_ReadR_Offset=REG_ReadR_Offset+EEPROM_READ_Byte(0x0A);
	REG_ReadR_Offset=REG_ReadR_Offset<<8;
	REG_ReadR_Offset=REG_ReadR_Offset+EEPROM_READ_Byte(0x0B);
	REG_ReadR_Offset=REG_ReadR_Offset<<8;
	REG_ReadR_Offset=REG_ReadR_Offset+EEPROM_READ_Byte(0x0C);
	
	REG_CorrectionV=EEPROM_READ_Byte(0x0D);
	REG_CorrectionV=REG_CorrectionV<<8;
	REG_CorrectionV=REG_CorrectionV+EEPROM_READ_Byte(0x0E);
	
	REG_CorrectionV1=EEPROM_READ_Byte(0x44);
	REG_CorrectionV1=REG_CorrectionV1<<8;
	REG_CorrectionV1=REG_CorrectionV1+EEPROM_READ_Byte(0x45);
	
	REG_CorrectionA=EEPROM_READ_Byte(0x0F);
	REG_CorrectionA=REG_CorrectionA<<8;
	REG_CorrectionA=REG_CorrectionA+EEPROM_READ_Byte(0x10);
	
	REG_CorrectionA1=EEPROM_READ_Byte(0x37);
	REG_CorrectionA1=REG_CorrectionA1<<8;
	REG_CorrectionA1=REG_CorrectionA1+EEPROM_READ_Byte(0x38);
	
	REG_CorrectionR=EEPROM_READ_Byte(0x11);
	REG_CorrectionR=REG_CorrectionR<<8;
	REG_CorrectionR=REG_CorrectionR+EEPROM_READ_Byte(0x12);
	
	Polar=EEPROM_READ_Byte(0x13);
	Polar3=EEPROM_READ_Byte(0x46);
/******************* ®◊É”éÀΩ◊Å»°****************************/
	SET_ReadV_Offset=EEPROM_READ_Byte(0x14);
	SET_ReadV_Offset=SET_ReadV_Offset<<8;
	SET_ReadV_Offset=SET_ReadV_Offset+EEPROM_READ_Byte(0x15);
	SET_ReadV_Offset=SET_ReadV_Offset<<8;
	SET_ReadV_Offset=SET_ReadV_Offset+EEPROM_READ_Byte(0x16);
	SET_ReadV_Offset=SET_ReadV_Offset<<8;
	SET_ReadV_Offset=SET_ReadV_Offset+EEPROM_READ_Byte(0x17);
	
	SET_ReadA_Offset=EEPROM_READ_Byte(0x18);
	SET_ReadA_Offset=SET_ReadA_Offset<<8;
	SET_ReadA_Offset=SET_ReadA_Offset+EEPROM_READ_Byte(0x19);
	SET_ReadA_Offset=SET_ReadA_Offset<<8;
	SET_ReadA_Offset=SET_ReadA_Offset+EEPROM_READ_Byte(0x1A);
	SET_ReadA_Offset=SET_ReadA_Offset<<8;
	SET_ReadA_Offset=SET_ReadA_Offset+EEPROM_READ_Byte(0x1B);
	
	SET_ReadA1_Offset=EEPROM_READ_Byte(0x39);
	SET_ReadA1_Offset=SET_ReadA1_Offset<<8;
	SET_ReadA1_Offset=SET_ReadA1_Offset+EEPROM_READ_Byte(0x3A);
	SET_ReadA1_Offset=SET_ReadA1_Offset<<8;
	SET_ReadA1_Offset=SET_ReadA1_Offset+EEPROM_READ_Byte(0x3B);
	SET_ReadA1_Offset=SET_ReadA1_Offset<<8;
	SET_ReadA1_Offset=SET_ReadA1_Offset+EEPROM_READ_Byte(0x3C);
	
	SET_CorrectionV=EEPROM_READ_Byte(0x1C);
	SET_CorrectionV=SET_CorrectionV<<8;
	SET_CorrectionV=SET_CorrectionV+EEPROM_READ_Byte(0x1D);
	
	SET_CorrectionA=EEPROM_READ_Byte(0x1E);
	SET_CorrectionA=SET_CorrectionA<<8;
	SET_CorrectionA=SET_CorrectionA+EEPROM_READ_Byte(0x1F);
	
	SET_CorrectionA1=EEPROM_READ_Byte(0x3D);
	SET_CorrectionA1=SET_CorrectionA1<<8;
	SET_CorrectionA1=SET_CorrectionA1+EEPROM_READ_Byte(0x3E);
	
	
	Polar1=EEPROM_READ_Byte(0x20);
	
	CON_CorrectionA=EEPROM_READ_Byte(0x21);
	CON_CorrectionA=CON_CorrectionA<<8;
	CON_CorrectionA=CON_CorrectionA+EEPROM_READ_Byte(0x22);
	
	CON_ReadA_Offset=EEPROM_READ_Byte(0x23);
	CON_ReadA_Offset=CON_ReadA_Offset<<8;
	CON_ReadA_Offset=CON_ReadA_Offset+EEPROM_READ_Byte(0x24);
	CON_ReadA_Offset=CON_ReadA_Offset<<8;
	CON_ReadA_Offset=CON_ReadA_Offset+EEPROM_READ_Byte(0x25);
	CON_ReadA_Offset=CON_ReadA_Offset<<8;
	CON_ReadA_Offset=CON_ReadA_Offset+EEPROM_READ_Byte(0x26);
	Polar2=EEPROM_READ_Byte(0x27);
	
/*****************◊Å»°⁄ò‹∫«∞ ®◊É÷µ*************************/
	pow_v=EEPROM_READ_Byte(0x2A);
	pow_v=pow_v<<8;
	pow_v=pow_v+EEPROM_READ_Byte(0x2B);
	
	pow_c=EEPROM_READ_Byte(0x2C);
	pow_c=pow_c<<8;
	pow_c=pow_c+EEPROM_READ_Byte(0x2D);
	
	TEMP_OFFSET=EEPROM_READ_Byte(0x28);
	TEMP_OFFSET=TEMP_OFFSET<<8;
	TEMP_OFFSET=TEMP_OFFSET+EEPROM_READ_Byte(0x29);

/*****************◊Å»°ÿ§ƒπ«∑◊¥Ã¨*************************/
//	Beep_Flag=EEPROM_READ_Byte(0x2E);
	t_beep=EEPROM_READ_Byte(0x2F);
    para_set4 = EEPROM_READ_Byte(0x56);
    para_set2 = EEPROM_READ_Byte(0x55);
    lang = EEPROM_READ_Byte(0x74);
    b_type = EEPROM_READ_Byte(0x57);
    buffer = EEPROM_READ_Byte(0x58);
    para_set1 = EEPROM_READ_Byte(0x59);
    year1 = EEPROM_READ_Byte(0x5A);
    year2 = EEPROM_READ_Byte(0x5B);
    year3 = EEPROM_READ_Byte(0x5C);
    year4 = EEPROM_READ_Byte(0x5D);
    month1 = EEPROM_READ_Byte(0x5E);
    month2 = EEPROM_READ_Byte(0x5F);
    day1 = EEPROM_READ_Byte(0x60);
    day2 = EEPROM_READ_Byte(0x61);
    code1 = EEPROM_READ_Byte(0x62);
    code2 = EEPROM_READ_Byte(0x63);
    code3 = EEPROM_READ_Byte(0x64);
    code4 = EEPROM_READ_Byte(0x65);
    code5 = EEPROM_READ_Byte(0x66);
    code6 = EEPROM_READ_Byte(0x67);
    code7 = EEPROM_READ_Byte(0x68);
    code8 = EEPROM_READ_Byte(0x69);
    steptime = EEPROM_READ_Byte(0x75);
// 	if(Beep_Flag==set_1_off)
// 	{
// 		Flag_Beep_OFF=1;
// 	}
// 	else
// 	{
// 		Flag_Beep_OFF=0;
// 	}
	t_lock=EEPROM_READ_Byte(0x30);
	/***************◊Å—æ‹∫÷ò÷∑*********************************/
	ADDR=EEPROM_READ_Byte(0x31);
	OFFSET_Zore=EEPROM_READ_Byte(0x32);
	if(OFFSET_Zore>10)
	{
		OFFSET_Zore=0;
	}
/*****************ËØªÂèñÁ≥ªÁªüËÆæÁΩÆ‰∏ä‰∏ãÈôê*************************/
	set_max_v=EEPROM_READ_Byte(0x47);
	set_max_v=set_max_v<<8;
	set_max_v=set_max_v+EEPROM_READ_Byte(0x48);
	
	set_min_v=EEPROM_READ_Byte(0x49);
	set_min_v=set_min_v<<8;
	set_min_v=set_min_v+EEPROM_READ_Byte(0x4A);
    
	set_max_r=EEPROM_READ_Byte(0x4B);
	set_max_r=set_max_r<<8;
	set_max_r=set_max_r+EEPROM_READ_Byte(0x4C);
	
	set_min_r=EEPROM_READ_Byte(0x4D);
	set_min_r=set_min_r<<8;
	set_min_r=set_min_r+EEPROM_READ_Byte(0x4E);

    set_max_c=EEPROM_READ_Byte(0x4F);
	set_max_c=set_max_c<<8;
	set_max_c=set_max_c+EEPROM_READ_Byte(0x50);
	
	set_min_c=EEPROM_READ_Byte(0x51);
	set_min_c=set_min_c<<8;
	set_min_c=set_min_c+EEPROM_READ_Byte(0x52);  

    load_c=EEPROM_READ_Byte(0x53);
	load_c=load_c<<8;
	load_c=load_c+EEPROM_READ_Byte(0x54); 
    
    set_init_c=EEPROM_READ_Byte(0x70);
	set_init_c=set_init_c<<8;
	set_init_c=set_init_c+EEPROM_READ_Byte(0x71);
    
    set_sbs_c=EEPROM_READ_Byte(0x72);
	set_sbs_c=set_sbs_c<<8;
	set_sbs_c=set_sbs_c+EEPROM_READ_Byte(0x73);
    
    opv1=EEPROM_READ_Byte(0x76);
	opv1=opv1<<8;
	opv1=opv1+EEPROM_READ_Byte(0x77);
    
    opv2=EEPROM_READ_Byte(0x7C);
	opv2=opv2<<8;
	opv2=opv2+EEPROM_READ_Byte(0x7D);
    
    opv3=EEPROM_READ_Byte(0x7E);
	opv3=opv3<<8;
	opv3=opv3+EEPROM_READ_Byte(0x7F);
    
    cov1=EEPROM_READ_Byte(0x86);
	cov1=cov1<<8;
	cov1=cov1+EEPROM_READ_Byte(0x87);
    
    cov2=EEPROM_READ_Byte(0x88);
	cov2=cov2<<8;
	cov2=cov2+EEPROM_READ_Byte(0x89);
    
    cov3=EEPROM_READ_Byte(0x8A);
	cov3=cov3<<8;
	cov3=cov3+EEPROM_READ_Byte(0x8B);
    
    opc1=EEPROM_READ_Byte(0x78);
	opc1=opc1<<8;
	opc1=opc1+EEPROM_READ_Byte(0x79);
    
    opc2=EEPROM_READ_Byte(0x80);
	opc2=opc2<<8;
	opc2=opc2+EEPROM_READ_Byte(0x81);
    
    opc3=EEPROM_READ_Byte(0x82);
	opc3=opc3<<8;
	opc3=opc3+EEPROM_READ_Byte(0x83);
    
    coc1=EEPROM_READ_Byte(0x8C);
	coc1=coc1<<8;
	coc1=coc1+EEPROM_READ_Byte(0x8D);
    
    coc2=EEPROM_READ_Byte(0x8E);
	coc2=coc2<<8;
	coc2=coc2+EEPROM_READ_Byte(0x8F);
    
    coc3=EEPROM_READ_Byte(0x90);
	coc3=coc3<<8;
	coc3=coc3+EEPROM_READ_Byte(0x91);
    
    set_loop_count=EEPROM_READ_Byte(0x84);
    
    cdc_dc=EEPROM_READ_Byte(0x7A);
	cdc_dc=cdc_dc<<8;
	cdc_dc=cdc_dc+EEPROM_READ_Byte(0x7B);
    
    set_dc_cutoff_v=EEPROM_READ_Byte(0x92);
	set_dc_cutoff_v=set_dc_cutoff_v<<8;
	set_dc_cutoff_v=set_dc_cutoff_v+EEPROM_READ_Byte(0x93);
    

}
/****************************************************************************/
void Wrtite_Zore(void)
{
	EEPROM_WriteByte(0x32, OFFSET_Zore);
}
void Wrtite_SetVA(void)
{
	vu8 data_8bit;
  /*********************************************/
	data_8bit = SET_Voltage >> 8;
	EEPROM_WriteByte(0x2A, data_8bit);
	EEPROM_WriteByte(0x2B, SET_Voltage);
	
	data_8bit = SET_Current >> 8;
	EEPROM_WriteByte(0x2C, data_8bit);
	EEPROM_WriteByte(0x2D, SET_Current);
	/********************************************/
}

void Write_Limits(void)
{
    vu8 data_8bit;
    
	data_8bit = set_max_v >> 8;
	EEPROM_WriteByte(0x47, data_8bit);
	EEPROM_WriteByte(0x48, set_max_v);
	
	data_8bit = set_min_v >> 8;
	EEPROM_WriteByte(0x49, data_8bit);
	EEPROM_WriteByte(0x4A, set_min_v);
    
    data_8bit = set_max_r >> 8;
	EEPROM_WriteByte(0x4B, data_8bit);
	EEPROM_WriteByte(0x4C, set_max_r);
	
	data_8bit = set_min_r >> 8;
	EEPROM_WriteByte(0x4D, data_8bit);
	EEPROM_WriteByte(0x4E, set_min_r);
    
    data_8bit = set_max_c >> 8;
	EEPROM_WriteByte(0x4F, data_8bit);
	EEPROM_WriteByte(0x50, set_max_c);
	
	data_8bit = set_min_c >> 8;
	EEPROM_WriteByte(0x51, data_8bit);
	EEPROM_WriteByte(0x52, set_min_c);
    
	data_8bit = pow_v >> 8;
	EEPROM_WriteByte(0x2A, data_8bit);
	EEPROM_WriteByte(0x2B, pow_v);
	
	data_8bit = pow_c >> 8;
	EEPROM_WriteByte(0x2C, data_8bit);
	EEPROM_WriteByte(0x2D, pow_c);
    
    data_8bit = load_c >> 8;
	EEPROM_WriteByte(0x53, data_8bit);
	EEPROM_WriteByte(0x54, load_c);
    
    data_8bit = set_init_c >> 8;
	EEPROM_WriteByte(0x70, data_8bit);
	EEPROM_WriteByte(0x71, set_init_c);
    
    data_8bit = set_sbs_c >> 8;
	EEPROM_WriteByte(0x72, data_8bit);
	EEPROM_WriteByte(0x73, set_sbs_c);
    
    data_8bit = opv1 >> 8;
	EEPROM_WriteByte(0x76, data_8bit);
	EEPROM_WriteByte(0x77, opv1);
    
    data_8bit = opv2 >> 8;
	EEPROM_WriteByte(0x7C, data_8bit);
	EEPROM_WriteByte(0x7D, opv2);
    
    data_8bit = opv3 >> 8;
	EEPROM_WriteByte(0x7E, data_8bit);
	EEPROM_WriteByte(0x7F, opv3);
    
    data_8bit = cov1 >> 8;
	EEPROM_WriteByte(0x86, data_8bit);
	EEPROM_WriteByte(0x87, cov1);
    
    data_8bit = cov2 >> 8;
	EEPROM_WriteByte(0x88, data_8bit);
	EEPROM_WriteByte(0x89, cov2);
    
    data_8bit = cov3 >> 8;
	EEPROM_WriteByte(0x8A, data_8bit);
	EEPROM_WriteByte(0x8B, cov3);
    
    data_8bit = opc1 >> 8;
	EEPROM_WriteByte(0x78, data_8bit);
	EEPROM_WriteByte(0x79, opc1);
    
    data_8bit = opc2 >> 8;
	EEPROM_WriteByte(0x80, data_8bit);
	EEPROM_WriteByte(0x81, opc2);
    
    data_8bit = opc3 >> 8;
	EEPROM_WriteByte(0x82, data_8bit);
	EEPROM_WriteByte(0x83, opc3);
    
    data_8bit = coc1 >> 8;
	EEPROM_WriteByte(0x8C, data_8bit);
	EEPROM_WriteByte(0x8D, coc1);
    
    data_8bit = coc2 >> 8;
	EEPROM_WriteByte(0x8E, data_8bit);
	EEPROM_WriteByte(0x8F, coc2);
    
    data_8bit = coc3 >> 8;
	EEPROM_WriteByte(0x90, data_8bit);
	EEPROM_WriteByte(0x91, coc3);
    
	EEPROM_WriteByte(0x84, set_loop_count);
    
    data_8bit = cdc_dc >> 8;
	EEPROM_WriteByte(0x7A, data_8bit);
	EEPROM_WriteByte(0x7B, cdc_dc);
    
    data_8bit = set_dc_cutoff_v >> 8;
	EEPROM_WriteByte(0x92, data_8bit);
	EEPROM_WriteByte(0x93, set_dc_cutoff_v);
    

    
}
void Wrtite_Beep(void)//—£’¶BEEP◊¥Ã¨◊ÅFLASH◊ê
{
	EEPROM_WriteByte(0x2E, Beep_Flag);
	EEPROM_WriteByte(0x2F, t_beep);
}
/*****************************************************************************/
void Wrtite_S(void)//—£’¶BEEP◊¥Ã¨◊ÅFLASH◊ê
{
	EEPROM_WriteByte(0x59, para_set1);
    EEPROM_WriteByte(0x74, lang);
}

void Write_info(void)
{
	EEPROM_WriteByte(0x5A,year1);
    EEPROM_WriteByte(0x5B,year2);
    EEPROM_WriteByte(0x5C,year3);
    EEPROM_WriteByte(0x5D,year4);
    EEPROM_WriteByte(0x5E,month1);
    EEPROM_WriteByte(0x5F,month2);
    EEPROM_WriteByte(0x60,day1);
    EEPROM_WriteByte(0x61,day2);
    EEPROM_WriteByte(0x62,code1);
    EEPROM_WriteByte(0x63,code2);
    EEPROM_WriteByte(0x64,code3);
    EEPROM_WriteByte(0x65,code4);
    EEPROM_WriteByte(0x66,code5);
    EEPROM_WriteByte(0x67,code6);
    EEPROM_WriteByte(0x68,code7);
    EEPROM_WriteByte(0x69,code8);
    
}

void Write_btype(void)
{
	EEPROM_WriteByte(0x57,b_type);
    EEPROM_WriteByte(0x58,buffer);
}
/************************************************************************/
void Write_alarm(void)
{
	EEPROM_WriteByte(0x56,para_set4);
}
/************************************************************************/
void Write_oct(void)
{
	EEPROM_WriteByte(0x55,para_set2);
}

void Wrtite_step(void)
{
	EEPROM_WriteByte(0x75, steptime);
}

/******************************************************************************/
void Wrtite_Lock(void)
{
	EEPROM_WriteByte(0x30, t_lock);
}

/************************************************************************/
void Wite_adress(void)
{
	EEPROM_WriteByte(0x31,ADDR);
}
/******************* (C) COPYRIGHT 2015 AVER *****END OF FILE*************************/

