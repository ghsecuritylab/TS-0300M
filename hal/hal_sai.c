/**
*
*	@FileName					hal_sai.c
*	@Author						KT
*	@CreationTime				2019/04/15
*	@Description
*
* 	@Include					hal_sai.h
*
*	@API						Sai
*
**/
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "fsl_dmamux.h"
#include "fsl_sai_edma.h"
#include "fsl_debug_console.h"
//#include "pin_mux.h"
#include "fsl_iomuxc.h"
#include "clock_config.h"
//#include "board.h"
#include "hal_sai.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if SAI1_ENABLE || SAI2_ENABLE || SAI3_ENABLE


/********** common definitions *********/
/* SAI PLL */
/* Select Audio/Video PLL (786.48 MHz) as sai clock source */
#define SAI_CLOCK_SOURCE_SELECT 								(2U)
/* Clock pre divider for sai clock source */
#define SAI_CLOCK_SOURCE_PRE_DIVIDER 							(0U)
/* Clock divider for sai clock source */
#define SAI_CLOCK_SOURCE_DIVIDER 								(63U)
/* Get frequency of sai1 clock */
#define SAI_CLK_FREQ											(CLOCK_GetFreq(kCLOCK_AudioPllClk) / (SAI_CLOCK_SOURCE_DIVIDER + 1U) / \
     															(SAI_CLOCK_SOURCE_PRE_DIVIDER + 1U))


#if defined(SAI_DMA_STATIC_MEM) && SAI_DMA_STATIC_MEM
/* 用于DMA音频接收缓存大小 */
#define SAI_DMA_BUF_SIZE										(8192)


#endif

/* 用于DMA音频接收缓存包数量 */
#define SAI_BUF_NUM												(SAI_XFER_QUEUE_SIZE)

#if (SAI_DMA_BUF_SIZE % SAI_BUF_NUM != 0)
	#error	"SAI_DMA_BUF_SIZE must be divisible by SAI_BUF_NUM"
#endif
/********** sai1 definitions *********/

#if SAI1_ENABLE

#define SAI1_CLOCK_MUX											kCLOCK_Sai1Mux
#define SAI1_CLOCK_DIV											kCLOCK_Sai1PreDiv
#define SAI1_CLOCK_PRE_DIV										kCLOCK_Sai1PreDiv
#define SAI1_TX_IRQ												SAI1_IRQn
#define SAI1_RX_IRQ												SAI1_IRQn
#define SAI1_DMA_TX_CHANNEL										(0)
#define SAI1_DMA_RX_CHANNEL										(1)
#define SAI1_DMA_TX_SOURCE										kDmaRequestMuxSai1Tx
#define SAI1_DMA_RX_SOURCE										kDmaRequestMuxSai1Rx
#define SAI1_OVER_SAMPLE_RATE 									(384U)

#endif

/********** sai2 definitions *********/
#if SAI2_ENABLE

#define SAI2_CLOCK_MUX											kCLOCK_Sai2Mux
#define SAI2_CLOCK_DIV											kCLOCK_Sai2PreDiv
#define SAI2_CLOCK_PRE_DIV										kCLOCK_Sai2PreDiv
#define SAI2_TX_IRQ												SAI2_IRQn
#define SAI2_RX_IRQ												SAI2_IRQn
#define SAI2_DMA_TX_CHANNEL										(2)
#define SAI2_DMA_RX_CHANNEL										(3)
#define SAI2_DMA_TX_SOURCE										kDmaRequestMuxSai2Tx
#define SAI2_DMA_RX_SOURCE										kDmaRequestMuxSai2Rx
#define SAI2_OVER_SAMPLE_RATE 									(384U)

#endif

/********** sai3 definitions *********/
#if SAI3_ENABLE

