/**
 *
 *	@name				conference.c
 *	@author 			KT
 *	@date 				2019/07/26
 *	@brief
 *  @include			conference.h
 *
 *  @API
 *
 *  @description
 *
 **/
/*******************************************************************************
* permission
******************************************************************************/
#define LICENSE_ACCESS_UNIT_INFO

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "stdarg.h"
/* OS */
#include "FreeRTOS.h"
#include "semphr.h"
#include "timers.h"

/* API */
#include "app_common.h"
#include "data_queue.h"
#include "ram.h"

/* APP */
#include "conference.h"
#include "wired_unit.h"
#include "wifi_unit.h"
#include "external_ctrl.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* 任务堆栈大小及优先级 */
#define CONFERENCE_TASK_STACK_SIZE						(2048)
#define CONFERENCE_TASK_PRIORITY						(17)

#define NOTICE_QUEUE_LENGTH								(100)
#define NOTICE_QUEUE_SIZE								(sizeof(void *))

/**************************************** 会议执行操作 ******************************************************/

#define EXCUTE(_prot)									do{_prot}while(0)

#define CONF_PROT(_dest,_id,_type,_ph,_pl,_ch,_sec,_exlen,_exdata) 	\
		    if((_dest & sPC) || (_dest & sWeb) || (_dest & sUartCtrl)) 	\
				ExternalCtrl.transWithExData(_dest,Protocol.conference(&confProt,_id,_type,_ph,_pl,_ch,_sec),_exlen,(uint8_t *)_exdata);	\
		    if(_dest & sWiredUnit)	\
		        WiredUnit.transWithExData(Protocol.conference(&confProt,_id,_type,_ph,_pl,_ch,_sec),_exlen,(uint8_t *)_exdata);		\

#define WIFI_PROT(_dest,_id,_type,_ph,_pl,_exlen,_exdata)	\
			if(_dest & sWifiUnit)	\
				WifiUnit.transWithExData(Protocol.wifiUnit(&wifiProt,_id,_type,_ph,_pl),_exlen,(uint8_t *)_exdata);	\


#define EXE_CONFERENCE_MODE()							EXCUTE(	CONF_PROT(EX_CTRL_DEST|sWiredUnit,WHOLE_BROADCAST_ID,BASIC_MSG,CONFERENCE_MODE,START_CONFERENCE_MODE,null,null,null,null) \
																WIFI_PROT(sWifiUnit,null,null,null,null,null,null))
																

																
#define EXE_EDIT_ID_MODE()								EXCUTE(	CONF_PROT(EX_CTRL_DEST|sWiredUnit,WHOLE_BROADCAST_ID,BASIC_MSG,EDIT_ID_MODE,START_EDIT_ID_MODE,null,null,null,null) \
																WIFI_PROT(sWifiUnit,null,null,null,null,null,null))

#define EXE_BROADCAST_MODE_NUM(_mode,_num)				EXCUTE(	CONF_PROT(EX_CTRL_DEST|sWiredUnit,MODE_BROADCAST_ID,STATE_MSG,_mode,_num,null,null,null,null) \
																WIFI_PROT(sWifiUnit,null,null,null,null,null,null))
																
#define EXE_RESPOND_MODE_NUM(_dest,_mode,_num)			EXCUTE(	CONF_PROT(_dest,MODE_BROADCAST_ID,STATE_MSG,_mode,_num,null,null,null,null))

/* 开关话筒相关执行命令 */
#define EXE_RPS_OPEN_MIC(_id,_ch)						EXCUTE(	CONF_PROT(EX_CTRL_DEST|sWiredUnit,_id,BASIC_MSG,CONFERENCE_MODE,RPS_OPEN_MIC,_ch,null,null,null))
#define EXE_RPS_CLOSE_MIC(_id)							EXCUTE(	CONF_PROT(EX_CTRL_DEST|sWiredUnit,_id,BASIC_MSG,CONFERENCE_MODE,RPS_CLOSE_MIC,null,null,null,null))
#define EXE_CHM_OPEN_MIC(_id,_ch)						EXCUTE(	CONF_PROT(EX_CTRL_DEST|sWiredUnit,_id,BASIC_MSG,CONFERENCE_MODE,CHM_OPEN_MIC,_ch,null,null,null))
#define EXE_CHM_CLOSE_MIC(_id)							EXCUTE(	CONF_PROT(EX_CTRL_DEST|sWiredUnit,_id,BASIC_MSG,CONFERENCE_MODE,CHM_CLOSE_MIC,null,null,null,null))
#define EXE_MIC_WAIT(_id)								EXCUTE(	CONF_PROT(EX_CTRL_DEST|sWiredUnit,_id,BASIC_MSG,CONFERENCE_MODE,MIC_WAIT,null,null,null,null))
#define EXE_MIC_DISWAIT(_id)							EXCUTE(	CONF_PROT(EX_CTRL_DEST|sWiredUnit,_id,BASIC_MSG,CONFERENCE_MODE,MIC_DISWAIT,null,null,null,null))
#define EXE_MIC_FULL(_dest,_id)							EXCUTE(	CONF_PROT(_dest,_id,BASIC_MSG,CONFERENCE_MODE,MIC_CHANNEL_FULL,null,null,null,null))
#define EXE_APPLY_OPEN_MIC(_id)							EXCUTE(	CONF_PROT(EX_CTRL_DEST|sWiredUnit,APPLY_OPEN_MIC_ID,APPLY_MSG,(_id >> 8),(_id && 0xFF),null,null,null,null))
#define EXE_REVOKE_APPLY(_id)							EXCUTE(	CONF_PROT(EX_CTRL_DEST|sWiredUnit,REVOKE_APPLY_ID,APPLY_MSG,(_id >> 8),(_id && 0xFF),null,null,null,null))


#define EXE_REPORT_ONLINE_UNIT(_dest,_id,_attr)			EXCUTE(	CONF_PROT(_dest,_id,PC_MSG,ONLINE_UNIT,_attr,null,null,null,null))
#define EXE_SCAN_UNIT_END(_dest,_type,_num)				EXCUTE(	CONF_PROT(_dest,WHOLE_BROADCAST_ID,PC_MSG,SCAN_ONLINE_UNIT,SCAN_UNIT_END,_type,_num,null,null))

/* 签到相关执行命令 */
#define EXE_SIGN_MODE()									EXCUTE(	CONF_PROT(EX_CTRL_DEST|sWiredUnit,WHOLE_BROADCAST_ID,BASIC_MSG,SIGN_MODE,START_SIGN_MODE,null,null,null,null) \
																WIFI_PROT(sWifiUnit,null,null,null,null,null,null))
