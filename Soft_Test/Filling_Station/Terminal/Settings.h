///**
//  ******************************************************************************
//  * File Name          : Settings.h
//  ******************************************************************************
//  */
///* Define to prevent recursive inclusion -------------------------------------*/
//#ifndef __TERMINAL_SETTINGS_H
//#define __TERMINAL_SETTINGS_H
//#ifdef __cplusplus
// extern "C" {
//#endif
///* Includes ------------------------------------------------------------------*/
//#include <stdbool.h>
//#include <stdint.h>
//#include "Terminal/Core.h"
//
///* Exported constants --------------------------------------------------------*/
///**
//* @brief  Terminal bill acceptor error
//*/
//typedef enum {
//	TERMINAL_SETTINGS_STATUS_READY = 0x00,
//	TERMINAL_SETTINGS_STATUS_START = 0x01,
//	TERMINAL_SETTINGS_STATUS_SETTINGS = 0x02,
//	TERMINAL_SETTINGS_STATUS_VALUE = 0x03,
//	TERMINAL_SETTINGS_STATUS_SAVE = 0x04,
//	TERMINAL_SETTINGS_STATUS_RETURN = 0x05,
//} TERMINAL_SettingsStatusTypeDef;
///**
//* @brief  Terminal bill acceptor status
//*/
//typedef enum {
//	TERMINAL_SETTINGS_ERROR_OK = 0x00,
//} TERMINAL_SettingsErrorTypeDef;
//
///**
//  * @brief  Terminal main structure
//  */
//typedef struct __TERMINAL_HandleSettingsTypeDef
//{
//	bool(*init)(void);
//	bool(*reset)(void);
//	void(*loop)(void);
//	TERMINAL_SettingsStatusTypeDef status;
//	TERMINAL_SettingsErrorTypeDef error;
//	TERMINAL_SettingsStatusTypeDef command;
//	TERMINAL_SettingsStatusTypeDef command_last;
//	TERMINAL_SettingsStatusTypeDef responce;
//	int32_t	position_settings;
//	int32_t	position_value;
//	int32_t	digit_value;
//	int32_t	value;
//} TERMINAL_HandleSettingsTypeDef;
///* Exported Macros -----------------------------------------------------------*/
///* Exported functions --------------------------------------------------------*/
//void Callback_Buttons_Settings(TERMINAL_ButtonsTypeDef num);
//void Set_Settings_Manual(void);
//void Encashment(void);
//void Check_Receive_Settings(TERMINAL_SettingsTypeDef* receive);
//#ifdef __cplusplus
//}
//#endif
//#endif /*__TERMINAL_SETTINGS_H*/
