/**
  ******************************************************************************
  * File Name          : Coin_Acceptor.c
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "Terminal/Terminal.h"
//#include "Terminal.h"

#ifdef TERMINAL_USE_FREERTOS
#include "cmsis_os2.h"
#elif defined(TERMINAL_USE_WINDOWS)
#include "..\Threads.h"
#include <Windows.h>
#endif /*TERMINAL_USE_FREERTOS*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
//used when debugging, declared in the file Terminal.h
#ifdef DEBUG_TERMINAL_COIN_ACCEPTOR
#undef DEBUG /* DEBUG */
#undef DEBUG_PRINT /* DEBUG_PRINT */
#define DEBUG(x)			print("COIN ACCEPTOR: ");  print x;
#define DEBUG_PRINT(x)		print x;
#else
#define DEBUG(x)
#define DEBUG_PRINT(x)
#endif // DEBUG_TERMINAL_COIN_ACCEPTOR
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static bool Init(void);
static bool Reset(void);
static void Loop(void const * argument);
// declare the basic structure of the coin acceptor, it stores the current state of the coin acceptor,
// state of the port modules and commands and work with memory, etc.
static TERMINAL_HandleCoinAcceptorTypeDef coinacceptor = {
	Init,
	Reset,
	Loop
};


// functions used for debugging, display information in the console
// about errors of the corresponding bootloader modules

/* Exported functions --------------------------------------------------------*/
/*###############################################################*/
/*###############################################################* Delay -->*/
/*###############################################################*/
static void Delay(uint32_t ms)
{
#ifdef TERMINAL_USE_FREERTOS
	osDelay(ms);
#elif defined(TERMINAL_USE_HAL)
	HAL_Delay(ms);
#elif defined(TERMINAL_USE_WINDOWS)
	//std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	Sleep(ms);
#endif /*TERMINAL_USE_FREERTOS*/
}
/*###############################################################*/
/*###############################################################* Terminal_Get_HandleCoinAcceptor -->*/
/*###############################################################*/
// Returns a pointer to the main structure of the bootloader
TERMINAL_HandleCoinAcceptorTypeDef *Terminal_Get_HandleCoinAcceptor(void)
{
	return &coinacceptor;
}
/*###############################################################*/
/*###############################################################* Init -->*/
/*###############################################################*/
//initialize the module
static bool Init(void)
{
	coinacceptor.status = TERMINAL_COINACCEPTOR_STATUS_READY;
	coinacceptor.error = TERMINAL_COINACCEPTOR_ERROR_OK;
	coinacceptor.command = TERMINAL_COINACCEPTOR_STATUS_NULL;
	coinacceptor.responce = TERMINAL_COINACCEPTOR_STATUS_NULL;

	//memset((void *)&coinacceptor, 0, sizeof(coinacceptor));
	for (int i = 0; i < sizeof(coinacceptor.coins_accepted) / sizeof(float); i++) {
		coinacceptor.coins_accepted[i] = 0;
	}
	coinacceptor.coins_total = 0;
	coinacceptor.coin = 0;
	coinacceptor.count_coins = 0;
	coinacceptor.count_new_coins = 0;
	coinacceptor.fl_accepted = false;


	return true;
}
/*###############################################################*/
/*###############################################################* Reset -->*/
/*###############################################################*/
//reset the module
static bool Reset(void)
{
	coinacceptor.status = TERMINAL_COINACCEPTOR_STATUS_READY;
	coinacceptor.error = TERMINAL_COINACCEPTOR_ERROR_OK;
	coinacceptor.responce = TERMINAL_COINACCEPTOR_STATUS_NULL;

	//memset((void *)&coinacceptor, 0, sizeof(coinacceptor));
	for (int i = 0; i < sizeof(coinacceptor.coins_accepted) / sizeof(float); i++) {
		coinacceptor.coins_accepted[i] = 0;
	}
	coinacceptor.coins_total = 0;
	coinacceptor.coin = 0;
	coinacceptor.count_coins = 0;
	coinacceptor.count_new_coins = 0;
	coinacceptor.fl_accepted = false;
	return true;
}


/*###############################################################*/
/*###############################################################* Loop -->*/
/*###############################################################*/
static void Loop(void const * argument)
{
	while (1) {
		Delay(1);
		if (coinacceptor.command == TERMINAL_COINACCEPTOR_STATUS_SET_SETTINGS) {
			coinacceptor.responce = TERMINAL_COINACCEPTOR_STATUS_SET_SETTINGS;
			while (coinacceptor.command != TERMINAL_COINACCEPTOR_STATUS_NULL) {
				Delay(1);
			}
		}
		if (!coinacceptor.fl_accepted) continue;

		if (coinacceptor.coin != 0) {
			coinacceptor.coins_accepted[coinacceptor.count_coins] = coinacceptor.coin;
			coinacceptor.coins_total += coinacceptor.coin;
			coinacceptor.count_coins++;
			coinacceptor.count_new_coins++;
			if (coinacceptor.count_coins > 40) { coinacceptor.count_coins = 0; }
			if (coinacceptor.count_new_coins > 40) { coinacceptor.count_new_coins = 0; }

			DEBUG(("монетоприемник принял %0.2f\n", (float)(coinacceptor.coin) / 100.0f));
		}
		coinacceptor.fl_accepted = false;
		coinacceptor.status = TERMINAL_COINACCEPTOR_STATUS_ACCEPTED;

	}

}


