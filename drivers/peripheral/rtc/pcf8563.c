/**
 *
 *	@name				pcf8563.c
 *	@modify 			KT
 *	@date 				2019/09/30
 *	@brief				
 *
 *  @API				
 *
 *  @description   		
 *
 **/

#include "pcf8563.h"
#include "fsl_lpi2c.h"
#include "drivers_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* ¼Ä´æÆ÷µØÖ·³¤¶È */
#define PCF8563_SUB_ADDR_SIZE					(1U)

/* ¼Ä´æÆ÷µØÖ· */
#define PCF8563_CTRL_STA_1						(0x00U)
#define PCF8563_CTRL_STA_2						(0x01U)

#define PCF8563_SEC								(0x02U)
#define PCF8563_MIN								(0x03U)
#define PCF8563_HOUR							(0x04U)
#define PCF8563_DAY								(0x05U)
#define PCF8563_WEEK_DAY						(0x06U)
#define PCF8563_MONTH							(0x07U)
#define PCF8563_YEAR							(0x08U)

/* ¼Ä´æÆ÷²ÎÊýÑÚÂë */
#define SEC_MASK								(0x7FU)
#define MIN_MASK								(0x7FU)
#define HOUR_MASK								(0x3FU)
#define DAY_MASK								(0x3FU)
#define WEEK_DAY_MASK							(0x07U)
#define MONTH_MASK								(0x1FU)
#define YEAR_MASK								(0xFFU)


#define DEC_TO_BCD(dec)							((((dec) / 10) << 4) | (dec % 10))
#define BCD_TO_DEC(bcd)							((((bcd) >> 4) * 10) + (bcd & 0xF))


#define Pcf8563_WRITE(addr,data,len)		I2C_Write(base,slaveAddr,addr,PCF8563_SUB_ADDR_SIZE,data,len)
#define Pcf8563_READ(addr,data,len)			I2C_Read(base,slaveAddr,addr,PCF8563_SUB_ADDR_SIZE,data,len)


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
status_t Pcf8563_SetDateTime(LPI2C_Type *base,uint16_t slaveAddr,
								  uint8_t year,uint8_t mon,uint8_t day,
								  uint8_t hour,uint8_t min,uint8_t sec,uint8_t weedday)
{
	uint8_t data;

	if(year > 99 || mon > 12 || day > 31 || hour > 23 || min > 59 || sec > 59 || weedday > 7)
		return kStatus_Fail;

	data = DEC_TO_BCD(year);
	Pcf8563_WRITE(PCF8563_YEAR,&data,1);

	data = DEC_TO_BCD(mon);
	Pcf8563_WRITE(PCF8563_MONTH,&data,1);

	data = DEC_TO_BCD(day);
	Pcf8563_WRITE(PCF8563_DAY,&data,1);

	data = DEC_TO_BCD(hour);
	Pcf8563_WRITE(PCF8563_HOUR,&data,1);

	data = DEC_TO_BCD(min);
	Pcf8563_WRITE(PCF8563_MIN,&data,1);

	data = DEC_TO_BCD(sec);
	Pcf8563_WRITE(PCF8563_SEC,&data,1);

	data = DEC_TO_BCD(weedday);
	Pcf8563_WRITE(PCF8563_WEEK_DAY,&data,1);

	return kStatus_Success;
}


status_t Pcf8563_GetDateTime(LPI2C_Type *base,uint16_t slaveAddr,
								  uint8_t *year,uint8_t *mon,uint8_t *day,
								  uint8_t *hour,uint8_t *min,uint8_t *sec,uint8_t *weedday)
{
	uint8_t data;

	if(year == null|| mon == null || day == null || hour == null|| min == null || sec == null || weedday == null)
		return kStatus_Fail;

	Pcf8563_READ(PCF8563_YEAR,&data,1);
	*year = BCD_TO_DEC(data & YEAR_MASK);;
	
	Pcf8563_READ(PCF8563_MONTH,&data,1);
	*mon = BCD_TO_DEC(data & MONTH_MASK);

	Pcf8563_READ(PCF8563_DAY,&data,1);
	*day = BCD_TO_DEC(data & DAY_MASK);

	Pcf8563_READ(PCF8563_HOUR,&data,1);
	*hour = BCD_TO_DEC(data & HOUR_MASK);

	Pcf8563_READ(PCF8563_MIN,&data,1);
	*min = BCD_TO_DEC(data & MIN_MASK);
	
	Pcf8563_READ(PCF8563_SEC,&data,1);
	*sec = BCD_TO_DEC(data & SEC_MASK);
	
	Pcf8563_READ(PCF8563_WEEK_DAY,&data,1);
	*weedday = BCD_TO_DEC(data & WEEK_DAY_MASK);

	return kStatus_Success;
}


uint8_t Pcf8563_GetState_1(LPI2C_Type *base,uint16_t slaveAddr){
	uint8_t sta = 0;
	Pcf8563_READ(PCF8563_CTRL_STA_1,&sta,1);
	return sta;
}

uint8_t Pcf8563_GetState_2(LPI2C_Type *base,uint16_t slaveAddr){
	uint8_t sta = 0;
	Pcf8563_READ(PCF8563_CTRL_STA_2,&sta,1);
	return sta;
}

void Pcf8563_SetState_1(LPI2C_Type *base,uint16_t slaveAddr,uint8_t ctrl){
	Pcf8563_WRITE(PCF8563_CTRL_STA_1,&ctrl,1);
}

void Pcf8563_SetState_2(LPI2C_Type *base,uint16_t slaveAddr,uint8_t ctrl){
	Pcf8563_WRITE(PCF8563_CTRL_STA_2,&ctrl,1);
}
