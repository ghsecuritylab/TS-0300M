/**
 *
 *	@FileName								audioRecord.c
 *	@Author									KT
 *	@CreationTime						2019/05/15
 *	@Description						创建录音功能，可选择
 *
 * 	@Include								audio_record.h	
 *
 *	@API										 
 *
 **/
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "string.h"
#include "stdio.h"
#include "debug.h"
#include "ram.h"
#include "audio_sai.h"
#include "audio_record.h"
#include "semphr.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define AUDIO_RECORD_DATA_STREAM_SIZE			(32U*1024U)
#define NUM_SAI_RECORD_CHANNEL_MAX				(1)
#define NUM_NET_RECORD_CHANNEL_MAX				(3)

#define NUM_TOTAL_RECORD_CHANNEL_MAX			(NUM_SAI_RECORD_CHANNEL_MAX + NUM_NET_RECORD_CHANNEL_MAX)

#define AUDIO_FILE_SUFFIX						".wav"
#define AUDIO_TEMP_FILE_SUFFIX					".wavtmp"
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void audioRecord_TimerCallback(TimerHandle_t xTimer);
static void audioRecord_WavHeader(uint8_t *header, uint32_t sampleRate, uint32_t bitsPerFrame, uint32_t fileSize);

static AudioRecordHandler_S *audioRecordCreate(const char *path,AudioType_EN type);
static void audioRecordSaiStart(AudioRecordHandler_S *audioRecordHandler);
static void audioRecordSaiStop(AudioRecordHandler_S *audioRecordHandler);
static void audioRecordDismiss(AudioRecordHandler_S *audioRecordHandler);
static void audioRecordNetData(AudioRecordHandler_S *handler, uint8_t *data,uint32_t size);
/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint8_t numSaiRecordChannel = 0;
static uint8_t numNetRecordChannel = 0;

static bool audioSaiInitialized = false;

/* 线程同步互斥信号量 */
static SemaphoreHandle_t taskSynchronization = NULL;

static AudioRecordHandler_S *audioRecordHandler[NUM_TOTAL_RECORD_CHANNEL_MAX] = {NULL};


AudioRecord_S AudioRecord = {
	.creat = audioRecordCreate,
	.saiStart = audioRecordSaiStart,
	.saiStop = audioRecordSaiStop,
	.netData = audioRecordNetData,
	.dismiss = audioRecordDismiss,
};
/*******************************************************************************
 * Code
 ******************************************************************************/
