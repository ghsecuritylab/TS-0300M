#ifndef __USBDISKAPP_H__
#define __USBDISKAPP_H__

#include "stdint.h"
#include "ff.h"
#include "app_common.h"
#include "data_stream.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define USBDISK_ROOT									"1:"
#define RES_MAX_WAIT									MAX_NUM

/**
 * @description 最大数据流通道数量
**/
#define USB_MAX_DATA_STREAM_NUM				4


typedef struct {
    void (*init)(void);
	void (*launch)(void);
	bool (*devConnected)(void);
	bool (*isExist)(const char *);
	void (*waitDevConnect)(void);
	uint32_t (*fileSize)(const char *);
	void (*rename)(const char *,const char *);

    FRESULT (*mkdir)(const char *, bool );
    FRESULT (*open)(FIL *,const char *,BYTE,bool );
    FRESULT (*write)(FIL *,const uint8_t*, uint32_t,bool );
    FRESULT (*close)(FIL *,bool );
	FRESULT (*read)(FIL *,uint8_t*, uint32_t,bool );
		
	size_t  (*freeSize)(void);
	size_t  (*totalSize)(void);
	uint8_t (*getFileList)(const TCHAR *,FILINFO **);
	
	uint8_t (*setOutputStream)(const char *,DataStreamHandler_S *);
	void (*closeDataStream)(uint8_t );
} UsbDisk_S;

/*! @brief host app device attach/detach status */
typedef enum _usb_host_app_state
{
    kStatus_DEV_Idle = 0, /*!< there is no device attach/detach */
    kStatus_DEV_Attached, /*!< device is attached */
    kStatus_DEV_Detached, /*!< device is detached */
} usb_host_app_state_t;

typedef enum {
	input = 0,
	output,
} StreamType_EN;

/*******************************************************************************
 * API
 ******************************************************************************/
extern UsbDisk_S UsbDisk;

//void USB_DiskCtrlCmdQueueSend(UsbDiskCtrlCmd *cmd);
//void USB_DiskCtrlCmdQueueSend(char *c);
#endif