#define EXE_END_SIGN_MODE()								EXCUTE(	CONF_PROT(sWiredUnit,WHOLE_BROADCAST_ID,BASIC_MSG,SIGN_MODE,END_SIGN_MODE,null,null,null,null))
#define EXE_SIGNED_NUM(_total,_num)						EXCUTE(	CONF_PROT(sWiredUnit,RESULT_MSG_ID(RES_SIGN_NUM),RESULT_MSG,(_total >> 8),(_total && 0xFF),null,_num,null,null)	\
																WIFI_PROT(sWifiUnit,null,null,null,null,null,null))
#define EXE_UNIT_SIGNED(_id)							EXCUTE(	CONF_PROT(EX_CTRL_DEST,_id,BASIC_MSG,SIGN_MODE,UNIT_SIGN_IN,null,null,null,null))	
#define EXE_CONTROL_UNIT_SIGN(_id)						EXCUTE(	CONF_PROT(sWiredUnit,_id,BASIC_MSG,SIGN_MODE,CONTROL_UNIT_SIGN,null,null,null,null))	
#define EXE_SUPPLEMENT_SIGN(_id)						EXCUTE(	CONF_PROT(sWiredUnit,_id,BASIC_MSG,SIGN_MODE,SUPPLEMENT_SIGN,null,null,null,null))	
#define EXE_UNIT_SUPPLEMENT_SIGN(_id)					EXCUTE(	CONF_PROT(EX_CTRL_DEST,_id,BASIC_MSG,SIGN_MODE,UNIT_SUPPLEMENT_SIGN,null,null,null,null))	


#define EXE_CONFIRM_ID(_id,_mac)						EXCUTE(	CONF_PROT(sWiredUnit,WHOLE_BROADCAST_ID,POLLING_MSG,EDIT_ID_POLLING,CONFIRM_ID,null,_id,sizeof(Network_Mac_S),_mac))
#define EXE_CURRENT_ID(_id)								EXCUTE(	CONF_PROT(sWiredUnit,WHOLE_BROADCAST_ID,POLLING_MSG,EDIT_ID_POLLING,CURRENT_ID,null,_id,null,null))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* API */
static void Conference_Launch(void);
static void Conference_Notify(Notify_S *notify);
static void Conference_UnitOnlineNum(UnitOnlineNum *onlineNum);
static SysMode_EN Conference_GetSysMode(void);
static uint16_t Conference_GetCurrentEditedID(void);
static UnitInfo_S *Conference_WiredUnitInfo(void);


/* 内部调用 */
static void Conference_NoticeProcessTask(void *pvParameters);
static void Conference_MessageProcess(Notify_S *notify);

static void Conference_ResetAudioChannel(UnitType_EN type);
static uint8_t Conference_GetAudioChannel(UnitType_EN type);
static void Conference_GiveAudioChannel(UnitType_EN type,uint8_t ch);

static void Conference_WiredOpenMic(uint16_t id, uint8_t type);
static void Conference_WiredCloseMic(uint16_t id, uint8_t type);
static void Conference_WiredCloseAllMic(UnitAttr_EN attr);
static void Conference_WiredOutlineAllUnit(void);
static void Conference_WiredClearApply(void);
static void Conference_ChangeSysMode(SysMode_EN mode);
static void Conference_ChairmanPriority(uint16_t id);

static void Conference_OpenMicListDebug(void);

#ifdef	CONFIRM_UNIT_NUM
static void Conference_ConfirmUnitNum(TimerHandle_t xTimer);
#endif
/*******************************************************************************
 * Variables
 ******************************************************************************/
/* 会议通知队列 */
static QueueHandle_t noticeQueue;

/* 会议系统通讯协议 */
static ConfProtocol_S confProt;

/* WIFI单元通讯协议 */
static WifiUnitProtocol_S wifiProt;

/* 系统模式 */
static SysMode_EN sysMode;

/* 话筒模式 */
static MicMode_EN	micMode;

/* 当前编辑ID(编ID) */
static uint16_t currentEditID;

/* 签到总人数 */
static uint16_t totalSignNum;
/* 当前签到人数 */
static uint16_t currentSignNum;

/* 单元信息保存堆栈
总大小为最大单元数+1 因为单元没有0号,方便索引 */
static struct {
    UnitInfo_S wired[WIRED_UNIT_MAX_ONLINE_NUM + 1];
    UnitInfo_S wifi[WIFI_UNIT_MAX_ONLINE_NUM + 1];
} UnitInfo __attribute__((section("OcramHeap")));

/* 在线话筒数 */
static UnitOnlineNum OnlineNum;

/* 允许开话筒数 - 有线单元 */
static uint8_t	wiredAllowOpen;

/* 可等待话筒数 - 有线单元
(可等待数量和允许开话筒数量相等) */
static uint8_t	wiredAllowWait;

/* 主席机队列 */
static DataQueueHandler_S chmMicQueue;

/* 代表机队列 */
static DataQueueHandler_S rpsMicQueue;

/* 等待(申请)队列 */
static DataQueueHandler_S waitQueue;

/* 音频通道队列 */
static DataQueueHandler_S channelQueue;

#ifdef	CONFIRM_UNIT_NUM
/* 确认话筒数量定时器 */
static TimerHandle_t cfmUnitNumTimer;
#endif



/* API 函数指针 */
Conference_S Conference = {
    .launch = Conference_Launch,
    .notify = Conference_Notify,
    .getOnlineNum = Conference_UnitOnlineNum,
    .getSysMode = Conference_GetSysMode,
    .getCurrentEditId = Conference_GetCurrentEditedID,

    .wiredUnitInfo = Conference_WiredUnitInfo,
};
/*******************************************************************************
 * Code
 ******************************************************************************/

/**
* @Name  		Conference_Launch
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void Conference_Launch(void)
{
    noticeQueue = xQueueCreate(NOTICE_QUEUE_LENGTH,NOTICE_QUEUE_SIZE);

    if (xTaskCreate(Conference_NoticeProcessTask, "NoticeProcessTask", CONFERENCE_TASK_STACK_SIZE, null, CONFERENCE_TASK_PRIORITY, null) != pdPASS) {
        debug("create host task error\r\n");
    }

    memset(&UnitInfo,0,sizeof(UnitInfo));

    micMode = mFifo;
    wiredAllowOpen = WIRED_UNIT_MAX_ALLWO_OPEN;
    wiredAllowWait = WIRED_UNIT_MAX_ALLWO_OPEN;

    chmMicQueue = DataQueue.creat(WIRED_UNIT_MAX_ALLWO_OPEN,sizeof(uint16_t));
    rpsMicQueue = DataQueue.creat(WIRED_UNIT_MAX_ALLWO_OPEN,sizeof(uint16_t));
    waitQueue = DataQueue.creat(WIRED_UNIT_MAX_ALLWO_OPEN,sizeof(uint16_t));
    channelQueue = DataQueue.creat(WIRED_UNIT_MAX_ALLWO_OPEN,sizeof(uint8_t));

    Conference_ResetAudioChannel(tWired);
}


/**
* @Name  		Conference_Notify
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void Conference_Notify(Notify_S *notify)
{
    if(notify == null)
        return;

    xQueueSend(noticeQueue,&notify,0);
}

/**
* @Name  		Conference_NoticeProcessTask
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void Conference_NoticeProcessTask(void *pvParameters)
{
    Notify_S *notify;


    debug("Conference notice process task launch!\r\n");
#ifdef	CONFIRM_UNIT_NUM
	/* 初始化确认话筒数量定时器 */
    cfmUnitNumTimer = xTimerCreate("ConfirmUnitNum",3000,pdFALSE,null,Conference_ConfirmUnitNum);
