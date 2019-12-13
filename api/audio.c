/**
 *
 *	@FileName							audio.c
 *	@Author								KT
 *	@CreationTime						2019/05/15
 *	@Description						音频录放功能
 *
 * 	@Include							audio.h
 *
 *	@API
 *
 *  @Modify								2019/12/05 by KT
 **/
/*******************************************************************************
 * includes
 ******************************************************************************/
/* DRIVER */
#include "mp3/wt2000a.h"

/* OS */
#include "FreeRTOS.h"
#include "timers.h"
#include "semphr.h"

/* API */
#include "ram.h"
#include "audio.h"

/* HAL */
#include "hal_gpio.h"
#include "hal_aud_codec.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* 继电器控制 */
#define RELAY_CTRL_GPIO									(GPIO1)
#define RELAY_CTRL_PIN									(1)

/* USB电源控制 */
#define USB_POWER_CTRL_GPIO								(GPIO1)
#define USB_POWER_CTRL_PIN								(25)


/* 继电器控制外部USB接口连接到MCU或WT2000 */
#define MCU												(0)
#define WT2000											(1)

#define USB_CONNET_TO(_target)							HAL_SetGpioLevel(SwitchCtrlIo, _target);

#define USB_POWER_ENABLE(_bool)							HAL_SetGpioLevel(UsbPowerCtrlIo, _bool);

/* 音频录放功能命令队列长度 */
#define AUDIO_CMD_QUEUE_LEN      	 					(10)
#define AUDIO_CMD_ITEM_SIZE    							(sizeof(AudCmd_S))

/* 音频录放功能线程堆栈大小、优先级 */
#define AUDIO_TASK_STACK								(1024)
#define AUDIO_TASK_PRIORITY								(9)

/* 运行计时器计时间隔 */
#define AUDIO_RUN_TIME_MS								(1000 - 100)

/* 录音文件指定目录文件名 */
#define AUDIO_RECORD_DIR								"AUREC"

/* 默认等待USB连接时间(秒) */
#define AUDIO_WAIT_USB_CONNECT_TIME						(10)

/* 音频录放控制命令类型 */
typedef enum {
    tNone = 0,
    tRecord,
    tStopRec,
    tPlayPause,
    tPlayNext,
    tPlayPrevious,
    tStopPlay,
} AudCmdType_EN;



/* 音频录放控制命令结构体 */
typedef struct {
    AudCmdType_EN type;
    char *fileName;
} AudCmd_S;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* API */
static void Audio_Launch(void);
static void Audio_RecordStart(const char *fileName);
static void Audio_RecordStop(void);
static void Audio_PlayPause(void);
static void Audio_PlayNext(void);
static void Audio_PlayPrevious(void);
static void Audio_PlayStop(void);
static void Audio_SetListener(Audio_StaListener listener);



/* INTERNAL */
static void Audio_LaunchTask(void *pvParameters);
static void Audio_CmdProcecssTask(void *pvParameters);
static void Audio_Wt2000Callback(uint8_t data);
static uint8_t Audio_WaitAck(uint8_t *data);
static bool Audio_WaitUsbConnect(uint8_t waitTime);
static void Audio_RunningTimer(TimerHandle_t xTimer);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* 继电器控制、电源控制GPIO */
static HAL_GpioIndex SwitchCtrlIo;
static HAL_GpioIndex UsbPowerCtrlIo;

/* 接收发送二值信号量 */
static SemaphoreHandle_t UartCmdRecvSem;
static SemaphoreHandle_t UartCmdSendSem;

/* USB控制任务队列 */
static QueueHandle_t AudioCmdQueue;

/* 运行定时器 */
static TimerHandle_t AudRunTimer;

/* 串口接收缓存、计数 */
static uint8_t DriveRetData[32];
static uint8_t DriveRetCont = 0;

/* 状态监听函数 */
static Audio_StaListener Listener = null;

/* API */
Audio_S Audio = {
    .launch = Audio_Launch,
    .playPause = Audio_PlayPause,
    .next = Audio_PlayNext,
    .previous = Audio_PlayPrevious,
    .record = Audio_RecordStart,
    .stopRec = Audio_RecordStop,
    .stopPlay = Audio_PlayStop,
    .setListener = Audio_SetListener,

};
/*******************************************************************************
 * Code
 ******************************************************************************/
