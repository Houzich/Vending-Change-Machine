/**
  ******************************************************************************
  * File Name          : Bill_Acceptor.h
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_BILL_ACCEPTOR_H
#define __TERMINAL_BILL_ACCEPTOR_H
//#ifdef __cplusplus
// extern "C" {
//#endif
/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include "Tamplates.h"
//#ifdef TERMINAL_USE_STM
//#include "cmsis_os2.h"
//#endif /*TERMINAL_USE_STM*/
//
///**
//* @brief  Terminal bill acceptor error
//*/
//typedef enum {
//	TERMINAL_BILLACCEPTOR_STATUS_READY = 0x00,
//	TERMINAL_BILLACCEPTOR_STATUS_ACCEPTED = 0x01,
//	//command
//	TERMINAL_BILLACCEPTOR_STATUS_NULL = 0x02,
//	TERMINAL_BILLACCEPTOR_STATUS_SET_SETTINGS = 0x03,
//	TERMINAL_BILLACCEPTOR_STATUS_HOLD = 0x04,
//} TERMINAL_BillAcceptorStatusTypeDef;
///**
//* @brief  Terminal bill acceptor status
//*/
//typedef enum {
//	TERMINAL_BILLACCEPTOR_ERROR_OK = 0x00U,
//} TERMINAL_BillAcceptorErrorTypeDef;
///** 
//  * @brief  Terminal main structure
//  */
//typedef struct __TERMINAL_HandleBillAcceptorTypeDef
//{
//	bool(*init)(void);
//	bool(*reset)(void);
//#ifdef TERMINAL_USE_STM
//__NO_RETURN	void(*loop)(void *arg);
//#else
//			void(*loop)(void const *arg);
//#endif
//	TERMINAL_BillAcceptorStatusTypeDef status;
//	TERMINAL_BillAcceptorErrorTypeDef error;
//	TERMINAL_BillAcceptorStatusTypeDef command;
//	TERMINAL_BillAcceptorStatusTypeDef responce;
//	int32_t	bills_accepted[40];
//	int32_t	bills_total;
//	int32_t	bill;
//	int32_t	count_bills;
//	int32_t	count_new_bills;
//	bool		fl_accepted;
//} TERMINAL_HandleBillAcceptorTypeDef;
//
//
//#define BILL_MSGQUEUE_OBJECTS 20
//typedef struct {                                // object data type
//  uint32_t count_pulse;
//} BillMsgQueueTypeDef;
//#ifdef TERMINAL_USE_STM
//extern osMessageQueueId_t mid_BillMsgQueue;
//#endif /*TERMINAL_USE_STM*/
//
///* Exported constants --------------------------------------------------------*/
///* Exported Macros -----------------------------------------------------------*/
///* Exported functions --------------------------------------------------------*/
//TERMINAL_HandleBillAcceptorTypeDef *Terminal_Get_HandleBillAcceptor(void);
//
//#ifdef __cplusplus
//}
//#endif


namespace BillAcceptorNS
{

	enum COMMAND {
		READY = 0x00,
		SETTINGS = 0x01,
		HOLD = 0x02,
		ACCEPTED = 0x03,
	};

	struct MessageClass
	{
		COMMAND command;
		uint32_t count_pulse;
	};


	class BillAcceptorClass
	{
	public:
		int32_t	bill;
		bool Inhibit; //показывает заблокирован обменник или нет
		QueueMessageClass< MessageClass, 10 > Messages;
	public:
		BillAcceptorClass();
    void Init();
		static void BillAcceptor_Thread(void* arg);
		void BillAcceptor_Inhibit_Off();
		void BillAcceptor_Inhibit_On();
	};
	extern BillAcceptorClass BillAcceptor;

}
#endif /*__TERMINAL_BILL_ACCEPTOR_H*/









