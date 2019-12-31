/*
*  File Name:      adau1466_reg.h
*  Created on:     2019年11月21日
*  Author:         陈泽芳 
*  description :   ADAU1466寄存器表
*/
#ifndef __ADAU1466_REG_H__
#define __ADAU1466_REG_H__

//===========================DSP2========================//
//Router1 start
//Router1 的寄存器写入和读出共4bytes
/* line_in_1  */
#define REG_DSP2_LINE_IN_1_ADDR                  		 0x0014

/* line_in_2  */
#define REG_DSP2_LINE_IN_2_ADDR                 		 (REG_DSP2_LINE_IN_1_ADDR + 1) 

/* line_in_3  */
#define REG_DSP2_LINE_IN_3_ADDR                  		 (REG_DSP2_LINE_IN_1_ADDR + 2) 

/* line_in_4  */
#define REG_DSP2_LINE_IN_4_ADDR                          (REG_DSP2_LINE_IN_1_ADDR + 3)

/* usb_in_l  */
#define REG_DSP2_USB_IN_L_ADDR                           (REG_DSP2_LINE_IN_1_ADDR + 4) 

/* usb_in_r  */
#define REG_DSP2_USB_IN_R_ADDR                           (REG_DSP2_LINE_IN_1_ADDR + 5) 

/* dante_in_l  */
#define REG_DSP2_DANTE_IN_L_ADDR                         (REG_DSP2_LINE_IN_1_ADDR + 6) 

/* dante_in_r  */
#define REG_DSP2_DANTE_IN_R_ADDR                         (REG_DSP2_LINE_IN_1_ADDR + 7) 

/* wire_wifi_mic_mixer_in  */
#define REG_DSP2_WIRE_WIFI_MIC_MIXER_IN_ADDR             (REG_DSP2_LINE_IN_1_ADDR + 8) 

/* line_out_1  for all in */
#define REG_DSP2_LINE_OUT_1_ADDR                         (REG_DSP2_LINE_IN_1_ADDR + 9) 

/* line_out_2  for all in */
#define REG_DSP2_LINE_OUT_2_ADDR                         (REG_DSP2_LINE_IN_1_ADDR + 10) 

/* usb_out_l  for all in */
#define REG_DSP2_USB_OUT_L_ADDR                          (REG_DSP2_LINE_IN_1_ADDR + 11) 

/* usb_out_r  for all in */
#define REG_DSP2_USB_OUT_R_ADDR                          (REG_DSP2_LINE_IN_1_ADDR + 12) 

/* dante_out_l  for all in */
#define REG_DSP2_DANTE_OUT_L_ADDR                        (REG_DSP2_LINE_IN_1_ADDR + 13) 

/* dante_out_r  for all in */
#define REG_DSP2_DANTE_OUT_R_ADDR                        (REG_DSP2_LINE_IN_1_ADDR + 14) 

/* line_out_1_1 for line_in_1 */
#define REG_DSP2_LINE_OUT_1_LINE1_ADDR                   (REG_DSP2_LINE_IN_1_ADDR + 15) 

/* line_out_1_2 for line_in_2 */
#define REG_DSP2_LINE_OUT_1_LINE2_ADDR                   (REG_DSP2_LINE_IN_1_ADDR + 16) 

/* line_out_1_3 for line_in_3 */
#define REG_DSP2_LINE_OUT_1_LINE3_ADDR                   (REG_DSP2_LINE_IN_1_ADDR + 17) 

/* line_out_1_4 for line_in_4 */
#define REG_DSP2_LINE_OUT_1_LINE4_ADDR                   (REG_DSP2_LINE_IN_1_ADDR + 18) 

/* line_out_1_5 for usb_in_l */
#define REG_DSP2_LINE_OUT_1_USBL_ADDR                    (REG_DSP2_LINE_IN_1_ADDR + 19) 

/* line_out_1_6 for usb_in_r */
#define REG_DSP2_LINE_OUT_1_USBR_ADDR                    (REG_DSP2_LINE_IN_1_ADDR + 20) 

/* line_out_1_7 for dante_in_l */
#define REG_DSP2_LINE_OUT_1_DANTEL_ADDR                  (REG_DSP2_LINE_IN_1_ADDR + 21) 

/* line_out_1_8 for dante_in_r */
#define REG_DSP2_LINE_OUT_1_DANTER_ADDR                  (REG_DSP2_LINE_IN_1_ADDR + 22) 

/* line_out_1_9 for wire_wifi_mic_mixer_in */
#define REG_DSP2_LINE_OUT_1_ALL_MIC_MIX_ADDR             (REG_DSP2_LINE_IN_1_ADDR + 23) 

/* line_out_2_1 for line_in_1 */
#define REG_DSP2_LINE_OUT_2_LINE1_ADDR                   (REG_DSP2_LINE_IN_1_ADDR + 24) 

/* line_out_2_2 for line_in_2 */
#define REG_DSP2_LINE_OUT_2_LINE2_ADDR                   (REG_DSP2_LINE_IN_1_ADDR + 25) 

/* line_out_2_3 for line_in_3 */
#define REG_DSP2_LINE_OUT_2_LINE3_ADDR                   (REG_DSP2_LINE_IN_1_ADDR + 26) 

/* line_out_2_4 for line_in_4 */
#define REG_DSP2_LINE_OUT_2_LINE4_ADDR                   (REG_DSP2_LINE_IN_1_ADDR + 27) 

/* line_out_2_5 for usb_in_l */
#define REG_DSP2_LINE_OUT_2_USBL_ADDR                    (REG_DSP2_LINE_IN_1_ADDR + 28) 

/* line_out_2_6 for usb_in_r */
#define REG_DSP2_LINE_OUT_2_USBR_ADDR                    (REG_DSP2_LINE_IN_1_ADDR + 29) 

/* line_out_2_7 for dante_in_l */
#define REG_DSP2_LINE_OUT_2_DANTEL_ADDR                  (REG_DSP2_LINE_IN_1_ADDR + 30) 

/* line_out_2_8 for dante_in_r */
#define REG_DSP2_LINE_OUT_2_DANTER_ADDR                  (REG_DSP2_LINE_IN_1_ADDR + 31) 

/* line_out_2_9 for wire_wifi_mic_mixer_in */
#define REG_DSP2_LINE_OUT_2_ALL_MIC_MIX_ADDR             (REG_DSP2_LINE_IN_1_ADDR + 32) 

/* usb_out_l_1 for line_in_1 */
#define REG_DSP2_USB_OUT_L_LINE1_ADDR                    (REG_DSP2_LINE_IN_1_ADDR + 33) 

/* usb_out_l_2 for line_in_2 */
#define REG_DSP2_USB_OUT_L_LINE2_ADDR                    (REG_DSP2_LINE_IN_1_ADDR + 34) 

/* usb_out_l_3 for line_in_3 */
#define REG_DSP2_USB_OUT_L_LINE3_ADDR                    (REG_DSP2_LINE_IN_1_ADDR + 35) 

/* usb_out_l_4 for line_in_4 */
#define REG_DSP2_USB_OUT_L_LINE4_ADDR                    (REG_DSP2_LINE_IN_1_ADDR + 36) 

/* usb_out_l_5 for usb_in_l */
#define REG_DSP2_USB_OUT_L_USBL_ADDR                     (REG_DSP2_LINE_IN_1_ADDR + 37) 

/* usb_out_l_6 for usb_in_r */
#define REG_DSP2_USB_OUT_L_USBR_ADDR                     (REG_DSP2_LINE_IN_1_ADDR + 38) 

/* usb_out_l_7 for dante_in_l */
#define REG_DSP2_USB_OUT_L_DANTEL_ADDR                   (REG_DSP2_LINE_IN_1_ADDR + 39) 

/* usb_out_l_8 for dante_in_r */
#define REG_DSP2_USB_OUT_L_DANTER_ADDR                   (REG_DSP2_LINE_IN_1_ADDR + 40) 

/* usb_out_l_9 for wire_wifi_mic_mixer_in */
#define REG_DSP2_USB_OUT_L_ALL_MIC_MIX_ADDR              (REG_DSP2_LINE_IN_1_ADDR + 41) 

/* usb_out_r_1 for line_in_1 */
#define REG_DSP2_USB_OUT_R_LINE1_ADDR                    (REG_DSP2_LINE_IN_1_ADDR + 42) 

/* usb_out_r_2 for line_in_2 */
#define REG_DSP2_USB_OUT_R_LINE2_ADDR                    (REG_DSP2_LINE_IN_1_ADDR + 43) 

/* usb_out_r_3 for line_in_3 */
#define REG_DSP2_USB_OUT_R_LINE3_ADDR                    (REG_DSP2_LINE_IN_1_ADDR + 44) 

/* usb_out_r_4 for line_in_4 */
#define REG_DSP2_USB_OUT_R_LINE4_ADDR                    (REG_DSP2_LINE_IN_1_ADDR + 45) 

/* usb_out_r_5 for usb_in_l */
#define REG_DSP2_USB_OUT_R_USBL_ADDR                     (REG_DSP2_LINE_IN_1_ADDR + 46) 

/* usb_out_r_6 for usb_in_r */
#define REG_DSP2_USB_OUT_R_USBR_ADDR                     (REG_DSP2_LINE_IN_1_ADDR + 47) 

/* usb_out_r_7 for dante_in_l */
#define REG_DSP2_USB_OUT_R_DANTEL_ADDR                   (REG_DSP2_LINE_IN_1_ADDR + 48) 

/* usb_out_r_8 for dante_in_r */
#define REG_DSP2_USB_OUT_R_DANTER_ADDR                   (REG_DSP2_LINE_IN_1_ADDR + 49) 

/* usb_out_r_9 for wire_wifi_mic_mixer_in */
#define REG_DSP2_USB_OUT_R_ALL_MIC_MIX_ADDR              (REG_DSP2_LINE_IN_1_ADDR + 50) 

/* dante_out_l_1 for line_in_1 */
#define REG_DSP2_DANTE_OUT_L_LINE1_ADDR                  (REG_DSP2_LINE_IN_1_ADDR + 51) 

/* dante_out_l_2 for line_in_2 */
#define REG_DSP2_DANTE_OUT_L_LINE2_ADDR                  (REG_DSP2_LINE_IN_1_ADDR + 52) 

/* dante_out_l_3 for line_in_3 */
#define REG_DSP2_DANTE_OUT_L_LINE3_ADDR                  (REG_DSP2_LINE_IN_1_ADDR + 53) 

/* dante_out_l_4 for line_in_4 */
#define REG_DSP2_DANTE_OUT_L_LINE4_ADDR                  (REG_DSP2_LINE_IN_1_ADDR + 54) 

/* dante_out_l_5 for usb_in_l */
#define REG_DSP2_DANTE_OUT_L_USBL_ADDR                   (REG_DSP2_LINE_IN_1_ADDR + 55) 

/* dante_out_l_6 for usb_in_r */
#define REG_DSP2_DANTE_OUT_L_USBR_ADDR                   (REG_DSP2_LINE_IN_1_ADDR + 56) 

/* dante_out_l_7 for dante_in_l */
#define REG_DSP2_DANTE_OUT_L_DANTEL_ADDR                 (REG_DSP2_LINE_IN_1_ADDR + 57) 

/* dante_out_l_8 for dante_in_r */
#define REG_DSP2_DANTE_OUT_L_DANTER_ADDR                 (REG_DSP2_LINE_IN_1_ADDR + 58) 

/* dante_out_l_9 for wire_wifi_mic_mixer_in */
#define REG_DSP2_DANTE_OUT_L_ALL_MIC_MIX_ADDR            (REG_DSP2_LINE_IN_1_ADDR + 59) 

/* dante_out_r_1 for line_in_1 */
#define REG_DSP2_DANTE_OUT_R_LINE1_ADDR                  (REG_DSP2_LINE_IN_1_ADDR + 60) 

/* dante_out_r_2 for line_in_2 */
#define REG_DSP2_DANTE_OUT_R_LINE2_ADDR                  (REG_DSP2_LINE_IN_1_ADDR + 61) 

/* dante_out_r_3 for line_in_3 */
#define REG_DSP2_DANTE_OUT_R_LINE3_ADDR                  (REG_DSP2_LINE_IN_1_ADDR + 62) 

/* dante_out_r_4 for line_in_4 */
#define REG_DSP2_DANTE_OUT_R_LINE4_ADDR                  (REG_DSP2_LINE_IN_1_ADDR + 63) 

/* dante_out_r_5 for usb_in_l */
#define REG_DSP2_DANTE_OUT_R_USBL_ADDR                   (REG_DSP2_LINE_IN_1_ADDR + 64) 

/* dante_out_r_6 for usb_in_r */
#define REG_DSP2_DANTE_OUT_R_USBR_ADDR                   (REG_DSP2_LINE_IN_1_ADDR + 65) 

/* dante_out_r_7 for dante_in_l */
#define REG_DSP2_DANTE_OUT_R_DANTEL_ADDR                 (REG_DSP2_LINE_IN_1_ADDR + 66) 

/* dante_out_r_8 for dante_in_r */
#define REG_DSP2_DANTE_OUT_R_DANTER_ADDR                 (REG_DSP2_LINE_IN_1_ADDR + 67) 

/* dante_out_r_9 for wire_wifi_mic_mixer_in */
#define REG_DSP2_DANTE_OUT_R_ALL_MIC_MIX_ADDR            (REG_DSP2_LINE_IN_1_ADDR + 68) 

//Router1 end

//音源mute组件寄存器定义
//音源mute组件寄存器一次读出和写入 4bytes，取值0和1

/* line_in_1  mute */
#define REG_DSP2_LINE_IN_1_MUTE_ADDR              0x00BF

/* line_in_2  mute */
#define REG_DSP2_LINE_IN_2_MUTE_ADDR              (REG_DSP2_LINE_IN_1_MUTE_ADDR+1)

/* line_in_3  mute */
#define REG_DSP2_LINE_IN_3_MUTE_ADDR              (REG_DSP2_LINE_IN_1_MUTE_ADDR+2)

/* line_in_4  mute */
#define REG_DSP2_LINE_IN_4_MUTE_ADDR              (REG_DSP2_LINE_IN_1_MUTE_ADDR+3)

/* usb_in_l  mute */
#define REG_DSP2_USB_IN_L_MUTE_ADDR 	          (REG_DSP2_LINE_IN_1_MUTE_ADDR+4)

/* usb_in_r  mute */
#define REG_DSP2_USB_IN_R_MUTE_ADDR 	          (REG_DSP2_LINE_IN_1_MUTE_ADDR+5)

/* dante_in_l  mute */
#define REG_DSP2_DANTE_IN_L_MUTE_ADDR 	          (REG_DSP2_LINE_IN_1_MUTE_ADDR+6)

/* dante_in_r  mute */
#define REG_DSP2_DANTE_IN_R_MUTE_ADDR 	          (REG_DSP2_LINE_IN_1_MUTE_ADDR+7)

//音源single组件寄存器定义
//音源single组件寄存器一次读出和写入 4bytes
/* line_in_1 single */
#define REG_DSP2_LINE_IN_1_SINGLE_ADDR             0x00C7

/* line_in_2 single */
#define REG_DSP2_LINE_IN_2_SINGLE_ADDR             (REG_DSP2_LINE_IN_1_SINGLE_ADDR +1)

/* line_in_3 single */
#define REG_DSP2_LINE_IN_3_SINGLE_ADDR             (REG_DSP2_LINE_IN_1_SINGLE_ADDR +2)

/* line_in_4 single */
#define REG_DSP2_LINE_IN_4_SINGLE_ADDR             (REG_DSP2_LINE_IN_1_SINGLE_ADDR +3)

/* usb_in_l single */
#define REG_DSP2_USB_IN_L_SINGLE_ADDR              (REG_DSP2_LINE_IN_1_SINGLE_ADDR +4)

/* usb_in_r single */
#define REG_DSP2_USB_IN_R_SINGLE_ADDR              (REG_DSP2_LINE_IN_1_SINGLE_ADDR +5)

/* dante_in_l single */
#define REG_DSP2_DANTE_IN_L_SINGLE_ADDR            (REG_DSP2_LINE_IN_1_SINGLE_ADDR +6)

/* dante_in_r single */
#define REG_DSP2_DANTE_IN_R_SINGLE_ADDR            (REG_DSP2_LINE_IN_1_SINGLE_ADDR +7)



//输出mute组件寄存器定义
//输出mute组件寄存器一次读出和写入 4bytes，取值0和1

/* line_out_1  mute */
#define REG_DSP2_LINE_OUT_1_MUTE_ADDR              0x00CF

/* line_out_2  mute */
#define REG_DSP2_LINE_OUT_2_MUTE_ADDR              (REG_DSP2_LINE_OUT_1_MUTE_ADDR+1)

/* usb_out_l   mute */
#define REG_DSP2_USB_OUT_L_MUTE_ADDR               (REG_DSP2_LINE_OUT_1_MUTE_ADDR+2)

/* usb_out_r   mute */
#define REG_DSP2_USB_OUT_R_MUTE_ADDR               (REG_DSP2_LINE_OUT_1_MUTE_ADDR+3)

/* dante_out_l   mute */
#define REG_DSP2_DANTE_OUT_L_MUTE_ADDR             (REG_DSP2_LINE_OUT_1_MUTE_ADDR+4)

/* dante_out_r   mute */
#define REG_DSP2_DANTE_OUT_R_MUTE_ADDR             (REG_DSP2_LINE_OUT_1_MUTE_ADDR+5)

//输出single组件寄存器定义
//输出single组件寄存器一次读出和写入 4bytes
/* line_out_1 single */
#define REG_DSP2_LINE_OUT_1_SINGLE_ADDR             0x00D5

/* line_out_2 single */
#define REG_DSP2_LINE_OUT_2_SINGLE_ADDR             (REG_DSP2_LINE_OUT_1_SINGLE_ADDR +1)

/* usb_out_l single */
#define REG_DSP2_USB_OUT_L_SINGLE_ADDR              (REG_DSP2_LINE_OUT_1_SINGLE_ADDR +2)

/* usb_out_r single */
#define REG_DSP2_USB_OUT_R_SINGLE_ADDR              (REG_DSP2_LINE_OUT_1_SINGLE_ADDR +3)

/* dante_out_l single */
#define REG_DSP2_DANTE_OUT_L_SINGLE_ADDR            (REG_DSP2_LINE_OUT_1_SINGLE_ADDR +4)

/* dante_out_r single */
#define REG_DSP2_DANTE_OUT_R_SINGLE_ADDR            (REG_DSP2_LINE_OUT_1_SINGLE_ADDR +5)

//输出eq组件寄存器定义
//输出eq组件寄存器一次读出和写入 4bytes
/* line_out_1 */
#define REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR    	   		0x005B
#define REG_DSP2_LINE_OUT_1_EQ_1_2_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+1)
#define REG_DSP2_LINE_OUT_1_EQ_1_3_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+2)
#define REG_DSP2_LINE_OUT_1_EQ_1_4_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+3)
#define REG_DSP2_LINE_OUT_1_EQ_1_5_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+4)

#define REG_DSP2_LINE_OUT_1_EQ_2_1_ADDR    	   		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+5)
#define REG_DSP2_LINE_OUT_1_EQ_2_2_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+6)
#define REG_DSP2_LINE_OUT_1_EQ_2_3_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+7)
#define REG_DSP2_LINE_OUT_1_EQ_2_4_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+8)
#define REG_DSP2_LINE_OUT_1_EQ_2_5_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+9)

#define REG_DSP2_LINE_OUT_1_EQ_3_1_ADDR    	   		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+10)
#define REG_DSP2_LINE_OUT_1_EQ_3_2_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+11)
#define REG_DSP2_LINE_OUT_1_EQ_3_3_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+12)
#define REG_DSP2_LINE_OUT_1_EQ_3_4_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+13)
#define REG_DSP2_LINE_OUT_1_EQ_3_5_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+14)

#define REG_DSP2_LINE_OUT_1_EQ_4_1_ADDR    	   		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+15)
#define REG_DSP2_LINE_OUT_1_EQ_4_2_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+16)
#define REG_DSP2_LINE_OUT_1_EQ_4_3_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+17)
#define REG_DSP2_LINE_OUT_1_EQ_4_4_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+18)
#define REG_DSP2_LINE_OUT_1_EQ_4_5_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+19)

#define REG_DSP2_LINE_OUT_1_EQ_5_1_ADDR    	   		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+20)
#define REG_DSP2_LINE_OUT_1_EQ_5_2_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+21)
#define REG_DSP2_LINE_OUT_1_EQ_5_3_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+22)
#define REG_DSP2_LINE_OUT_1_EQ_5_4_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+23)
#define REG_DSP2_LINE_OUT_1_EQ_5_5_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+24)

#define REG_DSP2_LINE_OUT_1_EQ_6_1_ADDR    	   		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+25)
#define REG_DSP2_LINE_OUT_1_EQ_6_2_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+26)
#define REG_DSP2_LINE_OUT_1_EQ_6_3_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+27)
#define REG_DSP2_LINE_OUT_1_EQ_6_4_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+28)
#define REG_DSP2_LINE_OUT_1_EQ_6_5_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+29)

#define REG_DSP2_LINE_OUT_1_EQ_7_1_ADDR    	   		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+30)
#define REG_DSP2_LINE_OUT_1_EQ_7_2_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+31)
#define REG_DSP2_LINE_OUT_1_EQ_7_3_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+32)
#define REG_DSP2_LINE_OUT_1_EQ_7_4_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+33)
#define REG_DSP2_LINE_OUT_1_EQ_7_5_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+34)

#define REG_DSP2_LINE_OUT_1_EQ_8_1_ADDR    	   		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+35)
#define REG_DSP2_LINE_OUT_1_EQ_8_2_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+36)
#define REG_DSP2_LINE_OUT_1_EQ_8_3_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+37)
#define REG_DSP2_LINE_OUT_1_EQ_8_4_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+38)
#define REG_DSP2_LINE_OUT_1_EQ_8_5_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+39)

#define REG_DSP2_LINE_OUT_1_EQ_9_1_ADDR    	   		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+40)
#define REG_DSP2_LINE_OUT_1_EQ_9_2_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+41)
#define REG_DSP2_LINE_OUT_1_EQ_9_3_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+42)
#define REG_DSP2_LINE_OUT_1_EQ_9_4_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+43)
#define REG_DSP2_LINE_OUT_1_EQ_9_5_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+44)

#define REG_DSP2_LINE_OUT_1_EQ_10_1_ADDR    	   	(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+45)
#define REG_DSP2_LINE_OUT_1_EQ_10_2_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+46)
#define REG_DSP2_LINE_OUT_1_EQ_10_3_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+47)
#define REG_DSP2_LINE_OUT_1_EQ_10_4_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+48)
#define REG_DSP2_LINE_OUT_1_EQ_10_5_ADDR     		(REG_DSP2_LINE_OUT_1_EQ_1_1_ADDR+49)

/* line_out_2 */
#define REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR    	   		0x008D
#define REG_DSP2_LINE_OUT_2_EQ_1_2_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+1)
#define REG_DSP2_LINE_OUT_2_EQ_1_3_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+2)
#define REG_DSP2_LINE_OUT_2_EQ_1_4_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+3)
#define REG_DSP2_LINE_OUT_2_EQ_1_5_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+4)

#define REG_DSP2_LINE_OUT_2_EQ_2_1_ADDR    	   		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+5)
#define REG_DSP2_LINE_OUT_2_EQ_2_2_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+6)
#define REG_DSP2_LINE_OUT_2_EQ_2_3_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+7)
#define REG_DSP2_LINE_OUT_2_EQ_2_4_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+8)
#define REG_DSP2_LINE_OUT_2_EQ_2_5_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+9)

#define REG_DSP2_LINE_OUT_2_EQ_3_1_ADDR    	   		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+10)
#define REG_DSP2_LINE_OUT_2_EQ_3_2_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+11)
#define REG_DSP2_LINE_OUT_2_EQ_3_3_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+12)
#define REG_DSP2_LINE_OUT_2_EQ_3_4_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+13)
#define REG_DSP2_LINE_OUT_2_EQ_3_5_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+14)

