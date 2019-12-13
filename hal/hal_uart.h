#ifndef __HAL_UART_H_
#define __HAL_UART_H_

#include "fsl_common.h"
#include "fsl_lpuart.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define HAL_UART_HANDLER_SIZE				(24)	

typedef void * HAL_UartHandler_S;


/* UART中断回调函数 */
typedef void(*UartIrqCallback)(uint8_t count,void *para);


typedef struct {
	LPUART_Type *base;
    uint32_t baudRate;                  
    uint8_t enableRx;                       
    uint8_t enableTx;  
	bool rxIrq;
	bool txIrq;
}HAL_UartConfig_S;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
status_t HAL_UartInit(HAL_UartHandler_S handle, HAL_UartConfig_S *config);
status_t HAL_UartDeinit(HAL_UartHandler_S handle);
status_t HAL_UartSetCallback(HAL_UartHandler_S handle, uint8_t *data,uint32_t maxSize, UartIrqCallback callback,void *para);
status_t HAL_UartClearCount(HAL_UartHandler_S handle);
status_t HAL_UartReceive(HAL_UartHandler_S handle, uint8_t *data, size_t length);
status_t HAL_UartSend(HAL_UartHandler_S handle, const uint8_t *data, size_t length);

#endif

