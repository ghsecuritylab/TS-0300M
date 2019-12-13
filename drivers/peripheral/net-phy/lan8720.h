#ifndef __LAN8720_H_
#define __LAN8720_H_

#include "drivers_common.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
status_t Lan8720a_Init(ENET_Type *base, uint32_t phyAddr);
status_t Lan8720a_GetAutoNegotiation(ENET_Type *base, uint32_t phyAddr);
status_t Lan8720a_GetLinkStatus(ENET_Type *base, uint32_t phyAddr, bool *status);
status_t Lan8720a_GetLinkSpeedDuplex(ENET_Type *base, uint32_t phyAddr, phy_speed_t *speed, phy_duplex_t *duplex);

#endif