#define SAI3_CLOCK_MUX											kCLOCK_Sai3Mux
#define SAI3_CLOCK_DIV											kCLOCK_Sai3PreDiv
#define SAI3_CLOCK_PRE_DIV										kCLOCK_Sai3PreDiv
#define SAI3_TX_IRQ												SAI3_TX_IRQn
#define SAI3_RX_IRQ												SAI3_RX_IRQn
#define SAI3_DMA_TX_CHANNEL										(4)
#define SAI3_DMA_RX_CHANNEL										(5)
#define SAI3_DMA_TX_SOURCE										kDmaRequestMuxSai3Tx
#define SAI3_DMA_RX_SOURCE										kDmaRequestMuxSai3Rx
#define SAI3_OVER_SAMPLE_RATE 									(384U)

#endif

/* 初始化配置数据结构 */
typedef struct {
    I2S_Type *base;
    clock_mux_t mux;
    clock_div_t div;
    clock_div_t preDiv;
    IRQn_Type txIrq;
    IRQn_Type rxIrq;
    uint32_t dmaTxChannel;
    uint32_t dmaRxChannel;
    dma_request_source_t dmaTxSource;
    dma_request_source_t dmaRxSource;
    uint32_t overSampleRate;
} SaiConfig_S;

typedef struct {
    /* SAI接口类型 */
    HAL_SaiType_S type;

    /* 用于SAI传输DMA句柄 */
    sai_edma_handle_t saiTxDma;
    sai_edma_handle_t saiRxDma;

	/* DMA句柄 */
	edma_handle_t txDma;
	edma_handle_t rxDma;
	
    /* SAI格式 */
    sai_transfer_format_t format;

    /* 数据传输使能 */
    bool txEnable;
    bool rxEnable;

    /* 中断回调函数 */
    HAL_SaiCallback txCallback;
    HAL_SaiCallback rxCallback;

    /* 数据缓存 */
    uint8_t *rxDataBuf;
	uint8_t *txDataBuf;
	
    /* 数据缓存大小 */
    uint32_t rxBufSize;
	uint32_t txBufSize;
	
    /* SAI 传输数据结构*/
	sai_transfer_t rxfer[SAI_BUF_NUM];
    sai_transfer_t txfer[SAI_BUF_NUM];

	/* 自定义参数指针 */
	void *param;
} SaiHandle_S;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void HAL_SaiDmaRxCallback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData);
static void HAL_SaiDmaTxCallback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData);
static void HAL_SaiSetMclkOutput(HAL_SaiType_S type,bool enable);
/*******************************************************************************
 * Variables
 ******************************************************************************/


/* 初始化配置 */
static const SaiConfig_S SaiDefCfg[SAI_ENABLE_NUM] = {
#if SAI1_ENABLE
    {
        SAI1, SAI1_CLOCK_MUX, SAI1_CLOCK_DIV, SAI1_CLOCK_PRE_DIV, SAI1_TX_IRQ, SAI1_RX_IRQ, SAI1_DMA_TX_CHANNEL, \
        SAI1_DMA_RX_CHANNEL,  SAI1_DMA_TX_SOURCE, SAI1_DMA_RX_SOURCE, SAI1_OVER_SAMPLE_RATE
    },
#endif

#if SAI2_ENABLE
    {
        SAI2, SAI2_CLOCK_MUX, SAI2_CLOCK_DIV, SAI2_CLOCK_PRE_DIV, SAI2_TX_IRQ, SAI2_RX_IRQ, SAI2_DMA_TX_CHANNEL, \
        SAI2_DMA_RX_CHANNEL,  SAI2_DMA_TX_SOURCE, SAI2_DMA_RX_SOURCE, SAI2_OVER_SAMPLE_RATE
    },
#endif

#if SAI3_ENABLE
    {
        SAI3, SAI3_CLOCK_MUX, SAI3_CLOCK_DIV, SAI3_CLOCK_PRE_DIV, SAI3_TX_IRQ, SAI3_RX_IRQ, SAI3_DMA_TX_CHANNEL, \
        SAI3_DMA_RX_CHANNEL,  SAI3_DMA_TX_SOURCE, SAI3_DMA_RX_SOURCE, SAI3_OVER_SAMPLE_RATE
    },
#endif
};

/* Sai 控制句柄 */
static SaiHandle_S SaiHandle[SAI_ENABLE_NUM];

