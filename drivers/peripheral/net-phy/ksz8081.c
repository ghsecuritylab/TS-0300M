/**
 *
 *	@name				ksz8081.c
 *	@modify 			KT
 *	@date 				2019/07/31
 *	@brief				
 *
 *  @API				
 *
 *  @description   		
 *
 **/
#include "ksz8081.h"
#include "drivers_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Defines the PHY registers. */
#define KSZ8081_BASICCONTROL_REG 						(0x00U)			/*!< The PHY basic control register. */
#define KSZ8081_BASICSTATUS_REG 						(0x01U)			/*!< The PHY basic status register. */
#define KSZ8081_ID1_REG 								(0x02U)			/*!< The PHY ID one register. */
#define KSZ8081_ID2_REG 								(0x03U)			/*!< The PHY ID two register. */
#define KSZ8081_AUTONEG_ADVERTISE_REG 					(0x04U)			/*!< The PHY auto-negotiate advertise register. */
#define KSZ8081_CONTROL1_REG 							(0x1EU)			/*!< The PHY control one register. */
#define KSZ8081_CONTROL2_REG 							(0x1FU)			/*!< The PHY control two register. */
	
#define KSZ8081_CONTROL_ID1 							(0x22U)			/*!< The PHY ID1*/
	
/*! @brief Defines the mask flag in basic control register. */
#define KSZ8081_BCTL_DUPLEX_MASK 						(0x0100U)		/*!< The PHY duplex bit mask. */
#define KSZ8081_BCTL_RESTART_AUTONEG_MASK 				(0x0200U)		/*!< The PHY restart auto negotiation mask. */
#define KSZ8081_BCTL_AUTONEG_MASK 						(0x1000U)		/*!< The PHY auto negotiation bit mask. */
#define KSZ8081_BCTL_SPEED_MASK 						(0x2000U)		/*!< The PHY speed bit mask. */
#define KSZ8081_BCTL_LOOP_MASK 							(0x4000U)		/*!< The PHY loop bit mask. */
#define KSZ8081_BCTL_RESET_MASK 						(0x8000U)		/*!< The PHY reset bit mask. */
#define KSZ8081_BCTL_SPEED_100M_MASK  					(0x2000U)		/*!< The PHY 100M speed mask. */
	
/*!@brief Defines the mask flag of operation mode in control two register*/
#define KSZ8081_CTL2_REMOTELOOP_MASK 					(0x0004U)		/*!< The PHY remote loopback mask. */
#define KSZ8081_CTL2_REFCLK_SELECT_MASK 				(0x0080U)		/*!< The PHY RMII reference clock select. */ 
#define KSZ8081_CTL1_10HALFDUPLEX_MASK 					(0x0001U)		/*!< The PHY 10M half duplex mask. */
#define KSZ8081_CTL1_100HALFDUPLEX_MASK 				(0x0002U)		/*!< The PHY 100M half duplex mask. */
#define KSZ8081_CTL1_10FULLDUPLEX_MASK 					(0x0005U)		/*!< The PHY 10M full duplex mask. */
#define KSZ8081_CTL1_100FULLDUPLEX_MASK 				(0x0006U)		/*!< The PHY 100M full duplex mask. */
#define KSZ8081_CTL1_SPEEDUPLX_MASK 					(0x0007U)		/*!< The PHY speed and duplex mask. */
#define KSZ8081_CTL1_ENERGYDETECT_MASK 					(0x10U)			/*!< The PHY signal present on rx differential pair. */
#define KSZ8081_CTL1_LINKUP_MASK 						(0x100U)		/*!< The PHY link up. */        
#define KSZ8081_LINK_READY_MASK 						(KSZ8081_CTL1_ENERGYDETECT_MASK | KSZ8081_CTL1_LINKUP_MASK)
	   
/*! @brief Defines the mask flag in basic status register. */
#define KSZ8081_BSTATUS_LINKSTATUS_MASK 				(0x0004U)  		/*!< The PHY link status mask. */
#define KSZ8081_BSTATUS_AUTONEGABLE_MASK 				(0x0008U)		/*!< The PHY auto-negotiation ability mask. */
#define KSZ8081_BSTATUS_AUTONEGCOMP_MASK 				(0x0020U)		/*!< The PHY auto-negotiation complete mask. */
	
