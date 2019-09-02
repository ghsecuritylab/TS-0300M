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
#include "wifi_unit.h"
#include "conference.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* WIFI单元——主机通讯协议格式 */
typedef struct {
	uint8_t frameCnt;
    WifiUnitProtocol_S prot;
    uint16_t exLen;
    uint8_t exDataHead;
} WifiUnitData_S;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* API调用 */
static void WifiUnit_Launch(void);
static void WifiUnit_NetDataTransmitWithExData(WifiUnitProtocol_S *prot, uint16_t exLen, uint8_t *exData);
static void WifiUnit_NetDataTransmit(WifiUnitProtocol_S *prot);

/* 内部调用 */
/*******************************************************************************
 * Variables
 ******************************************************************************/

WifiUnit_S WifiUnit = {
    .launch = WifiUnit_Launch,
    .transmit = WifiUnit_NetDataTransmit,
    .transWithExData = WifiUnit_NetDataTransmitWithExData,
};
/*******************************************************************************
 * Code
 ******************************************************************************/
/**
* @Name  		WifiUnit_Init
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void WifiUnit_Launch(void) {

}

/**
* @Name  		WifiUnit_Init
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void WifiUnit_LaunchTask(void *pvParameters) {

}


/**
* @Name  		WifiUnit_NetDataTransmitWithExData
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void WifiUnit_NetDataTransmitWithExData(WifiUnitProtocol_S *prot, uint16_t exLen, uint8_t *exData) {
    
}


/**
* @Name  		WifiUnit_NetDataTransmit
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void WifiUnit_NetDataTransmit(WifiUnitProtocol_S *prot) {
	WifiUnit_NetDataTransmitWithExData(prot,null,null);
}