static void Audio_Launch(void)
{
    if (xTaskCreate(Audio_LaunchTask, "Audio_LaunchTask", AUDIO_TASK_STACK,null, AUDIO_TASK_PRIORITY, NULL) != pdPASS) {
        debug("create audio task error\r\n");
    }
}

//static void Audio_UsbSwitch(uint8_t target){
//	if(target == MCU){
//	
//	}else if(target == )
//}

static void Audio_LaunchTask(void *pvParameters)
{
    /* 初始化GPIO */
    SwitchCtrlIo = HAL_GpioInit(RELAY_CTRL_GPIO, RELAY_CTRL_PIN, kGPIO_DigitalOutput, null, null);
    UsbPowerCtrlIo = HAL_GpioInit(USB_POWER_CTRL_GPIO, USB_POWER_CTRL_PIN, kGPIO_DigitalOutput, null, null);

    /* 默认连接 */
    USB_CONNET_TO(MCU);
	
	/* 打开U盘电源 */
//    HAL_SetGpioLevel(UsbPowerCtrlIo, true);
	USB_POWER_ENABLE(true);

    /* 初始化音频编解码器 */
    HAL_AudCodecInit(tNau88c22);

    /* 初始化信号量 */
    UartCmdRecvSem = xSemaphoreCreateBinary();
    UartCmdSendSem = xSemaphoreCreateBinary();
	 xSemaphoreGive(UartCmdSendSem);

    /* 任务队列初始化 */
    AudioCmdQueue = xQueueCreate(AUDIO_CMD_QUEUE_LEN,AUDIO_CMD_ITEM_SIZE);

    /* 关闭串口接收 */
    Wt2000_AckRecvEnable(false);

    /* 初始化配置WT2000 */
    Wt2000_CfgReturnNecessary();
    DELAY(200);
    Wt2000_CfgUsbDisk();
    DELAY(200);
    Wt2000_CfgMp3Rate();
    DELAY(200);
    Wt2000_CfgDefVolume();

    /* 设置回调函数 */
    Wt2000_SetAckCallback(Audio_Wt2000Callback);

    /* 启动初始化线程 */
    if (xTaskCreate(Audio_CmdProcecssTask, "Audio_ProcecssTask", AUDIO_TASK_STACK,null, AUDIO_TASK_PRIORITY, NULL) != pdPASS) {
        debug("create audio process task error\r\n");
    }

    vTaskDelete(null);

    while(1);
}

