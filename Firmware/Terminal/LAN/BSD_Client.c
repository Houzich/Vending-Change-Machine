/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::Network
 * Copyright (c) 2004-2018 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    BSD_Client.c
 * Purpose: LED Client example using BSD sockets
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "Terminal/Terminal.h"
#include "BSD_Client.h"
#include "RTE_Components.h" 

#include "rl_net.h"                     // Keil.MDK-Pro::Network:CORE
#include "rl_net_ds.h"

#ifdef RTE_Compiler_EventRecorder
#include "EventRecorder.h"
#endif

#define DEBUG_TERMINAL_LAN

#ifdef DEBUG_TERMINAL_LAN
#undef DEBUG
#undef DEBUG_PRINTF
#undef DEBUG_PUTCHAR
#define DEBUG(x)					printf("TERMINAL LAN: "); printf x ;
#define DEBUG_PRINTF(x)		printf x ;
#define DEBUG_PUTCHAR(x)	ITM_SendChar x ;
#else
#define DEBUG(x)
#define DEBUG_PRINTF(x)
#define DEBUG_PUTCHAR(x)
#endif // DEBUG_TERMINAL_LAN



//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

//   <s.40>Remote IP Address
//   =======================
//   <i> IPv4 or IPv6 Address in text representation
//   <i>Default: "192.168.0.100" or "fe80:1c30:6cff:fea2:455e"
//#define IP_ADDR        "fe80::1c30:6cff:fea2:455e"
#define IP_ADDR        "192.168.0.25"
//   <o>Remote Port <1-65535>
//   <i> Do not set number of port too small,
//   <i> maybe it is already used.
//   <i> Default: 1001
#define PORT_NUM       80

//   <o>Communication Protocol <0=> Stream (TCP) <1=> Datagram (UDP)
//   <i> Select a protocol for sending data.
#define PROTOCOL       0

//------------- <<< end of configuration section >>> -----------------------

#define BLINKLED 0x01                   /* Command for blink the leds         */
#if (PROTOCOL == 0)
 #define SOCKTYPE   SOCK_STREAM
#else
 #define SOCKTYPE   SOCK_DGRAM
#endif

// Main stack size must be multiple of 8 Bytes
#define BSD_CLIENT_STK_SZ (1024U)
uint64_t bsd_client_stk[BSD_CLIENT_STK_SZ / 8];
const osThreadAttr_t bsd_client_attr = {
    .name = "bsd_clientTask",
    .priority = (osPriority_t) osPriorityNormal,
	  .stack_mem  = &bsd_client_stk[0],
		.stack_size = sizeof(bsd_client_stk)
};


#define CLIENT_STK_SZ (4096U)
uint64_t client_stk[CLIENT_STK_SZ / 8];
const osThreadAttr_t client_attr = {
    .name = "clientTask",
    .priority = (osPriority_t) osPriorityAboveNormal,
	  .stack_mem  = &client_stk[0],
		.stack_size = sizeof(client_stk)
};


static void Client (void *arg);
void debug_net_status_printf  (netStatus net_status);
void debug_bsd_status_printf  (int32_t bsd_status, const char *str);

/* Print IP addresses */
static void print_address (void) {
  static uint8_t ip_addr[NET_ADDR_IP4_LEN];
  static char    ip_ascii[40];
  static char    buf[24];

  /* Print IPv4 network address */
  netIF_GetOption (NET_IF_CLASS_ETH, netIF_OptionIP4_Address, ip_addr, sizeof(ip_addr));
  netIP_ntoa (NET_ADDR_IP4, ip_addr, ip_ascii, sizeof(ip_ascii));

  sprintf (buf, "IP4:%-15s", ip_ascii);
  printf ("%s\n", buf);

//  /* Print IPv6 network address */
//  netIF_GetOption (NET_IF_CLASS_ETH, netIF_OptionIP6_LinkLocalAddress, ip_addr, sizeof(ip_addr));
//  netIP_ntoa(NET_ADDR_IP6, ip_addr, ip_ascii, sizeof(ip_ascii));

//  sprintf (buf, "IP6:%.16s", ip_ascii);
//  printf ("%s\n", buf);
//  sprintf (buf, "%s", ip_ascii+16);
//  printf ("%s\n", buf);
}

