/**
  ******************************************************************************
  * File Name          : Hoppers_MSP.c
  ******************************************************************************
  */
  /* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "Terminal/Terminal.h"
#include "Hopper_1_MSP.h"
#include "Hopper_2_MSP.h"
#include "Hoppers_MSP.h"
#include "stm32f4xx_hal.h"

#ifdef TERMINAL_USE_STM
#include "cmsis_os2.h"
#elif defined(TERMINAL_USE_WINDOWS)
#include "..\Threads.h"
#include <Windows.h>
#endif /*TERMINAL_USE_STM*/
using  namespace Hopper1MSPNS;
using  namespace Hopper2MSPNS;
namespace HoppersMSPNS
{
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
//used when debugging, declared in the file Terminal.h
#ifdef DEBUG_TERMINAL_HOPPER_MSP
#undef DEBUG /* DEBUG */
#undef DEBUG_PRINT /* DEBUG_PRINT */
#define DEBUG(...)		do {debug_header("HOPPER OUT MSP: ", __VA_ARGS__);} while (0)
#define DEBUG_PRINT(x)		debug_print x;
#else
#define DEBUG(...)
#define DEBUG_PRINT(x)
#endif // DEBUG_TERMINAL_HOPPER_MSP

 /* definition and creation of defaultTask */
uint64_t hoppersmsp_stk[2048 / 8];
const osThreadAttr_t HoppersMSPTask_attributes = {
  .name = "HoppersMSPTask",
  .stack_mem = &hoppersmsp_stk[0],
  .stack_size = sizeof(hoppersmsp_stk),
  .priority = (osPriority_t)osPriorityAboveNormal,
};
osThreadId_t HoppersMSP_TaskHandle;

HoppersMSPClass HoppersMSP;
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
	HoppersMSPClass::HoppersMSPClass() {
	}

  void HoppersMSPClass::Init()
  {
    Messages.queue_in = osMessageQueueNew(10, sizeof(Messages.message), NULL);
    Messages.queue_out = osMessageQueueNew(10, sizeof(Messages.message), NULL);
  }

  void HoppersMSPClass::Hoppers_MSP_Thread(void* arg)
  {
    MessageClass msg;
    osStatus_t status;
    for (;;)
    {
        status = HoppersMSP.Messages.popMessageIn(&msg, osWaitForever);
        if (msg.command == SPLIT_OUT_HOPPER_1) {
          uint32_t pulses = msg.pulses;
          for (int i = 0; i < pulses; i++)
          {
            hopper_1_msp.PAYOUT_Pin_Reset();
            osDelay(20);
            hopper_1_msp.PAYOUT_Pin_Set();
            osDelay(100);
          }
        }   
        if (msg.command == SPLIT_OUT_HOPPER_2) {
          uint32_t pulses = msg.pulses;
          for (int i = 0; i < pulses; i++)
          {
            hopper_2_msp.PAYOUT_Pin_Reset();
            osDelay(20);
            hopper_2_msp.PAYOUT_Pin_Set();
            osDelay(100);
          }
        } 
    }
  }

} //namespace HoppersMSPNS
