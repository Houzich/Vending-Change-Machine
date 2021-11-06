/**
  ******************************************************************************
  * File Name          : Core.c
  ******************************************************************************
  */
  /* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "Terminal/Core.h"
#include "Terminal/Terminal.h"
#include "Terminal/Settings.h"

#ifdef TERMINAL_USE_FREERTOS
#include "cmsis_os2.h"
#include "stm32f4xx.h"
#elif defined(TERMINAL_USE_WINDOWS)
#include "..\Threads.h"
#include <Windows.h>
#endif /*TERMINAL_USE_FREERTOS*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
//used when debugging, declared in the file Terminal.h
#ifdef DEBUG_TERMINAL_CORE
#undef DEBUG /* DEBUG */
#undef DEBUG_CORE /* DEBUG_CORE */
#undef DEBUG_PRINT /* DEBUG_PRINT */
#define DEBUG(x)			print("TERMINAL: ");  print x;
#define DEBUG_CORE(x)		print("TERMINAL CORE: "); print x;
#define DEBUG_PRINT(x)		print x;
#else
#define DEBUG(x)
#define DEBUG_CORE(x)
#define DEBUG_PRINT(x)
#endif // DEBUG_TERMINAL_CORE
/* Private variables ---------------------------------------------------------*/
// declare the basic structure of the terminal, it stores the current state of the terminal,
// state of the port modules and commands and work with memory, etc.
TERMINAL_HandleTypeDef terminal;
/* Private function prototypes -----------------------------------------------*/
// functions used for debugging, display information in the console
// about errors of the corresponding bootloader modules

/* Exported functions --------------------------------------------------------*/
static void Change_Money_Total(int32_t money);
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
#ifdef TERMINAL_USE_WINDOWS
/*###############################################################*/
/*###############################################################* HAL_GetTick -->*/
/*###############################################################*/
static uint32_t HAL_GetTick(void) {
	uint32_t result = GetTickCount();
	return result;
}
#endif // TERMINAL_USE_WINDOWS
/*###############################################################*/
/*###############################################################* Terminal_Slave_Get_Handle -->*/
/*###############################################################*/
// Returns a pointer to the main structure of the bootloader
TERMINAL_HandleTypeDef *Terminal_Get_Handle(void)
{
	return &terminal;
}
/*###############################################################*/
/*###############################################################* Terminal_Slave_Init -->*/
/*###############################################################*/
// Initialize the main structure of the bootloader, here it is set
// initial values, configurable port
void Terminal_Init(void)
{
	terminal.status = TERMINAL_STATUS_READY;
	terminal.error = TERMINAL_ERROR_OK;
	terminal.command = TERMINAL_STATUS_NULL;
	terminal.responce = TERMINAL_STATUS_NULL;
	terminal.money_total_in = 0;
	terminal.money_in = 0;
	terminal.money_total_out = 0;
	terminal.money_out = 0;
	terminal.money_total = 0;
	terminal.tickstart_for_split_out = 0;
	terminal.time_for_split_out = 0;
	terminal.fl_new_money = false;
	terminal.event_spit_out_cards = false;
	terminal.enable_button_carddispenser = false;
	terminal.event_spit_out_coins = false;
	terminal.enable_button_hoppers = false;
	terminal.event_insert_card = false;
	terminal.enable_insert_card = false;
	terminal.event_deposit_money = false;
	terminal.enable_button_cardreader = false;
	terminal.event_spit_out_hopper_1 = false;
	terminal.event_spit_out_hopper_2 = false;
	terminal.enable_button_hopper_1 = false;
	terminal.enable_button_hopper_2 = false;
	terminal.hold_button_hopper_1 = false;
	terminal.hold_button_hopper_2 = false;
	terminal.event_save_manual = false;

	terminal.enable_button_up = false;
	terminal.enable_button_down = false;
	terminal.enable_button_left = false;
	terminal.enable_button_right = false;
	terminal.enable_button_ok = false;
	terminal.enable_button_settings = false;
	terminal.enable_button_return = false;

	terminal.display = Terminal_Get_HandleDisplay();
	terminal.display->init();
	terminal.coinacceptor = Terminal_Get_HandleCoinAcceptor();
	terminal.coinacceptor->init();
	terminal.billacceptor = Terminal_Get_HandleBillAcceptor();
	terminal.billacceptor->init();

	terminal.carddispenser = Terminal_Get_HandleCardDispenser();
	terminal.carddispenser->init();
	terminal.carddispenser->cards_total = terminal.settings.number_cards;
	terminal.carddispenser->spit_out_cards = terminal.settings.number_spit_out_cards;
	if (terminal.settings.number_hoppers == 1) {
		terminal.hopper = Terminal_Get_HandleHopper();
		terminal.hopper->init(1);
		terminal.hopper->proportion_hoppers = 100;
		terminal.hopper->hopper_1->coins_total = terminal.settings.number_coins;
		terminal.hopper->hopper_1->value_of_coins = terminal.settings.cost_coin_1;
		terminal.hopper->spit_out_coins = terminal.settings.number_spit_out_coins;
	}
	else if (terminal.settings.number_hoppers == 2) {
		terminal.hopper = Terminal_Get_HandleHopper();
		terminal.hopper->init(2);
		terminal.hopper->proportion_hoppers = terminal.settings.proportion_hoppers;
		terminal.hopper->hopper_1->coins_total = terminal.settings.number_coins;
		terminal.hopper->hopper_2->coins_total = terminal.settings.number_coins;
		terminal.hopper->hopper_1->value_of_coins = terminal.settings.cost_coin_1;
		terminal.hopper->hopper_2->value_of_coins = terminal.settings.cost_coin_2;
		terminal.hopper->spit_out_coins = terminal.settings.number_spit_out_coins;
	}
	else {
		terminal.hopper = Terminal_Get_HandleHopper();
		terminal.hopper->init(0);
	}

	terminal.cardreader = Terminal_Get_HandleCardReader();
	terminal.cardreader->init();

}
/*###############################################################*/
/*###############################################################* Terminal_Slave_Init -->*/
/*###############################################################*/
//reset loader pointers
static void Terminal_Reset(void)
{
	uint32_t money = terminal.money_total;
	Terminal_Init();
	terminal.money_total_in = money;
	terminal.money_total = money;
	terminal.money_in = money;
}
/*###############################################################*/
/*###############################################################* Check_Error_Terminal -->*/
/*###############################################################*/
// Check the current state of each module if the state is critical
// and requires the loader to stop working, then set fatal_error = true,
// then boot.status = TERMINAL_STATUS_FATAL_ERROR. Otherwise
// reset the state of the loader modules (boot.status = TERMINAL_STATUS_RESET;)
static bool Check_Terminal_Status(void)
{
	return true;
}

