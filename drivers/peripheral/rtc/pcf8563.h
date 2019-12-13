#ifndef __PCF8563_H_
#define __PCF8563_H_

#include "drivers_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
status_t Pcf8563_SetDateTime(LPI2C_Type *base,uint16_t slaveAddr,
							      uint8_t year,uint8_t mon,uint8_t day,
								  uint8_t hour,uint8_t min,uint8_t sec,uint8_t weedday);

status_t Pcf8563_GetDateTime(LPI2C_Type *base,uint16_t slaveAddr,
								  uint8_t *year,uint8_t *mon,uint8_t *day,
								  uint8_t *hour,uint8_t *min,uint8_t *sec,uint8_t *weedday);

uint8_t Pcf8563_GetState_1(LPI2C_Type *base,uint16_t slaveAddr);
uint8_t Pcf8563_GetState_2(LPI2C_Type *base,uint16_t slaveAddr);
void Pcf8563_SetState_1(LPI2C_Type *base,uint16_t slaveAddr,uint8_t ctrl);
void Pcf8563_SetState_2(LPI2C_Type *base,uint16_t slaveAddr,uint8_t ctrl);

#endif

