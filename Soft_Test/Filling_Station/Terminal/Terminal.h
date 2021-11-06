///**
//******************************************************************************
//* File Name          : Terminal.h
//******************************************************************************
//*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_H
#define __TERMINAL_H
//#ifdef __cplusplus
// extern "C" {
//#endif
///* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifdef TERMINAL_USE_WINDOWS
#include <queue>
#include <thread>
#include <chrono>
#endif // TERMINAL_USE_WINDOWS

#include "Terminal/Bill_Acceptor.h"
#include "Terminal/Hopper.h"
#include "Terminal/Display.h"
#include "Terminal/Core.h"
//#include "Terminal/Settings.h"



#ifdef TERMINAL_USE_STM
#include "Terminal_MSP.h"
#include "Bill_Acceptor_MSP.h"
#include "Hopper_1_MSP.h"
#include "Hopper_2_MSP.h"
#include "Hoppers_MSP.h"
#include "Buttons_MSP.h"
#endif // TERMINAL_USE_STM

/* Exported types ------------------------------------------------------------*/
/*###############################################################*/
/*###############################################################* DEBUG -->*/
/*###############################################################*/
#ifdef TERMINAL_DEBUG
#define DEBUG_TERMINAL_HOPPER
#define DEBUG_TERMINAL_DISPLAY
#define DEBUG_TERMINAL_CARD_READER
#define DEBUG_TERMINAL_COIN_ACCEPTOR
#define DEBUG_TERMINAL_BILL_ACCEPTOR
#define DEBUG_TERMINAL_CARD_DISPENSER
#define DEBUG_TERMINAL_CORE
#define DEBUG_TERMINAL_SETTINGS
#define DEBUG_TERMINAL_BILL_ACCEPTOR_MSP
#define DEBUG_FLASH
#define DEBUG_RTC
#define DEBUG_TERMINAL_CARD_READER_MSP
#define DEBUG_TERMINAL_BUTTONS_MSP
#define DEBUG_TERMINAL_JSON
#define DEBUG_TERMINAL_HOPPER_MSP

#endif //TERMINAL_DEBUG

//#define TERMINAL_USE_DMA
//#define TERMINAL_TEST
//#define TERMINAL_USE_WINDOWS
//#define TERMINAL_USE_USB_FOR_DEBUG
//#define TERMINAL_USE_ETH_FOR_DEBUG

//#define USB_FS_VIRTUAL_COM

#ifdef TERMINAL_USE_STM
#ifdef TERMINAL_RELEASE
#define DISPLAY_PORT_RS485
//#define DISPLAY_PORT_ETH
#else
#define DISPLAY_PORT_RS485
#define DISPLAY_PORT_ETH
#endif //TERMINAL_RELEASE 
#endif //TERMINAL_USE_STM




#ifdef TERMINAL_USE_WINDOWS
#define sprintf	sprintf_s
#define strncpy	strncpy_s
#define _ARMABI
#define ThreadYield Yield
#else
#define ThreadYield osThreadYield
#endif // TERMINAL_USE_WINDOWS

#ifdef TERMINAL_USE_USB_FOR_DEBUG
_ARMABI int print(const char *format, ...);
#define debug_print	print
#elif defined(TERMINAL_USE_ETH_FOR_DEBUG)
_ARMABI int eth_print(const char *format, ...);
_ARMABI int eth_header_print(const char *str, const char *format, ...);
#define debug_header	eth_header_print
#define debug_print	eth_print
#else
#ifdef TERMINAL_USE_STM
_ARMABI int header_print(const char* str, const char* format, ...);
#else
int header_print(const char* str, const char* format, ...);
#endif // TERMINAL_USE_STM
#define debug_header header_print
#define debug_print	printf
#endif // TERMINAL_USE_USB_FOR_DEBUG


#define TERMINAL_WAIT_FOREVER 0xFFFFFFFF
	 



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



#ifdef TERMINAL_TEST
volatile extern bool Slave_Transmit_Enable;
volatile extern bool Slave_Receive_Enable;
#endif // TERMINAL_TEST


