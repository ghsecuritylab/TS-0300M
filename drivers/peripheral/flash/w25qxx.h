#ifndef __W25Q64_H_
#define __W25Q64_H_

#include "drivers_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define W25QXX_SECTOR_SIZE								(4096)
#define W25QXX_PAGE_SIZE								(256)


typedef enum {
    kType_W25qSta_1 = 1,
    kType_W25qSta_2,
    kType_W25qSta_3,
} W25qStaType_EN;

typedef enum {
    kType_W25qAddr_3byte = 3,
    kType_W25qAddr_4byte = 4,
} W25qAddrType_EN;


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
status_t W25qxx_BufferConfig(uint8_t *txbuf,uint8_t *rxbuf);
uint16_t W25qxx_DeviceID(LPSPI_Type *base,uint32_t pcs);
bool W25qxx_GetBusy(LPSPI_Type *base,uint32_t pcs);
status_t W25qxx_WriteSector(LPSPI_Type *base,uint32_t pcs,uint8_t addrLen,uint32_t addr,uint8_t* data);
status_t W25qxx_EraseSector(LPSPI_Type *base,uint32_t pcs,uint8_t addrLen,uint32_t addr);
status_t W25qxx_ReadSector(LPSPI_Type *base,uint32_t pcs,uint8_t addrLen,uint32_t addr,uint8_t *data);


#endif



