/**
 *
 *	@name				wired_unit.c
 *	@author 			KT
 *	@date 				2019/07/23
 *	@brief
 *  @include			wired_unit.h
 *
 *  @API
 *
 *  @description
 *
 **/
/*******************************************************************************
 * includes
 ******************************************************************************/
/* OS */
#include "FreeRTOS.h"
#include "timers.h"

/* API */
#include "network.h"
#include "ram.h"

/* APP */
#include "wired_unit.h"
#include "conference.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**** 网络相关参数定义 ****/
#define HOST_LOCAL_IP										{192,168,0,117}
#define HOST_GATEWAY										{192,168,0,1}
#define HOST_NETMASK										{255,255,255,0}
#define HOST_PORT											(1026)

/* 单元指令数据监听多播地址及端口 */
#define UNIT_DATA_MULTICAST_IP								{224,0,2,9}
#define UNIT_DATA_MULTICAST_PORT							(1028)

/* 单元指令数据目的多播地址及端口 */
#define UNIT_DEST_IP										{224,0,2,7}
#define UNIT_DEST_PORT										(1026)

/* 网络接口 */
#define NETWORK_ENET_TYPE									eth1

/* 网络类型 */
#define NETWORK_TYPE										NETWORK_TYPE_ETHERNET

/* 任务堆栈大小及优先级 */
#define WIRED_UNIT_TASK_STACK_SIZE							(2048)
#define WIRED_UNIT_TASK_PRIORITY							(15)

/* 接收单元数据BUF大小 */
#define UNIT_DATA_RECEIVE_BUF_SIZE							(64)


/* 一次轮询总时间为 POLLING_TIME_MS + (在线单元数 * POLLING_TIME_INTERVAL_MS) */
/* 轮询时间 */
#define POLLING_TIME_MS										(100)
/* 两台单元间轮询间隔 */
#define POLLING_TIME_INTERVAL_MS							(5)

/* 轮询无应答判断为离线次数 */
#if 0   
/* 测试用 */
#define POLLING_NO_REPLY_OFFLINE_COUNT						(1200)
#else
#define POLLING_NO_REPLY_OFFLINE_COUNT						(5)
#endif

#define IS_APPLY_ACCESS_SYS(_type,_ph,_pl)					((_pl == RPS_APPLY_ACCESS_SYS || _pl == CHM_APPLY_ACCESS_SYS) && _type == BASIC_MSG && _ph == CONFERENCE_MODE)
#define IS_CONFIRM_ID(_type,_ph,_pl)						(_pl == UNIT_CONFIRM_ID && _type == BASIC_MSG && _ph == EDIT_ID_MODE)
#define IS_UNIT_REPLY_ONLINE(_type,_ph,_pl)					((_pl == RPS_REPLY_ONLINE || _pl == CHM_REPLY_ONLINE) && _type == BASIC_MSG && _ph == CONFERENCE_MODE)

/* 单元主机通讯协议格式 */
typedef struct {
    char header[4];
    ConfProtocol_S prot;
    uint16_t exLen;
    uint8_t exDataHead;
} NetData_S;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* API调用 */
static void WiredUnit_Launch(void);
static void WiredUnit_NetDataTransmitWithExData(ConfProtocol_S *prot, uint16_t exLen, uint8_t *exData);
static void WiredUnit_NetDataTransmit(ConfProtocol_S *prot);

/* 内部调用 */
static void WiredUnit_LaunchTask(void *pvParameters);
static void WiredUnit_EthStaListener(bool sta);
static void WiredUnit_NetDataProcessTask(void *pvParameters);
static void WiredUnit_PollingTimer(TimerHandle_t xTimer);
static void WiredUnit_AccessSystem(uint16_t id,Network_Mac_S *unitSrcMac,UnitAttr_EN attr);
//static void WiredUnit_InfoInit(void);


static void WiredUnit_NotifyConference(ConfProtocol_S *prot);
static void WiredUnit_NotifyConferenceWithExData(ConfProtocol_S *prot, uint16_t exLen, uint8_t *exData);
/*******************************************************************************
 * Variables
 ******************************************************************************/
