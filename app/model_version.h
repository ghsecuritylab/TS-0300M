#ifndef _MODEL_VERSION_H_
#define _MODEL_VERSION_H_


/* 主机型号 */
#define TS_0300M										(0)


/* 打印设备信息 */
#define APP_PRINT_DEV_MSG()								APP_PrintDeviceMsg()


extern char *APP_BuildTime(void);
extern void APP_PrintDeviceMsg(void);
#endif
