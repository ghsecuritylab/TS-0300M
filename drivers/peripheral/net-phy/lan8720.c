/**
 *
 *	@name				lan8720.c
 *	@modify 			KT
 *	@date 				2019/07/31
 *	@brief				
 *
 *  @API				
 *
 *  @description   		
 *
 **/
#include "lan8720.h"
#include "drivers_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Defines the PHY registers. */
#define LAN8720A_BASICCONTROL_REG					(0x00U)			/*!< The PHY basic control register. */
#define LAN8720A_BASICSTATUS_REG					(0x01U)			/*!< The PHY basic status register. */
#define LAN8720A_ID1_REG							(0x02U)			/*!< The PHY ID one register. */
#define LAN8720A_ID2_REG							(0x03U)			/*!< The PHY ID two register. */
#define LAN8720A_AUTONEG_ADVERTISE_REG				(0x04U)			/*!< The PHY auto-negotiate advertise register. */
#define LAN8720A_SPECIAL_CONTROL_STATUS_REG			(0x1FU)			/*!< The PHY special control/status register. */

#define LAN8720A_CONTROL_ID1						(0x07U)			/*!< The PHY ID1*/
/*! @brief Defines the mask flag in basic control register. */
#define LAN8720A_BCTL_DUPLEX_MASK					(0x0100U)		/*!< The PHY duplex bit mask. */
#define LAN8720A_BCTL_RESTART_AUTONEG_MASK			(0x0200U)		/*!< The PHY restart auto negotiation mask. */
#define LAN8720A_BCTL_AUTONEG_MASK					(0x1000U)		/*!< The PHY auto negotiation bit mask. */
#define LAN8720A_BCTL_SPEED_MASK					(0x2000U)		/*!< The PHY speed bit mask. */
#define LAN8720A_BCTL_LOOP_MASK						(0x4000U)		/*!< The PHY loop bit mask. */
#define LAN8720A_BCTL_RESET_MASK					(0x8000U)		/*!< The PHY reset bit mask. */
#define LAN8720A_BCTL_SPEED_100M_MASK				(0x2000U)		/*!< The PHY 100M speed mask. */

/*! @brief Defines the mask flag in basic status register. */
#define LAN8720A_BSTATUS_LINKSTATUS_MASK			(0x0004U)		/*!< The PHY link status mask. */
#define LAN8720A_BSTATUS_AUTONEGABLE_MASK			(0x0008U)		/*!< The PHY auto-negotiation ability mask. */
#define LAN8720A_BSTATUS_AUTONEGCOMP_MASK			(0x0020U)		/*!< The PHY auto-negotiation complete mask. */

/*! @brief Defines the mask flag in PHY auto-negotiation advertise register. */
#define LAN8720A_100BASETX_FULLDUPLEX_MASK			(0x100U)		/*!< The PHY has the 100M full duplex ability.*/
#define LAN8720A_100BASETX_HALFDUPLEX_MASK			(0x080U)		/*!< The PHY has the 100M full duplex ability.*/
#define LAN8720A_10BASETX_FULLDUPLEX_MASK			(0x040U)		/*!< The PHY has the 10M full duplex ability.*/
#define LAN8720A_10BASETX_HALFDUPLEX_MASK			(0x020U)		/*!< The PHY has the 10M full duplex ability.*/

