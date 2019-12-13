/*
 *	 @FileName					 hal_spi_flash.c
 *	 @Author					 KT
 *	 @CreationTime				 2019/12/10
 *	 @Description
 *
 *	 @Include					 hal_spi_flash.h
 *
 *
 **/

#include "hal_spi_flash.h"
#include "flash/w25qxx.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if	FLASH_W25Q64_ENABLE

#ifndef FLASH_W25Q64_SPI_TYPE
#define FLASH_W25Q64_SPI_TYPE						LPSPI1
#endif

#ifndef FLASH_W25Q64_SPI_PCS
#define FLASH_W25Q64_SPI_PCS						(kLPSPI_MasterPcs0)
#endif

#ifndef FLASH_W25Q64_ADDR_LENGTH
#define FLASH_W25Q64_ADDR_LENGTH					(kType_W25qAddr_3byte)
#endif

#endif


typedef struct {

    LPSPI_Type *base;

    uint32_t pcs;

    uint8_t addrLen;

    status_t (*bufCfg)(uint8_t *txbuf,uint8_t *rxbuf);

    uint16_t (*deviceId)(LPSPI_Type *base,uint32_t pcs);

    bool (*getBusy)(LPSPI_Type *base,uint32_t pcs);

    status_t (*writeSector)(LPSPI_Type *base,uint32_t pcs,uint8_t addrLen,uint32_t addr,uint8_t* data);

    status_t (*eraseSector)(LPSPI_Type *base,uint32_t pcs,uint8_t addrLen,uint32_t addr);

    status_t (*readSector)(LPSPI_Type *base,uint32_t pcs,uint8_t addrLen,uint32_t addr,uint8_t *data);

} HAL_SpiFlash_S;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/
#if	FLASH_W25Q64_ENABLE
HAL_SpiFlash_S  W25Q64_driver = {
    .base = FLASH_W25Q64_SPI_TYPE,
    .pcs = FLASH_W25Q64_SPI_PCS,
    .addrLen = FLASH_W25Q64_ADDR_LENGTH,
    .bufCfg = W25qxx_BufferConfig,
    .deviceId = W25qxx_DeviceID,
    .getBusy = W25qxx_GetBusy,
    .writeSector = W25qxx_WriteSector,
    .eraseSector = W25qxx_EraseSector,
    .readSector = W25qxx_ReadSector,
};
#endif


static HAL_SpiFlash_S *Flash_drivers[FLASH_DRIVERS_TOTAL_NUM] = {
#if	FLASH_W25Q64_ENABLE
    &W25Q64_driver,
#endif
};

/*******************************************************************************
 * Code
 ******************************************************************************/
status_t HAL_FlashBufferConfig(HAL_SpiFlashType_EN type,uint8_t *txbuf,uint8_t *rxbuf)
{
    HAL_SpiFlash_S *flash;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < FLASH_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    flash = Flash_drivers[type];

    return flash->bufCfg(txbuf,rxbuf);

}


uint16_t HAL_FlashDeviceID(HAL_SpiFlashType_EN type)
{
    HAL_SpiFlash_S *flash;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < FLASH_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    flash = Flash_drivers[type];

    return flash->deviceId(flash->base,flash->pcs);
}


bool HAL_FlashGetBusy(HAL_SpiFlashType_EN type)
{
    HAL_SpiFlash_S *flash;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < FLASH_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    flash = Flash_drivers[type];

    return flash->getBusy(flash->base,flash->pcs);
}


status_t HAL_FlashWriteSector(HAL_SpiFlashType_EN type,uint32_t addr,uint8_t* data)
{
    HAL_SpiFlash_S *flash;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < FLASH_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    flash = Flash_drivers[type];

    return flash->writeSector(flash->base,flash->pcs,flash->addrLen,addr,data);
}


status_t HAL_FlashEraseSector(HAL_SpiFlashType_EN type,uint32_t addr)
{
    HAL_SpiFlash_S *flash;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < FLASH_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    flash = Flash_drivers[type];

    return flash->eraseSector(flash->base,flash->pcs,flash->addrLen,addr);
}


status_t HAL_FlashReadSector(HAL_SpiFlashType_EN type,uint32_t addr,uint8_t *data)
{
    HAL_SpiFlash_S *flash;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < FLASH_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    flash = Flash_drivers[type];

    return flash->readSector(flash->base,flash->pcs,flash->addrLen,addr,data);
}



