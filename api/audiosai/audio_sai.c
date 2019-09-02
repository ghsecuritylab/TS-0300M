 /**
 *
 *	@FileName								audioRecord.c
 *	@Author									KT
 *	@CreationTime						2019/04/15
 *	@Description						
 *
 * 	@Include								audio_record.h	
 *
 *	@API										audioSai 
 *
 **/
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "board.h"
#include "fsl_dmamux.h"
#include "fsl_sai_edma.h"
#include "fsl_debug_console.h"
#include "debug.h"
#include "fsl_wm8960.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "audio_sai.h"
#include "ram.h"
#include "app_common.h"
#include "board.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*********** WM8960 ***********/
#define AUDIO_CODEC_WM8960

/*********** SAI ***********/
#define AUDIO_SAI 							SAI2
#define AUDIO_SAI_CHANNEL 			(0)

/* Select Audio/Video PLL (786.48 MHz) as sai1 clock source */
#define AUDIO_SAI1_CLOCK_SOURCE_SELECT 			(2U)
/* Clock pre divider for sai1 clock source */
#define AUDIO_SAI1_CLOCK_SOURCE_PRE_DIVIDER (0U)
/* Clock divider for sai1 clock source */
#define AUDIO_SAI1_CLOCK_SOURCE_DIVIDER 		(63U)
/* Get frequency of sai1 clock */
#define AUDIO_SAI_CLK_FREQ                                                        \
    (CLOCK_GetFreq(kCLOCK_AudioPllClk) / (AUDIO_SAI1_CLOCK_SOURCE_DIVIDER + 1U) / \
     (AUDIO_SAI1_CLOCK_SOURCE_PRE_DIVIDER + 1U))

/*********** IRQ ***********/
#define SAI_UserIRQHandler 			SAI2_IRQHandler
#define AUDIO_SAI_IRQ 					SAI2_IRQn
#define AUDIO_SAI_TX_IRQ 				SAI2_IRQn
#define AUDIO_SAI_RX_IRQ 				SAI2_IRQn

/*********** DMA ***********/
#define AUDIO_DMA 						DMA0
#define AUDIO_DMAMUX 					DMAMUX
#define AUDIO_TX_CHANNEL 			(0U)
#define AUDIO_RX_CHANNEL 			(1U)

#define AUDIO_SAI_TX_SOURCE 	kDmaRequestMuxSai2Tx
#define AUDIO_SAI_RX_SOURCE 	kDmaRequestMuxSai2Rx

/*********** I2C ***********/
/* I2C instance and clock */
#define AUDIO_I2C 												LPI2C1
/* Select USB1 PLL (480 MHz) as master lpi2c clock source */
#define AUDIO_LPI2C_CLOCK_SOURCE_SELECT 	(0U)
/* Clock divider for master lpi2c clock source */
#define AUDIO_LPI2C_CLOCK_SOURCE_DIVIDER 	(5U)
/* Get frequency of lpi2c clock */
#define AUDIO_I2C_CLK_FREQ 								((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (AUDIO_LPI2C_CLOCK_SOURCE_DIVIDER + 1U))

/*********** Sampling ***********/
#define OVER_SAMPLE_RATE 			(384U)
#define SAMPLE_RATE 					(kSAI_SampleRate96KHz)//kSAI_SampleRate48KHz
#define BITS_PER_SAMPLE 			(kSAI_WordWidth16bits)
#define BUFFER_SIZE 					(8192)
#define BUFFER_NUM 						(SAI_XFER_QUEUE_SIZE)
#define BUFFER_TOTAL_SIZE			(BUFFER_SIZE*BUFFER_NUM)


