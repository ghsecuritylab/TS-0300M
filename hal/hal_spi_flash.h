#ifndef __HAL_SPI_FLASH_H_
#define __HAL_SPI_FLASH_H_

#include "hal.h"
#include "fsl_lpspi.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef FLASH_W25Q64_ENABLE
#define FLASH_W25Q64_ENABLE								(ENABLE)
#endif

#define FLASH_DRIVERS_TOTAL_NUM							(FLASH_W25Q64_ENABLE)

typedef enum {
#if	FLASH_W25Q64_ENABLE
    tW25Q64,
#endif
} HAL_SpiFlashType_EN;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
status_t HAL_FlashBufferConfig(HAL_SpiFlashType_EN type,uint8_t *txbuf,uint8_t *rxbuf);
uint16_t HAL_FlashDeviceID(HAL_SpiFlashType_EN type);
bool HAL_FlashGetBusy(HAL_SpiFlashType_EN type);
status_t HAL_FlashWriteSector(HAL_SpiFlashType_EN type,uint32_t addr,uint8_t* data);
status_t HAL_FlashEraseSector(HAL_SpiFlashType_EN type,uint32_t addr);
status_t HAL_FlashReadSector(HAL_SpiFlashType_EN type,uint32_t addr,uint8_t *data);


#endif