#if defined(SAI_DMA_STATIC_MEM) && SAI_DMA_STATIC_MEM
/* Sai 静态缓存 */
static uint8_t SaiRxBuffer[SAI_ENABLE_NUM][SAI_DMA_BUF_SIZE];
static uint8_t SaiTxBuffer[SAI_ENABLE_NUM][SAI_DMA_BUF_SIZE];
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/


/**
* @Name  		HAL_SaiInit
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
HAL_SaiHandle_S *HAL_SaiInit(HAL_SaiPara_S *para)
{

    ERR_CHECK(para != null, return null);

    sai_config_t saiTxCfg,saiRxCfg;
    SaiHandle_S *saiHandler;
    uint32_t mclkSourceClockHz = 0U;
    const SaiConfig_S *saiCfg = &SaiDefCfg[para->type];

    saiHandler = &SaiHandle[para->type];
    saiHandler->type = para->type;
	saiHandler->param = para->param;

    /*Clock setting for SAIx*/
    CLOCK_SetMux(saiCfg->mux, SAI_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(saiCfg->preDiv, SAI_CLOCK_SOURCE_PRE_DIVIDER);
    CLOCK_SetDiv(saiCfg->div, SAI_CLOCK_SOURCE_DIVIDER);

    if(para->masterSlave == kSAI_Master)
        HAL_SaiSetMclkOutput(para->type,true);

	saiHandler->saiTxDma.dmaHandle = &saiHandler->txDma;
	saiHandler->saiRxDma.dmaHandle = &saiHandler->rxDma;

    EDMA_CreateHandle(saiHandler->saiTxDma.dmaHandle, SAI_DMA, saiCfg->dmaTxChannel);
    EDMA_CreateHandle(saiHandler->saiRxDma.dmaHandle, SAI_DMA, saiCfg->dmaRxChannel);

    DMAMUX_SetSource(SAI_DMAMUX, saiCfg->dmaTxChannel, (uint8_t)saiCfg->dmaTxSource);
    DMAMUX_EnableChannel(SAI_DMAMUX, saiCfg->dmaTxChannel);
    DMAMUX_SetSource(SAI_DMAMUX, saiCfg->dmaRxChannel, (uint8_t)saiCfg->dmaRxSource);
    DMAMUX_EnableChannel(SAI_DMAMUX, saiCfg->dmaRxChannel);

    SAI_TxGetDefaultConfig(&saiTxCfg);
    SAI_RxGetDefaultConfig(&saiRxCfg);

    saiTxCfg.protocol = saiRxCfg.protocol = para->protocol;
    saiTxCfg.masterSlave = saiRxCfg.masterSlave = para->masterSlave;

    SAI_TxInit(saiCfg->base, &saiTxCfg);
    SAI_RxInit(saiCfg->base, &saiRxCfg);

    saiHandler->format.bitWidth = para->bitWidth;
    saiHandler->format.channel = 0U;
    saiHandler->format.sampleRate_Hz = para->sampleRate;
#if (defined FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER && FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER) || \
    (defined FSL_FEATURE_PCC_HAS_SAI_DIVIDER && FSL_FEATURE_PCC_HAS_SAI_DIVIDER)
    saiHandler->format.masterClockHz = saiCfg->overSampleRate * saiHandler->format.sampleRate_Hz;
#else
    saiHandler->format.masterClockHz = SAI_CLK_FREQ;
#endif
    saiHandler->format.protocol = para->protocol;
    /* 输入声道 */
    saiHandler->format.stereo = para->monoStereo;
    saiHandler->format.isFrameSyncCompact = true;
#if defined(FSL_FEATURE_SAI_FIFO_COUNT) && (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    saiHandler->format.watermark = FSL_FEATURE_SAI_FIFO_COUNT / 2U;
#endif

    mclkSourceClockHz = SAI_CLK_FREQ;
    SAI_TransferTxCreateHandleEDMA(saiCfg->base, &saiHandler->saiTxDma, HAL_SaiDmaTxCallback, saiHandler, saiHandler->saiTxDma.dmaHandle);
    SAI_TransferTxSetFormatEDMA(saiCfg->base, &saiHandler->saiTxDma, &saiHandler->format, mclkSourceClockHz, saiHandler->format.masterClockHz);

    SAI_TransferRxCreateHandleEDMA(saiCfg->base, &saiHandler->saiRxDma, HAL_SaiDmaRxCallback, saiHandler, saiHandler->saiRxDma.dmaHandle);
    SAI_TransferRxSetFormatEDMA(saiCfg->base, &saiHandler->saiRxDma, &saiHandler->format, mclkSourceClockHz, saiHandler->format.masterClockHz);

    SAI_TxEnableInterrupts(saiCfg->base, kSAI_FIFOErrorInterruptEnable);
    EnableIRQ(saiCfg->txIrq);

    SAI_RxEnableInterrupts(saiCfg->base, kSAI_FIFOErrorInterruptEnable);
    EnableIRQ(saiCfg->rxIrq);


    saiHandler->txEnable = false;
    saiHandler->rxEnable = false;

    return (HAL_SaiHandle_S *)saiHandler;
}




