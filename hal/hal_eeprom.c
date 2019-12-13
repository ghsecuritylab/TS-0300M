/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "hal_eeprom.h"
#include "fsl_iomuxc.h"

#include "eeprom/at24c512.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if EEPROM_AT24C512_ENABLE


#if	EEPROM_AT24C512_ENABLE

#ifndef EEPROM_AT24C512_I2C_TYPE
#define EEPROM_AT24C512_I2C_TYPE					LPI2C2
#endif

#ifndef EEPROM_AT24C512_I2C_ADDR
#define EEPROM_AT24C512_I2C_ADDR					(0xA0)
#endif

#endif



typedef struct {

    /* @brief DSP control & config LPI2C_Type */
    LPI2C_Type *base;

    /* @brief I2C address */
    uint8_t addr;

	status_t (*write)(LPI2C_Type *base,uint16_t slaveAddr,uint32_t addr,uint8_t *data,uint16_t len);
	status_t (*read)(LPI2C_Type *base,uint16_t slaveAddr,uint32_t addr,uint8_t *data,uint16_t len);	

} HAL_Eeprom_S;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/
#if	EEPROM_AT24C512_ENABLE
		HAL_Eeprom_S At24c512_driver = {
			.base = EEPROM_AT24C512_I2C_TYPE,
			.addr = EEPROM_AT24C512_I2C_ADDR,
			.write = At24c512_Write,
			.read = At24c512_Read,
		};
#endif
		
	
		
static HAL_Eeprom_S *Eeprom_drivers[EEPROM_DRIVERS_TOTAL_NUM] = {
#if	EEPROM_AT24C512_ENABLE
		&At24c512_driver,
#endif
};

/*******************************************************************************
 * Code
 ******************************************************************************/
status_t HAL_EepromWrite(HAL_EepromType_EN type,uint32_t addr,uint8_t *data,uint16_t len){
	HAL_Eeprom_S *eeprom;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < EEPROM_DRIVERS_TOTAL_NUM), return kStatus_Fail);
	ERR_CHECK(data != null, return kStatus_Fail);
    eeprom = Eeprom_drivers[type];

    return eeprom->write(eeprom->base,eeprom->addr,addr,data,len);
}


status_t HAL_EepromRead(HAL_EepromType_EN type,uint32_t addr,uint8_t *data,uint16_t len){
	HAL_Eeprom_S *eeprom;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < EEPROM_DRIVERS_TOTAL_NUM), return kStatus_Fail);
	ERR_CHECK(data != null, return kStatus_Fail);
    eeprom = Eeprom_drivers[type];

    return eeprom->read(eeprom->base,eeprom->addr,addr,data,len);
}


#endif