/*----------------------------------------------------------------------------
  Thread 'Client': BSD Client socket process
 *---------------------------------------------------------------------------*/
static __NO_RETURN void Client (void *arg) {
	
//	uint8_t ip_addr[NET_ADDR_IP4_LEN];
//	NET_ADDR addr = { NET_ADDR_IP4,1000,192,168,0,100};
	
  SOCKADDR_IN addr;
  int sock, res;
  char dbuf[4];
  uint8_t p2val,lshf;

  (void)arg;

  while (1) {
		osDelay (1000);
    memset (&addr, 0, sizeof(addr));

    /* Setup network parameters */
    if (netIP_aton (IP_ADDR, NET_ADDR_IP4, (uint8_t *)&addr.sin_addr)) {
      /* IP_ADDR specifies IPv4 address */
      addr.sin_family = AF_INET;
    }
//    else if (netIP_aton (IP_ADDR, NET_ADDR_IP6, (uint8_t *)&addr.sin6_addr)) {
//      /* IP_ADDR specified IPv6 address */
//      addr.sin6_family = AF_INET6;
//    }
    addr.sin_port = htons(PORT_NUM);

    /* Create socket */
		//sock = netTCP_GetSocket (tcp_cb_client);
    sock = socket (addr.sin_family, SOCKTYPE, IPPROTO_TCP);
		if(sock<0)
		{
			DEBUG(("Socket get failed\n"));
		}
		else if(sock>0)
		{
			DEBUG(("Creat socket number = %d\n",sock));
		}
    /* Establish connection to remote host */
		int bsd_status;
    bsd_status = connect (sock, (SOCKADDR *)&addr, sizeof (addr));
		debug_bsd_status_printf(bsd_status, "Connect: ");
		
    lshf  = 1;
    p2val = 0x01;
    while (1) {
      // Shift the LEDs
      p2val = lshf ? (uint8_t)((uint32_t)p2val << 1) : (uint8_t)((uint32_t)p2val >> 1);
      if (p2val == 0x80) lshf = 0;
      if (p2val == 0x01) lshf = 1;
    
      // Send the data to LED Server.
      dbuf[0] = BLINKLED;
      dbuf[1] = p2val;
      //res = send (sock, (char *)&dbuf, 2, 0);
      res = send (sock, (char *)"Anton!\n", sizeof("Anton!\n"), 0);
      if (res < 0) {
				debug_bsd_status_printf(res, "Send: ");
        break;
      }
      osDelay (100 * 10);
    }
    closesocket (sock);
  }
}

/*----------------------------------------------------------------------------
  Main Thread 'bsd_client': Run Network
 *---------------------------------------------------------------------------*/
__NO_RETURN void bsd_client (void *arg) {
	static uint32_t ret;
	netStatus status = netError;
  (void)arg;

#ifdef RTE_Compiler_EventRecorder
  ret = EventRecorderInitialize(0U, 1U);
	if (ret != 1) {printf("ERROR EventRecorderInitialize!!!\n"); for (;;) {}}
  ret = EventRecorderEnable (EventRecordError, 0xC0U, 0xDCU);    /* Net Events     */
	if (ret != 1) {printf("ERROR Enable Net Events!!!\n"); for (;;) {}}	
  ret = EventRecorderEnable (EventRecordAll,   0xCAU, 0xCAU);    /* DHCP Events    */
	if (ret != 1) {printf("ERROR Enable DHCP Events!!!\n"); for (;;) {}}	
  ret = EventRecorderEnable (EventRecordAll,   0xD2U, 0xD2U);    /* BSD Events     */
	if (ret != 1) {printf("ERROR Enable BSD Events!!!\n"); for (;;) {}}	
#endif
  
  status = netInitialize ();
		if(status != netOK){
			debug_net_status_printf(status);
			while(1){};
		}
  print_address ();

  // Create networking task
  osThreadNew (Client, NULL, &client_attr);
  while(1) {
    osThreadFlagsWait (0, osFlagsWaitAny, osWaitForever);
  }
}


