/**
 *
 *	@FileName							audio.c
 *	@Author								KT
 *	@CreationTime						2019/05/15
 *	@Description						创建录音功能，可选择
 *
 * 	@Include							audio.h
 *
 *	@API
 *
 **/
/*******************************************************************************
 * includes
 ******************************************************************************/
 
 #if 0
/* clib */
#include <string.h>
#include <stdio.h>

/* app */
#include "app.h"
//#include "audio_record.h"

/* api */
#include "usb_disk.h"
#include "audio.h"

/* hal */
//#include "hal_sai.h"

/* OS */
#include "semphr.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define AUDIO_RECORD_DATA_STREAM_SIZE			(64U*1024U)
#define RECORD_CHANNEL_MAX_NUM					(2)
//#define NUM_NET_RECORD_CHANNEL_MAX				(3)

//#define NUM_TOTAL_RECORD_CHANNEL_MAX			(RECORD_CHANNEL_MAX_NUM + NUM_NET_RECORD_CHANNEL_MAX)

#define AUDIO_FILE_SUFFIX						".wav"
#define AUDIO_TEMP_FILE_SUFFIX					".wavtmp"

#define AUDIO_REC_SAMPLERATE					(48000U)


/* 录音功能控制句柄 */
typedef struct {
    uint8_t index;

    uint8_t dataStreamIndex;
    DataStreamHandler_S *dataStreamHandler;

    Audio_TaskHandler_S audioHandler;

    uint32_t timeCount;
    TimerHandle_t timer;

    char *path;
    char *fname;
    FIL *fp;

} RecordHandler_S;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void AudRecord_TimerCallback(TimerHandle_t xTimer);
static void AudRecord_WavHeader(uint8_t *header, uint32_t sampleRate, uint32_t bitsPerFrame, uint32_t fileSize);

static AudRecordHandler_S AudRecord_Create(const char *path,const char *fname,HAL_SaiType_S saiType);
static void AudRecord_Dismiss(AudRecordHandler_S audRecordHandler);
static void AudRecord_Start(AudRecordHandler_S audRecordHandler);
static void AudRecord_Stop(AudRecordHandler_S audRecordHandler);
/*******************************************************************************
 * Variables
 ******************************************************************************/

static bool audioSaiInitialized = false;

/* 线程同步互斥信号量 */
//static SemaphoreHandle_t taskSynchronization = null;

static RecordHandler_S *RecordHandler[RECORD_CHANNEL_MAX_NUM] = {null};


AudRecord_S AudRecord = {
    .creat = AudRecord_Create,
    .dismiss = AudRecord_Dismiss,
    .saiStart = AudRecord_Start,
    .saiStop = AudRecord_Stop,
};
/*******************************************************************************
 * Code
 ******************************************************************************/
