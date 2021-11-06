/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::Network
 * Copyright (c) 2004-2018 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    TCP_Client.c
 * Purpose: LED Client example using TCP sockets
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "Terminal/Terminal.h"
#include "Terminal_MSP.h"
#include "Hopper_1_MSP.h"
#include "TCP_Client.h"
#include "RTE_Components.h" 



#include "rl_net.h"                     // Keil.MDK-Pro::Network:CORE
#include "rl_net_ds.h"

//#include "net_config.h"

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
#define IP_ADDR        "192.168.0.100"
//   <o>Remote Port <1-65535>
//   <i> Do not set number of port too small,
//   <i> maybe it is already used.
//   <i> Default: 1001
#define PORT_NUM_1       2000
#define PORT_NUM_2       81

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

int32_t tcp_sock = -1;
int32_t tcp_display_sock = -1;
bool link_up = false;
// Main stack size must be multiple of 8 Bytes
#define TCP_CLIENT_STK_SZ (4096U)
uint64_t tcp_client_stk[TCP_CLIENT_STK_SZ / 8];
const osThreadAttr_t tcp_client_attr = {
    .name = "tcp_clientTask",
	  .stack_mem  = &tcp_client_stk[0],
		.stack_size = sizeof(tcp_client_stk),
    .priority = (osPriority_t) osPriorityNormal,
};


#define CLIENT_STK_SZ (4096U)
uint64_t client_stk[CLIENT_STK_SZ / 8];
const osThreadAttr_t client_attr = {
    .name = "clientTask",
	  .stack_mem  = &client_stk[0],
		.stack_size = sizeof(client_stk),
    .priority = (osPriority_t) osPriorityNormal,
};
osMessageQueueId_t mid_TCPClientMsgQueue = NULL;
static TCPClientMsgQueueTypeDef msg;
static void Client (void *arg);
//void debug_net_status_printf  (netStatus net_status, const char *str);
//void debug_tcp_status_printf  (netTCP_State tcp_state, const char *str);
osEventFlagsId_t TCPClient_Event_ID;
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

}

void Parse_Message_Received(uint8_t* buff, int len) {
  int size;
  uint8_t* pbuff = buff;
while(len >= 8){
  size = 0;
  if (memcmp(pbuff, "SETT_IN:", 8) == 0) {
      osEventFlagsSet(TCPClient_Event_ID, EventTCPClient::SEND_SETTINGS);
      size = 8;
    }
  else if (memcmp(pbuff, "BUTT:STA", 8) == 0) {
      osEventFlagsSet(TCPClient_Event_ID, EventTCPClient::SEND_BUTTON_STATE);
      size = 8;
    }
  else if (memcmp(pbuff, "TERM:STA", 8) == 0) {
      osEventFlagsSet(TCPClient_Event_ID, EventTCPClient::SEND_TERMINAL_STATE);
      size = 8;
    }
  else if (memcmp(pbuff, "HOP1:STA", 8) == 0) {   
    osEventFlagsSet(Hopper1MSPNS::hopper_1_msp.Event_ID, EventHopperMSP::GET_PINS_STATE);
      size = 8;
    }  
  else if (memcmp(pbuff, "HOP2:STA", 8) == 0) {
      osEventFlagsSet(Hopper2MSPNS::hopper_2_msp.Event_ID, EventHopperMSP::GET_PINS_STATE);
      size = 8;
    }  
  else if (memcmp(pbuff, "HOP3:STA", 8) == 0) {
      //osEventFlagsSet(TCPClient_Event_ID, EventTCPClient::SEND_HOPPER_3_STATE);
      size = 8;
    }  
  else if (memcmp(pbuff, "CMD:BILL", 8) == 0) {
      BillAcceptorNS::MessageClass msg;
      uint32_t bill;
      memcpy(&bill, &pbuff[8], sizeof(uint32_t));
      msg.command = BillAcceptorNS::ACCEPTED;
      msg.count_pulse = bill / 100 / 5;
      BillAcceptorNS::BillAcceptor.Messages.pushMessageIn(&msg);
      size = 8 + sizeof(uint32_t);
    }
  
    if(size == 0)
      {
        break;
      }
    else 
      {
        len -= size;
        pbuff += size;
      }
  }
}
// Notify the user application about TCP socket events.
uint32_t tcp_cb_client (int32_t socket, netTCP_Event event,
                        const NET_ADDR *addr, const uint8_t *buf, uint32_t len) {
 
  switch (event) {
    case netTCP_EventConnect:
      // Connect request received in server mode
      printf("Connect request received in server mode\n");
			break;
 
    case netTCP_EventEstablished:
      // Connection established
      printf("Connection established\n");
      break;
 
    case netTCP_EventClosed:
      // Connection was properly closed
      printf("Connection was properly closed\n");
      break;
 
    case netTCP_EventAborted:
      // Connection is for some reason aborted
      printf("Connection is for some reason aborted\n");
      break;
 
    case netTCP_EventACK:
      // Previously sent data acknowledged
      //printf("Previously sent data acknowledged\n");
      break;
 
    case netTCP_EventData:
      // Data received
      //printf("Data received\n");
      msg.buff = (uint8_t *)buf;
      msg.len = len;
      osMessageQueuePut(mid_TCPClientMsgQueue, &msg, NULL, 0);
      //Parse_Message_Received((uint8_t *)buf, len);
      //netTCP_ResetReceiveWindow(tcp_sock);
      break;
  }
  return (0);
}
 
