/**
 *
 *	@name				app.c
 *	@author 			KT
 *	@date 				2019/07/26
 *	@brief
 *
 *  @API
 *
 *  @description
 *
 **/

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "stdio.h"
#include "fsl_device_registers.h"
#include "debug.h"
#include "board.h"
#include "fsl_lpuart_freertos.h"
#include "fsl_lpuart.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_common.h"
#include "usb_disk.h"
#include "ram.h"
#include "audio_sai.h"
#include "audio_record.h"
#include "network.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "wired_unit.h"
#include "conference.h"
#include "external_ctrl.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Task priorities. */
#define TESTTASK_PRIORITY 		6
#define TESTTASK_STACK_SIZE  	3000

/* Task priorities. */
#define LAUNCHER_PRIORITY 		(configMAX_PRIORITIES - 1)
#define LAUNCHER_STACK_SIZE  	(1024)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void testTask_1(void *pvParameters);
static void testTask_2(void *pvParameters);
static void recordTextTask(void *pvParameters);

static void App_LauncherTask(void *pvParameters);
/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

/*
 * @brief Application entry point.
 */
int main(void)
{
    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitModuleClock();

	APP_PRINT_DEV_MSG();
	
//    debug("Hardware init finish!!\r\n");
    Network.init();

    UsbDisk.init();

    /* test */
    if (xTaskCreate(App_LauncherTask, "Launcher", LAUNCHER_STACK_SIZE, null, LAUNCHER_PRIORITY, NULL) != pdPASS) {
        debug("create host task error\r\n");
    }

//    if (xTaskCreate(testTask_1, "testTask_2", TESTTASK_STACK_SIZE, "testTask_2", 2, NULL) != pdPASS)
//    {
//        debug("create host task error\r\n");
//    }
//
//	if (xTaskCreate(recordTextTask, "recordTextTask", TESTTASK_STACK_SIZE, NULL, TESTTASK_PRIORITY, NULL) != pdPASS)
//    {
//        debug("create host task error\r\n");
//    }

    vTaskStartScheduler();
    while(1);
}



static void App_LauncherTask(void *pvParameters)
{

    debug("Tasks is being launch.....\r\n");

    WiredUnit.launch();

    Conference.launch();

    UsbDisk.launch();

    ExternalCtrl.launch();

//	debug_init();
    vTaskDelete(null);
    while(1);
}

/*!
 * @brief testTask_1
 */
static void testTask_1(void *pvParameters)
{
	
    vTaskSuspend(NULL);
    while(1) {
		
    }
}


static TimerHandle_t testTimer1; // ¶¨Òå¾ä±ú
static volatile bool alarm;
void testTimer1CallBack(TimerHandle_t xTimer)
{
    alarm = true;
    debug("testTimer1 alarm!!\r\n");
}
/*!
 * @brief  testTask_2
 */
static void testTask_2(void *pvParameters)
{
    debug("testTask_2 start!!\r\n");

    while(1) {
        DELAY(1000);
        debug("testTask_2 : %s\r\n",(char *)pvParameters);
    }
}

static void recordTextTask(void *pvParameters)
{


    uint8_t sec = 120;
    uint32_t size = 8192;
    uint8_t *data;
    char *path;
    AudioRecordHandler_S *audioRecordHandler;
    AudioRecordHandler_S *audioRecordHandler2;
    AudioRecordHandler_S *audioRecordHandler3;
//    AudioRecordHandler_S *audioRecordHandler4;

    debug("recordTextTask start!!\r\n");

//		debug("Ram free size = 0x%x\r\n",xPortGetFreeHeapSize());
    data = MALLOC(size);


    testTimer1 = xTimerCreate("testTimer1",MsToTick(sec*1000),pdFALSE,( void * ) 0,testTimer1CallBack);
    path = MALLOC(50);


    UsbDisk.waitDevConnect();

    sprintf(path,"%s/%s",USBDISK_ROOT,"audioTest");
    audioRecordHandler = AudioRecord.creat(path,saiAudio);

    sprintf(path,"%s/%s",USBDISK_ROOT,"netdata2");
    audioRecordHandler2 = AudioRecord.creat(path,netAudio);

    sprintf(path,"%s/%s",USBDISK_ROOT,"netdata3");
    audioRecordHandler3 = AudioRecord.creat(path,netAudio);

//		sprintf(path,"%s/%s",USBDISK_ROOT,"netdata4");
//		audioRecordHandler4 = AudioRecord.creat(path,netAudio);
    if(audioRecordHandler == NULL) {
        debug("audio record creat fail\r\n");
        vTaskSuspend(NULL);
    }

    debug("audio record creat sucess\r\n");
    xTimerStart(testTimer1,0);
    AudioRecord.saiStart(audioRecordHandler);
    while(!alarm) {
        memset(data,'2',size);
        AudioRecord.netData(audioRecordHandler2,data,size);
        memset(data,'3',size);
        AudioRecord.netData(audioRecordHandler3,data,size);
//			memset(data,'4',size);
//			AudioRecord.netData(audioRecordHandler4,data,size);
        DELAY(80);
    }

    AudioRecord.saiStop(audioRecordHandler);

    AudioRecord.dismiss(audioRecordHandler);
    AudioRecord.dismiss(audioRecordHandler2);
    AudioRecord.dismiss(audioRecordHandler3);
//		AudioRecord.dismiss(audioRecordHandler4);

    while(1) {
        debug("testTask_1 : task finish!\r\n");
        DELAY(20);
        debug("Ram free size = 0x%x\r\n",xPortGetFreeHeapSize());
        vTaskSuspend(NULL);
    }
}


void HardFault_Handler(void)
{
    debug("HardFault_Handler!!!\r\n\r\n");
    while(1);
}

void MemManage_Handler(void)
{
    debug("MemManage_Handler!!!\r\n\r\n");
    while(1);
}

