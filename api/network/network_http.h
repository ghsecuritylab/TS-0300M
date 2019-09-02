#ifndef _NETWORK_HTTP_H_
#define _NETWORK_HTTP_H_


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define http_init_delay() delay();
/*******************************************************************************
 * API
 ******************************************************************************/
void main_thread(void *arg);
void BOARD_InitModuleClock(void);
void delay(void);
void udp_init(void);
#endif

