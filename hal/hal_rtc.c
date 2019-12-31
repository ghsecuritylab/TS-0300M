/*
 *	 @FileName					 hal_rtc.c
 *	 @Author					 KT
 *	 @CreationTime				 2019/09/30
 *	 @Description
 *
 *	 @Include					 hal_rtc.h
 *
 *	 @API						 Rtc
 *
 **/

#include "hal_rtc.h"
#include "fsl_iomuxc.h"
#include "rtc/pcf8563.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if	RTC_PCF8563_ENABLE

#ifndef RTC_PCF8563_I2C_TYPE
#define RTC_PCF8563_I2C_TYPE					LPI2C1
#endif

#ifndef RTC_PCF8563_I2C_ADDR
#define RTC_PCF8563_I2C_ADDR					(0xA2)
#endif

#endif

typedef struct {

    /* @brief DSP control & config LPI2C_Type */
    LPI2C_Type *base;

    /* @brief I2C address */
    uint8_t addr;

    status_t (*getDateTime)(LPI2C_Type *base,uint16_t slaveAddr,
                            uint8_t *year,uint8_t *mon,uint8_t *day,
                            uint8_t *hour,uint8_t *min,uint8_t *sec,uint8_t *weedday);

    status_t (*setDateTime)(LPI2C_Type *base,uint16_t slaveAddr,
                            uint8_t year,uint8_t mon,uint8_t day,
                            uint8_t hour,uint8_t min,uint8_t sec,uint8_t weedday);

    uint8_t (*getSta_1)(LPI2C_Type *base,uint16_t slaveAddr);
    uint8_t (*getSta_2)(LPI2C_Type *base,uint16_t slaveAddr);
    void (*setSta_1)(LPI2C_Type *base,uint16_t slaveAddr,uint8_t ctrl);
    void (*setSta_2)(LPI2C_Type *base,uint16_t slaveAddr,uint8_t ctrl);

} HAL_Rtc_S;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/
#if	RTC_PCF8563_ENABLE
HAL_Rtc_S  Pcf8563_driver = {
    .base = RTC_PCF8563_I2C_TYPE,
    .addr = RTC_PCF8563_I2C_ADDR,
    .getDateTime = Pcf8563_GetDateTime,
    .setDateTime = Pcf8563_SetDateTime,
    .getSta_1 =  Pcf8563_GetState_1,
    .getSta_2 =  Pcf8563_GetState_2,
    .setSta_1 =  Pcf8563_SetState_1,
    .setSta_2 =  Pcf8563_SetState_2,
};
#endif


static HAL_Rtc_S *Rtc_drivers[RTC_DRIVERS_TOTAL_NUM] = {
#if	RTC_PCF8563_ENABLE
    &Pcf8563_driver,
#endif
};

/*******************************************************************************
 * Code
 ******************************************************************************/
status_t HAL_RtcSetDateTime(HAL_RtcType_EN type,HAL_RtcPara_S *para)
{
    HAL_Rtc_S *rtc;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < RTC_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    ERR_CHECK(para != null, return kStatus_Fail);

    rtc = Rtc_drivers[type];

    return rtc->setDateTime(rtc->base,rtc->addr,para->year,para->month,para->day,para->hour,para->min,para->sec,(uint8_t)para->weekday);

}

status_t HAL_RtcGetDateTime(HAL_RtcType_EN type,HAL_RtcPara_S *para)
{

    HAL_Rtc_S *rtc;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < RTC_DRIVERS_TOTAL_NUM), return kStatus_Fail);
    ERR_CHECK(para != null, return kStatus_Fail);

    rtc = Rtc_drivers[type];

    return rtc->getDateTime(rtc->base,rtc->addr,&para->year,&para->month,&para->day,&para->hour,&para->min,&para->sec,(uint8_t *)(&para->weekday));
}

bool HAL_RtcGetRstFlag(HAL_RtcType_EN type)
{
    HAL_Rtc_S *rtc;
    uint8_t sta;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < RTC_DRIVERS_TOTAL_NUM), return kStatus_Fail);

    rtc = Rtc_drivers[type];
    sta = rtc->getSta_1(rtc->base,rtc->addr);

    return (sta & 0x08);
}

void HAL_RtcSetRstFlag(HAL_RtcType_EN type)
{
    HAL_Rtc_S *rtc;
    uint8_t sta;

    ERR_CHECK(((uint8_t)type >=0 && (uint8_t)type < RTC_DRIVERS_TOTAL_NUM), return );

    rtc = Rtc_drivers[type];
    sta = rtc->getSta_1(rtc->base,rtc->addr);
    rtc->setSta_1(rtc->base,rtc->addr,(sta & (~0x08)));
}