#endif
    while(1) {
        xQueueReceive(noticeQueue, &notify, MAX_NUM);

		/* 判断通知来源 */
		if(notify->nSrc & (EX_CTRL_DEST | sWiredUnit)){
			/* 通知来源为外部控制及有线单元 */	
			Conference_MessageProcess(notify);
		}
        FREE(notify);
    }
}

#ifdef	CONFIRM_UNIT_NUM
/**
* @Name  		Conference_ConfirmUnitNum
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void Conference_ConfirmUnitNum(TimerHandle_t xTimer){
	uint16_t chmNum = 0, rpsNum = 0, i;

	for(i = 0;i < WIRED_UNIT_MAX_ONLINE_NUM;i++){
		if(UnitInfo.wired[i].online){
			if(UnitInfo.wired[i].attr == aChairman)	chmNum++;
			else if(UnitInfo.wired[i].attr == aRepresentative) rpsNum++;
		}
	}

	if(OnlineNum.wiredChm != chmNum || OnlineNum.wiredRps != rpsNum){
		OnlineNum.wiredChm = chmNum;
		OnlineNum.wiredRps = rpsNum;
		debug("Online num is update: wiredUnit(CHM) = %d , wiredUnit(RPS) = %d\r\n",OnlineNum.wiredChm,OnlineNum.wiredRps);
	}
}
#endif

/**
* @Name  		Conference_MessageProcess
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void Conference_MessageProcess(Notify_S *notify)
{
    uint16_t id;
    uint8_t type, *para;

    ERR_CHECK(notify != null, return);

    id = notify->prot.conference.id;
    type = notify->prot.conference.type;
    para = &notify->prot.conference.ph;

#if 1
    debug("Conference Msg: id = %X, type = %X,para{ %X , %X , %X , %X , %X }",id,type,para[0],para[1],para[2],para[3],para[4]);
	if(notify->exLen){
		uint8_t i;
	
		debug(" exData{ ");
		for(i=0;i<notify->exLen;i++)
			debug(" %X ,",(&notify->exDataHead)[i]);
		debug(" } ");
	}
	debug("\r\n");
#endif

    switch(type) {
    /* 基本消息 0x80 */
    case BASIC_MSG: {
        uint8_t mode = para[0], cmd = para[1];

        switch(mode) {
        /* 会议模式 0x00 */
        case CONFERENCE_MODE: {
            switch(cmd) {
            case START_CONFERENCE_MODE:{
				Conference_ChangeSysMode(mConference);
			}break;	
            /*主席申请开话筒*/
            case CHM_OPEN_MIC:
            /*代表申请开话筒*/
            case RPS_OPEN_MIC:
            /* 同意开话筒 */
            case AGREE_OPEN_MIC:
            /* 不同意开话筒 */
            case DISAGREE_OPEN_MIC: {
                Conference_WiredOpenMic(id,cmd);
            }
            break;

            /*主席申请关话筒*/
            case CHM_CLOSE_MIC:
            /*代表申请关话筒*/
            case RPS_CLOSE_MIC: {
                Conference_WiredCloseMic(id,cmd);
            }
            break;

            /* 主席优先权 */
            case CHM_PRIORITY: {
                Conference_ChairmanPriority(id);
            }
            break;

            /* 话筒上线 */
            case UNIT_ACCESS_SYS: {
                if(UnitInfo.wired[id].attr == aChairman)
                    OnlineNum.wiredChm++;
                else if(UnitInfo.wired[id].attr == aRepresentative)
                    OnlineNum.wiredRps++;
#ifdef	CONFIRM_UNIT_NUM
				/* 打开定时器，3S后数一下话筒列表数量对不对，防止话筒重复上线 */
				xTimerStart(cfmUnitNumTimer,0);
#endif
				debug("WiredUnit(%s) id = %d online ( Chm num = %d , Rps num = %d )\r\n",UnitInfo.wired[id].attr == aChairman ? "CHM":"RPS",id,OnlineNum.wiredChm,OnlineNum.wiredRps);
            }
            break;

            /*话筒掉线*/
            case UNIT_OFFLINE: {
                if(UnitInfo.wired[id].attr == aChairman) {
                    Conference_WiredCloseMic(id,CHM_CLOSE_MIC);
                    OnlineNum.wiredChm--;
                } else if(UnitInfo.wired[id].attr == aRepresentative) {
                    Conference_WiredCloseMic(id,RPS_CLOSE_MIC);
                    OnlineNum.wiredRps--;
                }
#ifdef	CONFIRM_UNIT_NUM
				xTimerStart(cfmUnitNumTimer,0);
#endif
				debug("WiredUnit(%s) id = %d offline ( Chm num = %d , Rps num = %d )\r\n",UnitInfo.wired[id].attr == aChairman ? "CHM":"RPS",id,OnlineNum.wiredChm,OnlineNum.wiredRps);
            }
            break;
            }
        }
        break;
		
		/* 签到模式 0x01 */
		case SIGN_MODE:{
			uint16_t num;			
		
			switch(cmd){
				/* 进入签到模式 */
				case START_SIGN_MODE:{
					totalSignNum = (para[3] << 8) & para[4];
					currentSignNum = 0;
					EXE_SIGNED_NUM(totalSignNum, currentSignNum);
					Conference_ChangeSysMode(mSign);
				}
				break;
				/* 单元签到 */
				case UNIT_SIGN_IN:{
					/* 单元未签到 */
					if(!UnitInfo.wired[id].sign){
						UnitInfo.wired[id].sign = true;
						currentSignNum++;
						EXE_SIGNED_NUM(totalSignNum, currentSignNum);
						EXE_UNIT_SIGNED(id);
						
						/* 如果单元签到来自外部控制，则为控制签到 */
						if(notify->nSrc & (sPC | sWeb | sUartCtrl))
							EXE_CONTROL_UNIT_SIGN(id);
					}
				}
				break;
				/* 结束签到 */
				case END_SIGN_MODE:{
					EXE_END_SIGN_MODE();
					Conference_ChangeSysMode(mConference);
				}
				break;

				/* 补充签到 */
				case SUPPLEMENT_SIGN:{
					EXE_SUPPLEMENT_SIGN(id);
				}
				break;

				/* 单元应答补充签到 */
				case UNIT_SUPPLEMENT_SIGN:{
					if(!UnitInfo.wired[id].sign){
						UnitInfo.wired[id].sign = true;
						currentSignNum++;
						EXE_UNIT_SUPPLEMENT_SIGN(id);
					}
					
				}break;
			}
		}break;

        /* 编ID模式 0x03 */
        case EDIT_ID_MODE: {
            switch(cmd) {
			/* 开始编ID */
            case START_EDIT_ID_MODE: {
                currentEditID = (notify->prot.conference.sec == 0 ? 1 : notify->prot.conference.sec);
				Conference_ChangeSysMode(mEditID);
            }
            break;
			/* 单元确认当前ID为本机ID */
            case UNIT_CONFIRM_ID: {
                Network_Mac_S *devMac = (Network_Mac_S *)&notify->exDataHead;

                debug("confirm id = %d , dev mac = %X:%X:%X:%X:%X:%X \r\n",id,devMac->mac0,devMac->mac1,devMac->mac2,devMac->mac3,devMac->mac4,devMac->mac5);
                if(id == currentEditID) {
					/* 回复单元确定 */
                    EXE_CONFIRM_ID(id,devMac);
                    currentEditID = (currentEditID + 1) > WIRED_UNIT_MAX_ONLINE_NUM ? 1 : currentEditID + 1;
                    EXE_CURRENT_ID(currentEditID);
                }
            }
            break;
            }
        }
        break;
        }
    }
    break;
    /* 状态消息 0x82*/
    case STATE_MSG: {
        switch(id) {
        case MODE_BROADCAST_ID: {
            uint8_t mode = para[0], num = para[1];

            if(mode >= mFifo && mode <= mApply)
                micMode = (MicMode_EN)mode;
            if(num >= 1 && num <= WIRED_UNIT_MAX_ALLWO_OPEN) {
                wiredAllowOpen = num;
                wiredAllowWait = num;
            }
            /* 关闭所有单元 */
            Conference_WiredCloseAllMic(aChairman);
            Conference_WiredCloseAllMic(aRepresentative);

            /* 清除申请队列 */
            Conference_WiredClearApply();

            /* 清除等待队列 */
            DataQueue.empty(waitQueue);

            /* 广播模式及数量 */
            EXE_BROADCAST_MODE_NUM(micMode,wiredAllowOpen);
        }
        break;
        }
    }
    break;
    /* PC通讯消息 0x86*/
    case PC_MSG: {
        uint8_t cmd = para[0];

        switch(cmd) {
        /* 0x01 ~ 0x05 */
        case CFG_UART_1:
        case CFG_UART_2:
        case CFG_UART_3:
        case CFG_UART_4:
        case CFG_UART_5: {

        } break;
        /* 0x06 */
        case CFG_MAC:
            break;
        /* 0x07 */
        case CFG_IP:
            break;
        /* 0x08 */
        case CFG_MASK:
            break;
        /* 0x09 */
        case CFG_GW:
            break;
        /* 0x0F */
        case QUERY_HOST: {
            EXE_RESPOND_MODE_NUM(notify->nSrc,micMode,wiredAllowOpen);
        }
        break;
        case SCAN_ONLINE_UNIT: {
            uint16_t i;

            for(i = 1; i <= WIRED_UNIT_MAX_ONLINE_NUM; i++) {
                if(UnitInfo.wired[i].online) {
                    EXE_REPORT_ONLINE_UNIT(notify->nSrc,i,UnitInfo.wired[i].attr);
                }
            }
            EXE_SCAN_UNIT_END(notify->nSrc,tWired,(OnlineNum.wiredChm+OnlineNum.wiredRps));
        }
        break;
        }
    }
    break;
    }
}


