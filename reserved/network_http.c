 /**
 *
 *	@FileName								network_http.c
 *	@Author									KT
 *	@CreationTime						2019/06/22
 *	@Description						
 *
 * 	@Include								network_http.h	
 *
 *	@API										 
 *
 **/
/*******************************************************************************
 * includes
 ******************************************************************************/
 /* clib */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

/* OS */
#include "FreeRTOS.h"
#include "timers.h"

/* lwip */
#include "lwip/opt.h"
#include "lwip/netif.h"
#include "lwip/sys.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/ip.h"
#include "lwip/netifapi.h"
#include "lwip/sockets.h"
#include "netif/etharp.h"
#include "ethernetif.h"
#include "board.h"
#include "httpsrv.h"
#include "mdns.h"

#include "app_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* IP default address configuration. */
#define HTTP_DEF_IP_ADDR			{172,16,4,215}
#define HTTP_DEF_IP_ADDR2			{172,16,4,216}
/* Netmask default configuration. */
#define HTTP_DEF_NET_MASK			{255,255,255,0}

/* Gateway default address configuration. */
#define HTTP_DEF_GATEWAY			{172,16,4,254}

/* MAC address configuration. */
#define HTTP_MAC    				{0x02, 0x12, 0x13, 0x10, 0x15, 0x11}
#define MAC2    				{0x02, 0x12, 0x13, 0x10, 0x15, 0x12}
/* Address of PHY interface. */
#define HTTP_PHY_ADDRESS 			BOARD_ENET0_PHY_ADDRESS

/* System clock name. */
#define SYS_CLOCK_NAME 				kCLOCK_CoreSysClk

/* Stack size and priority for os task */
#define HTTP_STACKSIZE 				DEFAULT_THREAD_STACKSIZE
#define HTTP_PRIORITY 				DEFAULT_THREAD_PRIO

#define CGI_DATA_LENGTH_MAX 		(127)

#if		MDNS
#define MDNS_HOSTNAME 				"lwip-http"
#endif

typedef struct netif Netif_S;

typedef struct {
	Netif_S netif;
	ethernetif_config_t *config;
	ip4_addr_t ip, netmask, gateway;
} EthernetCfg_S;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void cgi_urldecode(char *url);
static int cgi_rtc_data(HTTPSRV_CGI_REQ_STRUCT *param);
static int cgi_example(HTTPSRV_CGI_REQ_STRUCT *param);
static int ssi_date_time(HTTPSRV_SSI_PARAM_STRUCT *param);
static bool cgi_get_varval(char *var_str, char *var_name, char *var_val, uint32_t length);

static void tcpecho_init(void);
void udp_init(void);
/*******************************************************************************
 * Variables
 ******************************************************************************/
/* default network configuration constant */
static const uint8_t defIpAddr[] = HTTP_DEF_IP_ADDR;
static const uint8_t defNetMask[] = HTTP_DEF_NET_MASK;
static const uint8_t defGateway[] = HTTP_DEF_GATEWAY;

static const uint8_t defIpAddr2[] = HTTP_DEF_IP_ADDR2;
/* FS data.*/
extern const HTTPSRV_FS_DIR_ENTRY httpsrv_fs_data[];
 
/*
 * Authentication users
 */
static const HTTPSRV_AUTH_USER_STRUCT users[] = {
    {"admin", "admin"}, {NULL, NULL} /* Array terminator */
};

/*
 * Authentication information.
 */
static const HTTPSRV_AUTH_REALM_STRUCT auth_realms[] = {
    {"Please use uid:admin pass:admin to login", "/auth.html", HTTPSRV_AUTH_BASIC, users},
    {NULL, NULL, HTTPSRV_AUTH_INVALID, NULL} /* Array terminator */
};

static char cgi_data[CGI_DATA_LENGTH_MAX + 1];

const HTTPSRV_CGI_LINK_STRUCT cgi_lnk_tbl[] = {
    {"rtcdata", cgi_rtc_data},
    {"get", cgi_example},
    {"post", cgi_example},
    {0, 0} // DO NOT REMOVE - last item - end of table
};

