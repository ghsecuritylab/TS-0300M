#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "stdint.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
 
/*******************************************************************************
 ***                        全数字会议系统通讯协议                           ***
 *******************************************************************************/
/************ 广播ID ****************/
#define WHOLE_BROADCAST_ID							(0xFFF0)			//广播全体机型
#define UNIT_BROADCAST_ID							(0xFFF1)			//仅对单元机广播消息
#define EX_HOST_BROADCAST_ID						(0xFFF2)			//仅对扩展主机广播消息
#define TRANS_BROADCAST_ID							(0xFFF3)			//仅对议员机广播消息
#define MODE_BROADCAST_ID							(0xFFE1)			//广播当前主机模式
#define NUM_BROADCAST_ID							(0xFFE2)			//广播会场总数量、当前开话筒数量
#define APPLY_OPEN_MIC_ID							(0xFFC1)			//向主席机广播当前申请开话筒ID
#define REVOKE_APPLY_ID								(0xFFC2)			//向主席机广播当前撤销申请话筒ID

/* 结果消息(0x83)相关ID */
#define RESULT_MSG_ID(_id)							(0xFFD0 + _id)		 //结果消息ID
#define RES_SIGN_NUM								(0x01)				 //签到总人数
#define RES_OPT_NUM(n)								(0x01 + n)			 //第n项选项人数
 
/************ 类型(type) ************/
#define BASIC_MSG									(0x80)				//基本消息
#define POLLING_MSG									(0x81)				//轮询消息
#define STATE_MSG									(0x82)				//状态消息
#define RESULT_MSG									(0x83)				//结果消息
#define APPLY_MSG									(0x84)				//申请消息
#define EXTEND_MSG									(0x85)				//扩展统计消息
#define PC_MSG										(0x86)				//PC通讯消息
#define WIRED_UNIT_NUM								(0x87)				//有线单元数量
#define WIFI_UNIT_NUM								(0x88)				//无线单元数量
#define NAMEPLATE_PARA								(0x90)				//电子铭牌参数
#define CONFERENCE_MSG								(0x96)				//会议信息（会议内容、摘要等）
#define NAMEPLATE_COMP								(0x97)				//PC下发电子铭牌内容（公司名称）
#define NAMEPLATE_POS								(0x98)				//PC下发电子铭牌内容（职位）
#define NAMEPLATE_CONTENT							(0x99)				//PC下发电子铭牌内容（旧电子铭牌协议，用于兼容）
#define USER_LIST									(0x9A)				//用户列表（ID和参会人的对应列表）
#define CONSTANT_NOTIFY								(0x9B)				//PC下发的固定通知消息（有事找您，xxxx）
#define NAMEPLATE_NAME								(0x9C)				//PC下发电子铭牌内容（姓名）
#define NAMEPLATE_UPDATE							(0x9D)				//PC单播更新电子铭牌（旧电子铭牌协议，用于兼容）
#define HOST_REPLY_PC								(0x9E)				//主机回复PC发送成功

 
/************ 参数ph(para high) ************/
/* 前置字段 	BASIC_MSG */
#define CONFERENCE_MODE								(0x00)
#define SIGN_MODE									(0x01)
#define VOTE_MODE									(0x02)
#define EDIT_ID_MODE								(0x03)

/* 前置字段 	PC_MSG */
#define HEARTBEAT									(0x00)
#define CFG_UART_1									(0x01)
#define CFG_UART_2									(0x02)
#define CFG_UART_3									(0x03)
#define CFG_UART_4									(0x04)
#define CFG_UART_5									(0x05)
#define CFG_MAC										(0x06)
#define CFG_IP										(0x07)
#define CFG_MASK									(0x08)
#define CFG_GW										(0x09)
#define QUERY_HOST									(0x0F)
#define SCAN_ONLINE_UNIT							(0x30)
#define ONLINE_UNIT									(0x31)
#define QUERY_PRIOR_SIGN							(0x33)
#define QUERY_PRIOR_VOTE							(0x34)
#define QUERY_PRIOR_SCAN							(0x35)

