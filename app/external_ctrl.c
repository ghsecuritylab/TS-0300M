/**
 *
 *	@name				external_ctrl.c
 *	@author 			KT
 *	@date 				2019/07/31
 *	@brief				
 *  @include			external_ctrl.h
 *
 *  @API				
 *
 *  @description   		
 *
 **/
/*******************************************************************************
 * includes
 ******************************************************************************/
/* CLIB*/
#include "stdio.h"
#include "ctype.h"
 
/* OS */
#include "FreeRTOS.h"
#include "timers.h"

/* LWIP */
#include "lwip\sys.h"
#include "mdns.h"

/* API */
#include "app.h"
#include "network.h"
#include "ram.h"

#include "external_ctrl.h"
#include "conference.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**** 网络相关参数定义 ****/
#define HOST_LOCAL_IP								{172,16,14,117}
#define HOST_GATEWAY								{172,16,14,254}
#define HOST_NETMASK								{255,255,255,0}
#define HOST_PORT									(50000)

/* 网络接口 */
#define NETWORK_ENET_TYPE							eth0

/* 网络类型 */
#define NETWORK_TYPE								NETWORK_TYPE_TCPIP
 
/* 任务堆栈大小及优先级 */
#define EXTERNAL_CTRL_TASK_STACK_SIZE				(1024)
#define EXTERNAL_CTRL_TASK_PRIORITY					(12)

/* 接收网络数据BUF大小 */
#define EXTERNAL_CTRL_DATA_RECEIVE_BUF_SIZE			(260)

/* 全数字会议协议数据包最小长度 */
#define CTRL_CMD_MIN_LEN							(13)

/* 最大分包数 */
#define DATA_PACK_MAX_NUM							(EXTERNAL_CTRL_DATA_RECEIVE_BUF_SIZE / CTRL_CMD_MIN_LEN)

/* 外部控制——主机协议结构 */
//#pragma pack(1)	/* 单字节对齐 */
typedef struct{
	uint8_t header[2];
	uint8_t len;
	ConfProtocol_S prot;
	uint8_t exDataHead;
}ExCtrlData_S;
//#pragma pack()

/* 协议数据捡包 */
typedef struct {
	uint8_t packNum;
	ExCtrlData_S *ctrlData[DATA_PACK_MAX_NUM];
}DataPack_S;

//static PcCtrl_S pcCtrl;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
 /* API调用 */
static void ExternalCtrl_Launch(void);
static void ExternalCtrl_ctrlDataTransmit(EXE_DEST dest, ConfProtocol_S *prot);
static void ExternalCtrl_ctrlDataTransmitWithExData(EXE_DEST dest, ConfProtocol_S *prot, uint16_t exLen, uint8_t *exData);


/* 内部调用 */
static void ExternalCtrl_LaunchTask(void *pvParameters);
static void ExternalCtrl_EthStaListener(bool sta);
static DataPack_S *ExternalCtrl_FetchDataFromBuf(Network_DataBuf_S *taskBuf);
static void ExternalCtrl_NotifyConference(NotifySrcType_EN nSrc, ConfProtocol_S *prot);
static void ExternalCtrl_NotifyConferenceWithExData(NotifySrcType_EN nSrc, ConfProtocol_S *prot, uint16_t exLen, uint8_t *exData);
static void ExternalCtrl_ReplyHeartbeat(EXE_DEST dest);
static void ExternalCtrl_ReplyQuery(EXE_DEST dest, uint8_t para);

static void PcCtrl_ProcessTask(void *pvParameters);
static void WebCtrl_ProcessTask(void *pvParameters);
/*******************************************************************************
 * Variables
 ******************************************************************************/

 
/* 网络参数变量 */
static NETWORK_IP hostIp = HOST_LOCAL_IP;
static NETWORK_GW hostGw = HOST_GATEWAY;
static NETWORK_MASK hostMask = HOST_NETMASK;
static NETWORK_PORT	hostPort = HOST_PORT;

/* 网线连接检测标志 */
static bool isEthConnected; 

/* 网线连接检测标志 */
static bool isPcCtrlEnable;
static bool isWebCtrlEnable;
static bool isUartCtrlEnable;

/* 网络任务控制句柄 */
static Network_TaskHandler_S *pcNetTaskHandler;
static Network_TaskHandler_S *webNetTaskHandler;