const HTTPSRV_SSI_LINK_STRUCT ssi_lnk_tbl[] = {{"date_time", ssi_date_time}, {0, 0}};


static ethernetif_config_t cfgHttp = {
        .phyAddress = HTTP_PHY_ADDRESS, 
		.clockName = SYS_CLOCK_NAME, 
		.macAddress = HTTP_MAC,
};
static ethernetif_config_t cfgEth2 = {
        .phyAddress = BOARD_ENET1_PHY_ADDRESS, 
		.clockName = SYS_CLOCK_NAME, 
		.macAddress = MAC2,
};

static EthernetCfg_S ethernetCfg;
static EthernetCfg_S ethernetCfg2;
/*******************************************************************************
 * Code
 ******************************************************************************/




static int cgi_rtc_data(HTTPSRV_CGI_REQ_STRUCT *param)
{
#define BUFF_SIZE sizeof("00\n00\n00\n")
    HTTPSRV_CGI_RES_STRUCT response;
    uint32_t time;
    uint32_t min;
    uint32_t hour;
    uint32_t sec;

    char str[BUFF_SIZE];
    uint32_t length = 0;

    if (param->request_method != HTTPSRV_REQ_GET)
    {
        return (0);
    }

    time = sys_now();

    sec = time / 1000;
    min = sec / 60;
    hour = min / 60;
    min %= 60;
    sec %= 60;

    response.ses_handle = param->ses_handle;
    response.content_type = HTTPSRV_CONTENT_TYPE_PLAIN;
    response.status_code = HTTPSRV_CODE_OK;
    /*
    ** When the keep-alive is used we have to calculate a correct content length
    ** so the receiver knows when to ACK the data and continue with a next request.
    ** Please see RFC2616 section 4.4 for further details.
    */

    /* Calculate content length while saving it to buffer */
    length = snprintf(str, BUFF_SIZE, "%ld\n%ld\n%ld\n", hour, min, sec);
    response.data = str;
    response.data_length = length;
    response.content_length = response.data_length;
    /* Send response */
    HTTPSRV_cgi_write(&response);
    return (response.content_length);
}

/* Example Common Gateway Interface callback. */
static int cgi_example(HTTPSRV_CGI_REQ_STRUCT *param)
{
    HTTPSRV_CGI_RES_STRUCT response = {0};

    response.ses_handle = param->ses_handle;
    response.status_code = HTTPSRV_CODE_OK;

    if (param->request_method == HTTPSRV_REQ_GET)
    {
        char *c;

        /* Replace '+' with spaces. */
        while ((c = strchr(cgi_data, '+')) != NULL)
        {
            *c = ' ';
        }
        response.content_type = HTTPSRV_CONTENT_TYPE_PLAIN;
        response.data = cgi_data;
        response.data_length = strlen(cgi_data);
        response.content_length = response.data_length;
        HTTPSRV_cgi_write(&response);
    }
    else if (param->request_method == HTTPSRV_REQ_POST)
    {
        uint32_t length = 0;
        uint32_t read;
        char buffer[sizeof("post_input = ") + CGI_DATA_LENGTH_MAX] = {0};

        length = param->content_length;
        read = HTTPSRV_cgi_read(param->ses_handle, buffer, (length > sizeof(buffer)) ? sizeof(buffer) : length);

        if (read > 0)
        {
            cgi_get_varval(buffer, "post_input", cgi_data, sizeof(cgi_data));
            cgi_urldecode(cgi_data);
        }

        /* Write the response using chunked transmission coding. */
        response.content_type = HTTPSRV_CONTENT_TYPE_HTML;
        /* Set content length to -1 to indicate unknown content length. */
        response.content_length = -1;
        response.data = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">";
        response.data_length = strlen(response.data);
        HTTPSRV_cgi_write(&response);
        response.data = "<html><head><title>POST successfull!</title>";
        response.data_length = strlen(response.data);
        HTTPSRV_cgi_write(&response);
        response.data = "<meta http-equiv=\"refresh\" content=\"0; url=cgi.html\"></head><body></body></html>";
        response.data_length = strlen(response.data);
        HTTPSRV_cgi_write(&response);
        response.data_length = 0;
        HTTPSRV_cgi_write(&response);
    }

    return (response.content_length);
}

