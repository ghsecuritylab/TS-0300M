/**
 *
 *	@name				w25qxx.c
 *	@modify 			KT
 *	@date 				2019/12/10
 *	@brief
 *
 *  @API
 *
 *  @description
 *
 **/

#include "flash/w25qxx.h"
#include "fsl_lpspi.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define W25QXX_WRITE_ENABLE										(0x06)
#define W25QXX_WRITE_DISABLE									(0x04)
#define W25QXX_READ_STA_REG_1									(0x05)
#define W25QXX_READ_STA_REG_2									(0x35)
#define W25QXX_READ_STA_REG_3									(0x15)
#define W25QXX_WRITE_STA_REG_1    								(0x01)
#define W25QXX_WRITE_STA_REG_2    								(0x31)
#define W25QXX_WRITE_STA_REG_3    								(0x11)
#define W25QXX_READ_DATA										(0x03)
#define W25QXX_FAST_READ_DATA									(0x0B)
#define W25QXX_FAST_READ_DUAL									(0x3B)
#define W25QXX_PAGE_PROGRAM										(0x02)
#define W25QXX_BLOCK_ERASE										(0xD8)
#define W25QXX_CHIP_ERASE										(0xC7)
#define W25QXX_SECTOR_ERASE										(0x20)
#define W25QXX_POWER_DOWN										(0xB9)
#define W25QXX_RELEASE_POWER_DOWN								(0xAB)
#define W25QXX_DEV_ID											(0xAB)
#define W25QXX_MANUFACT_DEV_ID									(0x90)
#define W25QXX_JEDEC_DEV_ID										(0x9F)
#define W25QXX_EBABLE_4BYTE_ADDR    							(0xB7)
#define W25QXX_EXIT_4BYTE_ADDR      							(0xE9)

#define W25QXX_PAGE_NUM_EACH_SECTOR								(W25QXX_SECTOR_SIZE / W25QXX_PAGE_SIZE)


#define W25QXX_WRITE_START(_base,_pcs)							W25qxx_SpiWrite(_base, _pcs, W25QXX_WRITE_ENABLE)
//#define W25QXX_READ_ENABLE(_base,_pcs)							W25qxx_SpiWrite(_base, _pcs, W25QXX_READ_DATA);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint8_t *TxBuffer = null;
static uint8_t *RxBuffer = null;


/*******************************************************************************
 * Code
 ******************************************************************************/
static uint8_t W25qxx_SpiRead(LPSPI_Type *base,uint32_t pcs,uint8_t reg)
{
    uint8_t txData[2] = {0},rxData[2] = {0};

    txData[0] = reg;
    LPSPI_MasterRead(base,pcs,txData,rxData,2);

    return rxData[1];
}

static void W25qxx_SpiWrite(LPSPI_Type *base,uint32_t pcs,uint8_t data)
{

    LPSPI_MasterWrite(base,pcs,&data,1);
}

static void W25qxx_SpiWriteBuf(LPSPI_Type *base,uint32_t pcs,uint8_t *txData,uint16_t len)
{

    LPSPI_MasterWrite(base,pcs,txData,len);
}


static void W25qxx_SpiWReadBuf(LPSPI_Type *base,uint32_t pcs,uint8_t *txData,uint8_t *rxData,uint16_t len)
{
    LPSPI_MasterRead(base,pcs,txData,rxData,len);
}


static uint8_t W25qxx_GetStaReg(LPSPI_Type *base,uint32_t pcs,uint8_t type)
{
    uint8_t reg,state;
    switch(type) {
    case kType_W25qSta_1:
        reg = W25QXX_READ_STA_REG_1;
        break;
    case kType_W25qSta_2:
        reg = W25QXX_READ_STA_REG_2;
        break;
    case kType_W25qSta_3:
        reg = W25QXX_READ_STA_REG_3;
        break;

    default:
        return 0;
    }

    state = W25qxx_SpiRead(base,pcs,reg);

    return state;
}

status_t W25qxx_BufferConfig(uint8_t *txbuf,uint8_t *rxbuf)
{
	ERR_CHECK(txbuf != 0 && rxbuf != 0, return kStatus_Fail);

    TxBuffer = txbuf;
    RxBuffer = rxbuf;

	return kStatus_Success;
}


uint16_t W25qxx_DeviceID(LPSPI_Type *base,uint32_t pcs)
{
    uint8_t txData[6] = {0},rxData[6] = {0};

    txData[0] = W25QXX_MANUFACT_DEV_ID;
    W25qxx_SpiWReadBuf(base,pcs,txData,rxData,6);
    return (uint16_t)(rxData[4] << 8 | rxData[5]);
}



bool W25qxx_GetBusy(LPSPI_Type *base,uint32_t pcs)
{
    return ((W25qxx_GetStaReg(base,pcs,kType_W25qSta_1) & 0x01) == 0x01);
}