/**
* @Name  		AudRecord_Create
* @Author  		KT
* @Description 	创建录音
* @para    		path : 录音文件名（无后缀）
*
* @return		AudioRecordHandler_S  : 录音功能控制句柄
*/
static AudRecordHandler_S AudRecord_Create(const char *path,const char *fname,HAL_SaiType_S saiType)
{
    uint8_t i,index = 0,len, *wavHeader;
    FRESULT fResult;
    char *wavfile, *wavtmpfile;
    RecordHandler_S *handler;
    Audio_TaskHandler_S audioHandler;

    ERR_CHECK(path != null, return null);
    ERR_CHECK_DBG(UsbDisk.devConnected() == true, "Usb dose not connect!\r\n", return null);


    /* 寻找指针数组中的空闲位置 */
    for(index = 0; index < RECORD_CHANNEL_MAX_NUM; index++) {
        /* 找到未使用的控制句柄并开始分配内存及赋值 */
        if(RecordHandler[index] != null)
            continue;

        /* 分配内存到控制句柄 */
        RecordHandler[index] = MALLOC(sizeof(RecordHandler_S));
        handler = RecordHandler[index];

        if(handler == null)
            return null;

        /* 保存句柄索引 */
        handler->index = index;

        /* 创建数据流句柄，如果失败，释放之前分配的内存，函数返回NULL */
        handler->dataStreamHandler = DataStream.creat(AUDIO_RECORD_DATA_STREAM_SIZE);
        if(handler->dataStreamHandler == null) {
            FREE(handler);
            return null;
        }

        /* 创建定时器，用于录音计时 */
        handler->timeCount = 0;
        handler->timer = xTimerCreate("Audio Record Timer",MsToTick(1000),true,handler,AudRecord_TimerCallback);

        /* +15 为预留长度(后缀及后标) */
        len = strlen(path) + strlen(fname) + 15;
        wavfile = MALLOC(len);
        wavtmpfile = MALLOC(len);

        memset(wavfile,0,len);
        memset(wavtmpfile,0,len);

        /* 传入路径名称加上后缀(AUDIO_FILE_SUFFIX,AUDIO_TEMP_FILE_SUFFIX)*/
        sprintf(wavfile,"%s%s%s",path,fname,AUDIO_FILE_SUFFIX);
        sprintf(wavtmpfile,"%s%s%s",path,fname,AUDIO_TEMP_FILE_SUFFIX);

        /* 检查传入文件路径名称（后缀为.wav及.wavtmp）是否已经存在,如存在修改路径名称,添加后标(1~9) */
        if(UsbDisk.isExist(wavfile) || UsbDisk.isExist(wavtmpfile)) {
            for(i = 0; i < 10; i++) {
                sprintf(wavfile,"%s%s(%d)%s",path,fname,i,AUDIO_FILE_SUFFIX);
                sprintf(wavtmpfile,"%s%s(%d)%s",path,fname,i,AUDIO_TEMP_FILE_SUFFIX);
                if(!UsbDisk.isExist(wavfile) && !UsbDisk.isExist(wavtmpfile)) {
                    /* 添加后标后检测文件如果不存在（两种后缀下都没有相同文件），保存路径名 */
                    uint16_t size;

                    /* 保存路径 */
                    size = strlen(path) + 1;
                    handler->path = MALLOC(size);
                    memset(handler->path,0,size);
                    sprintf(handler->path,"%s",path);

                    /* 保存文件名 */
                    size = strlen(fname) + 5;
                    handler->fname = MALLOC(size);
                    memset(handler->fname,0,size);
                    sprintf(handler->fname,"%s(%d)",fname,i);

                    break;
                }

                /* 如果添加后标都无法满足，返回NULL */
                if(i >= 9) {
                    FREE(wavfile);
                    FREE(wavtmpfile);
                    return null;
                }
            }
        }

        /* 不存在，直接保存传输文件路径名称 */
        else {
            uint16_t size;

            /* 保存路径 */
            size = strlen(path) + 1;
            handler->path = MALLOC(size);
            memset(handler->path,0,size);
            sprintf(handler->path,"%s",path);

            /* 保存文件名 */
            size = strlen(fname) + 1;
            handler->fname = MALLOC(size);
            memset(handler->fname,0,size);
            sprintf(handler->fname,"%s",fname);
        }
        FREE(wavfile);

        debug("audioRecord file path: %s name: %s\r\n",handler->path,handler->fname);

        /* 新建文件 */
        handler->fp = MALLOC(sizeof(FIL));
        sprintf(wavtmpfile,"%s%s%s",handler->path,handler->fname,AUDIO_TEMP_FILE_SUFFIX);
        fResult = UsbDisk.open(handler->fp,wavtmpfile,FA_READ|FA_WRITE|FA_CREATE_NEW,true);

        if(fResult != FR_OK) {
            debug("creat new file %s fail!! res = %d\r\n",wavtmpfile,fResult);
            FREE(wavtmpfile);
            return null;
        }

        /* 先写入wav数据头,然后关闭文件，后面数据用数据流写入 */
        wavHeader = MALLOC(44);
        AudRecord_WavHeader(wavHeader,AUDIO_REC_SAMPLERATE,16U,0);
        UsbDisk.write(handler->fp,wavHeader,44,true);
        UsbDisk.close(handler->fp,true);
        FREE(wavHeader);

        /* 配置usb输出流 */
        handler->dataStreamIndex = UsbDisk.setOutputStream(wavtmpfile,handler->dataStreamHandler);
        if(handler->dataStreamIndex >= USB_MAX_DATA_STREAM_NUM) {
            debug("set usb output stream fail! index = %d\r\n",handler->dataStreamIndex);
            FREE(wavtmpfile);
            return null;
        }

        handler->audioHandler = Audio.taskCreat(tSai1);

        FREE(wavtmpfile);
        return (AudRecordHandler_S)handler;
    }
    return null;
}


