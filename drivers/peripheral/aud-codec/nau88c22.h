#ifndef __NAU88C22_H_
#define __NAU88C22_H_

#include "drivers_common.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
status_t Nau88c22_Write(LPI2C_Type *base,uint16_t slaveAddr,uint32_t addr,uint8_t *data,uint16_t len);
status_t Nau88c22_Read(LPI2C_Type *base,uint16_t slaveAddr,uint32_t addr,uint8_t *data,uint16_t len);


#endif



