/*
 *	 @FileName					 hal_mac_phy.c
 *	 @Author					 KT
 *	 @CreationTime				 2019/10/25
 *	 @Description
 *
 *	 @Include					 hal_mac_phy.h
 *
 *	 @API						 MacPhy
 *
 **/


#include "hal_mac_phy.h"
#include "dm9051.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if	MAC_PHY_DM9051_ENABLE

#ifndef MAC_PHY_DM9051_SMI_TYPE
#define MAC_PHY_DM9051_SMI_TYPE						(LPSPI3)
#endif

#ifndef MAC_PHY_DM9051_PCS
#define MAC_PHY_DM9051_PCS							(kLPSPI_MasterPcs0)
#endif

#endif

#define MAC_PHY_DRIVERS_TOTAL_NUM					(MAC_PHY_DM9051_ENABLE)


typedef struct {

    LPSPI_Type *base;

    uint32_t pcs;

    status_t (*init)(LPSPI_Type *base,uint32_t pcs,uint8_t *mac,bool broadcast);

    status_t (*loopback)(LPSPI_Type *base,uint32_t pcs, phy_loop_t mode, phy_speed_t speed, bool enable);

    status_t (*getLink)(LPSPI_Type *base,uint32_t pcs, bool *status);

    status_t (*getSpeedDuplex)(LPSPI_Type *base,uint32_t pcs, phy_speed_t *speed, phy_duplex_t *duplex);

    status_t (*getAutoNegotiation)(LPSPI_Type *base,uint32_t pcs);

	status_t (*send)(LPSPI_Type *base,uint32_t pcs,uint8_t *data, uint16_t len);

	uint16_t (*receive)(LPSPI_Type *base,uint32_t pcs,uint8_t *data);

	uint8_t  (*getIsrSta)(LPSPI_Type *base,uint32_t pcs);
} HAL_MacPhy_S;


/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Variables
 ******************************************************************************/
#if	MAC_PHY_DM9051_ENABLE
HAL_MacPhy_S Dm9051_driver = {
    .base = MAC_PHY_DM9051_SMI_TYPE,
    .pcs = MAC_PHY_DM9051_PCS,
    .init = Dm9051_Init,
    .getLink = Dm9051_GetLink,
    .getSpeedDuplex = Dm9051_GetSpeedDuplex,
    .getAutoNegotiation = Dm9051_GetAutoNegotiation,
    .send = Dm9051_Send,
    .receive = Dm9051_Receive,
    .getIsrSta = Dm9051_IsrGetClear,
};
#endif

static HAL_MacPhy_S *MacPhy_drivers[MAC_PHY_DRIVERS_TOTAL_NUM] = {
#if	MAC_PHY_DM9051_ENABLE
    &Dm9051_driver,
#endif

};


/*******************************************************************************
 * Code
 ******************************************************************************/
status_t HAL_MacPhyInit(HAL_MacPhyType_EN type,uint8_t *mac,bool broadcast){
	HAL_MacPhy_S *macPhy;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < MAC_PHY_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    macPhy = MacPhy_drivers[type];

    return macPhy->init(macPhy->base,macPhy->pcs,mac,broadcast);
}


status_t HAL_MacPhyLoopback(HAL_MacPhyType_EN type,phy_loop_t mode, phy_speed_t speed, bool enable)
{
    HAL_MacPhy_S *macPhy;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < MAC_PHY_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    macPhy = MacPhy_drivers[type];

    return macPhy->loopback(macPhy->base,macPhy->pcs,mode,speed,enable);
}


status_t HAL_MacPhyGetLink(HAL_MacPhyType_EN type,bool *status)
{
   HAL_MacPhy_S *macPhy;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < MAC_PHY_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    macPhy = MacPhy_drivers[type];

    return macPhy->getLink(macPhy->base,macPhy->pcs,status);
}

status_t HAL_MacPhyGetSpeedDuplex(HAL_MacPhyType_EN type,phy_speed_t *speed, phy_duplex_t *duplex)
{
    HAL_MacPhy_S *macPhy;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < MAC_PHY_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    macPhy = MacPhy_drivers[type];

    return macPhy->getSpeedDuplex(macPhy->base,macPhy->pcs,speed,duplex);
}

status_t HAL_MacPhyGetAutoNegotiation(HAL_MacPhyType_EN type)
{
    HAL_MacPhy_S *macPhy;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < MAC_PHY_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    macPhy = MacPhy_drivers[type];

    return macPhy->getAutoNegotiation(macPhy->base,macPhy->pcs);
}


status_t HAL_MacPhySend(HAL_MacPhyType_EN type,uint8_t *data, uint16_t len){
	HAL_MacPhy_S *macPhy;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < MAC_PHY_DRIVERS_TOTAL_NUM), return kStatus_Fail);
	macPhy = MacPhy_drivers[type];

	return macPhy->send(macPhy->base,macPhy->pcs,data,len);
}

uint16_t HAL_MacPhyReceive(HAL_MacPhyType_EN type,uint8_t *data){
	HAL_MacPhy_S *macPhy;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < MAC_PHY_DRIVERS_TOTAL_NUM), return kStatus_Fail);
	macPhy = MacPhy_drivers[type];

	return macPhy->receive(macPhy->base,macPhy->pcs,data);
}


uint8_t HAL_MacPhyGetIrqSta(HAL_MacPhyType_EN type){
	HAL_MacPhy_S *macPhy;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < MAC_PHY_DRIVERS_TOTAL_NUM), return kStatus_Fail);
	macPhy = MacPhy_drivers[type];

	return macPhy->getIsrSta(macPhy->base,macPhy->pcs);
}