typedef struct
{
    /* 数据传输类型标志 */
    TransmitType_EN type;
		/* 数据传输使能 */
    bool enable;
		/* 数据头标号 */
    uint8_t head;
		/* 数据尾标号 */
    uint8_t end;
		
		
		/* 数据缓存(数据缓存会被分割为多个个buf) */
    uint8_t *audioCache;
		/* 已写入数据buf数目 */
    uint8_t filledBufNum;
		/* 数据缓存单个buf大小 */
		uint32_t bufSize;
		/* audioCache被分成buf的数量（一般等于BUFFER_NUM） */	
		uint8_t totalBufNum;
		/* buf总大小（等于audioCache大小） */	
		uint32_t totalBufSize;
		
    sai_transfer_t xfer[BUFFER_NUM];

    /* 音频输入、输出数据流控制句柄指针 */
    DataStreamHandler_S *dataStream;
} TransmitHandler;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void AUDIO_SAI_Init(void);
static void AUDIO_SAI_Deinit(void);
static void AUDIO_SAI_ReceiveStart(TransmitType_EN type);
static void AUDIO_SAI_SendStart(void);
static void AUDIO_SAI_ReceiveStop(void);
static void AUDIO_SAI_SendStop(void);
static uint32_t AUDIO_SAI_DataOutput(uint8_t *buf,uint32_t maxSize);
static void AUDIO_SAI_setRxDataStreamHandler_S(DataStreamHandler_S *dataStreamHandler);
static void AUDIO_SAI_setTxDataStreamHandler_S(DataStreamHandler_S *dataStreamHandler);
static void AUDIO_SAI_DataInput(uint8_t *buf);
static void txCallback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData);
static void rxCallback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData);
static void BOARD_EnableSaiMclkOutput(bool enable);
static void BOARD_USDHCClockConfiguration(void);
/*******************************************************************************
 * Variables
 ******************************************************************************/
static sai_edma_handle_t *txHandle = NULL;
static edma_handle_t *dmaTxHandle = NULL;
static sai_edma_handle_t *rxHandle = NULL;
static edma_handle_t *dmaRxHandle = NULL;
static sai_transfer_format_t *format = NULL;

static codec_handle_t codecHandle = {0};
//static codec_handle_t *codecHandle = NULL;
extern codec_config_t boardCodecConfig;
//static codec_config_t boardCodecConfig = {.I2C_SendFunc = BOARD_Codec_I2C_Send,
//                                   .I2C_ReceiveFunc = BOARD_Codec_I2C_Receive,
//                                   .op.Init = WM8960_Init,
//                                   .op.Deinit = WM8960_Deinit,
//                                   .op.SetFormat = WM8960_ConfigDataFormat};


/* 音频数据传输控制句柄 */
static TransmitHandler rxHandler;
static TransmitHandler txHandler;

/* 数据传输类型标志 */
//static TransmitType_EN transmitType = normal;

/* 音频输入、输出数据流控制句柄指针 */
//static DataStreamHandler_S *rxDataStream = NULL;
//static DataStreamHandler_S *txDataStream = NULL;

/* 音频输入相关变量 */
//接收功能使能标志位
//static BOOL receiving = false;


//static uint8_t rxBufHead,rxBufEnd,rxFillBufNum;

//static sai_transfer_t rxfer[BUFFER_NUM];

//static uint8_t *rxAudioBuff = NULL;

/* 音频输出相关变量 */
//static BOOL sending = false;


//static uint8_t txBufHead,txBufEnd,txBufNum;

//static sai_transfer_t txfer[BUFFER_NUM];

//static uint8_t *txAudioBuff = NULL;


//#if defined(AUDIO_CODEC_WM8960)
//wm8960_handle_t codecHandle = {0};
//#endif

//lpi2c_master_handle_t i2cHandle = {0};

/*
 * AUDIO PLL setting: Frequency = Fref * (DIV_SELECT + NUM / DENOM)
 *                              = 24 * (32 + 77/100)
 *                              = 786.48 MHz
 */
static const clock_audio_pll_config_t audioPllConfig = {
    .loopDivider = 32,  /* PLL loop divider. Valid range for DIV_SELECT divider value: 27~54. */
    .postDivider = 1,   /* Divider after the PLL, should only be 1, 2, 4, 8, 16. */
    .numerator = 77,    /* 30 bit numerator of fractional loop divider. */
    .denominator = 100, /* 30 bit denominator of fractional loop divider */
};


AudioSai_S AudioSai = {
    .init = AUDIO_SAI_Init,
    .deinit = AUDIO_SAI_Deinit,
    .recStart = AUDIO_SAI_ReceiveStart,
		.recStop = AUDIO_SAI_ReceiveStop,
    .sendStart = AUDIO_SAI_SendStart,
    .sendStop = AUDIO_SAI_SendStop,
    .dataOutput = AUDIO_SAI_DataOutput,
    .dataInput = AUDIO_SAI_DataInput,
    .setInputStream = AUDIO_SAI_setRxDataStreamHandler_S,
    .setOutputStream = AUDIO_SAI_setTxDataStreamHandler_S,
};

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @func 初始化变量内存分配
 */
