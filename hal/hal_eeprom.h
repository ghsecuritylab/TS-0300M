#ifndef __HAL_EEPROM_H_
#define __HAL_EEPROM_H_

#include "fsl_common.h"
#include "drivers_common.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
#ifndef EEPROM_AT24C512_ENABLE
#define EEPROM_AT24C512_ENABLE							DISABLE
#endif
	
#define EEPROM_DRIVERS_TOTAL_NUM						(EEPROM_AT24C512_ENABLE)
	
#if EEPROM_AT24C512_ENABLE

typedef enum {
#if	EEPROM_AT24C512_ENABLE
		tAt24C512,
#endif
} HAL_EepromType_EN;


/*******************************************************************************
 * API
 ******************************************************************************/
status_t HAL_EepromWrite(HAL_EepromType_EN type,uint32_t addr,uint8_t *data,uint16_t len);
status_t HAL_EepromRead(HAL_EepromType_EN type,uint32_t addr,uint8_t *data,uint16_t len);

#endif

#endif