/**
* @Name  		HAL_SaiDisconfig
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
void HAL_SaiDisconfig(HAL_SaiHandle_S handler)
{
    ERR_CHECK(handler != null, return);


    SaiHandle_S *saiHandler = (SaiHandle_S *)handler;
    const SaiConfig_S *saiCfg = &SaiDefCfg[saiHandler->type];
    HAL_SaiType_S type = saiHandler->type;

    DisableIRQ(saiCfg->rxIrq);
    DisableIRQ(saiCfg->txIrq);

    SAI_Deinit(saiCfg->base);

    DMAMUX_DisableChannel(SAI_DMAMUX, saiCfg->dmaTxChannel);
    DMAMUX_DisableChannel(SAI_DMAMUX, saiCfg->dmaRxChannel);

    HAL_SaiSetMclkOutput(type,false);

}





/**
* @Name  		HAL_SaiStartReceive
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
#if defined(SAI_DMA_STATIC_MEM) && SAI_DMA_STATIC_MEM
void HAL_SaiStartReceive(HAL_SaiHandle_S *handler,HAL_SaiCallback callback)
#else
void HAL_SaiStartReceive(HAL_SaiHandle_S *handler,uint8_t *data,uint32_t bufSize,HAL_SaiCallback callback)
#endif
{
	SaiHandle_S *saiHandler;
    uint32_t dataSize;
    uint8_t i;

    ERR_CHECK((handler != null), return);

	saiHandler = (SaiHandle_S *)handler;

    ERR_CHECK(saiHandler->rxEnable != true, return);

#if defined(SAI_DMA_STATIC_MEM) && SAI_DMA_STATIC_MEM
	uint8_t *data = SaiRxBuffer[saiHandler->type];
	uint32_t bufSize = SAI_DMA_BUF_SIZE;
#else
	ERR_CHECK((data != null) && (bufSize != 0),return);
	/* buf长度需可以整除缓存包数量 */
	ERR_CHECK_DBG(bufSize % SAI_BUF_NUM == 0,"Data \'bufSize\' needs to be divisible by \"SAI_BUF_NUM\"",return );
#endif

	saiHandler->rxDataBuf = data;
	saiHandler->rxBufSize = bufSize;
	saiHandler->rxCallback = callback;
	
    /* 清内存 */
    memset(data, 0, bufSize);
    dataSize = bufSize / SAI_BUF_NUM;

    for (i = 0; i < SAI_BUF_NUM; i++) {
        saiHandler->rxfer[i].data = data + i * dataSize;
        saiHandler->rxfer[i].dataSize = dataSize;
    }

    saiHandler->rxEnable = true;

    for (i = 0; i < SAI_BUF_NUM; i++) {
        SAI_TransferReceiveEDMA(SaiDefCfg[saiHandler->type].base, &saiHandler->saiRxDma, &saiHandler->rxfer[i]);
    }
}

