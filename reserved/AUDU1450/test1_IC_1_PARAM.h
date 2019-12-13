/*
 * File:           F:\work\项目文件\第三代会议主机\DSP\test1_IC_1_PARAM.h
 *
 * Created:        Saturday, September 28, 2019 11:58:05 AM
 * Description:    0300M:IC 1 parameter RAM definitions.
 *
 * This software is distributed in the hope that it will be useful,
 * but is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * This software may only be used to program products purchased from
 * Analog Devices for incorporation by you into audio products that
 * are intended for resale to audio product end users. This software
 * may not be distributed whole or in any part to third parties.
 *
 * Copyright ©2019 Analog Devices, Inc. All rights reserved.
 */
#ifndef __TEST1_IC_1_PARAM_H__
#define __TEST1_IC_1_PARAM_H__


/* Module LINE_IN - Mute*/
#define MOD_LINE_IN_COUNT                              2
#define MOD_LINE_IN_DEVICE                             "IC1"
#define MOD_LINE_IN_ALG0_SLEW_MODE_ADDR                28
#define MOD_LINE_IN_ALG0_SLEW_MODE_FIXPT               0x0000208A
#define MOD_LINE_IN_ALG0_SLEW_MODE_VALUE               SIGMASTUDIOTYPE_INTEGER_CONVERT(8330)
#define MOD_LINE_IN_ALG0_SLEW_MODE_TYPE                SIGMASTUDIOTYPE_INTEGER
#define MOD_LINE_IN_ALG0_MUTE_ADDR                     29
#define MOD_LINE_IN_ALG0_MUTE_VALUE                    SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_LINE_IN_ALG0_MUTE_TYPE                     SIGMASTUDIOTYPE_8_24

/* Module USB_播放L - Mute*/
#define MOD_USB_L_COUNT                                2
#define MOD_USB_L_DEVICE                               "IC1"
#define MOD_USB_L_ALG0_SLEW_MODE_ADDR                  31
#define MOD_USB_L_ALG0_SLEW_MODE_FIXPT                 0x0000208A
#define MOD_USB_L_ALG0_SLEW_MODE_VALUE                 SIGMASTUDIOTYPE_INTEGER_CONVERT(8330)
#define MOD_USB_L_ALG0_SLEW_MODE_TYPE                  SIGMASTUDIOTYPE_INTEGER
#define MOD_USB_L_ALG0_MUTE_ADDR                       32
#define MOD_USB_L_ALG0_MUTE_VALUE                      SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_USB_L_ALG0_MUTE_TYPE                       SIGMASTUDIOTYPE_8_24

/* Module USB_播放R - Mute*/
#define MOD_USB_R_COUNT                                2
#define MOD_USB_R_DEVICE                               "IC1"
#define MOD_USB_R_ALG0_SLEW_MODE_ADDR                  34
#define MOD_USB_R_ALG0_SLEW_MODE_FIXPT                 0x0000208A
#define MOD_USB_R_ALG0_SLEW_MODE_VALUE                 SIGMASTUDIOTYPE_INTEGER_CONVERT(8330)
#define MOD_USB_R_ALG0_SLEW_MODE_TYPE                  SIGMASTUDIOTYPE_INTEGER
#define MOD_USB_R_ALG0_MUTE_ADDR                       35
#define MOD_USB_R_ALG0_MUTE_VALUE                      SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_USB_R_ALG0_MUTE_TYPE                       SIGMASTUDIOTYPE_8_24

/* Module SIP通话_L - Mute*/
#define MOD_SIP_L_COUNT                                2
#define MOD_SIP_L_DEVICE                               "IC1"
#define MOD_SIP_L_ALG0_SLEW_MODE_ADDR                  37
#define MOD_SIP_L_ALG0_SLEW_MODE_FIXPT                 0x0000208A
#define MOD_SIP_L_ALG0_SLEW_MODE_VALUE                 SIGMASTUDIOTYPE_INTEGER_CONVERT(8330)
#define MOD_SIP_L_ALG0_SLEW_MODE_TYPE                  SIGMASTUDIOTYPE_INTEGER
#define MOD_SIP_L_ALG0_MUTE_ADDR                       38
#define MOD_SIP_L_ALG0_MUTE_VALUE                      SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_SIP_L_ALG0_MUTE_TYPE                       SIGMASTUDIOTYPE_8_24