static bool AUDIO_SAI_MemAlloc(void) {

    txHandle = MALLOC(sizeof(sai_edma_handle_t));
    rxHandle = MALLOC(sizeof(sai_edma_handle_t));
    dmaTxHandle = MALLOC(sizeof(edma_handle_t));
    dmaRxHandle = MALLOC(sizeof(edma_handle_t));
    format = MALLOC(sizeof(sai_transfer_format_t));
//		codecHandle = MALLOC(sizeof(codec_handle_t));

    if(!txHandle || !rxHandle || !dmaTxHandle || !dmaRxHandle || !format )
        return false;
    else
        return true;
}

/*!
 * @func 变量内存释放
 */
static void AUDIO_SAI_MemFree(void)
{
    FREE(txHandle);
    FREE(rxHandle);
    FREE(dmaTxHandle);
    FREE(dmaRxHandle);
    FREE(format);
}




/*!
 * @func 音频初始化
 */
static void AUDIO_SAI_Init(void) {
    sai_config_t config;
    uint32_t mclkSourceClockHz = 0U;
    edma_config_t dmaConfig = {0};
//    lpi2c_master_config_t i2cConfig = {0};
//    uint32_t i2cSourceClock;

    if(!AUDIO_SAI_MemAlloc()) {
        debug("Audio sai init variable memory alloc fail!!\r\n");
        return;
    }
		
		rxHandler.type = txHandler.type = normal;
		rxHandler.dataStream = txHandler.dataStream = NULL;

    CLOCK_InitAudioPll(&audioPllConfig);
    BOARD_USDHCClockConfiguration();

    /*Clock setting for LPI2C*/
    CLOCK_SetMux(kCLOCK_Lpi2cMux, AUDIO_LPI2C_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, AUDIO_LPI2C_CLOCK_SOURCE_DIVIDER);

    /*Clock setting for SAI2*/
		CLOCK_SetMux(kCLOCK_Sai2Mux, AUDIO_SAI1_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Sai2PreDiv, AUDIO_SAI1_CLOCK_SOURCE_PRE_DIVIDER);
    CLOCK_SetDiv(kCLOCK_Sai2Div, AUDIO_SAI1_CLOCK_SOURCE_DIVIDER);

    /*Enable MCLK clock*/
    BOARD_EnableSaiMclkOutput(true);
		BOARD_Codec_I2C_Init();
    /* Create EDMA handle */
    /*
     * dmaConfig.enableRoundRobinArbitration = false;
     * dmaConfig.enableHaltOnError = true;
     * dmaConfig.enableContinuousLinkMode = false;
     * dmaConfig.enableDebugMode = false;
     */
    EDMA_GetDefaultConfig(&dmaConfig);
    EDMA_Init(AUDIO_DMA, &dmaConfig);
    EDMA_CreateHandle(dmaTxHandle, AUDIO_DMA, AUDIO_TX_CHANNEL);
    EDMA_CreateHandle(dmaRxHandle, AUDIO_DMA, AUDIO_RX_CHANNEL);

    DMAMUX_Init(AUDIO_DMAMUX);
    DMAMUX_SetSource(AUDIO_DMAMUX, AUDIO_TX_CHANNEL, (uint8_t)AUDIO_SAI_TX_SOURCE);
    DMAMUX_EnableChannel(AUDIO_DMAMUX, AUDIO_TX_CHANNEL);
    DMAMUX_SetSource(AUDIO_DMAMUX, AUDIO_RX_CHANNEL, (uint8_t)AUDIO_SAI_RX_SOURCE);
    DMAMUX_EnableChannel(AUDIO_DMAMUX, AUDIO_RX_CHANNEL);

    /* Init SAI module */
    /*
     * config.masterSlave = kSAI_Master;
     * config.mclkSource = kSAI_MclkSourceSysclk;
     * config.protocol = kSAI_BusLeftJustified;
     * config.syncMode = kSAI_ModeAsync;
     * config.mclkOutputEnable = true;
     */
    SAI_TxGetDefaultConfig(&config);
    SAI_TxInit(AUDIO_SAI, &config);

    /* Initialize SAI Rx */
    SAI_RxGetDefaultConfig(&config);
    SAI_RxInit(AUDIO_SAI, &config);

    /* Configure the audio format */
    format->bitWidth = kSAI_WordWidth16bits;
    format->channel = 0U;
    format->sampleRate_Hz = SAMPLE_RATE;
#if (defined FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER && FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER) || \
    (defined FSL_FEATURE_PCC_HAS_SAI_DIVIDER && FSL_FEATURE_PCC_HAS_SAI_DIVIDER)
    format.masterClockHz = OVER_SAMPLE_RATE * format.sampleRate_Hz;
#else
    format->masterClockHz = AUDIO_SAI_CLK_FREQ;
#endif
    format->protocol = config.protocol;
    /* 单声道输入， */
    format->stereo = kSAI_MonoRight;  //kSAI_MonoLeft  kSAI_Stereo   kSAI_MonoRight
		format->isFrameSyncCompact = true;
#if defined(FSL_FEATURE_SAI_FIFO_COUNT) && (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    format->watermark = FSL_FEATURE_SAI_FIFO_COUNT / 2U;
#endif

    /* Configure Sgtl5000 I2C */
//    codecHandle.base = AUDIO_I2C;
//    codecHandle.i2cHandle = &i2cHandle;
//    i2cSourceClock = AUDIO_I2C_CLK_FREQ;

    /* Use default setting to init codec */
    CODEC_Init(&codecHandle, &boardCodecConfig);
    CODEC_SetFormat(&codecHandle, format->masterClockHz, format->sampleRate_Hz, format->bitWidth);
#if defined CODEC_USER_CONFIG
    BOARD_Codec_Config(&codecHandle);
#endif
    /*
     * i2cConfig.debugEnable = false;
     * i2cConfig.ignoreAck = false;
     * i2cConfig.pinConfig = kLPI2C_2PinOpenDrain;
     * i2cConfig.baudRate_Hz = 100000U;
     * i2cConfig.busIdleTimeout_ns = 0;
     * i2cConfig.pinLowTimeout_ns = 0;
     * i2cConfig.sdaGlitchFilterWidth_ns = 0;
     * i2cConfig.sclGlitchFilterWidth_ns = 0;
     */
//    LPI2C_MasterGetDefaultConfig(&i2cConfig);
//    LPI2C_MasterInit(AUDIO_I2C, &i2cConfig, i2cSourceClock);
//    LPI2C_MasterTransferCreateHandle(AUDIO_I2C, &i2cHandle, NULL, NULL);

//#if defined(AUDIO_CODEC_WM8960)
//    WM8960_Init(&codecHandle, NULL);
//    WM8960_ConfigDataFormat(&codecHandle, format->masterClockHz, format->sampleRate_Hz, format->bitWidth);
//#endif

    mclkSourceClockHz = AUDIO_SAI_CLK_FREQ;
    SAI_TransferTxCreateHandleEDMA(AUDIO_SAI, txHandle, txCallback, NULL, dmaTxHandle);
    SAI_TransferTxSetFormatEDMA(AUDIO_SAI, txHandle, format, mclkSourceClockHz, format->masterClockHz);

    SAI_TransferRxCreateHandleEDMA(AUDIO_SAI, rxHandle, rxCallback, NULL, dmaRxHandle);
    SAI_TransferRxSetFormatEDMA(AUDIO_SAI, rxHandle, format, mclkSourceClockHz, format->masterClockHz);

    /* Enable interrupt to handle FIFO error */
    SAI_TxEnableInterrupts(AUDIO_SAI, kSAI_FIFOErrorInterruptEnable);
    EnableIRQ(AUDIO_SAI_TX_IRQ);

    SAI_RxEnableInterrupts(AUDIO_SAI, kSAI_FIFOErrorInterruptEnable);
    EnableIRQ(AUDIO_SAI_RX_IRQ);
}