/*###############################################################*/
/*###############################################################* Terminal_Listen_Command -->*/
/*###############################################################*/
// Accept two bytes and if they match the bootloader command, call the corresponding
// function of the commands module (located in the Slave_Commands.c file)
bool Terminal_Listen_Command(void)
{

	return 0;
}
/*###############################################################*/
/*###############################################################* Wait_Handle_If_Error -->*/
/*###############################################################*/
static void Handle_Hopper_Error(TERMINAL_HandleCoreHopperTypeDef *hpr) {

	if (hpr->status == TERMINAL_HOPPER_STATUS_ERROR) {
		if (hpr->error == TERMINAL_HOPPER_ERROR_NO_COINS)
		{
			hpr->Send_Command(TERMINAL_HOPPER_STATUS_DO_NOT_STOP);
			while (hpr->responce != TERMINAL_HOPPER_STATUS_DO_NOT_STOP) { 
			Delay(1); 
			}
			hpr->Send_Command(TERMINAL_HOPPER_STATUS_READY);
		}
	}
}
/*###############################################################*/
/*###############################################################* Display_Money -->*/
/*###############################################################*/
bool Display_Money(char *display_string, uint32_t dig)
{
	char str[10];
	float money_f = (float)dig / 100.0f;
	snprintf(str, 6, "%5.2f", money_f);
	for (int i = 0; i < 5; i++)
		if (str[i] == ' ')
			str[i] = '0';
	snprintf(display_string, 6, "%s", str);
	return 0;
}
/*###############################################################*/
/*###############################################################* Display_Money -->*/
/*###############################################################*/
bool Display_Set_String(TERMINAL_HandleDisplayTypeDef *display, char *display_string)
{
	snprintf(display->display_string_1, 6, "%s", display_string);
	return true;
}
/*###############################################################*/
/*###############################################################* Display_String -->*/
/*###############################################################*/
bool Display_Strings(const char *string_1, const char *string_2, uint32_t num)
{
	if ((num == 1) || (num == 3)) {
		snprintf(terminal.display->display_1->display_string_1, 6, "%s", string_1);
	}
	if (num == 2) {
		snprintf(terminal.display->display_2->display_string_1, 6, "%s", string_2);
	}
	if (num == 1) return true;
	if (num == 2) return true;

	const char *string;
	string = (string_2 != NULL) ? string_2: string_1;
	snprintf(terminal.display->display_2->display_string_1, 6, "%s", string);
	terminal.display->command = TERMINAL_DISPLAY_STATUS_STRING;
	return true;
}
/*###############################################################*/
/*###############################################################* Display_Money_String -->*/
/*###############################################################*/
bool Display_Money_String(uint32_t dig)
{
	TERMINAL_HandleDisplaysTypeDef *display = terminal.display;
	char str[10];
	float money_f = (float)dig / 100.0f;
	snprintf(str, 6, "%5.2f", money_f);
	for (int i = 0; i < 5; i++)
		if (str[i] == ' ')
			str[i] = '0';
	snprintf(display->display_1->display_string_1, 6, "%s", str);
	display->command = TERMINAL_DISPLAY_STATUS_STRING;
	return true;
}
/*###############################################################*/
/*###############################################################* Display_Money -->*/
/*###############################################################*/
bool Display_Money_Accepted(int32_t dig1, int32_t dig2, int32_t dig3)
{
	TERMINAL_HandleDisplayTypeDef *display_1 = terminal.display->display_1;
	TERMINAL_HandleDisplayTypeDef *display_2 = terminal.display->display_2;
	Display_Money(display_1->display_string_1, dig1);
	Display_Money(display_1->display_string_2, dig2);
	if (dig3 != -1) {
		Display_Money(display_2->display_string_1, dig3);
	}
	
	//display->reset_tickstart();
	if (terminal.display->status == TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED) {
		terminal.display->command = TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED_REPLAY;
	}
	else {
		terminal.display->command = TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED;
	}
	return 0;
}
/*###############################################################*/
/*###############################################################* Disable_Buttons -->*/
/*###############################################################*/
bool Disable_Buttons(void)
{
	terminal.enable_button_carddispenser = false;
	terminal.enable_button_hoppers = false;
	terminal.enable_button_hoppers = false;
	terminal.enable_button_cardreader = false;
	terminal.enable_button_hopper_1 = false;
	terminal.enable_button_hopper_2 = false;
	terminal.enable_button_up = false;
	terminal.enable_button_down = false;
	terminal.enable_button_left = false;
	terminal.enable_button_right = false;
	terminal.enable_button_ok = false;
	terminal.enable_button_settings = false;
	terminal.enable_button_return = false;
	return true;
}
/*###############################################################*/
/*###############################################################* Wait_Hopper_Redy -->*/
/*###############################################################*/
bool Wait_Hopper_Redy(uint32_t timeout)
{
	TERMINAL_HandleCoreHopperTypeDef *hopper = terminal.hopper;
	while (hopper->responce != TERMINAL_HOPPER_STATUS_READY) {
		Delay(1);
	}
	return 0;
}