/**
* @Name  		Conference_WiredOpenMic
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void Conference_WiredOpenMic(uint16_t id, uint8_t para)
{
    uint8_t channel, chmMicNum, rpsMicNum, waitNum, index;

    ERR_CHECK(id > 0 && id <= WIRED_UNIT_MAX_ONLINE_NUM,return);
    ERR_CHECK(UnitInfo.wired[id].online == true,return);
    ERR_CHECK(!(para == CHM_OPEN_MIC && UnitInfo.wired[id].attr != aChairman),return);
    ERR_CHECK(!(para == RPS_OPEN_MIC && UnitInfo.wired[id].attr != aRepresentative),return);

    /* 获取队列中当前打开话筒数量 */
    chmMicNum = DataQueue.getSize(chmMicQueue);
    rpsMicNum = DataQueue.getSize(rpsMicQueue);
    waitNum = DataQueue.getSize(waitQueue);

    switch(para) {
    /* 主席申请开话筒 */
    case CHM_OPEN_MIC: {
        switch(micMode) {
        /*** 先进先出模式 ***/
        case mFifo:
        /*** 正常模式 ***/
        case mNormal:
        /*** 声控模式 ***/
        case mVoiceCtrl:
        /*** 申请模式 ***/
        case mApply: {
            /* 查找话筒队列是否已经存在对应ID的话筒 */
            if(DataQueue.search(chmMicQueue,&id)) {
                channel = UnitInfo.wired[id].channel;
                EXE_CHM_OPEN_MIC(id,channel);
                break;
            }

            /* 主席+代表开话筒数量未超过允许开话筒数 */
            if(chmMicNum + rpsMicNum < wiredAllowOpen) {
                DataQueue.enter(chmMicQueue,&id);
                channel = Conference_GetAudioChannel(tWired);
                UnitInfo.wired[id].channel = channel;
                EXE_CHM_OPEN_MIC(id,channel);
            }
            /* 主席+代表开话筒数量等于允许开话筒数 */
            else {
                if(rpsMicNum > 0) {
                    uint16_t closeId;

                    /* 队列取出代表单元并关闭 */
                    DataQueue.exit(rpsMicQueue,&closeId);
                    channel = UnitInfo.wired[closeId].channel;
                    UnitInfo.wired[closeId].channel = null;
                    EXE_RPS_CLOSE_MIC(closeId);

                    /* 打开主席 */
                    UnitInfo.wired[id].channel = channel;
                    DataQueue.enter(chmMicQueue,&id);
                    EXE_CHM_OPEN_MIC(id,channel);
                } else {
                    /* 话筒已满 */
                    EXE_MIC_FULL(sPC|sWiredUnit,id);
                }
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    /* 代表申请开话筒 */
    case RPS_OPEN_MIC: {
        switch(micMode) {
        /*** 先进先出模式 ***/
        case mFifo: {
            /* 查找话筒队列是否已经存在对应ID的话筒 */
            if(DataQueue.search(rpsMicQueue,&id)) {
                channel = UnitInfo.wired[id].channel;
                EXE_RPS_OPEN_MIC(id,channel);
                break;
            }

            /* 主席+代表开话筒数量未超过允许开话筒数 */
            if(chmMicNum + rpsMicNum < wiredAllowOpen) {
                channel = Conference_GetAudioChannel(tWired);
                UnitInfo.wired[id].channel = channel;
                DataQueue.enter(rpsMicQueue,&id);
                EXE_RPS_OPEN_MIC(id,channel);
            }
            /* 主席+代表开话筒数量等于允许开话筒数 */
            else {
                if(rpsMicNum > 0) {
                    uint16_t closeId;

                    /* 队列取出代表单元并关闭 */
                    DataQueue.exit(rpsMicQueue,&closeId);
                    channel = UnitInfo.wired[closeId].channel;
                    UnitInfo.wired[closeId].channel = null;
                    EXE_RPS_CLOSE_MIC(closeId);
                    /* 打开代表 */
                    UnitInfo.wired[id].channel = channel;
                    DataQueue.enter(rpsMicQueue,&id);
                    EXE_RPS_OPEN_MIC(id,channel);
                } else {
                    /* 话筒已满 */
                    EXE_MIC_FULL(id,sPC | sWiredUnit);
                }
            }
        }
        break;
        /*** 正常模式 ***/
        case mNormal:
        /*** 声控模式 ***/
        case mVoiceCtrl: {
            /* 查找话筒队列是否已经存在对应ID的话筒 */
            if(DataQueue.search(rpsMicQueue,&id)) {
                /* 重新发送打开话筒指令，不需要操作队列 */
                channel = UnitInfo.wired[id].channel;
                EXE_RPS_OPEN_MIC(id,channel);
                break;
            }

            /* 查找等待队列是否存在对应ID话筒 */
            if(waitNum > 0 ) {
                /* 取消该话筒等待 */
                index = DataQueue.search(waitQueue,&id);
                if(index != 0) {
                    DataQueue.deleted(waitQueue,index);
                    EXE_MIC_DISWAIT(id);
                }
                break;
            }

            /* 主席+代表开话筒数量未超过允许开话筒数 */
            if(chmMicNum + rpsMicNum < wiredAllowOpen) {
                channel = Conference_GetAudioChannel(tWired);
                UnitInfo.wired[id].channel = channel;
                DataQueue.enter(rpsMicQueue,&id);
                EXE_RPS_OPEN_MIC(id,channel);
            }
            /* 主席+代表开话筒数量等于允许开话筒数 */
            else {
                /* 等待数量未满 */
                if(waitNum < wiredAllowWait) {
                    /* 进入等待队列 */
                    DataQueue.enter(waitQueue,&id);
                    EXE_MIC_WAIT(id);
                } else {
                    /* 话筒已满 */
                    EXE_MIC_FULL(id,sPC | sWiredUnit);
                }
            }
        }
        /*** 申请模式 ***/
        case mApply: {
            /* 查找话筒队列是否已经存在对应ID的话筒 */
            if(DataQueue.search(rpsMicQueue,&id)) {
                channel = UnitInfo.wired[id].channel;
                EXE_RPS_OPEN_MIC(id,channel);
                break;
            }

            /* 查找等待队列是否存在对应ID话筒 */
            if(waitNum > 0 ) {
                /* 取消该话筒等待 */
                index = DataQueue.search(waitQueue,&id);
                if(index != 0) {
                    DataQueue.deleted(waitQueue,index);
                    EXE_MIC_DISWAIT(id);
                    EXE_REVOKE_APPLY(id);
                }
                break;
            }

            /* 主席+代表开话筒数量未超过允许开话筒数 */
            if(chmMicNum + rpsMicNum < wiredAllowOpen) {
                /* 进入等待队列 */
                DataQueue.enter(waitQueue,&id);
                EXE_MIC_WAIT(id);
                EXE_APPLY_OPEN_MIC(id);
            }
            /* 主席+代表开话筒数量等于允许开话筒数 */
            else {
                /* 话筒已满 */
                EXE_MIC_FULL(id,sPC | sWiredUnit);
            }
        }
        break;
        default:
            break;
        }
    }
    break;

    /* 同意开话筒 */
    case AGREE_OPEN_MIC: {
        if(chmMicNum + rpsMicNum < wiredAllowOpen && waitNum > 0) {
            /* 打开话筒，并删除等待队列中对应ID的话筒 */
            index = DataQueue.search(waitQueue,&id);
            if(index != 0) {
                DataQueue.deleted(waitQueue,index);

                DataQueue.enter(rpsMicQueue,&id);
                channel = Conference_GetAudioChannel(tWired);
                UnitInfo.wired[id].channel = channel;
                EXE_RPS_OPEN_MIC(id,channel);
            }
        }
    }
    break;
    /* 不同意开话筒 */
    case DISAGREE_OPEN_MIC: {
        /* 查找等待队列是否存在对应ID话筒 */
        if(waitNum > 0 ) {
            /* 取消该话筒等待 */
            index = DataQueue.search(waitQueue,&id);
            if(index != 0) {
                DataQueue.deleted(waitQueue,index);
                EXE_MIC_DISWAIT(id);
                EXE_REVOKE_APPLY(id);
            }
            break;
        }
    }
    break;
    }

#if 0
    switch(micMode) {
    /*** 先进先出模式 ***/
    case mFifo: {
        switch(para) {
        /* 主席单元 */
        case CHM_OPEN_MIC: {
            /* 查找话筒队列是否已经存在对应ID的话筒 */
            if(DataQueue.search(chmMicQueue,&id)) {
                channel = UnitInfo.wired[id].channel;
                EXE_CHM_OPEN_MIC(id,channel);
                break;
            }

            /* 主席+代表开话筒数量未超过允许开话筒数 */
            if(chmMicNum + rpsMicNum < wiredAllowOpen) {
                DataQueue.enter(chmMicQueue,&id);
                channel = Conference_GetAudioChannel(tWired);
                UnitInfo.wired[id].channel = channel;
                EXE_CHM_OPEN_MIC(id,channel);
            }
            /* 主席+代表开话筒数量等于允许开话筒数 */
            else {
                if(rpsMicNum > 0) {
                    uint16_t closeId;

                    /* 队列取出代表单元并关闭 */
                    DataQueue.exit(rpsMicQueue,&closeId);
                    channel = UnitInfo.wired[closeId].channel;
                    EXE_RPS_CLOSE_MIC(closeId);

                    /* 打开主席 */
                    DataQueue.enter(chmMicQueue,&id);
                    EXE_CHM_OPEN_MIC(id,channel);
                } else {
                    /* 话筒已满 */
                    EXE_MIC_FULL(sPC|sWiredUnit,id);
                }
            }
        }
        break;
        /* 代表单元 */
        case RPS_OPEN_MIC: {
            /* 查找话筒队列是否已经存在对应ID的话筒 */
            if(DataQueue.search(rpsMicQueue,&id)) {
                channel = UnitInfo.wired[id].channel;
                EXE_RPS_OPEN_MIC(id,channel);
                break;
            }

            /* 主席+代表开话筒数量未超过允许开话筒数 */
            if(chmMicNum + rpsMicNum < wiredAllowOpen) {
                channel = Conference_GetAudioChannel(tWired);
                UnitInfo.wired[id].channel = channel;
                DataQueue.enter(rpsMicQueue,&id);
                EXE_RPS_OPEN_MIC(id,channel);
            }
            /* 主席+代表开话筒数量等于允许开话筒数 */
            else {
                if(rpsMicNum > 0) {
                    uint16_t closeId;

                    /* 队列取出代表单元并关闭 */
                    DataQueue.exit(rpsMicQueue,&closeId);
                    channel = UnitInfo.wired[closeId].channel;
                    EXE_RPS_CLOSE_MIC(closeId);
                    /* 打开代表 */
                    DataQueue.enter(rpsMicQueue,&id);
                    EXE_RPS_OPEN_MIC(id,channel);
                } else {
                    /* 话筒已满 */
                    EXE_MIC_FULL(id,sPC | sWiredUnit);
                }
            }
        }
        break;
        }
    }
    break;

    /*** 正常模式 ***/
    case mNormal:
    /*** 声控模式 ***/
    case mVoiceCtrl: {
        switch(para) {
        /* 主席单元 */
        case CHM_OPEN_MIC: {
            /* 查找话筒队列是否已经存在对应ID的话筒 */
            if(DataQueue.search(chmMicQueue,&id)) {
                channel = UnitInfo.wired[id].channel;
                EXE_CHM_OPEN_MIC(id,channel);
                break;
            }

            /* 主席+代表开话筒数量未超过允许开话筒数 */
            if(chmMicNum + rpsMicNum < wiredAllowOpen) {
                DataQueue.enter(chmMicQueue,&id);
                channel = Conference_GetAudioChannel(tWired);
                UnitInfo.wired[id].channel = channel;
                EXE_CHM_OPEN_MIC(id,channel);
            }
            /* 主席+代表开话筒数量等于允许开话筒数 */
            else {
                if(rpsMicNum > 0) {
                    uint16_t closeId;

                    /* 队列取出代表单元并关闭 */
                    DataQueue.exit(rpsMicQueue,&closeId);
                    channel = UnitInfo.wired[closeId].channel;
                    EXE_RPS_CLOSE_MIC(closeId);

                    /* 打开主席 */
                    DataQueue.enter(chmMicQueue,&id);
                    EXE_CHM_OPEN_MIC(id,channel);
                } else {
                    /* 话筒已满 */
                    EXE_MIC_FULL(id,sPC | sWiredUnit);
                }
            }
        }
        break;
        /* 代表单元 */
        case RPS_OPEN_MIC: {
            /* 查找话筒队列是否已经存在对应ID的话筒 */
            if(DataQueue.search(rpsMicQueue,&id)) {
                /* 重新发送打开话筒指令，不需要操作队列 */
                channel = UnitInfo.wired[id].channel;
                EXE_RPS_OPEN_MIC(id,channel);
                break;
            }

            /* 查找等待队列是否存在对应ID话筒 */
            if(waitNum > 0 ) {
                /* 取消该话筒等待 */
                index = DataQueue.search(waitQueue,&id);
                if(index != 0) {
                    DataQueue.deleted(waitQueue,index);
                    EXE_MIC_DISWAIT(id);
                }
                break;
            }

            /* 主席+代表开话筒数量未超过允许开话筒数 */
            if(chmMicNum + rpsMicNum < wiredAllowOpen) {
                channel = Conference_GetAudioChannel(tWired);
                UnitInfo.wired[id].channel = channel;
                DataQueue.enter(rpsMicQueue,&id);
                EXE_RPS_OPEN_MIC(id,channel);
            }
            /* 主席+代表开话筒数量等于允许开话筒数 */
            else {
                /* 等待数量未满 */
                if(waitNum < wiredAllowWait) {
                    /* 进入等待队列 */
                    DataQueue.enter(waitQueue,&id);
                    EXE_MIC_WAIT(id);
                } else {
                    /* 话筒已满 */
                    EXE_MIC_FULL(id,sPC | sWiredUnit);
                }
            }
        }
        break;
        }
    }
    break;

    /*** 申请模式 ***/
    case mApply: {
        switch(para) {
        /* 主席单元 */
        case CHM_OPEN_MIC: {
            /* 查找话筒队列是否已经存在对应ID的话筒 */
            if(DataQueue.search(chmMicQueue,&id)) {
                channel = UnitInfo.wired[id].channel;
                EXE_CHM_OPEN_MIC(id,channel);
                break;
            }

            /* 主席+代表开话筒数量未超过允许开话筒数 */
            if(chmMicNum + rpsMicNum < wiredAllowOpen) {
                DataQueue.enter(chmMicQueue,&id);
                channel = Conference_GetAudioChannel(tWired);
                UnitInfo.wired[id].channel = channel;
                EXE_CHM_OPEN_MIC(id,channel);
            }
            /* 主席+代表开话筒数量等于允许开话筒数 */
            else {
                if(rpsMicNum > 0) {
                    uint16_t closeId;

                    /* 队列取出代表单元并关闭 */
                    DataQueue.exit(rpsMicQueue,&closeId);
                    channel = UnitInfo.wired[closeId].channel;
                    EXE_RPS_CLOSE_MIC(closeId);

                    /* 打开主席 */
                    DataQueue.enter(chmMicQueue,&id);
                    EXE_CHM_OPEN_MIC(id,channel);
                } else {
                    /* 话筒已满 */
                    EXE_MIC_FULL(sPC|sWiredUnit,id);
                }
            }
        }
        break;
        /* 代表单元 */
        case RPS_OPEN_MIC: {
            /* 查找话筒队列是否已经存在对应ID的话筒 */
            if(DataQueue.search(rpsMicQueue,&id)) {
                channel = UnitInfo.wired[id].channel;
                EXE_RPS_OPEN_MIC(id,channel);
                break;
            }

            /* 查找等待队列是否存在对应ID话筒 */
            if(waitNum > 0 ) {
                /* 取消该话筒等待 */
                index = DataQueue.search(waitQueue,&id);
                if(index != 0) {
                    DataQueue.deleted(waitQueue,index);
                    EXE_MIC_DISWAIT(id);
                    EXE_REVOKE_APPLY(id);
                }
                break;
            }

            /* 主席+代表开话筒数量未超过允许开话筒数 */
            if(chmMicNum + rpsMicNum < wiredAllowOpen) {
                /* 进入等待队列 */
                DataQueue.enter(waitQueue,&id);
                EXE_MIC_WAIT(id);
                EXE_APPLY_OPEN_MIC(id);
            }
            /* 主席+代表开话筒数量等于允许开话筒数 */
            else {
                /* 话筒已满 */
                EXE_MIC_FULL(id,sPC | sWiredUnit);
            }
        }
        break;
        /* 同意开话筒 */
        case AGREE_OPEN_MIC: {
            if(chmMicNum + rpsMicNum < wiredAllowOpen && waitNum > 0) {
                /* 打开话筒，并删除等待队列中对应ID的话筒 */
                index = DataQueue.search(waitQueue,&id);
                if(index != 0) {
                    DataQueue.deleted(waitQueue,index);

                    DataQueue.enter(rpsMicQueue,&id);
                    channel = Conference_GetAudioChannel(tWired);
                    UnitInfo.wired[id].channel = channel;
                    EXE_RPS_OPEN_MIC(id,channel);
                }
            }
        }
        break;
        /* 不同意开话筒 */
        case DISAGREE_OPEN_MIC: {
            /* 查找等待队列是否存在对应ID话筒 */
            if(waitNum > 0 ) {
                /* 取消该话筒等待 */
                index = DataQueue.search(waitQueue,&id);
                if(index != 0) {
                    DataQueue.deleted(waitQueue,index);
                    EXE_MIC_DISWAIT(id);
                    EXE_REVOKE_APPLY(id);
                }
                break;
            }
        }
        break;

        }
    }
    break;
    }
#endif
    Conference_OpenMicListDebug();
}



/**
* @Name  		Conference_WiredCloseMic
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void Conference_WiredCloseMic(uint16_t id, uint8_t para)
{
//    ConfProtocol_S prot;
    uint8_t index, waitNum;

    ERR_CHECK(id > 0 && id <= WIRED_UNIT_MAX_ONLINE_NUM,return);
    ERR_CHECK(!(para == CHM_CLOSE_MIC && UnitInfo.wired[id].attr != aChairman),return);
    ERR_CHECK(!(para == RPS_CLOSE_MIC && UnitInfo.wired[id].attr != aRepresentative),return);

    waitNum = DataQueue.getSize(waitQueue);

    switch(micMode) {
    /*** 先进先出模式 ***/
    case mFifo: {
        switch(para) {
        /* 主席单元 */
        case CHM_CLOSE_MIC: {
            /* 查找话筒队列是否已经存在对应ID的话筒 */
            index = DataQueue.search(chmMicQueue,&id);
            if(index) {
                Conference_GiveAudioChannel(tWired,UnitInfo.wired[id].channel);
                DataQueue.deleted(chmMicQueue,index);
                EXE_CHM_CLOSE_MIC(id);
            }
        }
        break;

        /* 代表单元 */
        case RPS_CLOSE_MIC: {
            /* 查找话筒队列是否已经存在对应ID的话筒 */
            index = DataQueue.search(rpsMicQueue,&id);
            if(index) {
                Conference_GiveAudioChannel(tWired,UnitInfo.wired[id].channel);
                UnitInfo.wired[id].channel = null;
                DataQueue.deleted(rpsMicQueue,index);
                EXE_RPS_CLOSE_MIC(id);
            }
        }
        break;
        }
    }
    break;

    /*** 正常模式 ***/
    case mNormal:
    /*** 声控模式 ***/
    case mVoiceCtrl: {
        switch(para) {
        /* 主席单元 */
        case CHM_CLOSE_MIC: {
            /* 查找话筒队列是否已经存在对应ID的话筒 */
            index = DataQueue.search(chmMicQueue,&id);
            if(index) {
                Conference_GiveAudioChannel(tWired,UnitInfo.wired[id].channel);
                DataQueue.deleted(chmMicQueue,index);
                EXE_CHM_CLOSE_MIC(id);
            } else
                break;

            if(waitNum > 0) {
                /* 等待队列取出单元并打开 */
                uint16_t waitId;
                DataQueue.exit(waitQueue,&waitId);
                Conference_WiredOpenMic(waitId,RPS_OPEN_MIC);
            }
        }
        break;

        /* 代表单元 */
        case RPS_CLOSE_MIC: {
            /* 查找话筒队列是否已经存在对应ID的话筒 */
            index = DataQueue.search(rpsMicQueue,&id);
            if(index) {
                Conference_GiveAudioChannel(tWired,UnitInfo.wired[id].channel);
                UnitInfo.wired[id].channel = null;
                DataQueue.deleted(rpsMicQueue,index);
                EXE_RPS_CLOSE_MIC(id);
            }

            if(waitNum > 0) {
                /* 等待队列取出单元并打开 */
                uint16_t waitId;
                DataQueue.exit(waitQueue,&waitId);
                Conference_WiredOpenMic(waitId,RPS_OPEN_MIC);
            }
        }
        break;
        }
    }
    break;



    /*** 申请模式 ***/
    case mApply: {
        switch(para) {
        /* 主席单元 */
        case CHM_CLOSE_MIC: {
            /* 查找话筒队列是否已经存在对应ID的话筒 */
            index = DataQueue.search(chmMicQueue,&id);
            if(index) {
                Conference_GiveAudioChannel(tWired,UnitInfo.wired[id].channel);
                DataQueue.deleted(chmMicQueue,index);
                EXE_CHM_CLOSE_MIC(id);
            }
        }
        break;

        /* 代表单元 */
        case RPS_CLOSE_MIC: {
            /* 查找话筒队列是否已经存在对应ID的话筒 */
            index = DataQueue.search(rpsMicQueue,&id);
            if(index) {
                Conference_GiveAudioChannel(tWired,UnitInfo.wired[id].channel);
                UnitInfo.wired[id].channel = null;
                DataQueue.deleted(rpsMicQueue,index);
                EXE_RPS_CLOSE_MIC(id);
            }
        }
        break;
        }
    }
    break;
    }

    Conference_OpenMicListDebug();
}


/**
* @Name  		Conference_WiredCloseAllMic
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void Conference_WiredCloseAllMic(UnitAttr_EN attr)
{
//    ConfProtocol_S prot;
    DataQueueHandler_S *queue;
    uint8_t micNum,i;
    uint16_t *idArr;

    if(attr == aChairman)
        queue = chmMicQueue;
    else if(attr == aRepresentative)
        queue = rpsMicQueue;
    else
        return;

    micNum = DataQueue.getSize(queue);
    if(micNum > 0) {
        idArr = MALLOC(micNum * sizeof(uint16_t));
        DataQueue.toArray(queue,idArr);
        for(i = 0; i<micNum; i++) {
            if(attr == aChairman)
                EXE_CHM_CLOSE_MIC(idArr[i]);
            else
                EXE_RPS_CLOSE_MIC(idArr[i]);
            Conference_GiveAudioChannel(tWired,UnitInfo.wired[idArr[i]].channel);
            UnitInfo.wired[idArr[i]].channel = null;
        }
        DataQueue.empty(queue);
    }
}


/**
* @Name  		Conference_WiredCloseAllMic
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void Conference_WiredOutlineAllUnit(void)
{
    Conference_WiredCloseAllMic(aChairman);
    Conference_WiredCloseAllMic(aRepresentative);

    memset(&OnlineNum,0,sizeof(UnitOnlineNum));
    memset(&UnitInfo,0,sizeof(UnitInfo));

    /* 重置音频通道队列 */
    Conference_ResetAudioChannel(tWired);
    /* 清除等待队列 */
    DataQueue.empty(waitQueue);
}



