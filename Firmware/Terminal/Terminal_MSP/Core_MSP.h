/**
  ******************************************************************************
  * File Name          : Core.h
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_CORE_H
#define __TERMINAL_CORE_H
#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include "Terminal/Coin_Acceptor.h"
#include "Terminal/Bill_Acceptor.h"
#include "Terminal/Card_Dispenser.h"
#include "Terminal/Hopper.h"
#include "Terminal/Display.h"
#include "Terminal/Card_Reader.h"

	 
	 /**
* @brief  Terminal main error
*/
typedef enum {
	TERMINAL_STATUS_READY = 0x00,
	//command
	TERMINAL_STATUS_SET_SETTINGS = 0x01,
	TERMINAL_STATUS_NULL = 0x02,
	TERMINAL_STATUS_SET_SETTINGS_MANUAL = 0x03,
} TERMINAL_CoreStatusTypeDef;
/**
* @brief  Terminal main status
*/
typedef enum {
	TERMINAL_ERROR_OK = 0x00,
	TERMINAL_ERROR_DISPLAY = 0x01,
} TERMINAL_CoreErrorTypeDef;
	 
/**
  * @brief  Terminal main structure
  */
typedef struct __TERMINAL_SettingsTypeDef
{
	uint32_t cost_coin_1; //Стоимость монет в хоппере 1
	uint32_t cost_coin_2; //Стоимость монет в хоппере 2
	uint32_t cost_card; //Стоимость карт в диспенсере
	uint32_t number_buttons; //Количество кнопок
	uint32_t number_spit_out_coins; //Кол-во выдаваемых монет за нажатие
	uint32_t number_spit_out_cards; //Кол-во выдаваемых карт за нажатие
	uint32_t number_coins; //Кол-во монет в хопперах
	uint32_t number_cards; //Кол-во карт в диспенсере
	uint32_t proportion_hoppers; //Пропорция выдачи монет
	uint32_t number_coinacceptors; //Количество монетоприемников
	uint32_t number_billacceptors; //Количество купюроприемников
	uint32_t number_hoppers; //Количество хопперов
	uint32_t number_carddispensers; //Количество диспенсеров
	uint32_t number_cardreaders; //Количество считывателей rfid
} TERMINAL_SettingsTypeDef;

#define NUM_SETTINGS_MANUAL	sizeof(TERMINAL_SettingsTypeDef)/4 - 1

/** 
  * @brief  Terminal main structure
  */
typedef struct __TERMINAL_HandleTypeDef
{
	TERMINAL_CoreStatusTypeDef status;
	TERMINAL_CoreErrorTypeDef error;
	TERMINAL_CoreStatusTypeDef command;
	TERMINAL_CoreStatusTypeDef responce;
	TERMINAL_HandleDisplaysTypeDef *display;
	TERMINAL_HandleCoinAcceptorTypeDef *coinacceptor;
	TERMINAL_HandleBillAcceptorTypeDef *billacceptor;
	TERMINAL_HandleCardDispenserTypeDef *carddispenser;
	TERMINAL_HandleCoreHopperTypeDef *hopper;
	TERMINAL_HandleCardReaderTypeDef *cardreader;
	TERMINAL_SettingsTypeDef settings;
	//char display_string[25];
	//uint32_t application_addr;
	//uint32_t application_size;
	uint32_t money_total_in;
	uint32_t money_in;
	uint32_t money_total_out;
	uint32_t money_out;
	uint32_t money_total;
	uint32_t tickstart_for_split_out;
	uint32_t time_for_split_out;
	bool fl_new_money;
	bool event_spit_out_cards;
	bool event_spit_out_coins;
	bool event_insert_card;
	bool event_deposit_money;
	bool event_spit_out_hopper_1;
	bool event_spit_out_hopper_2;
	bool event_save_manual;

	bool enable_insert_card;

	bool enable_button_carddispenser;
	bool enable_button_cardreader;
	bool enable_button_hoppers;
	bool enable_button_hopper_1;
	bool enable_button_hopper_2;

	bool hold_button_hopper_1;
	bool hold_button_hopper_2;

	bool enable_button_up;
	bool enable_button_down;
	bool enable_button_left;
	bool enable_button_right;
	bool enable_button_ok;
	bool enable_button_settings;
	bool enable_button_return;
} TERMINAL_HandleTypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void Terminal_Init(void);
TERMINAL_HandleTypeDef *Terminal_Get_Handle(void);
void Terminal_Loop(void const * argument);
#ifdef TERMINAL_USE_WINDOWS
//bool Display_String(const char *string);
//bool Display_Money_String(uint32_t dig);
#endif /*TERMINAL_USE_FREERTOS*/

#ifdef __cplusplus
}
#endif
#endif /*__TERMINAL_CORE_H*/