/* Module SIP通话_R - Mute*/
#define MOD_SIP_R_COUNT                                2
#define MOD_SIP_R_DEVICE                               "IC1"
#define MOD_SIP_R_ALG0_SLEW_MODE_ADDR                  40
#define MOD_SIP_R_ALG0_SLEW_MODE_FIXPT                 0x0000208A
#define MOD_SIP_R_ALG0_SLEW_MODE_VALUE                 SIGMASTUDIOTYPE_INTEGER_CONVERT(8330)
#define MOD_SIP_R_ALG0_SLEW_MODE_TYPE                  SIGMASTUDIOTYPE_INTEGER
#define MOD_SIP_R_ALG0_MUTE_ADDR                       41
#define MOD_SIP_R_ALG0_MUTE_VALUE                      SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_SIP_R_ALG0_MUTE_TYPE                       SIGMASTUDIOTYPE_8_24

/* Module DANTE - Mute*/
#define MOD_DANTE_COUNT                                2
#define MOD_DANTE_DEVICE                               "IC1"
#define MOD_DANTE_ALG0_SLEW_MODE_ADDR                  43
#define MOD_DANTE_ALG0_SLEW_MODE_FIXPT                 0x0000208A
#define MOD_DANTE_ALG0_SLEW_MODE_VALUE                 SIGMASTUDIOTYPE_INTEGER_CONVERT(8330)
#define MOD_DANTE_ALG0_SLEW_MODE_TYPE                  SIGMASTUDIOTYPE_INTEGER
#define MOD_DANTE_ALG0_MUTE_ADDR                       44
#define MOD_DANTE_ALG0_MUTE_VALUE                      SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_DANTE_ALG0_MUTE_TYPE                       SIGMASTUDIOTYPE_8_24

/* Module 全数字音频 - Mute*/
#define MOD__COUNT                                     2
#define MOD__DEVICE                                    "IC1"
#define MOD__ALG0_SLEW_MODE_ADDR                       46
#define MOD__ALG0_SLEW_MODE_FIXPT                      0x0000208A
#define MOD__ALG0_SLEW_MODE_VALUE                      SIGMASTUDIOTYPE_INTEGER_CONVERT(8330)
#define MOD__ALG0_SLEW_MODE_TYPE                       SIGMASTUDIOTYPE_INTEGER
#define MOD__ALG0_MUTE_ADDR                            47
#define MOD__ALG0_MUTE_VALUE                           SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD__ALG0_MUTE_TYPE                            SIGMASTUDIOTYPE_8_24

/* Module WIFI音频 - Mute*/
#define MOD_WIFI_COUNT                                 2
#define MOD_WIFI_DEVICE                                "IC1"
#define MOD_WIFI_ALG0_SLEW_MODE_ADDR                   49
#define MOD_WIFI_ALG0_SLEW_MODE_FIXPT                  0x0000208A
#define MOD_WIFI_ALG0_SLEW_MODE_VALUE                  SIGMASTUDIOTYPE_INTEGER_CONVERT(8330)
#define MOD_WIFI_ALG0_SLEW_MODE_TYPE                   SIGMASTUDIOTYPE_INTEGER
#define MOD_WIFI_ALG0_MUTE_ADDR                        50
#define MOD_WIFI_ALG0_MUTE_VALUE                       SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_WIFI_ALG0_MUTE_TYPE                        SIGMASTUDIOTYPE_8_24