/*###############################################################*/
/*###############################################################* Spit_Out_Hopper -->*/
/*###############################################################*/
bool Spit_Out_Cards(uint32_t timeout) {
	TERMINAL_HandleCardDispenserTypeDef *carddispenser = terminal.carddispenser;

	Display_Strings("----", NULL, 1);
	Delay(500);

	if (terminal.money_total < carddispenser->spit_out_cards * terminal.settings.cost_card)
	{
		Display_Strings("Err ", NULL, 1);
		Delay(1000);
		return false;
	}
	carddispenser->event_spit_out_cards = true;

	while (carddispenser->responce != TERMINAL_CARDDISPENSER_STATUS_SPIT_OUT_OK) {
		if (carddispenser->responce == TERMINAL_CARDDISPENSER_STATUS_NO_CARDS) {
			carddispenser->Command(TERMINAL_CARDDISPENSER_STATUS_RESET);
			carddispenser->Wait_Ready(1);
			Display_Strings("Err ", NULL, 1);
			Delay(1000);
			return false;
		}
		Delay(1);
	}

	Change_Money_Total(-(int32_t)(carddispenser->spit_out_cards * terminal.settings.cost_card));
	//if (carddispenser->status == TERMINAL_CARDDISPENSER_STATUS_ERROR) {
	//	if (carddispenser->responce == TERMINAL_CARDDISPENSER_STATUS_NO_CARDS) {
	//		carddispenser->Command(TERMINAL_CARDDISPENSER_STATUS_RESET);
	//		carddispenser->Wait_Ready(1);
	//	}
	//}
	carddispenser->Command(TERMINAL_CARDDISPENSER_STATUS_READY);
	return true;
}

