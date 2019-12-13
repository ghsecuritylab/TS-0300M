#ifndef __RTL8306_H_
#define __RTL8306_H_

#include "drivers_common.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
status_t Rtl8306m_Init(ENET_Type *base, uint32_t phyAddr);
status_t Rtl8306m_GetAutoNegotiation(ENET_Type *base, uint32_t phyAddr);
status_t Rtl8306m_GetLinkStatus(ENET_Type *base, uint32_t phyAddr, bool *status);
status_t Rtl8306m_GetLinkSpeedDuplex(ENET_Type *base, uint32_t phyAddr, phy_speed_t *speed, phy_duplex_t *duplex);

#endif


