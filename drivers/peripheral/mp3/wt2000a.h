#ifndef __WT2000A_H_
#define __WT2000A_H_

#include "drivers_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* 数据应答回调函数 */
typedef void(*Wt2000_AckCallback)(uint8_t data);


typedef enum{
	/* 播放 */
	kType_WtCmd_PlayFile = 0xA9,
	kType_WtCmd_Pause = 0xAA,
	kType_WtCmd_Stop = 0xAB,
	kType_WtCmd_Next = 0xAC,
	kType_WtCmd_Previous = 0xAD,
	
	/* 录音 */
	kType_WtCmd_RecStart = 0xD8,
	kType_WtCmd_RecStop = 0xD9,

	/* 查询 */
	kType_WtCmd_Volume = 0xC1,
	kType_WtCmd_State = 0xC2,
	kType_WtCmd_FileNum = 0xC5,
	kType_WtCmd_DirFileNum = 0xC6,
	kType_WtCmd_CurrPlayFile = 0xC9,
	kType_WtCmd_LinkSta = 0xCA,
	kType_WtCmd_Space = 0xCE,

}WtCmdType_EN;

typedef enum {
	kStatus_WtPlay_Playing = 1,
	kStatus_WtPlay_Stop = 2,
	kStatus_WtPlay_Pause = 3,
	kStatus_WtPlay_Recording = 4,
}WtPlaySta_EN;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void Wt2000_CfgReturnNecessary(void);
void Wt2000_CfgUsbDisk(void);
void Wt2000_CfgMp3Rate(void);
void Wt2000_CfgDefVolume(void);


void Wt2000_AckRecvEnable(bool enable);

void Wt2000_QueryState(WtCmdType_EN type);
void Wt2000_AudioRecord(const char *dir,  const char *file);
void Wt2000_RecordStop(void);
void Wt2000_AudioPlay(const char *dir, const char *file);
void Wt2000_AudioPlayPause(void);
void Wt2000_PlayNext(void);
void Wt2000_PlayPrevious(void);
void Wt2000_PlayStop(void);


status_t Wt2000_SetAckCallback(Wt2000_AckCallback callback);


#endif

