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
#include "global_config.h"
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
static ScreenProtocol_S *Protocol_SetScreen(ScreenProtocol_S *prot,ScreenProtType_EN type,uint16_t reg);

/*******************************************************************************
 * Variables
 ******************************************************************************/
Protocol_S Protocol = {
	.conference = Protocol_SetConference,
	.wifiUnit = Protocol_SetWifiUnit,
	.screen = Protocol_SetScreen,
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

static ScreenProtocol_S *Protocol_SetScreen(ScreenProtocol_S *prot,ScreenProtType_EN type,uint16_t reg){
	ERR_CHECK(prot != null,return prot);
	
	prot->type = type;
	switch(type){
		/* ÇĞ»»Ò³Ãæ */
		case tType_Screen_Page:{
			prot->para[0] = 0x03;
			prot->para[1] = (uint8_t)(reg >> 8);
			prot->para[2] = (uint8_t)(reg & 0xFF);	
		}break;
		/* ²éÑ¯Ò³Ãæ */
		case tType_Screen_Query:{
			prot->para[0] = 0x03;
			prot->para[1] = 0x02;	
		}break;
		/* ÅäÖÃ¼Ä´æÆ÷µÄÖµ */
		case tType_Screen_CfgReg:{
			prot->para[0] = (uint8_t)(reg >> 8);
			prot->para[1] = (uint8_t)(reg & 0xFF);		
		}break;

		default:break;
	}
	
	return prot;
}


