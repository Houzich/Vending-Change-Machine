///**
//  ******************************************************************************
//  * File Name          : Settings.c
//  ******************************************************************************
//  */
//  /* Includes ------------------------------------------------------------------*/
//#include <string.h>
//#include "Terminal/Settings.h"
//#include "Terminal/Core.h"
//#include "Terminal/Terminal.h"
//
//#ifdef TERMINAL_USE_STM
//#include "cmsis_os2.h"
//#include "stm32f4xx.h"
//#include <math.h>
//#include "FLASH.h"
//#elif defined(TERMINAL_USE_WINDOWS)
//#include <iostream>
//#include <thread>
//#include <chrono>
//#endif /*TERMINAL_USE_STM*/
///* Private typedef -----------------------------------------------------------*/
///* Private define ------------------------------------------------------------*/
///* Private macro -------------------------------------------------------------*/
////used when debugging, declared in the file Terminal.h
//#ifdef DEBUG_TERMINAL_SETTINGS
//#undef DEBUG /* DEBUG */
//#undef DEBUG_PRINT /* DEBUG_PRINT */
//#define DEBUG(...)		do {debug_header("SETTINGS: ", __VA_ARGS__);} while (0)
//#define DEBUG_PRINT(x)		debug_print x;
//#else
//#define DEBUG(...)
//#define DEBUG_PRINT(x)
//#endif // DEBUG_TERMINAL_SETTINGS
///* Private variables ---------------------------------------------------------*/
//
///* Private function prototypes -----------------------------------------------*/
//static void Check_Buttons(void);
///* Exported functions --------------------------------------------------------*/
//extern TERMINAL_HandleTypeDef terminal;
//extern bool Display_Strings(const char *string_1, const char *string_2, uint32_t num);
//
//TERMINAL_HandleSettingsTypeDef sett;
///*###############################################################*/
///*###############################################################* Delay -->*/
///*###############################################################*/
//static void Delay(uint32_t ms)
//{
//#ifdef TERMINAL_USE_STM
//	osDelay(ms);
//#elif defined(TERMINAL_USE_HAL)
//	HAL_Delay(ms);
//#elif defined(TERMINAL_USE_WINDOWS)
//	//std::this_thread::sleep_for(std::chrono::milliseconds(ms));
//	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
//#endif /*TERMINAL_USE_STM*/
//}
//#ifdef TERMINAL_USE_WINDOWS
///*###############################################################*/
///*###############################################################* HAL_GetTick -->*/
///*###############################################################*/
//static uint32_t HAL_GetTick(void) {
//	uint32_t result = (uint32_t)std::chrono::duration_cast<std::chrono::milliseconds>(
//		std::chrono::system_clock::now().time_since_epoch()
//		).count();
//	return result;
//}
//#endif /*TERMINAL_USE_WINDOWS*/
///*###############################################################*/
///*###############################################################* Init -->*/
///*###############################################################*/
//static void Init(void)
//{
//	sett.status = TERMINAL_SETTINGS_STATUS_READY;
//	sett.position_settings = 0;
//	sett.position_value = 0;
//}
///*###############################################################*/
///*###############################################################* Show -->*/
///*###############################################################*/
//void Display(char *data, TERMINAL_SettingsStatusTypeDef cmd, uint32_t timeout)
//
//{
//	uint32_t tickstart = HAL_GetTick();
//	while (sett.command == cmd) {
//		if (timeout != NULL) {
//			if (HAL_GetTick() - tickstart >= timeout) {
//				break;
//			}
//		}
//		Display_Strings((const char *)data, "    ", 3);
//		Delay(1);
//	}
//}
///*###############################################################*/
///*###############################################################* Display_Sett -->*/
///*###############################################################*/
//void Display_Value(uint32_t value, TERMINAL_SettingsStatusTypeDef cmd, uint32_t timeout)
//{
//	char str[10];
//	sprintf(str, "%04d", value);
//	uint32_t tickstart = HAL_GetTick();
//	while (sett.command == cmd) {
//		if (timeout != NULL) {
//			if (HAL_GetTick() - tickstart >= timeout) {
//				break;
//			}
//		}
//		Display_Strings((const char *)str, "    ", 3);
//		Delay(1);
//	}
//}
///*###############################################################*/
///*###############################################################* Display_Sett -->*/
///*###############################################################*/
//void Display_Sett(uint32_t num, TERMINAL_SettingsStatusTypeDef cmd, uint32_t timeout)
//{
//	char str[10];
//
//	uint32_t tickstart = HAL_GetTick();
//	while (sett.command == cmd) {
//		if (num < 10) sprintf(str, "S_0%d", num);
//		else  sprintf(str, "S_%d", num);
//		if (timeout != NULL) {
//			if (HAL_GetTick() - tickstart >= timeout) {
//				break;
//			}
//		}
//		Display_Strings((const char *)str, "    ", 3);
//		Delay(1);
//	}
//}
///*###############################################################*/
///*###############################################################* Display_Sett -->*/
///*###############################################################*/
//void Display_String(char *str, TERMINAL_SettingsStatusTypeDef cmd, uint32_t timeout)
//{
//	Display(str, cmd, timeout);
//}
//
///*###############################################################*/
///*###############################################################* Set_Value -->*/
///*###############################################################*/
//static void Set_Value(void)
//{
//	char str_1[10];
//	char str_2[10];
//	char str_3[10];
//	sett.status = TERMINAL_SETTINGS_STATUS_VALUE;
//
//	uint32_t count = 0;
//	bool bl = false;
//	while (sett.command == TERMINAL_SETTINGS_STATUS_VALUE) {
//		sprintf(str_1, "%04d", sett.value);
//		sprintf(str_2, "%s", "    ");
//		sprintf(str_3, "%s", "    ");
//		Check_Buttons();
//		uint32_t position = 3 - sett.position_value;
//		if (count < 15) sprintf(str_3, "%s", str_1);
//		else sprintf(str_3, "%s", "    ");
//
//		bl = !bl;
//		if (bl) str_3[position] = str_1[position];
//		else str_3[position] = ' ';
//
//		Display_String(str_3, TERMINAL_SETTINGS_STATUS_VALUE, 100);
//
//		count++;
//		if (count > 15) count = 0;
//	}
//	sett.status = TERMINAL_SETTINGS_STATUS_READY;
//}
///*###############################################################*/
///*###############################################################* Set_Settings -->*/
///*###############################################################*/
//static void Set_Settings(void)
//{
//	sett.status = TERMINAL_SETTINGS_STATUS_SETTINGS;
//	while (sett.command == TERMINAL_SETTINGS_STATUS_SETTINGS) {
//		Check_Buttons();
//		Display_Sett(sett.position_settings, TERMINAL_SETTINGS_STATUS_SETTINGS, 700);
//		Display_String((char *)"    ", TERMINAL_SETTINGS_STATUS_SETTINGS, 100);
//	}
//	sett.status = TERMINAL_SETTINGS_STATUS_READY;
//}
///*###############################################################*/
///*###############################################################* Enable_Disable_Settings -->*/
///*###############################################################*/
//static void Enable_Disable_Buttons(bool state)
//{
//	terminal.enable_button_up = state;
//	terminal.enable_button_down = state;
//	terminal.enable_button_left = state;
//	terminal.enable_button_right = state;
//	terminal.enable_button_ok = state;
//	terminal.enable_button_return = state;
//}
///*###############################################################*/
///*###############################################################* Enable_Disable_Settings -->*/
///*###############################################################*/
//static void Check_Buttons(void)
//{
//	if (sett.status == TERMINAL_SETTINGS_STATUS_SETTINGS) {
//		if (sett.position_settings == NUM_SETTINGS_MANUAL)
//			terminal.enable_button_up = false;
//		else
//			terminal.enable_button_up = true;
//		if (sett.position_settings == 0)
//			terminal.enable_button_down = false;
//		else
//			terminal.enable_button_down = true;
//
//		terminal.enable_button_left = false;
//		terminal.enable_button_right = false;
//		terminal.enable_button_ok = true;
//		terminal.enable_button_return = true;
//		terminal.enable_button_settings = false;
//		terminal.enable_button_encashment = false;
//	}
//	if (sett.status == TERMINAL_SETTINGS_STATUS_VALUE) {
//		if (sett.value == 9) terminal.enable_button_up = false;
//		else terminal.enable_button_up = true;
//
//		if (sett.value == 0) terminal.enable_button_down = false;
//		else terminal.enable_button_down = true;
//
//		if (sett.position_value == 0) terminal.enable_button_right = false;
//		else terminal.enable_button_right = true;
//
//		if (sett.position_value == 3) terminal.enable_button_left = false;
//		else terminal.enable_button_left = true;
//
//		terminal.enable_button_ok = true;
//		terminal.enable_button_return = true;
//		terminal.enable_button_settings = false;
//		terminal.enable_button_encashment = false;
//	}
//
//	if (sett.status == TERMINAL_SETTINGS_STATUS_SAVE) {
//		Enable_Disable_Buttons(false);
//	}
//
//	if (sett.status == TERMINAL_SETTINGS_STATUS_START) {
//		terminal.enable_button_settings = false;
//		terminal.enable_button_encashment = false;
//		Enable_Disable_Buttons(true);
//	}
//	if (sett.status == TERMINAL_SETTINGS_STATUS_READY) {
//		terminal.enable_button_settings = true;
//		terminal.enable_button_encashment = true;
//		Enable_Disable_Buttons(false);
//	}
//	if (sett.status == TERMINAL_SETTINGS_STATUS_RETURN) {
//		terminal.enable_button_settings = true;
//		terminal.enable_button_encashment = true;
//		Enable_Disable_Buttons(false);
//	}
//}
///*###############################################################*/
///*###############################################################* Set_Settings_Manual -->*/
///*###############################################################*/
//void Set_Settings_Manual(void)
//{
//	Init();
//	sett.status = TERMINAL_SETTINGS_STATUS_START;
//	terminal.enable_button_settings = false;
//	terminal.enable_button_encashment = false;
//	Display_Strings("SEtt", "    ", 3);
//	Delay(2000);
//	sett.command = TERMINAL_SETTINGS_STATUS_SETTINGS;
//	sett.status = TERMINAL_SETTINGS_STATUS_SETTINGS;
//	Check_Buttons();
//	while (1) {
//		Set_Settings();
//		Set_Value();
//		if (sett.command == TERMINAL_SETTINGS_STATUS_RETURN) {
//			sett.status = TERMINAL_SETTINGS_STATUS_RETURN;
//			Check_Buttons();
//			return;
//		}
//		if (sett.command == TERMINAL_SETTINGS_STATUS_SAVE) {
//			sett.status = TERMINAL_SETTINGS_STATUS_SAVE;
//			terminal.enable_button_settings = false;
//			terminal.enable_button_encashment = false;
//			Enable_Disable_Buttons(false);
//			Display_Strings("SAUE", "    ", 3);
//      Delay(200);
//			*(uint32_t *)((uint32_t *)&terminal.settings + sett.position_settings) = sett.value;
//			terminal.event_save_manual = true;
//      #ifdef TERMINAL_USE_STM
//      FLASH_Save_Settings();
//      #endif //TERMINAL_USE_STM
//			//Delay(1000);
//			sett.status = TERMINAL_SETTINGS_STATUS_READY;
//			sett.command = sett.command_last;
//			Check_Buttons();
//		}
//	}
//
//
//}
///*###############################################################*/
///*###############################################################* Encashment -->*/
///*###############################################################*/
//void Encashment(void)
//{
//	Init();
//	terminal.enable_button_settings = false;
//	terminal.enable_button_encashment = false;
//	Display_Strings("EnCA", "    ", 3);
//	Delay(2000);
//	Init();
//}
///*###############################################################*/
///*###############################################################* Callback_Buttons_Settings -->*/
///*###############################################################*/
//void Callback_Buttons_Settings(TERMINAL_ButtonsTypeDef num)
//{
//	//uint32_t temp;
//	char str[10];
//  
//  //osKernelGetTickCount ()
//	switch (num) {
//	case TERMINAL_BUTTON_UP:
//		if (sett.status == TERMINAL_SETTINGS_STATUS_SETTINGS) {
//			sett.position_settings++;
//			if (sett.position_settings > NUM_SETTINGS_MANUAL)
//				sett.position_settings = NUM_SETTINGS_MANUAL;
//		}
//		if (sett.status == TERMINAL_SETTINGS_STATUS_VALUE) {
//			sett.digit_value++;
//			if (sett.digit_value > 9) {
//				sett.digit_value = 9;
//			}
//			else {
//				sett.value += (int32_t)pow(10, sett.position_value);
//			}
//
//		}
//		break;
//	case TERMINAL_BUTTON_DOWN:
//		if (sett.status == TERMINAL_SETTINGS_STATUS_SETTINGS) {
//			sett.position_settings--;
//			if (sett.position_settings < 1)
//				sett.position_settings = 0;
//		}
//		if (sett.status == TERMINAL_SETTINGS_STATUS_VALUE) {
//			sett.digit_value--;
//			if (sett.digit_value < 0) {
//				sett.digit_value = 0;
//			}
//			else {
//				sett.value -= (int32_t)pow(10, sett.position_value);
//			}
//
//
//		}
//		break;
//	case TERMINAL_BUTTON_LEFT:
//		if (sett.status == TERMINAL_SETTINGS_STATUS_VALUE) {
//			sett.position_value++;
//			if (sett.position_value > 3) {
//				sett.position_value = 3;
//			}
//			else {
//				sprintf(str, "%04d", sett.value);
//				sett.digit_value = (uint32_t)str[3 - sett.position_value] - (uint32_t)'0';
//			}
//				
//		}
//		break;
//	case TERMINAL_BUTTON_RIGHT:
//		if (sett.status == TERMINAL_SETTINGS_STATUS_VALUE) {
//			sett.position_value--;
//			if (sett.position_value < 0) {
//				sett.position_value = 0;
//			}
//			else {
//				sprintf(str, "%04d", sett.value);
//				sett.digit_value = (uint32_t)str[3 - sett.position_value] - (uint32_t)'0';
//			}
//		}
//		break;
//	case TERMINAL_BUTTON_OK:
//		switch ((uint32_t)sett.status) {
//		case TERMINAL_SETTINGS_STATUS_SETTINGS:
//			sett.command = TERMINAL_SETTINGS_STATUS_VALUE;
//			sett.value = *(uint32_t *)((uint32_t *)&terminal.settings + sett.position_settings);
//			sett.digit_value = sett.value % 10;
//			sett.position_value = 0;
//			break;
//		case TERMINAL_SETTINGS_STATUS_VALUE:
//			sett.command_last = sett.command;
//			sett.command = TERMINAL_SETTINGS_STATUS_SAVE;
//			break;
//		}
//		break;
//	case TERMINAL_BUTTON_RETURN:
//		switch ((uint32_t)sett.status) {
//		case TERMINAL_SETTINGS_STATUS_SETTINGS:
//			sett.command = TERMINAL_SETTINGS_STATUS_RETURN;
//			break;
//		case TERMINAL_SETTINGS_STATUS_VALUE:
//			sett.command = TERMINAL_SETTINGS_STATUS_SETTINGS;
//			break;
//		}
//		break;
//	case TERMINAL_BUTTON_SETTINGS:
//		sett.command = TERMINAL_SETTINGS_STATUS_SETTINGS;
//		break;
//  default: break;
//	}
//	Check_Buttons();
//}
//
//
///*###############################################################*/
///*###############################################################* Actions_From_Received_Settings -->*/
///*###############################################################*/
//void Actions_From_Received_Settings(TERMINAL_SettingsTypeDef* receive)
//{
//	TERMINAL_HandleTypeDef* hterm = Terminal_Get_Handle();
//	bool core_reset = false;
//	if (hterm->settings.number_billacceptors != receive->number_billacceptors)
//	{
//		core_reset = true;
//	}
//	if (hterm->settings.number_buttons != receive->number_buttons)
//	{
//		core_reset = true;
//	}
//	if (hterm->settings.number_carddispensers != receive->number_carddispensers)
//	{
//		core_reset = true;
//	}
//	if (hterm->settings.number_cardreaders != receive->number_cardreaders)
//	{
//		core_reset = true;
//	}
//	if (hterm->settings.number_coinacceptors != receive->number_coinacceptors)
//	{
//		core_reset = true;
//	}
//	if (hterm->settings.number_hoppers != receive->number_hoppers)
//	{
//		core_reset = true;
//	}
// 
//#ifdef TERMINAL_USE_WINDOWS
//		memcpy(&hterm->settings, &hterm->settings_receive, sizeof(TERMINAL_SettingsTypeDef));
//#endif //TERMINAL_USE_WINDOWS
//
//  
//	if (core_reset) {
//		memcpy(&hterm->settings, &hterm->settings_receive, sizeof(TERMINAL_SettingsTypeDef));
//#ifdef TERMINAL_USE_WINDOWS
//		//if (Term_Soft.Mode == Term_Soft.TERMINAL_SOFT_SERVER)
//		//{
//		//	Terminal_Init();
//		//}
//#endif //TERMINAL_USE_WINDOWS
//		hterm->command = TERMINAL_STATUS_SET_SETTINGS;
//
//	}
//}
///*###############################################################*/
///*###############################################################* Check_Receive_Settings -->*/
///*###############################################################*/
//void Check_Receive_Settings(TERMINAL_SettingsTypeDef *receive)
//{
//	//here we check the settings for correctness
//	//here actions
//	Actions_From_Received_Settings(receive);
//}
