/**
  ******************************************************************************
  * File Name          : Hopper.h
  ******************************************************************************
  */
  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_HOPPER_H
#define __TERMINAL_HOPPER_H
//#ifdef __cplusplus
// extern "C" {
//#endif
///* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include "Terminal/Terminal.h"
//
//
///**
//* @brief  Terminal coin acceptor error
//*/
//typedef enum {
//	TERMINAL_HOPPER_STATUS_READY = 0x00,
//	TERMINAL_HOPPER_STATUS_ERROR = 0x01,
//	TERMINAL_HOPPER_STATUS_SPIT_OUT = 0x02,
//	TERMINAL_HOPPER_STATUS_SPIT_OUT_OK = 0x03,
//	//commands
//	TERMINAL_HOPPER_STATUS_RESET = 0x08,
//	TERMINAL_HOPPER_STATUS_DO_NOT_STOP = 0x09,
//	TERMINAL_HOPPER_STATUS_SPIT_OUT_TWO_HOPPERS = 0x10,
//	TERMINAL_HOPPER_STATUS_SPIT_OUT_HOPPER_1 = 0x11,
//	TERMINAL_HOPPER_STATUS_SPIT_OUT_HOPPER_2 = 0x12,
//	TERMINAL_HOPPER_STATUS_NULL = 0x13,
//	TERMINAL_HOPPER_STATUS_SET_SETTINGS = 0x14,
//} TERMINAL_HopperStatusTypeDef;
///**
//* @brief  Terminal coin acceptor status
//*/
//typedef enum {
//	TERMINAL_HOPPER_ERROR_OK = 0x00,
////	TERMINAL_HOPPER_NO_COINS_TWO_HOPPERS = 0x01,
////	TERMINAL_HOPPER_NO_COINS_HOPPER = 0x02,
////	TERMINAL_HOPPER_NO_COINS_HOPPER_2 = 0x03,
//	TERMINAL_HOPPER_ERROR_NO_COINS = 0x04,
//	TERMINAL_HOPPER_ERROR_INHIBIT = 0x05,
//	TERMINAL_HOPPER_ERROR_CRASH = 0x06,
//} TERMINAL_HopperErrorTypeDef;
//
///**
//* @brief  Terminal coin acceptor status
//*/

//
///**
//  * @brief  Hopper core structure
//  */
//typedef struct __TERMINAL_HandleHopperTypeDef
//{
//	TERMINAL_HopperStatusTypeDef status;
//	TERMINAL_HopperErrorTypeDef error;
//	TERMINAL_HopperStatusTypeDef command;
//	TERMINAL_HopperStatusTypeDef responce;
//	int32_t	number;
//	int32_t	coins_total;
//	int32_t	count_coins;
//	int32_t	count_new_coins;
//	bool		event_spit_out_coins;
//	int32_t	value_of_coins;
//	int32_t	money_total;
//	//счетчик сколько вообще выдал монет хоппер за время работы
//	int32_t	count_total_spit_out_coins;
//	bool	alarm_sensor; //если сработал сенсор
//	bool	alarm_coint_emply; //если закончились монеты физически
//#ifdef TERMINAL_USE_WINDOWS
//	int32_t	coins_total_real;
//#endif /*TERMINAL_USE_WINDOWS*/
//} TERMINAL_HandleHopperTypeDef;
//
//typedef enum {
//	TERMINAL_HOPPER_1 = 0x01,
//	TERMINAL_HOPPER_2 = 0x02,
//} TERMINAL_HopperInstanceTypeDef;
//
///** 
//  * @brief  Hopper core structure
//  */
//typedef struct __TERMINAL_HandleCoreHopperTypeDef
//{
//	bool(*init)(uint32_t num);
//	bool(*reset)(void);
//#ifdef TERMINAL_USE_STM
//__NO_RETURN	void(*loop)(void *arg);
//#else
//			void(*loop)(void const *arg);
//#endif
//	bool(*calculate_proportion)(int32_t *count_1, int32_t *count_2);
//	TERMINAL_HopperErrorTypeDef(*Start_Split_Out)(uint32_t num, int32_t money_for_out, uint32_t timeout);
//	TERMINAL_HopperErrorTypeDef(*Wait_Hopper_Ready)(uint32_t timeout);
//	bool(*Send_Command)(TERMINAL_HopperStatusTypeDef cmd);
//	TERMINAL_HopperStatusTypeDef status;
//	TERMINAL_HopperErrorTypeDef error;
//	TERMINAL_HopperStatusTypeDef command;
//	TERMINAL_HopperStatusTypeDef responce;
//	TERMINAL_HandleHopperTypeDef	*hopper_1;
//	TERMINAL_HandleHopperTypeDef	*hopper_2;
//	bool		event_spit_out_coins;
//	bool		event_spit_out_hopper_1;
//	bool		event_spit_out_hopper_2;
//	uint32_t	proportion_hoppers;
//	int32_t		money_for_out;
//	int32_t		money_out_for_hardware;
//	int32_t		money_total;
//	uint32_t	number;
//	uint32_t	spit_out_coins;
//} TERMINAL_HandleCoreHopperTypeDef;
//
//#define HOPPER_MSGQUEUE_OBJECTS 20
//typedef struct {                                // object data type
//  uint32_t coint_out;
//  uint32_t error_msp;
//  TERMINAL_HopperErrorTypeDef error;
//} HopperMsgQueueTypeDef;
//#ifdef TERMINAL_USE_STM
//extern osMessageQueueId_t mid_Hopper1MsgQueue;
//extern osMessageQueueId_t mid_Hopper2MsgQueue;
//extern osMessageQueueId_t mid_Hopper1MsgQueue_response;
//extern osMessageQueueId_t mid_Hopper2MsgQueue_response;
//#endif /*TERMINAL_USE_STM*/
///* Exported constants --------------------------------------------------------*/
///* Exported Macros -----------------------------------------------------------*/
///* Exported functions --------------------------------------------------------*/
//TERMINAL_HandleCoreHopperTypeDef *Terminal_Get_HandleHopper(void);
//
//#ifdef __cplusplus
//}
//#endif

namespace HoppersNS
{

    typedef enum {
        READY = 0x00,
        SPIT_OUT = 0x01,
        SPIT_OUT_OK = 0x02,
        SPIT_OUT_ERROR = 0x03,
    } COMMAND;

    struct MessageClass
    {
        COMMAND command;
        uint32_t money;
        uint32_t coins;
    };

    /**
      * @brief  Hopper core structure
      */
    class HopperClass
    {
    public:
        int32_t num; //номер хоппера, нужен для расспознования и отладки
        int32_t	value_of_coins;
        int32_t	money_for_out; //сюда записываем количество на выдачу
        QueueMessageClass< MessageClass, 10 > Messages;
    public:
        HopperClass();
        void Init();
        int Split_Out();
    };

    /**
      * @brief  Hopper core structure
      */
    class HopperCoreClass
    {
    public:
        HopperClass Hopper_1;
        HopperClass Hopper_2;
        int32_t		money_for_out;
        QueueMessageClass< MessageClass, 10 > Messages;
    public:
        HopperCoreClass();
        static void Hoppers_Thread(void* arg);
        void Init();
        int Two_Hoppers_Split_Out(uint32_t money_out);
        void Calculate_Proportion(int money);
        bool isAlarm();
    };


    extern HopperCoreClass Hoppers;

}	//HoppersNS

#endif /*__TERMINAL_HOPPER_H*/
