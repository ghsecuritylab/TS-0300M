/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_phy.h"
#include "phyksz8081.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines the PHY registers. */
#define PHY_BASICCONTROL_REG 0x00U      /*!< The PHY basic control register. */
#define PHY_BASICSTATUS_REG 0x01U       /*!< The PHY basic status register. */
#define PHY_ID1_REG 0x02U               /*!< The PHY ID one register. */
#define PHY_ID2_REG 0x03U               /*!< The PHY ID two register. */
#define PHY_AUTONEG_ADVERTISE_REG 0x04U /*!< The PHY auto-negotiate advertise register. */
#define PHY_CONTROL1_REG 0x1EU          /*!< The PHY control one register. */
#define PHY_CONTROL2_REG 0x1FU          /*!< The PHY control two register. */
	
#define PHY_CONTROL_ID1 0x22U /*!< The PHY ID1*/
	
/*! @brief Defines the mask flag in basic control register. */
#define PHY_BCTL_DUPLEX_MASK 0x0100U          /*!< The PHY duplex bit mask. */
#define PHY_BCTL_RESTART_AUTONEG_MASK 0x0200U /*!< The PHY restart auto negotiation mask. */
#define PHY_BCTL_AUTONEG_MASK 0x1000U         /*!< The PHY auto negotiation bit mask. */
#define PHY_BCTL_SPEED_MASK 0x2000U           /*!< The PHY speed bit mask. */
#define PHY_BCTL_LOOP_MASK 0x4000U            /*!< The PHY loop bit mask. */
#define PHY_BCTL_RESET_MASK 0x8000U           /*!< The PHY reset bit mask. */
#define PHY_BCTL_SPEED_100M_MASK  0x2000U     /*!< The PHY 100M speed mask. */
	
/*!@brief Defines the mask flag of operation mode in control two register*/
#define PHY_CTL2_REMOTELOOP_MASK 0x0004U    /*!< The PHY remote loopback mask. */
#define PHY_CTL2_REFCLK_SELECT_MASK 0x0080U /*!< The PHY RMII reference clock select. */ 
#define PHY_CTL1_10HALFDUPLEX_MASK 0x0001U  /*!< The PHY 10M half duplex mask. */
#define PHY_CTL1_100HALFDUPLEX_MASK 0x0002U /*!< The PHY 100M half duplex mask. */
#define PHY_CTL1_10FULLDUPLEX_MASK 0x0005U  /*!< The PHY 10M full duplex mask. */
#define PHY_CTL1_100FULLDUPLEX_MASK 0x0006U /*!< The PHY 100M full duplex mask. */
#define PHY_CTL1_SPEEDUPLX_MASK 0x0007U     /*!< The PHY speed and duplex mask. */
#define PHY_CTL1_ENERGYDETECT_MASK 0x10U    /*!< The PHY signal present on rx differential pair. */
#define PHY_CTL1_LINKUP_MASK 0x100U         /*!< The PHY link up. */        
#define PHY_LINK_READY_MASK (PHY_CTL1_ENERGYDETECT_MASK | PHY_CTL1_LINKUP_MASK)
	   
/*! @brief Defines the mask flag in basic status register. */
#define PHY_BSTATUS_LINKSTATUS_MASK 0x0004U  /*!< The PHY link status mask. */
#define PHY_BSTATUS_AUTONEGABLE_MASK 0x0008U /*!< The PHY auto-negotiation ability mask. */
#define PHY_BSTATUS_AUTONEGCOMP_MASK 0x0020U /*!< The PHY auto-negotiation complete mask. */
	
/*! @brief Defines the mask flag in PHY auto-negotiation advertise register. */
#define PHY_100BaseT4_ABILITY_MASK 0x200U    /*!< The PHY have the T4 ability. */
#define PHY_100BASETX_FULLDUPLEX_MASK 0x100U /*!< The PHY has the 100M full duplex ability.*/
#define PHY_100BASETX_HALFDUPLEX_MASK 0x080U /*!< The PHY has the 100M full duplex ability.*/
#define PHY_10BASETX_FULLDUPLEX_MASK 0x040U  /*!< The PHY has the 10M full duplex ability.*/
#define PHY_10BASETX_HALFDUPLEX_MASK 0x020U  /*!< The PHY has the 10M full duplex ability.*/


/*! @brief Defines the timeout macro. */
#define PHY_TIMEOUT_COUNT 0x3FFFFFFU
//#define PHY_TIMEOUT_COUNT 0x0FFFFU

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the ENET instance from peripheral base address.
 *
 * @param base ENET peripheral base address.
 * @return ENET instance.
 */