#define REG_DSP2_LINE_OUT_2_EQ_4_1_ADDR    	   		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+15)
#define REG_DSP2_LINE_OUT_2_EQ_4_2_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+16)
#define REG_DSP2_LINE_OUT_2_EQ_4_3_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+17)
#define REG_DSP2_LINE_OUT_2_EQ_4_4_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+18)
#define REG_DSP2_LINE_OUT_2_EQ_4_5_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+19)

#define REG_DSP2_LINE_OUT_2_EQ_5_1_ADDR    	   		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+20)
#define REG_DSP2_LINE_OUT_2_EQ_5_2_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+21)
#define REG_DSP2_LINE_OUT_2_EQ_5_3_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+22)
#define REG_DSP2_LINE_OUT_2_EQ_5_4_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+23)
#define REG_DSP2_LINE_OUT_2_EQ_5_5_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+24)

#define REG_DSP2_LINE_OUT_2_EQ_6_1_ADDR    	   		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+25)
#define REG_DSP2_LINE_OUT_2_EQ_6_2_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+26)
#define REG_DSP2_LINE_OUT_2_EQ_6_3_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+27)
#define REG_DSP2_LINE_OUT_2_EQ_6_4_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+28)
#define REG_DSP2_LINE_OUT_2_EQ_6_5_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+29)

#define REG_DSP2_LINE_OUT_2_EQ_7_1_ADDR    	   		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+30)
#define REG_DSP2_LINE_OUT_2_EQ_7_2_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+31)
#define REG_DSP2_LINE_OUT_2_EQ_7_3_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+32)
#define REG_DSP2_LINE_OUT_2_EQ_7_4_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+33)
#define REG_DSP2_LINE_OUT_2_EQ_7_5_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+34)

#define REG_DSP2_LINE_OUT_2_EQ_8_1_ADDR    	   		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+35)
#define REG_DSP2_LINE_OUT_2_EQ_8_2_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+36)
#define REG_DSP2_LINE_OUT_2_EQ_8_3_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+37)
#define REG_DSP2_LINE_OUT_2_EQ_8_4_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+38)
#define REG_DSP2_LINE_OUT_2_EQ_8_5_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+39)

#define REG_DSP2_LINE_OUT_2_EQ_9_1_ADDR    	   		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+40)
#define REG_DSP2_LINE_OUT_2_EQ_9_2_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+41)
#define REG_DSP2_LINE_OUT_2_EQ_9_3_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+42)
#define REG_DSP2_LINE_OUT_2_EQ_9_4_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+43)
#define REG_DSP2_LINE_OUT_2_EQ_9_5_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+44)

#define REG_DSP2_LINE_OUT_2_EQ_10_1_ADDR   	   		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+45)
#define REG_DSP2_LINE_OUT_2_EQ_10_2_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+46)
#define REG_DSP2_LINE_OUT_2_EQ_10_3_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+47)
#define REG_DSP2_LINE_OUT_2_EQ_10_4_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+48)
#define REG_DSP2_LINE_OUT_2_EQ_10_5_ADDR     		(REG_DSP2_LINE_OUT_2_EQ_1_1_ADDR+49)




//===========================DSP1========================//
//矩阵组件寄存器定义
//矩阵组件寄存器一次读出和写入 4bytes
/* wire_in_1 */
#define REG_DSP1_WIRE_IN_1_ADDR                           0x001C

/* wire_in_2 */
#define REG_DSP1_WIRE_IN_2_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 1)

/* wire_in_3 */
#define REG_DSP1_WIRE_IN_3_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 2)

/* wire_in_4 */
#define REG_DSP1_WIRE_IN_4_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 3)

/* wire_in_5 */
#define REG_DSP1_WIRE_IN_5_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 4)

/* wire_in_6 */
#define REG_DSP1_WIRE_IN_6_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 5)

/* wire_in_7 */
#define REG_DSP1_WIRE_IN_7_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 6)

/* wire_in_8 */
#define REG_DSP1_WIRE_IN_8_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 7)

/* wifi_in_1 */
#define REG_DSP1_WIFI_IN_1_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 8)

/* wifi_in_2 */
#define REG_DSP1_WIFI_IN_2_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 9)

/* wifi_in_3 */
#define REG_DSP1_WIFI_IN_3_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 10)

/* wifi_in_4 */
#define REG_DSP1_WIFI_IN_4_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 11)

/* wifi_in_5 */
#define REG_DSP1_WIFI_IN_5_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 12)

/* wifi_in_6 */
#define REG_DSP1_WIFI_IN_6_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 13)

/* line_in_1 */
#define REG_DSP1_LINE_IN_1_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 14)

/* line_in_2 */
#define REG_DSP1_LINE_IN_2_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 15)

/* line_in_3 */
#define REG_DSP1_LINE_IN_3_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 16)

/* line_in_4 */
#define REG_DSP1_LINE_IN_4_ADDR                           (REG_DSP1_WIRE_IN_1_ADDR + 17)

/* usb_in_l */
#define REG_DSP1_USB_IN_L_ADDR                            (REG_DSP1_WIRE_IN_1_ADDR + 18)

/* usb_in_r */
#define REG_DSP1_USB_IN_R_ADDR                            (REG_DSP1_WIRE_IN_1_ADDR + 19)

/* dante_in_l */
#define REG_DSP1_DANTE_IN_L_ADDR                          (REG_DSP1_WIRE_IN_1_ADDR + 20)

/* dante_in_r */
#define REG_DSP1_DANTE_IN_R_ADDR                          (REG_DSP1_WIRE_IN_1_ADDR + 21)

/* channel_out_1 for all in*/
#define REG_DSP1_CHANNEL_OUT_1_ADDR                       (REG_DSP1_WIRE_IN_1_ADDR + 22)

/* channel_out_2 for all in*/
#define REG_DSP1_CHANNEL_OUT_2_ADDR                       (REG_DSP1_WIRE_IN_1_ADDR + 23)

/* channel_out_3 for all in*/
#define REG_DSP1_CHANNEL_OUT_3_ADDR                       (REG_DSP1_WIRE_IN_1_ADDR + 24)

/* channel_out_4 for all in*/
#define REG_DSP1_CHANNEL_OUT_4_ADDR                       (REG_DSP1_WIRE_IN_1_ADDR + 25)

/* channel_out_5 for all in*/
#define REG_DSP1_CHANNEL_OUT_5_ADDR                       (REG_DSP1_WIRE_IN_1_ADDR + 26)

/* channel_out_6 for all in*/
#define REG_DSP1_CHANNEL_OUT_6_ADDR                       (REG_DSP1_WIRE_IN_1_ADDR + 27)

/* channel_out_7 for all in*/
#define REG_DSP1_CHANNEL_OUT_7_ADDR                       (REG_DSP1_WIRE_IN_1_ADDR + 28)

/* channel_out_8 for all in*/
#define REG_DSP1_CHANNEL_OUT_8_ADDR                       (REG_DSP1_WIRE_IN_1_ADDR + 29)

/* channel_out_9 for all in*/
#define REG_DSP1_CHANNEL_OUT_9_ADDR                       (REG_DSP1_WIRE_IN_1_ADDR + 30)

/* channel_out_10 for all in*/
#define REG_DSP1_CHANNEL_OUT_10_ADDR                      (REG_DSP1_WIRE_IN_1_ADDR + 31)

/* channel_out_11 for all in*/
#define REG_DSP1_CHANNEL_OUT_11_ADDR                      (REG_DSP1_WIRE_IN_1_ADDR + 32)

/* channel_out_12 for all in*/
#define REG_DSP1_CHANNEL_OUT_12_ADDR                      (REG_DSP1_WIRE_IN_1_ADDR + 33)

/* channel_out_13 for all in*/
#define REG_DSP1_CHANNEL_OUT_13_ADDR                      (REG_DSP1_WIRE_IN_1_ADDR + 34)

/* channel_out_14 for all in*/
#define REG_DSP1_CHANNEL_OUT_14_ADDR                      (REG_DSP1_WIRE_IN_1_ADDR + 35)

/* channel_out_15 for all in*/
#define REG_DSP1_CHANNEL_OUT_15_ADDR                      (REG_DSP1_WIRE_IN_1_ADDR + 36)

/* channel_out_16 for all in*/
#define REG_DSP1_CHANNEL_OUT_16_ADDR                      (REG_DSP1_WIRE_IN_1_ADDR + 37)

/* channel_out_mixer_to_si for all mixer or all mic mixer in to simultaneous interpreting*/
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_ADDR             (REG_DSP1_WIRE_IN_1_ADDR + 38)

/* channel_out_mixer_to_dsp2 for all mic mixer in to dsp2 */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_ADDR           (REG_DSP1_WIRE_IN_1_ADDR + 39)

/* channel_out_mixer_to_wifi for all mixer in to wifi */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_ADDR           (REG_DSP1_WIRE_IN_1_ADDR + 40)

/* channel_out_mixer_to_wire for all mixer in to wire */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_ADDR           (REG_DSP1_WIRE_IN_1_ADDR + 41)

/* channel_out_1 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_1_WIRE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 42)

/* channel_out_1 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_1_WIRE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 43)

/* channel_out_1 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_1_WIRE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 44)

/* channel_out_1 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_1_WIRE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 45)

/* channel_out_1 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_1_WIRE5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 46)

/* channel_out_1 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_1_WIRE6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 47)

/* channel_out_1 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_1_WIRE7_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 48)

/* channel_out_1 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_1_WIRE8_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 49)

/* channel_out_1 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_1_WIFI1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 50)

/* channel_out_1 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_1_WIFI2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 51)

/* channel_out_1 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_1_WIFI3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 52)

/* channel_out_1 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_1_WIFI4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 53)

/* channel_out_1 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_1_WIFI5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 54)

/* channel_out_1 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_1_WIFI6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 55)

/* channel_out_1 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_1_LINE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 56)

/* channel_out_1 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_1_LINE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 57)

/* channel_out_1 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_1_LINE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 58)

/* channel_out_1 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_1_LINE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 59)

/* channel_out_1 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_1_USBL_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 60)

/* channel_out_1 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_1_USBR_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 61)

/* channel_out_1 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_1_DANTEL_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 62)

/* channel_out_1 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_1_DANTER_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 63)

/* channel_out_2 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_2_WIRE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 64)

/* channel_out_2 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_2_WIRE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 65)

/* channel_out_2 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_2_WIRE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 66)

/* channel_out_2 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_2_WIRE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 67)

/* channel_out_2 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_2_WIRE5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 68)

/* channel_out_2 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_2_WIRE6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 69)

/* channel_out_2 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_2_WIRE7_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 70)

/* channel_out_2 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_2_WIRE8_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 71)

/* channel_out_2 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_2_WIFI1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 72)

/* channel_out_2 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_2_WIFI2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 73)

/* channel_out_2 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_2_WIFI3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 74)

/* channel_out_2 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_2_WIFI4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 75)

/* channel_out_2 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_2_WIFI5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 76)

/* channel_out_2 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_2_WIFI6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 77)

/* channel_out_2 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_2_LINE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 78)

/* channel_out_2 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_2_LINE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 79)

/* channel_out_2 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_2_LINE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 80)

/* channel_out_2 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_2_LINE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 81)

/* channel_out_2 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_2_USBL_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 82)

/* channel_out_2 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_2_USBR_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 83)

/* channel_out_2 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_2_DANTEL_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 84)

/* channel_out_2 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_2_DANTER_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 85)

/* channel_out_3 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_3_WIRE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 86)

/* channel_out_3 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_3_WIRE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 87)

/* channel_out_3 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_3_WIRE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 88)

/* channel_out_3 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_3_WIRE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 89)

/* channel_out_3 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_3_WIRE5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 90)

/* channel_out_3 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_3_WIRE6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 91)

/* channel_out_3 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_3_WIRE7_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 92)

/* channel_out_3 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_3_WIRE8_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 93)

/* channel_out_3 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_3_WIFI1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 94)

/* channel_out_3 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_3_WIFI2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 95)

/* channel_out_3 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_3_WIFI3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 96)

/* channel_out_3 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_3_WIFI4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 97)

/* channel_out_3 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_3_WIFI5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 98)

/* channel_out_3 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_3_WIFI6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 99)

/* channel_out_3 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_3_LINE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 100)

/* channel_out_3 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_3_LINE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 101)

/* channel_out_3 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_3_LINE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 102)

/* channel_out_3 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_3_LINE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 103)

/* channel_out_3 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_3_USBL_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 104)

/* channel_out_3 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_3_USBR_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 105)

/* channel_out_3 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_3_DANTEL_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 106)

/* channel_out_3 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_3_DANTER_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 107)

/* channel_out_4 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_4_WIRE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 108)

/* channel_out_4 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_4_WIRE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 109)

/* channel_out_4 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_4_WIRE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 110)

/* channel_out_4 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_4_WIRE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 111)

/* channel_out_4 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_4_WIRE5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 112)

/* channel_out_4 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_4_WIRE6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 113)

/* channel_out_4 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_4_WIRE7_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 114)

/* channel_out_4 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_4_WIRE8_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 115)

/* channel_out_4 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_4_WIFI1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 116)

/* channel_out_4 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_4_WIFI2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 117)

/* channel_out_4 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_4_WIFI3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 118)

/* channel_out_4 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_4_WIFI4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 119)

/* channel_out_4 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_4_WIFI5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 120)

/* channel_out_4 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_4_WIFI6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 121)

/* channel_out_4 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_4_LINE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 122)

/* channel_out_4 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_4_LINE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 123)

/* channel_out_4 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_4_LINE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 124)

/* channel_out_4 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_4_LINE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 125)

/* channel_out_4 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_4_USBL_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 126)

/* channel_out_4 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_4_USBR_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 127)

/* channel_out_4 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_4_DANTEL_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 128)

/* channel_out_4 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_4_DANTER_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 129)

/* channel_out_5 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_5_WIRE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 130)

/* channel_out_5 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_5_WIRE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 131)

/* channel_out_5 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_5_WIRE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 132)

/* channel_out_5 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_5_WIRE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 133)

/* channel_out_5 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_5_WIRE5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 134)

/* channel_out_5 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_5_WIRE6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 135)

/* channel_out_5 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_5_WIRE7_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 136)

/* channel_out_5 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_5_WIRE8_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 137)

/* channel_out_5 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_5_WIFI1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 138)

/* channel_out_5 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_5_WIFI2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 139)

/* channel_out_5 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_5_WIFI3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 140)

/* channel_out_5 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_5_WIFI4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 141)

/* channel_out_5 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_5_WIFI5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 142)

/* channel_out_5 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_5_WIFI6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 143)

/* channel_out_5 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_5_LINE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 144)

/* channel_out_5 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_5_LINE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 145)

/* channel_out_5 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_5_LINE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 146)

/* channel_out_5 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_5_LINE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 147)

/* channel_out_5 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_5_USBL_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 148)

/* channel_out_5 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_5_USBR_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 149)

/* channel_out_5 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_5_DANTEL_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 150)

/* channel_out_5 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_5_DANTER_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 151)

/* channel_out_6 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_6_WIRE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 152)

/* channel_out_6 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_6_WIRE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 153)

/* channel_out_6 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_6_WIRE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 154)

/* channel_out_6 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_6_WIRE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 155)

/* channel_out_6 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_6_WIRE5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 156)

/* channel_out_6 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_6_WIRE6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 157)

/* channel_out_6 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_6_WIRE7_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 158)

/* channel_out_6 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_6_WIRE8_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 159)

/* channel_out_6 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_6_WIFI1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 160)

/* channel_out_6 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_6_WIFI2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 161)

/* channel_out_6 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_6_WIFI3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 162)

/* channel_out_6 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_6_WIFI4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 163)

/* channel_out_6 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_6_WIFI5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 164)

/* channel_out_6 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_6_WIFI6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 165)

/* channel_out_6 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_6_LINE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 166)

/* channel_out_6 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_6_LINE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 167)

/* channel_out_6 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_6_LINE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 168)

/* channel_out_6 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_6_LINE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 169)

/* channel_out_6 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_6_USBL_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 170)

/* channel_out_6 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_6_USBR_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 171)

/* channel_out_6 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_6_DANTEL_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 172)

/* channel_out_6 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_6_DANTER_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 173)

/* channel_out_7 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_7_WIRE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 174)

/* channel_out_7 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_7_WIRE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 175)

/* channel_out_7 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_7_WIRE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 176)

/* channel_out_7 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_7_WIRE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 177)

/* channel_out_7 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_7_WIRE5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 178)

/* channel_out_7 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_7_WIRE6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 179)

/* channel_out_7 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_7_WIRE7_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 180)

/* channel_out_7 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_7_WIRE8_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 181)

/* channel_out_7 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_7_WIFI1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 182)

/* channel_out_7 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_7_WIFI2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 183)

/* channel_out_7 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_7_WIFI3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 184)

/* channel_out_7 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_7_WIFI4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 185)

/* channel_out_7 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_7_WIFI5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 186)

/* channel_out_7 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_7_WIFI6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 187)

/* channel_out_7 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_7_LINE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 188)

/* channel_out_7 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_7_LINE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 189)

/* channel_out_7 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_7_LINE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 190)

/* channel_out_7 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_7_LINE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 191)

/* channel_out_7 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_7_USBL_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 192)

/* channel_out_7 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_7_USBR_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 193)

/* channel_out_7 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_7_DANTEL_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 194)

/* channel_out_7 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_7_DANTER_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 195)

/* channel_out_8 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_8_WIRE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 196)

/* channel_out_8 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_8_WIRE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 197)

/* channel_out_8 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_8_WIRE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 198)

/* channel_out_8 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_8_WIRE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 199)

/* channel_out_8 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_8_WIRE5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 200)

/* channel_out_8 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_8_WIRE6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 201)

/* channel_out_8 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_8_WIRE7_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 202)

/* channel_out_8 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_8_WIRE8_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 203)

/* channel_out_8 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_8_WIFI1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 204)

/* channel_out_8 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_8_WIFI2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 205)

/* channel_out_8 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_8_WIFI3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 206)

/* channel_out_8 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_8_WIFI4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 207)

/* channel_out_8 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_8_WIFI5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 208)

/* channel_out_8 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_8_WIFI6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 209)

/* channel_out_8 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_8_LINE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 210)

/* channel_out_8 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_8_LINE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 211)

/* channel_out_8 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_8_LINE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 212)

/* channel_out_8 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_8_LINE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 213)

/* channel_out_8 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_8_USBL_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 214)

/* channel_out_8 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_8_USBR_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 215)

/* channel_out_8 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_8_DANTEL_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 216)

/* channel_out_8 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_8_DANTER_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 217)

/* channel_out_9 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_9_WIRE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 218)

/* channel_out_9 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_9_WIRE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 219)

/* channel_out_9 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_9_WIRE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 220)

/* channel_out_9 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_9_WIRE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 221)

/* channel_out_9 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_9_WIRE5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 222)

/* channel_out_9 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_9_WIRE6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 223)

/* channel_out_9 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_9_WIRE7_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 224)

/* channel_out_9 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_9_WIRE8_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 225)

/* channel_out_9 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_9_WIFI1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 226)

/* channel_out_9 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_9_WIFI2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 227)

/* channel_out_9 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_9_WIFI3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 228)

/* channel_out_9 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_9_WIFI4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 229)

/* channel_out_9 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_9_WIFI5_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 230)

/* channel_out_9 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_9_WIFI6_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 231)

/* channel_out_9 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_9_LINE1_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 232)

/* channel_out_9 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_9_LINE2_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 233)

/* channel_out_9 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_9_LINE3_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 234)

/* channel_out_9 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_9_LINE4_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 235)

/* channel_out_9 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_9_USBL_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 236)

/* channel_out_9 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_9_USBR_ADDR                  (REG_DSP1_WIRE_IN_1_ADDR + 237)

/* channel_out_9 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_9_DANTEL_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 238)

/* channel_out_9 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_9_DANTER_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 239)

/* channel_out_10 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_10_WIRE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 240)

/* channel_out_10 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_10_WIRE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 241)

/* channel_out_10 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_10_WIRE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 242)

/* channel_out_10 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_10_WIRE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 243)

/* channel_out_10 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_10_WIRE5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 244)

/* channel_out_10 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_10_WIRE6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 245)

/* channel_out_10 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_10_WIRE7_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 246)

/* channel_out_10 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_10_WIRE8_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 247)

/* channel_out_10 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_10_WIFI1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 248)

/* channel_out_10 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_10_WIFI2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 249)

/* channel_out_10 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_10_WIFI3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 250)

/* channel_out_10 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_10_WIFI4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 251)

/* channel_out_10 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_10_WIFI5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 252)

/* channel_out_10 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_10_WIFI6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 253)

/* channel_out_10 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_10_LINE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 254)

/* channel_out_10 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_10_LINE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 255)

/* channel_out_10 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_10_LINE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 256)

/* channel_out_10 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_10_LINE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 257)

/* channel_out_10 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_10_USBL_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 258)

/* channel_out_10 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_10_USBR_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 259)

/* channel_out_10 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_10_DANTEL_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 260)

/* channel_out_10 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_10_DANTER_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 261)

/* channel_out_11 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_11_WIRE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 262)

/* channel_out_11 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_11_WIRE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 263)

/* channel_out_11 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_11_WIRE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 264)

/* channel_out_11 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_11_WIRE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 265)

/* channel_out_11 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_11_WIRE5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 266)

/* channel_out_11 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_11_WIRE6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 267)

/* channel_out_11 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_11_WIRE7_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 268)

/* channel_out_11 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_11_WIRE8_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 269)

/* channel_out_11 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_11_WIFI1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 270)

/* channel_out_11 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_11_WIFI2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 271)

/* channel_out_11 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_11_WIFI3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 272)

/* channel_out_11 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_11_WIFI4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 273)

/* channel_out_11 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_11_WIFI5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 274)

/* channel_out_11 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_11_WIFI6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 275)

/* channel_out_11 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_11_LINE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 276)

/* channel_out_11 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_11_LINE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 277)

/* channel_out_11 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_11_LINE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 278)

/* channel_out_11 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_11_LINE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 279)

/* channel_out_11 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_11_USBL_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 280)

/* channel_out_11 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_11_USBR_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 281)

/* channel_out_11 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_11_DANTEL_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 282)

/* channel_out_11 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_11_DANTER_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 283)

/* channel_out_12 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_12_WIRE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 284)

/* channel_out_12 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_12_WIRE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 285)

/* channel_out_12 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_12_WIRE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 286)

/* channel_out_12 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_12_WIRE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 287)

/* channel_out_12 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_12_WIRE5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 288)

/* channel_out_12 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_12_WIRE6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 289)

/* channel_out_12 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_12_WIRE7_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 290)

/* channel_out_12 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_12_WIRE8_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 291)

/* channel_out_12 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_12_WIFI1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 292)

/* channel_out_12 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_12_WIFI2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 293)

/* channel_out_12 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_12_WIFI3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 294)

/* channel_out_12 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_12_WIFI4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 295)

/* channel_out_12 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_12_WIFI5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 296)

/* channel_out_12 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_12_WIFI6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 297)

/* channel_out_12 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_12_LINE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 298)

/* channel_out_12 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_12_LINE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 299)

/* channel_out_12 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_12_LINE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 300)

/* channel_out_12 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_12_LINE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 301)

/* channel_out_12 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_12_USBL_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 302)

/* channel_out_12 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_12_USBR_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 303)

/* channel_out_12 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_12_DANTEL_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 304)

/* channel_out_12 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_12_DANTER_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 305)

/* channel_out_13 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_13_WIRE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 306)

/* channel_out_13 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_13_WIRE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 307)

/* channel_out_13 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_13_WIRE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 308)

/* channel_out_13 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_13_WIRE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 309)

/* channel_out_13 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_13_WIRE5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 310)

/* channel_out_13 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_13_WIRE6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 311)

/* channel_out_13 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_13_WIRE7_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 312)

/* channel_out_13 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_13_WIRE8_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 313)

/* channel_out_13 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_13_WIFI1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 314)

/* channel_out_13 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_13_WIFI2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 315)

/* channel_out_13 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_13_WIFI3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 316)

/* channel_out_13 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_13_WIFI4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 317)

/* channel_out_13 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_13_WIFI5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 318)

/* channel_out_13 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_13_WIFI6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 319)

/* channel_out_13 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_13_LINE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 320)

/* channel_out_13 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_13_LINE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 321)

/* channel_out_13 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_13_LINE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 322)

/* channel_out_13 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_13_LINE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 323)

/* channel_out_13 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_13_USBL_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 324)

/* channel_out_13 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_13_USBR_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 325)

/* channel_out_13 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_13_DANTEL_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 326)

/* channel_out_13 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_13_DANTER_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 327)

/* channel_out_14 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_14_WIRE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 328)

/* channel_out_14 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_14_WIRE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 329)

/* channel_out_14 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_14_WIRE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 330)

/* channel_out_14 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_14_WIRE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 331)

/* channel_out_14 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_14_WIRE5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 332)

/* channel_out_14 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_14_WIRE6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 333)

/* channel_out_14 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_14_WIRE7_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 334)

/* channel_out_14 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_14_WIRE8_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 335)

/* channel_out_14 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_14_WIFI1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 336)

/* channel_out_14 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_14_WIFI2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 337)

/* channel_out_14 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_14_WIFI3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 338)

/* channel_out_14 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_14_WIFI4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 339)

/* channel_out_14 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_14_WIFI5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 340)

/* channel_out_14 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_14_WIFI6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 341)

/* channel_out_14 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_14_LINE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 342)

/* channel_out_14 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_14_LINE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 343)

/* channel_out_14 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_14_LINE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 344)

/* channel_out_14 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_14_LINE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 345)

/* channel_out_14 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_14_USBL_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 346)

/* channel_out_14 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_14_USBR_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 347)

/* channel_out_14 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_14_DANTEL_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 348)

/* channel_out_14 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_14_DANTER_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 349)

/* channel_out_15 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_15_WIRE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 350)

/* channel_out_15 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_15_WIRE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 351)

/* channel_out_15 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_15_WIRE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 352)

/* channel_out_15 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_15_WIRE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 353)

/* channel_out_15 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_15_WIRE5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 354)

/* channel_out_15 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_15_WIRE6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 355)

/* channel_out_15 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_15_WIRE7_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 356)

/* channel_out_15 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_15_WIRE8_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 357)

/* channel_out_15 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_15_WIFI1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 358)

/* channel_out_15 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_15_WIFI2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 359)

/* channel_out_15 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_15_WIFI3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 360)

/* channel_out_15 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_15_WIFI4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 361)

/* channel_out_15 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_15_WIFI5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 362)

/* channel_out_15 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_15_WIFI6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 363)

/* channel_out_15 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_15_LINE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 364)

/* channel_out_15 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_15_LINE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 365)

/* channel_out_15 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_15_LINE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 366)

/* channel_out_15 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_15_LINE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 367)

/* channel_out_15 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_15_USBL_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 368)

/* channel_out_15 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_15_USBR_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 369)

/* channel_out_15 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_15_DANTEL_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 370)

/* channel_out_15 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_15_DANTER_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 371)

/* channel_out_16 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_16_WIRE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 372)

/* channel_out_16 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_16_WIRE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 373)

/* channel_out_16 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_16_WIRE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 374)

/* channel_out_16 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_16_WIRE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 375)

/* channel_out_16 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_16_WIRE5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 376)

/* channel_out_16 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_16_WIRE6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 377)

/* channel_out_16 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_16_WIRE7_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 378)

/* channel_out_16 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_16_WIRE8_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 379)

/* channel_out_16 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_16_WIFI1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 380)

/* channel_out_16 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_16_WIFI2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 381)

/* channel_out_16 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_16_WIFI3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 382)

/* channel_out_16 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_16_WIFI4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 383)

/* channel_out_16 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_16_WIFI5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 384)

/* channel_out_16 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_16_WIFI6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 385)

/* channel_out_16 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_16_LINE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 386)

/* channel_out_16 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_16_LINE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 387)

/* channel_out_16 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_16_LINE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 388)

/* channel_out_16 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_16_LINE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 389)

/* channel_out_16 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_16_USBL_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 390)

/* channel_out_16 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_16_USBR_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 391)

/* channel_out_16 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_16_DANTEL_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 392)

/* channel_out_16 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_16_DANTER_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 393)

/* channel_out_mixer_to_si for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_WIRE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 394)

/* channel_out_mixer_to_si for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_WIRE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 395)

/* channel_out_mixer_to_si for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_WIRE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 396)

/* channel_out_mixer_to_si for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_WIRE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 397)

/* channel_out_mixer_to_si for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_WIRE5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 398)

/* channel_out_mixer_to_si for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_WIRE6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 399)

/* channel_out_mixer_to_si for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_WIRE7_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 400)

/* channel_out_mixer_to_si for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_WIRE8_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 401)

/* channel_out_mixer_to_si for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_WIFI1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 402)

/* channel_out_mixer_to_si for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_WIFI2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 403)

/* channel_out_mixer_to_si for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_WIFI3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 404)

/* channel_out_mixer_to_si for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_WIFI4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 405)

/* channel_out_mixer_to_si for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_WIFI5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 406)

/* channel_out_mixer_to_si for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_WIFI6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 407)

/* channel_out_mixer_to_si for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_LINE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 408)

/* channel_out_mixer_to_si for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_LINE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 409)

/* channel_out_mixer_to_si for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_LINE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 410)

/* channel_out_mixer_to_si for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_LINE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 411)

/* channel_out_mixer_to_si for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_USBL_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 412)

/* channel_out_mixer_to_si for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_USBR_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 413)

/* channel_out_mixer_to_si for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_DANTEL_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 414)

/* channel_out_mixer_to_si for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_SI_DANTER_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 415)

/* channel_out_mixer_to_dsp2 for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_WIRE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 416)

/* channel_out_mixer_to_dsp2 for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_WIRE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 417)

/* channel_out_mixer_to_dsp2 for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_WIRE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 418)

/* channel_out_mixer_to_dsp2 for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_WIRE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 419)

/* channel_out_mixer_to_dsp2 for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_WIRE5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 420)

/* channel_out_mixer_to_dsp2 for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_WIRE6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 421)

/* channel_out_mixer_to_dsp2 for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_WIRE7_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 422)

/* channel_out_mixer_to_dsp2 for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_WIRE8_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 423)

/* channel_out_mixer_to_dsp2 for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_WIFI1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 424)

/* channel_out_mixer_to_dsp2 for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_WIFI2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 425)

/* channel_out_mixer_to_dsp2 for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_WIFI3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 426)

/* channel_out_mixer_to_dsp2 for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_WIFI4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 427)

/* channel_out_mixer_to_dsp2 for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_WIFI5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 428)

/* channel_out_mixer_to_dsp2 for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_WIFI6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 429)

/* channel_out_mixer_to_dsp2 for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_LINE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 430)

/* channel_out_mixer_to_dsp2 for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_LINE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 431)

/* channel_out_mixer_to_dsp2 for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_LINE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 432)

/* channel_out_mixer_to_dsp2 for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_LINE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 433)

/* channel_out_mixer_to_dsp2 for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_USBL_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 434)

/* channel_out_mixer_to_dsp2 for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_USBR_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 435)

/* channel_out_mixer_to_dsp2 for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_DANTEL_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 436)

/* channel_out_mixer_to_dsp2 for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_DSP2_DANTER_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 437)

/* channel_out_mixer_to_wifi for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_WIRE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 438)

/* channel_out_mixer_to_wifi for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_WIRE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 439)

/* channel_out_mixer_to_wifi for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_WIRE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 440)

/* channel_out_mixer_to_wifi for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_WIRE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 441)

/* channel_out_mixer_to_wifi for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_WIRE5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 442)

/* channel_out_mixer_to_wifi for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_WIRE6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 443)

/* channel_out_mixer_to_wifi for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_WIRE7_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 444)

/* channel_out_mixer_to_wifi for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_WIRE8_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 445)

/* channel_out_mixer_to_wifi for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_WIFI1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 446)

/* channel_out_mixer_to_wifi for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_WIFI2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 447)

/* channel_out_mixer_to_wifi for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_WIFI3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 448)

/* channel_out_mixer_to_wifi for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_WIFI4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 449)

/* channel_out_mixer_to_wifi for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_WIFI5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 450)

/* channel_out_mixer_to_wifi for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_WIFI6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 451)

/* channel_out_mixer_to_wifi for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_LINE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 452)

/* channel_out_mixer_to_wifi for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_LINE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 453)

/* channel_out_mixer_to_wifi for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_LINE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 454)

/* channel_out_mixer_to_wifi for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_LINE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 455)

/* channel_out_mixer_to_wifi for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_USBL_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 456)

/* channel_out_mixer_to_wifi for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_USBR_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 457)

/* channel_out_mixer_to_wifi for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_DANTEL_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 458)

/* channel_out_mixer_to_wifi for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIFI_DANTER_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 459)

/* channel_out_mixer_to_wire for wire_in_1  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_WIRE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 460)

/* channel_out_mixer_to_wire for wire_in_2  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_WIRE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 461)

/* channel_out_mixer_to_wire for wire_in_3  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_WIRE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 462)

/* channel_out_mixer_to_wire for wire_in_4  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_WIRE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 463)

/* channel_out_mixer_to_wire for wire_in_5  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_WIRE5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 464)

/* channel_out_mixer_to_wire for wire_in_6  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_WIRE6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 465)

/* channel_out_mixer_to_wire for wire_in_7  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_WIRE7_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 466)

/* channel_out_mixer_to_wire for wire_in_8  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_WIRE8_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 467)

/* channel_out_mixer_to_wire for wifi_in_1  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_WIFI1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 468)

/* channel_out_mixer_to_wire for wifi_in_2  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_WIFI2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 469)

/* channel_out_mixer_to_wire for wifi_in_3  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_WIFI3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 470)

/* channel_out_mixer_to_wire for wifi_in_4  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_WIFI4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 471)

/* channel_out_mixer_to_wire for wifi_in_5  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_WIFI5_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 472)

/* channel_out_mixer_to_wire for wifi_in_6  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_WIFI6_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 473)

/* channel_out_mixer_to_wire for line_in_1  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_LINE1_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 474)

/* channel_out_mixer_to_wire for line_in_2  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_LINE2_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 475)

/* channel_out_mixer_to_wire for line_in_3  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_LINE3_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 476)

/* channel_out_mixer_to_wire for line_in_4  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_LINE4_ADDR                (REG_DSP1_WIRE_IN_1_ADDR + 477)

/* channel_out_mixer_to_wire for usb_in_l  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_USBL_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 478)

/* channel_out_mixer_to_wire for usb_in_r  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_USBR_ADDR                 (REG_DSP1_WIRE_IN_1_ADDR + 479)

/* channel_out_mixer_to_wire for dante_in_l  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_DANTEL_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 480)

/* channel_out_mixer_to_wire for dante_in_r  */
#define REG_DSP1_CHANNEL_OUT_MIXER_TO_WIRE_DANTER_ADDR               (REG_DSP1_WIRE_IN_1_ADDR + 481)