/*!
 * @func 音频关初始化
 */
static void AUDIO_SAI_Deinit(void) {
    DisableIRQ(AUDIO_SAI_RX_IRQ);
    DisableIRQ(AUDIO_SAI_TX_IRQ);

//#if defined(AUDIO_CODEC_WM8960)
//    WM8960_Deinit(&codecHandle);
//#endif

//    LPI2C_MasterDeinit(AUDIO_I2C);

    SAI_Deinit(AUDIO_SAI);

    DMAMUX_Deinit(AUDIO_DMAMUX);

    EDMA_Deinit(AUDIO_DMA);
		
    BOARD_EnableSaiMclkOutput(false);

    CLOCK_DeinitAudioPll();

    AUDIO_SAI_MemFree();
}

/*!
 * @func 设置数据接收流控制器
 */
static void AUDIO_SAI_setRxDataStreamHandler_S(DataStreamHandler_S *dataStreamHandler) {
    rxHandler.dataStream = dataStreamHandler;
}

/*!
 * @func 设置数据发送流控制器
 */
static void AUDIO_SAI_setTxDataStreamHandler_S(DataStreamHandler_S *dataStreamHandler) {
    txHandler.dataStream = dataStreamHandler;
}

/*!
 * @func DMA发送中断回调函数
 */