static void Audio_CmdProcecssTask(void *pvParameters)
{
	AudState_S *audState;
    AudCmd_S cmd;
    uint8_t *ack;

    /* ACK接收缓存分配内存         */
    ack = MALLOC(30);
	
	/* 音频录放状态句柄 */
	audState = MALLOC(sizeof(AudState_S));
	audState->state = kStatus_Aud_Idle;

	/* 初始化定时器 */
    AudRunTimer = xTimerCreate("AudRunTimer",AUDIO_RUN_TIME_MS,pdTRUE,audState,Audio_RunningTimer);

    while(1) {
        /* 等待任务队列 */
        xQueueReceive(AudioCmdQueue, &cmd, MAX_NUM);
        /* 获取串口发送信号量 */
        xSemaphoreTake(UartCmdSendSem, MAX_NUM);

        switch(cmd.type) {
        case tRecord: {
            if(cmd.fileName == null)
                break;

			memset(audState->recFile,0,25);
			if(strlen(cmd.fileName) > 22){
				memcpy(audState->recFile,cmd.fileName,22);
			}else{
				memcpy(audState->recFile,cmd.fileName,strlen(cmd.fileName));
			}
			FREE(cmd.fileName);

            USB_CONNET_TO(WT2000);
			
            if(!Audio_WaitUsbConnect(AUDIO_WAIT_USB_CONNECT_TIME)){
				audState->state = kStatus_Aud_UsbTimeout;
				if(Listener != null) 
                        Listener(audState);
				audState->state = kStatus_Aud_Idle;
				USB_CONNET_TO(MCU);
				break;
			}

            if(audState->state != kStatus_Aud_Idle && audState->state != kStatus_Aud_Pause)
                break;
			

            Wt2000_AudioRecord(AUDIO_RECORD_DIR,(const char *)audState->recFile);
            Audio_WaitAck(ack);
            if(ack[0] == 0) {
				audState->runTime = 0;
                audState->state = kStatus_Aud_Recording;
                xTimerStart(AudRunTimer,0);
            } else {
				audState->state = kStatus_Aud_StarRecErr;
                if(Listener != null) {
                    Listener(audState);
                }
                audState->state = kStatus_Aud_Idle;
				USB_CONNET_TO(MCU);
            }
			
			
        }
        break;
		
		
        case tStopRec: {
            Wt2000_RecordStop();
            Audio_WaitAck(ack);
            xTimerStop(AudRunTimer,0);
            audState->runTime = 0;

			DELAY(3000);

			audState->state = kStatus_Aud_RecStoped;
            if(Listener != null) {
                Listener(audState);
            }
			audState->state = kStatus_Aud_Idle;
			
			USB_CONNET_TO(MCU);
        }
        break;

        /* 播放 */
        case tPlayPause: {
            USB_CONNET_TO(WT2000);

            /* 等待USB挂载 */
            if(!Audio_WaitUsbConnect(AUDIO_WAIT_USB_CONNECT_TIME))	{
				audState->state = kStatus_Aud_UsbTimeout;
				if(Listener != null) 
                        Listener(audState);
				audState->state = kStatus_Aud_Idle;
				USB_CONNET_TO(MCU);
				break;
			}

            if(audState->state == kStatus_Aud_Idle || audState->state == kStatus_Aud_Pause) {
                Wt2000_AudioPlayPause();
                Audio_WaitAck(ack);
                if(ack[0] == 0) {
                    audState->state = kStatus_Aud_Playing;
                    xTimerStart(AudRunTimer,0);
                } else {
					audState->state = kStatus_Aud_StarPlayErr;
                    if(Listener != null) 
                        Listener(audState);
                    audState->state = kStatus_Aud_Idle;
                }
            }

            else if(audState->state == kStatus_Aud_Playing) {
                Wt2000_AudioPlayPause();
                Audio_WaitAck(ack);
                audState->state = kStatus_Aud_Pause;
                if(Listener != null) {
                    Listener(audState);
                }
            }
        }
        break;

        /* 播放下一首 */
        case tPlayNext: {
            USB_CONNET_TO(WT2000);

            if(audState->state != kStatus_Aud_Playing && audState->state != kStatus_Aud_Pause)	break;

            /* 等待USB挂载 */
            if(!Audio_WaitUsbConnect(AUDIO_WAIT_USB_CONNECT_TIME)){
				audState->state = kStatus_Aud_UsbTimeout;
				if(Listener != null) 
                        Listener(audState);
				audState->state = kStatus_Aud_Idle;
				break;
			}

            Wt2000_PlayNext();
            Audio_WaitAck(ack);
            audState->runTime = 0;
        }
        break;

        /* 播放上一首 */
        case tPlayPrevious: {
            USB_CONNET_TO(WT2000);

            if(audState->state != kStatus_Aud_Playing && audState->state != kStatus_Aud_Pause)	break;

            /* 等待USB挂载 */
            if(!Audio_WaitUsbConnect(AUDIO_WAIT_USB_CONNECT_TIME)){
				audState->state = kStatus_Aud_UsbTimeout;
				if(Listener != null) 
                        Listener(audState);
				audState->state = kStatus_Aud_Idle;
				break;
			}

            Wt2000_PlayPrevious();
            Audio_WaitAck(ack);
            audState->runTime = 0;
        }
        break;

        /* 停止 */
        case tStopPlay: {
            Wt2000_PlayStop();
            Audio_WaitAck(ack);

            xTimerStop(AudRunTimer,0);
            audState->runTime = 0;
            audState->state = kStatus_Aud_Idle;

			USB_CONNET_TO(MCU);
        }
        break;

        default:
            break;
        }

        /* 释放信号量 */
        xSemaphoreGive(UartCmdSendSem);
    }
}

static void Audio_SetListener(Audio_StaListener listener){
	Listener = listener;
}


static void Audio_SendCmdToTask(AudCmdType_EN type, char *fileName)
{
    AudCmd_S cmd;

    cmd.type = type;
    cmd.fileName = fileName;
    xQueueSend(AudioCmdQueue, &cmd, MAX_NUM);
}

static void Audio_RecordStart(const char *fileName)
{
    char *fname;
    ERR_CHECK(fileName != 0, return);

    fname = MALLOC(strlen(fileName) + 1);
    strcpy(fname,fileName);
    Audio_SendCmdToTask(tRecord,fname);
}

static void Audio_RecordStop(void)
{
    Audio_SendCmdToTask(tStopRec,null);
}