/*! @brief Defines the mask flag in PHY auto-negotiation advertise register. */
#define KSZ8081_100BaseT4_ABILITY_MASK 					(0x200U)		/*!< The PHY have the T4 ability. */
#define KSZ8081_100BASETX_FULLDUPLEX_MASK 				(0x100U)		/*!< The PHY has the 100M full duplex ability.*/
#define KSZ8081_100BASETX_HALFDUPLEX_MASK 				(0x080U)		/*!< The PHY has the 100M full duplex ability.*/
#define KSZ8081_10BASETX_FULLDUPLEX_MASK 				(0x040U)		/*!< The PHY has the 10M full duplex ability.*/
#define KSZ8081_10BASETX_HALFDUPLEX_MASK 				(0x020U)		/*!< The PHY has the 10M full duplex ability.*/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/
/*******************************************************************************
 * Code
 ******************************************************************************/
status_t KSZ8081_GetAutoNegotiation(ENET_Type *base, uint32_t phyAddr){
	uint32_t bssReg,ctlReg = 0;;

	if (ENET_Read(base, phyAddr, KSZ8081_BASICSTATUS_REG, &bssReg) == kStatus_Success)
	{
		ENET_Read(base, phyAddr, KSZ8081_CONTROL1_REG, &ctlReg);
		if (((bssReg & KSZ8081_BSTATUS_AUTONEGCOMP_MASK) != 0) && (ctlReg & KSZ8081_LINK_READY_MASK))
		{
			return kStatus_Success;
		}
	}
	return kStatus_PHY_AutoNegotiateFail;
}

status_t KSZ8081_PhyInit(ENET_Type *base, uint32_t phyAddr)
{
//    uint32_t bssReg;
    uint32_t counter = PHY_TIMEOUT_COUNT;
    uint32_t idReg = 0;
    status_t result = kStatus_Success;
//    uint32_t instance = ENET_GetInstance(base);
//    uint32_t timeDelay;
//    uint32_t ctlReg = 0;

//#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
//    /* Set SMI first. */
//    CLOCK_EnableClock(s_enetClock[instance]);
//#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
//    ENET_SetSMI(base, srcClock_Hz, false);

    /* Initialization after PHY stars to work. */
    while ((idReg != KSZ8081_CONTROL_ID1) && (counter != 0))
    {
        ENET_Read(base, phyAddr, KSZ8081_ID1_REG, &idReg);
        counter --;       
    }

    if (!counter)
    {
        return kStatus_Fail;
    }

    /* Reset PHY. */
    counter = PHY_TIMEOUT_COUNT;
    result = ENET_Write(base, phyAddr, KSZ8081_BASICCONTROL_REG, KSZ8081_BCTL_RESET_MASK);
    if (result == kStatus_Success)
    {

#if defined(FSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE)
        uint32_t data = 0;
        result = ENET_Read(base, phyAddr, KSZ8081_CONTROL2_REG, &data);
        if ( result != kStatus_Success)
        {
            return result;
        }
        result = ENET_Write(base, phyAddr, KSZ8081_CONTROL2_REG, (data | KSZ8081_CTL2_REFCLK_SELECT_MASK));
        if (result != kStatus_Success)
        {
            return result;
        }
#endif  /* FSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE */    
        
        /* Set the negotiation. */
        result = ENET_Write(base, phyAddr, KSZ8081_AUTONEG_ADVERTISE_REG,
                           (KSZ8081_100BASETX_FULLDUPLEX_MASK | KSZ8081_100BASETX_HALFDUPLEX_MASK |
                            KSZ8081_10BASETX_FULLDUPLEX_MASK | KSZ8081_10BASETX_HALFDUPLEX_MASK | 0x1U));
        if (result == kStatus_Success)
        {
            result = ENET_Write(base, phyAddr, KSZ8081_BASICCONTROL_REG,
                               (KSZ8081_BCTL_AUTONEG_MASK | KSZ8081_BCTL_RESTART_AUTONEG_MASK));
//            if (result == kStatus_Success)
//            {
//                /* Check auto negotiation complete. */
//                while (counter --)
//                {
//                    result = Dm9051_PhyRead(base, phyAddr, KSZ8081_BASICSTATUS_REG, &bssReg);
//                    if ( result == kStatus_Success)
//                    {
//                        Dm9051_PhyRead(base, phyAddr, KSZ8081_CONTROL1_REG, &ctlReg);
//                        if (((bssReg & KSZ8081_BSTATUS_AUTONEGCOMP_MASK) != 0) && (ctlReg & KSZ8081_LINK_READY_MASK))
//                        {
//                            /* Wait a moment for Phy status stable. */
//							for (timeDelay = 0; timeDelay < PHY_TIMEOUT_COUNT; timeDelay ++)
//                            {
//                                __ASM("nop");
//                            }
//                            break;
//                        }
//                    }

//                    if (!counter)
//                    {
//                        return kStatus_PHY_AutoNegotiateFail;
//                    }
//                }
//            }
        }
    }

    return result;
}