/* Module M Mixer1 - Multiple Control Mixer*/
#define MOD_MMIXER1_COUNT                              16
#define MOD_MMIXER1_DEVICE                             "IC1"
#define MOD_MMIXER1_ALG0_SLEW_MODE_ADDR                51
#define MOD_MMIXER1_ALG0_SLEW_MODE_FIXPT               0x0000186A
#define MOD_MMIXER1_ALG0_SLEW_MODE_VALUE               SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_ALG0_SLEW_MODE_TYPE                SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_ALG0_SLEW_MODE_ADDR                51
#define MOD_MMIXER1_ALG0_SLEW_MODE_FIXPT               0x0000186A
#define MOD_MMIXER1_ALG0_SLEW_MODE_VALUE               SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_ALG0_SLEW_MODE_TYPE                SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_ALG0_SLEW_MODE_ADDR                51
#define MOD_MMIXER1_ALG0_SLEW_MODE_FIXPT               0x0000186A
#define MOD_MMIXER1_ALG0_SLEW_MODE_VALUE               SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_ALG0_SLEW_MODE_TYPE                SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_ALG0_SLEW_MODE_ADDR                51
#define MOD_MMIXER1_ALG0_SLEW_MODE_FIXPT               0x0000186A
#define MOD_MMIXER1_ALG0_SLEW_MODE_VALUE               SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_ALG0_SLEW_MODE_TYPE                SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_ALG0_SLEW_MODE_ADDR                51
#define MOD_MMIXER1_ALG0_SLEW_MODE_FIXPT               0x0000186A
#define MOD_MMIXER1_ALG0_SLEW_MODE_VALUE               SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_ALG0_SLEW_MODE_TYPE                SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_ALG0_SLEW_MODE_ADDR                51
#define MOD_MMIXER1_ALG0_SLEW_MODE_FIXPT               0x0000186A
#define MOD_MMIXER1_ALG0_SLEW_MODE_VALUE               SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_ALG0_SLEW_MODE_TYPE                SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_ALG0_SLEW_MODE_ADDR                51
#define MOD_MMIXER1_ALG0_SLEW_MODE_FIXPT               0x0000186A
#define MOD_MMIXER1_ALG0_SLEW_MODE_VALUE               SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_ALG0_SLEW_MODE_TYPE                SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_ALG0_SLEW_MODE_ADDR                51
#define MOD_MMIXER1_ALG0_SLEW_MODE_FIXPT               0x0000186A
#define MOD_MMIXER1_ALG0_SLEW_MODE_VALUE               SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_ALG0_SLEW_MODE_TYPE                SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_ALG0_STAGE0_TARGET_ADDR            60
#define MOD_MMIXER1_ALG0_STAGE0_TARGET_VALUE           SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_ALG0_STAGE0_TARGET_TYPE            SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_ALG0_STAGE1_TARGET_ADDR            61
#define MOD_MMIXER1_ALG0_STAGE1_TARGET_VALUE           SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_ALG0_STAGE1_TARGET_TYPE            SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_ALG0_STAGE2_TARGET_ADDR            62
#define MOD_MMIXER1_ALG0_STAGE2_TARGET_VALUE           SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_ALG0_STAGE2_TARGET_TYPE            SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_ALG0_STAGE3_TARGET_ADDR            63
#define MOD_MMIXER1_ALG0_STAGE3_TARGET_VALUE           SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_ALG0_STAGE3_TARGET_TYPE            SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_ALG0_STAGE4_TARGET_ADDR            64
#define MOD_MMIXER1_ALG0_STAGE4_TARGET_VALUE           SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_ALG0_STAGE4_TARGET_TYPE            SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_ALG0_STAGE5_TARGET_ADDR            65
#define MOD_MMIXER1_ALG0_STAGE5_TARGET_VALUE           SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_ALG0_STAGE5_TARGET_TYPE            SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_ALG0_STAGE6_TARGET_ADDR            66
#define MOD_MMIXER1_ALG0_STAGE6_TARGET_VALUE           SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_ALG0_STAGE6_TARGET_TYPE            SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_ALG0_STAGE7_TARGET_ADDR            67
#define MOD_MMIXER1_ALG0_STAGE7_TARGET_VALUE           SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_ALG0_STAGE7_TARGET_TYPE            SIGMASTUDIOTYPE_8_24

/* Module M Mixer1_2 - Multiple Control Mixer*/
#define MOD_MMIXER1_2_COUNT                            14
#define MOD_MMIXER1_2_DEVICE                           "IC1"
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_ADDR              68
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_ADDR              68
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_ADDR              68
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_ADDR              68
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_ADDR              68
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_ADDR              68
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_ADDR              68
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_2_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_2_ALG0_STAGE0_TARGET_ADDR          76
#define MOD_MMIXER1_2_ALG0_STAGE0_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_2_ALG0_STAGE0_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_2_ALG0_STAGE1_TARGET_ADDR          77
#define MOD_MMIXER1_2_ALG0_STAGE1_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_2_ALG0_STAGE1_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_2_ALG0_STAGE2_TARGET_ADDR          78
#define MOD_MMIXER1_2_ALG0_STAGE2_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_2_ALG0_STAGE2_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_2_ALG0_STAGE3_TARGET_ADDR          79
#define MOD_MMIXER1_2_ALG0_STAGE3_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_2_ALG0_STAGE3_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_2_ALG0_STAGE4_TARGET_ADDR          80
#define MOD_MMIXER1_2_ALG0_STAGE4_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_2_ALG0_STAGE4_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_2_ALG0_STAGE5_TARGET_ADDR          81
#define MOD_MMIXER1_2_ALG0_STAGE5_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_2_ALG0_STAGE5_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_2_ALG0_STAGE6_TARGET_ADDR          82
#define MOD_MMIXER1_2_ALG0_STAGE6_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_2_ALG0_STAGE6_TARGET_TYPE          SIGMASTUDIOTYPE_8_24