/* 控制指令数据中捡取指令数据包 */
static DataPack_S fetchDataPack;
/* 控制指令处理信号量 */
static SemaphoreHandle_t ctrlProcessSemaphore;

/* 网页文件 */
extern const HTTPSRV_FS_DIR_ENTRY httpsrv_fs_data[];

ExternalCtrl_S ExternalCtrl = {
	.launch = ExternalCtrl_Launch,
	.transmit = ExternalCtrl_ctrlDataTransmit,
	.transWithExData = ExternalCtrl_ctrlDataTransmitWithExData,
};
/*******************************************************************************
 * Code
 ******************************************************************************/
/**
* @Name  		ExternalCtrl_Launch
* @Author  		KT
* @Description 	
* @para    		
*				
*
* @return		
*/
static void ExternalCtrl_Launch(void){
	if (xTaskCreate(ExternalCtrl_LaunchTask, "ExternalCtrlLaunchTask", EXTERNAL_CTRL_TASK_STACK_SIZE, null, EXTERNAL_CTRL_TASK_PRIORITY, null) != pdPASS)
    {
        debug("create launch task error\r\n");
    }
}


/**
* @Name  		ExternalCtrl_LaunchTask
* @Author  		KT
* @Description 	
* @para    		
*				
*
* @return		
*/
static void ExternalCtrl_LaunchTask(void *pvParameters){
	Network_EthPara_S *ethPara;

	isEthConnected = false;

	ethPara = MALLOC(sizeof(Network_EthPara_S));

	/* 网口初始化 */
	ethPara->index = NETWORK_ENET_TYPE;
	ethPara->type = NETWORK_TYPE;
	NETWORK_SET_ADDR(ethPara->ip,hostIp.addr0,hostIp.addr1,hostIp.addr2,hostIp.addr3);
	NETWORK_SET_ADDR(ethPara->gateway,hostGw.addr0,hostGw.addr1,hostGw.addr2,hostGw.addr3);
	NETWORK_SET_ADDR(ethPara->netmask,hostMask.addr0,hostMask.addr1,hostMask.addr2,hostMask.addr3);
	ethPara->ethStaListener = ExternalCtrl_EthStaListener;
	
	Network.ethConfig(ethPara);
	
	/* 初始化信号量 */
	ctrlProcessSemaphore = xSemaphoreCreateMutex();
	
	/* 等待网络连接 */
	while(!isEthConnected){
		DELAY(200);
	}
	
	/* 启动PC处理线程 */
	if (xTaskCreate(PcCtrl_ProcessTask, "PCProcessTask", EXTERNAL_CTRL_TASK_STACK_SIZE, null, EXTERNAL_CTRL_TASK_PRIORITY, null) != pdPASS)
    {
        debug("create PC data receive task error\r\n");
    }
	
	/* 启动WEB处理线程 */
	if (xTaskCreate(WebCtrl_ProcessTask, "WEBProcessTask", EXTERNAL_CTRL_TASK_STACK_SIZE, null, EXTERNAL_CTRL_TASK_PRIORITY, null) != pdPASS)
    {
        debug("create WEB data receive task error\r\n");
    }
	
	isPcCtrlEnable = isWebCtrlEnable = isUartCtrlEnable = false;
	
	vTaskDelete(null);
}

/**
* @Name  		ExternalCtrl_EthStaListener
* @Author  		KT
* @Description 	
* @para    		
*				
*
* @return		
*/
static void ExternalCtrl_EthStaListener(bool sta){
	isEthConnected = sta;
	debug("External control (net port) %s \r\n",sta ? "connected" : "disconnected");
}



