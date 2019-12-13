/*
 *	 @FileName					 hal_dsp.c
 *	 @Author					 KT
 *	 @CreationTime				 2019/09/30
 *	 @Description
 *
 *	 @Include					 hal_dsp.h
 *
 *	 @API						 
 *
 **/

#include "hal_dsp.h"
#include "fsl_iomuxc.h"
#include "dsp/adau1450.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if	DSP_ADAU1450_ENABLE

#ifndef DSP_ADAU1450_I2C_TYPE
#define DSP_ADAU1450_I2C_TYPE					LPI2C3
#endif

#ifndef DSP_ADAU1450_I2C_ADDR
#define DSP_ADAU1450_I2C_ADDR					(0x70)
#endif

#endif

#if	DSP_ADAU1466_A_ENABLE

#ifndef DSP_ADAU1466_A_I2C_TYPE
#define DSP_ADAU1466_A_I2C_TYPE					LPI2C3
#endif

#ifndef DSP_ADAU1466_A_I2C_ADDR
#define DSP_ADAU1466_A_I2C_ADDR					(0x70)
#endif

#endif

#if	DSP_ADAU1466_B_ENABLE

#ifndef DSP_ADAU1466_B_I2C_TYPE
#define DSP_ADAU1466_B_I2C_TYPE					LPI2C3
#endif

#ifndef DSP_ADAU1466_B_I2C_ADDR
#define DSP_ADAU1466_B_I2C_ADDR					(0x70)
#endif

#endif



typedef struct {

    /* @brief DSP control & config LPI2C_Type */
    LPI2C_Type *base;

    /* @brief I2C address */
    uint8_t addr;

    status_t (*init)(LPI2C_Type *base,uint16_t slaveAddr);


} HAL_Dsp_S;


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if	DSP_ADAU1450_ENABLE
	HAL_Dsp_S Adau1450_driver = {
		.base = DSP_ADAU1450_I2C_TYPE,
		.addr = DSP_ADAU1450_I2C_ADDR,
		.init = Adau1450_Init,
	};
#endif
	
#if	DSP_ADAU1466_A_ENABLE
	HAL_Dsp_S Adau1466_A_driver = {
		.base = DSP_ADAU1466_A_I2C_TYPE,
		.addr = DSP_ADAU1466_A_I2C_ADDR,
		.init = Adau1466_Init,
	};
#endif

#if	DSP_ADAU1466_B_ENABLE
		HAL_Dsp_S Adau1466_B_driver = {
			.base = DSP_ADAU1466_B_I2C_TYPE,
			.addr = DSP_ADAU1466_B_I2C_TYPE,
			.init = Adau1466_Init,
		};
#endif


	
static HAL_Dsp_S *Dsp_drivers[DSP_DRIVERS_TOTAL_NUM] = {
#if	DSP_ADAU1450_ENABLE
		&Adau1450_driver,
#endif
	
#if	DSP_ADAU1466_A_ENABLE
		&Adau1466_A_driver,
#endif
	
#if	DSP_ADAU1466_B_ENABLE
		&Adau1466_B_driver,
#endif
	};



/*******************************************************************************
 * Code
 ******************************************************************************/

status_t HAL_DspInit(HAL_DspType_EN type){
	 HAL_Dsp_S *dsp;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < DSP_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    dsp = Dsp_drivers[type];

    return dsp->init(dsp->base,dsp->addr);
}