void debug_net_status_printf  (netStatus net_status) {
	switch(net_status)
	{
		case netOK:											DEBUG_PRINTF(("netOK - Operation succeeded\n")); break;
		case netBusy:										DEBUG_PRINTF(("netBusy - Process is busy\n")); break;
		case netError:									DEBUG_PRINTF(("netError - Unspecified error\n")); break;
		case netInvalidParameter:				DEBUG_PRINTF(("netInvalidParameter - Invalid parameter specified\n")); break;
		case netWrongState:							DEBUG_PRINTF(("netWrongState - Wrong state error\n")); break;
		case netDriverError:						DEBUG_PRINTF(("netDriverError - Driver error\n")); break;
		case netServerError:						DEBUG_PRINTF(("netServerError - Server error\n")); break;
		case netAuthenticationFailed:		DEBUG_PRINTF(("netAuthenticationFailed - User authentication failed\n")); break;
		case netDnsResolverError:				DEBUG_PRINTF(("netDnsResolverError - DNS host resolver failed\n")); break;
		case netFileError:							DEBUG_PRINTF(("netFileError - File not found or file r/w error\n")); break;
		case netTimeout:								DEBUG_PRINTF(("netTimeout - Operation timeout\n")); break;
		default:												DEBUG_PRINTF(("ERROR net.status. UNKNOWN STATUS!!!\n")); break;
	}	
}
void debug_bsd_status_printf  (int32_t bsd_status, const char *str) {
	DEBUG(("%s", str));
	switch(bsd_status)
	{
		case 0:                   DEBUG_PRINTF(("Operation successful.\n")); break;
		case BSD_ERROR:           DEBUG_PRINTF(("Unspecified error\n")); break;
		case BSD_ESOCK:           DEBUG_PRINTF(("Invalid socket descriptor\n")); break;
		case BSD_EINVAL:          DEBUG_PRINTF(("Invalid parameter\n")); break;
		case BSD_ENOTSUP:         DEBUG_PRINTF(("Operation or feature not supported\n")); break;
		case BSD_ENOMEM:          DEBUG_PRINTF(("Not enough memory\n")); break;
		case BSD_ELOCKED:         DEBUG_PRINTF(("Socket locked by another thread\n")); break;
		case BSD_EWOULDBLOCK:     DEBUG_PRINTF(("Operation would block\n")); break;
		case BSD_ETIMEDOUT:       DEBUG_PRINTF(("Operation timed out\n")); break;
		case BSD_EINPROGRESS:     DEBUG_PRINTF(("Operation in progress\n")); break;
		case BSD_ENOTCONN:        DEBUG_PRINTF(("Socket not connected\n")); break;
		case BSD_EISCONN:         DEBUG_PRINTF(("Socket is connected\n")); break;
		case BSD_ECONNREFUSED:    DEBUG_PRINTF(("Connection rejected by the peer\n")); break;
		case BSD_ECONNRESET:      DEBUG_PRINTF(("Connection reset by the peer\n")); break;
		case BSD_ECONNABORTED:    DEBUG_PRINTF(("Connection aborted locally\n")); break;
		case BSD_EALREADY:        DEBUG_PRINTF(("Connection already in progress\n")); break;
		case BSD_EADDRINUSE:      DEBUG_PRINTF(("Address already in use\n")); break;
		case BSD_EDESTADDRREQ:    DEBUG_PRINTF(("Destination address required\n")); break;
		case BSD_EHOSTNOTFOUND:   DEBUG_PRINTF(("Host not found\n")); break;
		default:									DEBUG_PRINTF(("ERROR bsd.status. UNKNOWN BSD STATUS!!!\n")); break;
	}	
}