/**
* @Name  		ExternalCtrl_FetchDataFromBuf
* @Author  		KT
* @Description 	
* @para    		
*				
*
* @return		
*/
static DataPack_S *ExternalCtrl_FetchDataFromBuf(Network_DataBuf_S *buf){
	DataPack_S *dataPack = &fetchDataPack;
	uint16_t i;
	uint8_t *data;

	dataPack->packNum = 0;
	memset(dataPack->ctrlData,0,DATA_PACK_MAX_NUM);
	
	ERR_CHECK(buf != null,return dataPack);
	ERR_CHECK(buf->data != null,return dataPack);
	ERR_CHECK(buf->len >= CTRL_CMD_MIN_LEN,return dataPack);
		
	data = buf->data;
	
	/* 检索包头并根据包长度验证包尾*/
	/*	(taskBuf-> - CTRL_CMD_MIN_LEN)这个操作是因为一个包长度不应
		该小于CTRL_CMD_MIN_LEN，因此检索包头到数据包最后的字节就不需要了*/
	for(i = 0;i <= buf->len - CTRL_CMD_MIN_LEN;i++){
		if(data[i] == 0xAA && data[i+1] == 0xEE && \
		   data[i + 3 + data[i+2]] == 0xEE && \
		   data[i + 4 + data[i+2]] == 0xFC){

		   	/* 保存索引指针到数据包，包数量加一 */
			dataPack->ctrlData[dataPack->packNum] = (ExCtrlData_S *)(&data[i]);
			dataPack->packNum++;
			/* 数据索引跳过已经检索到的数据段 */
			i = i + 4 + data[i+2];
		}
	}
	return dataPack;
}


/**
* @Name  		ExternalCtrl_DataProcess
* @Author  		KT
* @Description 	
* @para    		
*				
*
* @return		
*/
static void ExternalCtrl_DataProcess(NotifySrcType_EN nSrc, ExCtrlData_S *ctrlData){
	ConfProtocol_S prot;
	uint8_t exLen = 0, *exData = null;
	
	ERR_CHECK(ctrlData != null,return);	

	memcpy(&prot,&ctrlData->prot,sizeof(ConfProtocol_S));
	prot.id = lwip_htons(prot.id);

	/* 将需要频繁操作或快速回复参数的操作放在接收线程直接处理，其他的发送给会议任务线程处理 */
	/* 回复心跳 */
	if(prot.ph == HEARTBEAT && prot.pl == HEARTBEAT && prot.type == PC_MSG ){
		ExternalCtrl_ReplyHeartbeat(nSrc);
		return;
	}
	/* 回复状态查询 */
	else if(prot.ph >= QUERY_PRIOR_SIGN && prot.ph <= QUERY_PRIOR_SCAN && prot.type == PC_MSG ){
		ExternalCtrl_ReplyQuery(nSrc,prot.ph);
		return;	
	}

	/* 通知会议任务 */
	if(ctrlData->len > sizeof(ConfProtocol_S)){
		exLen = ctrlData->len - sizeof(ConfProtocol_S);
		exData = MALLOC(exLen);
		memcpy(exData,&ctrlData->exDataHead,exLen);
		ExternalCtrl_NotifyConferenceWithExData(nSrc,&prot,exLen,exData);
	}
	else
		ExternalCtrl_NotifyConference(nSrc,&prot);
}

/** 
* @Name  		ExternalCtrl_NotifyConferenceWithExData
* @Author  		KT
* @Description 	
* @para    		
*				
*
* @return		
*/ 
static void ExternalCtrl_NotifyConferenceWithExData(NotifySrcType_EN nSrc, ConfProtocol_S *prot, uint16_t exLen, uint8_t *exData){
	Notify_S *notify;
	
	ERR_CHECK(prot != null,return);
	ERR_CHECK(!(exLen != 0 && exData == null),return);
		
	notify = MALLOC(sizeof(Notify_S) + exLen);
	
	notify->nSrc = nSrc;
//	notify->kWord = kWord;
	memcpy(&notify->prot.conference,prot,sizeof(ConfProtocol_S));
	notify->exLen = exLen;
	
	if(exLen != 0){
		memcpy(&notify->exDataHead,exData,exLen);
	}
	
	Conference.notify(notify);
}

/** 
* @Name  		ExternalCtrl_NotifyConference
* @Author  		KT
* @Description 	
* @para    		
*				
*
* @return		
*/ 
static void ExternalCtrl_NotifyConference(NotifySrcType_EN nSrc, ConfProtocol_S *prot){
	ExternalCtrl_NotifyConferenceWithExData(nSrc, prot, null, null);
}



