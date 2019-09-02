#ifndef __WIFI_UNIT_H__
#define __WIFI_UNIT_H__

#include "stdint.h"
#include "conference.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* 无线单元设备API数据结构 */
typedef struct {
	void (*launch)(void);
	void (*transWithExData)(WifiUnitProtocol_S *, uint16_t , uint8_t *);
	void (*transmit)(WifiUnitProtocol_S *);
}WifiUnit_S;



/*******************************************************************************
 * API
 ******************************************************************************/
extern WifiUnit_S WifiUnit;
#endif
