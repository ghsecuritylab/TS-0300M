#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "stdint.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef enum {
	kStatus_Aud_Idle = 0,
	kStatus_Aud_UsbBroken,
	kStatus_Aud_UsbTimeout,
	kStatus_Aud_Recording,
	kStatus_Aud_RecStoped,
	kStatus_Aud_Playing,
	kStatus_Aud_Pause,
	kStatus_Aud_PlayStoped,
	kStatus_Aud_StarRecErr,
	kStatus_Aud_StarPlayErr,
}AudStaType_EN;

typedef struct {
	AudStaType_EN state;
	uint32_t runTime;
	uint8_t playIndex;
	uint8_t recFile[25];
}AudState_S;

/* Â¼Òô/²¥·Å×´Ì¬¼àÌýº¯Êý */
typedef void(*Audio_StaListener)(AudState_S *state);


/* API */
typedef struct
{
	void (*launch)(void);
	void (*playPause)(void);
	void (*next)(void);
	void (*previous)(void);
	void (*record)(const char *fileName);
	void (*stopRec)(void);
	void (*stopPlay)(void);
	void (*setListener)(Audio_StaListener listener);
} Audio_S;
/*******************************************************************************
 * API
 ******************************************************************************/
extern Audio_S Audio;

#endif