//通道开关组件寄存器定义
//通道开关组件寄存器一次读出和写入 4bytes，取值0和1

/* channel 1 mono switch */
#define REG_DSP1_CH1_MONO_SWITCH_ADDR               (REG_DSP1_CH2_MONO_SWITCH_ADDR + 15)

/* channel 2 mono switch */
#define REG_DSP1_CH2_MONO_SWITCH_ADDR               0x3878

/* channel 3 mono switch */
#define REG_DSP1_CH3_MONO_SWITCH_ADDR               (REG_DSP1_CH2_MONO_SWITCH_ADDR+1)

/* channel 4 mono switch */
#define REG_DSP1_CH4_MONO_SWITCH_ADDR               (REG_DSP1_CH2_MONO_SWITCH_ADDR+2)

/* channel 5 mono switch */
#define REG_DSP1_CH5_MONO_SWITCH_ADDR               (REG_DSP1_CH2_MONO_SWITCH_ADDR+3)

/* channel 6 mono switch */
#define REG_DSP1_CH6_MONO_SWITCH_ADDR               (REG_DSP1_CH2_MONO_SWITCH_ADDR+4)

/* channel 7 mono switch */
#define REG_DSP1_CH7_MONO_SWITCH_ADDR               (REG_DSP1_CH2_MONO_SWITCH_ADDR+5)

/* channel 8 mono switch */
#define REG_DSP1_CH8_MONO_SWITCH_ADDR               (REG_DSP1_CH2_MONO_SWITCH_ADDR+6)

/* channel 9 mono switch */
#define REG_DSP1_CH9_MONO_SWITCH_ADDR               (REG_DSP1_CH2_MONO_SWITCH_ADDR+7)

/* channel 10 mono switch */
#define REG_DSP1_CH10_MONO_SWITCH_ADDR               (REG_DSP1_CH2_MONO_SWITCH_ADDR+8)

/* channel 11 mono switch */
#define REG_DSP1_CH11_MONO_SWITCH_ADDR               (REG_DSP1_CH2_MONO_SWITCH_ADDR+9)

/* channel 12 mono switch */
#define REG_DSP1_CH12_MONO_SWITCH_ADDR               (REG_DSP1_CH2_MONO_SWITCH_ADDR+10)

/* channel 13 mono switch */
#define REG_DSP1_CH13_MONO_SWITCH_ADDR               (REG_DSP1_CH2_MONO_SWITCH_ADDR+11)

/* channel 14 mono switch */
#define REG_DSP1_CH14_MONO_SWITCH_ADDR               (REG_DSP1_CH2_MONO_SWITCH_ADDR+12)

/* channel 15 mono switch */
#define REG_DSP1_CH15_MONO_SWITCH_ADDR               (REG_DSP1_CH2_MONO_SWITCH_ADDR+13)

/* channel 16 mono switch */
#define REG_DSP1_CH16_MONO_SWITCH_ADDR               (REG_DSP1_CH2_MONO_SWITCH_ADDR+14)

//通道mute组件寄存器定义
//通道mute组件寄存器一次读出和写入 4bytes，取值0和1

/* channel 1 mute */
#define REG_DSP1_CH1_MUTE_ADDR              0x3888

/* channel 2 mute */
#define REG_DSP1_CH2_MUTE_ADDR              (REG_DSP1_CH1_MUTE_ADDR+1)

/* channel 3 mute */
#define REG_DSP1_CH3_MUTE_ADDR              (REG_DSP1_CH1_MUTE_ADDR+2)

/* channel 4 mute */
#define REG_DSP1_CH4_MUTE_ADDR              (REG_DSP1_CH1_MUTE_ADDR+3)

/* channel 5 mute */
#define REG_DSP1_CH5_MUTE_ADDR              (REG_DSP1_CH1_MUTE_ADDR+4)

/* channel 6 mute */
#define REG_DSP1_CH6_MUTE_ADDR              (REG_DSP1_CH1_MUTE_ADDR+5)

/* channel 7 mute */
#define REG_DSP1_CH7_MUTE_ADDR              (REG_DSP1_CH1_MUTE_ADDR+6)

/* channel 8 mute */
#define REG_DSP1_CH8_MUTE_ADDR              (REG_DSP1_CH1_MUTE_ADDR+7)

/* channel 9 mute */
#define REG_DSP1_CH9_MUTE_ADDR              (REG_DSP1_CH1_MUTE_ADDR+8)

/* channel 10 mute */
#define REG_DSP1_CH10_MUTE_ADDR             (REG_DSP1_CH1_MUTE_ADDR+9)

/* channel 11 mute */
#define REG_DSP1_CH11_MUTE_ADDR             (REG_DSP1_CH1_MUTE_ADDR+10)

/* channel 12 mute */
#define REG_DSP1_CH12_MUTE_ADDR             (REG_DSP1_CH1_MUTE_ADDR+11)

/* channel 13 mute */
#define REG_DSP1_CH13_MUTE_ADDR             (REG_DSP1_CH1_MUTE_ADDR+12)

/* channel 14 mute */
#define REG_DSP1_CH14_MUTE_ADDR             (REG_DSP1_CH1_MUTE_ADDR+13)

/* channel 15 mute */
#define REG_DSP1_CH15_MUTE_ADDR             (REG_DSP1_CH1_MUTE_ADDR+14)

/* channel 16 mute */
#define REG_DSP1_CH16_MUTE_ADDR             (REG_DSP1_CH1_MUTE_ADDR+15)

//通道single组件寄存器定义
//通道single组件寄存器一次读出和写入 4bytes
/* channel 1 single */
#define REG_DSP1_CH1_SINGLE_ADDR             0x3898

/* channel 2 single */
#define REG_DSP1_CH2_SINGLE_ADDR             (REG_DSP1_CH1_SINGLE_ADDR +1)

/* channel 3 single */
#define REG_DSP1_CH3_SINGLE_ADDR             (REG_DSP1_CH1_SINGLE_ADDR +2)

/* channel 4 single */
#define REG_DSP1_CH4_SINGLE_ADDR             (REG_DSP1_CH1_SINGLE_ADDR +3)

/* channel 5 single */
#define REG_DSP1_CH5_SINGLE_ADDR             (REG_DSP1_CH1_SINGLE_ADDR +4)

/* channel 6 single */
#define REG_DSP1_CH6_SINGLE_ADDR             (REG_DSP1_CH1_SINGLE_ADDR +5)

/* channel 7 single */
#define REG_DSP1_CH7_SINGLE_ADDR             (REG_DSP1_CH1_SINGLE_ADDR +6)

/* channel 8 single */
#define REG_DSP1_CH8_SINGLE_ADDR             (REG_DSP1_CH1_SINGLE_ADDR +7)

/* channel 9 single */
#define REG_DSP1_CH9_SINGLE_ADDR             (REG_DSP1_CH1_SINGLE_ADDR +8)

/* channel 10 single */
#define REG_DSP1_CH10_SINGLE_ADDR            (REG_DSP1_CH1_SINGLE_ADDR +9)

/* channel 11 single */
#define REG_DSP1_CH11_SINGLE_ADDR            (REG_DSP1_CH1_SINGLE_ADDR +10)

/* channel 12 single */
#define REG_DSP1_CH12_SINGLE_ADDR            (REG_DSP1_CH1_SINGLE_ADDR +11)

/* channel 13 single */
#define REG_DSP1_CH13_SINGLE_ADDR            (REG_DSP1_CH1_SINGLE_ADDR +12)

/* channel 14 single */
#define REG_DSP1_CH14_SINGLE_ADDR            (REG_DSP1_CH1_SINGLE_ADDR +13)

/* channel 15 single */
#define REG_DSP1_CH15_SINGLE_ADDR            (REG_DSP1_CH1_SINGLE_ADDR +14)

/* channel 16 single */
#define REG_DSP1_CH16_SINGLE_ADDR            (REG_DSP1_CH1_SINGLE_ADDR +15)

//通道eq组件寄存器定义
//通道eq组件寄存器一次读出和写入 4bytes
/* channel_eq 1 */
#define REG_DSP1_CH1_EQ_1_1_ADDR    	    0x0200
#define REG_DSP1_CH1_EQ_1_2_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+1)
#define REG_DSP1_CH1_EQ_1_3_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+2)
#define REG_DSP1_CH1_EQ_1_4_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+3)
#define REG_DSP1_CH1_EQ_1_5_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+4)

#define REG_DSP1_CH1_EQ_2_1_ADDR    	    (REG_DSP1_CH1_EQ_1_1_ADDR+5)
#define REG_DSP1_CH1_EQ_2_2_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+6)
#define REG_DSP1_CH1_EQ_2_3_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+7)
#define REG_DSP1_CH1_EQ_2_4_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+8)
#define REG_DSP1_CH1_EQ_2_5_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+9)

#define REG_DSP1_CH1_EQ_3_1_ADDR    	    (REG_DSP1_CH1_EQ_1_1_ADDR+10)
#define REG_DSP1_CH1_EQ_3_2_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+11)
#define REG_DSP1_CH1_EQ_3_3_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+12)
#define REG_DSP1_CH1_EQ_3_4_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+13)
#define REG_DSP1_CH1_EQ_3_5_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+14)

#define REG_DSP1_CH1_EQ_4_1_ADDR    	    (REG_DSP1_CH1_EQ_1_1_ADDR+15)
#define REG_DSP1_CH1_EQ_4_2_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+16)
#define REG_DSP1_CH1_EQ_4_3_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+17)
#define REG_DSP1_CH1_EQ_4_4_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+18)
#define REG_DSP1_CH1_EQ_4_5_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+19)

#define REG_DSP1_CH1_EQ_5_1_ADDR    	    (REG_DSP1_CH1_EQ_1_1_ADDR+20)
#define REG_DSP1_CH1_EQ_5_2_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+21)
#define REG_DSP1_CH1_EQ_5_3_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+22)
#define REG_DSP1_CH1_EQ_5_4_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+23)
#define REG_DSP1_CH1_EQ_5_5_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+24)

#define REG_DSP1_CH1_EQ_6_1_ADDR    	    (REG_DSP1_CH1_EQ_1_1_ADDR+25)
#define REG_DSP1_CH1_EQ_6_2_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+26)
#define REG_DSP1_CH1_EQ_6_3_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+27)
#define REG_DSP1_CH1_EQ_6_4_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+28)
#define REG_DSP1_CH1_EQ_6_5_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+29)

#define REG_DSP1_CH1_EQ_7_1_ADDR    	    (REG_DSP1_CH1_EQ_1_1_ADDR+30)
#define REG_DSP1_CH1_EQ_7_2_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+31)
#define REG_DSP1_CH1_EQ_7_3_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+32)
#define REG_DSP1_CH1_EQ_7_4_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+33)
#define REG_DSP1_CH1_EQ_7_5_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+34)

#define REG_DSP1_CH1_EQ_8_1_ADDR    	    (REG_DSP1_CH1_EQ_1_1_ADDR+35)
#define REG_DSP1_CH1_EQ_8_2_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+36)
#define REG_DSP1_CH1_EQ_8_3_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+37)
#define REG_DSP1_CH1_EQ_8_4_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+38)
#define REG_DSP1_CH1_EQ_8_5_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+39)

#define REG_DSP1_CH1_EQ_9_1_ADDR    	    (REG_DSP1_CH1_EQ_1_1_ADDR+40)
#define REG_DSP1_CH1_EQ_9_2_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+41)
#define REG_DSP1_CH1_EQ_9_3_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+42)
#define REG_DSP1_CH1_EQ_9_4_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+43)
#define REG_DSP1_CH1_EQ_9_5_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+44)

#define REG_DSP1_CH1_EQ_10_1_ADDR    	    (REG_DSP1_CH1_EQ_1_1_ADDR+45)
#define REG_DSP1_CH1_EQ_10_2_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+46)
#define REG_DSP1_CH1_EQ_10_3_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+47)
#define REG_DSP1_CH1_EQ_10_4_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+48)
#define REG_DSP1_CH1_EQ_10_5_ADDR     		(REG_DSP1_CH1_EQ_1_1_ADDR+49)

/* channel_eq 2 */
#define REG_DSP1_CH2_EQ_1_1_ADDR    	    0x0232
#define REG_DSP1_CH2_EQ_1_2_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+1)
#define REG_DSP1_CH2_EQ_1_3_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+2)
#define REG_DSP1_CH2_EQ_1_4_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+3)
#define REG_DSP1_CH2_EQ_1_5_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+4)

#define REG_DSP1_CH2_EQ_2_1_ADDR    	    (REG_DSP1_CH2_EQ_1_1_ADDR+5)
#define REG_DSP1_CH2_EQ_2_2_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+6)
#define REG_DSP1_CH2_EQ_2_3_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+7)
#define REG_DSP1_CH2_EQ_2_4_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+8)
#define REG_DSP1_CH2_EQ_2_5_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+9)