/*###############################################################*/
/*###############################################################* Spit_Out_Hopper -->*/
/*###############################################################*/
bool Spit_Out_Hopper(uint32_t num, uint32_t money_for_out, uint32_t timeout) {
	TERMINAL_HandleCoreHopperTypeDef *hopper = terminal.hopper;
	int32_t money_out;

	Display_Strings("----", NULL, 1);
	Delay(1500);

	hopper->Start_Split_Out(num, money_for_out, TERMINAL_WAIT_FOREVER);

	while (hopper->responce != TERMINAL_HOPPER_STATUS_SPIT_OUT_OK) {
		hopper->Wait_Hopper_Ready(1);
		Display_Money_String(hopper->money_out_for_hardware);
		if (hopper->error == TERMINAL_HOPPER_ERROR_NO_COINS) {

			money_out = money_for_out - hopper->money_out_for_hardware;
			Change_Money_Total(-money_out);
			Display_Strings("Err ", NULL, 1);
			return false;
		}
	}
	money_out = money_for_out - hopper->money_for_out;
	Change_Money_Total(-money_out);


	if (hopper->status == TERMINAL_HOPPER_STATUS_ERROR) {
		if (hopper->error == TERMINAL_HOPPER_ERROR_NO_COINS) {
			hopper->Send_Command(TERMINAL_HOPPER_STATUS_RESET);
			hopper->Wait_Hopper_Ready(1);
		}
	}
	hopper->Send_Command(TERMINAL_HOPPER_STATUS_READY);
	return true;
}
/*###############################################################*/
/*###############################################################* Check_Hold_Hopper -->*/
/*###############################################################*/
void Check_Hold_Hopper(void)
{
	if (terminal.settings.number_buttons != 2) return;
	if (terminal.hold_button_hopper_1) {
		if ((terminal.money_total % terminal.hopper->hopper_1->value_of_coins == 0) &&
			(terminal.money_total <= terminal.hopper->hopper_1->money_total)) {
			DEBUG(("Разблокирываем хоппер 1\n"));
			terminal.hold_button_hopper_1 = false;
		}
	}
	if (terminal.hold_button_hopper_2) {
		if ((terminal.money_total % terminal.hopper->hopper_2->value_of_coins == 0) &&
			(terminal.money_total <= terminal.hopper->hopper_2->money_total)) {
			DEBUG(("Разблокирываем хоппер 2\n"));
			terminal.hold_button_hopper_2 = false;
		}
	}

}
/*###############################################################*/
/*###############################################################* Check_Buttons -->*/
/*###############################################################*/
void Check_Buttons(void)
{
	bool enable_button_hoppers = false;
	bool enable_button_hopper_1 = false;
	bool enable_button_hopper_2 = false;
	bool enable_button_cardreader = false;
	bool enable_button_carddispenser = false;


	bool disable_all_button = false;

	if (terminal.status != TERMINAL_STATUS_SET_SETTINGS_MANUAL)
		terminal.enable_button_settings = true;


	if ((terminal.cardreader->status == TERMINAL_CARDREADER_STATUS_WAIT_DEPOSIT_MONEY)
		|| (terminal.cardreader->status == TERMINAL_CARDREADER_STATUS_SENT_DEPOSIT_MONEY)) {
		disable_all_button = true;
	}
	else {
		enable_button_cardreader = ((terminal.money_total > 0) && (terminal.cardreader->fl_card_in_reader)) ? true : false;
		enable_button_carddispenser = (terminal.money_total >= terminal.settings.cost_card) ? true : false;
		if ((terminal.settings.number_buttons == 1)&&(terminal.settings.number_hoppers == 2)) {
			enable_button_hoppers = ((terminal.money_total >= terminal.settings.cost_coin_1) ||
									(terminal.money_total >= terminal.settings.cost_coin_2)) ? true : false;
			enable_button_hopper_1 = false;
			enable_button_hopper_2 = false;
		}
		else if ((terminal.settings.number_buttons == 1) && (terminal.settings.number_hoppers == 1)) {
			enable_button_hopper_1 = (terminal.money_total >= terminal.settings.cost_coin_1) ? true : false;
		}
		else if (terminal.settings.number_buttons == 2) {
			enable_button_hoppers = false;
			enable_button_hopper_1 = ((terminal.money_total >= terminal.settings.cost_coin_1) &&
				(terminal.money_total != 0) && (!terminal.hold_button_hopper_1)) ? true : false;
			enable_button_hopper_2 = ((terminal.money_total >= terminal.settings.cost_coin_2) &&
				(terminal.money_total != 0) && (!terminal.hold_button_hopper_2)) ? true : false;
		}
		else {
			disable_all_button = true;
		}
	}

	if (terminal.settings.number_buttons == 0) {
		enable_button_hoppers = false;
		enable_button_hopper_1 = false;
		enable_button_hopper_2 = false;
	}

	if ((terminal.settings.number_buttons == 1)&&
		(terminal.settings.number_hoppers == 1))	
	{
		enable_button_hoppers = false;
		enable_button_hopper_2 = false;
	}

	if ((terminal.settings.number_buttons == 1) &&
		(terminal.settings.number_hoppers == 2))
	{
		enable_button_hopper_1 = false;
		enable_button_hopper_2 = false;
	}

	if (terminal.settings.number_buttons == 2) {
		enable_button_hoppers = false;
	}

	//if (terminal.settings.number_hoppers == 1) {
	//	enable_button_hopper_2 = false;
	//}
	if (terminal.settings.number_hoppers == 0) {
		enable_button_hoppers = false;
		enable_button_hopper_1 = false;
		enable_button_hopper_2 = false;
	}
	if (terminal.settings.number_cardreaders == 0) {
		enable_button_cardreader = false;
	}
	if (terminal.settings.number_carddispensers == 0) {
		enable_button_carddispenser = false;
	}


	if (disable_all_button) {
		Disable_Buttons();
	}
	else {
		terminal.enable_button_hoppers = enable_button_hoppers;
		terminal.enable_button_hopper_1 = enable_button_hopper_1;
		terminal.enable_button_hopper_2 = enable_button_hopper_2;
		terminal.enable_button_cardreader = enable_button_cardreader;
		terminal.enable_button_carddispenser = enable_button_carddispenser;
	}

}
/*###############################################################*/
/*###############################################################* Change_Money_Total -->*/
/*###############################################################*/
static void Change_Money_Total(int32_t money) {
	if (money >= 0) {
		terminal.money_in = money;
		terminal.money_total_in += money;
		terminal.money_total += money;
	}
	else {
		money = -money;
		terminal.money_out = money;
		terminal.money_total_out += money;
		terminal.money_total -= money;
	}
}

