#ifndef _DEBUG_H_
#define _DEBUG_H_
#include "fsl_debug_console.h"


#define DEBUG					1
#define DEBUG_FILE				0
#define DEBUG_FUNCTION			0


//#if  defined(DEBUG) && (DEBUG)

#if  defined(DEBUG_FILE) && (DEBUG_FILE)
#define _DBG_FILE 			PRINTF("%s\\",__FILE__)
#else
#define _DBG_FILE 			
#endif

#if  defined(DEBUG_FUNCTION) && (DEBUG_FUNCTION)
#define _DBG_FUNCTION 	PRINTF("%s: ",__FUNCTION__)
#else
#define _DBG_FUNCTION 	
#endif


//#define debug(fmt_s,...) 	{do{_DBG_FILE;_DBG_FUNCTION;PRINTF(fmt_s,##__VA_ARGS__);}while(0);}
//#else
//#define debug(fmt_s, ...) PRINTF("",##__VA_ARGS__)
//#endif

extern int debug(const char *formatString, ...);
extern void debug_init(void);
#endif