/**
* @Name  		audioRecordCreate
* @Author  		KT
* @Description 	创建录音
* @para    		path	: 	录音文件名（无后缀）
*				type	:	录音类型（sai 通过sai接口数据录音  net 录音数据由代码传入（网络音频））
*
* @return		AudioRecordHandler_S * : 录音功能控制句柄
*/
static AudioRecordHandler_S *audioRecordCreate(const char *path,AudioType_EN type){
	uint8_t i,ch = 0,len, *wavHeader;
	FRESULT fResult;
	char *wavPath, *tmpPath;

	if(	!UsbDisk.devConnected || 
			(type == saiAudio && numSaiRecordChannel >= NUM_SAI_RECORD_CHANNEL_MAX)  ||
			(type == netAudio && numNetRecordChannel >= NUM_NET_RECORD_CHANNEL_MAX) 	)
			return NULL;
			
			if(taskSynchronization == NULL)
					taskSynchronization = xSemaphoreCreateMutex();
					
		/* 寻找指针数组中的空闲位置 */
		for(ch = 0;ch < NUM_TOTAL_RECORD_CHANNEL_MAX;ch++){
			/* 找到未使用的控制句柄并开始分配内存及赋值 */
			if(audioRecordHandler[ch] == NULL){
			
				xSemaphoreTake(taskSynchronization, MAX_NUM);
				
				/* 分配内存到控制句柄 */
				audioRecordHandler[ch] = MALLOC(sizeof(AudioRecordHandler_S));
				if(audioRecordHandler[ch] == NULL){
					xSemaphoreGive(taskSynchronization);
					return NULL;
				}
				
				/* 保存句柄索引 */
				audioRecordHandler[ch]->index = ch;
				/* 保存类型 */
				audioRecordHandler[ch]->type = type;
				
				/* 创建数据流，如果失败，释放之前分配的内存，函数返回NULL */
				audioRecordHandler[ch]->dataStreamHandler = DataStream.creat(AUDIO_RECORD_DATA_STREAM_SIZE);
				if(audioRecordHandler[ch]->dataStreamHandler == NULL){
					FREE(audioRecordHandler[ch]);
					xSemaphoreGive(taskSynchronization);
					return NULL;
				}
				
				/* 创建定时器，用于录音计时 */
				audioRecordHandler[ch]->timeCount = 0;
				audioRecordHandler[ch]->timer = xTimerCreate("Audio Record Timer",MsToTick(1000),true,audioRecordHandler[ch],audioRecord_TimerCallback);
				
				
				/* 传入路径名称加上后缀（后缀为.wav及.wavtmp） */
				len = strlen(path);
				wavPath = MALLOC(len+15);
				tmpPath = MALLOC(len+15);
				
				memset(wavPath,0,len+15);
				memset(tmpPath,0,len+15);
				
				sprintf(wavPath,"%s%s",path,AUDIO_FILE_SUFFIX);
				sprintf(tmpPath,"%s%s",path,AUDIO_TEMP_FILE_SUFFIX);
				
				/* 检查传入文件路径名称（后缀为.wav及.wavtmp）是否已经存在,如存在修改路径名称,添加后标(1~9) */
				if(UsbDisk.isExist(wavPath) || UsbDisk.isExist(tmpPath)){
				for(i = 0;i < 10;i++){
						sprintf(wavPath,"%s(%d)%s",path,i,AUDIO_FILE_SUFFIX);
						sprintf(tmpPath,"%s(%d)%s",path,i,AUDIO_TEMP_FILE_SUFFIX);
						if(!UsbDisk.isExist(wavPath) && !UsbDisk.isExist(tmpPath)){
							/* 添加后标后检测文件如果不存在（两种后缀下都没有相同文件），保存路径名 */
							audioRecordHandler[ch]->path = MALLOC(len+5);
							memset(audioRecordHandler[ch]->path,'\0',len+5);
							sprintf(audioRecordHandler[ch]->path,"%s(%d)",path,i);
							break;
						}
							
						/* 如果添加后标都无法满足，返回NULL */	
						if(i >= 9) {
							FREE(wavPath);
							FREE(tmpPath);
							xSemaphoreGive(taskSynchronization);
							return NULL;
						}
					}
				}
				
				/* 不存在，直接保存传输文件路径名称 */
				else{
						audioRecordHandler[ch]->path = MALLOC(len+1);
						memset(audioRecordHandler[ch]->path,'\0',len+1);
						strcpy(audioRecordHandler[ch]->path,path);
				}
				FREE(wavPath);
				
				debug("audioRecord file path = %s\r\n",audioRecordHandler[ch]->path);
				
				/* 新建文件 */
				audioRecordHandler[ch]->fp = MALLOC(sizeof(FIL));
				sprintf(tmpPath,"%s%s",audioRecordHandler[ch]->path,AUDIO_TEMP_FILE_SUFFIX);
				fResult = UsbDisk.open(audioRecordHandler[ch]->fp,tmpPath,FA_READ|FA_WRITE|FA_CREATE_NEW,true);
				
				if(fResult != FR_OK){
					debug("creat new file %s fail!! res = %d\r\n",tmpPath,fResult);
					FREE(tmpPath);
					xSemaphoreGive(taskSynchronization);
					return NULL;
				}
				/* 先写入wav数据头,然后关闭文件，后面数据用数据流写入 */
				wavHeader = MALLOC(44);
				audioRecord_WavHeader(wavHeader,48000U,16U,0);
				UsbDisk.write(audioRecordHandler[ch]->fp,wavHeader,44,true);
				UsbDisk.close(audioRecordHandler[ch]->fp,true);
				FREE(wavHeader);
				
				/* 配置usb输出流 */
				audioRecordHandler[ch]->dataStreamIndex = UsbDisk.setOutputStream(tmpPath,audioRecordHandler[ch]->dataStreamHandler);
				if(audioRecordHandler[ch]->dataStreamIndex >= USB_MAX_DATA_STREAM_NUM){
					debug("set usb output stream fail! index = %d\r\n",audioRecordHandler[ch]->dataStreamIndex);
					FREE(tmpPath);
					xSemaphoreGive(taskSynchronization);
					return NULL;
				}
				
				FREE(tmpPath);
				
				if(audioRecordHandler[ch]->type == saiAudio){
					/* 初始化音频模块,配置输入流 */
					if(!audioSaiInitialized){
							AudioSai.init();
							audioSaiInitialized = true;
					}
//					AudioSai.setInputStream(audioRecordHandler[ch]->dataStreamHandler);
				}
				
				/* 句柄分配成功，记录当前已分配的录音频道数量 */
				if(type == saiAudio)
					numSaiRecordChannel++;
				else if(type == netAudio)
					numNetRecordChannel++;
				
				xSemaphoreGive(taskSynchronization);
				return audioRecordHandler[ch];
			}
		}
		xSemaphoreGive(taskSynchronization);
		return NULL;
}