/**
* @Name  		ExternalCtrl_ctrlDataTransmitWithExData
* @Author  		KT
* @Description 	
* @para    		
*				
*
* @return		
*/
static void ExternalCtrl_ctrlDataTransmitWithExData(EXE_DEST dest, ConfProtocol_S *prot, uint16_t exLen, uint8_t *exData){
	Network_DataBuf_S *taskBuf;
	ExCtrlData_S *ctrlData;
	uint8_t dataLen;
	
	ERR_CHECK(prot != null,return);
	ERR_CHECK(!(exLen != 0 && exData == null),return);
	ERR_CHECK(isEthConnected && (isPcCtrlEnable || isWebCtrlEnable),return);
//	ERR_CHECK((isPcCtrlEnable || isWebCtrlEnable || isUartCtrlEnable),return);
		
	dataLen = exLen + CTRL_CMD_MIN_LEN;
	ctrlData = MALLOC(dataLen);
	taskBuf = MALLOC(sizeof(Network_DataBuf_S));
	memset(ctrlData,0,dataLen);
	
	ctrlData->header[0] = 0xAA;
	ctrlData->header[1] = 0xEE;
	ctrlData->len = dataLen - 5;
	memcpy(&ctrlData->prot,prot,sizeof(ConfProtocol_S));
	ctrlData->prot.id = lwip_htons(ctrlData->prot.id);
	ctrlData->prot.sec = lwip_htons(ctrlData->prot.sec);
	if(exLen != 0){
		memcpy(&ctrlData->exDataHead,exData,exLen);
	}
	((uint8_t *)ctrlData)[dataLen - 2] = 0xEE; 
	((uint8_t *)ctrlData)[dataLen - 1] = 0xFC; 
	
	taskBuf->len = dataLen;
	taskBuf->data = (uint8_t *)ctrlData;
	
	if((dest & kType_NotiSrc_PC) && isPcCtrlEnable)
		Network.transmit(pcNetTaskHandler,taskBuf);
	
	if((dest & kType_NotiSrc_Web) && isWebCtrlEnable){
		taskBuf->webType = tWebsocket;
		taskBuf->wsType = WS_DATA_BINARY;
		Network.transmit(webNetTaskHandler,taskBuf);
	}
	
	FREE(ctrlData);
	FREE(taskBuf);
}

/**
* @Name  		ExternalCtrl_ctrlDataTransmitWithExData
* @Author  		KT
* @Description 	
* @para    		
*				
*
* @return		
*/
static void ExternalCtrl_ctrlDataTransmit(EXE_DEST dest, ConfProtocol_S *prot){
	ExternalCtrl_ctrlDataTransmitWithExData(dest, prot, null, null);
}


/**
* @Name  		ExternalCtrl_ReplyHeartbeat
* @Author  		KT
* @Description 	
* @para    		
*				
*
* @return		
*/
static void ExternalCtrl_ReplyHeartbeat(EXE_DEST dest){
	UnitOnlineNum onlineNum;
	ConfProtocol_S prot;
	
	Conference.getOnlineNum(&onlineNum);
	
	Protocol.conference(&prot,WHOLE_BROADCAST_ID,WIRED_UNIT_NUM,0,onlineNum.interpreter,onlineNum.wiredChm,onlineNum.wiredRps);
	ExternalCtrl_ctrlDataTransmit(dest,&prot);
	Protocol.conference(&prot,WHOLE_BROADCAST_ID,WIFI_UNIT_NUM,0,0,onlineNum.wifiChm,onlineNum.wifiRps);
	ExternalCtrl_ctrlDataTransmit(dest,&prot);
}

/**
* @Name  		ExternalCtrl_ReplyQuery
* @Author  		KT
* @Description 	
* @para    		
*				
*
* @return		
*/
static void ExternalCtrl_ReplyQuery(EXE_DEST dest, uint8_t para){
	ConfProtocol_S prot;
	uint8_t sta;

	sta = (uint8_t)Conference.getSysMode();
	Protocol.conference(&prot, WHOLE_BROADCAST_ID, PC_MSG, para, 0x01, sta,null);
	ExternalCtrl_ctrlDataTransmit(dest,&prot);
}
/*****************************************  PC  ****************************************************************/
/**
* @Name  		PcCtrl_TcpStaListener
* @Author  		KT
* @Description 	
* @para    		
*				
*
* @return		
*/
static void PcCtrl_TcpStaListener(bool sta){
	isPcCtrlEnable = sta;
	debug("PC control is %s \r\n",sta ? "online" : "offline");
}