// Connect to TCP server and send data.
void send_data (void) {
	netStatus net_status;
	netTCP_State tcp_state;
  // IPv4 address: 192.168.0.11
  NET_ADDR addr = { NET_ADDR_IP4, PORT_NUM_1,
                    192, 168, 0, 11 };
while(1) 
  if (tcp_sock >= 0) {
		tcp_state = netTCP_GetState (tcp_sock);
		//debug_tcp_status_printf(tcp_state, "netTCP_GetState: ");
    switch (tcp_state) {
      case netTCP_StateUNUSED:
      case netTCP_StateCLOSED:
        // Connect to TCP socket server on port 80
        net_status = netTCP_Connect (tcp_sock, &addr, PORT_NUM_1);
        printf ("Local port is %d\n", netTCP_GetLocalPort (tcp_sock));
				debug_net_status_printf(net_status, "Connect: ");

        break;
 
      case netTCP_StateESTABLISHED:
        // Connected, send the data
        
        TCPClientSemaphoreAcquire(sid_ClientTCP_Semaphore, osWaitForever);
        if (netTCP_SendReady (tcp_sock) == true) {
          uint8_t *sendbuf; 
          sendbuf = netTCP_GetBuffer (100);
          if(sendbuf == NULL) {
            TCPClientSemaphoreRelease(sid_ClientTCP_Semaphore);
            break;
          }
          memcpy(sendbuf, "DEBUG:__Anton!\n", sizeof("DEBUG:__Anton!\n"));
					net_status = netTCP_Send(tcp_sock, sendbuf, sizeof("DEBUG:__Anton!\n"));
					if (net_status < 0) {
						debug_net_status_printf(net_status, "Send Error: ");
					}
          TCPClientSemaphoreRelease(sid_ClientTCP_Semaphore);
          return;
        }
        TCPClientSemaphoreRelease(sid_ClientTCP_Semaphore);
        break;
 
      default:
        break;
    }
  }
}


//if (netTCP_SendReady (tcp_sock)) {
//  // The socket is ready to send the data
//  maxlen  = netTCP_GetMaxSegmentSize (tcp_sock);
//  sendbuf = netTCP_GetBuffer (maxlen);
//  memcpy (sendbuf, my_data_buf, maxlen);
//  netTCP_Send (tcp_sock, sendbuf, maxlen);
//}
/*----------------------------------------------------------------------------
  Thread 'Client': TCP Client socket process
 *---------------------------------------------------------------------------*/