/**
*	@Name  				audioRecord_SaiRecordStart
*	@Author  			KT
* @Description 	开始SAI数据录音
*	@para    			AudioRecordHandler_S * : 录音功能控制句柄
*
*/
static void audioRecordSaiStart(AudioRecordHandler_S *handler){
		if(handler == NULL || handler->type != saiAudio)
			return;
			
			AudioSai.setInputStream(handler->dataStreamHandler);
			AudioSai.recStart(stream);
			xTimerStart(handler->timer,0);
			
			DELAY(250);
}

/**
*	@Name  				audioRecordSaiStop
*	@Author  			KT
* @Description 	暂停SAI数据录音（可恢复）
*	@para    			AudioRecordHandler_S * : 录音功能控制句柄
*
*/
static void audioRecordSaiStop(AudioRecordHandler_S *handler){
			if(handler == NULL || handler->type != saiAudio)
				return;

			AudioSai.recStop();
			xTimerStop(handler->timer,0);
			
			DELAY(250);
}


/**
*	@Name  				audioRecordDismiss
*	@Author  			KT
* @Description 	停止并关闭录音
*	@para    			AudioRecordHandler_S * : 录音功能控制句柄
*
*/
static void audioRecordDismiss(AudioRecordHandler_S *handler){
			uint8_t *wavHeader;
			uint32_t fSize;
			char *tmpPath ,*wavPath;

			if(handler == NULL)
				return;
			
			/* 关闭SAI */
//			if(handler->type == saiAudio)
//				AudioSai.deinit();
			
			/* 关闭USB数据流 */
			UsbDisk.closeDataStream(handler->dataStreamIndex);
			
			/* 删除数据流 */
			DataStream.dismiss(handler->dataStreamHandler);
			
			/* 更新wav数据头 */
			tmpPath = MALLOC(strlen(handler->path) + 10);
			sprintf(tmpPath,"%s%s",handler->path,AUDIO_TEMP_FILE_SUFFIX);
			fSize = UsbDisk.fileSize(tmpPath);
			
			wavHeader = MALLOC(44);
			audioRecord_WavHeader(wavHeader,48000U,16U,fSize);
			
			UsbDisk.open(handler->fp,tmpPath,FA_WRITE|FA_OPEN_EXISTING,true);
			UsbDisk.write(handler->fp,wavHeader,44,true);
			UsbDisk.close(handler->fp,true);
			FREE(wavHeader);
			
			/* 修改文件名，把临时文件(.wavtmp)改为(.wav),完成录音 */
			wavPath = MALLOC(strlen(handler->path) + 10);
			sprintf(wavPath,"%s%s",handler->path,AUDIO_FILE_SUFFIX);
			UsbDisk.rename(tmpPath,wavPath);
			
			debug("\"%s\" audio record completed!!\r\n",wavPath);
			
			/* 释放内存 */
			FREE(tmpPath);
			FREE(wavPath);
			FREE(handler->path);
			FREE(handler->fp);
			xTimerDelete(handler->timer,0);
			FREE(audioRecordHandler[handler->index]);
			
			/* 音频频道数量 */
				if(handler->type == saiAudio)
					numSaiRecordChannel--;
				else if(handler->type == netAudio)
					numNetRecordChannel--;
			
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
static void audioRecordNetData(AudioRecordHandler_S *handler, uint8_t *data,uint32_t size){
//			uint8_t *wavHeader;
//			uint32_t fSize;
//			char *tmpPath ,*wavPath;

			if(handler == NULL || handler->type == saiAudio || data == NULL)
				return;
			
			DataStream.write(handler->dataStreamHandler,data,size);
}


/* 定时器回调函数，1S回调一次，时间计数器 +1 */
static void audioRecord_TimerCallback(TimerHandle_t xTimer) {
		AudioRecordHandler_S *audioRecordHandler;
		
		audioRecordHandler = (AudioRecordHandler_S *)pvTimerGetTimerID(xTimer);
		
		audioRecordHandler->timeCount++;
		
		debug("audio file \'%s\' was record by %d second\r\n",audioRecordHandler->path,audioRecordHandler->timeCount);
}

static void audioRecord_WavHeader(uint8_t *header, uint32_t sampleRate, uint32_t bitsPerFrame, uint32_t fileSize)
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