/**
* @Name  		PcCtrl_ProcessTask
* @Author  		KT
* @Description 	
* @para    		
*				
*
* @return		
*/
static void PcCtrl_ProcessTask(void *pvParameters){
	Network_TcpTaskPara_S *taskPara;
	Network_DataBuf_S *taskBuf;
	DataPack_S *dataPack;
	
	uint32_t index;
	
	taskBuf	= MALLOC(sizeof(Network_DataBuf_S));
	taskBuf->data = MALLOC(EXTERNAL_CTRL_DATA_RECEIVE_BUF_SIZE);
	taskBuf->maxLen = EXTERNAL_CTRL_DATA_RECEIVE_BUF_SIZE;
	taskBuf->len = 0;
	
	/* 初始化网络任务 */
	taskPara = MALLOC(sizeof(Network_TcpTaskPara_S));
	taskPara->port = hostPort;
	taskPara->type = tServer;
	taskPara->tcpListener = PcCtrl_TcpStaListener;
	pcNetTaskHandler = Network.creatTask(NETWORK_ENET_TYPE,tTcp,taskPara);
	
	debug("PC control process task start!!\r\n");
	
	while(1){
		Network.receive(pcNetTaskHandler,taskBuf,MAX_NUM);
		
		xSemaphoreTake(ctrlProcessSemaphore, MAX_NUM);
		dataPack = ExternalCtrl_FetchDataFromBuf(taskBuf);
		if(dataPack->packNum > 0){
			for(index = 0;index < dataPack->packNum;index++){
				ExternalCtrl_DataProcess(kType_NotiSrc_PC,dataPack->ctrlData[index]);
			}
		}
		xSemaphoreGive(ctrlProcessSemaphore);
		
		taskBuf->len = 0;
		memset(taskBuf->data,0,EXTERNAL_CTRL_DATA_RECEIVE_BUF_SIZE);
		
	}
}

	

/*****************************************  WEB  ****************************************************************/
/**
* @Name  		WebCtrl_TcpStaListener
* @Author  		KT
* @Description 	
* @para    		
*				
*
* @return		
*/
static void WebCtrl_WsStaListener(bool sta){
	isWebCtrlEnable = sta;
	debug("Websocket is %s \r\n",sta ? "online" : "offline");
}

/**
* @Name  		WebCtrl_ProcessTask
* @Author  		KT
* @Description 	
* @para    		
*				
*
* @return		
*/
static void WebCtrl_ProcessTask(void *pvParameters){
	Network_HttpTaskPara_S *taskPara;
	Network_DataBuf_S *taskBuf;
	DataPack_S *dataPack;
	uint32_t index;
	
	taskBuf	= MALLOC(sizeof(Network_DataBuf_S));
	taskBuf->data = MALLOC(EXTERNAL_CTRL_DATA_RECEIVE_BUF_SIZE);
	taskBuf->maxLen = EXTERNAL_CTRL_DATA_RECEIVE_BUF_SIZE;
	taskBuf->len = 0;
	
	/* 配置HTTP网络任务 */
	taskPara = MALLOC(sizeof(Network_HttpTaskPara_S));
	taskPara->httpFsDir = httpsrv_fs_data;
	taskPara->rootDir = "";
	taskPara->indexPage = "/index.html";
	
	/* 端口配置为null 表示使用默认端口 */
	taskPara->port = null;

	/* 使能CGI功能并配置 */
#if 0
	taskPara->cgi.enable = true;
	taskPara->cgi.postName = "post_input";
#endif

	/* 使能Websocket功能并配置 */
	taskPara->websocket.enable = true;
	taskPara->websocket.wsListener = WebCtrl_WsStaListener;

	/* 初始化网络任务 */
	webNetTaskHandler = Network.creatTask(NETWORK_ENET_TYPE,tHttp,taskPara);
	
	debug("WEB control process task start!!\r\n");
	
	while(1){
		Network.receive(webNetTaskHandler,taskBuf,MAX_NUM);
		
		if(taskBuf->webType == tWebsocket && taskBuf->wsType == WS_DATA_BINARY){
			xSemaphoreTake(ctrlProcessSemaphore, MAX_NUM);
			dataPack = ExternalCtrl_FetchDataFromBuf(taskBuf);
			
			if(dataPack->packNum > 0){
				for(index = 0;index < dataPack->packNum;index++){
					ExternalCtrl_DataProcess(kType_NotiSrc_Web,dataPack->ctrlData[index]);
				}
			}
			xSemaphoreGive(ctrlProcessSemaphore);
		}
		
		taskBuf->len = 0;
		memset(taskBuf->data,0,EXTERNAL_CTRL_DATA_RECEIVE_BUF_SIZE);
	}
}
/*****************************************  Uart  ****************************************************************/