static const NETWORK_IP hostIp = HOST_LOCAL_IP;
static const NETWORK_GW hostGw = HOST_GATEWAY;
static const NETWORK_MASK hostMask = HOST_NETMASK;
static const NETWORK_IP multicastIp = UNIT_DATA_MULTICAST_IP;
static const NETWORK_IP unitIp = UNIT_DEST_IP;
static const NETWORK_PORT unitPort = UNIT_DEST_PORT;
static NETWORK_MAC unitMac;

static Network_TaskHandler_S *netTaskHandler;

static bool isEthConnected;


static UnitInfo_S *unitInfo;

static const uint8_t VotePollingCode[] = 
{ POLLING_VOTE, POLLING_VOTE_SIGN, POLLING_VOTE_F, POLLING_VOTE_FSIGN, 
  POLLING_ELECT, POLLING_ELECT_SIGN, POLLING_ELECT_F, POLLING_ELECT_FSIGN, 
  POLLING_RATE, POLLING_RATE_SIGN, POLLING_RATE_F, POLLING_RATE_FSIGN, 
  POLLING_VOTECUSTOM_F_2_S, POLLING_VOTECUSTOM_F_2, POLLING_VOTECUSTOM_L_2_S, POLLING_VOTECUSTOM_L_2, 
  POLLING_VOTECUSTOM_F_3_S, POLLING_VOTECUSTOM_F_3, POLLING_VOTECUSTOM_L_3_S, POLLING_VOTECUSTOM_L_3, 
  POLLING_VOTECUSTOM_F_4_S, POLLING_VOTECUSTOM_F_4, POLLING_VOTECUSTOM_L_4_S, POLLING_VOTECUSTOM_L_4, 
  POLLING_VOTECUSTOM_F_5_S, POLLING_VOTECUSTOM_F_5, POLLING_VOTECUSTOM_L_5_S, POLLING_VOTECUSTOM_L_5, 
  POLLING_SATISFACTION, POLLING_SATISFACTION_SIGN, POLLING_SATISFACTION_F, POLLING_SATISFACTION_FSIGN
 };

/* 轮询定时器 */
static TimerHandle_t pollingTimer;

WiredUnit_S WiredUnit = {
    .launch = WiredUnit_Launch,
    .transmit = WiredUnit_NetDataTransmit,
    .transWithExData = WiredUnit_NetDataTransmitWithExData,
};
/*******************************************************************************
 * Code
 ******************************************************************************/
/**
* @Name  		WiredUnit_Init
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void WiredUnit_Launch(void) {
    if (xTaskCreate(WiredUnit_LaunchTask, "WiredUnitLaunchTask", WIRED_UNIT_TASK_STACK_SIZE, null, WIRED_UNIT_TASK_PRIORITY, null) != pdPASS) {
        debug("create launch task error\r\n");
    }
}

/**
* @Name  		WiredUnit_Init
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void WiredUnit_LaunchTask(void *pvParameters) {
    Network_EthPara_S *ethPara;
    Network_EthernetTaskPara_S *taskPara;

    isEthConnected = false;

    ethPara = MALLOC(sizeof(Network_EthPara_S));
    taskPara = MALLOC(sizeof(Network_EthernetTaskPara_S));

    /* 网口初始化 */
    ethPara->index = NETWORK_ENET_TYPE;
    ethPara->type = NETWORK_TYPE;
    NETWORK_SET_ADDR(ethPara->ip,hostIp.addr0,hostIp.addr1,hostIp.addr2,hostIp.addr3);
    NETWORK_SET_ADDR(ethPara->gateway,hostGw.addr0,hostGw.addr1,hostGw.addr2,hostGw.addr3);
    NETWORK_SET_ADDR(ethPara->netmask,hostMask.addr0,hostMask.addr1,hostMask.addr2,hostMask.addr3);
    ethPara->ethStaListener = WiredUnit_EthStaListener;

    Network.ethConfig(ethPara);

    /* 等待网络连接 */
    while(!isEthConnected) {
        DELAY(200);
    }

    /* 网络功能初始化 */
    taskPara->port = HOST_PORT;

    /* 多播地址 */
    taskPara->multicastNum = 1;
    taskPara->multiPort = MALLOC(sizeof(NETWORK_PORT) * taskPara->multicastNum);
    taskPara->multiIp = MALLOC(sizeof(NETWORK_IP) * taskPara->multicastNum);
    NETWORK_SET_ADDR(taskPara->multiIp[0],multicastIp.addr0,multicastIp.addr1,multicastIp.addr2,multicastIp.addr3);
    taskPara->multiPort[0] = UNIT_DATA_MULTICAST_PORT;
    NETWORK_SET_MAC((&unitMac),0x01,0x00,0x5E,(unitIp.addr1 & 0x7F),unitIp.addr2,unitIp.addr3);

    /* 获取单元数据指针 */
	unitInfo = Conference.wiredUnitInfo();

    netTaskHandler = Network.creatTask(NETWORK_ENET_TYPE,tEthernet,taskPara);

    /* 启动单元数据处理线程 */
    if (xTaskCreate(WiredUnit_NetDataProcessTask, "NetDataProcessTask", WIRED_UNIT_TASK_STACK_SIZE, null, WIRED_UNIT_TASK_PRIORITY, null) != pdPASS) {
        debug("create host task error\r\n");
    }

    /* 启动轮询定时器 */
    pollingTimer = xTimerCreate("PollingTimer",POLLING_TIME_MS,pdTRUE,null,WiredUnit_PollingTimer);
    
    vTaskDelete(null);
}


