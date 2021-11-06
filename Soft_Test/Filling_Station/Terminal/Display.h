/**
  ******************************************************************************
  * File Name          : Display.h
  ******************************************************************************
  */
  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_DISPLAY_INTERFACE_H
#define __TERMINAL_DISPLAY_INTERFACE_H
//#ifdef __cplusplus
// extern "C" {
//#endif
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "Tamplates.h"
#include "cmsis_os2.h"


#ifdef TERMINAL_USE_WINDOWS
#include <thread>
#include <chrono>
#include <queue>
#endif /*TERMINAL_USE_STM*/
/* Exported types ------------------------------------------------------------*/
//
///**
//* @brief  Terminal display_1 status
//*/
//typedef enum {
//	TERMINAL_DISPLAY_STATUS_READY = 0x00,
//	TERMINAL_DISPLAY_STATUS_BUSY 	= 0x01,
//	TERMINAL_DISPLAY_STATUS_ERROR = 0x02,
//	TERMINAL_DISPLAY_STATUS_WAIT 	= 0x03,
//	//port
//	TERMINAL_PORT_ERROR_RX_TIMEOUT	= 0x04,
//	TERMINAL_PORT_ERROR_RX					= 0x05,
//	TERMINAL_PORT_ERROR_TX_TIMEOUT	= 0x06,
//	TERMINAL_PORT_ERROR_TX					= 0x07,
//	//commands
//	TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED	= 0x08,
//	TERMINAL_DISPLAY_STATUS_MONEY_TOTAL			= 0x09,
//	TERMINAL_DISPLAY_STATUS_STRING_ARR			= 0x10,
//	TERMINAL_DISPLAY_STATUS_SPIT_OUT_CARDS	= 0x11,
//	TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED_REPLAY = 0x12,
//	TERMINAL_DISPLAY_STATUS_STRING	= 0x13,
//	TERMINAL_DISPLAY_STATUS_NULL		= 0x14,
//	TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED_WITH_CARD = 0x15,
//	TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED_REPLAY_WITH_CARD = 0x16,
//} TERMINAL_DisplayStatusTypeDef;
//
///**
//* @brief  Terminal display_1 error
//*/
//typedef enum {
//	TERMINAL_DISPLAY_ERROR_OK = 0x0U,
//	TERMINAL_DISPLAY_ERROR_TX = 0x1U,
//	TERMINAL_DISPLAY_ERROR_RX = 0x2U,
//	TERMINAL_DISPLAY_ERROR_TX_TIMEOUT = 0x3U,
//	TERMINAL_DISPLAY_ERROR_RX_TIMEOUT = 0x4U,
//} TERMINAL_DisplayErrorTypeDef;
///**
//* @brief  Terminal serial structure
//*/
//typedef struct __TERMINAL_HandleDisplayInterfaceTypeDef
//{
//	TERMINAL_DisplayStatusTypeDef status;
//	TERMINAL_DisplayStatusTypeDef command;
//	TERMINAL_DisplayErrorTypeDef error;
//	uint32_t tx_timeout;
//	uint32_t rx_timeout;
//	char display_string[25];
//	char display_string_1[25];
//	char display_string_2[25];
//	uint32_t count;
//	//char string_arr[25][5];
//	//uint32_t num_string;
//	//uint32_t delay_arr[5];
//
//	//uint32_t timeout_state_ready;
//	uint32_t tickstart;
//#ifdef TERMINAL_USE_RS485
//	UART_HandleTypeDef *huart;
//	uint32_t rs485_re_pin;
//	uint32_t rs485_re_port;
//	uint32_t rs485_de_pin;
//	uint32_t rs485_de_port;
//#endif
//	void(*transmit_enable)(void);
//	void(*receive_enable)(void);
//	bool(*init)(void);
//	bool(*reset)(void);
//	bool(*reset_tickstart)(void);
//#ifdef TERMINAL_USE_STM
//__NO_RETURN	void(*loop)(void *arg);
//#else
//			void(*loop)(void const *arg);
//#endif
//} TERMINAL_HandleDisplayTypeDef;
///**
//* @brief  Terminal serial structure
//*/
//typedef struct __TERMINAL_HandleDisplaysInterfaceTypeDef
//{
//	TERMINAL_DisplayStatusTypeDef status;
//	TERMINAL_DisplayStatusTypeDef command;
//	TERMINAL_DisplayErrorTypeDef error;
//	TERMINAL_HandleDisplayTypeDef *display_1;
//	TERMINAL_HandleDisplayTypeDef *display_2;
//	uint32_t timeout_state_ready;
//	uint32_t tickstart;
//#ifdef TERMINAL_USE_STM
//__NO_RETURN	void(*loop)(void *arg);
//#else
//			void(*loop)(void const *arg);
//#endif
//	bool(*init)(void);
//	bool(*reset)(void);
//	bool(*reset_tickstart)(void);
//	bool(*send)(TERMINAL_HandleDisplayTypeDef *display, uint8_t *data, uint32_t size);
//	bool(*receive)(TERMINAL_HandleDisplayTypeDef *display, uint8_t *data, uint32_t size);
//} TERMINAL_HandleDisplaysTypeDef;
/* Exported constants --------------------------------------------------------*/
#define RS485_EN_Pin GPIO_PIN_7
#define RS485_EN_GPIO_Port GPIOD
//
///* Exported Macros -----------------------------------------------------------*/
///* Exported functions --------------------------------------------------------*/
//
//#ifdef __cplusplus
//}
//#endif

namespace DisplayNS
{

	typedef enum:uint32_t {
		//NONE = 0x11,
		READY = 0x01,
		MONEY = 0x02,
		SPIT_OUT_MONEY = 0x03,
		STRING = 0x04,
		STRING_ERROR = 0x05,
	} COMMAND;

	struct MessageClass
	{
		COMMAND command;
		uint32_t money;
	};



	class DisplayMSPClass
	{
	public:
		char display_string[10];
		QueueMessageClass< MessageClass, 10 > Messages;
		DisplayMSPClass() {
		}
    void Init();

	};
	/**
	* @brief  Terminal serial structure
	*/
	class DisplayClass
	{
	public:
		DisplayMSPClass	Display_1;

	public:
    DisplayClass();
    void Init();
		static void Display_1_Thread(void* arg);
		static bool Display_Send(DisplayMSPClass* display, const char* data);
		static bool Display_Send(DisplayMSPClass* display, int money);
	};
	extern DisplayClass Displays;
}

#endif /*__TERMINAL_DISPLAY_INTERFACE_H*/
/************************ (C) COPYRIGHT *****END OF FILE****/
