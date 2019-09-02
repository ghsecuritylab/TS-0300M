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
 * permission
 ******************************************************************************/
#define LICENSE_ACCESS_UNIT_INFO

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
/**** ������ز������� ****/
#define HOST_LOCAL_IP										{172,16,4,215}
#define HOST_GATEWAY										{172,16,4,254}
#define HOST_NETMASK										{255,255,255,0}
#define HOST_PORT											(1026)

#define UNIT_DATA_MULTICAST_IP								{224,0,2,9}
#define UNIT_DATA_MULTICAST_PORT							(1028)

#define UNIT_DEST_IP										{224,0,2,7}
#define UNIT_DEST_PORT										(1026)

/* �����ջ��С�����ȼ� */
#define WIRED_UNIT_TASK_STACK_SIZE							(2048)
#define WIRED_UNIT_TASK_PRIORITY							(15)

/* ���յ�Ԫ����BUF��С */
#define UNIT_DATA_RECEIVE_BUF_SIZE							(64)


/* һ����ѯ��ʱ��Ϊ POLLING_TIME_MS + (���ߵ�Ԫ�� * POLLING_TIME_INTERVAL_MS) */
/* ��ѯʱ�� */
#define POLLING_TIME_MS										(100)
/* ��̨��Ԫ����ѯ��� */
#define POLLING_TIME_INTERVAL_MS							(1)

/* ��ѯ��Ӧ���ж�Ϊ���ߴ��� */
#if 1   
/* ������ */
#define POLLING_NO_REPLY_OFFLINE_COUNT						(1200)
#else
#define POLLING_NO_REPLY_OFFLINE_COUNT						(5)
#endif

#define IS_APPLY_ACCESS_SYS(_type,_ph,_pl)					((_pl == RPS_APPLY_ACCESS_SYS || _pl == CHM_APPLY_ACCESS_SYS) && _type == BASIC_MSG && _ph == CONFERENCE_MODE)
#define IS_CONFIRM_ID(_type,_ph,_pl)						(_pl == UNIT_CONFIRM_ID && _type == BASIC_MSG && _ph == EDIT_ID_MODE)
#define IS_UNIT_REPLY_ONLINE(_type,_ph,_pl)					((prot.pl == RPS_REPLY_ONLINE || prot.pl == CHM_REPLY_ONLINE) && prot.type == BASIC_MSG && prot.ph == CONFERENCE_MODE)

/* ��Ԫ����ͨѶЭ���ʽ */
typedef struct {
    char header[4];
    ConfProtocol_S prot;
    uint16_t exLen;
    uint8_t exDataHead;
} NetData_S;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* API���� */
static void WiredUnit_Launch(void);
static void WiredUnit_NetDataTransmitWithExData(ConfProtocol_S *prot, uint16_t exLen, uint8_t *exData);
static void WiredUnit_NetDataTransmit(ConfProtocol_S *prot);

/* �ڲ����� */
static void WiredUnit_LaunchTask(void *pvParameters);
static void WiredUnit_EthStaListener(bool sta);
static void WiredUnit_NetDataProcessTask(void *pvParameters);
static void WiredUnit_PollingTimer(TimerHandle_t xTimer);
static void WiredUnit_AccessSystem(uint16_t id,Network_Mac_S *unitSrcMac,UnitAttr_EN attr);
//static void WiredUnit_InfoInit(void);


static void WiredUnit_NotifyConference(NOTIFY_KEYWORD kWord, ConfProtocol_S *prot);
static void WiredUnit_NotifyConferenceWithExData(NOTIFY_KEYWORD kWord, ConfProtocol_S *prot, uint16_t exLen, uint8_t *exData);
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


