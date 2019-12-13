/**
 *
 *	@name				at24c512.c
 *	@modify 			KT
 *	@date 				2019/09/30
 *	@brief				
 *
 *  @API				
 *
 *  @description   		
 *
 **/

#include "eeprom/at24c512.h"
#include "fsl_lpi2c.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* ¼Ä´æÆ÷µØÖ·³¤¶È */
#define AT24C512_SUB_ADDR_SIZE					(2U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/
/*******************************************************************************
 * Code
 ******************************************************************************/
status_t At24c512_Write(LPI2C_Type *base,uint16_t slaveAddr,uint32_t addr,uint8_t *data,uint16_t len)
{
	if(data == null || len == 0)
		return kStatus_Fail;

	I2C_Write(base,slaveAddr,addr,AT24C512_SUB_ADDR_SIZE,data,len);

	return kStatus_Success;
}


status_t At24c512_Read(LPI2C_Type *base,uint16_t slaveAddr,uint32_t addr,uint8_t *data,uint16_t len)
{
	if(data == null || len == 0)
		return kStatus_Fail;

	I2C_Read(base,slaveAddr,addr,AT24C512_SUB_ADDR_SIZE,data,len);

	return kStatus_Success;
}



