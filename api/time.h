#ifndef __TIME_H_
#define __TIME_H_

#include "hal_rtc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef HAL_RtcPara_S TimePara_S;


typedef struct {
	void (*init)(void);
	void (*getNow)(TimePara_S *para);
	void (*pirnNow)(char *str);
	void (*setNow)(TimePara_S *para);
}Time_S;
/*******************************************************************************
 * API
 ******************************************************************************/
extern Time_S Time;
#endif


