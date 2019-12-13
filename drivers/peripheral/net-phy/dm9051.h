#ifndef __DM9051_H_
#define __DM9051_H_

#include "drivers_common.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
status_t Dm9051_Loopback(LPSPI_Type *base,uint32_t pcs, phy_loop_t mode, phy_speed_t speed, bool enable);
status_t Dm9051_GetLink(LPSPI_Type *base,uint32_t pcs, bool *status);
status_t Dm9051_GetSpeedDuplex(LPSPI_Type *base,uint32_t pcs, phy_speed_t *speed, phy_duplex_t *duplex);
status_t Dm9051_GetAutoNegotiation(LPSPI_Type *base,uint32_t pcs);
status_t Dm9051_Init(LPSPI_Type *base,uint32_t pcs,uint8_t *mac,bool broadcast);
status_t Dm9051_Send(LPSPI_Type *base,uint32_t pcs,uint8_t *data, uint16_t len);
uint16_t Dm9051_Receive(LPSPI_Type *base,uint32_t pcs,uint8_t *data);
uint8_t  Dm9051_IsrGetClear(LPSPI_Type *base,uint32_t pcs);

#endif

