/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_phy.h"
#include "fsl_debug_console.h"

#if USE_RTOS && defined(FSL_RTOS_FREE_RTOS)
#include "FreeRTOS.h"
#include "task.h"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/

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
 
status_t PHY_PreInit(ENET_Type *base, uint32_t phyAddr, uint32_t srcClock_Hz)
{
    uint32_t bssReg;
    uint32_t counter = PHY_TIMEOUT_COUNT;
    uint32_t idReg = 0;
    status_t result = kStatus_Success;
    uint32_t instance = ENET_GetInstance(base);
    uint32_t timeDelay;
    uint32_t ctlReg = 0;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Set SMI first. */
    CLOCK_EnableClock(s_enetClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    ENET_SetSMI(base, srcClock_Hz, false);

    /* Initialization after PHY stars to work. */
    while ((idReg != PHY_CONTROL_ID1) && (counter != 0))
    {
        PHY_Read(base, phyAddr, PHY_ID1_REG, &idReg);
        counter --;       
    }

//	#define MII_BASIC_MODE_CONTROL_REG          (0x0)
//#define MII_BASIC_MODE_STATUS_REG           (0x1)
//#define MII_PHY_IDENTIFIER_1_REG            (0x2)
//#define MII_PHY_IDENTIFIER_2_REG            (0x3)
//#define MII_AUTO_NEG_ADVERTISEMENT_REG      (0x4)
//#define MII_PHY_LINK_PARTNER_ABILITY_REG    (0x5)
//#define PORT5_PHY_CONTROL_REG0						(0x16)
//#define PORT5_PHY_CONTROL_REG1						(0x18)
//	
//	PHY_Read(base, phyAddr, MII_BASIC_MODE_CONTROL_REG, &idReg);
//	PRINTF("REG:0x%02X = 0x%04X\r\n",MII_BASIC_MODE_CONTROL_REG,idReg);
//	
//	PHY_Read(base, phyAddr, MII_BASIC_MODE_STATUS_REG, &idReg);
//	PRINTF("REG:0x%02X = 0x%04X\r\n",MII_BASIC_MODE_STATUS_REG,idReg);
//	
//	PHY_Read(base, phyAddr, MII_PHY_IDENTIFIER_1_REG, &idReg);
//	PRINTF("REG:0x%02X = 0x%04X\r\n",MII_PHY_IDENTIFIER_1_REG,idReg);
//	
//	PHY_Read(base, phyAddr, MII_PHY_IDENTIFIER_2_REG, &idReg);
//	PRINTF("REG:0x%02X = 0x%04X\r\n",MII_PHY_IDENTIFIER_2_REG,idReg);
//	
//	PHY_Read(base, phyAddr, MII_AUTO_NEG_ADVERTISEMENT_REG, &idReg);
//	PRINTF("REG:0x%02X = 0x%04X\r\n",MII_AUTO_NEG_ADVERTISEMENT_REG,idReg);
//	
//	PHY_Read(base, phyAddr, MII_PHY_LINK_PARTNER_ABILITY_REG, &idReg);
//	PRINTF("REG:0x%02X = 0x%04X\r\n",MII_PHY_LINK_PARTNER_ABILITY_REG,idReg);
//	
//	PHY_Read(base, phyAddr, PORT5_PHY_CONTROL_REG0, &idReg);
//	PRINTF("REG:0x%02X = 0x%04X\r\n",PORT5_PHY_CONTROL_REG0,idReg);
//	
//	PHY_Read(base, phyAddr, PORT5_PHY_CONTROL_REG1, &idReg);
//	PRINTF("REG:0x%02X = 0x%04X\r\n",PORT5_PHY_CONTROL_REG1,idReg);
	
    if (!counter)
    {
        return kStatus_Fail;
    }

    /* Reset PHY. */
    counter = PHY_TIMEOUT_COUNT;
    result = PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result == kStatus_Success)
    {

#if defined(FSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE)
        uint32_t data = 0;
        result = PHY_Read(base, phyAddr, PHY_CONTROL2_REG, &data);
        if ( result != kStatus_Success)
        {
            return result;
        }
        result = PHY_Write(base, phyAddr, PHY_CONTROL2_REG, (data | PHY_CTL2_REFCLK_SELECT_MASK));
        if (result != kStatus_Success)
        {
            return result;
        }
#endif  /* FSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE */    
        
        /* Set the negotiation. */
        result = PHY_Write(base, phyAddr, PHY_AUTONEG_ADVERTISE_REG,
                           (PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK |
                            PHY_10BASETX_FULLDUPLEX_MASK | PHY_10BASETX_HALFDUPLEX_MASK | 0x1U));
        if (result == kStatus_Success)
        {
            result = PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG,
                               (PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
        }
    }

    return result;
} 

bool PHY_CheckAutoNegotiation(ENET_Type *base, uint32_t phyAddr){
	uint32_t bssReg,ctlReg = 0;;
	status_t result = kStatus_Success;

	result = PHY_Read(base, phyAddr, PHY_BASICSTATUS_REG, &bssReg);
	if ( result == kStatus_Success)
	{
		PHY_Read(base, phyAddr, PHY_CONTROL1_REG, &ctlReg);
		if (((bssReg & PHY_BSTATUS_AUTONEGCOMP_MASK) != 0) && (ctlReg & PHY_LINK_READY_MASK))
		{
			return true;
		}
	}
	return false;
}

#define BIT(n)								(1 << n)
	
#define RTL8306M_PHY_ID1 		0x001C
#define RTL8306M_PHY_ID2 		0xC850
#define RTL8306M_PHY_ID2_MASK 	0xFFF0


#define MII_BASIC_MODE_CONTROL_REG          (0x0)
#define MII_SOFTWARE_RESET                     BIT(15)
#define MII_AUTO_NEGOTITION                     BIT(12)
#define MII_SPEED                     BIT(13)
#define MII_DUPLEX                     BIT(8)


#define MII_BASIC_MODE_STATUS_REG           (0x1)
#define MII_AUTO_NEGOTIATION_COMPLETE          BIT(5)
#define MII_LINK_STATUS                        BIT(2)

#define MII_PHY_IDENTIFIER_1_REG              (0x2)
#define MII_PHY_IDENTIFIER_2_REG              (0x3)

#define MII_AUTO_NEG_ADVERTISEMENT_REG      (0x4)
#define PHY_100BASETX_FULLDUPLEX_MASK	0x100U		/*!< The PHY has the 100M full duplex ability.*/
#define PHY_100BASETX_HALFDUPLEX_MASK	0x080U		/*!< The PHY has the 100M full duplex ability.*/
#define PHY_10BASETX_FULLDUPLEX_MASK	0x040U		/*!< The PHY has the 10M full duplex ability.*/
#define PHY_10BASETX_HALFDUPLEX_MASK	0x020U		/*!< The PHY has the 10M full duplex ability.*/

#define MII_ASM_DIR                            BIT(11)
#define MII_PAUSE                              BIT(10)

#define MII_PHY_LINK_PARTNER_ABILITY_REG    (0x5)
#define MII_PARTNER_ASM_DIR                    BIT(11)
#define MII_PARTNER_PAUSE                      BIT(10)

/* RTL8306M-specific registers */
#define PORT5_PHY_CONTROL_REG0						(0x16)
#define PORT5_LINK_STATUS							BIT(15)
#define PORT5_LOCAL_LOOPBACK						BIT(13)
#define PORT5_NULL_VID_REPLACEMENT					BIT(12)
#define PORT5_NON_PVID_PACKERS_DISCARD				BIT(11)
#define PORT5_802_1P_PRIORITY_DISABLE				BIT(10)
#define PORT5_DIFFSERV_PRIORITY_DISABLE				BIT(9)
#define PORT5_PORTBASE_PRIORITY_DISABLE				BIT(8)
#define PORT5_AUTO_NEGOTITATION_ENABLE				BIT(6)
#define PORT5_SPEED_INDICATION_100T              	BIT(5)
#define PORT5_DUPLEX_INDICATION_FULL               	BIT(4)
#define PORT5_802_3X_FLOW_CONTROL_ABILITY			BIT(3)
#define PORT5_BACKPRESSURE_ENABLE					BIT(2)

#define PORT5_PHY_CONTROL_REG1						(0x18)
#define DISABLE_TRANSMIT_FLOW_CONTROL_OF_PORT5_MAC	BIT(14)
#define DISABLE_RECEIVE_FLOW_CONTROL_OF_PORT5_MAC	BIT(13)
#define FORCE_ASYM_FLOW_CONTROL_OF_PORT5_MAC		BIT(12)
#define PORT5_TRANSMISSION_ENABLE					BIT(11)
#define PORT5_RECEPTION_ENABLE						BIT(10)
#define PORT5_LEARNING_ENABLE						BIT(9)
#define PORT5_LOOP_STATUS							BIT(8)

void print_phy_reg(void){
	uint32_t idReg = 0;
	
	ENET_Type *base = ENET2;
	uint32_t phyAddr = 6;
	
	PHY_Read(base, phyAddr, MII_BASIC_MODE_CONTROL_REG, &idReg);
	PRINTF("REG:0x%02X = 0x%04X\r\n",MII_BASIC_MODE_CONTROL_REG,idReg);
	
	PHY_Read(base, phyAddr, MII_BASIC_MODE_STATUS_REG, &idReg);
	PRINTF("REG:0x%02X = 0x%04X\r\n",MII_BASIC_MODE_STATUS_REG,idReg);
	
	PHY_Read(base, phyAddr, MII_PHY_IDENTIFIER_1_REG, &idReg);
	PRINTF("REG:0x%02X = 0x%04X\r\n",MII_PHY_IDENTIFIER_1_REG,idReg);
	
	PHY_Read(base, phyAddr, MII_PHY_IDENTIFIER_2_REG, &idReg);
	PRINTF("REG:0x%02X = 0x%04X\r\n",MII_PHY_IDENTIFIER_2_REG,idReg);
	
	PHY_Read(base, phyAddr, MII_AUTO_NEG_ADVERTISEMENT_REG, &idReg);
	PRINTF("REG:0x%02X = 0x%04X\r\n",MII_AUTO_NEG_ADVERTISEMENT_REG,idReg);
	
	PHY_Read(base, phyAddr, MII_PHY_LINK_PARTNER_ABILITY_REG, &idReg);
	PRINTF("REG:0x%02X = 0x%04X\r\n",MII_PHY_LINK_PARTNER_ABILITY_REG,idReg);
	
	PHY_Read(base, phyAddr, PORT5_PHY_CONTROL_REG0, &idReg);
	PRINTF("REG:0x%02X = 0x%04X\r\n",PORT5_PHY_CONTROL_REG0,idReg);
	
	PHY_Read(base, phyAddr, PORT5_PHY_CONTROL_REG1, &idReg);
	PRINTF("REG:0x%02X = 0x%04X\r\n",PORT5_PHY_CONTROL_REG1,idReg);
}

status_t PHY_Init(ENET_Type *base, uint32_t phyAddr, uint32_t srcClock_Hz)
{
    uint32_t bssReg;
    uint32_t counter = PHY_TIMEOUT_COUNT;
    uint32_t idReg = 0,idReg2 = 0;
    status_t result = kStatus_Success;
    uint32_t instance = ENET_GetInstance(base);
    uint32_t timeDelay;
    uint32_t ctlReg = 0;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Set SMI first. */
    CLOCK_EnableClock(s_enetClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    ENET_SetSMI(base, srcClock_Hz, false);
	
	
	PHY_Write(base, phyAddr,MII_BASIC_MODE_CONTROL_REG, MII_SOFTWARE_RESET);

//    esp_err_t res1, res2;
//    do {
//        // Call esp_eth_smi_wait_value() with a timeout so it prints an error periodically
//        res1 = esp_eth_smi_wait_value(MII_PHY_IDENTIFIER_1_REG, RTL8306M_PHY_ID1, UINT16_MAX, 1000);
//        res2 = esp_eth_smi_wait_value(MII_PHY_IDENTIFIER_2_REG, RTL8306M_PHY_ID2, RTL8306M_PHY_ID2_MASK, 1000);
//    } while(res1 != ESP_OK || res2 != ESP_OK);

//    ets_delay_us(300);
	PRINTF("Phy reset finish\r\n");
	 while ((idReg != RTL8306M_PHY_ID1)  && (counter != 0))
    {
        PHY_Read(base, phyAddr, MII_PHY_IDENTIFIER_1_REG, &idReg);
//		PHY_Read(base, phyAddr, MII_PHY_IDENTIFIER_2_REG, &idReg2);
        counter --;       
    }
	PRINTF("Phy identify finish\r\n");
	
//	PHY_Read(base, phyAddr,MII_BASIC_MODE_CONTROL_REG,&idReg);
//	idReg |= MII_AUTO_NEGOTITION;
//	PHY_Write(base, phyAddr,MII_BASIC_MODE_CONTROL_REG, idReg);
	//Enable puase flow control
//	PHY_Read(base, phyAddr,MII_AUTO_NEG_ADVERTISEMENT_REG,&idReg);
//    idReg |= MII_PAUSE;
//    PHY_Write(base, phyAddr,MII_AUTO_NEG_ADVERTISEMENT_REG, idReg);

	

	
	//Enable auto negotitation
	PHY_Read(base, phyAddr,PORT5_PHY_CONTROL_REG0,&idReg);
    idReg |= PORT5_AUTO_NEGOTITATION_ENABLE | PORT5_LINK_STATUS;
    PHY_Write(base, phyAddr,PORT5_PHY_CONTROL_REG0, idReg);

	//Set link up
//	PHY_Read(base, phyAddr,PORT5_PHY_CONTROL_REG0,&idReg);
//    idReg |= PORT5_LINK_STATUS;
//    PHY_Write(base, phyAddr,PORT5_PHY_CONTROL_REG0, idReg);
//	
	
	PHY_Read(base, phyAddr,MII_AUTO_NEG_ADVERTISEMENT_REG,&idReg);
	idReg |= (PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK |PHY_10BASETX_FULLDUPLEX_MASK | PHY_10BASETX_HALFDUPLEX_MASK | 0x01);
	PHY_Write(base, phyAddr,MII_AUTO_NEG_ADVERTISEMENT_REG, idReg);

//	PHY_Write(base, phyAddr, MII_BASIC_MODE_CONTROL_REG,(PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));

	
	print_phy_reg();
	PRINTF("Phy config finish\r\n");
	
	
#if 0
    /* Initialization after PHY stars to work. */
    while ((idReg != PHY_CONTROL_ID1) && (counter != 0))
    {
        PHY_Read(base, phyAddr, PHY_ID1_REG, &idReg);
        counter --;       
    }

    if (!counter)
    {
        return kStatus_Fail;
    }

    /* Reset PHY. */
    counter = PHY_TIMEOUT_COUNT;
    result = PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result == kStatus_Success)
    {

#if defined(FSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE)
        uint32_t data = 0;
        result = PHY_Read(base, phyAddr, PHY_CONTROL2_REG, &data);
        if ( result != kStatus_Success)
        {
            return result;
        }
        result = PHY_Write(base, phyAddr, PHY_CONTROL2_REG, (data | PHY_CTL2_REFCLK_SELECT_MASK));
        if (result != kStatus_Success)
        {
            return result;
        }
#endif  /* FSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE */    
        
        /* Set the negotiation. */
        result = PHY_Write(base, phyAddr, PHY_AUTONEG_ADVERTISE_REG,
                           (PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK |
                            PHY_10BASETX_FULLDUPLEX_MASK | PHY_10BASETX_HALFDUPLEX_MASK | 0x1U));
        if (result == kStatus_Success)
        {
            result = PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG,
                               (PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
//            if (result == kStatus_Success)
//            {
//                /* Check auto negotiation complete. */
//                while (counter --)
//                {
//                    result = PHY_Read(base, phyAddr, PHY_BASICSTATUS_REG, &bssReg);
//                    if ( result == kStatus_Success)
//                    {
//                        PHY_Read(base, phyAddr, PHY_CONTROL1_REG, &ctlReg);
//                        if (((bssReg & PHY_BSTATUS_AUTONEGCOMP_MASK) != 0) && (ctlReg & PHY_LINK_READY_MASK))
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
#endif
    return kStatus_Success;
}

status_t PHY_Write(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t data)
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

status_t PHY_Read(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t *dataPtr)
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

status_t PHY_EnableLoopback(ENET_Type *base, uint32_t phyAddr, phy_loop_t mode, phy_speed_t speed, bool enable)
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
                data = PHY_BCTL_SPEED_100M_MASK | PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
            }
            else
            {
                data = PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;                
            }
           return PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG, data);
        }
        else
        {
            /* First read the current status in control register. */
            result = PHY_Read(base, phyAddr, PHY_CONTROL2_REG, &data);
            if (result == kStatus_Success)
            {
                return PHY_Write(base, phyAddr, PHY_CONTROL2_REG, (data | PHY_CTL2_REMOTELOOP_MASK));
            }
        }
    }
    else
    {
        /* Disable the loop mode. */
        if (mode == kPHY_LocalLoop)
        {
            /* First read the current status in control register. */
            result = PHY_Read(base, phyAddr, PHY_BASICCONTROL_REG, &data);
            if (result == kStatus_Success)
            {
                data &= ~PHY_BCTL_LOOP_MASK;
                return PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG, (data | PHY_BCTL_RESTART_AUTONEG_MASK));
            }
        }
        else
        {
            /* First read the current status in control one register. */
            result = PHY_Read(base, phyAddr, PHY_CONTROL2_REG, &data);
            if (result == kStatus_Success)
            {
                return PHY_Write(base, phyAddr, PHY_CONTROL2_REG, (data & ~PHY_CTL2_REMOTELOOP_MASK));
            }
        }
    }
    return result;
}