static __NO_RETURN void Client (void *arg) {
	
  NET_ADDR addr = { NET_ADDR_IP4, PORT_NUM_1,
                    192, 168, 0, 12 };	
  NET_ADDR addr_display = { NET_ADDR_IP4, PORT_NUM_2,
                            192, 168, 0, 12 };
  int res;
  char dbuf[4];
  uint8_t p2val,lshf;
	netStatus net_status;
	netTCP_State tcp_state;  
  (void)arg;
                                                      
#ifdef TERMINAL_USE_ETH_FOR_DEBUG
  
#endif // TERMINAL_USE_ETH_FOR_DEBUG                   
  while (1) {
    while(!link_up){
      osDelay (10);    
    }

    if (mid_TCPClientMsgQueue == NULL) {
      mid_TCPClientMsgQueue = osMessageQueueNew(TCPCLIENT_MSGQUEUE_OBJECTS, sizeof(TCPClientMsgQueueTypeDef), NULL);
    }
    if (mid_TCPClientMsgQueue == NULL) assert_param(0);
    /* Create socket */
		// Allocate a free TCP socket.
    //TCPClientSemaphoreAcquire(sid_ClientTCP_Semaphore, osWaitForever);
		
    tcp_sock = netTCP_GetSocket (tcp_cb_client);
		tcp_display_sock = netTCP_GetSocket (tcp_cb_client);    
    //TCPClientSemaphoreRelease(sid_ClientTCP_Semaphore);

		if((tcp_sock < 0)||(tcp_display_sock < 0))
		{
			printf("Socket get failed\n");
      for(;;)osDelay(100);
		}
		else if((tcp_sock >= 0)&&(tcp_display_sock >= 0))
		{
			printf("Creat socket number = %d\n", tcp_sock);
			printf("Creat socket number = %d\n", tcp_display_sock);
		}
    
//    if (tcp_sock >= 0) {
//      // Start listening on TCP port 80 
//      netTCP_Listen (tcp_sock, 80);
//    }

    while (1) {

      if (tcp_sock >= 0) {
        //TCPClientSemaphoreAcquire(sid_ClientTCP_Semaphore, osWaitForever);
        tcp_state = netTCP_GetState (tcp_sock);
        //TCPClientSemaphoreRelease(sid_ClientTCP_Semaphore);
        //debug_tcp_status_printf(tcp_state, "netTCP_GetState: ");
        switch (tcp_state) {
          case netTCP_StateUNUSED:
          case netTCP_StateCLOSED:
            //TCPClientSemaphoreAcquire(sid_ClientTCP_Semaphore, osWaitForever);
            // Connect to TCP socket server on port 80
            net_status = netTCP_Connect (tcp_sock, &addr, PORT_NUM_1);
            //TCPClientSemaphoreRelease(sid_ClientTCP_Semaphore);
            printf ("Local port is %d\n", netTCP_GetLocalPort (tcp_sock));
            debug_net_status_printf(net_status, "Connect: ");
            break; 
          case netTCP_StateESTABLISHED: 
          break;
          case netTCP_StateINVALID: 
            printf("\n netTCP_StateINVALID!!!! \n");
          break;
          default: break;
        }
      }
      if (tcp_display_sock >= 0) {
        //TCPClientSemaphoreAcquire(sid_ClientTCP_Semaphore, osWaitForever);
        tcp_state = netTCP_GetState (tcp_display_sock);
        //TCPClientSemaphoreRelease(sid_ClientTCP_Semaphore);
        //debug_tcp_status_printf(tcp_state, "netTCP_GetState: ");
        switch (tcp_state) {
          case netTCP_StateUNUSED:
          case netTCP_StateCLOSED:
            //TCPClientSemaphoreAcquire(sid_ClientTCP_Semaphore, osWaitForever);
            // Connect to TCP socket server on port 80
            net_status = netTCP_Connect (tcp_display_sock, &addr_display, PORT_NUM_2);
            //TCPClientSemaphoreRelease(sid_ClientTCP_Semaphore);
            printf ("Local port is %d\n", netTCP_GetLocalPort (tcp_display_sock));
            debug_net_status_printf(net_status, "Connect: ");
            break; 
          case netTCP_StateESTABLISHED: 
          break;
          case netTCP_StateINVALID: 
            printf("\n netTCP_StateINVALID!!!! \n");
          break;
          default: break;
        }
      }
      osDelay(100);
    }
		netTCP_Close(tcp_sock);
		netTCP_Close(tcp_display_sock);
  }
}

/*----------------------------------------------------------------------------
  Main Thread 'tcp_client': Run Network
 *---------------------------------------------------------------------------*/