/**
* @Name  		Conference_WiredClearApply
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void Conference_WiredClearApply(void)
{
    uint8_t waitNum,i;
    uint16_t *idArr;

    waitNum = DataQueue.getSize(waitQueue);
    if(waitNum > 0) {
        idArr = MALLOC(waitNum * sizeof(uint16_t));
        DataQueue.toArray(waitQueue,idArr);
        for(i = 0; i<waitNum; i++) {
            EXE_MIC_DISWAIT(idArr[i]);
            if(micMode == mApply)
                EXE_REVOKE_APPLY(idArr[i]);
        }
        DataQueue.empty(waitQueue);
    }
}

/**
* @Name  		Conference_ChangeSysMode
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void Conference_ChangeSysMode(SysMode_EN mode)
{
	/* 检查当前模式和目标模式，如果当前是“会议模式”下，目标模式可随便切换，
		如果当前是“非会议模式”下，则除了会议模式别的模式都不能切换
	(换句话说在非会议模式[EditID,Sign,Vote]下，必须先结束该模式，切换到
	会议模式[conference]，才可以再切换成别的非会议模式) */
	ERR_CHECK(!(sysMode != mConference && mode != mConference), return);

 	switch(mode){
		case mConference:{
			EXE_CONFERENCE_MODE();
			sysMode = mConference;
		}
		break;

		case mEditID:{
			EXE_EDIT_ID_MODE();
			sysMode = mEditID;
			Conference_WiredOutlineAllUnit();		
		}break;

		case mSign:{
			uint16_t id;

			for(id = 0;id < WIRED_UNIT_MAX_ONLINE_NUM;id++)
				UnitInfo.wired[id].sign = false;
					
			for(id = 0;id < WIFI_UNIT_MAX_ONLINE_NUM;id++)
				UnitInfo.wifi[id].sign = false;
			
			EXE_SIGN_MODE();
			sysMode = mSign;
		}break;
	}
}