static void txCallback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData)
{
/* 继续DMA发送 */
    if(txHandler.enable)
    {
    /* 数据缓存队列头部为当前发送中断返回缓存编号的后两个编号，因为当前缓存返回编号的后一个编号正在被DMA读取并发送数据 */
    txHandler.head = (handle->queueUser + 2) % BUFFER_NUM;

    /* 如果缓存大小等于0，缓存尾标号跟随头部移动，txBufEnd = txBufHead  */
    txHandler.end = (txHandler.filledBufNum == 0) ? txHandler.head : txHandler.end;

    txHandler.filledBufNum = (txHandler.filledBufNum - 1) <= 0 ? 0 : txHandler.filledBufNum - 1;
//    txBufSize = (txBufSize >= BUFFER_SIZE) ? (txBufSize - BUFFER_SIZE) : 0;

    
        SAI_TransferSendEDMA(base, handle, &txHandler.xfer[handle->queueUser]);
    }

    /* 停止DMA发送 */
    else
    {
        debug("Terminate send\r\n");
        SAI_TransferTerminateSendEDMA(base, handle);
    }
}

/*!
 * @func DMA接收中断回调函数
 */
static void rxCallback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData)
{


    /* 继续DMA接收 */
    if(rxHandler.enable)
    {

        if(rxHandler.type == normal) {
            /* 数据缓存队列尾部为当前接收中断返回缓存编号 */
            rxHandler.end = handle->queueUser;

            /* 如果在上一个中断时 rxFillBufNum 已经大于等于最大缓存数，并在本次中断前没有读取缓存，缓存头应后移一位*/
            rxHandler.head = (rxHandler.filledBufNum >= BUFFER_NUM - 1) ? (rxHandler.head + 1) % BUFFER_NUM : rxHandler.head;

            /*  因为数据缓存队列其中一个 BUFFER 在当前正在被DMA写入数据,所以可读缓存数目 rxBufNum 最大为 BUFFER_NUM-1
            		不可读该缓存为当前中断返回的缓存编号的下一个号码，因此可缓存buffer的最大数量为 (BUFFER_TOTAL_SIZE - BUFFER_SIZE) */
            rxHandler.filledBufNum = (rxHandler.filledBufNum >= BUFFER_NUM - 1) ? (BUFFER_NUM - 1) : (rxHandler.filledBufNum + 1);
//            rxBufSize = (rxBufSize + BUFFER_SIZE) > (BUFFER_TOTAL_SIZE - BUFFER_SIZE)? (BUFFER_TOTAL_SIZE - BUFFER_SIZE) : (rxBufSize + BUFFER_SIZE);

//            debug("rxCallback(normal): rxBufHead = %d  rxBufEnd = %d  rxFillBufNum = %d \r\n",rxHandler.head,rxHandler.end,rxHandler.filledBufNum);
        }

        else if(rxHandler.type == stream)
        {
            /* 数据尾为下一个缓存的首地址 */
            rxHandler.dataStream->end = rxHandler.xfer[(handle->queueUser + 1) % BUFFER_NUM].data;

            rxHandler.dataStream->head = (rxHandler.dataStream->filledSize >= rxHandler.totalBufSize - rxHandler.bufSize) ? 
																					rxHandler.xfer[(handle->queueUser + 2) % BUFFER_NUM].data	:
																					rxHandler.dataStream->head;
																					

            rxHandler.dataStream->filledSize = (rxHandler.dataStream->filledSize >= rxHandler.totalBufSize - rxHandler.bufSize) ? 
																								rxHandler.totalBufSize - rxHandler.bufSize : rxHandler.dataStream->filledSize + rxHandler.bufSize;

            rxHandler.dataStream->emptySize = rxHandler.dataStream->totalSize - rxHandler.dataStream->filledSize;

//            debug("rxCallback(stream): filledSize = %d  \r\n",rxHandler.dataStream->filledSize);
        }

        /* rxfer重新放回DMA队列 */
        SAI_TransferReceiveEDMA(base, handle, &rxHandler.xfer[handle->queueUser]);
    }

    /* 停止DMA接收 */
    else
    {
        debug("stop audio sai dma receive\r\n");
        SAI_TransferTerminateReceiveEDMA(base, handle);

    }
}

