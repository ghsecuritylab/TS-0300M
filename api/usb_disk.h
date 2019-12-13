#ifndef __USBDISKAPP_H__
#define __USBDISKAPP_H__

#include "stdint.h"
#include "ff.h"
#include "app.h"
#include "data_stream.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define USBDISK_ROOT									"1:"
#define RES_MAX_WAIT									MAX_NUM

/* USBÁ¬½Ó×´Ì¬¼àÌýº¯Êý */
typedef void(*USB_StaListener)(status_t sta);


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

	void (*setListener)(USB_StaListener listener);
	
#if (defined(USB_STREAM_ENABLE) && USB_STREAM_ENABLE)	
	uint8_t (*setOutputStream)(const char *,DataStreamHandler_S *);
	uint8_t (*setInputStream)(const char *,DataStreamHandler_S *);
	void (*closeDataStream)(uint8_t );
#endif
} UsbDisk_S;

/*! @brief host app device attach/detach status */
typedef enum {
    kStatus_DEV_Idle = 0, /*!< there is no device attach/detach */
    kStatus_DEV_Attached, /*!< device is attached */
    kStatus_FS_Mounted,    /*!< File System is mounted */
    kStatus_DEV_Detached, /*!< device is detached */
} UsbState_EN;

#if (defined(USB_STREAM_ENABLE) && USB_STREAM_ENABLE)
typedef enum {
	input = 0,
	output,
} StreamType_EN;
#endif




/*******************************************************************************
 * API
 ******************************************************************************/
extern UsbDisk_S UsbDisk;

#endif
