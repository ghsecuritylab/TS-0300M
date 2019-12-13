#ifndef __HAL_MAC_PHY_H_
#define __HAL_MAC_PHY_H_

#include "fsl_common.h"
#include "drivers_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef MAC_PHY_DM9051_ENABLE
#define MAC_PHY_DM9051_ENABLE						ENABLE
#endif


#if MAC_PHY_DM9051_ENABLE
/* Link Status Change */
#define MAC_PHY_DM9051_ISR_LINK						(1 << 5)
/*  Receive Overflow Counter Overflow */
#define MAC_PHY_DM9051_ISR_ROO						(1 << 3)
/* Receive Overflow */
#define MAC_PHY_DM9051_ISR_ROS						(1 << 2)
/* Packet Transmitted */
#define MAC_PHY_DM9051_ISR_PT						(1 << 1)
/* Packet Received */
#define MAC_PHY_DM9051_ISR_PR						(1 << 0)
#endif


typedef enum {
#if	MAC_PHY_DM9051_ENABLE
    tDm9051,
#endif
} HAL_MacPhyType_EN;


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
status_t HAL_MacPhyInit(HAL_MacPhyType_EN type,uint8_t *mac,bool broadcast);
status_t HAL_MacPhyLoopback(HAL_MacPhyType_EN type,phy_loop_t mode, phy_speed_t speed, bool enable);
status_t HAL_MacPhyGetLink(HAL_MacPhyType_EN type,bool *status);
status_t HAL_MacPhyGetSpeedDuplex(HAL_MacPhyType_EN type,phy_speed_t *speed, phy_duplex_t *duplex);	
status_t HAL_MacPhyGetAutoNegotiation(HAL_MacPhyType_EN type);
status_t HAL_MacPhySend(HAL_MacPhyType_EN type,uint8_t *data, uint16_t len);
uint16_t HAL_MacPhyReceive(HAL_MacPhyType_EN type,uint8_t *data);
uint8_t HAL_MacPhyGetIrqSta(HAL_MacPhyType_EN type);

#endif