extern uint32_t ENET_GetInstance(ENET_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to enet clocks for each instance. */
extern clock_ip_name_t s_enetClock[FSL_FEATURE_SOC_ENET_COUNT];
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static status_t PhyKsz8081_Write(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t data);
static status_t PhyKsz8081_Read(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t *dataPtr);

 
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
status_t PhyKsz8081_Init(ENET_Type *base, uint32_t phyAddr, uint32_t srcClock_Hz)
{
    uint32_t counter = PHY_TIMEOUT_COUNT;
    uint32_t idReg = 0;
    status_t result = kStatus_Success;
    uint32_t instance = ENET_GetInstance(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Set SMI first. */
    CLOCK_EnableClock(s_enetClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    ENET_SetSMI(base, srcClock_Hz, false);

    /* Initialization after PHY stars to work. */
    while ((idReg != PHY_CONTROL_ID1) && (counter != 0))
    {
        PhyKsz8081_Read(base, phyAddr, PHY_ID1_REG, &idReg);
        counter --;       
    }

    if (!counter)
    {
        return kStatus_Fail;
    }

    /* Reset PHY. */
    counter = PHY_TIMEOUT_COUNT;
    result = PhyKsz8081_Write(base, phyAddr, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result == kStatus_Success)
    {

#if defined(FSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE)
        uint32_t data = 0;
        result = PhyKsz8081_Read(base, phyAddr, PHY_CONTROL2_REG, &data);
        if ( result != kStatus_Success)
        {
            return result;
        }
        result = PhyKsz8081_Write(base, phyAddr, PHY_CONTROL2_REG, (data | PHY_CTL2_REFCLK_SELECT_MASK));
        if (result != kStatus_Success)
        {
            return result;
        }
#endif  /* FSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE */    
        
        /* Set the negotiation. */
        result = PhyKsz8081_Write(base, phyAddr, PHY_AUTONEG_ADVERTISE_REG,
                           (PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK |
                            PHY_10BASETX_FULLDUPLEX_MASK | PHY_10BASETX_HALFDUPLEX_MASK | 0x1U));
        if (result == kStatus_Success)
        {
            result = PhyKsz8081_Write(base, phyAddr, PHY_BASICCONTROL_REG,
                               (PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
        }
    }

    return result;
}


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
status_t PhyKsz8081_GetAutoNegotiation(ENET_Type *base, uint32_t phyAddr) 
{
	uint32_t counter = PHY_TIMEOUT_COUNT;
	uint32_t bssReg;
	uint32_t timeDelay;
	
	while (counter --)
    {
        if(PhyKsz8081_Read(base, phyAddr, PHY_BASICSTATUS_REG, &bssReg) == kStatus_Success) {
        	if((bssReg & PHY_BSTATUS_AUTONEGCOMP_MASK) != 0)
            {
                /* Wait a moment for Phy status stable. */
                for (timeDelay = 0; timeDelay < PHY_TIMEOUT_COUNT; timeDelay ++)
                {
                    __ASM("nop");
                }
                break;
            }
        }

        if (!counter)
        {
            return kStatus_PHY_AutoNegotiateFail;
        }
    }

	return kStatus_Success;
}


static status_t PhyKsz8081_Write(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t data)
{
    uint32_t counter;

    /* Clear the SMI interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    /* Starts a SMI write command. */
    ENET_StartSMIWrite(base, phyAddr, phyReg, kENET_MiiWriteValidFrame, data);

    /* Wait for SMI complete. */
    for (counter = PHY_TIMEOUT_COUNT; counter > 0; counter--)
    {
        if (ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK)
        {
            break;
        }
    }

    /* Check for timeout. */
    if (!counter)
    {
        return kStatus_PHY_SMIVisitTimeout;
    }

    /* Clear MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    return kStatus_Success;
}

static status_t PhyKsz8081_Read(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t *dataPtr)
{
    assert(dataPtr);

    uint32_t counter;

    /* Clear the MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    /* Starts a SMI read command operation. */
    ENET_StartSMIRead(base, phyAddr, phyReg, kENET_MiiReadValidFrame);

    /* Wait for MII complete. */
    for (counter = PHY_TIMEOUT_COUNT; counter > 0; counter--)
    {
        if (ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK)
        {
            break;
        }
    }

    /* Check for timeout. */
    if (!counter)
    {
        return kStatus_PHY_SMIVisitTimeout;
    }

    /* Get data from MII register. */
    *dataPtr = ENET_ReadSMIData(base);

    /* Clear MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    return kStatus_Success;
}

status_t PhyKsz8081_GetLinkStatus(ENET_Type *base, uint32_t phyAddr, bool *status)
{
    assert(status);

    status_t result = kStatus_Success;
    uint32_t data;

    /* Read the basic status register. */
    result = PhyKsz8081_Read(base, phyAddr, PHY_BASICSTATUS_REG, &data);
    if (result == kStatus_Success)
    {
        if (!(PHY_BSTATUS_LINKSTATUS_MASK & data))
        {
            /* link down. */
            *status = false;
        }
        else
        {
            /* link up. */
            *status = true;
        }
    }
    return result;
}

status_t PhyKsz8081_GetLinkSpeedDuplex(ENET_Type *base, uint32_t phyAddr, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(duplex);

    status_t result = kStatus_Success;
    uint32_t data, ctlReg;

    /* Read the control two register. */
    result = PhyKsz8081_Read(base, phyAddr, PHY_CONTROL1_REG, &ctlReg);
    if (result == kStatus_Success)
    {
        data = ctlReg & PHY_CTL1_SPEEDUPLX_MASK;
        if ((PHY_CTL1_10FULLDUPLEX_MASK == data) || (PHY_CTL1_100FULLDUPLEX_MASK == data))
        {
            /* Full duplex. */
            *duplex = kPHY_FullDuplex;
        }
        else
        {
            /* Half duplex. */
            *duplex = kPHY_HalfDuplex;
        }

        data = ctlReg & PHY_CTL1_SPEEDUPLX_MASK;
        if ((PHY_CTL1_100HALFDUPLEX_MASK == data) || (PHY_CTL1_100FULLDUPLEX_MASK == data))
        {
            /* 100M speed. */
            *speed = kPHY_Speed100M;
        }
        else
        { /* 10M speed. */
            *speed = kPHY_Speed10M;
        }
    }

    return result;
}