/**
* @Name  		WiredUnit_PollingTimer
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void WiredUnit_PollingTimer(TimerHandle_t xTimer) {
    uint16_t id;
    ConfProtocol_S prot;
	ConfSysInfo_S *info;

    memset(&prot,0,sizeof(ConfProtocol_S));

	info = Conference.getConfSysInfo();

	switch(info->state.sysMode){
		/* 会议模式 */
		case kMode_Conference:{
			/* 轮询从1号ID开始 */
			for(id = 1; id<WIRED_UNIT_MAX_ONLINE_NUM; id++) {
				/* 如果单元在线，发轮询指令 */
				if(unitInfo[id].online) {
					if(unitInfo[id].pollCount < POLLING_NO_REPLY_OFFLINE_COUNT) {
						Protocol.conference(&prot,id,BASIC_MSG,CONFERENCE_MODE,QUERY_UNIT,0,0);
						unitInfo[id].pollCount++;
					} else {
						Protocol.conference(&prot,id,BASIC_MSG,CONFERENCE_MODE,UNIT_OFFLINE,0,0);
						unitInfo[id].online = false;
						WiredUnit_NotifyConference(&prot);
					}
					WiredUnit_NetDataTransmit(&prot);
					DELAY(POLLING_TIME_INTERVAL_MS);
				}
			}
		}break;
		
		/* 编ID模式 */
		case kMode_EditID:{
			Protocol.conference(&prot, WHOLE_BROADCAST_ID, POLLING_MSG, EDIT_ID_POLLING, CURRENT_ID,0,Conference.getCurrentEditId());
			WiredUnit_NetDataTransmit(&prot);
		}break;
		case kMode_Sign:{
			/* 轮询从1号ID开始 */
			for(id = 1; id<WIRED_UNIT_MAX_ONLINE_NUM; id++) {
				/* 如果单元在线，且未进行签到，发轮询指令 */
				if(unitInfo[id].online && !unitInfo[id].sign) {
					Protocol.conference(&prot,id,POLLING_MSG,SIGN_POLLING,HOST_SIGN_POLLIGN,0,0);
					WiredUnit_NetDataTransmit(&prot);
					DELAY(POLLING_TIME_INTERVAL_MS);
				}
			}
		}break; 
		case kMode_Vote:{
			/* 轮询从1号ID开始 */
			for(id = 1; id<WIRED_UNIT_MAX_ONLINE_NUM; id++) {
				if(unitInfo[id].online) {
					Protocol.conference(&prot,id,POLLING_MSG,VOTE_POLLING,VotePollingCode[info->state.voteMode],0,0);
					WiredUnit_NetDataTransmit(&prot);
					DELAY(POLLING_TIME_INTERVAL_MS);
				}
			}
		}break;
		
		default:break;
	}
    
}

