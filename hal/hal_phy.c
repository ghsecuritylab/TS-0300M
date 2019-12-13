/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/*
 *	@FileName					hal_phy.c
 *	@Author 					KT
 *	@CreationTime				2019/09/30
 *	@Description
 *
 *	@Include					hal_phy.h
 *
 *
 **/

#include "hal_phy.h"

#include "ksz8081.h"
#include "lan8720.h"
#include "rtl8306m.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if	PHY_LAN8720A_ENABLE

#ifndef PHY_LAN8720A_SMI_TYPE
#define PHY_LAN8720A_SMI_TYPE					ENET
#endif

#ifndef PHY_LAN8720A_ADDR
#define PHY_LAN8720A_ADDR						(0)
#endif

#endif

#if	PHY_RTL8306M_ENABLE

#ifndef PHY_RTL8306M_SMI_TYPE
#define PHY_RTL8306M_SMI_TYPE					ENET2
#endif

#ifndef PHY_RTL8306M_ADDR
#define PHY_RTL8306M_ADDR						(6)
#endif

#endif

#if	PHY_KSZ8081_ENABLE

#ifndef PHY_KSZ8081_SMI_TYPE
#define PHY_KSZ8081_SMI_TYPE					ENET
#endif

#ifndef PHY_KSZ8081_ADDR
#define PHY_KSZ8081_ADDR						(1)
#endif

#endif


#define PHY_DRIVERS_TOTAL_NUM					(PHY_LAN8720A_ENABLE + PHY_RTL8306M_ENABLE + PHY_KSZ8081_ENABLE)


typedef struct {

    /* @brief PHY control & config ENET_Type */
    ENET_Type *base;

    /* @brief PHY address */
    uint8_t addr;


    /*!
     * @brief Initializes PHY.
     *
     *  This function initialize the SMI interface and initialize PHY.
     *  The SMI is the MII management interface between PHY and MAC, which should be
     *  firstly initialized before any other operation for PHY. The PHY initialize with auto-negotiation.
     *
     * @param base       ENET peripheral base address.
     * @param phyAddr    The PHY address.
     * @param srcClock_Hz  The module clock frequency - system clock for MII management interface - SMI.
     * @retval kStatus_Success  PHY initialize success
     * @retval kStatus_PHY_SMIVisitTimeout  PHY SMI visit time out
     * @retval kStatus_PHY_AutoNegotiateFail  PHY auto negotiate fail
     */
    status_t (*init)(ENET_Type *base, uint32_t phyAddr);

    /*!
     * @brief Enables/disables PHY loopback.
     *
     * @param base     ENET peripheral base address.
     * @param phyAddr  The PHY address.
     * @param mode     The loopback mode to be enabled, please see "phy_loop_t".
     * the two loopback mode should not be both set. when one loopback mode is set
     * the other one should be disabled.
     * @param speed    PHY speed for loopback mode.
     * @param enable   True to enable, false to disable.
     * @retval kStatus_Success  PHY loopback success
     * @retval kStatus_PHY_SMIVisitTimeout  PHY SMI visit time out
     */
    status_t (*loopback)(ENET_Type *base, uint32_t phyAddr, phy_loop_t mode, phy_speed_t speed, bool enable);

    /*!
     * @brief Gets the PHY link status.
     *
     * @param base     ENET peripheral base address.
     * @param phyAddr  The PHY address.
     * @param status   The link up or down status of the PHY.
     *         - true the link is up.
     *         - false the link is down.
     * @retval kStatus_Success   PHY get link status success
     * @retval kStatus_PHY_SMIVisitTimeout  PHY SMI visit time out
     */
    status_t (*getLink)(ENET_Type *base, uint32_t phyAddr, bool *status);

    /*!
     * @brief Gets the PHY link speed and duplex.
     *
     * @param base     ENET peripheral base address.
     * @param phyAddr  The PHY address.
     * @param speed    The address of PHY link speed.
     * @param duplex   The link duplex of PHY.
     * @retval kStatus_Success   PHY get link speed and duplex success
     * @retval kStatus_PHY_SMIVisitTimeout  PHY SMI visit time out
     */
    status_t (*getSpeedDuplex)(ENET_Type *base, uint32_t phyAddr, phy_speed_t *speed, phy_duplex_t *duplex);

    /*!
     * @brief Gets the PHY auto negotiation.
     *
     * @param base     ENET peripheral base address.
     * @param phyAddr  The PHY address.
     * @retval kStatus_Success   PHY get link speed and duplex success
     * @retval kStatus_PHY_AutoNegotiateFail  PHY auto negotiation not complete
     */
    status_t (*getAutoNegotiation)(ENET_Type *base, uint32_t phyAddr);

} HAL_Phy_S;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Variables
 ******************************************************************************/