static status_t W25qxx_WritePage(LPSPI_Type *base,uint32_t pcs,uint8_t addrLen,uint32_t addr,uint8_t* data)
{
    uint32_t totalSize = addrLen + W25QXX_PAGE_SIZE + 1;

	ERR_CHECK(((addr % W25QXX_PAGE_SIZE) == 0) && (data != null), return kStatus_Fail);

    W25QXX_WRITE_START(base, pcs);

    TxBuffer[0] = W25QXX_PAGE_PROGRAM;
    if(addrLen == kType_W25qAddr_4byte) {              //如果是W25Q256的话地址为4字节的，要发送最高8位
        TxBuffer[1] = (uint8_t)(addr >> 24);
        TxBuffer[2] = (uint8_t)(addr >> 16);
        TxBuffer[3] = (uint8_t)(addr >> 8);
        TxBuffer[4] = (uint8_t)(addr);
    } else if(addrLen == kType_W25qAddr_3byte) {
        TxBuffer[1] = (uint8_t)(addr >> 16);
        TxBuffer[2] = (uint8_t)(addr >> 8);
        TxBuffer[3] = (uint8_t)(addr);
    } else
        return kStatus_Fail;


    memcpy(&TxBuffer[addrLen + 1],data,W25QXX_PAGE_SIZE);

    W25qxx_SpiWriteBuf(base,pcs,TxBuffer,totalSize);

    memset(TxBuffer,0,totalSize);

//	W25qxx_WaitBusy();
	while(W25qxx_GetBusy(base, pcs)) {
    }

	return kStatus_Success;
}

status_t W25qxx_WriteSector(LPSPI_Type *base,uint32_t pcs,uint8_t addrLen,uint32_t addr,uint8_t* data)
{
    uint8_t i;

	ERR_CHECK(((addr % W25QXX_SECTOR_SIZE) == 0) && (data != null), return kStatus_Fail);

    for(i = 0; i < W25QXX_PAGE_NUM_EACH_SECTOR; i++) {
        if(W25qxx_WritePage(base,pcs,addrLen,(addr + i * W25QXX_PAGE_SIZE),&data[i * W25QXX_PAGE_SIZE]) != kStatus_Success)
			return kStatus_Fail;
	
    }
	return kStatus_Success;
}


status_t W25qxx_EraseSector(LPSPI_Type *base,uint32_t pcs,uint8_t addrLen,uint32_t addr)
{

	ERR_CHECK((addr % W25QXX_SECTOR_SIZE) == 0, return kStatus_Fail);

    W25QXX_WRITE_START(base, pcs);                 //SET WEL

//    W25qxx_WaitBusy();
    while(W25qxx_GetBusy(base, pcs)) {
    }

    TxBuffer[0] = W25QXX_SECTOR_ERASE;
    if(addrLen == kType_W25qAddr_4byte) {
        TxBuffer[1] = (uint8_t)(addr >> 24);
        TxBuffer[2] = (uint8_t)(addr >> 16);
        TxBuffer[3] = (uint8_t)(addr >> 8);
        TxBuffer[4] = (uint8_t)(addr);
    } else if(addrLen == kType_W25qAddr_3byte) {
        TxBuffer[1] = (uint8_t)(addr >> 16);
        TxBuffer[2] = (uint8_t)(addr >> 8);
        TxBuffer[3] = (uint8_t)(addr);
    } else
        return kStatus_Fail;

    W25qxx_SpiWriteBuf(base,pcs,TxBuffer,addrLen + 1);

//    W25QXX_Wait_Busy();   				    //等待擦除完成

	return kStatus_Success;
}


status_t W25qxx_ReadSector(LPSPI_Type *base,uint32_t pcs,uint8_t addrLen,uint32_t addr,uint8_t *data)
{
    ERR_CHECK(((addr % W25QXX_SECTOR_SIZE) == 0) && (data != null), return kStatus_Fail);

    TxBuffer[0] = W25QXX_READ_DATA;
    if(addrLen == kType_W25qAddr_4byte) {
        TxBuffer[1] = (uint8_t)(addr >> 24);
        TxBuffer[2] = (uint8_t)(addr >> 16);
        TxBuffer[3] = (uint8_t)(addr >> 8);
        TxBuffer[4] = (uint8_t)(addr);
    } else if(addrLen == kType_W25qAddr_3byte) {
        TxBuffer[1] = (uint8_t)(addr >> 16);
        TxBuffer[2] = (uint8_t)(addr >> 8);
        TxBuffer[3] = (uint8_t)(addr);
    } else
        return kStatus_Fail;

    W25qxx_SpiWReadBuf(base,pcs,TxBuffer,RxBuffer,addrLen + W25QXX_SECTOR_SIZE + 1);

    memcpy(data,&RxBuffer[addrLen+1],W25QXX_SECTOR_SIZE);
	return kStatus_Success;
}




