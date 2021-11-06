/**
******************************************************************************
* File Name          : Terminal.h
******************************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_H
#define __TERMINAL_H
#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "Terminal/Coin_Acceptor.h"
#include "Terminal/Bill_Acceptor.h"
#include "Terminal/Card_Dispenser.h"
#include "Terminal/Hopper.h"
#include "Terminal/Display.h"
#include "Terminal/Card_Reader.h"
#include "Terminal/Core.h"
/* Exported types ------------------------------------------------------------*/
/*###############################################################*/
/*###############################################################* DEBUG -->*/
/*###############################################################*/
#define DEBUG_TERMINAL_HOPPER
#define DEBUG_TERMINAL_CARD_READER
#define DEBUG_TERMINAL_COIN_ACCEPTOR
#define DEBUG_TERMINAL_BILL_ACCEPTOR
#define DEBUG_TERMINAL_CARD_DISPENSER
#define DEBUG_TERMINAL_CORE

//#define TERMINAL_USE_FREERTOS
//#define TERMINAL_USE_DMA
//#define TERMINAL_TEST
//#define TERMINAL_USE_WINDOWS

#define TERMINAL_WAIT_FOREVER 0xFFFFFFFF

/**
* @brief  Terminal buttons
*/
typedef enum {
	TERMINAL_BUTTON_UP = 0x00,
	TERMINAL_BUTTON_DOWN = 0x01,
	TERMINAL_BUTTON_LEFT = 0x02,
	TERMINAL_BUTTON_RIGHT = 0x03,
	TERMINAL_BUTTON_OK = 0x04,
	TERMINAL_BUTTON_SETTINGS = 0x05,
	TERMINAL_BUTTON_RETURN = 0x06,
} TERMINAL_ButtonsTypeDef;


///**
//* @brief  Terminal core error
//*/
//typedef enum {
//	TERMINAL_STATUS_READY = 0x00,
//	//command
//	TERMINAL_STATUS_SET_SETTINGS = 0x01,
//	TERMINAL_STATUS_NULL = 0x02,
//	TERMINAL_STATUS_SET_SETTINGS_MANUAL = 0x03,
//} TERMINAL_CoreStatusTypeDef;
///**
//* @brief  Terminal core status
//*/
//typedef enum {
//	TERMINAL_ERROR_OK = 0x00,
//	TERMINAL_ERROR_DISPLAY = 0x01,
//} TERMINAL_CoreErrorTypeDef;


/**
* @brief  Terminal rs485 structure
*/
typedef struct __TERMINAL_PortTypeDef
{
	uint32_t tx_timeout;
	uint32_t rx_timeout;
#ifdef TERMINAL_USE_UART
	UART_HandleTypeDef *huart;
	uint32_t rs485_re_pin;
	uint32_t rs485_re_port;
	uint32_t rs485_de_pin;
	uint32_t rs485_de_port;
#endif
} TERMINAL_PortTypeDef;






#ifdef TERMINAL_TEST
volatile extern bool Slave_Transmit_Enable;
volatile extern bool Slave_Receive_Enable;
#endif // TERMINAL_TEST
/* Exported constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /*__TERMINAL_H*/
