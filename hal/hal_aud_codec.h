#ifndef __HAL_AUD_CODEC_H_
#define __HAL_AUD_CODEC_H_

#include "fsl_common.h"
#include "drivers_common.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
#ifndef AUD_CODEC_NAU88C22_ENABLE
#define AUD_CODEC_NAU88C22_ENABLE							ENABLE
#endif
	
#define AUD_CODEC_DRIVERS_TOTAL_NUM							(AUD_CODEC_NAU88C22_ENABLE)
	
	
typedef enum {
#if	AUD_CODEC_NAU88C22_ENABLE
		tNau88c22,
#endif
} HAL_AudCodecType_EN;


/*******************************************************************************
 * API
 ******************************************************************************/
status_t HAL_AudCodecInit(HAL_AudCodecType_EN type);



#endif

