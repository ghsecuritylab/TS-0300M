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
#include "stdarg.h"
#include "debug.h"
#include "app.h"
#include "fsl_debug_console.h"
#include "fsl_debug_console_conf.h"
#include "fsl_str.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEBUG_TASK_PRIORITY 				2
#define DEBUG_TASK_STACK_SIZE  				512

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
extern int DbgConsole_SendData(uint8_t *ch, size_t size);
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
static void DbgConsole_PrintCallback(char *buf, int32_t *indicator, char val, int len)
{
    int i = 0;

    for (i = 0; i < len; i++)
    {
        if ((*indicator + 1) >= DEBUG_CONSOLE_PRINTF_MAX_LOG_LEN)
        {
//            DbgConsole_SendData((uint8_t *)buf, *indicator);
            *indicator = 0U;
        }

        buf[*indicator] = val;
        (*indicator)++;
    }
}

int debug(const char *formatString, ...){
	
	 
    int logLength = 0U, result = 0U;
	
	if(mode == dbgMode){
		va_list ap;
		char printBuf[DEBUG_CONSOLE_PRINTF_MAX_LOG_LEN] = {0U};

		va_start(ap, formatString);
		/* format print log first */
		logLength = StrFormatPrintf(formatString, ap, printBuf, DbgConsole_PrintCallback);
		/* print log */
		result = DbgConsole_SendData((uint8_t *)printBuf, logLength);
		va_end(ap);
	}
    return result;
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

static void debug_task(void *pvParameters)
{
	char c;
	
	memset(back,'\b',DEBUG_CMD_MAX_LEN+sizeof(topic));
	
	while(1){
		c = GETCHAR();
		
		switch(mode){
			case dbgMode:{
				if(c == '\r' || c == '\n'){
					c = GETCHAR();
					if(c == '\r' || c == '\n'){
						mode = cmdMode;
						PRINTF("\r\n%s",topic);
					}
				}
			}break;
			case cmdMode:{
				if(c == '\r' || c == '\n'){
					PRINTF("\r\n");
					analysis_cmd(cmd);
					index = 0;
					memset(cmd,0,DEBUG_CMD_MAX_LEN + 1);
				}
				else{
					getCharToCmd(c);
					if(c == '\b') PRINTF("\b \b");
				}
				
				if(mode == cmdMode)
					PRINTF("%s%s%s",back,topic,cmd);
			}break;
			default:break;
		}
	}
}
void debug_init(void){

    if (xTaskCreate(debug_task, "debug_task", DEBUG_TASK_STACK_SIZE, null, DEBUG_TASK_PRIORITY, NULL) != pdPASS)
    {
        debug("debug task error\r\n");
    }
}
