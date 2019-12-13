#ifndef __KSZ8081_H_
#define __KSZ8081_H_

#include "drivers_common.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
status_t KSZ8081_GetAutoNegotiation(ENET_Type *base, uint32_t phyAddr);
status_t KSZ8081_PhyInit(ENET_Type *base, uint32_t phyAddr);
status_t KSZ8081_EnableLoopback(ENET_Type *base, uint32_t phyAddr, phy_loop_t mode, phy_speed_t speed, bool enable);
status_t KSZ8081_GetLinkStatus(ENET_Type *base, uint32_t phyAddr, bool *status);
status_t KSZ8081_GetLinkSpeedDuplex(ENET_Type *base, uint32_t phyAddr, phy_speed_t *speed, phy_duplex_t *duplex);


#endif
