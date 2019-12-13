#ifndef _MODEL_VERSION_H_
#define _MODEL_VERSION_H_

#include <stdint.h>

/* 主机型号 */
#define TS_0300M										(0)
#define OK1061_S										(1)										


/* 打印设备信息 */
#define APP_PRINT_DEV_MSG()								APP_PrintDeviceMsg()


extern char *APP_BuildTime(void);
extern void APP_PrintDeviceMsg(void);
void APP_GetBuildDate(uint16_t *year,uint16_t *mon,uint16_t *day);

#endif
