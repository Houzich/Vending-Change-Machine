/**
  ******************************************************************************
  * File Name          : Bill_Acceptor.c
  ******************************************************************************
  */
  /* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "Terminal/Terminal.h"

#ifdef TERMINAL_USE_STM
#include "Terminal_MSP.h"
#include "cmsis_os2.h"
#endif /*TERMINAL_USE_STM*/

namespace BillAcceptorNS
{
#ifdef TERMINAL_USE_STM
using namespace BillAcceptorMSPNS;
#endif /*TERMINAL_USE_STM*/
	/* Private typedef -----------------------------------------------------------*/
	/* Private define ------------------------------------------------------------*/
	/* Private macro -------------------------------------------------------------*/
	//used when debugging, declared in the file Terminal.h
#ifdef DEBUG_TERMINAL_BILL_ACCEPTOR
#undef DEBUG /* DEBUG */
#undef DEBUG_PRINT /* DEBUG_PRINT */
#define DEBUG(...)		do {debug_header("BILL ACCEPTOR: ", __VA_ARGS__);} while (0)
#define DEBUG_PRINT(x)		debug_print x;
#else
#define DEBUG(...)
#define DEBUG_PRINT(x)
#endif // DEBUG_TERMINAL_BILL_ACCEPTOR
/* Private variables ---------------------------------------------------------*/
#ifdef TERMINAL_USE_STM
	osMessageQueueId_t mid_BillMsgQueue = NULL;
#endif /*TERMINAL_USE_STM*/

	BillAcceptorClass	BillAcceptor;
	/* Private function prototypes -----------------------------------------------*/

	/* Exported functions --------------------------------------------------------*/
	BillAcceptorClass::BillAcceptorClass() {
		Inhibit = false;
		bill = 0;
	}

  void BillAcceptorClass::Init()
	{
    #ifdef TERMINAL_USE_STM
    Messages.queue_in = osMessageQueueNew(20, sizeof(Messages.message), NULL);
    Messages.queue_out = osMessageQueueNew(20, sizeof(Messages.message), NULL);
	BillAcceptorMSP.Init();
    #endif /*TERMINAL_USE_STM*/
  }
	void BillAcceptorClass::BillAcceptor_Inhibit_Off()
	{
#ifdef TERMINAL_USE_STM
		osEventFlagsSet(BillAcceptorMSP.Event_ID, BILL_ACCEPTOR_INHIBIT_OFF);
#endif /*TERMINAL_USE_STM*/
		Inhibit = false;
}

	void BillAcceptorClass::BillAcceptor_Inhibit_On()
	{
#ifdef TERMINAL_USE_STM
		osEventFlagsSet(BillAcceptorMSP.Event_ID, BILL_ACCEPTOR_INHIBIT_ON);
#endif /*TERMINAL_USE_STM*/
		Inhibit = true;
	}
	/*###############################################################*/
	/*###############################################################* Terminal_Loop -->*/
	/*###############################################################*/
	void BillAcceptorClass::BillAcceptor_Thread(void* arg)
	{
		BillAcceptor.BillAcceptor_Inhibit_On();
		while (1) {
			MessageClass msg;
			osStatus_t status;
			status = BillAcceptor.Messages.popMessageIn(&msg, osWaitForever);
			if (status != osOK) continue;

			if (msg.command == ACCEPTED) 
			{
				BillAcceptor.bill = msg.count_pulse * 100 * 5;
				BillAcceptor.Messages.pushMessageOut(&msg);
				BillAcceptor.BillAcceptor_Inhibit_On();
			}
			if (msg.command == HOLD)
			{
				BillAcceptor.BillAcceptor_Inhibit_On();
			}
			if (msg.command == SETTINGS)
			{
				BillAcceptor.BillAcceptor_Inhibit_On();
			}
			if (msg.command == READY)
			{
				BillAcceptor.BillAcceptor_Inhibit_Off();
			}
		}

	}

}	//BillAcceptorNS