/* 前置字段 	POLLING_MSG */
#define SIGN_POLLING								(0x06)
#define EDIT_ID_POLLING								(0x08)		

/************ 参数pl(para low) ************/
/* 前置字段 	BASIC_MSG  CONFERENCE_MODE */
#define START_CONFERENCE_MODE						(0x01)
#define ID_DUPICATE									(0x03)
#define RPS_OPEN_MIC								(0x05)
#define RPS_CLOSE_MIC								(0x06)
#define CHM_OPEN_MIC								(0x07)
#define CHM_CLOSE_MIC								(0x08)
#define CHM_PRIORITY								(0x0B)
#define MIC_WAIT									(0x0D)
#define MIC_DISWAIT									(0x0E)
#define QUERY_UNIT									(0x13)
#define AGREE_OPEN_MIC								(0x15)
#define RPS_REPLY_ONLINE							(0x16)
#define CHM_REPLY_ONLINE							(0x17)
#define MIC_CHANNEL_FULL							(0x25)
#define RPS_APPLY_ACCESS_SYS						(0x26)
#define CHM_APPLY_ACCESS_SYS						(0x27)
#define UNIT_ACCESS_SYS								(0x28)
#define UNIT_OFFLINE								(0x40)
#define DISAGREE_OPEN_MIC							(0x5C)

/* 前置字段 	BASIC_MSG  SIGN_MODE */
#define START_SIGN_MODE								(0x01)
#define UNIT_SIGN_IN								(0x05)
#define END_SIGN_MODE								(0x06)
#define SIGN_ENABLE									(0x08)
#define SIGN_DISABLE								(0x09)
#define SUPPLEMENT_SIGN								(0x0A)
#define UNIT_SUPPLEMENT_SIGN						(0x0B)
#define DEV_START_SIGN_MODE							(0x0E)
#define DEV_END_SIGN_MODE							(0x0F)
#define CONTROL_UNIT_SIGN							(0x12)

/* 前置字段 	BASIC_MSG  EDIT_ID_MODE */
#define START_EDIT_ID_MODE							(0x80)
#define UNIT_CONFIRM_ID								(0x86)

/* 前置字段 	POLLING_MSG  SIGN_POLLING */
#define HOST_SIGN_POLLIGN							(0x52)

/* 前置字段 	POLLING_MSG  EDIT_ID_POLLING */
#define REPEATED_ID									(0x60)
#define CURRENT_ID									(0x61)
#define CONFIRM_ID									(0x62)




/* 前置字段 	PC_MSG  SCAN_ONLINE_UNIT */
#define SCAN_UNIT_END								(0x01)


/*******************************************************************************
 ***                        WIFI单元通讯协议                           ***
 *******************************************************************************/





/******************************** 协议数据结构 ************************************/
/*  全数字会议系统通讯协议数据结构(基本结构) */
#pragma pack(1)	/* 单字节对齐 */
typedef struct {
	uint16_t id;
	uint8_t type;
	uint8_t ph;
	uint8_t pl;
	uint8_t ch; 
	uint16_t sec;
}ConfProtocol_S;
#pragma pack()

/*  WIFI单元通讯协议数据结构(基本结构) */
#pragma pack(1)	/* 单字节对齐 */
typedef struct {
	uint16_t id;
	uint8_t cmd;
	uint8_t ph;
	uint8_t pl;
}WifiUnitProtocol_S;
#pragma pack()


typedef struct {
	ConfProtocol_S *(*conference)(ConfProtocol_S *,uint16_t ,uint8_t ,uint8_t ,uint8_t ,uint8_t ,uint16_t );
	WifiUnitProtocol_S *(*wifiUnit)(WifiUnitProtocol_S *, uint16_t, uint8_t ,uint8_t ,uint8_t);
}Protocol_S;

extern Protocol_S Protocol;
#endif

