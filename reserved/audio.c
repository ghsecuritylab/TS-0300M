/**
 *
 *	@name				audio.c
 *	@author 			KT
 *	@date 				2019/10/08
 *	@brief				
 *  @include			aduio.h
 *
 *  @API				Audio
 *
 *  @description   
 *
 **/
/*******************************************************************************
 * includes
 ******************************************************************************/
/* api */
#include "app_common.h"
#include "data_stream.h"
#include "audio.h"

/* hal */
#include "hal_sai.h"
#include "hal_dsp.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if SAI1_ENABLE
#define SAI1_SAMPLERATE				kSAI_SampleRate48KHz
#define SAI1_BITWIDTH				kSAI_WordWidth16bits
#define SAI1_MONO_STEREO			kSAI_Stereo
#define SAI1_MASTER_SLAVE			kSAI_Slave
#define SAI1_PROTOCOL				kSAI_BusI2S
#endif
	
#if SAI2_ENABLE
#define SAI2_SAMPLERATE				kSAI_SampleRate48KHz
#define SAI2_BITWIDTH				kSAI_WordWidth16bits
#define SAI2_MONO_STEREO			kSAI_Stereo
#define SAI2_MASTER_SLAVE			kSAI_Slave
#define SAI2_PROTOCOL				kSAI_BusI2S
#endif
	
#if SAI3_ENABLE
#define SAI3_SAMPLERATE				kSAI_SampleRate48KHz
#define SAI3_BITWIDTH				kSAI_WordWidth16bits
#define SAI3_MONO_STEREO			kSAI_Stereo
#define SAI3_MASTER_SLAVE			kSAI_Slave
#define SAI3_PROTOCOL				kSAI_BusI2S
#endif




#define AUDIO_CHANNEL_NUM			SAI_ENABLE_NUM

typedef struct {
	uint8_t index;

	bool enabled;

	HAL_SaiHandle_S *saiHandler;

	DataStreamHandler_S *outputStream;
	
	DataStreamHandler_S *inputStream;
}AudioHandler_S;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void Audio_Init(void);
static Audio_TaskHandler_S Audio_TaskCreat(HAL_SaiType_S type);
static void Audio_TaskDismiss(Audio_TaskHandler_S *audHandler);
static void Audio_StarReceive(Audio_TaskHandler_S *audHandler,DataStreamHandler_S *stream);
static void Audio_StarTransmit(Audio_TaskHandler_S *audHandler,DataStreamHandler_S *stream);
static void Audio_StopReceive(Audio_TaskHandler_S *audHandler);
static void Audio_StopTransmit(Audio_TaskHandler_S *audHandler);


static void Audio_SaiRxCallback(HAL_SaiHandle_S * saiHandler,uint8_t *data,uint32_t dataLen,void *param);
static void Audio_SaiTxCallback(HAL_SaiHandle_S * saiHandler,uint8_t *data,uint32_t dataLen,void *param);

/*******************************************************************************
 * Variables
 ******************************************************************************/


static AudioHandler_S AudioHandler[AUDIO_CHANNEL_NUM] = {
#if SAI1_ENABLE
	{0,false,null,null,null},
#endif

#if SAI2_ENABLE
	{1,false,null,null,null},
#endif

#if SAI3_ENABLE
	{2,false,null,null,null},
#endif

};


/* API */
Audio_S Audio = {
	.init = Audio_Init,
	.taskCreat = Audio_TaskCreat,
	.taskDismiss = Audio_TaskDismiss,
	.starReceive = Audio_StarReceive,
	.starTransmit = Audio_StarTransmit,
	.stopReceive = Audio_StopReceive,
	.stopTransmit = Audio_StopTransmit,
};

/*******************************************************************************
 * Code
 ******************************************************************************/


/**
* @Name 		Audio_Init
* @Author		KT
* @Description	
* @para 		
*
* @return		
*/
static void Audio_Init(void){
//	Sai.init();
//	Dsp.init();
}



/**
* @Name 		Audio_TaskCreat
* @Author		KT
* @Description	
* @para 		
*
* @return		
*/
static Audio_TaskHandler_S Audio_TaskCreat(HAL_SaiType_S type){
	HAL_SaiPara_S *para;
	AudioHandler_S *handler;

	ERR_CHECK((uint8_t)type < AUDIO_CHANNEL_NUM, return null);
	
	handler = &AudioHandler[type];

	ERR_CHECK(handler->enabled == false, return null);

	para = MALLOC(sizeof(HAL_SaiPara_S));
	para->type = type;
	para->param = handler;
	
	switch(type){
		
#if SAI1_ENABLE
	case tSai1:{
		para->sampleRate = SAI1_SAMPLERATE;
		para->bitWidth = SAI1_BITWIDTH;
		para->monoStereo = SAI1_MONO_STEREO;
		para->masterSlave = SAI1_MASTER_SLAVE;
		para->protocol = SAI1_PROTOCOL;
		handler->saiHandler = HAL_SaiConfig(para);
	}break;
#endif
		
#if SAI2_ENABLE
	case tSai2:{
		para->sampleRate = SAI2_SAMPLERATE;
		para->bitWidth = SAI2_BITWIDTH;
		para->monoStereo = SAI2_MONO_STEREO;
		para->masterSlave = SAI2_MASTER_SLAVE;
		para->protocol = SAI2_PROTOCOL;
		handler->saiHandler = Sai.config(para);
	}break;
#endif
		
#if SAI3_ENABLE
	case tSai3:{
		para->sampleRate = SAI3_SAMPLERATE;
		para->bitWidth = SAI3_BITWIDTH;
		para->monoStereo = SAI3_MONO_STEREO;
		para->masterSlave = SAI3_MASTER_SLAVE;
		para->protocol = SAI3_PROTOCOL;
		handler->saiHandler = Sai.config(para);
	}break;
#endif
	default:break;
	}
	FREE(para);
	handler->enabled = true;
	return (Audio_TaskHandler_S *)handler;
}


