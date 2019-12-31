/**
 *
 *	@name				drivers_common.c
 *	@modify 			KT
 *	@date 				2019/09/30
 *	@brief
 *
 *  @API
 *
 *  @description
 *
 **/

#include "drivers_common.h"



void DRIVER_DELAY(uint32_t dly){
	for(;dly > 0;dly --){
		__asm("NOP");
	}
}
/*******************************************************************************
 * 	ENET
 ******************************************************************************/
#include "fsl_enet.h"


status_t ENET_Write(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t data)
{
    uint32_t counter;

    /* Clear the SMI interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    /* Starts a SMI write command. */
    ENET_StartSMIWrite(base, phyAddr, phyReg, kENET_MiiWriteValidFrame, data);

    /* Wait for SMI complete. */
    for (counter = PHY_TIMEOUT_COUNT; counter > 0; counter--) {
        if (ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK) {
            break;
        }
    }

    /* Check for timeout. */
    if (!counter) {
        return kStatus_PHY_SMIVisitTimeout;
    }

    /* Clear MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    return kStatus_Success;
}

status_t ENET_Read(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t *dataPtr)
{
    assert(dataPtr);

    uint32_t counter;

    /* Clear the MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    /* Starts a SMI read command operation. */
    ENET_StartSMIRead(base, phyAddr, phyReg, kENET_MiiReadValidFrame);

    /* Wait for MII complete. */
    for (counter = PHY_TIMEOUT_COUNT; counter > 0; counter--) {
        if (ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK) {
            break;
        }
    }

    /* Check for timeout. */
    if (!counter) {
        return kStatus_PHY_SMIVisitTimeout;
    }

    /* Get data from MII register. */
    *dataPtr = ENET_ReadSMIData(base);

    /* Clear MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    return kStatus_Success;
}

/*******************************************************************************
 * 	I2C
 ******************************************************************************/
status_t I2C_Write(LPI2C_Type *base,uint16_t slaveAddr,uint32_t subAdd,uint8_t subAddrSize,uint8_t *dataBuff,uint16_t dataLen)
{
    lpi2c_master_transfer_t xfer;
    status_t status;

    xfer.slaveAddress = (slaveAddr >> 1);  
    xfer.direction = kLPI2C_Write;
    xfer.subaddress = subAdd;
    xfer.subaddressSize = subAddrSize;
    xfer.data = dataBuff;
    xfer.dataSize = dataLen;
    xfer.flags = kLPI2C_TransferDefaultFlag;

    status = LPI2C_MasterTransferBlocking(base, &xfer);

    return status;
}



status_t I2C_Read(LPI2C_Type *base,uint16_t slaveAddr,uint32_t subAdd,uint8_t subAddrSize,uint8_t* dataBuffer, uint16_t dataLen)
{
    lpi2c_master_transfer_t masterXfer = {0};
    status_t status;

    masterXfer.slaveAddress = (slaveAddr >> 1);
    masterXfer.direction = kLPI2C_Read;
    masterXfer.subaddress = subAdd;
    masterXfer.subaddressSize = subAddrSize;
    masterXfer.data = dataBuffer;
    masterXfer.dataSize = dataLen;
    masterXfer.flags = kLPI2C_TransferDefaultFlag;

    status = LPI2C_MasterTransferBlocking(base, &masterXfer);

	return status;
}


/*******************************************************************************
 * 	SPI
 ******************************************************************************/
	status_t LPSPI_MasterRead(LPSPI_Type *base,uint32_t pcs,uint8_t *txData,uint8_t *rxData,uint16_t len)
	{
		status_t status;
		lpspi_transfer_t xfer = {0};
	
		ERR_CHECK((txData != null) && (rxData != null) && (len != 0), return kStatus_LPSPI_Error);
		ERR_CHECK((pcs == kLPSPI_MasterPcs0) || (pcs == kLPSPI_MasterPcs1) ||  \
				  (pcs == kLPSPI_MasterPcs2) || (pcs == kLPSPI_MasterPcs3), return kStatus_LPSPI_Error);
		
		xfer.txData = txData;
		xfer.rxData = rxData;
		xfer.dataSize = len;
		xfer.configFlags = pcs | kLPSPI_MasterByteSwap | kLPSPI_MasterPcsContinuous;
		status = LPSPI_MasterTransferBlocking(base,&xfer);
	
		return status;
	}
	
	status_t LPSPI_MasterWrite(LPSPI_Type *base,uint32_t pcs,uint8_t *txData,uint16_t len)
	{
		status_t status;
		lpspi_transfer_t xfer = {0};
	
		ERR_CHECK((txData != null) && (len != 0), return kStatus_LPSPI_Error);
		ERR_CHECK((pcs == kLPSPI_MasterPcs0) || (pcs == kLPSPI_MasterPcs1) ||  \
				  (pcs == kLPSPI_MasterPcs2) || (pcs == kLPSPI_MasterPcs3), return kStatus_LPSPI_Error);
		
		xfer.txData = txData;
		xfer.rxData = NULL;
		xfer.dataSize = len;
		xfer.configFlags = pcs | kLPSPI_MasterByteSwap | kLPSPI_MasterPcsContinuous;
		
		status = LPSPI_MasterTransferBlocking(base,&xfer);
	
		return status;
	}