/**
* @Name  		HAL_SaiStartSend
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
#if defined(SAI_DMA_STATIC_MEM) && SAI_DMA_STATIC_MEM
void HAL_SaiStartSend(HAL_SaiHandle_S *handler,HAL_SaiCallback callback)
#else
void HAL_SaiStartSend(HAL_SaiHandle_S *handler,uint8_t *data,uint32_t bufSize,HAL_SaiCallback callback)
#endif
{
	SaiHandle_S *saiHandler;
    uint32_t dataSize;
    uint8_t i;

    ERR_CHECK((handler != null), return);
	
	saiHandler = (SaiHandle_S *)handler;

    ERR_CHECK(saiHandler->txEnable != true, return);
#if defined(SAI_DMA_STATIC_MEM) && SAI_DMA_STATIC_MEM
		uint8_t *data = SaiTxBuffer[saiHandler->type];
		uint32_t bufSize = SAI_DMA_BUF_SIZE;
#else
	ERR_CHECK((data != null) && (bufSize != 0),return);
	/* buf长度需可以整除缓存包数量 */
	ERR_CHECK_DBG(bufSize % SAI_BUF_NUM == 0,"Data \'bufSize\' needs to be divisible by \"SAI_BUF_NUM\"",return );
#endif
	
	saiHandler->txDataBuf = data;
	saiHandler->txBufSize = bufSize;
	saiHandler->txCallback = callback;
	
	/* 清内存 */
    memset(data, 0, bufSize);
    dataSize = bufSize / SAI_BUF_NUM;

    for (i = 0; i < SAI_BUF_NUM; i++) {
        saiHandler->txfer[i].data = data + i * dataSize;
        saiHandler->txfer[i].dataSize = dataSize;
    }

    saiHandler->txEnable = true;

    for (i = 0; i < SAI_BUF_NUM; i++) {
        SAI_TransferSendEDMA(SaiDefCfg[saiHandler->type].base, &saiHandler->saiTxDma, &saiHandler->txfer[i]);
    }
}



/**
* @Name  		HAL_SaiDmaRxCallback
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
void HAL_SaiStopReceive(HAL_SaiHandle_S *handler)
{
	uint8_t i;
	
    ERR_CHECK(handler != null, return);

    SaiHandle_S *saiHandler = (SaiHandle_S *)handler;

    SAI_TransferTerminateReceiveEDMA(SaiDefCfg[saiHandler->type].base, &saiHandler->saiRxDma);
	
	for (i = 0; i < SAI_BUF_NUM; i++) {
		saiHandler->rxfer[i].data = null;
		saiHandler->rxfer[i].dataSize = 0;
	}
	saiHandler->rxCallback = null;
    saiHandler->rxEnable = false;
}


/**
* @Name  		HAL_SaiStopSend
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
void HAL_SaiStopSend(HAL_SaiHandle_S *handler)
{
 	uint8_t i;
	
    ERR_CHECK(handler != null, return);

    SaiHandle_S *saiHandler = (SaiHandle_S *)handler;

    SAI_TransferTerminateReceiveEDMA(SaiDefCfg[saiHandler->type].base, &saiHandler->saiTxDma);
	
	for (i = 0; i < SAI_BUF_NUM; i++) {
		saiHandler->txfer[i].data = null;
		saiHandler->txfer[i].dataSize = 0;
	}
	saiHandler->txCallback = null;
    saiHandler->txEnable = false;
}


/**
* @Name  		HAL_SaiDmaRxCallback
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void HAL_SaiDmaRxCallback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData)
{
    SaiHandle_S *saiHandler = (SaiHandle_S *)userData;
    uint8_t index = handle->queueUser;

    /* 继续DMA接收 */
    if(saiHandler->rxEnable) {
        if(saiHandler->rxCallback != null)
            saiHandler->rxCallback((HAL_SaiHandle_S *)saiHandler,saiHandler->rxfer[index].data,saiHandler->rxfer[index].dataSize,saiHandler->param);

        /* rxfer重新放回DMA队列 */
        SAI_TransferReceiveEDMA(base, handle, &saiHandler->rxfer[index]);
    }
}