__NO_RETURN void tcp_client (void *arg) {
	static uint32_t ret;
	netStatus status = netError;
  (void)arg;

#ifdef RTE_Compiler_EventRecorder
  ret = EventRecorderInitialize(0U, 1U);
	if (ret != 1) {printf("ERROR EventRecorderInitialize!!!\n"); for (;;) {}}
//  ret = EventRecorderEnable (EventRecordError, 0xC0U, 0xDCU);    /* Net Events     */
//	if (ret != 1) {printf("ERROR Enable Net Events!!!\n"); for (;;) {}}	
//  ret = EventRecorderEnable (EventRecordAll,   0xCAU, 0xCAU);    /* DHCP Events    */
//	if (ret != 1) {printf("ERROR Enable DHCP Events!!!\n"); for (;;) {}}	
//  ret = EventRecorderEnable (EventRecordAll,   0xD3U, 0xD3U);    /* HTTP Events    */
//	if (ret != 1) {printf("ERROR Enable HTTP Events!!!\n"); for (;;) {}}	
#endif

  TCPClient_Event_ID = osEventFlagsNew(NULL);
	if (TCPClient_Event_ID == NULL) {
		DEBUG(("Event Flags object not created, handle failure!!!\n")); // Event Flags object not created, handle failure
		for (;;);
	}  
  status = netInitialize ();
		if(status != netOK){
			debug_net_status_printf(status, "netInitialize: ");
			while(1){};
		}
  print_address ();

  // Create networking task
  osThreadNew (Client, NULL, &client_attr);
  osStatus_t os_status;
  TCPClientMsgQueueTypeDef message;
  uint32_t flags;
  while(1) {
    	osDelay(1);
      if (tcp_sock >= 0) {
        os_status = osMessageQueueGet(mid_TCPClientMsgQueue, &message, NULL, 1);   // wait for message
        if (os_status == osOK) {
          Parse_Message_Received(message.buff, message.len);
        }
        flags = osEventFlagsWait(TCPClient_Event_ID, 0xFFFF, osFlagsWaitAny, 0U);     
        if (Check_CMSIS_Flags_Functions_Error_Codes(flags) != 0) {
          continue;        
        }
        
        if(flags & EventTCPClient::SEND_SETTINGS){
          printf("Send Settings\n");
          Send_Settings_ETH();
        }
        
        if(flags & EventTCPClient::SEND_BUTTON_STATE){
          printf("Send Button State\n");
          Send_Button_State_ETH();
        }
        
        if(flags & EventTCPClient::SEND_TERMINAL_STATE){
          printf("Send Terminal State\n");
        } 
        
        if((flags & EventTCPClient::SEND_HOPPER_1_STATE)||(flags & EventTCPClient::SEND_HOPPER_2_STATE)||(flags & EventTCPClient::SEND_HOPPER_3_STATE)){
           int num = 0;
          if (flags & EventTCPClient::SEND_HOPPER_1_STATE) {num = 1;}
          else if  (flags & EventTCPClient::SEND_HOPPER_2_STATE) {num = 2;}
           else  {num = 3;}
          printf("Send Hopper %d State\n", num);
          Send_Hopper_State_ETH(num);
        }             
      }
		
  }
}

// Process DCHP server information
void netDHCP_Notify (uint32_t if_id, uint8_t option, const uint8_t *val, uint32_t len) {
  char ip_ascii[16];
  uint32_t idx;
  
  switch (option)  {
    case NET_DHCP_OPTION_IP_ADDRESS:           // IP address has changed
      netIP_ntoa (NET_ADDR_IP4, &val[0], ip_ascii, sizeof(ip_ascii));
      printf ("IP address: %s", ip_ascii);
      break;
  
    case NET_DHCP_OPTION_NTP_SERVERS:          // List of NTP Server IP addresses
      printf ("NTP Server IP address list:\n");
      idx = 0;
      while ((idx+3) < len) {
        netIP_ntoa (NET_ADDR_IP4, &val[idx], ip_ascii, sizeof(ip_ascii));
        printf ("IP address: %s", ip_ascii);
        idx += 4;
      }
      break;
  
    case NET_DHCP_OPTION_BOOTFILE_NAME:        // DCHP server boot file
      printf ("Boot File: %s\n", val);
      break;
  }   
}

