/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __HAL_PHY_H_
#define __HAL_PHY_H_

#include "fsl_common.h"
#include "drivers_common.h"
/*!
 * @addtogroup Physical Layer driver of Ethernet Network
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef PHY_LAN8720A_ENABLE
#define PHY_LAN8720A_ENABLE						ENABLE
#endif

#ifndef PHY_RTL8306M_ENABLE
#define PHY_RTL8306M_ENABLE						ENABLE
#endif

#ifndef PHY_KSZ8081_ENABLE
#define PHY_KSZ8081_ENABLE						DISABLE
#endif




typedef enum {
#if	PHY_LAN8720A_ENABLE
    tLan8720a,
#endif

#if	PHY_RTL8306M_ENABLE
    tRtl8306m,
#endif

#if	PHY_KSZ8081_ENABLE
    tKsz8081,
#endif
} HAL_PhyType_EN;



/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * API
 ******************************************************************************/
status_t HAL_PhyInit(HAL_PhyType_EN type);
status_t HAL_PhyLoopback(HAL_PhyType_EN type,phy_loop_t mode, phy_speed_t speed, bool enable);
status_t HAL_PhyGetLink(HAL_PhyType_EN type,bool *status);
status_t HAL_PhyGetSpeedDuplex(HAL_PhyType_EN type,phy_speed_t *speed, phy_duplex_t *duplex);
status_t HAL_PhyGetAutoNegotiation(HAL_PhyType_EN type);

#endif /* _FSL_PHY_H_ */
