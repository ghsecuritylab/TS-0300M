/**
 *
 *	@name				rtl8306m.c
 *	@modify 			KT
 *	@date 				2019/07/31
 *	@brief				
 *
 *  @API				
 *
 *  @description   		
 *
 **/
#include "rtl8306m.h"
#include "drivers_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Defines the PHY registers. */
#define RTL8306M_BASICCONTROL_REG					(0x00U)			/*!< The PHY basic control register. */
#define RTL8306M_BASICSTATUS_REG					(0x01U)			/*!< The PHY basic status register. */
#define RTL8306M_ID1_REG							(0x02U)			/*!< The PHY ID one register. */
#define RTL8306M_ID2_REG							(0x03U)			/*!< The PHY ID two register. */
#define RTL8306M_AUTONEG_ADVERTISE_REG				(0x04U)			/*!< The PHY auto-negotiate advertise register. */
#define RTL8306M_LINK_PARTNER_ABILITY_REG			(0x05U)			/*!< The PHY link partner ability register. */
#define RTL8306M_SPECIAL_CONTROL_REG0				(0x16U)			/*!< The PHY special control/status register. */
#define RTL8306M_SPECIAL_CONTROL_REG1				(0x18U)			/*!< The PHY special control/status register. */

#define RTL8306M_CONTROL_ID1						(0x1CU)			/*!< The PHY ID1*/
	
/*! @brief Defines the mask flag in basic control register. */
#define RTL8306M_BCTL_DUPLEX_MASK					(0x0100U)		/*!< The PHY duplex bit mask. */
#define RTL8306M_BCTL_AUTONEG_MASK					(0x1000U)		/*!< The PHY auto negotiation bit mask. */
#define RTL8306M_BCTL_SPEED_MASK					(0x2000U)		/*!< The PHY speed bit mask. */
#define RTL8306M_BCTL_RESET_MASK					(0x8000U)		/*!< The PHY reset bit mask. */
#define RTL8306M_BCTL_SPEED_100M_MASK				(0x2000U)		/*!< The PHY 100M speed mask. */

	   
/*! @brief Defines the mask flag in basic status register. */
#define RTL8306M_BSTATUS_LINKSTATUS_MASK			(0x0004U)		/*!< The PHY link status mask. */
#define RTL8306M_BSTATUS_AUTONEGABLE_MASK			(0x0008U)		/*!< The PHY auto-negotiation ability mask. */
#define RTL8306M_BSTATUS_AUTONEGCOMP_MASK			(0x0020U)		/*!< The PHY auto-negotiation complete mask. */
	
/*! @brief Defines the mask flag in PHY auto-negotiation advertise register. */
#define RTL8306M_100BASETX_FULLDUPLEX_MASK			(0x100U)		/*!< The PHY has the 100M full duplex ability.*/
#define RTL8306M_100BASETX_HALFDUPLEX_MASK			(0x080U)		/*!< The PHY has the 100M full duplex ability.*/
#define RTL8306M_10BASETX_FULLDUPLEX_MASK			(0x040U)		/*!< The PHY has the 10M full duplex ability.*/
#define RTL8306M_10BASETX_HALFDUPLEX_MASK			(0x020U)		/*!< The PHY has the 10M full duplex ability.*/

/*! @brief Defines the mask flag in PHY special control/status register. */
#define RTL8306M_SPECIAL_CONTROL_LINKSTATUS			(0x8000U)		/*!< The PHY special control link status. */
#define RTL8306M_AUTO_NEGOTITATION_ENABLE			(0x0040U)		/*!< The PHY special control auto-negotiation. */
/*******************************************************************************
 * Code
 ******************************************************************************/
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
status_t Rtl8306m_Init(ENET_Type *base, uint32_t phyAddr)
{
    uint32_t counter = PHY_TIMEOUT_COUNT;
    uint32_t idReg = 0;
    status_t result = kStatus_Success;
    uint32_t instance = ENET_GetInstance(base);
//
//#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
//    /* Set SMI first. */
//    CLOCK_EnableClock(s_enetClock[instance]);
//#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
//    ENET_SetSMI(base, srcClock_Hz, false);

    /* Initialization after PHY stars to work. */
    while ((idReg != RTL8306M_CONTROL_ID1) && (counter != 0))
    {
        ENET_Read(base, phyAddr, RTL8306M_ID1_REG, &idReg);
        counter --;       
    }

    if (!counter)
    {
        return kStatus_Fail;
    }

    /* Reset PHY. */
    counter = PHY_TIMEOUT_COUNT;
	
    ENET_Write(base, phyAddr, RTL8306M_BASICCONTROL_REG, RTL8306M_BCTL_RESET_MASK);
	
	ENET_Read(base, phyAddr,RTL8306M_SPECIAL_CONTROL_REG0,&idReg);
    idReg |= RTL8306M_AUTO_NEGOTITATION_ENABLE | RTL8306M_SPECIAL_CONTROL_LINKSTATUS;
    ENET_Write(base, phyAddr,RTL8306M_SPECIAL_CONTROL_REG0, idReg);
	
    /* Set the negotiation. */
//    PHY_Write(base, phyAddr, RTL8306M_AUTONEG_ADVERTISE_REG,
//                           (RTL8306M_100BASETX_FULLDUPLEX_MASK | RTL8306M_100BASETX_HALFDUPLEX_MASK |
//                            RTL8306M_10BASETX_FULLDUPLEX_MASK | RTL8306M_10BASETX_HALFDUPLEX_MASK | 0x1U));

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
status_t Rtl8306m_GetAutoNegotiation(ENET_Type *base, uint32_t phyAddr) 
{
	uint32_t bssReg;

    if(ENET_Read(base, phyAddr, RTL8306M_BASICSTATUS_REG, &bssReg) == kStatus_Success) {
        if((bssReg & RTL8306M_BSTATUS_AUTONEGCOMP_MASK) != 0) {
            return kStatus_Success;
        }
    }
    return kStatus_PHY_AutoNegotiateFail;
}

status_t Rtl8306m_GetLinkStatus(ENET_Type *base, uint32_t phyAddr, bool *status)
{
    assert(status);

    status_t result = kStatus_Success;
    uint32_t data;

    /* Read the basic status register. */
    result = ENET_Read(base, phyAddr, RTL8306M_BASICSTATUS_REG, &data);
    if (result == kStatus_Success)
    {
        if (!(RTL8306M_BSTATUS_LINKSTATUS_MASK & data))
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

status_t Rtl8306m_GetLinkSpeedDuplex(ENET_Type *base, uint32_t phyAddr, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(duplex);

    status_t result = kStatus_Success;
    uint32_t ctlReg;

    /* Read the control two register. */
    result = ENET_Read(base, phyAddr, RTL8306M_BASICCONTROL_REG, &ctlReg);
    if (result == kStatus_Success)
    {
		if(ctlReg & RTL8306M_BCTL_DUPLEX_MASK)
        {
            /* Full duplex. */
            *duplex = kPHY_FullDuplex;
        }
        else
        {
            /* Half duplex. */
            *duplex = kPHY_HalfDuplex;
        }
        if (ctlReg & RTL8306M_BCTL_SPEED_MASK)
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


