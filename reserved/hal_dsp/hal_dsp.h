#ifndef __HAL_DSP_H_
#define __HAL_DSP_H_

#include "fsl_common.h"
#include "drivers_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef DSP_ADAU1450_ENABLE
#define DSP_ADAU1450_ENABLE							DISABLE
#endif

#ifndef DSP_ADAU1466_A_ENABLE
#define DSP_ADAU1466_A_ENABLE						ENABLE
#endif

#ifndef DSP_ADAU1466_B_ENABLE
#define DSP_ADAU1466_B_ENABLE						DISABLE
#endif

#define DSP_DRIVERS_TOTAL_NUM						(DSP_ADAU1450_ENABLE + DSP_ADAU1466_A_ENABLE + DSP_ADAU1466_B_ENABLE)


typedef enum {
#if	DSP_ADAU1450_ENABLE
    tAudu1450,
#endif

#if	DSP_ADAU1466_A_ENABLE
    tAudu1466BA,
#endif

#if	DSP_ADAU1466_B_ENABLE
    tAudu1466B,
#endif
} HAL_DspType_EN;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
status_t HAL_DspInit(HAL_DspType_EN type);



#endif