#pragma pack (push, 4)
typedef struct __TERMINAL_HopperStateForServerTypeDef
{
	int	inhibit_pin_state;
	int	meter_pin_state;
	int	credit_pin_state;
	int	coin_empty_pin_state;
	int	inhibit_no_pin_exti;
	int	meter_no_pin_exti;
	int	credit_no_pin_exti;
	int	coin_empty_no_pin_exti;
	int	payout_in_pin_exti;	
} TERMINAL_HopperStateForServerTypeDef;
#pragma pack ( pop)

/* Exported constants --------------------------------------------------------*/
#ifdef TERMINAL_USE_STM



//#define TERMINAL_USE_TCP_SEMAPHORE

#ifdef TERMINAL_USE_TCP_SEMAPHORE
#define sid_ETH_Debug_Semaphore     sid_ClientTCP_Semaphore
#define sid_ETH_Display_Semaphore   sid_ClientTCP_Semaphore
extern osSemaphoreId_t sid_ClientTCP_Semaphore;
//extern osSemaphoreId_t sid_ETH_Debug_Semaphore;
//extern osSemaphoreId_t sid_ETH_Display_Semaphore;
#define TCPClientSemaphoreAcquire(x,y) osSemaphoreAcquire(x,y)
#define TCPClientSemaphoreRelease(x) osSemaphoreRelease(x)
#else
#define TCPClientSemaphoreAcquire(x,y)
#define TCPClientSemaphoreRelease(x)
#endif // TERMINAL_USE_TCP_SEMAPHORE


extern osMutexId_t ClientTCP_Mutex_ID; 
extern  const osMutexAttr_t ClientTCP_Mutex_attr;
/*###############################################################*/
 /* definition and creation of CoreTask */
extern const osThreadAttr_t CoreTask_attributes;
extern osThreadId_t Core_TaskHandle;
/*###############################################################*/
 /* definition and creation of CardreaderTask */
extern const osThreadAttr_t CardreaderTask_attributes;
extern osThreadId_t Cardreader_TaskHandle;
/*###############################################################*/
 /* definition and creation of BillAcceptorTask */
extern const osThreadAttr_t BillAcceptorTask_attributes;
extern osThreadId_t BillAcceptor_TaskHandle;
/*###############################################################*/
 /* definition and creation of CardDispanserTask */
extern const osThreadAttr_t CardDispanserTask_attributes;
extern osThreadId_t CardDispanser_TaskHandle;
/*###############################################################*/
 /* definition and creation of CionAcceptorTask */
extern const osThreadAttr_t CionAcceptorTask_attributes;
extern osThreadId_t CionAcceptor_TaskHandle;
/*###############################################################*/
 /* definition and creation of Display1Task */
extern const osThreadAttr_t Display1Task_attributes;
extern osThreadId_t Display1_TaskHandle;
/*###############################################################*/
 /* definition and creation of Display2Task */
extern const osThreadAttr_t Display2Task_attributes;
extern osThreadId_t Display2_TaskHandle;
/*###############################################################*/
 /* definition and creation of HopperTask */
extern const osThreadAttr_t HopperTask_attributes;
extern osThreadId_t Hopper_TaskHandle;
#endif //TERMINAL_USE_STM
/* Exported Macros -----------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
extern uint8_t *EthDebugBuf;
extern uint8_t *EthSettingsBuf;
extern uint8_t *DisplayBuf;


int Send_Settings_ETH(void);
int Send_Button_State_ETH(void);
uint32_t Check_CMSIS_Flags_Functions_Error_Codes(uint32_t flags);
int Send_Hopper_State_ETH(int num);
#define  DEBUG_USB_BUFFER_SIZE      (1024)    // USB Buffer Size
#define  DEBUG_ETH_BUFFER_SIZE      (256)    // ETH Buffer Size
//#ifdef __cplusplus
//}
//#endif

#ifdef TERMINAL_USE_STM
#define  Delay(ms)	osDelay(ms)
#else
#define  Delay(ms)	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
#endif // TERMINAL_USE_STM


#endif /*__TERMINAL_H*/