/**
*	@Name  				AudRecord_Dismiss
*	@Author  			KT
* @Description 	停止并关闭录音
*	@para    			AudioRecordHandler_S * : 录音功能控制句柄
*
*/
static void AudRecord_Dismiss(AudRecordHandler_S audRecordHandler)
{

    uint8_t *wavHeader;
    uint32_t fSize;
    char *tmpPath,*wavPath;
	FILINFO *fList;
    RecordHandler_S *handler = (RecordHandler_S *)audRecordHandler;

    ERR_CHECK(handler != null,return);

    /* 关闭SAI */
    Audio.taskDismiss(handler->audioHandler);

    /* 关闭USB数据流 */
    UsbDisk.closeDataStream(handler->dataStreamIndex);
	DELAY(100);
	
    /* 删除数据流 */
    DataStream.dismiss(handler->dataStreamHandler);

    /* 更新wav数据头 */
    tmpPath = MALLOC(strlen(handler->path) + strlen(handler->fname) + 10);
    sprintf(tmpPath,"%s%s%s",handler->path,handler->fname,AUDIO_TEMP_FILE_SUFFIX);
//	sprintf(tmpPath,"%s%s",handler->fname,AUDIO_TEMP_FILE_SUFFIX);
    fSize = UsbDisk.fileSize(tmpPath);

    wavHeader = MALLOC(44);
    AudRecord_WavHeader(wavHeader,AUDIO_REC_SAMPLERATE,16U,fSize);

    UsbDisk.open(handler->fp,tmpPath,FA_WRITE|FA_OPEN_EXISTING,true);
    UsbDisk.write(handler->fp,wavHeader,44,true);
    UsbDisk.close(handler->fp,true);
    FREE(wavHeader);

    /* 修改文件名，把临时文件(.wavtmp)改为(.wav),完成录音 */
    wavPath = MALLOC(strlen(handler->fname) + 10);
    sprintf(wavPath,"%s%s",handler->fname,AUDIO_FILE_SUFFIX);
    UsbDisk.rename(tmpPath,wavPath);
	/* 打开关闭一次文件，确保改名成功 */
	UsbDisk.open(handler->fp,wavPath,FA_OPEN_EXISTING,true);
	UsbDisk.close(handler->fp,true);

//	UsbDisk.getFileList(USBDISK_ROOT,&fList);

    debug("\"%s\" audio record completed!!\r\n",wavPath);

    /* 释放内存 */
    FREE(tmpPath);
    FREE(wavPath);
    FREE(handler->path);
	FREE(handler->fname);
    FREE(handler->fp);
    xTimerDelete(handler->timer,0);
    FREE(RecordHandler[handler->index]);

    /* 音频频道数量 */
//				if(handler->type == saiAudio)
//					numSaiRecordChannel--;
//				else if(handler->type == netAudio)
//					numNetRecordChannel--;

}


/**
*	@Name  				AudRecord_Start
*	@Author  			KT
* @Description 	开始SAI数据录音
*	@para    			AudioRecordHandler_S * : 录音功能控制句柄
*
*/
static void AudRecord_Start(AudRecordHandler_S audRecordHandler)
{
    RecordHandler_S *handler = (RecordHandler_S *)audRecordHandler;

    ERR_CHECK(handler != null, return);

    Audio.starReceive(handler->audioHandler,handler->dataStreamHandler);

    xTimerStart(handler->timer,0);

    DELAY(550);
}

