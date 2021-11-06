/**
  ******************************************************************************
  * File Name          : Core.c
  ******************************************************************************
  */
  /* Includes ------------------------------------------------------------------*/

#include "Terminal/Terminal.h"


#ifdef TERMINAL_USE_STM
#include "cmsis_os2.h"
#include "stm32f4xx.h"
#include "FLASH.h"
#elif defined(TERMINAL_USE_WINDOWS)
#include <thread>
#include <chrono>
#endif /*TERMINAL_USE_STM*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
//used when debugging, declared in the file Terminal.h
#ifdef DEBUG_TERMINAL_CORE
#undef DEBUG /* DEBUG */
#undef DEBUG_CORE /* DEBUG_CORE */
#undef DEBUG_PRINT /* DEBUG_PRINT */
#define DEBUG(...)		do {debug_header("TERMINAL: ", __VA_ARGS__);} while (0)
#define DEBUG_CORE(...)		do {debug_header("TERMINAL CORE: ", __VA_ARGS__);} while (0)
#define DEBUG_PRINT(x)		debug_print x;
#else
#define DEBUG(...)
#define DEBUG_CORE(x)
#define DEBUG_PRINT(x)
#endif // DEBUG_TERMINAL_CORE
/* Private variables ---------------------------------------------------------*/
// declare the basic structure of the terminal, it stores the current state of the terminal,
// state of the port modules and commands and work with memory, etc.
using namespace DisplayNS;
using namespace BillAcceptorNS;
using namespace HoppersNS;
#ifdef TERMINAL_USE_STM
using namespace Hopper1MSPNS;
using namespace Hopper2MSPNS;
using namespace HoppersMSPNS;
using namespace BillAcceptorMSPNS;
using namespace ButtonsNS;
#endif // TERMINAL_USE_STM
CoreClass Terminal;
/* Private function prototypes -----------------------------------------------*/
// functions used for debugging, display information in the console
// about errors of the corresponding bootloader modules