#if	PHY_LAN8720A_ENABLE
HAL_Phy_S Lan8720a_driver = {
    .base = PHY_LAN8720A_SMI_TYPE,
    .addr = PHY_LAN8720A_ADDR,
    .init = Lan8720a_Init,
    .getLink = Lan8720a_GetLinkStatus,
    .getSpeedDuplex = Lan8720a_GetLinkSpeedDuplex,
    .getAutoNegotiation = Lan8720a_GetAutoNegotiation,
};
#endif

#if	PHY_RTL8306M_ENABLE
HAL_Phy_S Rtl8306m_driver = {
    .base = PHY_RTL8306M_SMI_TYPE,
    .addr = PHY_RTL8306M_ADDR,
    .init = Rtl8306m_Init,
    .getLink = Rtl8306m_GetLinkStatus,
    .getSpeedDuplex = Rtl8306m_GetLinkSpeedDuplex,
    .getAutoNegotiation = Rtl8306m_GetAutoNegotiation,
};
#endif

#if	PHY_KSZ8081_ENABLE
HAL_Phy_S Ksz8081_driver = {
    .base = PHY_KSZ8081_SMI_TYPE,
    .addr = PHY_KSZ8081_ADDR,
    .init = KSZ8081_PhyInit,
    .getLink = KSZ8081_GetLinkStatus,
    .loopback = KSZ8081_EnableLoopback,
    .getSpeedDuplex = KSZ8081_GetLinkSpeedDuplex,
    .getAutoNegotiation = KSZ8081_GetAutoNegotiation,
};
#endif

static HAL_Phy_S *Phy_drivers[PHY_DRIVERS_TOTAL_NUM] = {
#if	PHY_LAN8720A_ENABLE
    &Lan8720a_driver,
#endif

#if	PHY_RTL8306M_ENABLE
    &Rtl8306m_driver,
#endif

#if	PHY_KSZ8081_ENABLE
    &Ksz8081_driver,
#endif
};
/*******************************************************************************
 * Code
 ******************************************************************************/
status_t HAL_PhyInit(HAL_PhyType_EN type)
{
    HAL_Phy_S *phy;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < PHY_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    phy = Phy_drivers[type];

    return phy->init(phy->base,phy->addr);
}

status_t HAL_PhyLoopback(HAL_PhyType_EN type,phy_loop_t mode, phy_speed_t speed, bool enable)
{
    HAL_Phy_S *phy;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < PHY_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    phy = Phy_drivers[type];

    return phy->loopback(phy->base,phy->addr,mode,speed,enable);
}


status_t HAL_PhyGetLink(HAL_PhyType_EN type,bool *status)
{
    HAL_Phy_S *phy;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < PHY_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    phy = Phy_drivers[type];

    return phy->getLink(phy->base,phy->addr,status);
}

status_t HAL_PhyGetSpeedDuplex(HAL_PhyType_EN type,phy_speed_t *speed, phy_duplex_t *duplex)
{
    HAL_Phy_S *phy;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < PHY_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    phy = Phy_drivers[type];

    return phy->getSpeedDuplex(phy->base,phy->addr,speed,duplex);
}

status_t HAL_PhyGetAutoNegotiation(HAL_PhyType_EN type)
{
    HAL_Phy_S *phy;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < PHY_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    phy = Phy_drivers[type];

    return phy->getAutoNegotiation(phy->base,phy->addr);
}


