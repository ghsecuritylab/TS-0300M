/**
 *
 *	@name				time.c
 *	@author 			KT
 *	@date 				2019/12/11
 *  @include			time.h
 *
 *	@description		用于获取设备系统时间，设备注册功能；
 *
 **/
#include "hal_rtc.h"
#include "time.h"
/*******************************************************************************
 * includes
 ******************************************************************************/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void Time_Launch(void);


//HAL_RtcPara_S *para;
//	para = MALLOC(sizeof(HAL_RtcPara_S));
//	
//	para->year = 19;
//		para->month = 12;
//		para->day = 10;
//		para->hour = 14;
//		para->min = 38;
//		para->sec = 30;
//		HAL_RtcSetDateTime(tPcf8563,para);
////	if(HAL_RtcGetRstFlag(tPcf8563)){
////		debug("RTC has been reset,please check the battery!!\r\n");
////		para = MALLOC(sizeof(HAL_RtcPara_S));

////		para->year = 19;
////		para->month = 12;
////		para->day = 10;
////		para->hour = 14;
////		para->min = 38;
////		para->sec = 30;
////		
////		HAL_RtcSetDateTime(tPcf8563,para);
////		
////		HAL_RtcSetRstFlag(tPcf8563);
////	}
//DELAY(1000);
//	HAL_RtcGetDateTime(tPcf8563, para);
//	
//	sprintf(dateTimeStr,"%02d-%02d-%02d %02d:%02d:%02d",para->year,para->month,para->day,para->hour,para->min,para->sec);
//	debug("Date time : %s \r\n",dateTimeStr);

/*******************************************************************************
 * Variables
 ******************************************************************************/
Time_S Time = {
	.launch = Time_Launch,
};


/*******************************************************************************
 * Code
 ******************************************************************************/
static void Time_Launch(void){
	if(HAL_RtcGetRstFlag(tPcf8563)){
			debug("RTC has been reset,please check the battery!!\r\n");
			
			HAL_RtcSetRstFlag(tPcf8563);
	}

}