#define REG_DSP1_CH2_EQ_3_1_ADDR    	    (REG_DSP1_CH2_EQ_1_1_ADDR+10)
#define REG_DSP1_CH2_EQ_3_2_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+11)
#define REG_DSP1_CH2_EQ_3_3_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+12)
#define REG_DSP1_CH2_EQ_3_4_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+13)
#define REG_DSP1_CH2_EQ_3_5_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+14)

#define REG_DSP1_CH2_EQ_4_1_ADDR    	    (REG_DSP1_CH2_EQ_1_1_ADDR+15)
#define REG_DSP1_CH2_EQ_4_2_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+16)
#define REG_DSP1_CH2_EQ_4_3_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+17)
#define REG_DSP1_CH2_EQ_4_4_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+18)
#define REG_DSP1_CH2_EQ_4_5_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+19)

#define REG_DSP1_CH2_EQ_5_1_ADDR    	    (REG_DSP1_CH2_EQ_1_1_ADDR+20)
#define REG_DSP1_CH2_EQ_5_2_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+21)
#define REG_DSP1_CH2_EQ_5_3_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+22)
#define REG_DSP1_CH2_EQ_5_4_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+23)
#define REG_DSP1_CH2_EQ_5_5_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+24)

#define REG_DSP1_CH2_EQ_6_1_ADDR    	    (REG_DSP1_CH2_EQ_1_1_ADDR+25)
#define REG_DSP1_CH2_EQ_6_2_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+26)
#define REG_DSP1_CH2_EQ_6_3_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+27)
#define REG_DSP1_CH2_EQ_6_4_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+28)
#define REG_DSP1_CH2_EQ_6_5_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+29)

#define REG_DSP1_CH2_EQ_7_1_ADDR    	    (REG_DSP1_CH2_EQ_1_1_ADDR+30)
#define REG_DSP1_CH2_EQ_7_2_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+31)
#define REG_DSP1_CH2_EQ_7_3_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+32)
#define REG_DSP1_CH2_EQ_7_4_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+33)
#define REG_DSP1_CH2_EQ_7_5_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+34)

#define REG_DSP1_CH2_EQ_8_1_ADDR    	    (REG_DSP1_CH2_EQ_1_1_ADDR+35)
#define REG_DSP1_CH2_EQ_8_2_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+36)
#define REG_DSP1_CH2_EQ_8_3_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+37)
#define REG_DSP1_CH2_EQ_8_4_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+38)
#define REG_DSP1_CH2_EQ_8_5_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+39)

#define REG_DSP1_CH2_EQ_9_1_ADDR    	    (REG_DSP1_CH2_EQ_1_1_ADDR+40)
#define REG_DSP1_CH2_EQ_9_2_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+41)
#define REG_DSP1_CH2_EQ_9_3_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+42)
#define REG_DSP1_CH2_EQ_9_4_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+43)
#define REG_DSP1_CH2_EQ_9_5_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+44)

#define REG_DSP1_CH2_EQ_10_1_ADDR    	    (REG_DSP1_CH2_EQ_1_1_ADDR+45)
#define REG_DSP1_CH2_EQ_10_2_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+46)
#define REG_DSP1_CH2_EQ_10_3_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+47)
#define REG_DSP1_CH2_EQ_10_4_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+48)
#define REG_DSP1_CH2_EQ_10_5_ADDR     		(REG_DSP1_CH2_EQ_1_1_ADDR+49)

/* channel_eq 3 */
#define REG_DSP1_CH3_EQ_1_1_ADDR    	    0x0264
#define REG_DSP1_CH3_EQ_1_2_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+1)
#define REG_DSP1_CH3_EQ_1_3_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+2)
#define REG_DSP1_CH3_EQ_1_4_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+3)
#define REG_DSP1_CH3_EQ_1_5_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+4)

#define REG_DSP1_CH3_EQ_2_1_ADDR    	    (REG_DSP1_CH3_EQ_1_1_ADDR+5)
#define REG_DSP1_CH3_EQ_2_2_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+6)
#define REG_DSP1_CH3_EQ_2_3_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+7)
#define REG_DSP1_CH3_EQ_2_4_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+8)
#define REG_DSP1_CH3_EQ_2_5_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+9)

#define REG_DSP1_CH3_EQ_3_1_ADDR    	    (REG_DSP1_CH3_EQ_1_1_ADDR+10)
#define REG_DSP1_CH3_EQ_3_2_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+11)
#define REG_DSP1_CH3_EQ_3_3_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+12)
#define REG_DSP1_CH3_EQ_3_4_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+13)
#define REG_DSP1_CH3_EQ_3_5_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+14)

#define REG_DSP1_CH3_EQ_4_1_ADDR    	    (REG_DSP1_CH3_EQ_1_1_ADDR+15)
#define REG_DSP1_CH3_EQ_4_2_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+16)
#define REG_DSP1_CH3_EQ_4_3_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+17)
#define REG_DSP1_CH3_EQ_4_4_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+18)
#define REG_DSP1_CH3_EQ_4_5_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+19)

#define REG_DSP1_CH3_EQ_5_1_ADDR    	    (REG_DSP1_CH3_EQ_1_1_ADDR+20)
#define REG_DSP1_CH3_EQ_5_2_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+21)
#define REG_DSP1_CH3_EQ_5_3_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+22)
#define REG_DSP1_CH3_EQ_5_4_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+23)
#define REG_DSP1_CH3_EQ_5_5_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+24)

#define REG_DSP1_CH3_EQ_6_1_ADDR    	    (REG_DSP1_CH3_EQ_1_1_ADDR+25)
#define REG_DSP1_CH3_EQ_6_2_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+26)
#define REG_DSP1_CH3_EQ_6_3_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+27)
#define REG_DSP1_CH3_EQ_6_4_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+28)
#define REG_DSP1_CH3_EQ_6_5_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+29)

#define REG_DSP1_CH3_EQ_7_1_ADDR    	    (REG_DSP1_CH3_EQ_1_1_ADDR+30)
#define REG_DSP1_CH3_EQ_7_2_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+31)
#define REG_DSP1_CH3_EQ_7_3_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+32)
#define REG_DSP1_CH3_EQ_7_4_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+33)
#define REG_DSP1_CH3_EQ_7_5_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+34)

#define REG_DSP1_CH3_EQ_8_1_ADDR    	    (REG_DSP1_CH3_EQ_1_1_ADDR+35)
#define REG_DSP1_CH3_EQ_8_2_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+36)
#define REG_DSP1_CH3_EQ_8_3_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+37)
#define REG_DSP1_CH3_EQ_8_4_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+38)
#define REG_DSP1_CH3_EQ_8_5_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+39)

#define REG_DSP1_CH3_EQ_9_1_ADDR    	    (REG_DSP1_CH3_EQ_1_1_ADDR+40)
#define REG_DSP1_CH3_EQ_9_2_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+41)
#define REG_DSP1_CH3_EQ_9_3_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+42)
#define REG_DSP1_CH3_EQ_9_4_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+43)
#define REG_DSP1_CH3_EQ_9_5_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+44)

#define REG_DSP1_CH3_EQ_10_1_ADDR    	    (REG_DSP1_CH3_EQ_1_1_ADDR+45)
#define REG_DSP1_CH3_EQ_10_2_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+46)
#define REG_DSP1_CH3_EQ_10_3_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+47)
#define REG_DSP1_CH3_EQ_10_4_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+48)
#define REG_DSP1_CH3_EQ_10_5_ADDR     		(REG_DSP1_CH3_EQ_1_1_ADDR+49)

/* channel_eq 4 */
#define REG_DSP1_CH4_EQ_1_1_ADDR    	    0x0296
#define REG_DSP1_CH4_EQ_1_2_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+1)
#define REG_DSP1_CH4_EQ_1_3_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+2)
#define REG_DSP1_CH4_EQ_1_4_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+3)
#define REG_DSP1_CH4_EQ_1_5_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+4)

#define REG_DSP1_CH4_EQ_2_1_ADDR    	    (REG_DSP1_CH4_EQ_1_1_ADDR+5)
#define REG_DSP1_CH4_EQ_2_2_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+6)
#define REG_DSP1_CH4_EQ_2_3_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+7)
#define REG_DSP1_CH4_EQ_2_4_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+8)
#define REG_DSP1_CH4_EQ_2_5_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+9)

#define REG_DSP1_CH4_EQ_3_1_ADDR    	    (REG_DSP1_CH4_EQ_1_1_ADDR+10)
#define REG_DSP1_CH4_EQ_3_2_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+11)
#define REG_DSP1_CH4_EQ_3_3_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+12)
#define REG_DSP1_CH4_EQ_3_4_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+13)
#define REG_DSP1_CH4_EQ_3_5_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+14)

#define REG_DSP1_CH4_EQ_4_1_ADDR    	    (REG_DSP1_CH4_EQ_1_1_ADDR+15)
#define REG_DSP1_CH4_EQ_4_2_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+16)
#define REG_DSP1_CH4_EQ_4_3_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+17)
#define REG_DSP1_CH4_EQ_4_4_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+18)
#define REG_DSP1_CH4_EQ_4_5_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+19)

#define REG_DSP1_CH4_EQ_5_1_ADDR    	    (REG_DSP1_CH4_EQ_1_1_ADDR+20)
#define REG_DSP1_CH4_EQ_5_2_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+21)
#define REG_DSP1_CH4_EQ_5_3_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+22)
#define REG_DSP1_CH4_EQ_5_4_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+23)
#define REG_DSP1_CH4_EQ_5_5_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+24)

#define REG_DSP1_CH4_EQ_6_1_ADDR    	    (REG_DSP1_CH4_EQ_1_1_ADDR+25)
#define REG_DSP1_CH4_EQ_6_2_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+26)
#define REG_DSP1_CH4_EQ_6_3_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+27)
#define REG_DSP1_CH4_EQ_6_4_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+28)
#define REG_DSP1_CH4_EQ_6_5_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+29)

#define REG_DSP1_CH4_EQ_7_1_ADDR    	    (REG_DSP1_CH4_EQ_1_1_ADDR+30)
#define REG_DSP1_CH4_EQ_7_2_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+31)
#define REG_DSP1_CH4_EQ_7_3_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+32)
#define REG_DSP1_CH4_EQ_7_4_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+33)
#define REG_DSP1_CH4_EQ_7_5_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+34)

#define REG_DSP1_CH4_EQ_8_1_ADDR    	    (REG_DSP1_CH4_EQ_1_1_ADDR+35)
#define REG_DSP1_CH4_EQ_8_2_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+36)
#define REG_DSP1_CH4_EQ_8_3_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+37)
#define REG_DSP1_CH4_EQ_8_4_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+38)
#define REG_DSP1_CH4_EQ_8_5_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+39)

#define REG_DSP1_CH4_EQ_9_1_ADDR    	    (REG_DSP1_CH4_EQ_1_1_ADDR+40)
#define REG_DSP1_CH4_EQ_9_2_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+41)
#define REG_DSP1_CH4_EQ_9_3_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+42)
#define REG_DSP1_CH4_EQ_9_4_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+43)
#define REG_DSP1_CH4_EQ_9_5_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+44)

#define REG_DSP1_CH4_EQ_10_1_ADDR    	    (REG_DSP1_CH4_EQ_1_1_ADDR+45)
#define REG_DSP1_CH4_EQ_10_2_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+46)
#define REG_DSP1_CH4_EQ_10_3_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+47)
#define REG_DSP1_CH4_EQ_10_4_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+48)
#define REG_DSP1_CH4_EQ_10_5_ADDR     		(REG_DSP1_CH4_EQ_1_1_ADDR+49)

/* channel_eq 5 */
#define REG_DSP1_CH5_EQ_1_1_ADDR    	    0x02C8
#define REG_DSP1_CH5_EQ_1_2_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+1)
#define REG_DSP1_CH5_EQ_1_3_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+2)
#define REG_DSP1_CH5_EQ_1_4_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+3)
#define REG_DSP1_CH5_EQ_1_5_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+4)

#define REG_DSP1_CH5_EQ_2_1_ADDR    	    (REG_DSP1_CH5_EQ_1_1_ADDR+5)
#define REG_DSP1_CH5_EQ_2_2_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+6)
#define REG_DSP1_CH5_EQ_2_3_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+7)
#define REG_DSP1_CH5_EQ_2_4_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+8)
#define REG_DSP1_CH5_EQ_2_5_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+9)

#define REG_DSP1_CH5_EQ_3_1_ADDR    	    (REG_DSP1_CH5_EQ_1_1_ADDR+10)
#define REG_DSP1_CH5_EQ_3_2_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+11)
#define REG_DSP1_CH5_EQ_3_3_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+12)
#define REG_DSP1_CH5_EQ_3_4_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+13)
#define REG_DSP1_CH5_EQ_3_5_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+14)

#define REG_DSP1_CH5_EQ_4_1_ADDR    	    (REG_DSP1_CH5_EQ_1_1_ADDR+15)
#define REG_DSP1_CH5_EQ_4_2_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+16)
#define REG_DSP1_CH5_EQ_4_3_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+17)
#define REG_DSP1_CH5_EQ_4_4_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+18)
#define REG_DSP1_CH5_EQ_4_5_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+19)

#define REG_DSP1_CH5_EQ_5_1_ADDR    	    (REG_DSP1_CH5_EQ_1_1_ADDR+20)
#define REG_DSP1_CH5_EQ_5_2_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+21)
#define REG_DSP1_CH5_EQ_5_3_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+22)
#define REG_DSP1_CH5_EQ_5_4_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+23)
#define REG_DSP1_CH5_EQ_5_5_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+24)

#define REG_DSP1_CH5_EQ_6_1_ADDR    	    (REG_DSP1_CH5_EQ_1_1_ADDR+25)
#define REG_DSP1_CH5_EQ_6_2_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+26)
#define REG_DSP1_CH5_EQ_6_3_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+27)
#define REG_DSP1_CH5_EQ_6_4_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+28)
#define REG_DSP1_CH5_EQ_6_5_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+29)

#define REG_DSP1_CH5_EQ_7_1_ADDR    	    (REG_DSP1_CH5_EQ_1_1_ADDR+30)
#define REG_DSP1_CH5_EQ_7_2_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+31)
#define REG_DSP1_CH5_EQ_7_3_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+32)
#define REG_DSP1_CH5_EQ_7_4_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+33)
#define REG_DSP1_CH5_EQ_7_5_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+34)

#define REG_DSP1_CH5_EQ_8_1_ADDR    	    (REG_DSP1_CH5_EQ_1_1_ADDR+35)
#define REG_DSP1_CH5_EQ_8_2_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+36)
#define REG_DSP1_CH5_EQ_8_3_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+37)
#define REG_DSP1_CH5_EQ_8_4_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+38)
#define REG_DSP1_CH5_EQ_8_5_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+39)

#define REG_DSP1_CH5_EQ_9_1_ADDR    	    (REG_DSP1_CH5_EQ_1_1_ADDR+40)
#define REG_DSP1_CH5_EQ_9_2_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+41)
#define REG_DSP1_CH5_EQ_9_3_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+42)
#define REG_DSP1_CH5_EQ_9_4_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+43)
#define REG_DSP1_CH5_EQ_9_5_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+44)

#define REG_DSP1_CH5_EQ_10_1_ADDR    	    (REG_DSP1_CH5_EQ_1_1_ADDR+45)
#define REG_DSP1_CH5_EQ_10_2_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+46)
#define REG_DSP1_CH5_EQ_10_3_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+47)
#define REG_DSP1_CH5_EQ_10_4_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+48)
#define REG_DSP1_CH5_EQ_10_5_ADDR     		(REG_DSP1_CH5_EQ_1_1_ADDR+49)

/* channel_eq 6 */
#define REG_DSP1_CH6_EQ_1_1_ADDR    	    0x02FA
#define REG_DSP1_CH6_EQ_1_2_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+1)
#define REG_DSP1_CH6_EQ_1_3_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+2)
#define REG_DSP1_CH6_EQ_1_4_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+3)
#define REG_DSP1_CH6_EQ_1_5_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+4)

#define REG_DSP1_CH6_EQ_2_1_ADDR    	    (REG_DSP1_CH6_EQ_1_1_ADDR+5)
#define REG_DSP1_CH6_EQ_2_2_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+6)
#define REG_DSP1_CH6_EQ_2_3_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+7)
#define REG_DSP1_CH6_EQ_2_4_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+8)
#define REG_DSP1_CH6_EQ_2_5_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+9)

#define REG_DSP1_CH6_EQ_3_1_ADDR    	    (REG_DSP1_CH6_EQ_1_1_ADDR+10)
#define REG_DSP1_CH6_EQ_3_2_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+11)
#define REG_DSP1_CH6_EQ_3_3_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+12)
#define REG_DSP1_CH6_EQ_3_4_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+13)
#define REG_DSP1_CH6_EQ_3_5_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+14)

#define REG_DSP1_CH6_EQ_4_1_ADDR    	    (REG_DSP1_CH6_EQ_1_1_ADDR+15)
#define REG_DSP1_CH6_EQ_4_2_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+16)
#define REG_DSP1_CH6_EQ_4_3_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+17)
#define REG_DSP1_CH6_EQ_4_4_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+18)
#define REG_DSP1_CH6_EQ_4_5_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+19)

#define REG_DSP1_CH6_EQ_5_1_ADDR    	    (REG_DSP1_CH6_EQ_1_1_ADDR+20)
#define REG_DSP1_CH6_EQ_5_2_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+21)
#define REG_DSP1_CH6_EQ_5_3_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+22)
#define REG_DSP1_CH6_EQ_5_4_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+23)
#define REG_DSP1_CH6_EQ_5_5_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+24)

#define REG_DSP1_CH6_EQ_6_1_ADDR    	    (REG_DSP1_CH6_EQ_1_1_ADDR+25)
#define REG_DSP1_CH6_EQ_6_2_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+26)
#define REG_DSP1_CH6_EQ_6_3_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+27)
#define REG_DSP1_CH6_EQ_6_4_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+28)
#define REG_DSP1_CH6_EQ_6_5_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+29)

#define REG_DSP1_CH6_EQ_7_1_ADDR    	    (REG_DSP1_CH6_EQ_1_1_ADDR+30)
#define REG_DSP1_CH6_EQ_7_2_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+31)
#define REG_DSP1_CH6_EQ_7_3_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+32)
#define REG_DSP1_CH6_EQ_7_4_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+33)
#define REG_DSP1_CH6_EQ_7_5_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+34)

#define REG_DSP1_CH6_EQ_8_1_ADDR    	    (REG_DSP1_CH6_EQ_1_1_ADDR+35)
#define REG_DSP1_CH6_EQ_8_2_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+36)
#define REG_DSP1_CH6_EQ_8_3_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+37)
#define REG_DSP1_CH6_EQ_8_4_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+38)
#define REG_DSP1_CH6_EQ_8_5_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+39)

#define REG_DSP1_CH6_EQ_9_1_ADDR    	    (REG_DSP1_CH6_EQ_1_1_ADDR+40)
#define REG_DSP1_CH6_EQ_9_2_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+41)
#define REG_DSP1_CH6_EQ_9_3_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+42)
#define REG_DSP1_CH6_EQ_9_4_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+43)
#define REG_DSP1_CH6_EQ_9_5_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+44)

#define REG_DSP1_CH6_EQ_10_1_ADDR    	    (REG_DSP1_CH6_EQ_1_1_ADDR+45)
#define REG_DSP1_CH6_EQ_10_2_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+46)
#define REG_DSP1_CH6_EQ_10_3_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+47)
#define REG_DSP1_CH6_EQ_10_4_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+48)
#define REG_DSP1_CH6_EQ_10_5_ADDR     		(REG_DSP1_CH6_EQ_1_1_ADDR+49)

/* channel_eq 7 */
#define REG_DSP1_CH7_EQ_1_1_ADDR    	    0x032C
#define REG_DSP1_CH7_EQ_1_2_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+1)
#define REG_DSP1_CH7_EQ_1_3_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+2)
#define REG_DSP1_CH7_EQ_1_4_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+3)
#define REG_DSP1_CH7_EQ_1_5_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+4)

#define REG_DSP1_CH7_EQ_2_1_ADDR    	    (REG_DSP1_CH7_EQ_1_1_ADDR+5)
#define REG_DSP1_CH7_EQ_2_2_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+6)
#define REG_DSP1_CH7_EQ_2_3_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+7)
#define REG_DSP1_CH7_EQ_2_4_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+8)
#define REG_DSP1_CH7_EQ_2_5_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+9)

#define REG_DSP1_CH7_EQ_3_1_ADDR    	    (REG_DSP1_CH7_EQ_1_1_ADDR+10)
#define REG_DSP1_CH7_EQ_3_2_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+11)
#define REG_DSP1_CH7_EQ_3_3_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+12)
#define REG_DSP1_CH7_EQ_3_4_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+13)
#define REG_DSP1_CH7_EQ_3_5_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+14)

#define REG_DSP1_CH7_EQ_4_1_ADDR    	    (REG_DSP1_CH7_EQ_1_1_ADDR+15)
#define REG_DSP1_CH7_EQ_4_2_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+16)
#define REG_DSP1_CH7_EQ_4_3_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+17)
#define REG_DSP1_CH7_EQ_4_4_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+18)
#define REG_DSP1_CH7_EQ_4_5_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+19)

#define REG_DSP1_CH7_EQ_5_1_ADDR    	    (REG_DSP1_CH7_EQ_1_1_ADDR+20)
#define REG_DSP1_CH7_EQ_5_2_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+21)
#define REG_DSP1_CH7_EQ_5_3_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+22)
#define REG_DSP1_CH7_EQ_5_4_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+23)
#define REG_DSP1_CH7_EQ_5_5_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+24)

#define REG_DSP1_CH7_EQ_6_1_ADDR    	    (REG_DSP1_CH7_EQ_1_1_ADDR+25)
#define REG_DSP1_CH7_EQ_6_2_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+26)
#define REG_DSP1_CH7_EQ_6_3_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+27)
#define REG_DSP1_CH7_EQ_6_4_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+28)
#define REG_DSP1_CH7_EQ_6_5_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+29)

#define REG_DSP1_CH7_EQ_7_1_ADDR    	    (REG_DSP1_CH7_EQ_1_1_ADDR+30)
#define REG_DSP1_CH7_EQ_7_2_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+31)
#define REG_DSP1_CH7_EQ_7_3_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+32)
#define REG_DSP1_CH7_EQ_7_4_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+33)
#define REG_DSP1_CH7_EQ_7_5_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+34)

#define REG_DSP1_CH7_EQ_8_1_ADDR    	    (REG_DSP1_CH7_EQ_1_1_ADDR+35)
#define REG_DSP1_CH7_EQ_8_2_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+36)
#define REG_DSP1_CH7_EQ_8_3_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+37)
#define REG_DSP1_CH7_EQ_8_4_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+38)
#define REG_DSP1_CH7_EQ_8_5_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+39)

#define REG_DSP1_CH7_EQ_9_1_ADDR    	    (REG_DSP1_CH7_EQ_1_1_ADDR+40)
#define REG_DSP1_CH7_EQ_9_2_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+41)
#define REG_DSP1_CH7_EQ_9_3_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+42)
#define REG_DSP1_CH7_EQ_9_4_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+43)
#define REG_DSP1_CH7_EQ_9_5_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+44)

#define REG_DSP1_CH7_EQ_10_1_ADDR    	    (REG_DSP1_CH7_EQ_1_1_ADDR+45)
#define REG_DSP1_CH7_EQ_10_2_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+46)
#define REG_DSP1_CH7_EQ_10_3_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+47)
#define REG_DSP1_CH7_EQ_10_4_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+48)
#define REG_DSP1_CH7_EQ_10_5_ADDR     		(REG_DSP1_CH7_EQ_1_1_ADDR+49)

/* channel_eq 8 */
#define REG_DSP1_CH8_EQ_1_1_ADDR    	    0x035E
#define REG_DSP1_CH8_EQ_1_2_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+1)
#define REG_DSP1_CH8_EQ_1_3_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+2)
#define REG_DSP1_CH8_EQ_1_4_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+3)
#define REG_DSP1_CH8_EQ_1_5_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+4)

