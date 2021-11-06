///**
//  ******************************************************************************
//  * File Name          : Core.h
//  ******************************************************************************
//  */
//  /* Define to prevent recursive inclusion -------------------------------------*/
//#ifndef __TERMINAL_CORE_H
//#define __TERMINAL_CORE_H
//#ifdef __cplusplus
//extern "C" {
//#endif
//	/* Includes ------------------------------------------------------------------*/
//#include <stdbool.h>
//#include <stdint.h>
//#include "Terminal/Bill_Acceptor.h"
//#include "Terminal/Hopper.h"
//#include "Terminal/Display.h"
//
//
//	 /**
//* @brief  Terminal main error
//*/
//	typedef enum {
//		TERMINAL_STATUS_READY = 0x00,
//		//command
//		TERMINAL_STATUS_SET_SETTINGS = 0x01,
//		TERMINAL_STATUS_NULL = 0x02,
//		TERMINAL_STATUS_SET_SETTINGS_MANUAL = 0x03,
//		TERMINAL_STATUS_ENCASHMENT = 0x04,
//	} TERMINAL_CoreStatusTypeDef;
//	/**
//	* @brief  Terminal main status
//	*/
//	typedef enum {
//		TERMINAL_ERROR_OK = 0x00,
//		TERMINAL_ERROR_DISPLAY = 0x01,
//	} TERMINAL_CoreErrorTypeDef;
//
//	/**
//	* @brief  Terminal buttons
//	*/
//	typedef enum {
//		TERMINAL_BUTTON_HOPPERS = 1 << 0,
//		TERMINAL_BUTTON_HOPPER_1 = 1 << 1,
//		TERMINAL_BUTTON_HOPPER_2 = 1 << 2,
//		TERMINAL_BUTTON_CARD_DISPANSER = 1 << 3,
//		TERMINAL_BUTTON_DEPOSIT = 1 << 4,
//		TERMINAL_BUTTON_UP = 1 << 5,
//		TERMINAL_BUTTON_DOWN = 1 << 6,
//		TERMINAL_BUTTON_LEFT = 1 << 7,
//		TERMINAL_BUTTON_RIGHT = 1 << 8,
//		TERMINAL_BUTTON_OK = 1 << 9,
//		TERMINAL_BUTTON_SETTINGS = 1 << 10,
//		TERMINAL_BUTTON_RETURN = 1 << 11,
//		TERMINAL_BUTTON_ENCASHMENT = 1 << 12,
//	} TERMINAL_ButtonsTypeDef;
//
//	/**
//	  * @brief  Terminal main structure
//	  */
//#pragma pack (push, 4)
//	typedef struct __TERMINAL_SettingsTypeDef
//	{
//		int32_t cost_coin_1; //Стоимость монет в хоппере 1
//		int32_t cost_coin_2; //Стоимость монет в хоппере 2
//		int32_t cost_card; //Стоимость карт в диспенсере
//		uint32_t number_buttons; //Количество кнопок
//		uint32_t number_spit_out_coins; //Кол-во выдаваемых монет за нажатие
//		uint32_t number_spit_out_cards; //Кол-во выдаваемых карт за нажатие
//		int32_t number_coins; //Кол-во монет в хопперах
//		int32_t number_cards; //Кол-во карт в диспенсере
//		uint32_t proportion_hoppers; //Пропорция выдачи монет
//		uint32_t number_coinacceptors; //Количество монетоприемников
//		uint32_t number_billacceptors; //Количество купюроприемников
//		uint32_t number_hoppers; //Количество хопперов
//		uint32_t number_carddispensers; //Количество диспенсеров
//		uint32_t number_cardreaders; //Количество считывателей rfid
//		uint32_t diapason_hold_acceptors; //Разница между внесенными деньгами и общей суммой в хопперах, для отключения приемников
//		uint32_t key; //Ключ сохранения
//	} TERMINAL_SettingsTypeDef;
//#pragma pack ( pop)
//
//#define NUM_SETTINGS_MANUAL	sizeof(TERMINAL_SettingsTypeDef)/4 - 1
//
//	/**
//	  * @brief  Terminal main structure
//	  */
//	typedef struct __TERMINAL_HandleTypeDef
//	{
//		TERMINAL_CoreStatusTypeDef status;
//		TERMINAL_CoreErrorTypeDef error;
//		TERMINAL_CoreStatusTypeDef command;
//		TERMINAL_CoreStatusTypeDef responce;
//		TERMINAL_HandleDisplaysTypeDef* display;
//		TERMINAL_HandleBillAcceptorTypeDef* billacceptor;
//		TERMINAL_HandleCoreHopperTypeDef* hopper;
//		TERMINAL_SettingsTypeDef settings;
//		TERMINAL_SettingsTypeDef settings_receive;
//#ifdef TERMINAL_USE_WINDOWS
//		TERMINAL_SettingsTypeDef settings_send;
//#endif //TERMINAL_USE_STM
//		//char display_string[25];
//		//uint32_t application_addr;
//		//uint32_t application_size;
//		int32_t money_total_in;
//		int32_t money_in;
//		int32_t money_total_out;
//		int32_t money_out;
//		int32_t money_total;
//		uint32_t tickstart_for_split_out;
//		uint32_t time_for_split_out;
//		bool fl_new_money;
//		bool event_spit_out_coins;
//		bool event_deposit_money;
//		bool event_spit_out_hopper_1;
//		bool event_spit_out_hopper_2;
//		bool event_save_manual;
//
//		bool event_button_up;
//		bool event_button_down;
//		bool event_button_left;
//		bool event_button_right;
//		bool event_button_ok;
//		bool event_button_settings;
//		bool event_button_encashment;
//		bool event_button_return;
//
//
//		bool enable_button_up;
//		bool enable_button_down;
//		bool enable_button_left;
//		bool enable_button_right;
//		bool enable_button_ok;
//		bool enable_button_settings;
//		bool enable_button_return;
//		bool enable_button_encashment;
//		//нужны для замарозки хоппер когда закончились монеты и 
//		//переключаемся на другой хоппер. Чтоб не было замкнутого цикла
//		bool hold_hopper_1;
//		bool hold_hopper_2;
//		bool hold_terminal;
//		bool hold_bill_acceptor;
//		
//		
//		bool enable_exti_hopper1;
//		bool enable_exti_hopper2;
//		bool enable_exti_buttons;
//	} TERMINAL_HandleTypeDef;
//
//	/* Exported constants --------------------------------------------------------*/
//	/* Exported Macros -----------------------------------------------------------*/
//	/* Exported functions --------------------------------------------------------*/
//	void Terminal_Init(void);
//	TERMINAL_HandleTypeDef* Terminal_Get_Handle(void);
//#ifdef TERMINAL_USE_STM
//	__NO_RETURN void Terminal_Loop(void* arg);
//#else
//	void Terminal_Loop();
//#endif
//#ifdef TERMINAL_USE_WINDOWS
//	//bool Display_String(const char *string);
//	//bool Display_Money_String(uint32_t dig);
//#endif /*TERMINAL_USE_STM*/
//
//#ifdef __cplusplus
//}
//#endif
//#endif /*__TERMINAL_CORE_H*/

#ifndef __TERMINAL_CORE_H
#define __TERMINAL_CORE_H

class CoreClass
{
	public:
		int32_t Money; //храним текущие деньги в обменнике
	public:
		CoreClass();
    void Init();
		static void Core_Thread(void* arg);
};

extern CoreClass Terminal;
#endif /*__TERMINAL_CORE_H*/
