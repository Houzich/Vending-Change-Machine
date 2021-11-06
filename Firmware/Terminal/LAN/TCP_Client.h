/**
  ******************************************************************************
  * @file    TCP_Client.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TCP_CLIENT_H
#define __TCP_CLIENT_H
#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "rl_net.h"                     // Keil.MDK-Pro::Network:CORE
#include "rl_net_ds.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern uint64_t tcp_client_stk[];
extern const osThreadAttr_t tcp_client_attr;
extern int32_t tcp_sock;
extern int32_t tcp_display_sock;
/* Exported macro ------------------------------------------------------------*/

#define TCPCLIENT_MSGQUEUE_OBJECTS 40
typedef struct {                                // object data type
  uint8_t* buff;
  int len;
} TCPClientMsgQueueTypeDef;

extern osEventFlagsId_t TCPClient_Event_ID;   
enum EventTCPClient{
  SEND_SETTINGS = (1<<0),
  SEND_BUTTON_STATE = (1<<1),
  SEND_TERMINAL_STATE = (1<<2),
  SEND_HOPPER_1_STATE = (1<<3),
  SEND_HOPPER_2_STATE = (1<<4),
  SEND_HOPPER_3_STATE = (1<<5),
};

/* Exported functions ------------------------------------------------------- */
extern void tcp_client (void *arg);
void debug_net_status_printf(netStatus net_status, const char *str);
void debug_tcp_status_printf(netTCP_State tcp_state, const char *str);

#ifdef __cplusplus
}
#endif
#endif /* __TCP_CLIENT_H */

/*****************************END OF FILE****/