#define REG_DSP1_CH8_EQ_2_1_ADDR    	    (REG_DSP1_CH8_EQ_1_1_ADDR+5)
#define REG_DSP1_CH8_EQ_2_2_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+6)
#define REG_DSP1_CH8_EQ_2_3_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+7)
#define REG_DSP1_CH8_EQ_2_4_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+8)
#define REG_DSP1_CH8_EQ_2_5_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+9)

#define REG_DSP1_CH8_EQ_3_1_ADDR    	    (REG_DSP1_CH8_EQ_1_1_ADDR+10)
#define REG_DSP1_CH8_EQ_3_2_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+11)
#define REG_DSP1_CH8_EQ_3_3_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+12)
#define REG_DSP1_CH8_EQ_3_4_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+13)
#define REG_DSP1_CH8_EQ_3_5_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+14)

#define REG_DSP1_CH8_EQ_4_1_ADDR    	    (REG_DSP1_CH8_EQ_1_1_ADDR+15)
#define REG_DSP1_CH8_EQ_4_2_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+16)
#define REG_DSP1_CH8_EQ_4_3_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+17)
#define REG_DSP1_CH8_EQ_4_4_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+18)
#define REG_DSP1_CH8_EQ_4_5_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+19)

#define REG_DSP1_CH8_EQ_5_1_ADDR    	    (REG_DSP1_CH8_EQ_1_1_ADDR+20)
#define REG_DSP1_CH8_EQ_5_2_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+21)
#define REG_DSP1_CH8_EQ_5_3_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+22)
#define REG_DSP1_CH8_EQ_5_4_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+23)
#define REG_DSP1_CH8_EQ_5_5_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+24)

#define REG_DSP1_CH8_EQ_6_1_ADDR    	    (REG_DSP1_CH8_EQ_1_1_ADDR+25)
#define REG_DSP1_CH8_EQ_6_2_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+26)
#define REG_DSP1_CH8_EQ_6_3_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+27)
#define REG_DSP1_CH8_EQ_6_4_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+28)
#define REG_DSP1_CH8_EQ_6_5_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+29)

#define REG_DSP1_CH8_EQ_7_1_ADDR    	    (REG_DSP1_CH8_EQ_1_1_ADDR+30)
#define REG_DSP1_CH8_EQ_7_2_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+31)
#define REG_DSP1_CH8_EQ_7_3_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+32)
#define REG_DSP1_CH8_EQ_7_4_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+33)
#define REG_DSP1_CH8_EQ_7_5_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+34)

#define REG_DSP1_CH8_EQ_8_1_ADDR    	    (REG_DSP1_CH8_EQ_1_1_ADDR+35)
#define REG_DSP1_CH8_EQ_8_2_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+36)
#define REG_DSP1_CH8_EQ_8_3_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+37)
#define REG_DSP1_CH8_EQ_8_4_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+38)
#define REG_DSP1_CH8_EQ_8_5_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+39)

#define REG_DSP1_CH8_EQ_9_1_ADDR    	    (REG_DSP1_CH8_EQ_1_1_ADDR+40)
#define REG_DSP1_CH8_EQ_9_2_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+41)
#define REG_DSP1_CH8_EQ_9_3_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+42)
#define REG_DSP1_CH8_EQ_9_4_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+43)
#define REG_DSP1_CH8_EQ_9_5_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+44)

#define REG_DSP1_CH8_EQ_10_1_ADDR    	    (REG_DSP1_CH8_EQ_1_1_ADDR+45)
#define REG_DSP1_CH8_EQ_10_2_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+46)
#define REG_DSP1_CH8_EQ_10_3_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+47)
#define REG_DSP1_CH8_EQ_10_4_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+48)
#define REG_DSP1_CH8_EQ_10_5_ADDR     		(REG_DSP1_CH8_EQ_1_1_ADDR+49)

/* channel_eq 9 */
#define REG_DSP1_CH9_EQ_1_1_ADDR    	    0x0390
#define REG_DSP1_CH9_EQ_1_2_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+1)
#define REG_DSP1_CH9_EQ_1_3_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+2)
#define REG_DSP1_CH9_EQ_1_4_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+3)
#define REG_DSP1_CH9_EQ_1_5_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+4)

#define REG_DSP1_CH9_EQ_2_1_ADDR    	    (REG_DSP1_CH9_EQ_1_1_ADDR+5)
#define REG_DSP1_CH9_EQ_2_2_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+6)
#define REG_DSP1_CH9_EQ_2_3_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+7)
#define REG_DSP1_CH9_EQ_2_4_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+8)
#define REG_DSP1_CH9_EQ_2_5_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+9)

#define REG_DSP1_CH9_EQ_3_1_ADDR    	    (REG_DSP1_CH9_EQ_1_1_ADDR+10)
#define REG_DSP1_CH9_EQ_3_2_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+11)
#define REG_DSP1_CH9_EQ_3_3_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+12)
#define REG_DSP1_CH9_EQ_3_4_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+13)
#define REG_DSP1_CH9_EQ_3_5_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+14)

#define REG_DSP1_CH9_EQ_4_1_ADDR    	    (REG_DSP1_CH9_EQ_1_1_ADDR+15)
#define REG_DSP1_CH9_EQ_4_2_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+16)
#define REG_DSP1_CH9_EQ_4_3_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+17)
#define REG_DSP1_CH9_EQ_4_4_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+18)
#define REG_DSP1_CH9_EQ_4_5_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+19)

#define REG_DSP1_CH9_EQ_5_1_ADDR    	    (REG_DSP1_CH9_EQ_1_1_ADDR+20)
#define REG_DSP1_CH9_EQ_5_2_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+21)
#define REG_DSP1_CH9_EQ_5_3_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+22)
#define REG_DSP1_CH9_EQ_5_4_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+23)
#define REG_DSP1_CH9_EQ_5_5_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+24)

#define REG_DSP1_CH9_EQ_6_1_ADDR    	    (REG_DSP1_CH9_EQ_1_1_ADDR+25)
#define REG_DSP1_CH9_EQ_6_2_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+26)
#define REG_DSP1_CH9_EQ_6_3_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+27)
#define REG_DSP1_CH9_EQ_6_4_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+28)
#define REG_DSP1_CH9_EQ_6_5_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+29)

#define REG_DSP1_CH9_EQ_7_1_ADDR    	    (REG_DSP1_CH9_EQ_1_1_ADDR+30)
#define REG_DSP1_CH9_EQ_7_2_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+31)
#define REG_DSP1_CH9_EQ_7_3_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+32)
#define REG_DSP1_CH9_EQ_7_4_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+33)
#define REG_DSP1_CH9_EQ_7_5_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+34)

#define REG_DSP1_CH9_EQ_8_1_ADDR    	    (REG_DSP1_CH9_EQ_1_1_ADDR+35)
#define REG_DSP1_CH9_EQ_8_2_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+36)
#define REG_DSP1_CH9_EQ_8_3_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+37)
#define REG_DSP1_CH9_EQ_8_4_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+38)
#define REG_DSP1_CH9_EQ_8_5_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+39)

#define REG_DSP1_CH9_EQ_9_1_ADDR    	    (REG_DSP1_CH9_EQ_1_1_ADDR+40)
#define REG_DSP1_CH9_EQ_9_2_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+41)
#define REG_DSP1_CH9_EQ_9_3_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+42)
#define REG_DSP1_CH9_EQ_9_4_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+43)
#define REG_DSP1_CH9_EQ_9_5_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+44)

#define REG_DSP1_CH9_EQ_10_1_ADDR    	    (REG_DSP1_CH9_EQ_1_1_ADDR+45)
#define REG_DSP1_CH9_EQ_10_2_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+46)
#define REG_DSP1_CH9_EQ_10_3_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+47)
#define REG_DSP1_CH9_EQ_10_4_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+48)
#define REG_DSP1_CH9_EQ_10_5_ADDR     		(REG_DSP1_CH9_EQ_1_1_ADDR+49)

/* channel_eq 10 */
#define REG_DSP1_CH10_EQ_1_1_ADDR    	    0x03C2
#define REG_DSP1_CH10_EQ_1_2_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+1)
#define REG_DSP1_CH10_EQ_1_3_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+2)
#define REG_DSP1_CH10_EQ_1_4_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+3)
#define REG_DSP1_CH10_EQ_1_5_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+4)

#define REG_DSP1_CH10_EQ_2_1_ADDR    	    (REG_DSP1_CH10_EQ_1_1_ADDR+5)
#define REG_DSP1_CH10_EQ_2_2_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+6)
#define REG_DSP1_CH10_EQ_2_3_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+7)
#define REG_DSP1_CH10_EQ_2_4_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+8)
#define REG_DSP1_CH10_EQ_2_5_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+9)

#define REG_DSP1_CH10_EQ_3_1_ADDR    	    (REG_DSP1_CH10_EQ_1_1_ADDR+10)
#define REG_DSP1_CH10_EQ_3_2_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+11)
#define REG_DSP1_CH10_EQ_3_3_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+12)
#define REG_DSP1_CH10_EQ_3_4_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+13)
#define REG_DSP1_CH10_EQ_3_5_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+14)

#define REG_DSP1_CH10_EQ_4_1_ADDR    	    (REG_DSP1_CH10_EQ_1_1_ADDR+15)
#define REG_DSP1_CH10_EQ_4_2_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+16)
#define REG_DSP1_CH10_EQ_4_3_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+17)
#define REG_DSP1_CH10_EQ_4_4_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+18)
#define REG_DSP1_CH10_EQ_4_5_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+19)

#define REG_DSP1_CH10_EQ_5_1_ADDR    	    (REG_DSP1_CH10_EQ_1_1_ADDR+20)
#define REG_DSP1_CH10_EQ_5_2_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+21)
#define REG_DSP1_CH10_EQ_5_3_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+22)
#define REG_DSP1_CH10_EQ_5_4_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+23)
#define REG_DSP1_CH10_EQ_5_5_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+24)

#define REG_DSP1_CH10_EQ_6_1_ADDR    	    (REG_DSP1_CH10_EQ_1_1_ADDR+25)
#define REG_DSP1_CH10_EQ_6_2_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+26)
#define REG_DSP1_CH10_EQ_6_3_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+27)
#define REG_DSP1_CH10_EQ_6_4_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+28)
#define REG_DSP1_CH10_EQ_6_5_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+29)

#define REG_DSP1_CH10_EQ_7_1_ADDR    	    (REG_DSP1_CH10_EQ_1_1_ADDR+30)
#define REG_DSP1_CH10_EQ_7_2_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+31)
#define REG_DSP1_CH10_EQ_7_3_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+32)
#define REG_DSP1_CH10_EQ_7_4_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+33)
#define REG_DSP1_CH10_EQ_7_5_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+34)

#define REG_DSP1_CH10_EQ_8_1_ADDR    	    (REG_DSP1_CH10_EQ_1_1_ADDR+35)
#define REG_DSP1_CH10_EQ_8_2_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+36)
#define REG_DSP1_CH10_EQ_8_3_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+37)
#define REG_DSP1_CH10_EQ_8_4_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+38)
#define REG_DSP1_CH10_EQ_8_5_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+39)

#define REG_DSP1_CH10_EQ_9_1_ADDR    	    (REG_DSP1_CH10_EQ_1_1_ADDR+40)
#define REG_DSP1_CH10_EQ_9_2_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+41)
#define REG_DSP1_CH10_EQ_9_3_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+42)
#define REG_DSP1_CH10_EQ_9_4_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+43)
#define REG_DSP1_CH10_EQ_9_5_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+44)

#define REG_DSP1_CH10_EQ_10_1_ADDR    	    (REG_DSP1_CH10_EQ_1_1_ADDR+45)
#define REG_DSP1_CH10_EQ_10_2_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+46)
#define REG_DSP1_CH10_EQ_10_3_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+47)
#define REG_DSP1_CH10_EQ_10_4_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+48)
#define REG_DSP1_CH10_EQ_10_5_ADDR     		(REG_DSP1_CH10_EQ_1_1_ADDR+49)

/* channel_eq 11 */
#define REG_DSP1_CH11_EQ_1_1_ADDR    	    0x03F4
#define REG_DSP1_CH11_EQ_1_2_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+1)
#define REG_DSP1_CH11_EQ_1_3_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+2)
#define REG_DSP1_CH11_EQ_1_4_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+3)
#define REG_DSP1_CH11_EQ_1_5_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+4)

#define REG_DSP1_CH11_EQ_2_1_ADDR    	    (REG_DSP1_CH11_EQ_1_1_ADDR+5)
#define REG_DSP1_CH11_EQ_2_2_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+6)
#define REG_DSP1_CH11_EQ_2_3_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+7)
#define REG_DSP1_CH11_EQ_2_4_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+8)
#define REG_DSP1_CH11_EQ_2_5_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+9)

#define REG_DSP1_CH11_EQ_3_1_ADDR    	    (REG_DSP1_CH11_EQ_1_1_ADDR+10)
#define REG_DSP1_CH11_EQ_3_2_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+11)
#define REG_DSP1_CH11_EQ_3_3_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+12)
#define REG_DSP1_CH11_EQ_3_4_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+13)
#define REG_DSP1_CH11_EQ_3_5_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+14)

#define REG_DSP1_CH11_EQ_4_1_ADDR    	    (REG_DSP1_CH11_EQ_1_1_ADDR+15)
#define REG_DSP1_CH11_EQ_4_2_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+16)
#define REG_DSP1_CH11_EQ_4_3_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+17)
#define REG_DSP1_CH11_EQ_4_4_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+18)
#define REG_DSP1_CH11_EQ_4_5_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+19)

#define REG_DSP1_CH11_EQ_5_1_ADDR    	    (REG_DSP1_CH11_EQ_1_1_ADDR+20)
#define REG_DSP1_CH11_EQ_5_2_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+21)
#define REG_DSP1_CH11_EQ_5_3_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+22)
#define REG_DSP1_CH11_EQ_5_4_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+23)
#define REG_DSP1_CH11_EQ_5_5_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+24)

#define REG_DSP1_CH11_EQ_6_1_ADDR    	    (REG_DSP1_CH11_EQ_1_1_ADDR+25)
#define REG_DSP1_CH11_EQ_6_2_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+26)
#define REG_DSP1_CH11_EQ_6_3_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+27)
#define REG_DSP1_CH11_EQ_6_4_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+28)
#define REG_DSP1_CH11_EQ_6_5_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+29)

#define REG_DSP1_CH11_EQ_7_1_ADDR    	    (REG_DSP1_CH11_EQ_1_1_ADDR+30)
#define REG_DSP1_CH11_EQ_7_2_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+31)
#define REG_DSP1_CH11_EQ_7_3_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+32)
#define REG_DSP1_CH11_EQ_7_4_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+33)
#define REG_DSP1_CH11_EQ_7_5_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+34)

#define REG_DSP1_CH11_EQ_8_1_ADDR    	    (REG_DSP1_CH11_EQ_1_1_ADDR+35)
#define REG_DSP1_CH11_EQ_8_2_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+36)
#define REG_DSP1_CH11_EQ_8_3_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+37)
#define REG_DSP1_CH11_EQ_8_4_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+38)
#define REG_DSP1_CH11_EQ_8_5_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+39)

#define REG_DSP1_CH11_EQ_9_1_ADDR    	    (REG_DSP1_CH11_EQ_1_1_ADDR+40)
#define REG_DSP1_CH11_EQ_9_2_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+41)
#define REG_DSP1_CH11_EQ_9_3_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+42)
#define REG_DSP1_CH11_EQ_9_4_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+43)
#define REG_DSP1_CH11_EQ_9_5_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+44)

#define REG_DSP1_CH11_EQ_10_1_ADDR    	    (REG_DSP1_CH11_EQ_1_1_ADDR+45)
#define REG_DSP1_CH11_EQ_10_2_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+46)
#define REG_DSP1_CH11_EQ_10_3_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+47)
#define REG_DSP1_CH11_EQ_10_4_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+48)
#define REG_DSP1_CH11_EQ_10_5_ADDR     		(REG_DSP1_CH11_EQ_1_1_ADDR+49)

/* channel_eq 12 */
#define REG_DSP1_CH12_EQ_1_1_ADDR    	    0x0426
#define REG_DSP1_CH12_EQ_1_2_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+1)
#define REG_DSP1_CH12_EQ_1_3_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+2)
#define REG_DSP1_CH12_EQ_1_4_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+3)
#define REG_DSP1_CH12_EQ_1_5_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+4)

#define REG_DSP1_CH12_EQ_2_1_ADDR    	    (REG_DSP1_CH12_EQ_1_1_ADDR+5)
#define REG_DSP1_CH12_EQ_2_2_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+6)
#define REG_DSP1_CH12_EQ_2_3_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+7)
#define REG_DSP1_CH12_EQ_2_4_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+8)
#define REG_DSP1_CH12_EQ_2_5_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+9)

#define REG_DSP1_CH12_EQ_3_1_ADDR    	    (REG_DSP1_CH12_EQ_1_1_ADDR+10)
#define REG_DSP1_CH12_EQ_3_2_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+11)
#define REG_DSP1_CH12_EQ_3_3_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+12)
#define REG_DSP1_CH12_EQ_3_4_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+13)
#define REG_DSP1_CH12_EQ_3_5_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+14)

#define REG_DSP1_CH12_EQ_4_1_ADDR    	    (REG_DSP1_CH12_EQ_1_1_ADDR+15)
#define REG_DSP1_CH12_EQ_4_2_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+16)
#define REG_DSP1_CH12_EQ_4_3_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+17)
#define REG_DSP1_CH12_EQ_4_4_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+18)
#define REG_DSP1_CH12_EQ_4_5_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+19)

#define REG_DSP1_CH12_EQ_5_1_ADDR    	    (REG_DSP1_CH12_EQ_1_1_ADDR+20)
#define REG_DSP1_CH12_EQ_5_2_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+21)
#define REG_DSP1_CH12_EQ_5_3_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+22)
#define REG_DSP1_CH12_EQ_5_4_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+23)
#define REG_DSP1_CH12_EQ_5_5_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+24)

#define REG_DSP1_CH12_EQ_6_1_ADDR    	    (REG_DSP1_CH12_EQ_1_1_ADDR+25)
#define REG_DSP1_CH12_EQ_6_2_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+26)
#define REG_DSP1_CH12_EQ_6_3_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+27)
#define REG_DSP1_CH12_EQ_6_4_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+28)
#define REG_DSP1_CH12_EQ_6_5_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+29)

#define REG_DSP1_CH12_EQ_7_1_ADDR    	    (REG_DSP1_CH12_EQ_1_1_ADDR+30)
#define REG_DSP1_CH12_EQ_7_2_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+31)
#define REG_DSP1_CH12_EQ_7_3_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+32)
#define REG_DSP1_CH12_EQ_7_4_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+33)
#define REG_DSP1_CH12_EQ_7_5_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+34)

#define REG_DSP1_CH12_EQ_8_1_ADDR    	    (REG_DSP1_CH12_EQ_1_1_ADDR+35)
#define REG_DSP1_CH12_EQ_8_2_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+36)
#define REG_DSP1_CH12_EQ_8_3_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+37)
#define REG_DSP1_CH12_EQ_8_4_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+38)
#define REG_DSP1_CH12_EQ_8_5_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+39)

#define REG_DSP1_CH12_EQ_9_1_ADDR    	    (REG_DSP1_CH12_EQ_1_1_ADDR+40)
#define REG_DSP1_CH12_EQ_9_2_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+41)
#define REG_DSP1_CH12_EQ_9_3_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+42)
#define REG_DSP1_CH12_EQ_9_4_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+43)
#define REG_DSP1_CH12_EQ_9_5_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+44)

#define REG_DSP1_CH12_EQ_10_1_ADDR    	    (REG_DSP1_CH12_EQ_1_1_ADDR+45)
#define REG_DSP1_CH12_EQ_10_2_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+46)
#define REG_DSP1_CH12_EQ_10_3_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+47)
#define REG_DSP1_CH12_EQ_10_4_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+48)
#define REG_DSP1_CH12_EQ_10_5_ADDR     		(REG_DSP1_CH12_EQ_1_1_ADDR+49)

/* channel_eq 13 */
#define REG_DSP1_CH13_EQ_1_1_ADDR    	    0x0458
#define REG_DSP1_CH13_EQ_1_2_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+1)
#define REG_DSP1_CH13_EQ_1_3_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+2)
#define REG_DSP1_CH13_EQ_1_4_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+3)
#define REG_DSP1_CH13_EQ_1_5_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+4)

#define REG_DSP1_CH13_EQ_2_1_ADDR    	    (REG_DSP1_CH13_EQ_1_1_ADDR+5)
#define REG_DSP1_CH13_EQ_2_2_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+6)
#define REG_DSP1_CH13_EQ_2_3_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+7)
#define REG_DSP1_CH13_EQ_2_4_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+8)
#define REG_DSP1_CH13_EQ_2_5_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+9)

#define REG_DSP1_CH13_EQ_3_1_ADDR    	    (REG_DSP1_CH13_EQ_1_1_ADDR+10)
#define REG_DSP1_CH13_EQ_3_2_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+11)
#define REG_DSP1_CH13_EQ_3_3_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+12)
#define REG_DSP1_CH13_EQ_3_4_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+13)
#define REG_DSP1_CH13_EQ_3_5_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+14)

#define REG_DSP1_CH13_EQ_4_1_ADDR    	    (REG_DSP1_CH13_EQ_1_1_ADDR+15)
#define REG_DSP1_CH13_EQ_4_2_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+16)
#define REG_DSP1_CH13_EQ_4_3_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+17)
#define REG_DSP1_CH13_EQ_4_4_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+18)
#define REG_DSP1_CH13_EQ_4_5_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+19)

#define REG_DSP1_CH13_EQ_5_1_ADDR    	    (REG_DSP1_CH13_EQ_1_1_ADDR+20)
#define REG_DSP1_CH13_EQ_5_2_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+21)
#define REG_DSP1_CH13_EQ_5_3_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+22)
#define REG_DSP1_CH13_EQ_5_4_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+23)
#define REG_DSP1_CH13_EQ_5_5_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+24)

#define REG_DSP1_CH13_EQ_6_1_ADDR    	    (REG_DSP1_CH13_EQ_1_1_ADDR+25)
#define REG_DSP1_CH13_EQ_6_2_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+26)
#define REG_DSP1_CH13_EQ_6_3_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+27)
#define REG_DSP1_CH13_EQ_6_4_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+28)
#define REG_DSP1_CH13_EQ_6_5_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+29)

#define REG_DSP1_CH13_EQ_7_1_ADDR    	    (REG_DSP1_CH13_EQ_1_1_ADDR+30)
#define REG_DSP1_CH13_EQ_7_2_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+31)
#define REG_DSP1_CH13_EQ_7_3_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+32)
#define REG_DSP1_CH13_EQ_7_4_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+33)
#define REG_DSP1_CH13_EQ_7_5_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+34)

#define REG_DSP1_CH13_EQ_8_1_ADDR    	    (REG_DSP1_CH13_EQ_1_1_ADDR+35)
#define REG_DSP1_CH13_EQ_8_2_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+36)
#define REG_DSP1_CH13_EQ_8_3_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+37)
#define REG_DSP1_CH13_EQ_8_4_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+38)
#define REG_DSP1_CH13_EQ_8_5_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+39)

#define REG_DSP1_CH13_EQ_9_1_ADDR    	    (REG_DSP1_CH13_EQ_1_1_ADDR+40)
#define REG_DSP1_CH13_EQ_9_2_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+41)
#define REG_DSP1_CH13_EQ_9_3_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+42)
#define REG_DSP1_CH13_EQ_9_4_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+43)
#define REG_DSP1_CH13_EQ_9_5_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+44)

#define REG_DSP1_CH13_EQ_10_1_ADDR    	    (REG_DSP1_CH13_EQ_1_1_ADDR+45)
#define REG_DSP1_CH13_EQ_10_2_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+46)
#define REG_DSP1_CH13_EQ_10_3_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+47)
#define REG_DSP1_CH13_EQ_10_4_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+48)
#define REG_DSP1_CH13_EQ_10_5_ADDR     		(REG_DSP1_CH13_EQ_1_1_ADDR+49)

