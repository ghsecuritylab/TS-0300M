#ifndef __AT24C512_H_
#define __AT24C512_H_

#include "drivers_common.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
status_t At24c512_Write(LPI2C_Type *base,uint16_t slaveAddr,uint32_t addr,uint8_t *data,uint16_t len);
status_t At24c512_Read(LPI2C_Type *base,uint16_t slaveAddr,uint32_t addr,uint8_t *data,uint16_t len);


#endif