/*###############################################################*/
/*###############################################################* Wait_Peripherals_Ready -->*/
/*###############################################################*/
void Wait_Peripherals_Ready(void)
{
	TERMINAL_HandleBillAcceptorTypeDef *billacceptor = terminal.billacceptor;
	TERMINAL_HandleCoinAcceptorTypeDef *coinacceptor = terminal.coinacceptor;
	TERMINAL_HandleCardDispenserTypeDef *carddispenser = terminal.carddispenser;
	//TERMINAL_HandleDisplayTypeDef *display = terminal.display;
	TERMINAL_HandleCoreHopperTypeDef *hopper = terminal.hopper;
	TERMINAL_HandleCardReaderTypeDef *cardreader = terminal.cardreader;

	billacceptor->command = TERMINAL_BILLACCEPTOR_STATUS_SET_SETTINGS;
	coinacceptor->command = TERMINAL_COINACCEPTOR_STATUS_SET_SETTINGS;
	carddispenser->command = TERMINAL_CARDDISPENSER_STATUS_SET_SETTINGS;
	hopper->command = TERMINAL_HOPPER_STATUS_SET_SETTINGS;
	cardreader->command = TERMINAL_CARDREADER_STATUS_SET_SETTINGS;

	uint32_t count = 0;
	bool fl_ready[10] = { 0 };
	while (1) {
		if (billacceptor->responce == TERMINAL_BILLACCEPTOR_STATUS_SET_SETTINGS) {
			if (!fl_ready[0]) { DEBUG(("Купюроприемник готов\n")); }
			fl_ready[0] = true;
		}
		if (terminal.settings.number_billacceptors == 0) fl_ready[0] = true;

		if (coinacceptor->responce == TERMINAL_COINACCEPTOR_STATUS_SET_SETTINGS) {
			if (!fl_ready[1]) { DEBUG(("Монетоприемник готов\n")); }
			fl_ready[1] = true;
		}
		if (terminal.settings.number_coinacceptors == 0) fl_ready[1] = true;

		if (carddispenser->responce == TERMINAL_CARDDISPENSER_STATUS_SET_SETTINGS) {
			if (!fl_ready[2]) { DEBUG(("Диспансер готов\n")); }
			fl_ready[2] = true;
		}
		if (terminal.settings.number_carddispensers == 0) fl_ready[2] = true;

		if (hopper->responce == TERMINAL_HOPPER_STATUS_SET_SETTINGS) {
			if (!fl_ready[3]) { DEBUG(("Хопперы готовы\n")); }
			fl_ready[3] = true;
		}
		if (terminal.settings.number_hoppers == 0) fl_ready[3] = true;

		if (cardreader->responce == TERMINAL_CARDREADER_STATUS_SET_SETTINGS) {
			if (!fl_ready[4]) { DEBUG(("Считыватель карт готов\n")); }
			fl_ready[4] = true;
		}
		if (terminal.settings.number_cardreaders == 0) fl_ready[4] = true;


		Delay(1);
		count++;
		if (count > 4000) {
			if (terminal.settings.number_billacceptors != 0)
				if (billacceptor->responce != TERMINAL_BILLACCEPTOR_STATUS_SET_SETTINGS) {
					{DEBUG(("Купюроприемник еще занят\n")); }
				}
			if (terminal.settings.number_coinacceptors != 0)
				if (coinacceptor->responce != TERMINAL_COINACCEPTOR_STATUS_SET_SETTINGS) {
					{DEBUG(("Монетоприемник еще занят\n")); }
				}
			if (terminal.settings.number_carddispensers != 0)
				if (carddispenser->responce != TERMINAL_CARDDISPENSER_STATUS_SET_SETTINGS) {
					{DEBUG(("Диспансер еще занят\n")); }
				}
			if (terminal.settings.number_hoppers != 0)
				if (hopper->responce != TERMINAL_HOPPER_STATUS_SET_SETTINGS) {
					{DEBUG(("Хопперы еще заняты\n")); }
				}
			if (terminal.settings.number_cardreaders != 0)
				if (cardreader->responce != TERMINAL_CARDREADER_STATUS_SET_SETTINGS) {
					{DEBUG(("Считыватель занят. Нужно вынуть карту\n")); }
				}
			count = 0;
		}
		if ((fl_ready[0]) && (fl_ready[1]) && (fl_ready[2]) && (fl_ready[3]) && (fl_ready[4]))
			break;
	}
}
/*###############################################################*/
/*###############################################################* Set_Settings -->*/
/*###############################################################*/
void Set_Settings(void)
{

	terminal.status = TERMINAL_STATUS_SET_SETTINGS;
	Wait_Peripherals_Ready();
	terminal.responce = TERMINAL_STATUS_SET_SETTINGS;
	Display_Strings("SEtt", NULL, 1);
	DEBUG_PRINT(("\nСохраняем настройки\n"));
	Delay(2000);
	Terminal_Reset();
}
/*###############################################################*/
/*###############################################################* Terminal_Loop -->*/
/*###############################################################*/
//Main Terminal loop
void Terminal_Loop(void const * argument)
{
	TERMINAL_HandleTypeDef *trmnal = &terminal;
	TERMINAL_HandleBillAcceptorTypeDef *billacceptor = terminal.billacceptor;
	TERMINAL_HandleCoinAcceptorTypeDef *coinacceptor = terminal.coinacceptor;
	TERMINAL_HandleCardDispenserTypeDef *carddispenser = terminal.carddispenser;
	TERMINAL_HandleDisplaysTypeDef *display = terminal.display;
	TERMINAL_HandleCoreHopperTypeDef *hopper = terminal.hopper;
	TERMINAL_HandleCardReaderTypeDef *cardreader = terminal.cardreader;
	while (1) {

		//terminal.money_total_in = coinacceptor->coins_total + billacceptor->bills_total;
		//uint32_t money_total = terminal.money_total_in - terminal.money_total_out;
		uint32_t money = 0;
		uint32_t money_card = 0;
		//terminal.money_total = terminal.money_total_in - terminal.money_total_out;

		if (coinacceptor->status == TERMINAL_COINACCEPTOR_STATUS_ACCEPTED) {
			if (coinacceptor->count_new_coins != 0) {
				money = coinacceptor->coins_accepted[coinacceptor->count_coins - 1];
				Change_Money_Total(money);
				if (!cardreader->fl_card_in_reader) money_card = -1;
				else money_card = cardreader->balance;
				Display_Money_Accepted(money, terminal.money_total, money_card);
				coinacceptor->count_new_coins = 0;
				if (terminal.settings.number_buttons == 2) {
					terminal.hold_button_hopper_1 = false;
					terminal.hold_button_hopper_2 = false;
				}
				terminal.fl_new_money = true;
				terminal.tickstart_for_split_out = HAL_GetTick();
			}
		}

		if (billacceptor->status == TERMINAL_BILLACCEPTOR_STATUS_ACCEPTED) {
			if (billacceptor->count_new_bills != 0) {
				money = billacceptor->bills_accepted[billacceptor->count_bills - 1];
				Change_Money_Total(money);
				if (!cardreader->fl_card_in_reader) money_card = -1;
				else money_card = cardreader->balance;
				Display_Money_Accepted(money, terminal.money_total, money_card);
				billacceptor->count_new_bills = 0;
				if (terminal.settings.number_buttons == 2) {
					terminal.hold_button_hopper_1 = false;
					terminal.hold_button_hopper_2 = false;
				}
				terminal.fl_new_money = true;
				terminal.tickstart_for_split_out = HAL_GetTick();
			}
		}

		if ((terminal.fl_new_money) && (terminal.settings.number_buttons == 0)) {
			uint32_t tick = HAL_GetTick();
			terminal.time_for_split_out = tick - terminal.tickstart_for_split_out;
			if (terminal.time_for_split_out > 10000) {
				terminal.event_spit_out_coins = true;
				terminal.fl_new_money = false;
			}
		}
		else {
			terminal.time_for_split_out = 0;
		}

		if (terminal.event_spit_out_cards) {
			terminal.enable_button_carddispenser = false;
			Disable_Buttons();
			Spit_Out_Cards(TERMINAL_WAIT_FOREVER);
			Display_Money(display->display_1->display_string_1, terminal.money_total);
			
			display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
			Delay(600);
			terminal.event_spit_out_cards = false;
		}


//HOPPERS
		if (hopper->number == 1) {
			hopper->hopper_1->money_total = hopper->hopper_1->coins_total * hopper->hopper_1->value_of_coins;
			hopper->money_total = hopper->hopper_1->money_total;
		}

		if (hopper->number == 2) {
			hopper->hopper_2->money_total = hopper->hopper_2->coins_total * hopper->hopper_2->value_of_coins;
			hopper->money_total = hopper->hopper_2->money_total;
		}

		if (hopper->number == 3) {
			hopper->hopper_1->money_total = hopper->hopper_1->coins_total * hopper->hopper_1->value_of_coins;
			hopper->hopper_2->money_total = hopper->hopper_2->coins_total * hopper->hopper_2->value_of_coins;
			hopper->money_total = hopper->hopper_1->money_total + hopper->hopper_2->money_total;
		}

		if (terminal.event_spit_out_hopper_1) {
			terminal.event_spit_out_hopper_1 = false;
			Disable_Buttons();
			if (!Spit_Out_Hopper(1, terminal.money_total, TERMINAL_WAIT_FOREVER)) {
				Handle_Hopper_Error(hopper);
				terminal.hold_button_hopper_1 = true;
				Delay(1500);
			}
			display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
		}

		if (terminal.event_spit_out_hopper_2) {
			terminal.event_spit_out_hopper_2 = false;
			Disable_Buttons();
			if (!Spit_Out_Hopper(2, terminal.money_total, TERMINAL_WAIT_FOREVER)) {
				Handle_Hopper_Error(hopper);
				terminal.hold_button_hopper_2 = true;
				Delay(1500);
			}
			display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
		}

		if (terminal.event_spit_out_coins) {
			terminal.event_spit_out_coins = false;
			Disable_Buttons();
			if (!Spit_Out_Hopper(3, terminal.money_total, TERMINAL_WAIT_FOREVER)) {
				
				//DEBUG(("Точка 0\n"));
				Handle_Hopper_Error(hopper);
				//DEBUG(("Точка 1\n"));
				Delay(1500);
				//DEBUG(("Точка 2\n"));
			}
			display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
		}

		if (cardreader->event_received_balance) {
			uint32_t count = 0;
			display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
			while (count < 1000) {
				count++;
				if (coinacceptor->count_new_coins != 0) break;
				if (billacceptor->count_new_bills != 0) break;
				if (!cardreader->fl_card_in_reader) break;

				money_card = cardreader->balance;
				Display_Money(display->display_1->display_string_1, terminal.money_total);
				Display_Set_String(display->display_2, (char *)"CArd");
				Delay(1);
			}
			money_card = cardreader->balance;
			Display_Money(display->display_2->display_string_1, money_card);
			display->display_2->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
			display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
			cardreader->event_received_balance = false;
		}

		if (terminal.event_deposit_money) {
			cardreader->event_deposit_money = true;
			cardreader->money_deposit = terminal.money_total;
			terminal.event_deposit_money = false;
			//Display_Strings("----", NULL, 3);
		}

		if (cardreader->event_deposit_money_ok) {
			cardreader->event_deposit_money_ok = false;
			display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
			Change_Money_Total(-(int32_t)cardreader->money_deposit);
		}

		//terminal.money_total = terminal.money_total_in - terminal.money_total_out;
		Check_Hold_Hopper();
		Check_Buttons();

		if (display->command == TERMINAL_DISPLAY_STATUS_MONEY_TOTAL) {
			if (!cardreader->fl_card_in_reader) {
				Display_Money(display->display_1->display_string_1, terminal.money_total);
			}
			else {
				Display_Money(display->display_1->display_string_1, terminal.money_total);
				Display_Money(display->display_2->display_string_1, cardreader->balance);

			}
		}



		if ((terminal.money_total == 0)&&(!cardreader->fl_card_in_reader)) {
			display->command = TERMINAL_DISPLAY_STATUS_READY;
			display->display_2->command = TERMINAL_DISPLAY_STATUS_READY;
		}
		else if ((terminal.money_total == 0) && (cardreader->fl_card_in_reader)) {
			display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
		}


		if (cardreader->status == TERMINAL_CARDREADER_STATUS_ERROR) {
			if (cardreader->error == TERMINAL_CARDREADER_ERROR_NO_CARD_DEPOSIT_MONEY) {
				Display_Strings("Err ", NULL, 3);
			}
			cardreader->command = TERMINAL_CARDREADER_STATUS_RESET;
		}

		if (cardreader->responce == TERMINAL_CARDREADER_STATUS_CARD_OUT_READER){
			//Display_Strings("    ", "    ");
			Display_Set_String(display->display_2, (char *)"    ");
			display->display_2->command = TERMINAL_DISPLAY_STATUS_READY;
			if (terminal.money_total != 0) {
				Display_Money(display->display_1->display_string_1, terminal.money_total);
				display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
			}
			cardreader->command = TERMINAL_CARDREADER_STATUS_RESET;
		}

		if (terminal.command == TERMINAL_STATUS_SET_SETTINGS) {
			Set_Settings();
			if (terminal.money_total != 0) display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
			else  display->command = TERMINAL_DISPLAY_STATUS_READY;
		}

		if (terminal.command == TERMINAL_STATUS_SET_SETTINGS_MANUAL) {
			terminal.status = TERMINAL_STATUS_SET_SETTINGS_MANUAL;
			Wait_Peripherals_Ready();
			Set_Settings_Manual();
			if (terminal.money_total != 0) display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
			else  display->command = TERMINAL_DISPLAY_STATUS_READY;
			terminal.event_save_manual = true;
			terminal.command = TERMINAL_STATUS_READY;
		}

		Delay(1);
	}

}