/**
* @Name
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void WiredUnit_EthStaListener(bool sta) {
    isEthConnected = sta;
}

/**
* @Name  		WiredUnit_NetDataProcessTask
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void WiredUnit_NetDataProcessTask(void *pvParameters) {
    Network_DataBuf_S *taskBuf;
    Network_Mac_S *unitSrcMac;
    NetData_S *netData;
	ConfSysInfo_S *info;

    ConfProtocol_S prot;

    taskBuf	= MALLOC(sizeof(Network_DataBuf_S));
    taskBuf->data = MALLOC(UNIT_DATA_RECEIVE_BUF_SIZE);
    taskBuf->maxLen = UNIT_DATA_RECEIVE_BUF_SIZE;
	
    debug("Wired unit data process task start!!\r\n");
	
	xTimerStart(pollingTimer,0);

	/* 广播模式及数量 */
	info = Conference.getConfSysInfo();
	WiredUnit_NetDataTransmit(Protocol.conference(&prot,MODE_BROADCAST_ID,STATE_MSG,info->config->micMode,info->config->wiredAllowOpen,null,null));
    while(1) {

        Network.receive(netTaskHandler,taskBuf,MAX_NUM);

        if(taskBuf->len < 14) {
            continue;
        }
        netData = (NetData_S *)taskBuf->data;

        /* 复制参数 */
        memcpy(&prot,&netData->prot,sizeof(ConfProtocol_S));
        prot.id = lwip_htons(prot.id);
        unitSrcMac = &taskBuf->srcMac;

        if(prot.id >= 1 && prot.id <= WIRED_UNIT_MAX_ONLINE_NUM) {

            /* 检查单元在线标志位 */
            if(unitInfo[prot.id].online) {
                /* 单元状态为在线 */
				
                unitInfo[prot.id].pollCount = 0;

                /* 单元申请进入系统 */
				if(IS_APPLY_ACCESS_SYS(prot.type,prot.ph,prot.pl))	goto access_sys;

                /* 单元回复在线 */
				else if(IS_UNIT_REPLY_ONLINE(prot.type,prot.ph,prot.pl))	goto clear_buf;


                /* 其他会议消息发送给会议任务处理 */
                WiredUnit_NotifyConference(&prot);
                goto clear_buf;
            } else {
                /* 单元状态为离线 */
				
				/* 单元申请进入系统 */
                if(IS_APPLY_ACCESS_SYS(prot.type,prot.ph,prot.pl)) {
                    goto access_sys;
                }
				
				/* 单元确认当前ID(编ID),需要向会议任务报告申请ID的MAC */
				else if(IS_CONFIRM_ID(prot.type,prot.ph,prot.pl)){
					WiredUnit_NotifyConferenceWithExData(&prot,6,(uint8_t *)unitSrcMac);
					goto clear_buf;
				}
                /* 如果为非在线状态而且不是申请进入系统及编ID，不处理当前数据，直接返回给单元离线 */
                else {
                    Protocol.conference(&prot,prot.id,BASIC_MSG,CONFERENCE_MODE, UNIT_OFFLINE,null,null);
                    WiredUnit_NetDataTransmit(&prot);
                    goto clear_buf;
                }
            }
            
access_sys:
			/* 单元机进系统 */
            if(prot.pl == RPS_APPLY_ACCESS_SYS)
                WiredUnit_AccessSystem(prot.id,unitSrcMac,aRepresentative);
            else if(prot.pl == CHM_APPLY_ACCESS_SYS)
                WiredUnit_AccessSystem(prot.id,unitSrcMac,aChairman);

        }

        /* 清空缓存 */
clear_buf:
        taskBuf->len = 0;
        memset(taskBuf->data,0,UNIT_DATA_RECEIVE_BUF_SIZE);
    }
}