/* Exported functions --------------------------------------------------------*/
//#ifdef TERMINAL_USE_WINDOWS
///*###############################################################*/
///*###############################################################* HAL_GetTick -->*/
///*###############################################################*/
//static uint32_t HAL_GetTick(void) {
//	uint32_t result = GetTickCount();
//	return result;
//}
//#endif // TERMINAL_USE_WINDOWS
///*###############################################################*/
///*###############################################################* Terminal_Slave_Get_Handle -->*/
///*###############################################################*/
//// Returns a pointer to the main structure of the bootloader
//TERMINAL_HandleTypeDef* Terminal_Get_Handle(void)
//{
//	return &terminal;
//}
///*###############################################################*/
///*###############################################################* Terminal_Slave_Init -->*/
///*###############################################################*/
//// Initialize the main structure of the bootloader, here it is set
//// initial values, configurable port
//void Terminal_Init(void)
//{
//	terminal.status = TERMINAL_STATUS_READY;
//	terminal.error = TERMINAL_ERROR_OK;
//	terminal.command = TERMINAL_STATUS_NULL;
//	terminal.responce = TERMINAL_STATUS_NULL;
//	terminal.money_total_in = 0;
//	terminal.money_in = 0;
//	terminal.money_total_out = 0;
//	terminal.money_out = 0;
//	terminal.money_total = 0;
//	terminal.tickstart_for_split_out = 0;
//	terminal.time_for_split_out = 0;
//	terminal.fl_new_money = false;
//	terminal.event_spit_out_coins = false;
//	terminal.event_deposit_money = false;
//	terminal.event_spit_out_hopper_1 = false;
//	terminal.event_spit_out_hopper_2 = false;
//
//	terminal.hold_terminal = false;
//	terminal.hold_hopper_1 = false;
//	terminal.hold_hopper_2 = false;
//	terminal.hold_bill_acceptor = false;
//
//	terminal.event_save_manual = false;
//
//	terminal.enable_button_up = false;
//	terminal.enable_button_down = false;
//	terminal.enable_button_left = false;
//	terminal.enable_button_right = false;
//	terminal.enable_button_ok = false;
//	terminal.enable_button_settings = false;
//	terminal.enable_button_encashment = false;
//	terminal.enable_button_return = false;
//
//
//	terminal.enable_exti_hopper1 = false;
//	terminal.enable_exti_hopper2 = false;
//	terminal.enable_exti_buttons = false;
//
//
//	terminal.display = Terminal_Get_HandleDisplay();
//	terminal.display->init();
//
//	terminal.billacceptor = Terminal_Get_HandleBillAcceptor();
//	terminal.billacceptor->init();
//
//
//	if (terminal.settings.number_hoppers == 1) {
//		terminal.hopper = Terminal_Get_HandleHopper();
//		terminal.hopper->init(1);
//		terminal.hopper->proportion_hoppers = 100;
//		terminal.hopper->hopper_1->coins_total = terminal.settings.number_coins;
//		terminal.hopper->hopper_1->value_of_coins = terminal.settings.cost_coin_1;
//		terminal.hopper->spit_out_coins = 1;
//	}
//	else if (terminal.settings.number_hoppers == 2) {
//		terminal.hopper = Terminal_Get_HandleHopper();
//		terminal.hopper->init(2);
//		terminal.hopper->proportion_hoppers = terminal.settings.proportion_hoppers;
//		terminal.hopper->hopper_1->coins_total = terminal.settings.number_coins;
//		terminal.hopper->hopper_2->coins_total = terminal.settings.number_coins;
//		terminal.hopper->hopper_1->value_of_coins = terminal.settings.cost_coin_1;
//		terminal.hopper->hopper_2->value_of_coins = terminal.settings.cost_coin_2;
//		terminal.hopper->spit_out_coins = 1;
//	}
//	else {
//		//		terminal.hopper = Terminal_Get_HandleHopper();
//		//		terminal.hopper->init(0);
//		terminal.hopper = Terminal_Get_HandleHopper();
//		terminal.hopper->init(2);
//		terminal.hopper->proportion_hoppers = terminal.settings.proportion_hoppers;
//		terminal.hopper->hopper_1->coins_total = terminal.settings.number_coins;
//		terminal.hopper->hopper_2->coins_total = terminal.settings.number_coins;
//		terminal.hopper->hopper_1->value_of_coins = terminal.settings.cost_coin_1;
//		terminal.hopper->hopper_2->value_of_coins = terminal.settings.cost_coin_2;
//		terminal.hopper->spit_out_coins = 1;
//	}
//
//}
///*###############################################################*/
///*###############################################################* Terminal_Slave_Init -->*/
///*###############################################################*/
////reset loader pointers
//static void Terminal_Reset(void)
//{
//	uint32_t money = terminal.money_total;
//	Terminal_Init();
//	terminal.money_total_in = money;
//	terminal.money_total = money;
//	terminal.money_in = money;
//	if (money != 0) {
//		terminal.display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
//	}
//	else {
//		terminal.display->command = TERMINAL_DISPLAY_STATUS_READY;
//	}
//}
///*###############################################################*/
///*###############################################################* Check_Error_Terminal -->*/
///*###############################################################*/
//// Check the current state of each module if the state is critical
//// and requires the loader to stop working, then set fatal_error = true,
//// then boot.status = TERMINAL_STATUS_FATAL_ERROR. Otherwise
//// reset the state of the loader modules (boot.status = TERMINAL_STATUS_RESET;)
//static bool Check_Terminal_Status(void)
//{
//	return true;
//}
//
///*###############################################################*/
///*###############################################################* Terminal_Listen_Command -->*/
///*###############################################################*/
//// Accept two bytes and if they match the bootloader command, call the corresponding
//// function of the commands module (located in the Slave_Commands.c file)
//bool Terminal_Listen_Command(void)
//{
//
//	return 0;
//}
///*###############################################################*/
///*###############################################################* Wait_Handle_If_Error -->*/
///*###############################################################*/
//static void Handle_Hopper_Error(TERMINAL_HandleCoreHopperTypeDef* hpr) {
//
//	if (hpr->status == TERMINAL_HOPPER_STATUS_ERROR) {
//		if (hpr->error == TERMINAL_HOPPER_ERROR_NO_COINS)
//		{
//			hpr->Send_Command(TERMINAL_HOPPER_STATUS_DO_NOT_STOP);
//			while (hpr->responce != TERMINAL_HOPPER_STATUS_DO_NOT_STOP) {
//				Delay(1);
//			}
//			hpr->Send_Command(TERMINAL_HOPPER_STATUS_READY);
//		}
//	}
//}
///*###############################################################*/
///*###############################################################* Display_Money -->*/
///*###############################################################*/
//bool Display_Money(char* display_string, int32_t dig)
//{
//	char str[10];
//	float money_f = (float)dig / 100.0f;
//	snprintf(str, 6, "%5.2f", money_f);
//	for (int i = 0; i < 5; i++)
//		if (str[i] == ' ')
//			str[i] = '0';
//	snprintf(display_string, 6, "%s", str);
//	return 0;
//}
///*###############################################################*/
///*###############################################################* Display_Money -->*/
///*###############################################################*/
//bool Display_Set_String(TERMINAL_HandleDisplayTypeDef* display, char* display_string)
//{
//	snprintf(display->display_string_1, 6, "%s", display_string);
//	return true;
//}
///*###############################################################*/
///*###############################################################* Display_String -->*/
///*###############################################################*/
//bool Display_Strings(const char* string_1, const char* string_2, uint32_t num)
//{
//	if ((num == 1) || (num == 3)) {
//		snprintf(terminal.display->Display_1->display_string_1, 6, "%s", string_1);
//	}
//	if (num == 2) {
//		snprintf(terminal.display->display_2->display_string_1, 6, "%s", string_2);
//	}
//	if (num == 1) {
//		terminal.display->command = TERMINAL_DISPLAY_STATUS_STRING;
//		return true;
//	}
//	if (num == 2) return true;
//
//	const char* string;
//	string = (string_2 != NULL) ? string_2 : string_1;
//	snprintf(terminal.display->display_2->display_string_1, 6, "%s", string);
//	terminal.display->command = TERMINAL_DISPLAY_STATUS_STRING;
//	terminal.display->display_2->command = TERMINAL_DISPLAY_STATUS_STRING;
//	return true;
//}
///*###############################################################*/
///*###############################################################* Display_Money_String -->*/
///*###############################################################*/
//bool Display_Money_String(int32_t dig)
//{
//	TERMINAL_HandleDisplaysTypeDef* display = terminal.display;
//	char str[10];
//	float money_f = (float)dig / 100.0f;
//	snprintf(str, 6, "%5.2f", money_f);
//	for (int i = 0; i < 5; i++)
//		if (str[i] == ' ')
//			str[i] = '0';
//	snprintf(display->Display_1->display_string_1, 6, "%s", str);
//	display->command = TERMINAL_DISPLAY_STATUS_STRING;
//	return true;
//}
///*###############################################################*/
///*###############################################################* Display_Money -->*/
///*###############################################################*/
//bool Display_Money_Accepted(int32_t dig1, int32_t dig2, int32_t dig3)
//{
//	TERMINAL_HandleDisplayTypeDef* Display_1 = terminal.display->Display_1;
//	TERMINAL_HandleDisplayTypeDef* display_2 = terminal.display->display_2;
//	Display_Money(Display_1->display_string_1, dig1);
//	Display_Money(Display_1->display_string_2, dig2);
//	if (dig3 != -1) {
//		Display_Money(display_2->display_string_1, dig3);
//	}
//
//	//display->reset_tickstart();
//	if (terminal.display->status == TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED) {
//		terminal.display->command = TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED_REPLAY;
//	}
//	else {
//		terminal.display->command = TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED;
//	}
//	return 0;
//}
///*###############################################################*/
///*###############################################################* Disable_Buttons -->*/
///*###############################################################*/
//bool Disable_Buttons(void)
//{
//	terminal.enable_button_up = false;
//	terminal.enable_button_down = false;
//	terminal.enable_button_left = false;
//	terminal.enable_button_right = false;
//	terminal.enable_button_ok = false;
//	terminal.enable_button_settings = false;
//	terminal.enable_button_encashment = false;
//	terminal.enable_button_return = false;
//	return true;
//}
///*###############################################################*/
///*###############################################################* Wait_Hopper_Redy -->*/
///*###############################################################*/
//bool Wait_Hopper_Redy(uint32_t timeout)
//{
//	TERMINAL_HandleCoreHopperTypeDef* hopper = terminal.hopper;
//	while (hopper->responce != TERMINAL_HOPPER_STATUS_READY) {
//		Delay(1);
//	}
//	return 0;
//}
//
//
///*###############################################################*/
///*###############################################################* Spit_Out_Hopper -->*/
///*###############################################################*/
//bool Spit_Out_Hopper(uint32_t num, uint32_t money_for_out, uint32_t timeout) {
//	TERMINAL_HandleCoreHopperTypeDef* hopper = terminal.hopper;
//	int32_t money_out;
//
//	Display_Strings("----", NULL, 1);
//
//#ifdef TERMINAL_USE_WINDOWS  
//	Delay(500);
//#endif //TERMINAL_USE_WINDOWS
//
//	hopper->Start_Split_Out(num, money_for_out, TERMINAL_WAIT_FOREVER);
//
//	while (hopper->responce != TERMINAL_HOPPER_STATUS_SPIT_OUT_OK) {
//		hopper->Wait_Hopper_Ready(1);
//		if (hopper->error == TERMINAL_HOPPER_ERROR_NO_COINS) {
//
//			money_out = money_for_out - hopper->money_out_for_hardware;
//			Change_Money_Total(-money_out);
//			return false;
//		}
//		else {
//			money_out = money_for_out - hopper->money_out_for_hardware;
//			//если начали что-то выдавать, с первой манеты, тогда отображаем текущий баланс
//			//если ничего не выдали пока, то отображаем черточки. Чтоб было понятно что идет процесс
//			//выдачи
//			if (money_out != 0)
//				Display_Money_String(terminal.money_total - money_out);
//			//Display_Money_String(hopper->money_out_for_hardware);
//		}
//		Delay(100);
//	}
//	money_out = money_for_out - hopper->money_for_out;
//	Change_Money_Total(-money_out);
//
//
//	if (hopper->status == TERMINAL_HOPPER_STATUS_ERROR) {
//		if (hopper->error == TERMINAL_HOPPER_ERROR_NO_COINS) {
//			hopper->Send_Command(TERMINAL_HOPPER_STATUS_RESET);
//			hopper->Wait_Hopper_Ready(1);
//		}
//	}
//	hopper->Send_Command(TERMINAL_HOPPER_STATUS_READY);
//	return true;
//}
///*###############################################################*/
///*###############################################################* Check_Hold_Hopper -->*/
///*###############################################################*/
//void Check_Hold_Hopper(void)
//{
//	//if (terminal.settings.number_buttons != 2) return;
//	//if (terminal.hold_button_hopper_1) {
//	//	if (!terminal.hold_hopper_1) { //если не заблокирован
//	//		if ((terminal.money_total % terminal.hopper->hopper_1->value_of_coins == 0) &&
//	//			(terminal.money_total <= terminal.hopper->hopper_1->money_total)) {
//	//			DEBUG("Unlock the hopper 1\n");
//	//			terminal.hold_button_hopper_1 = false;
//	//		}
//	//	}
//	//}
//	//if (terminal.hold_button_hopper_2) {
//	//	if (!terminal.hold_hopper_2) { //если не заблокирован
//	//		if ((terminal.money_total % terminal.hopper->hopper_2->value_of_coins == 0) &&
//	//			(terminal.money_total <= terminal.hopper->hopper_2->money_total)) {
//	//			DEBUG("Unlock the hopper 2\n");
//	//			terminal.hold_button_hopper_2 = false;
//	//		}
//	//	}
//	//}
//}
///*###############################################################*/
///*###############################################################* Change_Money_Total -->*/
///*###############################################################*/
//static void Change_Money_Total(int32_t money) {
//	if (money >= 0) {
//		terminal.money_in = money;
//		terminal.money_total_in += money;
//		terminal.money_total += money;
//	}
//	else {
//		money = -money;
//		terminal.money_out = money;
//		terminal.money_total_out += money;
//		terminal.money_total -= money;
//	}
//}
//
///*###############################################################*/
///*###############################################################* Wait_Peripherals_Ready -->*/
///*###############################################################*/
//void Wait_Peripherals_Ready(void)
//{
//	TERMINAL_HandleBillAcceptorTypeDef* billacceptor = terminal.billacceptor;
//	TERMINAL_HandleCoreHopperTypeDef* hopper = terminal.hopper;
//
//	billacceptor->command = TERMINAL_BILLACCEPTOR_STATUS_SET_SETTINGS;
//	hopper->command = TERMINAL_HOPPER_STATUS_SET_SETTINGS;
//
//	uint32_t count = 0;
//	bool fl_ready[10] = { 0 };
//	while (1) {
//
//		if (billacceptor->responce == TERMINAL_BILLACCEPTOR_STATUS_SET_SETTINGS) {
//			if (!fl_ready[0]) { DEBUG("Bill acceptor is ready\n"); }
//			fl_ready[0] = true;
//		}
//		if (terminal.settings.number_billacceptors == 0) fl_ready[0] = true;
//#ifdef TERMINAL_USE_STM
//		if (BillAcceptor_TaskHandle == NULL) fl_ready[0] = true;
//#endif //TERMINAL_USE_STM
//
//
//		//______________ HOPPER
//		if (hopper->responce == TERMINAL_HOPPER_STATUS_SET_SETTINGS) {
//			if (!fl_ready[3]) { DEBUG("Hoppers is ready\n"); }
//			fl_ready[3] = true;
//		}
//		if (terminal.settings.number_hoppers == 0) fl_ready[3] = true;
//#ifdef TERMINAL_USE_STM
//		if (Hopper_TaskHandle == NULL) fl_ready[3] = true;
//#endif //TERMINAL_USE_STM
//
//		Delay(1);
//		count++;
//		if (count > 4000) {
//			if (terminal.settings.number_billacceptors != 0)
//				if (!fl_ready[0]) {
//					{DEBUG("Bill acceptor is still busy\n"); }
//				}
//
//			if (terminal.settings.number_coinacceptors != 0)
//				if (!fl_ready[1]) {
//					{DEBUG("Coin acceptor is still busy\n"); }
//				}
//
//			if (terminal.settings.number_carddispensers != 0)
//				if (!fl_ready[2]) {
//					{DEBUG("Card dispenser is still busy\n"); }
//				}
//
//			if (terminal.settings.number_hoppers != 0)
//				if (!fl_ready[3]) {
//					{DEBUG("Hoppers is still busy\n"); }
//				}
//
//			if (terminal.settings.number_cardreaders != 0)
//				if (!fl_ready[4]) {
//					{DEBUG("Cardreader is still busy. Need to take out a card\n"); }
//				}
//
//			count = 0;
//		}
//		if ((fl_ready[0]) && (fl_ready[1]) && (fl_ready[2]) && (fl_ready[3]) && (fl_ready[4]))
//			break;
//	}
//}
///*###############################################################*/
///*###############################################################* Set_Settings -->*/
///*###############################################################*/
//void Set_Settings(void)
//{
//	terminal.status = TERMINAL_STATUS_SET_SETTINGS;
//	Wait_Peripherals_Ready();
//	memcpy(&terminal.settings, &terminal.settings_receive, sizeof(TERMINAL_SettingsTypeDef));
//#ifdef TERMINAL_USE_STM
//	FLASH_Save_Settings();
//#endif //TERMINAL_USE_STM
//	terminal.responce = TERMINAL_STATUS_SET_SETTINGS;
//	Display_Strings("SEtt", NULL, 1);
//	DEBUG_PRINT(("\nSave settings\n"));
//	Delay(1000);
//	Terminal_Reset();
//}
//
///*###############################################################*/
///*###############################################################* Unhold_Devices -->*/
///*###############################################################*/
//void Unhold_Acceptors(void)
//{
//	//Посылаем запрос, ждем пока ответят
//	if (terminal.billacceptor->status == TERMINAL_BILLACCEPTOR_STATUS_HOLD)
//		terminal.billacceptor->command = TERMINAL_BILLACCEPTOR_STATUS_NULL;
//
//	while (terminal.billacceptor->status == TERMINAL_BILLACCEPTOR_STATUS_HOLD)
//
//	{
//		Delay(1);
//	}
//	terminal.hold_bill_acceptor = false;
//}
///*###############################################################*/
///*###############################################################* Hold_Devices -->*/
///*###############################################################*/
//void Hold_Acceptors(void)
//{
//	//Посылаем запрос, ждем пока ответят
//	if (terminal.billacceptor->status != TERMINAL_BILLACCEPTOR_STATUS_HOLD)
//		terminal.billacceptor->command = TERMINAL_BILLACCEPTOR_STATUS_HOLD;
//	//	if (terminal.coinacceptor->status != TERMINAL_COINACCEPTOR_STATUS_HOLD)
//	//		terminal.coinacceptor->command = TERMINAL_COINACCEPTOR_STATUS_HOLD;
//	while (
//		(terminal.billacceptor->status != TERMINAL_BILLACCEPTOR_STATUS_HOLD)
//		//		||(terminal.coinacceptor->status != TERMINAL_COINACCEPTOR_STATUS_HOLD)
//		)
//	{
//		Delay(1);
//	}
//	terminal.hold_bill_acceptor = true;
//}
///*###############################################################*/
///*###############################################################* Hold_Terminal -->*/
///*###############################################################*/
//void Hold_Terminal(void)
//{
//	static int count_hold = 301;
//	static int count_unhold = 301;
//	bool send_mess_hold = false; //отправлять ли сообщения устройствам
//	bool send_mess_unhold = false;
//	//если уже выдали монеты
//	if ((!terminal.event_spit_out_hopper_1) && (!terminal.event_spit_out_hopper_2)) {
//		//если на линиях сигналы пустой или inhibit или другой
//		bool	alarm_sensor; //если сработал сенсор
//		bool	alarm_coint_emply; //если закончились монеты физически
//
//	//***************************************************************************
//	//HOPPER 1
//		alarm_sensor = terminal.hopper->hopper_1->alarm_sensor;
//		alarm_coint_emply = terminal.hopper->hopper_1->alarm_coint_emply;
//		if (alarm_sensor || alarm_coint_emply) {
//			terminal.hold_hopper_1 = true;
//		}
//		else {
//			terminal.hold_hopper_1 = false;
//		}
//
//		//***************************************************************************
//		//HOPPER 1
//		alarm_sensor = terminal.hopper->hopper_2->alarm_sensor;
//		alarm_coint_emply = terminal.hopper->hopper_2->alarm_coint_emply;
//		if (alarm_sensor || alarm_coint_emply) {
//			terminal.hold_hopper_2 = true;
//		}
//		else {
//			terminal.hold_hopper_2 = false;
//		}
//
//		//если какой-то из хопперов заморожен
//		if ((terminal.hold_hopper_1) || (terminal.hold_hopper_2)) {
//			//if (!terminal.hold_terminal) {
//			send_mess_hold = true;
//			//}			
//		}
//		else {
//			//if (terminal.hold_terminal) {
//			send_mess_unhold = true;
//			//}   
//		}
//
//	}
//
//	if (send_mess_hold)
//	{
//		terminal.hold_terminal = true;
//		//Посылаем запрос, ждем пока ответят
//		Hold_Acceptors();
//	}
//
//	if (send_mess_unhold)
//	{
//		terminal.hold_terminal = false;
//		Unhold_Acceptors();
//	}
//
//}
///*###############################################################*/
///*###############################################################* Calc_Hoppers_Money -->*/
///*###############################################################*/
//void Calc_Hoppers_Money(void)
//{
//	TERMINAL_HandleCoreHopperTypeDef* hopper = terminal.hopper;
//	if (hopper->number == 1) {
//		hopper->hopper_1->money_total = hopper->hopper_1->coins_total * hopper->hopper_1->value_of_coins;
//		hopper->money_total = hopper->hopper_1->money_total;
//	}
//
//	if (hopper->number == 2) {
//		//		hopper->hopper_2->money_total = hopper->hopper_2->coins_total * hopper->hopper_2->value_of_coins;
//		//		hopper->money_total = hopper->hopper_2->money_total;
//
//		hopper->hopper_1->money_total = hopper->hopper_1->coins_total * hopper->hopper_1->value_of_coins;
//		hopper->hopper_2->money_total = hopper->hopper_2->coins_total * hopper->hopper_2->value_of_coins;
//		hopper->money_total = hopper->hopper_1->money_total + hopper->hopper_2->money_total;
//	}
//
//	//	if (hopper->number == 3) {
//	//		hopper->hopper_1->money_total = hopper->hopper_1->coins_total * hopper->hopper_1->value_of_coins;
//	//		hopper->hopper_2->money_total = hopper->hopper_2->coins_total * hopper->hopper_2->value_of_coins;
//	//		hopper->money_total = hopper->hopper_1->money_total + hopper->hopper_2->money_total;
//	//	}
//}
///*###############################################################*/
///*###############################################################* Hoppers -->*/
///*###############################################################*/
//void Hoppers(void)
//{
//	TERMINAL_HandleDisplaysTypeDef* display = terminal.display;
//	TERMINAL_HandleCoreHopperTypeDef* hopper = terminal.hopper;
//
//	Calc_Hoppers_Money();
//
//	if (terminal.event_spit_out_hopper_1) {
//		Hold_Acceptors();
//		terminal.event_spit_out_hopper_1 = false;
//		if (terminal.hold_hopper_1) {
//			DEBUG("The request for the split out of coins cannot be processed, as hopper 1 is blocked\n");
//		}
//		else {
//			Disable_Buttons();
//
//			int32_t money_out = 0;
//			//если сумма больше, то выдаем все что есть в хоппере и переключаемся на другой хоппер
//			static bool start_hopper2 = false;
//			if (terminal.settings.number_spit_out_coins == 0) {
//				if (terminal.money_total > hopper->hopper_1->money_total) {
//					DEBUG("ERROR: Not enough coins in hopper 1! Split out all that is\n");
//				}
//				money_out = terminal.money_total;
//
//			}
//			else {
//				//if (terminal.money_total > terminal.settings.number_spit_out_coins * hopper->hopper_1->value_of_coins) {
//					//DEBUG("ERROR: Not enough coins in hopper 1! Split out all that is\n");
//					//money_out = hopper->hopper_1->money_total;
//					//money_out = terminal.money_total;
//				//}else{
//				money_out = terminal.settings.number_spit_out_coins * hopper->hopper_1->value_of_coins;
//				//если сумма высыпаемых монет больше внесенной суммы выдаем монеты на внесенную сумму
//						//к примеру закинули 1 рубль а стоит в настройках выдача 100 монет при нажати 
//				if (money_out > terminal.money_total)
//				{
//					money_out = terminal.money_total;
//				}
//				//}				
//			}
//
//			if (!Spit_Out_Hopper(1, money_out, TERMINAL_WAIT_FOREVER)) {
//				//если физически закончились монеты или сломался хоппер 
//				//и режим размена всех денег, то переключаемся на другой хоппер
//				if (terminal.settings.number_spit_out_coins == 0) {
//					start_hopper2 = true;
//				}
//				Handle_Hopper_Error(hopper);
//			}
//			if (start_hopper2) {
//				terminal.hold_hopper_1 = true;
//				DEBUG("Start hopper 2\n");
//				terminal.event_spit_out_hopper_2 = true;
//			}
//			//Unhold_Devices();
//			display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
//		}
//	}
//
//	if (terminal.event_spit_out_hopper_2) {
//		Hold_Acceptors();
//		terminal.event_spit_out_hopper_2 = false;
//		if (terminal.hold_hopper_2) {
//			DEBUG("The request for the split out of coins cannot be processed, as hopper 2 is blocked\n");
//		}
//		else {
//			Disable_Buttons();
//
//			int32_t money_out = 0;
//			//если сумма больше, то выдаем все что есть в хоппере и переключаемся на другой хоппер
//			static bool start_hopper1 = false;
//			if (terminal.settings.number_spit_out_coins == 0) {
//				if (terminal.money_total > hopper->hopper_2->money_total) {
//					DEBUG("ERROR: Not enough coins in hopper 2! Split out all that is\n");
//				}
//				money_out = terminal.money_total;
//
//			}
//			else {
//				//if (terminal.money_total > terminal.settings.number_spit_out_coins * hopper->hopper_2->value_of_coins) {
//					//DEBUG("ERROR: Not enough coins in hopper 2! Split out all that is\n");
//					//money_out = hopper->hopper_2->money_total;
//					//money_out = terminal.money_total;
//				//}else{
//				money_out = terminal.settings.number_spit_out_coins * hopper->hopper_2->value_of_coins;
//				//если сумма высыпаемых монет больше внесенной суммы выдаем монеты на внесенную сумму
//				//к примеру закинули 1 рубль а стоит в настройках выдача 100 монет при нажати 
//				if (money_out > terminal.money_total)
//				{
//					money_out = terminal.money_total;
//				}
//				//}				
//			}
//			if (!Spit_Out_Hopper(2, money_out, TERMINAL_WAIT_FOREVER)) {
//				//если физически закончились монеты или сломался хоппер 
//				//и режим размена всех денег, то переключаемся на другой хоппер
//				if (terminal.settings.number_spit_out_coins == 0) {
//					start_hopper1 = true;
//				}
//				Handle_Hopper_Error(hopper);
//			}
//			if (start_hopper1) {
//				terminal.hold_hopper_2 = true;
//				DEBUG("Start hopper 1\n");
//				terminal.event_spit_out_hopper_1 = true;
//			}
//			//Unhold_Devices();
//			display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
//		}
//
//	}
//
//	if (terminal.event_spit_out_coins) {
//		Hold_Acceptors();
//		terminal.event_spit_out_coins = false;
//		Disable_Buttons();
//		if (!Spit_Out_Hopper(3, terminal.money_total, TERMINAL_WAIT_FOREVER)) {
//			Display_Strings("Err ", NULL, 1);
//			//DEBUG("Точка 0\n");
//			Handle_Hopper_Error(hopper);
//			//DEBUG("Точка 1\n");
//			Delay(1500);
//			//DEBUG("Точка 2\n");
//		}
//		//Unhold_Devices();
//		display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
//	}
//	//Check_Buttons();
//
//}
///*###############################################################*/
///*###############################################################* Terminal_Loop -->*/
///*###############################################################*/
////Main Terminal loop
//#ifdef TERMINAL_USE_STM
//__NO_RETURN void Terminal_Loop(void* arg)
//#else
//void Terminal_Loop()
//#endif
//{
//	TERMINAL_HandleTypeDef* trmnal = &terminal;
//	TERMINAL_HandleBillAcceptorTypeDef* billacceptor = terminal.billacceptor;
//	TERMINAL_HandleDisplaysTypeDef* display = terminal.display;
//	TERMINAL_HandleCoreHopperTypeDef* hopper = terminal.hopper;
//
//	while ((!terminal.enable_exti_hopper1) || (!terminal.enable_exti_hopper2) || (!terminal.enable_exti_buttons))
//	{
//		Delay(300);
//	}
//	//CREDIT_NO - B7	 
//	//METER_NO - E1
//	//INHIBIT_NO - E4
//	//PAYONT_IN - E6
//	//COIN-EMPTY_O - C0
//
//	//B7, E1, E4, E6, C0
//
//	//HOPPER 2
//	//CREDIT_NO - D4	 
//	//METER_NO - E0
//	//INHIBIT_NO - E5
//	//PAYONT_IN - C13
//	//COIN-EMPTY_O - A0	
//
//	//D4, E0, E5, C13, A0
//
//	//BUTTON_UP_IRQ - A8	
//	//BUTTON_DOWN_IRQ - C6	
//	//BUTTON_LEFT_IRQ - C7	
//	//BUTTON_RIGHT_IRQ - D15	
//	//BUTTON_OK_IRQ - D13	
//	//BUTTON_RETURN_IRQ - D11	
//	//BUTTON_SETTINGS_IRQ - D9	
//	//BUTTON_ENCASHMENT_IRQ - E10	
//	//BUTTON_HOPPER1_IRQ - E12	
//	//BUTTON_HOPPER2_IRQ - E11	
//
//	//A8, C6, C7, D15, D13, D11, D9, E10, E12, E11
//
//#ifdef TERMINAL_USE_STM	
//	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
//	HAL_NVIC_DisableIRQ(EXTI1_IRQn);
//	HAL_NVIC_DisableIRQ(EXTI4_IRQn);
//	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
//	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
//
//
//	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
//
//	HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
//
//	HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
//
//	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
//
//	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
//#endif 	
//
//
//
//	while (1) {
//		uint32_t money = 0;
//
//
//		if (billacceptor->status == TERMINAL_BILLACCEPTOR_STATUS_ACCEPTED) {
//			if (billacceptor->count_new_bills != 0) {
//				money = billacceptor->bills_accepted[billacceptor->count_bills - 1];
//				Change_Money_Total(money);
//				Display_Money_Accepted(money, terminal.money_total, 0);
//				billacceptor->count_new_bills = 0;
//				terminal.fl_new_money = true;
//				terminal.tickstart_for_split_out = HAL_GetTick();
//			}
//		}
//
//		//if (terminal.fl_new_money) {
//			//Проверяем внесенную сумму, и если она достаточно большая, отключаем приемники денег
//		int money_in_hopper_1 = 0;
//		int money_in_hopper_2 = 0;
//		int diapason_hold_acceptors = (int)trmnal->settings.diapason_hold_acceptors;
//		Calc_Hoppers_Money();
//		//считаем деньги которые мы можем выдать
//		money_in_hopper_1 = hopper->hopper_1->money_total;
//		money_in_hopper_2 = hopper->hopper_2->money_total;
//		money_in_hopper_1 -= hopper->hopper_1->value_of_coins * diapason_hold_acceptors;
//		money_in_hopper_2 -= hopper->hopper_2->value_of_coins * diapason_hold_acceptors;
//
//		int diff = (money_in_hopper_1 + money_in_hopper_2) - terminal.money_total;
//		static bool hold_acceptors = false; //чтоб один раз надпись написать (для удобства)
//		//сравниваем с наименьшей купюрой;
//		if ((500 >= diff) || (hopper->hopper_1->coins_total <= diapason_hold_acceptors) || (hopper->hopper_2->coins_total <= diapason_hold_acceptors)) {
//			//For Debug!!!!!**************************************************
//			//For Debug!!!!!**************************************************
//			//For Debug!!!!!**************************************************
//#ifdef TERMINAL_USE_STM	
//			static uint32_t cnt_debug = 0xFFFFF;
//			if (++cnt_debug > 0xFFFFF) {
//				cnt_debug = 0;
//				DEBUG("The accepted amount is more than the threshold. Turn off the acceptors\n");
//				DEBUG("Hopper_1 coins total %d, Hopper_2 coins total %d\n", hopper->hopper_1->coins_total, hopper->hopper_2->coins_total);
//			}
//#endif 	
//			//For Debug!!!!!**************************************************
//			//For Debug!!!!!**************************************************
//
//			Hold_Acceptors();
//			hold_acceptors = true;
//
//		}
//		else {
//			hold_acceptors = false;
//		}
//		//}
//
//		if ((terminal.fl_new_money) && (terminal.settings.number_buttons == 0)) {
//			uint32_t tick = HAL_GetTick();
//			terminal.time_for_split_out = tick - terminal.tickstart_for_split_out;
//			if (terminal.time_for_split_out > 10000) {
//				terminal.event_spit_out_coins = true;
//				terminal.fl_new_money = false;
//			}
//		}
//		else {
//			terminal.time_for_split_out = 0;
//		}
//
//
//		//HOPPERS
//		Hoppers();
//		Check_Hold_Hopper();
//
//
//		if (display->command == TERMINAL_DISPLAY_STATUS_MONEY_TOTAL) {
//			Display_Money(display->Display_1->display_string_1, terminal.money_total);
//		}
//
//		if (terminal.money_total == 0) {
//			display->command = TERMINAL_DISPLAY_STATUS_READY;
//			display->display_2->command = TERMINAL_DISPLAY_STATUS_READY;
//		}
//
//
//		if (terminal.command == TERMINAL_STATUS_SET_SETTINGS) {
//			Set_Settings();
//			if (terminal.money_total != 0) display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
//			else  display->command = TERMINAL_DISPLAY_STATUS_READY;
//		}
//
//		if (terminal.command == TERMINAL_STATUS_SET_SETTINGS_MANUAL) {
//			terminal.status = TERMINAL_STATUS_SET_SETTINGS_MANUAL;
//			Wait_Peripherals_Ready();
//			terminal.event_save_manual = false;
//			Set_Settings_Manual();
//			if (terminal.event_save_manual) {
//				Terminal_Reset();
//			}
//			if (terminal.money_total != 0) display->command = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
//			else  display->command = TERMINAL_DISPLAY_STATUS_READY;
//			//terminal.event_save_manual = true;
//			terminal.billacceptor->command = TERMINAL_BILLACCEPTOR_STATUS_NULL;
//			terminal.hopper->command = TERMINAL_HOPPER_STATUS_NULL;
//			terminal.command = TERMINAL_STATUS_READY;
//			terminal.hold_terminal = false;
//			terminal.hold_hopper_1 = false;
//			terminal.hold_hopper_2 = false;
//			terminal.hold_bill_acceptor = false;
//		}
//
//		if (terminal.command == TERMINAL_STATUS_ENCASHMENT) {
//			terminal.status = TERMINAL_STATUS_ENCASHMENT;
//			Encashment();
//			//terminal.money_total = 0;
//			Terminal_Reset();
//			terminal.command = TERMINAL_STATUS_READY;
//		}
//
//		//Замораживаем устройства
//		Hold_Terminal();
//
//		ThreadYield();
//
//		//Delay(1);
//	}
//
//}
//
//



