#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "app_common.h"
#include "data_stream.h"
#include "hal_sai.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef void * Audio_TaskHandler_S;


/* API */
typedef struct{
	void (*init)(void);
	Audio_TaskHandler_S(*taskCreat)(HAL_SaiType_S type);
	void (*taskDismiss)(Audio_TaskHandler_S *audHandler);
	void (*starReceive)(Audio_TaskHandler_S *audHandler,DataStreamHandler_S *stream);
	void (*starTransmit)(Audio_TaskHandler_S *audHandler,DataStreamHandler_S *stream);
	void (*stopReceive)(Audio_TaskHandler_S *audHandler);
	void (*stopTransmit)(Audio_TaskHandler_S *audHandler);
} Audio_S;
/*******************************************************************************
 * API
 ******************************************************************************/
extern Audio_S Audio;
#endif


