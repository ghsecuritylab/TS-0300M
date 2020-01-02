/**
 *
 *	@name				debug.c
 *	@author 			KT
 *	@date 				2019/08/19
 *	@brief				
 *
 *  @API					
 *
 *  @description   
 *
 **/
/*******************************************************************************
 * includes
 ******************************************************************************/
 /* OS */
#include "FreeRTOS.h"
#include "task.h"
 
/* GLOBAL */
#include "global_config.h"
#include "debug.h"

#include "stdarg.h"

/* SDK */
//#include "fsl_debug_console.h"
//#include "fsl_debug_console_conf.h"
//#include "fsl_str.h"
#include "fsl_lpuart.h"

#include <stdio.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

 
#define DEBUG_TASK_PRIORITY 				(3)
#define DEBUG_TASK_STACK_SIZE  				(1024)

#define DEBUG_CMD_MAX_LEN					16

#define CMD_TOTAL_NUM						5

#define CMD_DEBUG_MODE						"debug"
#define CMD_MEM								"mem"

typedef enum {
	tDebug = 0,
	tMem,
}CommandType_EN;

typedef enum {
	dbgMode , cmdMode
}DebugMode_EN;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void Log_ShellTask(void *pvParameters);
/*******************************************************************************
 * Variables
 ******************************************************************************/
static DebugMode_EN mode = dbgMode;

static const char topic[] = "TS-0300:/ # ";
static char cmd[DEBUG_CMD_MAX_LEN + 1] = {0};
static char back[DEBUG_CMD_MAX_LEN+sizeof(topic)];
static uint8_t index = 0;

static const char command[CMD_TOTAL_NUM][10] = 
{
	CMD_DEBUG_MODE,CMD_MEM

};
/*******************************************************************************
 * Code
 ******************************************************************************/
/**
* @Name  		fputc
* @Author  		KT
* @Description	重定向printf函数
*
*/
int fputc(int c,FILE *stream){
	uint8_t data = c;
	LPUART_WriteBlocking(LOG_SERIAL_PORT,&data,1);
	return c;
}

/**
* @Name  		fgetc
* @Author  		KT
* @Description	重定向getchar函数
*
*/
int getc(FILE *stream){
	uint8_t data;
	LPUART_ReadBlocking(LOG_SERIAL_PORT,&data,1);
	return data;
}


void debug(const char *fmt_s, ...)  
{  
	va_list args;       
	va_start(args,fmt_s); 
	vprintf(fmt_s,args); 
	va_end(args);      
}


static void Log_Init(void){
	if (xTaskCreate(Log_ShellTask, "shell", DEBUG_TASK_STACK_SIZE, null, DEBUG_TASK_PRIORITY, NULL) != pdPASS)
    {
        debug("shell init error\r\n");
    }
}

static void Log_Debug(const char *fmt_s, ...){
	va_list args;       
	va_start(args,fmt_s); 
	vprintf(fmt_s,args); 
	va_end(args);
}


static char getCharToCmd(char c){
	
	if(c == '\b' && index >= 0){
		index = (index == 0) ? 0 : index - 1;
		cmd[index] = 0;
	}
	else if(c >= 0x20 && c <= 0x7E && index < DEBUG_CMD_MAX_LEN){
		cmd[index] = c;
		index++;
	}
	
	return c;
}

static void analysis_cmd(char *cmd){
	uint8_t i;
	CommandType_EN type;
	
	for(i = 0;i<CMD_TOTAL_NUM;i++){
		if(strstr(cmd,command[i]) != null){
			type = (CommandType_EN)i;
			break;
		}
		
		if(i == CMD_TOTAL_NUM -1){
			PRINTF("command invalid!!\r\n");
			return;
		}
	}
	
//	PRINTF("cmd :%s\r\n",command[type]);
	switch(type){
		case tDebug:{
			mode = dbgMode;
		}break;
		case tMem:break;
	}
}

static void Log_ShellTask(void *pvParameters)
{
	char c;
	
	memset(back,'\b',DEBUG_CMD_MAX_LEN+sizeof(topic));
	
	while(1){
		c = getchar();
		printf("%c",c);
		
//		switch(mode){
//			case dbgMode:{
//				if(c == '\r' || c == '\n'){
//					c = GETCHAR();
//					if(c == '\r' || c == '\n'){
//						mode = cmdMode;
//						PRINTF("\r\n%s",topic);
//					}
//				}
//			}break;
//			case cmdMode:{
//				if(c == '\r' || c == '\n'){
//					PRINTF("\r\n");
//					analysis_cmd(cmd);
//					index = 0;
//					memset(cmd,0,DEBUG_CMD_MAX_LEN + 1);
//				}
//				else{
//					getCharToCmd(c);
//					if(c == '\b') PRINTF("\b \b");
//				}
//				
//				if(mode == cmdMode)
//					PRINTF("%s%s%s",back,topic,cmd);
//			}break;
//			default:break;
//		}
	}
}

