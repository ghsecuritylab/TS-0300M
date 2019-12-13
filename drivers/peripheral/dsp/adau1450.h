#ifndef __ADAU1450_H__
#define __ADAU1450_H__
#include "drivers_common.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
status_t Adau1450_Init(LPI2C_Type *base,uint16_t slaveAddr);

#endif