/*!
 * @func 外部调用读取数据缓存
 */
static uint32_t AUDIO_SAI_DataOutput(uint8_t *buf,uint32_t maxSize) {
    uint8_t i,num = rxHandler.filledBufNum,head = rxHandler.head;
    uint32_t outputSize = 0;

    if(maxSize < BUFFER_SIZE || buf == NULL || rxHandler.type == stream)
        return outputSize;

    debug("##DataOutput:  \r\n");
    for(i=0; i<num; i++) {
        memcpy(buf + outputSize,rxHandler.xfer[(head+i)%BUFFER_NUM].data,BUFFER_SIZE);

        rxHandler.head = (rxHandler.head + 1) % BUFFER_NUM;
//        rxBufSize = (rxBufSize >= BUFFER_SIZE) ? (rxBufSize - BUFFER_SIZE) : 0;
        rxHandler.filledBufNum = (rxHandler.filledBufNum > 0) ? (rxHandler.filledBufNum - 1) : 0;

        outputSize += BUFFER_SIZE;
        if((outputSize + BUFFER_SIZE) > maxSize)
            return outputSize;
        debug("    rxBufHead = %d  rxBufEnd = %d  rxBufNum = %d\r\n",rxHandler.head,rxHandler.end,rxHandler.filledBufNum);
    }
    debug(" End##\r\n");

    return outputSize;
}

/*!
 * @func 外部调用写入数据缓存
 */
static void AUDIO_SAI_DataInput(uint8_t *buf) {
//    uint8_t bufEnd = txHandler.end;

    if(txHandler.filledBufNum >= BUFFER_NUM -1 || buf == NULL)
        return;

    memcpy(txHandler.xfer[txHandler.end].data,buf,BUFFER_SIZE);
    txHandler.end = (txHandler.end + 1) % BUFFER_NUM;
    txHandler.filledBufNum++;
//    txBufSize += BUFFER_SIZE;
}

/*!
 * @func 开始接收
 */
static void AUDIO_SAI_ReceiveStart(TransmitType_EN type)
{
    uint8_t i;

		/* 缓存空间不为空，证明接收已经开始，不能重复操作，可能造成内存泄漏 */
		if(rxHandler.audioCache != NULL)
			return;

    /* 判断输入流控制句柄是否被赋值（每次初始化音频接收功能，流控制句柄指针都会被置空，
    		因此需要在初始化后和开始接收前设置数据流句柄） */
    if(type == stream && rxHandler.dataStream != NULL)
    {

        /* 输入流控制句柄不为空,音频rxAudioBuff指针指向数据流数据内存 */
        rxHandler.audioCache = rxHandler.dataStream->data;
        rxHandler.type = stream;

        debug("audio receive by stream mode\r\n");

        /* 按照数据流总内存大小分割buf块 */
        rxHandler.totalBufSize = rxHandler.dataStream->totalSize;
        rxHandler.bufSize = rxHandler.totalBufSize / BUFFER_NUM;
				rxHandler.totalBufNum = BUFFER_NUM;

        rxHandler.dataStream->wProtect = true;
    }
    else if(type == normal){
        rxHandler.audioCache = MALLOC(BUFFER_TOTAL_SIZE);

        rxHandler.totalBufSize = BUFFER_TOTAL_SIZE;
        rxHandler.bufSize = BUFFER_SIZE;
				rxHandler.totalBufNum = BUFFER_NUM;
	
        rxHandler.head = rxHandler.end = rxHandler.filledBufNum = 0;
        debug("audio receive by normal mode\r\n");
    }
		else
			return;



    if(rxHandler.audioCache == NULL) {
        debug("receive start fail!! malloc fail!!\r\n");
        return;
    }

    /* 清内存 */
    memset(rxHandler.audioCache, 0, rxHandler.totalBufSize);

    for (i = 0; i < BUFFER_NUM; i++)
    {
        rxHandler.xfer[i].data = rxHandler.audioCache + i * rxHandler.bufSize;
        rxHandler.xfer[i].dataSize = rxHandler.bufSize;
    }

    rxHandler.enable = true;

    for (i = 0; i < BUFFER_NUM; i++)
    {
        SAI_TransferReceiveEDMA(AUDIO_SAI, rxHandle, &rxHandler.xfer[i]);
    }
}