CoreClass::CoreClass() {
	Money = 0;
}

void CoreClass::Init()
{
	Displays.Init();
	BillAcceptor.Init();
	Hoppers.Init();


#ifdef TERMINAL_USE_STM   
	Buttons.Init();
	BillAcceptor_TaskHandle = osThreadNew(BillAcceptorClass::BillAcceptor_Thread, NULL, &BillAcceptorTask_attributes);
	Display1_TaskHandle = osThreadNew(DisplayClass::Display_1_Thread, NULL, &Display1Task_attributes);
	Hopper_TaskHandle = osThreadNew(HopperCoreClass::Hoppers_Thread, NULL, &HopperTask_attributes);
	//  

  HoppersMSP_TaskHandle = osThreadNew(HoppersMSP.Hoppers_MSP_Thread, NULL, &HoppersMSPTask_attributes);
	Hopper1MSP_TaskHandle = osThreadNew(hopper_1_msp.Hopper_1_MSP_Thread, NULL, &Hopper1MSPTask_attributes);
	Hopper2MSP_TaskHandle = osThreadNew(hopper_2_msp.Hopper_2_MSP_Thread, NULL, &Hopper2MSPTask_attributes);
	BillAcceptorMSP_TaskHandle = osThreadNew(BillAcceptorMSP.Bill_Acceptor_MSP_Thread, NULL, &BillAcceptorMSPTask_attributes);
	ButtonsMSP_TaskHandle = osThreadNew(ButtonsMSPClass::Buttons_MSP_Thread, NULL, &ButtonsMSPTask_attributes);
#endif	//TERMINAL_USE_STM
}

