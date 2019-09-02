#ifndef _AUDIO_RECORD_H_
#define _AUDIO_RECORD_H_

#include "app_common.h"
#include "data_stream.h"
#include "usb_disk.h"
#include "timers.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef enum {
    /* SAI接口音频数据 */
    saiAudio,
    /* 网络音频数据 */
    netAudio,
} AudioType_EN;

//typedef enum{
//	finish,
//	err,
//	usbDisconnect,
//}	AudRcodResult;

/* 录音功能控制句柄 */
typedef struct
{
    uint8_t index;
    AudioType_EN type;
    uint8_t dataStreamIndex;
    DataStreamHandler_S *dataStreamHandler;

    uint32_t timeCount;
    TimerHandle_t timer;

    char *path;
    FIL *fp;

} AudioRecordHandler_S;

/* API */
typedef struct
{
    AudioRecordHandler_S *(* creat)(const char *,AudioType_EN );
    void (* saiStart)(AudioRecordHandler_S *);
    void (* saiStop)(AudioRecordHandler_S *);
    void (* dismiss)(AudioRecordHandler_S *);
		
	void (* netData)(AudioRecordHandler_S *,uint8_t *,uint32_t);

} AudioRecord_S;
/*******************************************************************************
 * API
 ******************************************************************************/
extern AudioRecord_S AudioRecord;
#endif