status_t KSZ8081_EnableLoopback(ENET_Type *base, uint32_t phyAddr, phy_loop_t mode, phy_speed_t speed, bool enable)
{
    status_t result;
    uint32_t data = 0;

    /* Set the loop mode. */
    if (enable)
    {
        if (mode == kPHY_LocalLoop)
        {
            if (speed == kPHY_Speed100M)
            {
                data = KSZ8081_BCTL_SPEED_100M_MASK | KSZ8081_BCTL_DUPLEX_MASK | KSZ8081_BCTL_LOOP_MASK;
            }
            else
            {
                data = KSZ8081_BCTL_DUPLEX_MASK | KSZ8081_BCTL_LOOP_MASK;                
            }
           return ENET_Write(base, phyAddr, KSZ8081_BASICCONTROL_REG, data);
        }
        else
        {
            /* First read the current status in control register. */
            result = ENET_Read(base, phyAddr, KSZ8081_CONTROL2_REG, &data);
            if (result == kStatus_Success)
            {
                return ENET_Write(base, phyAddr, KSZ8081_CONTROL2_REG, (data | KSZ8081_CTL2_REMOTELOOP_MASK));
            }
        }
    }
    else
    {
        /* Disable the loop mode. */
        if (mode == kPHY_LocalLoop)
        {
            /* First read the current status in control register. */
            result = ENET_Read(base, phyAddr, KSZ8081_BASICCONTROL_REG, &data);
            if (result == kStatus_Success)
            {
                data &= ~KSZ8081_BCTL_LOOP_MASK;
                return ENET_Write(base, phyAddr, KSZ8081_BASICCONTROL_REG, (data | KSZ8081_BCTL_RESTART_AUTONEG_MASK));
            }
        }
        else
        {
            /* First read the current status in control one register. */
            result = ENET_Read(base, phyAddr, KSZ8081_CONTROL2_REG, &data);
            if (result == kStatus_Success)
            {
                return ENET_Write(base, phyAddr, KSZ8081_CONTROL2_REG, (data & ~KSZ8081_CTL2_REMOTELOOP_MASK));
            }
        }
    }
    return result;
}

status_t KSZ8081_GetLinkStatus(ENET_Type *base, uint32_t phyAddr, bool *status)
{
    assert(status);

    status_t result = kStatus_Success;
    uint32_t data;

    /* Read the basic status register. */
    result = ENET_Read(base, phyAddr, KSZ8081_BASICSTATUS_REG, &data);
    if (result == kStatus_Success)
    {
        if (!(KSZ8081_BSTATUS_LINKSTATUS_MASK & data))
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

status_t KSZ8081_GetLinkSpeedDuplex(ENET_Type *base, uint32_t phyAddr, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(duplex);

    status_t result = kStatus_Success;
    uint32_t data, ctlReg;

    /* Read the control two register. */
    result = ENET_Read(base, phyAddr, KSZ8081_CONTROL1_REG, &ctlReg);
    if (result == kStatus_Success)
    {
        data = ctlReg & KSZ8081_CTL1_SPEEDUPLX_MASK;
        if ((KSZ8081_CTL1_10FULLDUPLEX_MASK == data) || (KSZ8081_CTL1_100FULLDUPLEX_MASK == data))
        {
            /* Full duplex. */
            *duplex = kPHY_FullDuplex;
        }
        else
        {
            /* Half duplex. */
            *duplex = kPHY_HalfDuplex;
        }

        data = ctlReg & KSZ8081_CTL1_SPEEDUPLX_MASK;
        if ((KSZ8081_CTL1_100HALFDUPLEX_MASK == data) || (KSZ8081_CTL1_100FULLDUPLEX_MASK == data))
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