/*!
 * @func 停止接收
 */
static void AUDIO_SAI_ReceiveStop(void)
{
    rxHandler.enable = false;

    DELAY(200);

    /* 释放内存或置空 */
		if(rxHandler.type == normal){
				FREE(rxHandler.audioCache);
		}
		
		else if(rxHandler.type == stream){
				rxHandler.audioCache = NULL;
		}
}

/*!
 * @func 开始发送
 */
static void AUDIO_SAI_SendStart(void)
{
//    uint8_t i;

    txHandler.audioCache = MALLOC(BUFFER_TOTAL_SIZE);

    if(txHandler.audioCache == NULL) {
        debug("send start fail!! malloc fail!!\r\n");
        return;
    }

    memset(txHandler.audioCache, 0, BUFFER_TOTAL_SIZE);
//    for (i = 0; i < BUFFER_NUM; i++)
//    {
//        txfer[i].data = txAudioBuff + i * BUFFER_SIZE;
//        txfer[i].dataSize = BUFFER_SIZE;
//    }

//    txBufHead = txBufEnd = txBufNum = txBufSize = 0;

//    sending = true;

//    for (i = 0; i < BUFFER_NUM; i++)
//    {
//        SAI_TransferSendEDMA(AUDIO_SAI, txHandle, &txfer[i]);
//    }
}



/*!
 * @func 停止发送
 */
static void AUDIO_SAI_SendStop(void)
{
    txHandler.enable = false;

    DELAY(500);

    /* 释放内存 */
    FREE(txHandler.audioCache);
}

static void BOARD_EnableSaiMclkOutput(bool enable)
{
    if (enable)
    {
        IOMUXC_GPR->GPR1 |= IOMUXC_GPR_GPR1_SAI2_MCLK_DIR_MASK;
    }
    else
    {
        IOMUXC_GPR->GPR1 &= (~IOMUXC_GPR_GPR1_SAI2_MCLK_DIR_MASK);
    }
}

static void BOARD_USDHCClockConfiguration(void)
{
    /*configure system pll PFD2 fractional divider to 18*/
    CLOCK_InitSysPfd(kCLOCK_Pfd0, 0x12U);
    /* Configure USDHC clock source and divider */
    CLOCK_SetDiv(kCLOCK_Usdhc1Div, 0U);
    CLOCK_SetMux(kCLOCK_Usdhc1Mux, 1U);
}


/*!
 * @brief 这几个中断函数是原来SDK带的，并没有什么卵用，中断不进这里；
 */
void SAI_UserTxIRQHandler(void)
{
    /* Clear the FEF flag */
    SAI_TxClearStatusFlags(AUDIO_SAI, kSAI_FIFOErrorFlag);
    SAI_TxSoftwareReset(AUDIO_SAI, kSAI_ResetTypeFIFO);
}

void SAI_UserRxIRQHandler(void)
{
    SAI_RxClearStatusFlags(AUDIO_SAI, kSAI_FIFOErrorFlag);
    SAI_RxSoftwareReset(AUDIO_SAI, kSAI_ResetTypeFIFO);
}

void SAI_UserIRQHandler(void)
{
    if (AUDIO_SAI->TCSR & kSAI_FIFOErrorFlag)
    {
        SAI_UserTxIRQHandler();
    }

    if (AUDIO_SAI->RCSR & kSAI_FIFOErrorFlag)
    {
        SAI_UserRxIRQHandler();
    }
}