/* channel_eq 14 */
#define REG_DSP1_CH14_EQ_1_1_ADDR    	    0x048A
#define REG_DSP1_CH14_EQ_1_2_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+1)
#define REG_DSP1_CH14_EQ_1_3_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+2)
#define REG_DSP1_CH14_EQ_1_4_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+3)
#define REG_DSP1_CH14_EQ_1_5_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+4)

#define REG_DSP1_CH14_EQ_2_1_ADDR    	    (REG_DSP1_CH14_EQ_1_1_ADDR+5)
#define REG_DSP1_CH14_EQ_2_2_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+6)
#define REG_DSP1_CH14_EQ_2_3_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+7)
#define REG_DSP1_CH14_EQ_2_4_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+8)
#define REG_DSP1_CH14_EQ_2_5_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+9)

#define REG_DSP1_CH14_EQ_3_1_ADDR    	    (REG_DSP1_CH14_EQ_1_1_ADDR+10)
#define REG_DSP1_CH14_EQ_3_2_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+11)
#define REG_DSP1_CH14_EQ_3_3_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+12)
#define REG_DSP1_CH14_EQ_3_4_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+13)
#define REG_DSP1_CH14_EQ_3_5_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+14)

#define REG_DSP1_CH14_EQ_4_1_ADDR    	    (REG_DSP1_CH14_EQ_1_1_ADDR+15)
#define REG_DSP1_CH14_EQ_4_2_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+16)
#define REG_DSP1_CH14_EQ_4_3_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+17)
#define REG_DSP1_CH14_EQ_4_4_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+18)
#define REG_DSP1_CH14_EQ_4_5_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+19)

#define REG_DSP1_CH14_EQ_5_1_ADDR    	    (REG_DSP1_CH14_EQ_1_1_ADDR+20)
#define REG_DSP1_CH14_EQ_5_2_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+21)
#define REG_DSP1_CH14_EQ_5_3_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+22)
#define REG_DSP1_CH14_EQ_5_4_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+23)
#define REG_DSP1_CH14_EQ_5_5_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+24)

#define REG_DSP1_CH14_EQ_6_1_ADDR    	    (REG_DSP1_CH14_EQ_1_1_ADDR+25)
#define REG_DSP1_CH14_EQ_6_2_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+26)
#define REG_DSP1_CH14_EQ_6_3_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+27)
#define REG_DSP1_CH14_EQ_6_4_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+28)
#define REG_DSP1_CH14_EQ_6_5_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+29)

#define REG_DSP1_CH14_EQ_7_1_ADDR    	    (REG_DSP1_CH14_EQ_1_1_ADDR+30)
#define REG_DSP1_CH14_EQ_7_2_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+31)
#define REG_DSP1_CH14_EQ_7_3_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+32)
#define REG_DSP1_CH14_EQ_7_4_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+33)
#define REG_DSP1_CH14_EQ_7_5_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+34)

#define REG_DSP1_CH14_EQ_8_1_ADDR    	    (REG_DSP1_CH14_EQ_1_1_ADDR+35)
#define REG_DSP1_CH14_EQ_8_2_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+36)
#define REG_DSP1_CH14_EQ_8_3_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+37)
#define REG_DSP1_CH14_EQ_8_4_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+38)
#define REG_DSP1_CH14_EQ_8_5_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+39)

#define REG_DSP1_CH14_EQ_9_1_ADDR    	    (REG_DSP1_CH14_EQ_1_1_ADDR+40)
#define REG_DSP1_CH14_EQ_9_2_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+41)
#define REG_DSP1_CH14_EQ_9_3_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+42)
#define REG_DSP1_CH14_EQ_9_4_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+43)
#define REG_DSP1_CH14_EQ_9_5_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+44)

#define REG_DSP1_CH14_EQ_10_1_ADDR    	    (REG_DSP1_CH14_EQ_1_1_ADDR+45)
#define REG_DSP1_CH14_EQ_10_2_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+46)
#define REG_DSP1_CH14_EQ_10_3_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+47)
#define REG_DSP1_CH14_EQ_10_4_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+48)
#define REG_DSP1_CH14_EQ_10_5_ADDR     		(REG_DSP1_CH14_EQ_1_1_ADDR+49)

/* channel_eq 15 */
#define REG_DSP1_CH15_EQ_1_1_ADDR    	    0x04BC
#define REG_DSP1_CH15_EQ_1_2_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+1)
#define REG_DSP1_CH15_EQ_1_3_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+2)
#define REG_DSP1_CH15_EQ_1_4_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+3)
#define REG_DSP1_CH15_EQ_1_5_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+4)

#define REG_DSP1_CH15_EQ_2_1_ADDR    	    (REG_DSP1_CH15_EQ_1_1_ADDR+5)
#define REG_DSP1_CH15_EQ_2_2_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+6)
#define REG_DSP1_CH15_EQ_2_3_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+7)
#define REG_DSP1_CH15_EQ_2_4_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+8)
#define REG_DSP1_CH15_EQ_2_5_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+9)

#define REG_DSP1_CH15_EQ_3_1_ADDR    	    (REG_DSP1_CH15_EQ_1_1_ADDR+10)
#define REG_DSP1_CH15_EQ_3_2_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+11)
#define REG_DSP1_CH15_EQ_3_3_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+12)
#define REG_DSP1_CH15_EQ_3_4_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+13)
#define REG_DSP1_CH15_EQ_3_5_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+14)

#define REG_DSP1_CH15_EQ_4_1_ADDR    	    (REG_DSP1_CH15_EQ_1_1_ADDR+15)
#define REG_DSP1_CH15_EQ_4_2_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+16)
#define REG_DSP1_CH15_EQ_4_3_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+17)
#define REG_DSP1_CH15_EQ_4_4_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+18)
#define REG_DSP1_CH15_EQ_4_5_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+19)

#define REG_DSP1_CH15_EQ_5_1_ADDR    	    (REG_DSP1_CH15_EQ_1_1_ADDR+20)
#define REG_DSP1_CH15_EQ_5_2_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+21)
#define REG_DSP1_CH15_EQ_5_3_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+22)
#define REG_DSP1_CH15_EQ_5_4_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+23)
#define REG_DSP1_CH15_EQ_5_5_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+24)

#define REG_DSP1_CH15_EQ_6_1_ADDR    	    (REG_DSP1_CH15_EQ_1_1_ADDR+25)
#define REG_DSP1_CH15_EQ_6_2_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+26)
#define REG_DSP1_CH15_EQ_6_3_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+27)
#define REG_DSP1_CH15_EQ_6_4_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+28)
#define REG_DSP1_CH15_EQ_6_5_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+29)

#define REG_DSP1_CH15_EQ_7_1_ADDR    	    (REG_DSP1_CH15_EQ_1_1_ADDR+30)
#define REG_DSP1_CH15_EQ_7_2_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+31)
#define REG_DSP1_CH15_EQ_7_3_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+32)
#define REG_DSP1_CH15_EQ_7_4_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+33)
#define REG_DSP1_CH15_EQ_7_5_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+34)

#define REG_DSP1_CH15_EQ_8_1_ADDR    	    (REG_DSP1_CH15_EQ_1_1_ADDR+35)
#define REG_DSP1_CH15_EQ_8_2_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+36)
#define REG_DSP1_CH15_EQ_8_3_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+37)
#define REG_DSP1_CH15_EQ_8_4_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+38)
#define REG_DSP1_CH15_EQ_8_5_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+39)

#define REG_DSP1_CH15_EQ_9_1_ADDR    	    (REG_DSP1_CH15_EQ_1_1_ADDR+40)
#define REG_DSP1_CH15_EQ_9_2_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+41)
#define REG_DSP1_CH15_EQ_9_3_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+42)
#define REG_DSP1_CH15_EQ_9_4_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+43)
#define REG_DSP1_CH15_EQ_9_5_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+44)

#define REG_DSP1_CH15_EQ_10_1_ADDR    	    (REG_DSP1_CH15_EQ_1_1_ADDR+45)
#define REG_DSP1_CH15_EQ_10_2_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+46)
#define REG_DSP1_CH15_EQ_10_3_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+47)
#define REG_DSP1_CH15_EQ_10_4_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+48)
#define REG_DSP1_CH15_EQ_10_5_ADDR     		(REG_DSP1_CH15_EQ_1_1_ADDR+49)

/* channel_eq 16 */
#define REG_DSP1_CH16_EQ_1_1_ADDR    	    0x04EE
#define REG_DSP1_CH16_EQ_1_2_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+1)
#define REG_DSP1_CH16_EQ_1_3_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+2)
#define REG_DSP1_CH16_EQ_1_4_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+3)
#define REG_DSP1_CH16_EQ_1_5_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+4)

#define REG_DSP1_CH16_EQ_2_1_ADDR    	    (REG_DSP1_CH16_EQ_1_1_ADDR+5)
#define REG_DSP1_CH16_EQ_2_2_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+6)
#define REG_DSP1_CH16_EQ_2_3_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+7)
#define REG_DSP1_CH16_EQ_2_4_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+8)
#define REG_DSP1_CH16_EQ_2_5_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+9)

#define REG_DSP1_CH16_EQ_3_1_ADDR    	    (REG_DSP1_CH16_EQ_1_1_ADDR+10)
#define REG_DSP1_CH16_EQ_3_2_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+11)
#define REG_DSP1_CH16_EQ_3_3_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+12)
#define REG_DSP1_CH16_EQ_3_4_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+13)
#define REG_DSP1_CH16_EQ_3_5_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+14)

#define REG_DSP1_CH16_EQ_4_1_ADDR    	    (REG_DSP1_CH16_EQ_1_1_ADDR+15)
#define REG_DSP1_CH16_EQ_4_2_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+16)
#define REG_DSP1_CH16_EQ_4_3_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+17)
#define REG_DSP1_CH16_EQ_4_4_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+18)
#define REG_DSP1_CH16_EQ_4_5_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+19)

#define REG_DSP1_CH16_EQ_5_1_ADDR    	    (REG_DSP1_CH16_EQ_1_1_ADDR+20)
#define REG_DSP1_CH16_EQ_5_2_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+21)
#define REG_DSP1_CH16_EQ_5_3_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+22)
#define REG_DSP1_CH16_EQ_5_4_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+23)
#define REG_DSP1_CH16_EQ_5_5_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+24)

#define REG_DSP1_CH16_EQ_6_1_ADDR    	    (REG_DSP1_CH16_EQ_1_1_ADDR+25)
#define REG_DSP1_CH16_EQ_6_2_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+26)
#define REG_DSP1_CH16_EQ_6_3_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+27)
#define REG_DSP1_CH16_EQ_6_4_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+28)
#define REG_DSP1_CH16_EQ_6_5_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+29)

#define REG_DSP1_CH16_EQ_7_1_ADDR    	    (REG_DSP1_CH16_EQ_1_1_ADDR+30)
#define REG_DSP1_CH16_EQ_7_2_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+31)
#define REG_DSP1_CH16_EQ_7_3_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+32)
#define REG_DSP1_CH16_EQ_7_4_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+33)
#define REG_DSP1_CH16_EQ_7_5_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+34)

#define REG_DSP1_CH16_EQ_8_1_ADDR    	    (REG_DSP1_CH16_EQ_1_1_ADDR+35)
#define REG_DSP1_CH16_EQ_8_2_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+36)
#define REG_DSP1_CH16_EQ_8_3_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+37)
#define REG_DSP1_CH16_EQ_8_4_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+38)
#define REG_DSP1_CH16_EQ_8_5_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+39)

#define REG_DSP1_CH16_EQ_9_1_ADDR    	    (REG_DSP1_CH16_EQ_1_1_ADDR+40)
#define REG_DSP1_CH16_EQ_9_2_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+41)
#define REG_DSP1_CH16_EQ_9_3_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+42)
#define REG_DSP1_CH16_EQ_9_4_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+43)
#define REG_DSP1_CH16_EQ_9_5_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+44)

#define REG_DSP1_CH16_EQ_10_1_ADDR    	    (REG_DSP1_CH16_EQ_1_1_ADDR+45)
#define REG_DSP1_CH16_EQ_10_2_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+46)
#define REG_DSP1_CH16_EQ_10_3_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+47)
#define REG_DSP1_CH16_EQ_10_4_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+48)
#define REG_DSP1_CH16_EQ_10_5_ADDR     		(REG_DSP1_CH16_EQ_1_1_ADDR+49)

//通道eq组件寄存器定义
//通道eq组件寄存器一次读出和写入 4bytes
/* channel_delay 1 */
#define REG_DSP1_CH1_DELAY_ADDR    	   		0x0520

/* channel_delay 2 */
#define REG_DSP1_CH2_DELAY_ADDR    	    	(REG_DSP1_CH1_DELAY_ADDR+1) 

/* channel_delay 3 */
#define REG_DSP1_CH3_DELAY_ADDR    	    	(REG_DSP1_CH1_DELAY_ADDR+2)

/* channel_delay 4 */
#define REG_DSP1_CH4_DELAY_ADDR    	    	(REG_DSP1_CH1_DELAY_ADDR+3)

/* channel_delay 5 */
#define REG_DSP1_CH5_DELAY_ADDR    	    	(REG_DSP1_CH1_DELAY_ADDR+4)

/* channel_delay 6 */
#define REG_DSP1_CH6_DELAY_ADDR    	    	(REG_DSP1_CH1_DELAY_ADDR+5)

/* channel_delay 7 */
#define REG_DSP1_CH7_DELAY_ADDR    	    	(REG_DSP1_CH1_DELAY_ADDR+6)

/* channel_delay 8 */
#define REG_DSP1_CH8_DELAY_ADDR    	    	(REG_DSP1_CH1_DELAY_ADDR+7)

/* channel_delay 9 */
#define REG_DSP1_CH9_DELAY_ADDR    	    	(REG_DSP1_CH1_DELAY_ADDR+8)

/* channel_delay 10 */
#define REG_DSP1_CH10_DELAY_ADDR    	    (REG_DSP1_CH1_DELAY_ADDR+9)

/* channel_delay 11 */
#define REG_DSP1_CH11_DELAY_ADDR    	    (REG_DSP1_CH1_DELAY_ADDR+10)

/* channel_delay 12 */
#define REG_DSP1_CH12_DELAY_ADDR    	    (REG_DSP1_CH1_DELAY_ADDR+11)

/* channel_delay 13 */
#define REG_DSP1_CH13_DELAY_ADDR    	    (REG_DSP1_CH1_DELAY_ADDR+12)

/* channel_delay 14 */
#define REG_DSP1_CH14_DELAY_ADDR    	    (REG_DSP1_CH1_DELAY_ADDR+13)

/* channel_delay 15 */
#define REG_DSP1_CH15_DELAY_ADDR    	    (REG_DSP1_CH1_DELAY_ADDR+14)

/* channel_delay 16 */
#define REG_DSP1_CH16_DELAY_ADDR    	    (REG_DSP1_CH1_DELAY_ADDR+15)


//DSP1 with DSP2 share


#define DSP_REG_VALUE_TYPE							const uint8_t

#define REG_VOLUME_BYTE						0x04
#define REG_MUTE_BYTE							0x04
#define REG_MONO_BYTE							0x04
#define REG_DELAY_BYTE						0x04
#define REG_PAGE_SELECT_BYTE			0x02
#define REG_EQ_BYTE								0x04

// volume -30db~0db
DSP_REG_VALUE_TYPE DSP_REG_VOLUME_VALUE[32][REG_VOLUME_BYTE] = {
{0x01,0x00,0x00,0x00},//0db
{0x00,0xe4,0x29,0x05},//-1db
{0x00,0xcb,0x59,0x18},//-2db
{0x00,0xb5,0x3b,0xef},//-3db
{0x00,0xa1,0x86,0x6c},//-4db
{0x00,0x8f,0xf5,0x9a},//-5db
{0x00,0x80,0x4d,0xce},//-6db
{0x00,0x72,0x59,0xdb},//-7db
{0x00,0x65,0xea,0x5a},//-8db
{0x00,0x5a,0xd5,0x0d},//-9db
{0x00,0x50,0xf4,0x4e},//-10db
{0x00,0x48,0x26,0x8e},//-11db
{0x00,0x40,0x4d,0xe6},//-12db
{0x00,0x39,0x4f,0xaf},//-13db
{0x00,0x33,0x14,0x27},//-14db
{0x00,0x2d,0x86,0x22},//-15db
{0x00,0x28,0x92,0xc2},//-16db
{0x00,0x24,0x29,0x35},//-17db
{0x00,0x20,0x3a,0x7e},//-18db
{0x00,0x1c,0xb9,0x43},//-19db
{0x00,0x19,0x99,0x9a},//-20db
{0x00,0x16,0xd0,0xe7},//-21db
{0x00,0x14,0x55,0xb6},//-22db
{0x00,0x12,0x1f,0x98},//-23db
{0x00,0x10,0x27,0x0b},//-24db
{0x00,0x0e,0x65,0x5c},//-25db
{0x00,0x0c,0xd4,0x95},//-26db
{0x00,0x0b,0x6f,0x63},//-27db
{0x00,0x0a,0x31,0x09},//-28db
{0x00,0x09,0x15,0x4e},//-29db
{0x00,0x08,0x18,0x6e},//-30db
{0x00,0x00,0x00,0x00},//-144db mute
};

// mute mute/not mute
DSP_REG_VALUE_TYPE DSP_REG_MUTE_VALUE[2][REG_MUTE_BYTE] = {
{0x00,0x00,0x00,0x01},//not mute
{0x00,0x00,0x00,0x00},//mute
};

// mono on/off
DSP_REG_VALUE_TYPE DSP_REG_MONO_VALUE[2][REG_MONO_BYTE] = {
{0x00,0x00,0x00,0x00},//off,其他模式
{0x00,0x00,0x00,0x01},//on,同传模式
};

// page select 
DSP_REG_VALUE_TYPE DSP_REG_PAGE_SELECT_VALUE[2][REG_PAGE_SELECT_BYTE] = {
{0x00,0x00},//page 0
{0x00,0x01},//page 1
};

// EQ 100
DSP_REG_VALUE_TYPE DSP_REG_EQ_100_VALUE[21][REG_EQ_BYTE*5] = {
{
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x01,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,  
},//0
{
	0x00,0xFD,0xA1,0x41,
	0xFE,0x02,0x47,0x0A,
	0x01,0x00,0x22,0xE3,
	0xFF,0x02,0x3B,0xDC,
	0x01,0xFD,0xB8,0xF6, 
},//1
{
	0x00,0xFD,0x9E,0x17,
	0xFE,0x02,0x27,0x2F,
	0x01,0x00,0x45,0xE9,
	0xFF,0x02,0x1C,0x00,
	0x01,0xFD,0xD8,0xD1, 
},//2
{
	0x00,0xFD,0x98,0xE9,
	0xFE,0x02,0x09,0x19,
	0x01,0x00,0x69,0x2E,
	0xFF,0x01,0xFD,0xE9,
	0x01,0xFD,0xF6,0xE7,
},//3
{
	0x00,0xFD,0x91,0xB3,
	0xFE,0x01,0xEC,0xAE,
	0x01,0x00,0x8C,0xD0,
	0xFF,0x01,0xE1,0x7E,
	0x01,0xFE,0x13,0x52,
},//4
{
	0x00,0xFD,0x88,0x6D,
	0xFE,0x01,0xD1,0xD7,
	0x01,0x00,0xB0,0xEC,
	0xFF,0x01,0xC6,0xA7,
	0x01,0xFE,0x2E,0x29,
},//5
{
	0x00,0xFD,0x7D,0x11,
	0xFE,0x01,0xB8,0x7E,
	0x01,0x00,0xD5,0xA2,
	0xFF,0x01,0xAD,0x4D,
	0x01,0xFE,0x47,0x82,
},//6
{
	0x00,0xFD,0x6F,0x93,
	0xFE,0x01,0xA0,0x8E,
	0x01,0x00,0xFB,0x11,
	0xFF,0x01,0x95,0x5C,
	0x01,0xFE,0x5F,0x72,
},//7
{
	0x00,0xFD,0x5F,0xE9,
	0xFE,0x01,0x89,0xF3,
	0x01,0x01,0x21,0x57,
	0xFF,0x01,0x7E,0xC0,
	0x01,0xFE,0x76,0x0D,
},//8
{
	0x00,0xFD,0x4E,0x05,
	0xFE,0x01,0x74,0x99,
	0x01,0x01,0x48,0x95,
	0xFF,0x01,0x69,0x66,
	0x01,0xFE,0x8B,0x67,
},//9
{
	0x00,0xFD,0x39,0xD7,
	0xFE,0x01,0x60,0x70,
	0x01,0x01,0x70,0xEC,
	0xFF,0x01,0x55,0x3C,
	0x01,0xFE,0x9F,0x90,
},//10

{
	0x00,0xFD,0xA1,0x94,
	0xFE,0x02,0x8C,0x78,
	0x00,0xFF,0xDD,0x21,
	0xFF,0x02,0x81,0x4B,
	0x01,0xFD,0x73,0x88,
},//-1
{
	0x00,0xFD,0x9E,0xBD,
	0xFE,0x02,0xB2,0x44,
	0x00,0xFF,0xBA,0x2A,
	0xFF,0x02,0xA7,0x19,
	0x01,0xFD,0x4D,0xBC,
},//-2
{
	0x00,0xFD,0x99,0xE5,
	0xFE,0x02,0xDA,0x48,
	0x00,0xFF,0x96,0xFD,
	0xFF,0x02,0xCF,0x1D,
	0x01,0xFD,0x25,0xB8,
},//-3
{
	0x00,0xFD,0x93,0x08,
	0xFE,0x03,0x04,0xA4,
	0x00,0xFF,0x73,0x7E,
	0xFF,0x02,0xF9,0x7A,
	0x01,0xFC,0xFB,0x5C,
},//-4
{
	0x00,0xFD,0x8A,0x20,
	0xFE,0x03,0x31,0x7B,
	0x00,0xFF,0x4F,0x8E,
	0xFF,0x03,0x26,0x52,
	0x01,0xFC,0xCE,0x85,
},//-5
{
	0x00,0xFD,0x7F,0x27,
	0xFE,0x03,0x60,0xF1,
	0x00,0xFF,0x2B,0x0F,
	0xFF,0x03,0x55,0xC9,
	0x01,0xFC,0x9F,0x0F,
},//-6
{
	0x00,0xFD,0x72,0x14,
	0xFE,0x03,0x93,0x2E,
	0x00,0xFF,0x05,0xE5,
	0xFF,0x03,0x88,0x07,
	0x01,0xFC,0x6C,0xD2,
},//-7
{
	0x00,0xFD,0x62,0xDD,
	0xFE,0x03,0xC8,0x5A,
	0x00,0xFE,0xDF,0xEF,
	0xFF,0x03,0xBD,0x34,
	0x01,0xFC,0x37,0xA6,
},//-8
{
	0x00,0xFD,0x51,0x76,
	0xFE,0x04,0x00,0xA0,
	0x00,0xFE,0xB9,0x0F,
	0xFF,0x03,0xF5,0x7B,
	0x01,0xFB,0xFF,0x60,
},//-9
{
	0x00,0xFD,0x3D,0xD1,
	0xFE,0x04,0x3C,0x2E,
	0x00,0xFE,0x91,0x24,
	0xFF,0x04,0x31,0x0B,
	0x01,0xFB,0xC3,0xD2,
},//-10
};

