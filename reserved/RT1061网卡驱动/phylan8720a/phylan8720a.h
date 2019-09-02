/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _LAN8720A_H_
#define _LAN8720A_H_

/*!
 * @addtogroup phy_driver
 * @{
 */
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
  * @name PHY Driver
  * @{
  */

/*
*@description: PHY芯片初始化函数
*@Author: NXP
*@param[in]base: 网卡硬件
*@param[in]phyAddr: 网卡phy地址
*@param[in]srcClock_Hz:SMI接口时钟
*@param[out]kStatus_Success:PHY initialize success
*@param[out]kStatus_PHY_SMIVisitTimeout:PHY SMI visit time out
*@param[out]kStatus_PHY_AutoNegotiateFail:PHY auto negotiate fail
*@return:无
*@Modify date: 20190514
*@Modifier Author:srj
*@others:无
*/
status_t PhyLan8720a_Init(ENET_Type *base, uint32_t phyAddr, uint32_t srcClock_Hz);

/*
*@description: 检测PHY芯片自适应情况
*@Author: srj
*@param[in]base: 网卡硬件
*@param[in]phyAddr: 网卡phy地址
*@param[out] kStatus_PHY_AutoNegotiateFail: 自适应失败
*@param[out] kStatus_Success: 自适应成功
*@return:无
*@Modify date: 20190514
*@Modifier Author:srj
*@others:无
*/
status_t PhyLan8720a_GetAutoNegotiation(ENET_Type *base, uint32_t phyAddr);

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
status_t PhyLan8720a_GetLinkStatus(ENET_Type *base, uint32_t phyAddr, bool *status);

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
status_t PhyLan8720a_GetLinkSpeedDuplex(ENET_Type *base, uint32_t phyAddr, phy_speed_t *speed, phy_duplex_t *duplex);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_PHY_H_ */

