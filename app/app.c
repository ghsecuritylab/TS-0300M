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
/* APP */ 
#include "app.h"
#include "wired_unit.h"
#include "conference.h"
#include "external_ctrl.h"
#include "wifi_unit.h"
#include "screen.h"

/* OS */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* API */
#include "network.h"
#include "usb_disk.h"
#include "audio.h"
#include "time.h"

/* HAL */
#include "hal.h"
#include "hal_gpio.h"
#include "hal_rtc.h"
#include "hal_spi_flash.h"

/* LIB */
#include "stdio.h"

/* SDK */
#include "board.h"
#include "pin_mux.h"
#include "fsl_iomuxc.h"

/* DRIVER */
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

static void App_LauncherTask(void *pvParameters);
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * @brief Application entry point.
 */
int main(void)
{
	HAL_Init();

	/* 打印软件设备信息 */
	APP_PRINT_DEV_MSG();
	
    if (xTaskCreate(App_LauncherTask, "Launcher", LAUNCHER_STACK_SIZE, null, LAUNCHER_PRIORITY, NULL) != pdPASS) {
        debug("create host task error\r\n");
    }

    if (xTaskCreate(testTask_1, "testTask_1", TESTTASK_STACK_SIZE, null, TESTTASK_PRIORITY, NULL) != pdPASS)
    {
        debug("create host task error\r\n");
    }
	
//	if (xTaskCreate(testTask_2, "testTask_2", TESTTASK_STACK_SIZE, NULL, TESTTASK_PRIORITY, NULL) != pdPASS)
//    {
//        debug("create host task error\r\n");
//    }


    vTaskStartScheduler();
    while(1);
}

//#undef send


static void App_LauncherTask(void *pvParameters)
{

	taskENTER_CRITICAL();	
	
	Network.init();
    UsbDisk.init();

	
	taskEXIT_CRITICAL();	
	
	
    debug("Tasks is being launch.....\r\n");
	
	Conference.launch();
	
    WiredUnit.launch();

	WifiUnit.launch();
	
    ExternalCtrl.launch();

    UsbDisk.launch();
	
	Screen.launch();

	Audio.launch();

	Time.launch();

//	debug_init();
    vTaskDelete(null);
    while(1);
}



/*!
 * @brief testTask_1
 */
 static HAL_GpioIndex MuteCtrl;
static HAL_GpioIndex MuteCtrl2;
static HAL_GpioIndex StaLed;

static void testTask_1(void *pvParameters)
{
	bool staled = false;

	MuteCtrl = HAL_GpioInit(GPIO1, 24, kGPIO_DigitalOutput, null, null);
	MuteCtrl2 = HAL_GpioInit(GPIO2, 29, kGPIO_DigitalOutput, null, null);
	StaLed = HAL_GpioInit(GPIO1, 20, kGPIO_DigitalOutput, null, null);
	HAL_SetGpioLevel(MuteCtrl, 0);
	HAL_SetGpioLevel(MuteCtrl2, 0);

	DELAY(500);

	HAL_SetGpioLevel(MuteCtrl, 1);
	HAL_SetGpioLevel(MuteCtrl2, 1);

    while(1) {
		staled = !staled;
		HAL_SetGpioLevel(StaLed, staled);
		DELAY(1000);
    }
}

/*!
 * @brief  testTask_2
 */
static void testTask_2(void *pvParameters)
{
	
	char dateTimeStr[30] = {0};
	uint8_t sta[5];
	uint16_t id;
	
	uint8_t *data,*txBuf,*rxBuf;
	
	
	DELAY(3000);
	data = MALLOC(4096);
	txBuf = MALLOC(4200);
	rxBuf = MALLOC(4200);
	
    debug("testTask_2 start!!\r\n");

	id = HAL_FlashDeviceID(tW25Q64);
	debug("Flash id = %X\r\n",id);
	
	HAL_FlashBufferConfig(tW25Q64,txBuf,rxBuf);
	
	
	
	HAL_FlashReadSector(tW25Q64,0x1000,data);
	
	debug("data : \r\n");
	for(id = 0;id < 4096;id ++){
		debug(" %X",data[id]);
	}
	debug("\r\n\r\n");
	
	for(id = 0;id <4096;id++){
		data[id] = id % 256;
	}
	
	
	HAL_FlashEraseSector(tW25Q64,0x1000);
	
	while(HAL_FlashGetBusy(tW25Q64)){
		DELAY(100);
	}
	
	HAL_FlashWriteSector(tW25Q64,0x1000,data);
	
	while(HAL_FlashGetBusy(tW25Q64)){
		DELAY(100);
	}
	
	memset(data,0,4096);
	
	HAL_FlashReadSector(tW25Q64,0x1000,data);
	
	debug("data : \r\n");
	for(id = 0;id < 4096;id ++){
		debug(" %X",data[id]);
	}
	debug("\r\n\r\n");
	
	
	vTaskDelete(null);

    while(1) {
        DELAY(1000);
//        debug("testTask_2 : %s\r\n",(char *)pvParameters);
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