/* Module M Mixer1_4 - Multiple Control Mixer*/
#define MOD_MMIXER1_4_COUNT                            4
#define MOD_MMIXER1_4_DEVICE                           "IC1"
#define MOD_MMIXER1_4_ALG0_SLEW_MODE_ADDR              83
#define MOD_MMIXER1_4_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_4_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_4_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_4_ALG0_SLEW_MODE_ADDR              83
#define MOD_MMIXER1_4_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_4_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_4_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_4_ALG0_STAGE0_TARGET_ADDR          86
#define MOD_MMIXER1_4_ALG0_STAGE0_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_4_ALG0_STAGE0_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_4_ALG0_STAGE1_TARGET_ADDR          87
#define MOD_MMIXER1_4_ALG0_STAGE1_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_4_ALG0_STAGE1_TARGET_TYPE          SIGMASTUDIOTYPE_8_24

/* Module M Mixer1_5 - Multiple Control Mixer*/
#define MOD_MMIXER1_5_COUNT                            16
#define MOD_MMIXER1_5_DEVICE                           "IC1"
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_ADDR              88
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_ADDR              88
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_ADDR              88
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_ADDR              88
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_ADDR              88
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_ADDR              88
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_ADDR              88
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_ADDR              88
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_5_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_5_ALG0_STAGE0_TARGET_ADDR          97
#define MOD_MMIXER1_5_ALG0_STAGE0_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_5_ALG0_STAGE0_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_5_ALG0_STAGE1_TARGET_ADDR          98
#define MOD_MMIXER1_5_ALG0_STAGE1_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_5_ALG0_STAGE1_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_5_ALG0_STAGE2_TARGET_ADDR          99
#define MOD_MMIXER1_5_ALG0_STAGE2_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_5_ALG0_STAGE2_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_5_ALG0_STAGE3_TARGET_ADDR          100
#define MOD_MMIXER1_5_ALG0_STAGE3_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_5_ALG0_STAGE3_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_5_ALG0_STAGE4_TARGET_ADDR          101
#define MOD_MMIXER1_5_ALG0_STAGE4_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_5_ALG0_STAGE4_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_5_ALG0_STAGE5_TARGET_ADDR          102
#define MOD_MMIXER1_5_ALG0_STAGE5_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_5_ALG0_STAGE5_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_5_ALG0_STAGE6_TARGET_ADDR          103
#define MOD_MMIXER1_5_ALG0_STAGE6_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_5_ALG0_STAGE6_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_5_ALG0_STAGE7_TARGET_ADDR          104
#define MOD_MMIXER1_5_ALG0_STAGE7_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_5_ALG0_STAGE7_TARGET_TYPE          SIGMASTUDIOTYPE_8_24

/* Module M Mixer1_3 - Multiple Control Mixer*/
#define MOD_MMIXER1_3_COUNT                            12
#define MOD_MMIXER1_3_DEVICE                           "IC1"
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_ADDR              105
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_ADDR              105
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_ADDR              105
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_ADDR              105
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_ADDR              105
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_ADDR              105
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_FIXPT             0x0000186A
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(6250)
#define MOD_MMIXER1_3_ALG0_SLEW_MODE_TYPE              SIGMASTUDIOTYPE_INTEGER
#define MOD_MMIXER1_3_ALG0_STAGE0_TARGET_ADDR          112
#define MOD_MMIXER1_3_ALG0_STAGE0_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_3_ALG0_STAGE0_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_3_ALG0_STAGE1_TARGET_ADDR          113
#define MOD_MMIXER1_3_ALG0_STAGE1_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_3_ALG0_STAGE1_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_3_ALG0_STAGE2_TARGET_ADDR          114
#define MOD_MMIXER1_3_ALG0_STAGE2_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_3_ALG0_STAGE2_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_3_ALG0_STAGE3_TARGET_ADDR          115
#define MOD_MMIXER1_3_ALG0_STAGE3_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_3_ALG0_STAGE3_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_3_ALG0_STAGE4_TARGET_ADDR          116
#define MOD_MMIXER1_3_ALG0_STAGE4_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_3_ALG0_STAGE4_TARGET_TYPE          SIGMASTUDIOTYPE_8_24
#define MOD_MMIXER1_3_ALG0_STAGE5_TARGET_ADDR          117
#define MOD_MMIXER1_3_ALG0_STAGE5_TARGET_VALUE         SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_MMIXER1_3_ALG0_STAGE5_TARGET_TYPE          SIGMASTUDIOTYPE_8_24

#endif