/**
* @Name 		Audio_TaskDismiss
* @Author		KT
* @Description	
* @para 		
*
* @return		
*/
static void Audio_TaskDismiss(Audio_TaskHandler_S *audHandler){
	AudioHandler_S *handler = (AudioHandler_S *)audHandler;

	ERR_CHECK(handler != null, return);

	HAL_SaiDisconfig(handler->saiHandler);
	
	handler->inputStream = null;
	handler->outputStream = null;
	handler->enabled = false;
}

/**
* @Name 		Audio_StarReceive
* @Author		KT
* @Description	
* @para 		
*
* @return		
*/
static void Audio_StarReceive(Audio_TaskHandler_S *audHandler,DataStreamHandler_S *stream){
	AudioHandler_S *handler = (AudioHandler_S *)audHandler;
	
	ERR_CHECK(stream != null, return);
	ERR_CHECK(handler != null, return);

	handler->inputStream = stream;
	
#if defined(SAI_DMA_STATIC_MEM) && SAI_DMA_STATIC_MEM
	HAL_SaiStartReceive(handler->saiHandler,Audio_SaiRxCallback);
#else
	Sai.starReceive(handler->saiHandler,stream->data,stream->totalSize,Audio_SaiRxCallback);
#endif
}


/**
* @Name 		Audio_StarTransmit
* @Author		KT
* @Description	
* @para 		
*
* @return		
*/
static void Audio_StarTransmit(Audio_TaskHandler_S *audHandler,DataStreamHandler_S *stream){
	AudioHandler_S *handler = (AudioHandler_S *)audHandler;
	
	ERR_CHECK(stream != null, return);
	ERR_CHECK(handler != null, return);

	handler->outputStream = stream;
	
#if defined(SAI_DMA_STATIC_MEM) && SAI_DMA_STATIC_MEM
	HAL_SaiStartSend(handler->saiHandler,Audio_SaiTxCallback);
#else
	Sai.starSend(handler->saiHandler,stream->data,stream->totalSize,Audio_SaiTxCallback);
#endif
	
}

/**
* @Name 		Audio_StopReceive
* @Author		KT
* @Description	
* @para 		
*
* @return		
*/


static void Audio_StopReceive(Audio_TaskHandler_S *audHandler){
	AudioHandler_S *handler = (AudioHandler_S *)audHandler;
	
	ERR_CHECK(handler != null, return);
	HAL_SaiStopReceive(handler->saiHandler);
}


/**
* @Name 		Audio_StopTransmit
* @Author		KT
* @Description	
* @para 		
*
* @return		
*/
static void Audio_StopTransmit(Audio_TaskHandler_S *audHandler){
	AudioHandler_S *handler = (AudioHandler_S *)audHandler;
	
	ERR_CHECK(handler != null, return);

	HAL_SaiStopSend(handler->saiHandler);
}




/**
* @Name 		Audio_Init
* @Author		KT
* @Description	
* @para 		
*
* @return		
*/
static uint8_t saiBuffer[4100];

static void Audio_SaiRxCallback(HAL_SaiHandle_S * saiHandler,uint8_t *data,uint32_t dataLen,void *param){
	AudioHandler_S *handler = (AudioHandler_S *)param;
	DataStreamHandler_S *stream = handler->inputStream;
	uint32_t len,i;

#if defined(SAI_DMA_STATIC_MEM) && SAI_DMA_STATIC_MEM
	
	for(i = 0;i < (dataLen / 2);i+=2){
		saiBuffer[i] = data[i*2];
		saiBuffer[i+1] = data[i*2+1];
	}
	
	DataStream.write(stream,saiBuffer,(dataLen / 2));
#else
	stream->end = data + dataLen;
	stream->emptySize = stream->emptySize >= dataLen ? stream->emptySize - dataLen : 0;
	stream->filledSize = (stream->filledSize + dataLen) <= stream->totalSize ? stream->filledSize + dataLen : stream->totalSize;
#endif
	

	
	
}


/**
* @Name 		Audio_Init
* @Author		KT
* @Description	
* @para 		
*
* @return		
*/
static void Audio_SaiTxCallback(HAL_SaiHandle_S * saiHandler,uint8_t *data,uint32_t dataLen,void *param){
	AudioHandler_S *handler = (AudioHandler_S *)param;
	DataStreamHandler_S *stream = handler->outputStream;
	uint32_t len;
	
#if defined(SAI_DMA_STATIC_MEM) && SAI_DMA_STATIC_MEM

	len = DataStream.fillSize(stream);
	if(len == 0)
		return;
	
	len = (len < dataLen) ? len : dataLen;
	DataStream.read(stream,data,len);
//	debug("Sai tx data len = 0x%X \r\n",len);
#else
	stream->data = data;
	stream->emptySize = (stream->emptySize + dataLen) <= stream->emptySize ? stream->emptySize + dataLen : stream->totalSize;
	stream->filledSize = stream->filledSize >= dataLen ? stream->filledSize - dataLen : 0;
#endif

}


