#ifndef _GLOBAL_CONFIG_H_
#define _GLOBAL_CONFIG_H_

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*******************************************************************************
 * 									全局定义
 ******************************************************************************/
#define ENABLE												(true)
#define DISABLE												(false)

/*******************************************************************************
 * 							   网络及相关默认配置
 ******************************************************************************/
#define EX_CTRL_LOCAL_IP_DEF								{172,16,14,65}
#define EX_CTRL_GATEWAY_DEF									{172,16,14,254}
#define EX_CTRL_NETMASK_DEF									{255,255,255,0}
#define EX_CTRL_PORT_DEF									(50000)

/*******************************************************************************
 * 							   主机及会议相关默认配置
 ******************************************************************************/
/* 最大有线单元数 */
#define WIRED_UNIT_MAX_ONLINE_NUM							(4096)
	
/* 最大WIFI单元数 */
#define WIFI_UNIT_MAX_ONLINE_NUM							(300)
	
/* 默认最大允许开话筒数（有线） */
#define WIRED_UNIT_MAX_ALLWO_OPEN_DEF						(8)
	
/* 默认最大允许开话筒数（WIFI） */
#define WIFI_UNIT_MAX_ALLWO_OPEN_DEF						(6)

/* 默认语言 */
#define CONFERENCE_LANGUAGE_DEF								(Chinese)


/*******************************************************************************
 * 								外部接口/硬件配置
 ******************************************************************************/

/******************************** I2C 1 ~ 3 ************************************/

#define LPI2C1_ENABLE									ENABLE

#define LPI2C2_ENABLE									ENABLE

#define LPI2C3_ENABLE									ENABLE


#if (defined(LPI2C1_ENABLE) && LPI2C1_ENABLE) || (defined(LPI2C2_ENABLE) && LPI2C2_ENABLE) || (defined(LPI2C3_ENABLE) && LPI2C3_ENABLE)

#define I2C_CLOCK_SOURCE_DIVIDER 						(5U)
#define I2C_CLOCK_FREQ 									((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (I2C_CLOCK_SOURCE_DIVIDER + 1U))

#if defined(LPI2C1_ENABLE) && LPI2C1_ENABLE
#define LPI2C1_BAUDRATE 								(100000U)
#endif

#if defined(LPI2C2_ENABLE) && LPI2C2_ENABLE
#define LPI2C2_BAUDRATE 								(100000U)
#endif

#if defined(LPI2C3_ENABLE) && LPI2C3_ENABLE
#define LPI2C3_BAUDRATE 								(400000U)
#endif

#endif

/******************************** SPI 1 ~ 3 ************************************/

#define LPSPI1_ENABLE									ENABLE

#define LPSPI2_ENABLE									DISABLE

#define LPSPI3_ENABLE									ENABLE

#if (defined(LPSPI1_ENABLE) && LPSPI1_ENABLE) || (defined(LPSPI2_ENABLE) && LPSPI2_ENABLE) || (defined(LPSPI3_ENABLE) && LPSPI3_ENABLE)

/* Select USB1 PLL PFD0 (720 MHz) as lpspi clock source */
#define LPSPI_CLOCK_SOURCE_SELECT 						(1U)
/* Clock divider for master lpspi clock source */
#define LPSPI_CLOCK_SOURCE_DIVIDER 						(7U)
	
#define LPSPI_MASTER_CLK_FREQ 							(CLOCK_GetFreq(kCLOCK_Usb1PllPfd0Clk) / (LPSPI_CLOCK_SOURCE_DIVIDER + 1U))

#define LPSPI_USE_IRQ 									DISABLE

#if defined(LPSPI1_ENABLE) && LPSPI1_ENABLE
#define LPSPI1_BAUDRATE 								(40*1000*1000U)				//40MHz
#define LPSPI1_DELAY_NANO_SEC							(0)
#define LPSPI1_MASTER_PCS								(kLPSPI_Pcs0)
#endif

#if defined(LPSPI2_ENABLE) && LPSPI2_ENABLE
#define LPSPI2_BAUDRATE 								(500000U)
#define LPSPI2_DELAY_NANO_SEC							(0)
#define LPSPI2_MASTER_PCS								(kLPSPI_Pcs0)
#endif

#if defined(LPSPI3_ENABLE) && LPSPI3_ENABLE
#define LPSPI3_BAUDRATE 								(40*1000*1000U)				//40MHz
#define LPSPI3_DELAY_NANO_SEC							(0)
#define LPSPI3_MASTER_PCS								(kLPSPI_Pcs0)
#endif

#endif

/******************************** ENET / ENET2 ************************************/
/* ENET 接口使能  */
#define ENET_ENABLE										ENABLE

/* SMI 接口使能  */
#define SMI_ENABLE										ENABLE

/* ENET2 接口使能  */
#define ENET2_ENABLE									ENABLE

/* SMI2 接口使能  */
#define SMI2_ENABLE										ENABLE


/* SMI时钟. */
#define SMI_CLOCK_NAME 									kCLOCK_CoreSysClk

/******************************** UART 1 ~ 8 ************************************/
/* UART1 接口使能  */
#define UART1_ENABLE									ENABLE

/* UART2 接口使能  */
#define UART2_ENABLE									DISABLE

/* UART3 接口使能  */
#define UART3_ENABLE									ENABLE

/* UART4 接口使能  */
#define UART4_ENABLE									DISABLE

/* UART5 接口使能  */
#define UART5_ENABLE									DISABLE

/* UART6 接口使能  */
#define UART6_ENABLE									ENABLE

/* UART7 接口使能  */
#define UART7_ENABLE									DISABLE

/* UART8 接口使能  */
#define UART8_ENABLE									ENABLE


/* 串口默认中断优先级 */
#define UART_DEF_ISR_PRIORITY							(3U)


/* UARTx_USE_IN_DRIVER宏定义用与区分接口用与HAL库调用还是驱动直接调用
   驱动调用在hal_init中初始化 */
#define UART6_USE_IN_DRIVER								ENABLE

#define UART6_BAUDRATE									(9600U)


/******************************** SAI 1 ~ 3 ************************************/

/* SAI1 接口使能  */
#define SAI1_ENABLE										DISABLE

/* SAI2 接口使能   */
#define SAI2_ENABLE										DISABLE

/* SAI3 接口使能   */
#define SAI3_ENABLE										DISABLE

#if SAI1_ENABLE || SAI2_ENABLE || SAI3_ENABLE
/* SAI接口DMA */
#ifndef	SAI_DMA
#define SAI_DMA 										DMA0
#endif

#ifndef SAI_DMAMUX
#define SAI_DMAMUX 										DMAMUX
#endif

#endif


/*
 * AUDIO PLL config: Frequency = Fref * (DIV_SELECT + NUM / DENOM)
 *								= 24 * (32 + 77/100)
 *								= 786.48 MHz
 */
#define AUDIO_PLL_LOOP_DIVIDER							(32)
#define AUDIO_PLL_POST_DIVIDER							(1)
#define AUDIO_PLL_NUMERATOR								(77)
#define AUDIO_PLL_DENOMINATOR							(100)




#endif