/* ��ѯ��ʱ�� */
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

    /* ���ڳ�ʼ�� */
    ethPara->index = eth0;
    ethPara->type = NETWORK_TYPE_ETHERNET;
    NETWORK_SET_ADDR(ethPara->ip,hostIp.addr0,hostIp.addr1,hostIp.addr2,hostIp.addr3);
    NETWORK_SET_ADDR(ethPara->gateway,hostGw.addr0,hostGw.addr1,hostGw.addr2,hostGw.addr3);
    NETWORK_SET_ADDR(ethPara->netmask,hostMask.addr0,hostMask.addr1,hostMask.addr2,hostMask.addr3);
    ethPara->ethStaListener = WiredUnit_EthStaListener;

    Network.ethConfig(ethPara);

    /* �ȴ��������� */
    while(!isEthConnected) {
        DELAY(200);
    }

    /* ���繦�ܳ�ʼ�� */
    taskPara->port = HOST_PORT;

    /* �ಥ��ַ */
    taskPara->multicastNum = 1;
    taskPara->multiPort = MALLOC(sizeof(NETWORK_PORT) * taskPara->multicastNum);
    taskPara->multiIp = MALLOC(sizeof(NETWORK_IP) * taskPara->multicastNum);
    NETWORK_SET_ADDR(taskPara->multiIp[0],multicastIp.addr0,multicastIp.addr1,multicastIp.addr2,multicastIp.addr3);
    taskPara->multiPort[0] = UNIT_DATA_MULTICAST_PORT;
    NETWORK_SET_MAC((&unitMac),0x01,0x00,0x5E,(unitIp.addr1 & 0x7F),unitIp.addr2,unitIp.addr3);

    /* ��ȡ��Ԫ����ָ�� */
	unitInfo = Conference.wiredUnitInfo();

    netTaskHandler = Network.creatTask(eth0,tEthernet,taskPara);

    /* ������Ԫ���ݴ����߳� */
    if (xTaskCreate(WiredUnit_NetDataProcessTask, "NetDataProcessTask", WIRED_UNIT_TASK_STACK_SIZE, null, WIRED_UNIT_TASK_PRIORITY, null) != pdPASS) {
        debug("create host task error\r\n");
    }

    /* ������ѯ��ʱ�� */
    pollingTimer = xTimerCreate("PollingTimer",POLLING_TIME_MS,pdTRUE,null,WiredUnit_PollingTimer);
    

    debug("Wired unit init done!!\r\n");

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

    memset(&prot,0,sizeof(ConfProtocol_S));

	switch(Conference.getSysMode()){
		/* ����ģʽ */
		case mConference:{
			/* ��ѯ��1��ID��ʼ */
			for(id = 1; id<WIRED_UNIT_MAX_ONLINE_NUM; id++) {
				/* �����Ԫ���ߣ�����ѯָ�� */
				if(unitInfo[id].online) {
					if(unitInfo[id].pollCount < POLLING_NO_REPLY_OFFLINE_COUNT) {
						Protocol.conference(&prot,id,BASIC_MSG,CONFERENCE_MODE,QUERY_UNIT,0,0);
						unitInfo[id].pollCount++;
					} else {
						Protocol.conference(&prot,id,BASIC_MSG,CONFERENCE_MODE,UNIT_OFFLINE,0,0);
						unitInfo[id].online = false;
						WiredUnit_NotifyConference(NK_CONFERENCE_MSG,&prot);
//						debug("Unit id = %d offline \r\n",id);
					}
					WiredUnit_NetDataTransmit(&prot);
					DELAY(POLLING_TIME_INTERVAL_MS);
				}
			}
		}break;
		
		/* ��IDģʽ */
		case mEditID:{
			Protocol.conference(&prot, WHOLE_BROADCAST_ID, POLLING_MSG, EDIT_ID_POLLING, CURRENT_ID,0,Conference.getCurrentEditId());
			WiredUnit_NetDataTransmit(&prot);
		}break;
		case mSign:{
			/* ��ѯ��1��ID��ʼ */
			for(id = 1; id<WIRED_UNIT_MAX_ONLINE_NUM; id++) {
				/* �����Ԫ���ߣ���δ����ǩ��������ѯָ�� */
				if(unitInfo[id].online && !unitInfo[id].sign) {
					Protocol.conference(&prot,id,POLLING_MSG,SIGN_POLLING,HOST_SIGN_POLLIGN,0,0);
					WiredUnit_NetDataTransmit(&prot);
					DELAY(POLLING_TIME_INTERVAL_MS);
				}
			}
		}break; 
		case mVote:break;
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

    ConfProtocol_S prot;

    taskBuf	= MALLOC(sizeof(Network_DataBuf_S));
    taskBuf->data = MALLOC(UNIT_DATA_RECEIVE_BUF_SIZE);
    taskBuf->maxLen = UNIT_DATA_RECEIVE_BUF_SIZE;
	
    debug("Unit device network data process task start!!\r\n");
	
	xTimerStart(pollingTimer,0);
    while(1) {

        Network.receive(netTaskHandler,taskBuf,MAX_NUM);

        if(taskBuf->len < 14) {
            continue;
        }
        netData = (NetData_S *)taskBuf->data;

        /* ���Ʋ��� */
        memcpy(&prot,&netData->prot,sizeof(ConfProtocol_S));
        prot.id = lwip_htons(prot.id);
        unitSrcMac = &taskBuf->srcMac;

        if(prot.id >= 1 && prot.id <= WIRED_UNIT_MAX_ONLINE_NUM) {

            /* ��鵥Ԫ���߱�־λ */
            if(unitInfo[prot.id].online) {
                /* ��Ԫ״̬Ϊ���� */
				
                unitInfo[prot.id].pollCount = 0;

                /* ��Ԫ�������ϵͳ */
				if(IS_APPLY_ACCESS_SYS(prot.type,prot.ph,prot.pl))	goto access_sys;

                /* ��Ԫ�ظ����� */
				else if(IS_UNIT_REPLY_ONLINE(prot.type,prot.ph,prot.pl))	goto clear_buf;


                /* ����������Ϣ���͸����������� */
                WiredUnit_NotifyConference(NK_CONFERENCE_MSG,&prot);
                goto clear_buf;
            } else {
                /* ��Ԫ״̬Ϊ���� */
				
				/* ��Ԫ�������ϵͳ */
                if(IS_APPLY_ACCESS_SYS(prot.type,prot.ph,prot.pl)) {
                    goto access_sys;
                }
				
				/* ��Ԫȷ�ϵ�ǰID(��ID),��Ҫ��������񱨸�����ID��MAC */
				else if(IS_CONFIRM_ID(prot.type,prot.ph,prot.pl)){
					WiredUnit_NotifyConferenceWithExData(NK_CONFERENCE_MSG,&prot,6,(uint8_t *)unitSrcMac);
					goto clear_buf;
				}
                /* ���Ϊ������״̬���Ҳ����������ϵͳ����ID����������ǰ���ݣ�ֱ�ӷ��ظ���Ԫ���� */
                else {
                    Protocol.conference(&prot,prot.id,BASIC_MSG,CONFERENCE_MODE, UNIT_OFFLINE,null,null);
                    WiredUnit_NetDataTransmit(&prot);
                    goto clear_buf;
                }
            }

            /* ��Ԫ����ϵͳ */
access_sys:
            if(prot.pl == RPS_APPLY_ACCESS_SYS)
                WiredUnit_AccessSystem(prot.id,unitSrcMac,aRepresentative);
            else if(prot.pl == CHM_APPLY_ACCESS_SYS)
                WiredUnit_AccessSystem(prot.id,unitSrcMac,aChairman);

        }

        /* ��ջ��� */
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

    /* �豸ID�����ߣ���MAC�������ϵͳMAC��ͬ */
    if(devInfo->online && !NETWORK_COMPARISON_MAC((&devInfo->mac),unitSrcMac)) {
        Protocol.conference(&prot,id, BASIC_MSG, CONFERENCE_MODE, ID_DUPICATE,null,null);

        WiredUnit_NetDataTransmit(&prot);
        WiredUnit_NotifyConference(NK_CONFERENCE_MSG,&prot);
    }
    /* �豸ID������,�������ߵ�MAC��ͬ */
    else {
        Protocol.conference(&prot,id, BASIC_MSG, CONFERENCE_MODE, UNIT_ACCESS_SYS,null,null);
		WiredUnit_NetDataTransmit(&prot);

		devInfo->attr = attr;
        devInfo->pollCount = 0;
        NETWORK_SET_MAC((&devInfo->mac),unitSrcMac->mac0,unitSrcMac->mac1,unitSrcMac->mac2,unitSrcMac->mac3,unitSrcMac->mac4,unitSrcMac->mac5);

		/* ����豸�����Ѿ����ߣ��Ͳ�����Ԫ����֪ͨ���������� */
		if(!devInfo->online){
			WiredUnit_NotifyConference(NK_CONFERENCE_MSG,&prot);
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
static void WiredUnit_NotifyConferenceWithExData(NOTIFY_KEYWORD kWord, ConfProtocol_S *prot, uint16_t exLen, uint8_t *exData) {

    Notify_S *notify;

    if(prot == null || (exLen != 0 && exData == null))
        return;

    notify = MALLOC(sizeof(Notify_S) + exLen);

    notify->nSrc = sWiredUnit;

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
static void WiredUnit_NotifyConference(NOTIFY_KEYWORD kWord, ConfProtocol_S *prot) {
    WiredUnit_NotifyConferenceWithExData(kWord, prot, null, null);
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