// EQ 200
DSP_REG_VALUE_TYPE DSP_REG_EQ_200_VALUE[21][REG_EQ_BYTE*5] = {
{
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x01,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,  
},//0
{
	0x00,0xFB,0x47,0xE2,
	0xFE,0x04,0x9F,0x2D,
	0x01,0x00,0x45,0x78,
	0xFF,0x04,0x72,0xA7,
	0x01,0xFB,0x60,0xD3,
},//1
{
	0x00,0xFB,0x41,0x4A,
	0xFE,0x04,0x60,0x06,
	0x01,0x00,0x8B,0x3C,
	0xFF,0x04,0x33,0x7A,
	0x01,0xFB,0x9F,0xFA,
},//2
{
	0x00,0xFB,0x36,0xB1,
	0xFE,0x04,0x24,0x5A,
	0x01,0x00,0xD1,0x86,
	0xFF,0x03,0xF7,0xC8,
	0x01,0xFB,0xDB,0xA6,
},//3
{
	0x00,0xFB,0x28,0x0E,
	0xFE,0x03,0xEB,0xF7,
	0x01,0x01,0x18,0x91,
	0xFF,0x03,0xBF,0x61,
	0x01,0xFC,0x14,0x09,
},//4
{
	0x00,0xFB,0x15,0x54,
	0xFE,0x03,0xB6,0xB0,
	0x01,0x01,0x60,0x98,
	0xFF,0x03,0x8A,0x15,
	0x01,0xFC,0x49,0x50,
},//5
{
	0x00,0xFA,0xFE,0x70,
	0xFE,0x03,0x84,0x59,
	0x01,0x01,0xA9,0xD6,
	0xFF,0x03,0x57,0xBA,
	0x01,0xFC,0x7B,0xA7,
},//6
{
	0x00,0xFA,0xE3,0x4F,
	0xFE,0x03,0x54,0xCB,
	0x01,0x01,0xF4,0x8A,
	0xFF,0x03,0x28,0x27,
	0x01,0xFC,0xAB,0x35,
},//7
{
	0x00,0xFA,0xC3,0xD9,
	0xFE,0x03,0x27,0xDD,
	0x01,0x02,0x40,0xF1,
	0xFF,0x02,0xFB,0x36,
	0x01,0xFC,0xD8,0x23,
},//8
{
	0x00,0xFA,0x9F,0xF3,
	0xFE,0x02,0xFD,0x6B,
	0x01,0x02,0x8F,0x4D,
	0xFF,0x02,0xD0,0xC0,
	0x01,0xFD,0x02,0x95,
},//9
{
	0x00,0xFA,0x77,0x7D,
	0xFE,0x02,0xD5,0x53,
	0x01,0x02,0xDF,0xDE,
	0xFF,0x02,0xA8,0xA4,
	0x01,0xFD,0x2A,0xAD,
},//10

{
	0x00,0xFB,0x49,0x29,
	0xFE,0x05,0x28,0xB6,
	0x00,0xFF,0xBA,0x9B,
	0xFF,0x04,0xFC,0x3C,
	0x01,0xFA,0xD7,0x4A,
},//-1
{
	0x00,0xFB,0x43,0xDD,
	0xFE,0x05,0x73,0x87,
	0x00,0xFF,0x75,0x10,
	0xFF,0x05,0x47,0x14,
	0x01,0xFA,0x8C,0x79,
},//-2
{
	0x00,0xFB,0x3A,0x99,
	0xFE,0x05,0xC2,0xAF,
	0x00,0xFF,0x2F,0x25,
	0xFF,0x05,0x96,0x42,
	0x01,0xFA,0x3D,0x51,
},//-3
{
	0x00,0xFB,0x2D,0x58,
	0xFE,0x06,0x16,0x6D,
	0x00,0xFE,0xE8,0xA1,
	0xFF,0x05,0xEA,0x07,
	0x01,0xF9,0xE9,0x93,
},//-4
{
	0x00,0xFB,0x1C,0x10,
	0xFE,0x06,0x6F,0x02,
	0x00,0xFE,0xA1,0x4B,
	0xFF,0x06,0x42,0xA5,
	0x01,0xF9,0x90,0xFE,
},//-5
{
	0x00,0xFB,0x06,0xB6,
	0xFE,0x06,0xCC,0xB6,
	0x00,0xFE,0x58,0xEA,
	0xFF,0x06,0xA0,0x60,
	0x01,0xF9,0x33,0x4A,
},//-6
{
	0x00,0xFA,0xED,0x3A,
	0xFE,0x07,0x2F,0xD1,
	0x00,0xFE,0x0F,0x41,
	0xFF,0x07,0x03,0x84,
	0x01,0xF8,0xD0,0x2F,
},//-7
{
	0x00,0xFA,0xCF,0x8B,
	0xFE,0x07,0x98,0xA1,
	0x00,0xFD,0xC4,0x18,
	0xFF,0x07,0x6C,0x5D,
	0x01,0xF8,0x67,0x5F,
},//-8
{
	0x00,0xFA,0xAD,0x92,
	0xFE,0x08,0x07,0x78,
	0x00,0xFD,0x77,0x30,
	0xFF,0x07,0xDB,0x3E,
	0x01,0xF7,0xF8,0x88,
},//-9
{
	0x00,0xFA,0x87,0x38,
	0xFE,0x08,0x7C,0xAA,
	0x00,0xFD,0x28,0x4D,
	0xFF,0x08,0x50,0x7B,
	0x01,0xF7,0x83,0x56,
},//-10
};

// EQ 400
DSP_REG_VALUE_TYPE DSP_REG_EQ_400_VALUE[21][REG_EQ_BYTE*5] = {
{
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x01,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,  
},//0
{
	0x00,0xF6,0xA5,0x61,
	0xFE,0x09,0x81,0x77,
	0x01,0x00,0x89,0xB2,
	0xFF,0x08,0xD0,0xEE,
	0x01,0xF6,0x7E,0x89,
},//1
{
	0x00,0xF6,0x97,0x29,
	0xFE,0x09,0x05,0x70,
	0x01,0x01,0x14,0x1C,
	0xFF,0x08,0x54,0xBB,
	0x01,0xF6,0xFA,0x90,
},//2
{
	0x00,0xF6,0x81,0x0D,
	0xFE,0x08,0x90,0x21,
	0x01,0x01,0x9F,0xB0,
	0xFF,0x07,0xDF,0x43,
	0x01,0xF7,0x6F,0xDF,
},//3
{
	0x00,0xF6,0x62,0xF7,
	0xFE,0x08,0x21,0x30,
	0x01,0x02,0x2C,0xDE,
	0xFF,0x07,0x70,0x2B,
	0x01,0xF7,0xDE,0xD0,
},//4
{
	0x00,0xF6,0x3C,0xC8,
	0xFE,0x07,0xB8,0x47,
	0x01,0x02,0xBC,0x1B,
	0xFF,0x07,0x07,0x1D,
	0x01,0xF8,0x47,0xB9,
},//5
{
	0x00,0xF6,0x0E,0x5C,
	0xFE,0x07,0x55,0x14,
	0x01,0x03,0x4D,0xDD,
	0xFF,0x06,0xA3,0xC7,
	0x01,0xF8,0xAA,0xEC,
},//6
{
	0x00,0xF5,0xD7,0x89,
	0xFE,0x06,0xF7,0x4A,
	0x01,0x03,0xE2,0x9B,
	0xFF,0x06,0x45,0xDC,
	0x01,0xF9,0x08,0xB6,
},//7
{
	0x00,0xF5,0x98,0x1D,
	0xFE,0x06,0x9E,0x9E,
	0x01,0x04,0x7A,0xD1,
	0xFF,0x05,0xED,0x11,
	0x01,0xF9,0x61,0x62,
},//8
{
	0x00,0xF5,0x4F,0xE0,
	0xFE,0x06,0x4A,0xCC,
	0x01,0x05,0x16,0xFE,
	0xFF,0x05,0x99,0x22,
	0x01,0xF9,0xB5,0x34,
},//9
{
	0x00,0xF4,0xFE,0x92,
	0xFE,0x05,0xFB,0x91,
	0x01,0x05,0xB7,0xA3,
	0xFF,0x05,0x49,0xCB,
	0x01,0xFA,0x04,0x6F,
},//10

{
	0x00,0xF6,0xAA,0x66,
	0xFE,0x0A,0x8F,0x2C,
	0x00,0xFF,0x76,0x98,
	0xFF,0x09,0xDF,0x01,
	0x01,0xF5,0x70,0xD4,
},//-1
{
	0x00,0xF6,0xA1,0x44,
	0xFE,0x0B,0x21,0xA7,
	0x00,0xFE,0xED,0x0D,
	0xFF,0x0A,0x71,0xB0,
	0x01,0xF4,0xDE,0x59,
},//-2
{
	0x00,0xF6,0x90,0x60,
	0xFE,0x0B,0xBC,0x72,
	0x00,0xFE,0x62,0xEF,
	0xFF,0x0B,0x0C,0xB1,
	0x01,0xF4,0x43,0x8E,
},//-3
{
	0x00,0xF6,0x77,0xB3,
	0xFE,0x0C,0x60,0x01,
	0x00,0xFD,0xD7,0xD3,
	0xFF,0x0B,0xB0,0x7A,
	0x01,0xF3,0x9F,0xFF,
},//-4
{
	0x00,0xF6,0x57,0x32,
	0xFE,0x0D,0x0C,0xCD,
	0x00,0xFD,0x4B,0x4B,
	0xFF,0x0C,0x5D,0x82,
	0x01,0xF2,0xF3,0x33,
},//-5
{
	0x00,0xF6,0x2E,0xCC,
	0xFE,0x0D,0xC3,0x54,
	0x00,0xFC,0xBC,0xEA,
	0xFF,0x0D,0x14,0x49,
	0x01,0xF2,0x3C,0xAC,
},//-6
{
	0x00,0xF5,0xFE,0x69,
	0xFE,0x0E,0x84,0x1A,
	0x00,0xFC,0x2C,0x43,
	0xFF,0x0D,0xD5,0x53,
	0x01,0xF1,0x7B,0xE6,
},//-7
{
	0x00,0xF5,0xC5,0xEE,
	0xFE,0x0F,0x4F,0xAA,
	0x00,0xFB,0x98,0xE8,
	0xFF,0x0E,0xA1,0x2A,
	0x01,0xF0,0xB0,0x56,
},//-8
{
	0x00,0xF5,0x85,0x37,
	0xFE,0x10,0x26,0x94,
	0x00,0xFB,0x02,0x69,
	0xFF,0x0F,0x78,0x60,
	0x01,0xEF,0xD9,0x6C,
},//-9
{
	0x00,0xF5,0x3C,0x1E,
	0xFE,0x11,0x09,0x70,
	0x00,0xFA,0x68,0x56,
	0xFF,0x10,0x5B,0x8B,
	0x01,0xEE,0xF6,0x90,
},//-10
};
// EQ 600
DSP_REG_VALUE_TYPE DSP_REG_EQ_600_VALUE[21][REG_EQ_BYTE*5] = {
{
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x01,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,  
},//0
{
	0x00,0xF2,0x18,0xB6,
	0xFE,0x0E,0xA4,0x56,
	0x01,0x00,0xCC,0xAA,
	0xFF,0x0D,0x1A,0xA0,
	0x01,0xF1,0x5B,0xAA,
},//1
{
	0x00,0xF2,0x01,0xE5,
	0xFE,0x0D,0xED,0xC9,
	0x01,0x01,0x9A,0x98,
	0xFF,0x0C,0x63,0x83,
	0x01,0xF2,0x12,0x37,
},//2
{
	0x00,0xF1,0xDF,0x6A,
	0xFE,0x0D,0x40,0xF8,
	0x01,0x02,0x6A,0x6D,
	0xFF,0x0B,0xB6,0x29,
	0x01,0xF2,0xBF,0x08,
},//3
{
	0x00,0xF1,0xB1,0x1D,
	0xFE,0x0C,0x9D,0x63,
	0x01,0x03,0x3C,0xD0,
	0xFF,0x0B,0x12,0x12,
	0x01,0xF3,0x62,0x9D,
},//4
{
	0x00,0xF1,0x76,0xCF,
	0xFE,0x0C,0x02,0x92,
	0x01,0x04,0x12,0x6B,
	0xFF,0x0A,0x76,0xC6,
	0x01,0xF3,0xFD,0x6E,
},//5
{
	0x00,0xF1,0x30,0x44,
	0xFE,0x0B,0x70,0x11,
	0x01,0x04,0xEB,0xEA,
	0xFF,0x09,0xE3,0xD2,
	0x01,0xF4,0x8F,0xEF,
},//6
{
	0x00,0xF0,0xDD,0x3A,
	0xFE,0x0A,0xE5,0x74,
	0x01,0x05,0xC9,0xFE,
	0xFF,0x09,0x58,0xC7,
	0x01,0xF5,0x1A,0x8C,
},//7
{
	0x00,0xF0,0x7D,0x65,
	0xFE,0x0A,0x62,0x52,
	0x01,0x06,0xAD,0x5E,
	0xFF,0x08,0xD5,0x3D,
	0x01,0xF5,0x9D,0xAE,
},//8
{
	0x00,0xF0,0x10,0x6C,
	0xFE,0x09,0xE6,0x46,
	0x01,0x07,0x96,0xC5,
	0xFF,0x08,0x58,0xCF,
	0x01,0xF6,0x19,0xBA,
},//9
{
	0x00,0xEF,0x95,0xEF,
	0xFE,0x09,0x70,0xF2,
	0x01,0x08,0x86,0xF3,
	0xFF,0x07,0xE3,0x1E,
	0x01,0xF6,0x8F,0x0E,
},//10

{
	0x00,0xF2,0x23,0xCB,
	0xFE,0x10,0x30,0xB8,
	0x00,0xFF,0x33,0xF9,
	0xFF,0x0E,0xA8,0x3C,
	0x01,0xEF,0xCF,0x48,
},//-1
{
	0x00,0xF2,0x18,0x33,
	0xFE,0x11,0x07,0xA8,
	0x00,0xFE,0x67,0xF7,
	0xFF,0x0F,0x7F,0xD7,
	0x01,0xEE,0xF8,0x58,
},//-2
{
	0x00,0xF2,0x01,0x39,
	0xFE,0x11,0xEA,0x8A,
	0x00,0xFD,0x9B,0x5B,
	0xFF,0x10,0x63,0x6C,
	0x01,0xEE,0x15,0x76,
},//-3
{
	0x00,0xF1,0xDE,0xDC,
	0xFE,0x12,0xD9,0xFB,
	0x00,0xFC,0xCD,0x89,
	0xFF,0x11,0x53,0x9B,
	0x01,0xED,0x26,0x05,
},//-4
{
	0x00,0xF1,0xB1,0x12,
	0xFE,0x13,0xD6,0xA0,
	0x00,0xFB,0xFD,0xE7,
	0xFF,0x12,0x51,0x07,
	0x01,0xEC,0x29,0x60,
},//-5
{
	0x00,0xF1,0x77,0xC9,
	0xFE,0x14,0xE1,0x23,
	0x00,0xFB,0x2B,0xDA,
	0xFF,0x13,0x5C,0x5D,
	0x01,0xEB,0x1E,0xDD,
},//-6
{
	0x00,0xF1,0x32,0xE9,
	0xFE,0x15,0xFA,0x36,
	0x00,0xFA,0x56,0xC7,
	0xFF,0x14,0x76,0x4F,
	0x01,0xEA,0x05,0xCA,
},//-7
{
	0x00,0xF0,0xE2,0x53,
	0xFE,0x17,0x22,0x94,
	0x00,0xF9,0x7E,0x16,
	0xFF,0x15,0x9F,0x97,
	0x01,0xE8,0xDD,0x6C,
},//-8
{
	0x00,0xF0,0x85,0xE1,
	0xFE,0x18,0x5A,0xFA,
	0x00,0xF8,0xA1,0x2A,
	0xFF,0x16,0xD8,0xF5,
	0x01,0xE7,0xA5,0x06,
},//-9
{
	0x00,0xF0,0x1D,0x63,
	0xFE,0x19,0xA4,0x32,
	0x00,0xF7,0xBF,0x6C,
	0xFF,0x18,0x23,0x31,
	0x01,0xE6,0x5B,0xCE,
},//-10
};

