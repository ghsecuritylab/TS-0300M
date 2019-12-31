#ifndef _APP_H_
#define _APP_H_

/*******************************************************************************
 * Device model & Application version
 ******************************************************************************/
#include "model_version.h"
/**************************** 本机型号 *******************************/
#define DEVICE_MODEL									TS_0300M
/*********************************************************************/

/**************************** 软件版本 *******************************/
#define APP_VERSION										"V1.0"
/*********************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
 /* OS */
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

/* c lib */
//#include "stdbool.h"

/* api */
#include "debug.h"
#include "ram.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* 最大数值 */
#define MAX_NUM  										(0xffffffffUL)	

/* 微秒与系统Tick转换 */
#define MsToTick(ms) 									((1000L + ((uint32_t)configTICK_RATE_HZ * (uint32_t)(ms - 1U))) / 1000L)
#define TickToMs(tick) 									((tick)*1000uL / (uint32_t)configTICK_RATE_HZ)

/* OS延时函数 */
#define DELAY(ms)										vTaskDelay(MsToTick(ms))

/* null值 */
#ifndef null
#define null 											0
#endif

///* reserved(开发用，表示未确定参数) */
//#ifndef reserved
//#define reserved 										null
//#endif


/* 错误条件判断 */
#define ERR_CHECK(condition, implement) 				do { if (!(condition)) {implement;}} while(0)
/* 带debug错误条件判断 */
#define ERR_CHECK_DBG(condition, dbg, implement) 		do { if (!(condition)) {debug(dbg); implement;}} while(0)

/* 软件编译时间 */
#define APP_BUILD_TIME									APP_BuildTime()



#endif
