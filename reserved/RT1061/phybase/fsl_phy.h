/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_PHY_H_
#define _FSL_PHY_H_

#include "fsl_enet.h"

/*!
 * @addtogroup phy_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines the PHY status. */
enum _phy_status
{
    kStatus_PHY_SMIVisitTimeout = MAKE_STATUS(kStatusGroup_PHY, 1),  /*!< ENET PHY SMI visit timeout. */
    kStatus_PHY_AutoNegotiateFail = MAKE_STATUS(kStatusGroup_PHY, 2) /*!< ENET PHY AutoNegotiate Fail. */
};

/*! @brief Defines the PHY link speed. This is align with the speed for ENET MAC. */
typedef enum _phy_speed
{
    kPHY_Speed10M = 0U, /*!< ENET PHY 10M speed. */
    kPHY_Speed100M      /*!< ENET PHY 100M speed. */
} phy_speed_t;

/*! @brief Defines the PHY link duplex. */
typedef enum _phy_duplex
{
    kPHY_HalfDuplex = 0U, /*!< ENET PHY half duplex. */
    kPHY_FullDuplex       /*!< ENET PHY full duplex. */
} phy_duplex_t;

/*! @brief Defines the PHY loopback mode. */
typedef enum _phy_loop
{
    kPHY_LocalLoop = 0U, /*!< ENET PHY local loopback. */
    kPHY_RemoteLoop      /*!< ENET PHY remote loopback. */
} phy_loop_t;

#endif /* _FSL_PHY_H_ */