/**
* @Name  		Conference_ChairmanPriority
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void Conference_ChairmanPriority(uint16_t id)
{

    ERR_CHECK(id > 0 && id <= WIRED_UNIT_MAX_ONLINE_NUM,return);
    ERR_CHECK(UnitInfo.wired[id].attr == aChairman,return);

    /* 关闭所有代表单元 */
    Conference_WiredCloseAllMic(aRepresentative);
    /* 打开主席单元 */
    Conference_WiredOpenMic(id,CHM_OPEN_MIC);

    /* 取消所有话筒申请 */
    Conference_WiredClearApply();
}



/**
* @Name  		Conference_ResetAudioChannel
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void Conference_ResetAudioChannel(UnitType_EN type)
{
//	ConfHandler_S *confHandler = &ConfHandler[type];
    uint8_t ch;

    DataQueue.empty(channelQueue);
    for(ch = 1; ch <= WIRED_UNIT_MAX_ALLWO_OPEN; ch++) {
        DataQueue.enter(channelQueue,&ch);
    }
}

/**
* @Name  		Conference_GetAudioChannel
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static uint8_t Conference_GetAudioChannel(UnitType_EN type)
{
    uint8_t ch;

    DataQueue.exit(channelQueue,&ch);
    ch += 0x80;
    return ch;
}

/**
* @Name  		Conference_GiveAudioChannel
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void Conference_GiveAudioChannel(UnitType_EN type,uint8_t ch)
{
    if(ch < 0x81 || ch > WIRED_UNIT_MAX_ALLWO_OPEN + 0x80)
        return;
    ch -= 0x80;
    DataQueue.enter(channelQueue,&ch);
}

/**
* @Name  		Conference_UnitOnlineNum
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void Conference_UnitOnlineNum(UnitOnlineNum *onlineNum)
{
    ERR_CHECK(onlineNum != null,return);
    memcpy(onlineNum,&OnlineNum,sizeof(UnitOnlineNum));
}

/**
* @Name  		Conference_GetSysMode
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static SysMode_EN Conference_GetSysMode(void)
{
    return sysMode;
}

/**
* @Name  		Conference_GetCurrentEditedID
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static uint16_t Conference_GetCurrentEditedID(void)
{
    return currentEditID;
}

/**
* @Name  		Conference_WiredUnitInfo
* @Author  		KT
* @Description	对单元处理任务下发单元信息结构指针
*				(需要在引入头文件前定义宏 LICENSE_ACCESS_UNIT_INFO)
*
* @License		LICENSE_ACCESS_UNIT_INFO
*
* @para
*
* @return
*/
static UnitInfo_S *Conference_WiredUnitInfo(void)
{
    return UnitInfo.wired;
}

/**
* @Name  		Conference_OpenMicListDebug
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void Conference_OpenMicListDebug(void)
{
    uint32_t i;
    uint16_t *idArr;
    uint8_t len;


    len = DataQueue.getSize(chmMicQueue);
    idArr = MALLOC(len * sizeof(uint16_t));
    DataQueue.toArray(chmMicQueue,idArr);

//	debug("==========================================================\r\n");
//	debug("========              Open mic list            ===========\r\n");
    debug("==========================================================\r\n");
    debug("==      Attr      ==      ID      ==      Channel       ==\r\n");
    for(i=0; i<len; i++)
        debug("==    Chairman    ==      %02d      ==        %02X          ==\r\n",idArr[i],UnitInfo.wired[idArr[i]].channel);
    FREE(idArr);

    len = DataQueue.getSize(rpsMicQueue);
    idArr = MALLOC(len * sizeof(uint16_t));
    DataQueue.toArray(rpsMicQueue,idArr);

    for(i=0; i<len; i++)
        debug("== Representative ==      %02d      ==        %02X          ==\r\n",idArr[i],UnitInfo.wired[idArr[i]].channel);
    debug("==========================================================\r\n");
    FREE(idArr);


}