static bool cgi_get_varval(char *src, char *var_name, char *dst, uint32_t length)
{
    char *name;
    bool result;
    uint32_t index;
    uint32_t n_length;

    result = false;
    dst[0] = 0;
    name = src;

    n_length = strlen(var_name);

    while ((name = strstr(name, var_name)) != 0)
    {
        if (name[n_length] == '=')
        {
            name += n_length + 1;

            index = strcspn(name, "&");
            if (index >= length)
            {
                index = length - 1;
            }
            strncpy(dst, name, index);
            dst[index] = '\0';
            result = true;
            break;
        }
        else
        {
            name = strchr(name, '&');
        }
    }

    return (result);
}

/* Example Server Side Include callback. */
static int ssi_date_time(HTTPSRV_SSI_PARAM_STRUCT *param)
{
    if (strcmp(param->com_param, "time") == 0)
    {
        HTTPSRV_ssi_write(param->ses_handle, __TIME__, strlen(__TIME__));
    }
    else if (strcmp(param->com_param, "date") == 0)
    {
        HTTPSRV_ssi_write(param->ses_handle, __DATE__, strlen(__DATE__));
    }
    return (0);
}

/* Decode URL encoded string in place. */
static void cgi_urldecode(char *url)
{
    char *src = url;
    char *dst = url;

    while (*src != '\0')
    {
        if ((*src == '%') && (isxdigit((int)*(src + 1))) && (isxdigit((int)*(src + 2))))
        {
            *src = *(src + 1);
            *(src + 1) = *(src + 2);
            *(src + 2) = '\0';
            *dst++ = strtol(src, NULL, 16);
            src += 3;
        }
        else
        {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
}

#if HTTPSRV_CFG_WEBSOCKET_ENABLED
/*
 * Echo plugin code - simple plugin which echoes any message it receives back to
 * client.
 */
uint32_t ws_echo_connect(void *param, WS_USER_CONTEXT_STRUCT context)
{
    PRINTF("WebSocket echo client connected.\r\n");
    return (0);
}

uint32_t ws_echo_disconnect(void *param, WS_USER_CONTEXT_STRUCT context)
{
    PRINTF("WebSocket echo client disconnected.\r\n");
    return (0);
}

uint32_t ws_echo_message(void *param, WS_USER_CONTEXT_STRUCT context)
{
    WS_send(&context); /* Send back what was received.*/
    if (context.data.type == WS_DATA_TEXT)
    {
        /* Print received text message to console. */
        context.data.data_ptr[context.data.length] = 0;
        PRINTF("WebSocket message received:\r\n%s\r\n", context.data.data_ptr);
    }
    else
    {
        /* Inform user about binary message. */
        PRINTF("WebSocket binary data with length of %d bytes received.", context.data.length);
    }

    return (0);
}

uint32_t ws_echo_error(void *param, WS_USER_CONTEXT_STRUCT context)
{
    PRINTF("WebSocket error: 0x%X.\r\n", context.error);
    return (0);
}

WS_PLUGIN_STRUCT ws_tbl[] = {{"/echo", ws_echo_connect, ws_echo_message, ws_echo_error, ws_echo_disconnect, NULL},
                             {0, 0, 0, 0, 0, 0}};
#endif /* HTTPSRV_CFG_WEBSOCKET_ENABLED */

/*!
 * @brief Callback function to generate TXT mDNS record for HTTP service.
 */
static void http_srv_txt(struct mdns_service *service, void *txt_userdata)
{
    mdns_resp_add_service_txtitem(service, "path=/", 6);
}


static TimerHandle_t testTimer2; // ¶¨Òå¾ä±ú
static void testTimer2CallBack(TimerHandle_t xTimer) {
	if(!enet_link(ethernetCfg.config->phyAddress)){
		debug("ethernet phy disconnected!! \r\n");
	}
	
}
  
/*!
 * @brief Initializes lwIP stack.
 */
static void stack_init(void)
{
	ethernetCfg.config = &cfgHttp;
	ethernetCfg2.config = &cfgEth2;

    IP4_ADDR(&ethernetCfg.ip, defIpAddr[0], defIpAddr[1], defIpAddr[2], defIpAddr[3]);
    IP4_ADDR(&ethernetCfg.netmask, defNetMask[0], defNetMask[1], defNetMask[2], defNetMask[3]);
    IP4_ADDR(&ethernetCfg.gateway, defGateway[0], defGateway[1], defGateway[2], defGateway[3]);
		
	IP4_ADDR(&ethernetCfg2.ip, defIpAddr2[0], defIpAddr2[1], defIpAddr2[2], defIpAddr2[3]);
    IP4_ADDR(&ethernetCfg2.netmask, defNetMask[0], defNetMask[1], defNetMask[2], defNetMask[3]);
    IP4_ADDR(&ethernetCfg2.gateway, defGateway[0], defGateway[1], defGateway[2], defGateway[3]);
//	enet_phy_init(ethernetCfg.config);
//	while(!enet_link(ethernetCfg.config->phyAddress)){
//		debug("phy unlink!!\r\n");
//		DELAY(1000);
//	}
//	debug("phy link!!\r\n");
	
	tcpip_init(NULL, NULL);
	
    netifapi_netif_add(&ethernetCfg.netif, &ethernetCfg.ip, &ethernetCfg.netmask, &ethernetCfg.gateway, ethernetCfg.config,
                       ethernetif0_init, tcpip_input);
    netifapi_netif_set_default(&ethernetCfg.netif);
    netifapi_netif_set_up(&ethernetCfg.netif);
	
	netifapi_netif_add(&ethernetCfg2.netif, &ethernetCfg2.ip, &ethernetCfg2.netmask, &ethernetCfg2.gateway, ethernetCfg2.config,
                       ethernetif1_init, tcpip_input);
    netifapi_netif_set_default(&ethernetCfg2.netif);
    netifapi_netif_set_up(&ethernetCfg2.netif);
	
#if		MDNS
    mdns_resp_init();
    mdns_resp_add_netif(&ethernetCfg.netif, MDNS_HOSTNAME, 60);
    mdns_resp_add_service(&ethernetCfg.netif, MDNS_HOSTNAME, "_http", DNSSD_PROTO_TCP, 80, 300, http_srv_txt, NULL);
#endif

    LWIP_PLATFORM_DIAG(("************************************************"));
    LWIP_PLATFORM_DIAG((" IPv4 Address     : %u.%u.%u.%u", ((u8_t *)&ethernetCfg.ip)[0],
                        ((u8_t *)&ethernetCfg.ip)[1], ((u8_t *)&ethernetCfg.ip)[2],
                        ((u8_t *)&ethernetCfg.ip)[3]));
    LWIP_PLATFORM_DIAG((" IPv4 Subnet mask : %u.%u.%u.%u", ((u8_t *)&ethernetCfg.netmask)[0],
                        ((u8_t *)&ethernetCfg.netmask)[1], ((u8_t *)&ethernetCfg.netmask)[2],
                        ((u8_t *)&ethernetCfg.netmask)[3]));
    LWIP_PLATFORM_DIAG((" IPv4 Gateway     : %u.%u.%u.%u", ((u8_t *)&ethernetCfg.gateway)[0], ((u8_t *)&ethernetCfg.gateway)[1],
                        ((u8_t *)&ethernetCfg.gateway)[2], ((u8_t *)&ethernetCfg.gateway)[3]));
#if		MDNS
    LWIP_PLATFORM_DIAG((" mDNS hostname    : %s", MDNS_HOSTNAME));
#endif
    LWIP_PLATFORM_DIAG(("************************************************"));
		
	
//	testTimer2 = xTimerCreate("testTimer2",1000,pdTRUE,( void * ) 0,testTimer2CallBack);
//	xTimerStart(testTimer2,0);
	
//	tcpecho_init();
	
//	udp_init();
}

/*!
 * @brief Initializes lwIP stack.
 */
 /*
static void tcp_init(void)
{
		ip4_addr_t fsl_netif1_ipaddr, fsl_netif1_netmask, fsl_netif1_gw;
		
		ethernetif_config_t fsl_enet_config1 = {
        .phyAddress = EXAMPLE_PHY_ADDRESS_1,
        .clockName = EXAMPLE_CLOCK_NAME,
        .macAddress = configMAC_ADDR_1,
    };
		
	IP4_ADDR(&fsl_netif1_ipaddr, configIP_ADDR0_1, configIP_ADDR1_1, configIP_ADDR2_1, configIP_ADDR3_1);
    IP4_ADDR(&fsl_netif1_netmask, configNET_MASK0, configNET_MASK1, configNET_MASK2, configNET_MASK3);
    IP4_ADDR(&fsl_netif1_gw, configGW_ADDR0_1, configGW_ADDR1_1, configGW_ADDR2_1, configGW_ADDR3_1);
		
//		tcpip_init(NULL, NULL);
		
		
		netif_add(&fsl_netif1, &fsl_netif1_ipaddr, &fsl_netif1_netmask, &fsl_netif1_gw,
              &fsl_enet_config1, ethernetif1_init, ethernet_input);
    netif_set_default(&fsl_netif1);
    netif_set_up(&fsl_netif1);
		
		PRINTF("\r\n************************************************\r\n");
    PRINTF(" TCP Echo example\r\n");
    PRINTF("************************************************\r\n");
    PRINTF(" IPv4 Address     : %u.%u.%u.%u\r\n", ((u8_t *)&fsl_netif1_ipaddr)[0], ((u8_t *)&fsl_netif1_ipaddr)[1],
           ((u8_t *)&fsl_netif1_ipaddr)[2], ((u8_t *)&fsl_netif1_ipaddr)[3]);
    PRINTF(" IPv4 Subnet mask : %u.%u.%u.%u\r\n", ((u8_t *)&fsl_netif1_netmask)[0], ((u8_t *)&fsl_netif1_netmask)[1],
           ((u8_t *)&fsl_netif1_netmask)[2], ((u8_t *)&fsl_netif1_netmask)[3]);
    PRINTF(" IPv4 Gateway     : %u.%u.%u.%u\r\n", ((u8_t *)&fsl_netif1_gw)[0], ((u8_t *)&fsl_netif1_gw)[1],
           ((u8_t *)&fsl_netif1_gw)[2], ((u8_t *)&fsl_netif1_gw)[3]);
    PRINTF("************************************************\r\n");
}
*/
/*!
 * @brief Initializes server.
 */
const struct in_addr http_addr = {0xd70410acUL};
static void http_server_socket_init(void)
{
    HTTPSRV_PARAM_STRUCT params;
	struct sockaddr_in addr;
    uint32_t httpsrv_handle;

    /* Init Fs*/
    HTTPSRV_FS_init(httpsrv_fs_data);

    /* Init HTTPSRV parameters.*/
    memset(&params, 0, sizeof(params));
    params.root_dir = "";
    params.index_page = "/index.html";
    params.auth_table = auth_realms;
    params.cgi_lnk_tbl = cgi_lnk_tbl;
    params.ssi_lnk_tbl = ssi_lnk_tbl;
#if HTTPSRV_CFG_WEBSOCKET_ENABLED
    params.ws_tbl = ws_tbl;
#endif
	addr.sin_addr = http_addr;
	addr.sin_port = (in_port_t)80;
	params.address = *(struct sockaddr *)(&addr);

    /* Init HTTP Server.*/
    httpsrv_handle = HTTPSRV_init(&params);
    if (httpsrv_handle == 0)
    {
        LWIP_PLATFORM_DIAG(("HTTPSRV_init() is Failed"));
    }
}

/*!
 * @brief The main function containing server thread.
 */
void main_thread(void *arg)
{
    LWIP_UNUSED_ARG(arg);
	PRINTF("main thread start!!\r\n");
    stack_init();
    http_server_socket_init();

    vTaskDelete(NULL);
}

static const ip_addr_t tcp_addr = {0xd70410acUL};
static void tcpecho_thread(void *arg)
{
  struct netconn *conn, *newconn;
  err_t err;
  LWIP_UNUSED_ARG(arg);
  
  u32_t addr = 0x00000000UL;

  /* Create a new connection identifier. */
  /* Bind connection to well known port number 7. */
#if LWIP_IPV6
  conn = netconn_new(NETCONN_TCP_IPV6);
  netconn_bind(conn, IP6_ADDR_ANY, 7);
#else /* LWIP_IPV6 */
  conn = netconn_new(NETCONN_TCP);
//  netconn_bind(conn, IP_ADDR_ANY, 5000);
	netconn_bind(conn, &tcp_addr, 5000);
#endif /* LWIP_IPV6 */
  LWIP_ERROR("tcpecho: invalid conn", (conn != NULL), return;);

  /* Tell connection to go into listening mode. */
  netconn_listen(conn);

  while (1) {

    /* Grab new connection. */
    err = netconn_accept(conn, &newconn);
    /*printf("accepted new connection %p\n", newconn);*/
    /* Process the new connection. */
    if (err == ERR_OK) {
      struct netbuf *buf;
      void *data;
      u16_t len;
      
      while ((err = netconn_recv(newconn, &buf)) == ERR_OK) {
        /*printf("Recved\n");*/
        do {
             netbuf_data(buf, &data, &len);
             err = netconn_write(newconn, data, len, NETCONN_COPY);
#if 0
            if (err != ERR_OK) {
              printf("tcpecho: netconn_write: error \"%s\"\n", lwip_strerr(err));
            }
#endif
        } while (netbuf_next(buf) >= 0);
        netbuf_delete(buf);
      }
      /*printf("Got EOF, looping\n");*/ 
      /* Close connection and discard connection identifier. */
      netconn_close(newconn);
      netconn_delete(newconn);
    }
  }
}

static void tcpecho_init(void)
{
  sys_thread_new("tcpecho_thread", tcpecho_thread, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
}


const ip_addr_t udp_addr = {0xd80410acUL};
/*-----------------------------------------------------------------------------------*/
static void udpecho_thread(void *arg)
{
  struct netconn *conn;
  struct netbuf *buf;
  char buffer[4096];
  err_t err;
  LWIP_UNUSED_ARG(arg);

#if LWIP_IPV6
  conn = netconn_new(NETCONN_UDP_IPV6);
  netconn_bind(conn, IP6_ADDR_ANY, 7);
#else /* LWIP_IPV6 */
  conn = netconn_new(NETCONN_UDP);
//  netconn_bind(conn, IP_ADDR_ANY, 3000);
  netconn_bind(conn, &udp_addr, 3000);
#endif /* LWIP_IPV6 */
  LWIP_ERROR("udpecho: invalid conn", (conn != NULL), return;);

#if LWIP_IGMP /* Only for testing of multicast join*/
{
  #include "lwip\netif.h"

//  ip4_addr_t multiaddr;
//  IP4_ADDR(&multiaddr, 224, 5, 6, 7);

//  err = netconn_join_leave_group(conn, &multiaddr, &netif_default->ip_addr, NETCONN_JOIN);
//  LWIP_ERROR("udpecho: join group is failed", (err == ERR_OK), return;);
}
#endif
  while (1) {
    err = netconn_recv(conn, &buf);
    if (err == ERR_OK) {
      /*  no need netconn_connect here, since the netbuf contains the address */
      if(netbuf_copy(buf, buffer, sizeof(buffer)) != buf->p->tot_len) {
        LWIP_DEBUGF(LWIP_DBG_ON, ("netbuf_copy failed\n"));
      } else {
        buffer[buf->p->tot_len] = '\0';
        err = netconn_send(conn, buf);
        if(err != ERR_OK) {
          LWIP_DEBUGF(LWIP_DBG_ON, ("netconn_send failed: %d\n", (int)err));
        } else {
          LWIP_DEBUGF(LWIP_DBG_ON, ("got %s\n", buffer));
        }
      }
      netbuf_delete(buf);
    }
  }
}
/*-----------------------------------------------------------------------------------*/
static void udp_init(void)
{
  sys_thread_new("udpecho_thread", udpecho_thread, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
}
/*!
 * @brief The tcp function containing server thread.
 */
//static void tcp_thread(void *arg)
//{
//    LWIP_UNUSED_ARG(arg);
//		PRINTF("tcp thread start!!\r\n");
//    tcp_init();

//    vTaskDelete(NULL);
//}

