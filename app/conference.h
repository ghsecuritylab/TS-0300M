#ifndef __CONFERENCE_H__
#define __CONFERENCE_H__

/* 定义许可,只在本 .h文件内定义,文件末尾取消定义 */
#define LICENSE_ACCESS_UNIT_INFO 

#include "stdint.h"
#include "network.h"
#include "protocol.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
 /* 会议状态 */
typedef enum {
	mConference = 0, mEditID, mSign, mVote, mDevSign, mDevVote
}SysMode_EN;

/* 话筒模式 */
typedef enum {
	mFifo = 1, mNormal, mVoiceCtrl, mApply
}MicMode_EN;
 

/********************** 会议线程通知相关数据结构及定义 *****************************/  
 
 /* 外部线程（web,pc,unit,screen等） 通知会议线程
	关键词,前缀(NK_  ==  Notify Keywork)*/
#define NOTIFY_KEYWORD						uint8_t

#define NK_CONFERENCE_MSG					(0x01)
#define NK_UNITINFO_UPDATE					(0x02)
#define NK_UNIT_OFFLINE						(0x03)

/* 通知源(有线单元、WIFI单元、WEB控制(HTTP)、PC端口控制(TCP)、串口控制、屏幕控制) */
typedef enum {
	sWiredUnit 	= (1<<0), 
	sWifiUnit  	= (1<<1),
	sWeb 		= (1<<2), 
	sPC			= (1<<3), 
	sUartCtrl	= (1<<4), 
	sScreenCtrl = (1<<5),
}NotifySrc_EN;

/* 通知格式 */
typedef struct {
	/* 通知源 */
	NotifySrc_EN nSrc;
	
//	/* 通知关键字 */
//	NOTIFY_KEYWORD kWord;
	
	/* 会议通知传参变量 */
	union{
		ConfProtocol_S conference;
		WifiUnitProtocol_S wifi;
	}prot;

	uint16_t    exLen;
	uint8_t		exDataHead;
}Notify_S;

/********************** 会议线程执行操作相关数据结构及定义 *****************************/  
/* 执行操作目标对象(有线单元、WIFI单元、WEB控制、PC端口控制、串口控制、屏幕控制)
	通过 NotifySrc_EN 强转short型数据，通过位判断确定操作目标*/
#define EXE_DEST							uint16_t
#define ALL_DEST							(0xFFFF)
#define EX_CTRL_DEST						(sPC|sWeb|sUartCtrl)
#define ALL_UNIT							(sWifiUnit|sWiredUnit)


/********************** 单元设备相关数据结构及定义 *****************************/ 
/* 单元类型数量 */
#define UNIT_TYPE_NUM								(2)
 
/* 最大有线单元数 */
#define WIRED_UNIT_MAX_ONLINE_NUM					(4096)

/* 最大允许开话筒数（有线） */
#define WIRED_UNIT_MAX_ALLWO_OPEN					(8)

/* 最大WIFI单元数 */
#define WIFI_UNIT_MAX_ONLINE_NUM					(300)

/* 最大允许开话筒数（WIFI） */
#define WIFI_UNIT_MAX_ALLWO_OPEN					(6)

 /* 单元类型（有线单元、WIFI单元） */
 typedef enum{
	tWired = 0, tWifi = 1
 }UnitType_EN;
 
/* 单元属性（主席、单元、译员） */
typedef enum {
	aRepresentative, aChairman, aInterpreter
}UnitAttr_EN;

/* 单元话筒状态 */
typedef enum {
	sClose,sOpen,sApply,sWait
}UnitMicSta_EN;


/* 在线话筒数 */
typedef struct {
	/* 有线主席单元 */
	uint16_t wiredChm;
	/* 有线代表单元 */
	uint16_t wiredRps;
	/* WIFI主席单元 */
	uint16_t wifiChm;
	/* WIFI代表单元 */
	uint16_t wifiRps;
	/* 译员机 */
	uint16_t interpreter;
}UnitOnlineNum;

/**
* @Description	单元信息数据结构,需要定义宏“LICENSE_ACCESS_UNIT_INFO”
*
* @License 		LICENSE_ACCESS_UNIT_INFO
**/
#ifdef LICENSE_ACCESS_UNIT_INFO
#pragma pack(1)
typedef struct {

	/* 上线标志 */
	bool online;

	/* 签到标志 */
	bool sign;
	
	/* 轮询计数（得到应答会清空，
	   计数超过"POLLING_NO_REPLY_OFFLINE_COUNT"判断离线） */
	uint16_t pollCount;
	
	/* 单元类型（主席、代表、译员机） */
	UnitAttr_EN attr;
	
	/* 单元MAC */
	NETWORK_MAC mac;
	
	/* 单元话筒状态(开、关、申请、等待) */
	UnitMicSta_EN micSta;
	
	/* 打开话筒时音频通道（默认0） */
	uint8_t channel;
}UnitInfo_S;
#pragma pack()
#endif



 /* API struct */
typedef struct {
	void (*launch)(void);
	void (*notify)(Notify_S *);
	void (*getOnlineNum)(UnitOnlineNum *);
	SysMode_EN (*getSysMode)(void);
	uint16_t (*getCurrentEditId)(void);
#ifdef LICENSE_ACCESS_UNIT_INFO
	UnitInfo_S *(*wiredUnitInfo)(void);
#else
	void *priv;
#endif
	
}Conference_S;

/*******************************************************************************
 * API
 ******************************************************************************/
extern Conference_S Conference;



/* 取消定义许可 */
#undef LICENSE_ACCESS_UNIT_INFO
#endif
