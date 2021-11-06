/**
  ******************************************************************************
  * File Name          : Coin_Acceptor.h
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_COIN_ACCEPTOR_H
#define __TERMINAL_COIN_ACCEPTOR_H
#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
//#include "Terminal/Terminal.h"


/**
* @brief  Terminal coin acceptor error
*/
typedef enum {
	TERMINAL_COINACCEPTOR_STATUS_READY = 0x00,
	TERMINAL_COINACCEPTOR_STATUS_ACCEPTED = 0x01,
	//command
	TERMINAL_COINACCEPTOR_STATUS_NULL = 0x02,
	TERMINAL_COINACCEPTOR_STATUS_SET_SETTINGS = 0x03,
} TERMINAL_CoinAcceptorStatusTypeDef;
/**
* @brief  Terminal coin acceptor status
*/
typedef enum {
	TERMINAL_COINACCEPTOR_ERROR_OK = 0x00,
} TERMINAL_CoinAcceptorErrorTypeDef;
/** 
  * @brief  Terminal main structure
  */
typedef struct __TERMINAL_HandleCoinAcceptorTypeDef
{
	bool(*init)(void);
	bool(*reset)(void);
	void(*loop)(void const * argument);
	TERMINAL_CoinAcceptorStatusTypeDef status;
	TERMINAL_CoinAcceptorErrorTypeDef error;
	TERMINAL_CoinAcceptorStatusTypeDef command;
	TERMINAL_CoinAcceptorStatusTypeDef responce;
	uint32_t	coins_accepted[40];
	uint32_t	coins_total;
	uint32_t	coin;
	uint32_t	count_coins;
	uint32_t	count_new_coins;
	bool		fl_accepted;
} TERMINAL_HandleCoinAcceptorTypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
TERMINAL_HandleCoinAcceptorTypeDef *Terminal_Get_HandleCoinAcceptor(void);

#ifdef __cplusplus
}
#endif
#endif /*__TERMINAL_COIN_ACCEPTOR_H*/