static void Wait_Reset_Command(int timeout) {
#ifdef TERMINAL_USE_STM
	osStatus_t status;
	static ButtonsNS::MessageClass msg_buttons;
	status = Buttons.Messages.popMessageOut(&msg_buttons, timeout);
	if (status == osOK) {
		if (msg_buttons.command == ButtonsNS::RESET)
		{
			DEBUG("Reset MCU!!!!\n");
			HAL_NVIC_SystemReset();
		}
	}
#else
	Delay(timeout);
#endif //TERMINAL_USE_STM
}


void CoreClass::Core_Thread(void* arg) {
	osStatus_t status;
	static DisplayNS::MessageClass msg_display;
	static BillAcceptorNS::MessageClass msg_billacceptor;
	static HoppersNS::MessageClass msg_hoppers;

	DEBUG("START!!!\n");
	Terminal.Init();

	strcpy(Displays.Display_1.display_string, "    ");
	msg_display.command = DisplayNS::STRING;
	Displays.Display_1.Messages.pushMessageIn(&msg_display);
	Delay(1000);
	msg_display.command = DisplayNS::READY;
	Displays.Display_1.Messages.pushMessageIn(&msg_display);

	msg_billacceptor.command = BillAcceptorNS::READY;
	BillAcceptor.Messages.pushMessageIn(&msg_billacceptor);
	while (true)
	{
		Wait_Reset_Command(0);

		status = BillAcceptor.Messages.popMessageOut(&msg_billacceptor, 1);
		if (status == osOK) {
			if (msg_billacceptor.command == ACCEPTED)
			{
				Terminal.Money = BillAcceptor.bill;
				msg_display.command = DisplayNS::MONEY;
				msg_display.money = Terminal.Money;
				Displays.Display_1.Messages.pushMessageIn(&msg_display);
				Delay(2000);
				msg_hoppers.command = HoppersNS::SPIT_OUT;
				msg_hoppers.money = Terminal.Money;
				Hoppers.Messages.pushMessageIn(&msg_hoppers);
				msg_display.command = DisplayNS::SPIT_OUT_MONEY;
				Displays.Display_1.Messages.pushMessageIn(&msg_display);

			}
		}


		status = Hoppers.Messages.popMessageOut(&msg_hoppers, 1);
		if (status == osOK) {
			if (msg_hoppers.command == HoppersNS::SPIT_OUT_OK)
			{
				Terminal.Money = 0;
				msg_display.command = DisplayNS::READY;
				Displays.Display_1.Messages.pushMessageIn(&msg_display);
				msg_billacceptor.command = BillAcceptorNS::READY;
				BillAcceptor.Messages.pushMessageIn(&msg_billacceptor);
			}
			if (msg_hoppers.command == HoppersNS::SPIT_OUT_ERROR)
			{
				Terminal.Money = msg_hoppers.money;
				msg_display.command = DisplayNS::STRING_ERROR;
				Displays.Display_1.Messages.pushMessageIn(&msg_display);
				Delay(3000);
				msg_display.command = DisplayNS::MONEY;
				msg_display.money = Terminal.Money;
				Displays.Display_1.Messages.pushMessageIn(&msg_display);
				//Уходим в бесконечный цикл, ждем ресет
				Wait_Reset_Command(osWaitForever);
				//while(true){Delay(3000);}
			}
		}

    if(Terminal.Money == 0){
      if (Hoppers.isAlarm()){
          
          //Светим на экране ошибку
          msg_display.command = DisplayNS::STRING_ERROR;
          Displays.Display_1.Messages.pushMessageIn(&msg_display);
        while (true)
        {
          bool store_state_bill_acceptor = BillAcceptor.Inhibit;
          //if (!BillAcceptor.Inhibit) { //если приемник включен, тогда выключаем
            msg_billacceptor.command = BillAcceptorNS::HOLD;
            BillAcceptor.Messages.pushMessageIn(&msg_billacceptor);
          //}
          Wait_Reset_Command(1000);
          if (!Hoppers.isAlarm())
          {

            msg_display.command = DisplayNS::READY;
            Displays.Display_1.Messages.pushMessageIn(&msg_display);
            msg_billacceptor.command = BillAcceptorNS::READY;
            BillAcceptor.Messages.pushMessageIn(&msg_billacceptor);
            break;
          }
        }
      }
    }
    
	}

}