status_t PHY_GetLinkStatus(ENET_Type *base, uint32_t phyAddr, bool *status)
{
    assert(status);

    status_t result = kStatus_Success;
    uint32_t data;

    /* Read the basic status register. */
    result = PHY_Read(base, phyAddr, PHY_BASICSTATUS_REG, &data);
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

status_t PHY_GetLinkSpeedDuplex(ENET_Type *base, uint32_t phyAddr, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(duplex);

    status_t result = kStatus_Success;
    uint32_t data, ctlReg;

    /* Read the control two register. */
    result = PHY_Read(base, phyAddr, MII_BASIC_MODE_CONTROL_REG, &ctlReg);
    if (result == kStatus_Success)
    {
//        data = ctlReg & PHY_CTL1_SPEEDUPLX_MASK;
//        if ((PHY_CTL1_10FULLDUPLEX_MASK == data) || (PHY_CTL1_100FULLDUPLEX_MASK == data))
		if(ctlReg & MII_DUPLEX)
        {
            /* Full duplex. */
            *duplex = kPHY_FullDuplex;
        }
        else
        {
            /* Half duplex. */
            *duplex = kPHY_HalfDuplex;
        }

//        data = ctlReg & PHY_CTL1_SPEEDUPLX_MASK;
        if (ctlReg & MII_SPEED)
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