static void Audio_PlayPause(void)
{
    Audio_SendCmdToTask(tPlayPause,null);
}

static void Audio_PlayNext(void)
{
    Audio_SendCmdToTask(tPlayNext,null);
}

static void Audio_PlayPrevious(void)
{
    Audio_SendCmdToTask(tPlayPrevious,null);
}

static void Audio_PlayStop(void)
{
    Audio_SendCmdToTask(tStopPlay,null);
}





static uint8_t Audio_WaitAckByTime(uint8_t *data,uint32_t time)
{
    uint8_t i,count = 0;
    ERR_CHECK(data != 0, return 0);

    Wt2000_AckRecvEnable(true);

    /* 获取到信号量后延时，然后再获取一次信号量（不等待），
    	清除串口中断接收多字节时的重复信号量 */
    xSemaphoreTake(UartCmdRecvSem, MAX_NUM);
    DELAY(time);
    xSemaphoreTake(UartCmdRecvSem, 1);

    if(DriveRetCont == 0)
        return 0;

    count = DriveRetCont;
    memcpy(data,DriveRetData,count);
    DriveRetCont = 0;
#if 0
    for(i = 0; i < count; i++)
        debug("%X ",data[i]);
    debug("\r\n");
#endif
    Wt2000_AckRecvEnable(false);
    return count;
}

static uint8_t Audio_WaitAck(uint8_t *data)
{
    return Audio_WaitAckByTime(data,30);
}


static void Audio_Wt2000Callback(uint8_t data)
{
    portBASE_TYPE taskToWake = pdFALSE;

    DriveRetData[DriveRetCont++] = data;
    xSemaphoreGiveFromISR(UartCmdRecvSem, &taskToWake);
}

static bool Audio_WaitUsbConnect(uint8_t waitTime)
{
    uint8_t ack[5],cont;

    do {
        Wt2000_QueryState(kType_WtCmd_LinkSta);
        cont = Audio_WaitAck(ack);
        if(cont > 0 && ack[0] == kType_WtCmd_LinkSta && ack[1] == 2) {
            return true;
        } else {
//            if(Listener != null)
//                Listener(kStatus_Aud_UsbTimeout,null,null);
            debug("Usb connect timeout\r\n");
            return false;
        }
    } while(waitTime--);
}

static bool Audio_CheckUsbConnect(void){
	return Audio_WaitUsbConnect(0);
}

static void Audio_RunningTimer(TimerHandle_t xTimer)
{
	AudState_S *audState;
    uint8_t ack[5];
	bool usbConnect;
	WtPlaySta_EN playSta;

	audState = pvTimerGetTimerID(xTimer);

    xSemaphoreTake(UartCmdSendSem, MAX_NUM);

	/* 检查USB连接 */
	usbConnect = Audio_CheckUsbConnect();
	/* USB断开 */
	if(!usbConnect){
		Audio_PlayStop();
		xSemaphoreGive(UartCmdSendSem);
		audState->state = kStatus_Aud_UsbBroken;
		if(Listener != null)
        	Listener(audState);
		debug("Usb was broken!! \r\n");
		return;
	}

	/* 检查音频录放状态 */
	Wt2000_QueryState(kType_WtCmd_State);
	Audio_WaitAck(ack);
	if(ack[0] == kType_WtCmd_State){
        playSta = ack[1];
	}	

    switch(audState->state) {
    case kStatus_Aud_Playing: {
		if(playSta == kStatus_WtPlay_Playing){
	        audState->runTime++;
	        /* 获取当前播放索引 */
	        Wt2000_QueryState(kType_WtCmd_CurrPlayFile);
	        Audio_WaitAck(ack);
	        if(ack[0] == kType_WtCmd_CurrPlayFile && audState->playIndex != ack[2]){
	            audState->playIndex = ack[2];
				audState->runTime = 0;
			}	
		}
		else if(playSta == kStatus_WtPlay_Stop){
			Audio_PlayNext();
		}
    }
    break;
    case kStatus_Aud_Recording: {
        audState->runTime++;
    }
    break;

    default:
        break;

    }

    xSemaphoreGive(UartCmdSendSem);

//    debug("AudioState = %X, audSta = %X, time = %d ,index = %d, usbConnect = %d\r\n",audState->state,playSta,audState->runTime,audState->playIndex,usbConnect);

    if(Listener != null)
        Listener(audState);
}



