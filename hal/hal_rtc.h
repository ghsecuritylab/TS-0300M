#ifndef __HAL_RTC_H_
#define __HAL_RTC_H_

#include "fsl_common.h"
#include "drivers_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef RTC_PCF8563_ENABLE
#define RTC_PCF8563_ENABLE							ENABLE
#endif	

#define RTC_DRIVERS_TOTAL_NUM						(RTC_PCF8563_ENABLE)


typedef enum {
#if	RTC_PCF8563_ENABLE
		tPcf8563,
#endif
} HAL_RtcType_EN;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
typedef enum{
	Mon, Tue, Wed, Thu,Fri, Sat, Sun
}Weekday_EN;

typedef struct {
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
	Weekday_EN weekday;
}HAL_RtcPara_S;



/*******************************************************************************
 * API
 ******************************************************************************/
status_t HAL_RtcGetDateTime(HAL_RtcType_EN type,HAL_RtcPara_S *para);
status_t HAL_RtcSetDateTime(HAL_RtcType_EN type,HAL_RtcPara_S *para);
bool HAL_RtcGetRstFlag(HAL_RtcType_EN type);
void HAL_RtcSetRstFlag(HAL_RtcType_EN type);

#endif