/**
* @Name  		HAL_SaiDmaTxCallback
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void HAL_SaiDmaTxCallback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData)
{
    SaiHandle_S *saiHandler = (SaiHandle_S *)userData;
    uint8_t index = handle->queueUser;

    /* 继续DMA发送 */
    if(saiHandler->txEnable) {
        if(saiHandler->txCallback != null)
            saiHandler->txCallback((HAL_SaiHandle_S *)saiHandler,saiHandler->txfer[index].data,saiHandler->txfer[index].dataSize,saiHandler->param);

        /* txfer重新放回DMA队列 */
        SAI_TransferSendEDMA(base, handle, &saiHandler->txfer[index]);
    }
}

/**
* @Name  		HAL_SaiDmaRxCallback
* @Author  		KT
* @Description
* @para
*
*
* @return
*/
static void HAL_SaiSetMclkOutput(HAL_SaiType_S type,bool enable)
{
    uint32_t saiMclkDirMask;

    switch(type) {
#if SAI1_ENABLE
    case tSai1: {
        saiMclkDirMask = IOMUXC_GPR_GPR1_SAI1_MCLK_DIR_MASK;
    }
    break;
#endif

#if SAI2_ENABLE
    case tSai2: {
        saiMclkDirMask = IOMUXC_GPR_GPR1_SAI2_MCLK_DIR_MASK;
    }
    break;
#endif

#if SAI3_ENABLE
    case tSai3: {
        saiMclkDirMask = IOMUXC_GPR_GPR1_SAI3_MCLK_DIR_MASK;
    }
    break;
#endif

    default:
        return;
    }

    if (enable) {
        IOMUXC_GPR->GPR1 |= saiMclkDirMask;
    } else {
        IOMUXC_GPR->GPR1 &= (~saiMclkDirMask);
    }
}

/***************************** IRQ Handler ***********************************/

#define SAI_TX_FIFO_ERR			1
#define SAI_RX_FIFO_ERR			2

static void HAL_SaiIrqHandler(I2S_Type *base,uint8_t type)
{


    if(type == SAI_TX_FIFO_ERR) {
        /* Clear the FEF flag */
        SAI_TxClearStatusFlags(base, kSAI_FIFOErrorFlag);
        SAI_TxSoftwareReset(base, kSAI_ResetTypeFIFO);
        /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
        	exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
        __DSB();
#endif
    } else if(type == SAI_RX_FIFO_ERR) {
        SAI_RxClearStatusFlags(base, kSAI_FIFOErrorFlag);
        SAI_RxSoftwareReset(base, kSAI_ResetTypeFIFO);
        /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
          exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
        __DSB();
#endif

    }

}

void SAI1_IRQHandler(void)
{
    if (SAI_TxGetStatusFlag(SAI1) & kSAI_FIFOErrorFlag)
        HAL_SaiIrqHandler(SAI1,SAI_TX_FIFO_ERR);

    if (SAI_RxGetStatusFlag(SAI1) & kSAI_FIFOErrorFlag)
        HAL_SaiIrqHandler(SAI1,SAI_RX_FIFO_ERR);

    __DSB();
}


void SAI2_IRQHandler(void)
{
    if (SAI_TxGetStatusFlag(SAI2) & kSAI_FIFOErrorFlag)
        HAL_SaiIrqHandler(SAI2,SAI_TX_FIFO_ERR);

    if (SAI_RxGetStatusFlag(SAI2) & kSAI_FIFOErrorFlag)
        HAL_SaiIrqHandler(SAI2,SAI_RX_FIFO_ERR);

    __DSB();
}

void SAI3_RX_IRQHandler(void)
{
    if (SAI_TxGetStatusFlag(SAI3) & kSAI_FIFOErrorFlag)
        HAL_SaiIrqHandler(SAI3,SAI_RX_FIFO_ERR);

    __DSB();
}

void SAI3_TX_IRQHandler(void)
{
    if (SAI_RxGetStatusFlag(SAI3) & kSAI_FIFOErrorFlag)
        HAL_SaiIrqHandler(SAI3,SAI_TX_FIFO_ERR);

    __DSB();
}


#endif