/**
*	@Name  				audioRecordSaiStop
*	@Author  			KT
* @Description 	暂停SAI数据录音（可恢复）
*	@para    			AudioRecordHandler_S * : 录音功能控制句柄
*
*/
static void AudRecord_Stop(AudRecordHandler_S audRecordHandler)
{
    RecordHandler_S *handler = (RecordHandler_S *)audRecordHandler;

    ERR_CHECK(handler != null, return);

    Audio.stopReceive(handler->audioHandler);

    xTimerStop(handler->timer,0);

    DELAY(550);
}




/**
*	@Name  				audioRecordNetData
*	@Author  			KT
* @Description 	网络音频输入接口
*	@para    			handler : 录音功能控制句柄
*								data		:	数据指针
*								size		：数据大小
*
*/
//static void audioRecordNetData(AudioRecordHandler_S *handler, uint8_t *data,uint32_t size){
////			uint8_t *wavHeader;
////			uint32_t fSize;
////			char *tmpPath ,*wavPath;

//			if(handler == null || handler->type == saiAudio || data == null)
//				return;
//
//			DataStream.write(handler->dataStreamHandler,data,size);
//}


/* 定时器回调函数，1S回调一次，时间计数器 +1 */
static void AudRecord_TimerCallback(TimerHandle_t xTimer)
{
    RecordHandler_S *handler;

    handler = (RecordHandler_S *)pvTimerGetTimerID(xTimer);

    handler->timeCount++;

    debug("audio file \'%s%s\' was record by %d second\r\n",handler->path,handler->fname,handler->timeCount);
}

static void AudRecord_WavHeader(uint8_t *header, uint32_t sampleRate, uint32_t bitsPerFrame, uint32_t fileSize)
{
    uint32_t totalDataLen = fileSize - 8U;
    uint32_t audioDataLen = fileSize - 44U;
    uint32_t byteRate = sampleRate * (bitsPerFrame / 8U);
    header[0] = 'R';
    header[1] = 'I';
    header[2] = 'F';
    header[3] = 'F';
    header[4] = (totalDataLen & 0xff); /* file-size (equals file-size - 8) */
    header[5] = ((totalDataLen >> 8U) & 0xff);
    header[6] = ((totalDataLen >> 16U) & 0xff);
    header[7] = ((totalDataLen >> 24U) & 0xff);
    header[8] = 'W'; /* Mark it as type "WAVE" */
    header[9] = 'A';
    header[10] = 'V';
    header[11] = 'E';
    header[12] = 'f'; /* Mark the format section 'fmt ' chunk */
    header[13] = 'm';
    header[14] = 't';
    header[15] = ' ';
    header[16] = 16; /* 4 bytes: size of 'fmt ' chunk, Length of format data.  Always 16 */
    header[17] = 0;
    header[18] = 0;
    header[19] = 0;
    header[20] = 1; /* format = 1 ,Wave type PCM */
    header[21] = 0;
    header[22] = 1; /* channels */
    header[23] = 0;
    header[24] = (sampleRate & 0xff);
    header[25] = ((sampleRate >> 8U) & 0xff);
    header[26] = ((sampleRate >> 16U) & 0xff);
    header[27] = ((sampleRate >> 24U) & 0xff);
    header[28] = (byteRate & 0xff);
    header[29] = ((byteRate >> 8U) & 0xff);
    header[30] = ((byteRate >> 16U) & 0xff);
    header[31] = ((byteRate >> 24U) & 0xff);
    header[32] = (bitsPerFrame / 8); /* block align */
    header[33] = 0;
    header[34] = bitsPerFrame; /* bits per sample */
    header[35] = 0;
    header[36] = 'd'; /*"data" marker */
    header[37] = 'a';
    header[38] = 't';
    header[39] = 'a';
    header[40] = (audioDataLen & 0xff); /* data-size (equals file-size - 44).*/
    header[41] = ((audioDataLen >> 8) & 0xff);
    header[42] = ((audioDataLen >> 16) & 0xff);
    header[43] = ((audioDataLen >> 24) & 0xff);
}

#endif