/*! @brief Defines the mask flag in PHY special control/status register. */
#define LAN8720A_SCS_AUTONEG_DONE_MASK				(0x1000U)		/*!< The PHY Auto-negotiation done indication mask. */
#define LAN8720A_SCS_10HALFDUPLEX_MASK				(0x0004U) 		/*!< The PHY 10M half duplex mask. */
#define LAN8720A_SCS_100HALFDUPLEX_MASK				(0x0008U) 		/*!< The PHY 100M half duplex mask. */
#define LAN8720A_SCS_10FULLDUPLEX_MASK				(0x0014U)  		/*!< The PHY 10M full duplex mask. */
#define LAN8720A_SCS_100FULLDUPLEX_MASK				(0x0018U) 		/*!< The PHY 100M full duplex mask. */
#define LAN8720A_SCS_SPEEDUPLX_MASK					(0x001CU)		/*!< The PHY speed and duplex mask. */
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/
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
status_t Lan8720a_Init(ENET_Type *base, uint32_t phyAddr)
{
    uint32_t counter = PHY_TIMEOUT_COUNT;
    uint32_t idReg = 0;
    status_t result = kStatus_Success;
    uint32_t instance = ENET_GetInstance(base);

//#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
//    /* Set SMI first. */
//    CLOCK_EnableClock(s_enetClock[instance]);
//#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
//    ENET_SetSMI(base, srcClock_Hz, false);

    /* Initialization after PHY stars to work. */
    while ((idReg != LAN8720A_CONTROL_ID1) && (counter != 0)) {
        ENET_Read(base, phyAddr, LAN8720A_ID1_REG, &idReg);
        counter --;
    }

    if (!counter) {
        return kStatus_Fail;
    }

    /* Reset PHY. */
    counter = PHY_TIMEOUT_COUNT;
    result = ENET_Write(base, phyAddr, LAN8720A_BASICCONTROL_REG, LAN8720A_BCTL_RESET_MASK);
    if (result == kStatus_Success) {
        /* Set the negotiation. */
        result = ENET_Write(base, phyAddr, LAN8720A_AUTONEG_ADVERTISE_REG,
                           (LAN8720A_100BASETX_FULLDUPLEX_MASK | LAN8720A_100BASETX_HALFDUPLEX_MASK |
                            LAN8720A_10BASETX_FULLDUPLEX_MASK | LAN8720A_10BASETX_HALFDUPLEX_MASK | 0x1U));
        if (result == kStatus_Success) {
            result = ENET_Write(base, phyAddr, LAN8720A_BASICCONTROL_REG,
                               (LAN8720A_BCTL_AUTONEG_MASK | LAN8720A_BCTL_RESTART_AUTONEG_MASK));
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
status_t Lan8720a_GetAutoNegotiation(ENET_Type *base, uint32_t phyAddr)
{
    uint32_t bssReg;

    if(ENET_Read(base, phyAddr, LAN8720A_BASICSTATUS_REG, &bssReg) == kStatus_Success) {
        if((bssReg & LAN8720A_BSTATUS_AUTONEGCOMP_MASK) != 0) {
            return kStatus_Success;
        }
    }
    return kStatus_PHY_AutoNegotiateFail;
}

status_t Lan8720a_GetLinkStatus(ENET_Type *base, uint32_t phyAddr, bool *status)
{
    status_t result = kStatus_Success;
    uint32_t data;

	ERR_CHECK(status != null, return kStatus_Fail);

    /* Read the basic status register. */
    result = ENET_Read(base, phyAddr, LAN8720A_BASICSTATUS_REG, &data);
    if (result == kStatus_Success) {
        if (!(LAN8720A_BSTATUS_LINKSTATUS_MASK & data)) {
            /* link down. */
            *status = false;
        } else {
            /* link up. */
            *status = true;
        }
    }
    return result;
}

status_t Lan8720a_GetLinkSpeedDuplex(ENET_Type *base, uint32_t phyAddr, phy_speed_t *speed, phy_duplex_t *duplex)
{
    status_t result = kStatus_Success;
    uint32_t data, ctlReg;

	ERR_CHECK((speed != null) && (duplex != null), return kStatus_Fail);
	
    /* Read the control two register. */
    result = ENET_Read(base, phyAddr, LAN8720A_SPECIAL_CONTROL_STATUS_REG, &ctlReg);
    if (result == kStatus_Success) {
        data = ctlReg & LAN8720A_SCS_SPEEDUPLX_MASK;
        if ((LAN8720A_SCS_10FULLDUPLEX_MASK == data) || (LAN8720A_SCS_100FULLDUPLEX_MASK == data)) {
            /* Full duplex. */
            *duplex = kPHY_FullDuplex;
        } else {
            /* Half duplex. */
            *duplex = kPHY_HalfDuplex;
        }

        data = ctlReg & LAN8720A_SCS_SPEEDUPLX_MASK;
        if ((LAN8720A_SCS_100HALFDUPLEX_MASK == data) || (LAN8720A_SCS_100FULLDUPLEX_MASK == data)) {
            /* 100M speed. */
            *speed = kPHY_Speed100M;
        } else {
            /* 10M speed. */
            *speed = kPHY_Speed10M;
        }
    }

    return result;
}


