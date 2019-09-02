/**
 *
 *	@name				protocol.c
 *	@author 			KT
 *	@date 				2019/08/13
 *	@brief				
 *
 *  @description   		
 *
 **/
 
#include "protocol.h"
#include "app_common.h"
/*******************************************************************************
 * includes
 ******************************************************************************/



/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static ConfProtocol_S *Protocol_SetConference(ConfProtocol_S *prot,uint16_t id,uint8_t type,uint8_t ph,uint8_t pl,uint8_t ch,uint16_t sec);
static WifiUnitProtocol_S *Protocol_SetWifiUnit(WifiUnitProtocol_S *prot,uint16_t id,uint8_t cmd,uint8_t ph,uint8_t pl);
/*******************************************************************************
 * Variables
 ******************************************************************************/
Protocol_S Protocol = {
	.conference = Protocol_SetConference,
	.wifiUnit = Protocol_SetWifiUnit,
};
/*******************************************************************************
 * Code
 ******************************************************************************/
static ConfProtocol_S *Protocol_SetConference(ConfProtocol_S *prot,uint16_t id,uint8_t type,uint8_t ph,uint8_t pl,uint8_t ch,uint16_t sec){
	ERR_CHECK(prot != null,return prot);
	
	prot->id = id;
	prot->type = type;
	prot->ph = ph;
	prot->pl = pl;
	prot->ch = ch;
	prot->sec = sec;
	
	return prot;
}

static WifiUnitProtocol_S *Protocol_SetWifiUnit(WifiUnitProtocol_S *prot,uint16_t id,uint8_t cmd,uint8_t ph,uint8_t pl){
	ERR_CHECK(prot != null,return prot);
	
	prot->id = id;
	prot->cmd = cmd;
	prot->ph = ph;
	prot->pl = pl;
	
	return prot;
}