/**
* @Name  		WiredUnit_AccessSystem
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void WiredUnit_AccessSystem(uint16_t id,Network_Mac_S *unitSrcMac,UnitAttr_EN attr) {
    ConfProtocol_S prot;
    UnitInfo_S *devInfo;

    if(id <= 0 || id > WIRED_UNIT_MAX_ONLINE_NUM || unitSrcMac == null)
        return;

    devInfo = &unitInfo[id];

    /* 设备ID已在线，且MAC与申请进系统MAC不同 */
    if(devInfo->online && !NETWORK_COMPARISON_MAC((&devInfo->mac),unitSrcMac)) {
        Protocol.conference(&prot,WHOLE_BROADCAST_ID, BASIC_MSG, CONFERENCE_MODE, ID_DUPICATE,id,null);
//
//        WiredUnit_NetDataTransmit(&prot);
        WiredUnit_NotifyConference(&prot);
    }
    /* 设备ID不在线,或已在线但MAC相同 */
    else {
        Protocol.conference(&prot,id, BASIC_MSG, CONFERENCE_MODE, UNIT_ACCESS_SYS,null,null);
		WiredUnit_NetDataTransmit(&prot);

		devInfo->attr = attr;
        devInfo->pollCount = 0;
        NETWORK_SET_MAC((&devInfo->mac),unitSrcMac->mac0,unitSrcMac->mac1,unitSrcMac->mac2,unitSrcMac->mac3,unitSrcMac->mac4,unitSrcMac->mac5);

		/* 如果设备本来已经在线，就不发单元上线通知给会议任务 */
		if(!devInfo->online){
			WiredUnit_NotifyConference(&prot);
	        devInfo->online = true;
		}
    }
}

/**
* @Name  		WiredUnit_NotifyConferenceWithExData
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void WiredUnit_NotifyConferenceWithExData(ConfProtocol_S *prot, uint16_t exLen, uint8_t *exData) {

    Notify_S *notify;

    if(prot == null || (exLen != 0 && exData == null))
        return;

    notify = MALLOC(sizeof(Notify_S) + exLen);

    notify->nSrc = kType_NotiSrc_WiredUnit;

//    notify->kWord = kWord;

    memcpy(&notify->prot.conference,prot,sizeof(ConfProtocol_S));
    notify->exLen = exLen;
    if(exLen != 0) {
        memcpy(&notify->exDataHead,exData,exLen);
    }

    Conference.notify(notify);
}

/**
* @Name  		WiredUnit_NotifyConference
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void WiredUnit_NotifyConference(ConfProtocol_S *prot) {
    WiredUnit_NotifyConferenceWithExData(prot, null, null);
}


/**
* @Name  		WiredUnit_NetDataTransmitWithExData
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void WiredUnit_NetDataTransmitWithExData(ConfProtocol_S *prot, uint16_t exLen, uint8_t *exData) {
    Network_DataBuf_S *taskBuf;
    NetData_S *netData;
    uint32_t dataLen;

    if(prot == null || (exLen != 0 && exData == null))
        return;

    dataLen = exLen + sizeof(NetData_S);
    netData = MALLOC(dataLen);
    taskBuf = MALLOC(sizeof(Network_DataBuf_S));
    memset(netData,0,dataLen);

    netData->header[0] = 'h';
    netData->header[1] = 'y';
    netData->header[2] = 'x';
    netData->header[3] = 't';
    memcpy(&netData->prot,prot,sizeof(ConfProtocol_S));
    netData->prot.id = lwip_htons(netData->prot.id);
	netData->prot.sec = lwip_htons(netData->prot.sec);
    netData->exLen = lwip_htons(exLen);
    if(exLen != 0) {
        memcpy(&netData->exDataHead,exData,exLen);
    }

    NETWORK_SET_MAC((&(taskBuf->destMac)),unitMac.mac0,unitMac.mac1,unitMac.mac2,unitMac.mac3,unitMac.mac4,unitMac.mac5);
    NETWORK_SET_ADDR(taskBuf->destIp,unitIp.addr0,unitIp.addr1,unitIp.addr2,unitIp.addr3);
    taskBuf->destPort = unitPort;
    taskBuf->len = dataLen;
    taskBuf->data = (uint8_t *)netData;

    Network.transmit(netTaskHandler,taskBuf);

    FREE(netData);
    FREE(taskBuf);
}


/**
* @Name  		WiredUnit_NetDataTransmit
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void WiredUnit_NetDataTransmit(ConfProtocol_S *prot) {
    WiredUnit_NetDataTransmitWithExData(prot,null,null);
}