// EQ 1000
DSP_REG_VALUE_TYPE DSP_REG_EQ_1000_VALUE[21][REG_EQ_BYTE*5] = {
{
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x01,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,  
},//0
{
	0x00,0xE9,0x41,0x95,
	0xFE,0x19,0xA2,0x03,
	0x01,0x01,0x4E,0xCC,
	0xFF,0x15,0x6F,0x9F,
	0x01,0xE6,0x5D,0xFD,
},//1
{
	0x00,0xE9,0x16,0xEA,
	0xFE,0x18,0x7D,0xBA,
	0x01,0x02,0xA0,0x46,
	0xFF,0x14,0x48,0xD0,
	0x01,0xE7,0x82,0x46,
},//2
{
	0x00,0xE8,0xD9,0x57,
	0xFE,0x17,0x68,0x86,
	0x01,0x03,0xF5,0x72,
	0xFF,0x13,0x31,0x38,
	0x01,0xE8,0x97,0x7A,
},//3
{
	0x00,0xE8,0x88,0x8C,
	0xFE,0x16,0x61,0xB3,
	0x01,0x05,0x4F,0x54,
	0xFF,0x12,0x28,0x20,
	0x01,0xE9,0x9E,0x4D,
},//4
{
	0x00,0xE8,0x24,0x2F,
	0xFE,0x15,0x68,0x8F,
	0x01,0x06,0xAE,0xFC,
	0xFF,0x11,0x2C,0xD5,
	0x01,0xEA,0x97,0x71,
},//5
{
	0x00,0xE7,0xAB,0xD4,
	0xFE,0x14,0x7C,0x72,
	0x01,0x08,0x15,0x7D,
	0xFF,0x10,0x3E,0xAF,
	0x01,0xEB,0x83,0x8E,
},//6
{
	0x00,0xE7,0x1F,0x02,
	0xFE,0x13,0x9C,0xB9,
	0x01,0x09,0x83,0xF7,
	0xFF,0x0F,0x5D,0x08,
	0x01,0xEC,0x63,0x47,
},//7
{
	0x00,0xE6,0x7D,0x30,
	0xFE,0x12,0xC8,0xC8,
	0x01,0x0A,0xFB,0x8D,
	0xFF,0x0E,0x87,0x43,
	0x01,0xED,0x37,0x38,
},//8
{
	0x00,0xE5,0xC5,0xC5,
	0xFE,0x12,0x00,0x0C,
	0x01,0x0C,0x7D,0x70,
	0xFF,0x0D,0xBC,0xCB,
	0x01,0xED,0xFF,0xF4,
},//9
{
	0x00,0xE4,0xF8,0x18,
	0xFE,0x11,0x41,0xF3,
	0x01,0x0E,0x0A,0xD9,
	0xFF,0x0C,0xFD,0x0F,
	0x01,0xEE,0xBE,0x0D,
},//10

{
	0x00,0xE9,0x5F,0x2D,
	0xFE,0x1C,0x1A,0xD9,
	0x00,0xFE,0xB2,0xE8,
	0xFF,0x17,0xED,0xEB,
	0x01,0xE3,0xE5,0x27,
},//-1
{
	0x00,0xE9,0x52,0x78,
	0xFE,0x1D,0x70,0xF6,
	0x00,0xFD,0x66,0x8D,
	0xFF,0x19,0x46,0xFB,
	0x01,0xE2,0x8F,0x0A,
},//-2
{
	0x00,0xE9,0x33,0x98,
	0xFE,0x1E,0xD9,0x4A,
	0x00,0xFC,0x19,0xFD,
	0xFF,0x1A,0xB2,0x6B,
	0x01,0xE1,0x26,0xB6,
},//-3
{
	0x00,0xE9,0x02,0x9F,
	0xFE,0x20,0x54,0xAE,
	0x00,0xFA,0xCC,0x4B,
	0xFF,0x1C,0x31,0x16,
	0x01,0xDF,0xAB,0x52,
},//-4
{
	0x00,0xE8,0xBF,0x96,
	0xFE,0x21,0xE4,0x03,
	0x00,0xF9,0x7C,0x8D,
	0xFF,0x1D,0xC3,0xDD,
	0x01,0xDE,0x1B,0xFD,
},//-5
{
	0x00,0xE8,0x6A,0x7B,
	0xFE,0x23,0x88,0x2F,
	0x00,0xF8,0x29,0xDC,
	0xFF,0x1F,0x6B,0xA9,
	0x01,0xDC,0x77,0xD1,
},//-6
{
	0x00,0xE8,0x03,0x42,
	0xFE,0x25,0x42,0x1E,
	0x00,0xF6,0xD3,0x56,
	0xFF,0x21,0x29,0x68,
	0x01,0xDA,0xBD,0xE2,
},//-7
{
	0x00,0xE7,0x89,0xD7,
	0xFE,0x27,0x12,0xC2,
	0x00,0xF5,0x78,0x1B,
	0xFF,0x22,0xFE,0x0F,
	0x01,0xD8,0xED,0x3E,
},//-8
{
	0x00,0xE6,0xFE,0x1D,
	0xFE,0x28,0xFB,0x12,
	0x00,0xF4,0x17,0x4E,
	0xFF,0x24,0xEA,0x95,
	0x01,0xD7,0x04,0xEE,
},//-9
{
	0x00,0xE6,0x5F,0xEF,
	0xFE,0x2A,0xFC,0x0A,
	0x00,0xF2,0xB0,0x16,
	0xFF,0x26,0xEF,0xFB,
	0x01,0xD5,0x03,0xF6,
},//-10
};
// EQ 3000
DSP_REG_VALUE_TYPE DSP_REG_EQ_3000_VALUE[21][REG_EQ_BYTE*5] = {
{
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x01,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,  
},//0
{
	0x00,0xC2,0x4E,0xE7,
	0xFE,0x5C,0xB1,0x30,
	0x01,0x03,0x8C,0x1F,
	0xFF,0x3A,0x24,0xFA,
	0x01,0xA3,0x4E,0xD0,
},//1
{
	0x00,0xC1,0x9A,0xF4,
	0xFE,0x5A,0x02,0xEB,
	0x01,0x07,0x26,0xE2,
	0xFF,0x37,0x3E,0x2A,
	0x01,0xA5,0xFD,0x15,
},//2
{
	0x00,0xC0,0xB5,0x3C,
	0xFE,0x57,0x72,0xF0,
	0x01,0x0A,0xD2,0xA1,
	0xFF,0x34,0x78,0x23,
	0x01,0xA8,0x8D,0x10,
},//3
{
	0x00,0xBF,0x9C,0x4F,
	0xFE,0x55,0x00,0x4C,
	0x01,0x0E,0x91,0xD3,
	0xFF,0x31,0xD1,0xDE,
	0x01,0xAA,0xFF,0xB4,
},//4
{
	0x00,0xBE,0x4E,0xA0,
	0xFE,0x52,0xAA,0x0C,
	0x01,0x12,0x67,0x0D,
	0xFF,0x2F,0x4A,0x53,
	0x01,0xAD,0x55,0xF4,
},//5
{
	0x00,0xBC,0xCA,0x85,
	0xFE,0x50,0x6F,0x38,
	0x01,0x16,0x55,0x04,
	0xFF,0x2C,0xE0,0x77,
	0x01,0xAF,0x90,0xC8,
},//6
{
	0x00,0xBB,0x0E,0x30,
	0xFE,0x4E,0x4E,0xDB,
	0x01,0x1A,0x5E,0x91,
	0xFF,0x2A,0x93,0x40,
	0x01,0xB1,0xB1,0x25,
},//7
{
	0x00,0xB9,0x17,0xB1,
	0xFE,0x4C,0x47,0xFF,
	0x01,0x1E,0x86,0xAB,
	0xFF,0x28,0x61,0xA4,
	0x01,0xB3,0xB8,0x01,
},//8
{
	0x00,0xB6,0xE4,0xF1,
	0xFE,0x4A,0x59,0xB1,
	0x01,0x22,0xD0,0x73,
	0xFF,0x26,0x4A,0x9C,
	0x01,0xB5,0xA6,0x4F,
},//9
{
	0x00,0xB4,0x73,0xB0,
	0xFE,0x48,0x83,0x01,
	0x01,0x27,0x3F,0x2D,
	0xFF,0x24,0x4D,0x24,
	0x01,0xB7,0x7C,0xFF,
},//10

{
	0x00,0xC3,0x26,0xC1,
	0xFE,0x62,0x6C,0x4A,
	0x00,0xFC,0x80,0x4A,
	0xFF,0x40,0x58,0xF5,
	0x01,0x9D,0x93,0xB6,
},//-1
{
	0x00,0xC3,0x4D,0x11,
	0xFE,0x65,0x7A,0xE9,
	0x00,0xF9,0x0A,0xE0,
	0xFF,0x43,0xA8,0x0F,
	0x01,0x9A,0x85,0x17,
},//-2
{
	0x00,0xC3,0x46,0x72,
	0xFE,0x68,0xAB,0x62,
	0x00,0xF5,0x9D,0xC0,
	0xFF,0x47,0x1B,0xCE,
	0x01,0x97,0x54,0x9E,
},//-3
{
	0x00,0xC3,0x13,0xEC,
	0xFE,0x6B,0xFE,0x83,
	0x00,0xF2,0x37,0x05,
	0xFF,0x4A,0xB5,0x0F,
	0x01,0x94,0x01,0x7D,
},//-4
{
	0x00,0xC2,0xB6,0x78,
	0xFE,0x6F,0x75,0x0D,
	0x00,0xEE,0xD4,0xE4,
	0xFF,0x4E,0x74,0xA4,
	0x01,0x90,0x8A,0xF3,
},//-5
{
	0x00,0xC2,0x2F,0x02,
	0xFE,0x73,0x0F,0xB1,
	0x00,0xEB,0x75,0xB1,
	0xFF,0x52,0x5B,0x4D,
	0x01,0x8C,0xF0,0x4F,
},//-6
{
	0x00,0xC1,0x7E,0x6F,
	0xFE,0x76,0xCF,0x11,
	0x00,0xE8,0x17,0xD8,
	0xFF,0x56,0x69,0xB8,
	0x01,0x89,0x30,0xEF,
},//-7
{
	0x00,0xC0,0xA5,0x9C,
	0xFE,0x7A,0xB3,0xBA,
	0x00,0xE4,0xB9,0xE5,
	0xFF,0x5A,0xA0,0x7F,
	0x01,0x85,0x4C,0x46,
},//-8
{
	0x00,0xBF,0xA5,0x60,
	0xFE,0x7E,0xBE,0x23,
	0x00,0xE1,0x5A,0x7D,
	0xFF,0x5F,0x00,0x23,
	0x01,0x81,0x41,0xDD,
},//-9
{
	0x00,0xBE,0x7E,0x92,
	0xFE,0x82,0xEE,0xAE,
	0x00,0xDD,0xF8,0x62,
	0xFF,0x63,0x89,0x0C,
	0x01,0x7D,0x11,0x52,
},//-10
};
// EQ 6000
DSP_REG_VALUE_TYPE DSP_REG_EQ_6000_VALUE[21][REG_EQ_BYTE*5] = {
{
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x01,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,  
},//0
{
	0x00,0x98,0x04,0xE6,
	0xFE,0xDB,0x42,0x55,
	0x01,0x05,0xFA,0xA1,
	0xFF,0x62,0x00,0x79,
	0x01,0x24,0xBD,0xAB,
},//1
{
	0x00,0x96,0x5F,0x16,
	0xFE,0xD8,0x17,0x39,
	0x01,0x0C,0x1B,0x85,
	0xFF,0x5D,0x85,0x65,
	0x01,0x27,0xE8,0xC7,
},//2
{
	0x00,0x94,0x66,0x4C,
	0xFE,0xD5,0x09,0x36,
	0x01,0x12,0x66,0x3E,
	0xFF,0x59,0x33,0x76,
	0x01,0x2A,0xF6,0xCA,
},//3
{
	0x00,0x92,0x17,0x23,
	0xFE,0xD2,0x17,0xFB,
	0x01,0x18,0xDE,0xA1,
	0xFF,0x55,0x0A,0x3C,
	0x01,0x2D,0xE8,0x05,
},//4
{
	0x00,0x8F,0x6E,0x0F,
	0xFE,0xCF,0x43,0x27,
	0x01,0x1F,0x88,0xC5,
	0xFF,0x51,0x09,0x2C,
	0x01,0x30,0xBC,0xD9,
},//5
{
	0x00,0x8C,0x67,0x55,
	0xFE,0xCC,0x8A,0x48,
	0x01,0x26,0x69,0x04,
	0xFF,0x4D,0x2F,0xA6,
	0x01,0x33,0x75,0xB8,
},//6
{
	0x00,0x88,0xFF,0x07,
	0xFE,0xC9,0xEC,0xE0,
	0x01,0x2D,0x84,0x02,
	0xFF,0x49,0x7C,0xF7,
	0x01,0x36,0x13,0x20,
},//7
{
	0x00,0x85,0x31,0x00,
	0xFE,0xC7,0x6A,0x61,
	0x01,0x34,0xDE,0xA9,
	0xFF,0x45,0xF0,0x56,
	0x01,0x38,0x95,0x9F,
},//8
{
	0x00,0x80,0xF8,0xDD,
	0xFE,0xC5,0x02,0x35,
	0x01,0x3C,0x7E,0x33,
	0xFF,0x42,0x88,0xF0,
	0x01,0x3A,0xFD,0xCB,
},//9
{
	0x00,0x7C,0x51,0xF8,
	0xFE,0xC2,0xB3,0xBB,
	0x01,0x44,0x68,0x27,
	0xFF,0x3F,0x45,0xE1,
	0x01,0x3D,0x4C,0x45,
},//10

{
	0x00,0x9A,0x64,0x69,
	0xFE,0xE1,0xF0,0xB0,
	0x00,0xFA,0x28,0x4E,
	0xFF,0x6B,0x73,0x49,
	0x01,0x1E,0x0F,0x50,
},//-1
{
	0x00,0x9B,0x24,0x3B,
	0xFE,0xE5,0x74,0x26,
	0x00,0xF4,0x70,0x74,
	0xFF,0x70,0x6B,0x51,
	0x01,0x1A,0x8B,0xDA,
},//-2
{
	0x00,0x9B,0x9D,0x54,
	0xFE,0xE9,0x15,0x1F,
	0x00,0xEE,0xD5,0x98,
	0xFF,0x75,0x8D,0x14,
	0x01,0x16,0xEA,0xE1,
},//-3
{
	0x00,0x9B,0xD2,0x85,
	0xFE,0xEC,0xD3,0x76,
	0x00,0xE9,0x55,0x1B,
	0xFF,0x7A,0xD8,0x60,
	0x01,0x13,0x2C,0x8A,
},//-4
{
	0x00,0x9B,0xC6,0x8F,
	0xFE,0xF0,0xAE,0xEC,
	0x00,0xE3,0xEC,0x95,
	0xFF,0x80,0x4C,0xDC,
	0x01,0x0F,0x51,0x14,
},//-5
{
	0x00,0x9B,0x7C,0x24,
	0xFE,0xF4,0xA7,0x25,
	0x00,0xDE,0x99,0xD9,
	0xFF,0x85,0xEA,0x03,
	0x01,0x0B,0x58,0xDB,
},//-6
{
	0x00,0x9A,0xF5,0xE8,
	0xFE,0xF8,0xBB,0xA5,
	0x00,0xD9,0x5A,0xEF,
	0xFF,0x8B,0xAF,0x29,
	0x01,0x07,0x44,0x5B,
},//-7
{
	0x00,0x9A,0x36,0x78,
	0xFE,0xFC,0xEB,0xD1,
	0x00,0xD4,0x2E,0x17,
	0xFF,0x91,0x9B,0x71,
	0x01,0x03,0x14,0x2F,
},//-8
{
	0x00,0x99,0x40,0x6B,
	0xFF,0x01,0x36,0xEF,
	0x00,0xCF,0x11,0xC2,
	0xFF,0x97,0xAD,0xD3,
	0x00,0xFE,0xC9,0x11,
},//-9
{
	0x00,0x98,0x16,0x51,
	0xFF,0x05,0x9C,0x21,
	0x00,0xCA,0x04,0x97,
	0xFF,0x9D,0xE5,0x18,
	0x00,0xFA,0x63,0xDF,
},//-10
};
// EQ 12000
DSP_REG_VALUE_TYPE DSP_REG_EQ_12000_VALUE[21][REG_EQ_BYTE*5] = {
{
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x01,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,  
},//0
{
	0x00,0x77,0xC0,0x53,
	0x00,0x00,0x00,0x00,
	0x01,0x07,0xD5,0x9F,
	0xFF,0x80,0x6A,0x0E,
	0x00,0x00,0x00,0x00,
},//1
{
	0x00,0x75,0x20,0x35,
	0x00,0x00,0x00,0x00,
	0x01,0x0F,0xEB,0x10,
	0xFF,0x7A,0xF4,0xBB,
	0x00,0x00,0x00,0x00,
},//2
{
	0x00,0x72,0x12,0x7C,
	0x00,0x00,0x00,0x00,
	0x01,0x18,0x44,0xEF,
	0xFF,0x75,0xA8,0x94,
	0x00,0x00,0x00,0x00,
},//3
{
	0x00,0x6E,0x91,0xD6,
	0x00,0x00,0x00,0x00,
	0x01,0x20,0xE8,0x34,
	0xFF,0x70,0x85,0xF5,
	0x00,0x00,0x00,0x00,
},//4
{
	0x00,0x6A,0x98,0xB9,
	0x00,0x00,0x00,0x00,
	0x01,0x29,0xDA,0x36,
	0xFF,0x6B,0x8D,0x11,
	0x00,0x00,0x00,0x00,
},//5
{
	0x00,0x66,0x21,0x60,
	0x00,0x00,0x00,0x00,
	0x01,0x33,0x20,0xAC,
	0xFF,0x66,0xBD,0xF4,
	0x00,0x00,0x00,0x00,
},//6
{
	0x00,0x61,0x25,0xBE,
	0x00,0x00,0x00,0x00,
	0x01,0x3C,0xC1,0xB7,
	0xFF,0x62,0x18,0x8A,
	0x00,0x00,0x00,0x00,
},//7
{
	0x00,0x5B,0x9F,0x82,
	0x00,0x00,0x00,0x00,
	0x01,0x46,0xC3,0xE2,
	0xFF,0x5D,0x9C,0x9C,
	0x00,0x00,0x00,0x00,
},//8
{
	0x00,0x55,0x88,0x06,
	0x00,0x00,0x00,0x00,
	0x01,0x51,0x2E,0x25,
	0xFF,0x59,0x49,0xD5,
	0x00,0x00,0x00,0x00,
},//9
{
	0x00,0x4E,0xD8,0x4D,
	0x00,0x00,0x00,0x00,
	0x01,0x5C,0x07,0xEE,
	0xFF,0x55,0x1F,0xC5,
	0x00,0x00,0x00,0x00,
},//10

{
	0x00,0x7B,0xCC,0x10,
	0x00,0x00,0x00,0x00,
	0x00,0xF8,0x65,0xEF,
	0xFF,0x8B,0xCE,0x01,
	0x00,0x00,0x00,0x00,
},//-1
{
	0x00,0x7D,0x41,0x6D,
	0x00,0x00,0x00,0x00,
	0x00,0xF1,0x03,0x7E,
	0xFF,0x91,0xBB,0x15,
	0x00,0x00,0x00,0x00,
},//-2
{
	0x00,0x7E,0x5C,0xB4,
	0x00,0x00,0x00,0x00,
	0x00,0xE9,0xD5,0x0F,
	0xFF,0x97,0xCE,0x3D,
	0x00,0x00,0x00,0x00,
},//-3
{
	0x00,0x7F,0x22,0x6C,
	0x00,0x00,0x00,0x00,
	0x00,0xE2,0xD7,0x54,
	0xFF,0x9E,0x06,0x40,
	0x00,0x00,0x00,0x00,
},//-4
{
	0x00,0x7F,0x96,0xFF,
	0x00,0x00,0x00,0x00,
	0x00,0xDC,0x07,0x49,
	0xFF,0xA4,0x61,0xB8,
	0x00,0x00,0x00,0x00,
},//-5
{
	0x00,0x7F,0xBE,0xBE,
	0x00,0x00,0x00,0x00,
	0x00,0xD5,0x62,0x34,
	0xFF,0xAA,0xDF,0x0E,
	0x00,0x00,0x00,0x00,
},//-6
{
	0x00,0x7F,0x9D,0xE3,
	0x00,0x00,0x00,0x00,
	0x00,0xCE,0xE5,0x9F,
	0xFF,0xB1,0x7C,0x7E,
	0x00,0x00,0x00,0x00,
},//-7
{
	0x00,0x7F,0x38,0x94,
	0x00,0x00,0x00,0x00,
	0x00,0xC8,0x8F,0x58,
	0xFF,0xB8,0x38,0x15,
	0x00,0x00,0x00,0x00,
},//-8
{
	0x00,0x7E,0x92,0xE1,
	0x00,0x00,0x00,0x00,
	0x00,0xC2,0x5D,0x69,
	0xFF,0xBF,0x0F,0xB6,
	0x00,0x00,0x00,0x00,
},//-9
{
	0x00,0x7D,0xB0,0xCD,
	0x00,0x00,0x00,0x00,
	0x00,0xBC,0x4E,0x1A,
	0xFF,0xC6,0x01,0x19,
	0x00,0x00,0x00,0x00,
},//-10
};

// EQ 14000
DSP_REG_VALUE_TYPE DSP_REG_EQ_14000_VALUE[21][REG_EQ_BYTE*5] = {
{
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x01,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,  
},//0
{
	0x00,0x7B,0x42,0x69,
	0x00,0x64,0x22,0x93,
	0x01,0x07,0xA1,0xFB,
	0xFF,0x7D,0x1B,0x9C,
	0xFF,0x9B,0xDD,0x6D,
},//1
{
	0x00,0x78,0xC0,0x49,
	0x00,0x65,0x85,0xD3,
	0x01,0x0F,0x80,0xAF,
	0xFF,0x77,0xBF,0x08,
	0xFF,0x9A,0x7A,0x2D,
},//2
{
	0x00,0x75,0xD3,0x8B,
	0x00,0x66,0xDE,0x5B,
	0x01,0x17,0xA0,0x99,
	0xFF,0x72,0x8B,0xDC,
	0xFF,0x99,0x21,0xA5,
},//3
{
	0x00,0x72,0x77,0x17,
	0x00,0x68,0x2C,0x1B,
	0x01,0x20,0x06,0x8D,
	0xFF,0x6D,0x82,0x5B,
	0xFF,0x97,0xD3,0xE5,
},//4
{
	0x00,0x6E,0xA5,0xA1,
	0x00,0x69,0x6F,0x0A,
	0x01,0x28,0xB7,0xBE,
	0xFF,0x68,0xA2,0xA1,
	0xFF,0x96,0x90,0xF6,
},//5
{
	0x00,0x6A,0x59,0xA0,
	0x00,0x6A,0xA7,0x2C,
	0x01,0x31,0xB9,0xBA,
	0xFF,0x63,0xEC,0xA6,
	0xFF,0x95,0x58,0xD4,
},//6
{
	0x00,0x65,0x8D,0x4A,
	0x00,0x6B,0xD4,0x8A,
	0x01,0x3B,0x12,0x76,
	0xFF,0x5F,0x60,0x40,
	0xFF,0x94,0x2B,0x76,
},//7
{
	0x00,0x60,0x3A,0x8D,
	0x00,0x6C,0xF7,0x38,
	0x01,0x44,0xC8,0x4C,
	0xFF,0x5A,0xFD,0x26,
	0xFF,0x93,0x08,0xC8,
},//8
{
	0x00,0x5A,0x5B,0x0A,
	0x00,0x6E,0x0F,0x50,
	0x01,0x4E,0xE2,0x02,
	0xFF,0x56,0xC2,0xF4,
	0xFF,0x91,0xF0,0xB0,
},//9
{
	0x00,0x53,0xE8,0x0B,
	0x00,0x6F,0x1C,0xF3,
	0x01,0x59,0x66,0xCD,
	0xFF,0x52,0xB1,0x29,
	0xFF,0x90,0xE3,0x0D,
},//10
{
	0x00,0x7F,0x1A,0x40,
	0x00,0x61,0x3C,0x66,
	0x00,0xF8,0x96,0x98,
	0xFF,0x88,0x4F,0x29,
	0xFF,0x9E,0xC3,0x9A,
},//-1
{
	0x00,0x80,0x79,0x48,
	0x00,0x5F,0xB9,0xD1,
	0x00,0xF1,0x61,0xED,
	0xFF,0x8E,0x24,0xCB,
	0xFF,0xA0,0x46,0x2F,
},//-2
{
	0x00,0x81,0x80,0x5E,
	0x00,0x5E,0x2D,0x37,
	0x00,0xEA,0x5E,0x7C,
	0xFF,0x94,0x21,0x26,
	0xFF,0xA1,0xD2,0xC9,
},//-3
{
	0x00,0x82,0x33,0xD5,
	0x00,0x5C,0x96,0xE0,
	0x00,0xE3,0x89,0x0C,
	0xFF,0x9A,0x43,0x1F,
	0xFF,0xA3,0x69,0x20,
},//-4
{
	0x00,0x82,0x97,0xE7,
	0x00,0x5A,0xF7,0x23,
	0x00,0xDC,0xDE,0xAE,
	0xFF,0xA0,0x89,0x6B,
	0xFF,0xA5,0x08,0xDD,
},//-5
{
	0x00,0x82,0xB0,0xB7,
	0x00,0x59,0x4E,0x61,
	0x00,0xD6,0x5C,0xBB,
	0xFF,0xA6,0xF2,0x8E,
	0xFF,0xA6,0xB1,0x9F,
},//-6
{
	0x00,0x82,0x82,0x4F,
	0x00,0x57,0x9D,0x08,
	0x00,0xD0,0x00,0xD0,
	0xFF,0xAD,0x7C,0xE1,
	0xFF,0xA8,0x62,0xF8,
},//-7
{
	0x00,0x82,0x10,0xA9,
	0x00,0x55,0xE3,0x92,
	0x00,0xC9,0xC8,0xC9,
	0xFF,0xB4,0x26,0x8E,
	0xFF,0xAA,0x1C,0x6E,
},//-8
{
	0x00,0x81,0x5F,0xAE,
	0x00,0x54,0x22,0x84,
	0x00,0xC3,0xB2,0xC3,
	0xFF,0xBA,0xED,0x8F,
	0xFF,0xAB,0xDD,0x7C,
},//-9
{
	0x00,0x80,0x73,0x35,
	0x00,0x52,0x5A,0x70,
	0x00,0xBD,0xBD,0x13,
	0xFF,0xC1,0xCF,0xB7,
	0xFF,0xAD,0xA5,0x90,
},//-10
};

// EQ 16000
DSP_REG_VALUE_TYPE DSP_REG_EQ_16000_VALUE[21][REG_EQ_BYTE*5] = {
{
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x01,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,  
},//0
{
	0x00,0x85,0xE7,0x04,
	0x00,0xC6,0x76,0x2A,
	0x01,0x07,0x05,0x50,
	0xFF,0x73,0x13,0xAC,
	0xFF,0x39,0x89,0xD6,
},//1
{
	0x00,0x83,0xBB,0xB9,
	0x00,0xC8,0xFD,0x13,
	0x01,0x0E,0x3E,0x6D,
	0xFF,0x6E,0x05,0xD9,
	0xFF,0x37,0x02,0xED,
},//2
{
	0x00,0x81,0x2E,0xBA,
	0x00,0xCB,0x6F,0x1A,
	0x01,0x15,0xAF,0x7A,
	0xFF,0x69,0x21,0xCC,
	0xFF,0x34,0x90,0xE6,
},//3
{
	0x00,0x7E,0x3B,0x98,
	0x00,0xCD,0xCC,0x40,
	0x01,0x1D,0x5C,0xE7,
	0xFF,0x64,0x67,0x81,
	0xFF,0x32,0x33,0xC0,
},//4
{
	0x00,0x7A,0xDD,0xB8,
	0x00,0xD0,0x14,0x98,
	0x01,0x25,0x4B,0x78,
	0xFF,0x5F,0xD6,0xD0,
	0xFF,0x2F,0xEB,0x68,
},//5
{
	0x00,0x77,0x10,0x44,
	0x00,0xD2,0x48,0x46,
	0x01,0x2D,0x80,0x48,
	0xFF,0x5B,0x6F,0x75,
	0xFF,0x2D,0xB7,0xBA,
},//6
{
	0x00,0x72,0xCE,0x2D,
	0x00,0xD4,0x67,0x7A,
	0x01,0x36,0x00,0xC7,
	0xFF,0x57,0x31,0x0C,
	0xFF,0x2B,0x98,0x86,
},//7
{
	0x00,0x6E,0x12,0x22,
	0x00,0xD6,0x72,0x73,
	0x01,0x3E,0xD2,0xC4,
	0xFF,0x53,0x1B,0x1A,
	0xFF,0x29,0x8D,0x8D,
},//8
{
	0x00,0x68,0xD6,0x8B,
	0x00,0xD8,0x69,0x7C,
	0x01,0x47,0xFC,0x6D,
	0xFF,0x4F,0x2D,0x07,
	0xFF,0x27,0x96,0x84,
},//9
{
	0x00,0x63,0x15,0x82,
	0x00,0xDA,0x4C,0xEA,
	0x01,0x51,0x84,0x53,
	0xFF,0x4B,0x66,0x2B,
	0xFF,0x25,0xB3,0x16,
},//10
{
	0x00,0x89,0x29,0x5A,
	0x00,0xC1,0x2A,0x02,
	0x00,0xF9,0x2A,0xAA,
	0xFF,0x7D,0xAB,0xFC,
	0xFF,0x3E,0xD5,0xFE,
},//-1
{
	0x00,0x8A,0x48,0x77,
	0x00,0xBE,0x65,0x1E,
	0x00,0xF2,0x81,0xC4,
	0xFF,0x83,0x35,0xC4,
	0xFF,0x41,0x9A,0xE2,
},//-2
{
	0x00,0x8B,0x16,0x0E,
	0x00,0xBB,0x8C,0x0F,
	0x00,0xEC,0x02,0x0F,
	0xFF,0x88,0xE7,0xE3,
	0xFF,0x44,0x73,0xF1,
},//-3
{
	0x00,0x8B,0x95,0xDD,
	0x00,0xB8,0x9F,0x37,
	0x00,0xE5,0xA8,0x90,
	0xFF,0x8E,0xC1,0x93,
	0xFF,0x47,0x60,0xC9,
},//-4
{
	0x00,0x8B,0xCB,0x8E,
	0x00,0xB5,0x9F,0x10,
	0x00,0xDF,0x72,0x91,
	0xFF,0x94,0xC1,0xE1,
	0xFF,0x4A,0x60,0xF0,
},//-5
{
	0x00,0x8B,0xBA,0xB5,
	0x00,0xB2,0x8C,0x2A,
	0x00,0xD9,0x5D,0x9F,
	0xFF,0x9A,0xE7,0xAC,
	0xFF,0x4D,0x73,0xD6,
},//-6
{
	0x00,0x8B,0x66,0xD6,
	0x00,0xAF,0x67,0x2E,
	0x00,0xD3,0x67,0x86,
	0xFF,0xA1,0x31,0xA4,
	0xFF,0x50,0x98,0xD2,
},//-7
{
	0x00,0x8A,0xD3,0x67,
	0x00,0xAC,0x30,0xDA,
	0x00,0xCD,0x8E,0x4D,
	0xFF,0xA7,0x9E,0x4C,
	0xFF,0x53,0xCF,0x26,
},//-8
{
	0x00,0x8A,0x03,0xD3,
	0x00,0xA8,0xEA,0x06,
	0x00,0xC7,0xD0,0x3A,
	0xFF,0xAE,0x2B,0xF4,
	0xFF,0x57,0x15,0xFA,
},//-9
{
	0x00,0x88,0xFB,0x76,
	0x00,0xA5,0x93,0x9F,
	0x00,0xC2,0x2B,0xC8,
	0xFF,0xB4,0xD8,0xC2,
	0xFF,0x5A,0x6C,0x61,
},//-10
};

#endif