void netETH_Notify (uint32_t if_num, netETH_Event event, uint32_t val) {
  NET_ETH_LINK_INFO *info;
     
  switch (event) {
    case netETH_LinkDown:
      link_up = false;
      printf ("Link is down\n");
      break;
    case netETH_LinkUp:
      link_up = true;
      printf ("Link is up\n");
      info = (NET_ETH_LINK_INFO *)&val;
      switch (info->speed) {
        case 0:
          printf ("10 MBit\n");
          break;
        case 1:
          printf ("100 MBit\n");
          break;
        case 2:
          printf ("1 GBit\n");
          break;
      }
      switch (info->duplex) {
        case 0:
          printf ("Half duplex\n");
          break;
        case 1:
          printf ("Full duplex\n");
          break;
      }
      break;
    case netETH_Wakeup:
      printf ("Wakeup frame received\n");
      break;
    case netETH_TimerAlarm:
      printf ("Timer alarm\n");
      break;
  }
} 

void debug_net_status_printf  (netStatus net_status, const char *str) {
	printf("%s", str);
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
void debug_tcp_status_printf  (netTCP_State tcp_state, const char *str) {
	DEBUG(("%s", str));
	switch(tcp_state)
	{
		case netTCP_StateINVALID:           DEBUG_PRINTF(("Invalid Socket\n")); break;
		case netTCP_StateUNUSED:           	DEBUG_PRINTF(("Entry is free and unused\n")); break;
		case netTCP_StateCLOSED:           	DEBUG_PRINTF(("Entry allocated, socket still closed\n")); break;
		case netTCP_StateLISTEN:           	DEBUG_PRINTF(("Socket waiting for incoming connection\n")); break;
		case netTCP_StateSYN_RECEIVED:      DEBUG_PRINTF(("SYN frame received\n")); break;
		case netTCP_StateSYN_SENT:          DEBUG_PRINTF(("SYN packet sent to establish a connection\n")); break;
		case netTCP_StateFIN_WAIT_1:        DEBUG_PRINTF(("Close started FIN packet was sent\n")); break;
		case netTCP_StateFIN_WAIT_2:        DEBUG_PRINTF(("Our FIN ACK-ed, waiting for remote FIN\n")); break;
		case netTCP_StateCLOSING:           DEBUG_PRINTF(("Received FIN independently of our FIN\n")); break;
		case netTCP_StateLAST_ACK:          DEBUG_PRINTF(("Waiting for last ACK for our FIN\n")); break;
		case netTCP_StateTIME_WAIT:         DEBUG_PRINTF(("Timed waiting for 2MSL\n")); break;
		case netTCP_StateESTABLISHED:       DEBUG_PRINTF(("TCP Connection established\n")); break;
		default:														DEBUG_PRINTF(("ERROR tcp.status. UNKNOWN TCP STATUS!!!\n")); break;
	}	
}

/**
\addtogroup net_genFunc
@{
*/
/**
  \fn          void net_sys_error (NET_ERROR error)
  \ingroup     net_cores
  \brief       Network system error handler.
*/
//void net_sys_error (NET_ERROR error) {
//  /* This function is called when a fatal error is encountered. */
//  /* The normal program execution is not possible anymore.      */

//  switch (error) {
//    case NET_ERROR_MEM_ALLOC:
//      /* Out of memory */
//		DEBUG("FATAL ERROR: NET_ERROR_MEM_ALLOC\n"));
//      break;

//    case NET_ERROR_MEM_FREE:
//      /* Trying to release non existing memory block */
//			DEBUG("FATAL ERROR: NET_ERROR_MEM_FREE\n"));
//      break;

//    case NET_ERROR_MEM_CORRUPT:
//      /* Memory Link pointer corrupted */
//      /* More data written than the size of allocated memory block */
//			DEBUG("FATAL ERROR: NET_ERROR_MEM_CORRUPT\n"));
//      break;

//    case NET_ERROR_CONFIG:
//      /* Network configuration error detected */
//			DEBUG("FATAL ERROR: NET_ERROR_CONFIG\n"));
//      break;

//    case NET_ERROR_UDP_ALLOC:
//      /* Out of UDP Sockets */
//			DEBUG("FATAL ERROR: NET_ERROR_UDP_ALLOC\n"));
//      break;

//    case NET_ERROR_TCP_ALLOC:
//      /* Out of TCP Sockets */
//			DEBUG("FATAL ERROR: NET_ERROR_TCP_ALLOC\n"));
//      break;

//    case NET_ERROR_TCP_STATE:
//      /* TCP State machine in undefined state */
//			DEBUG("FATAL ERROR: NET_ERROR_TCP_STATE\n"));
//      break;
//  }

//	assert_param(0);
//  /* End-less loop */
//  while (1);
//}
/**
@}
*/

