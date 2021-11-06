/**
  ******************************************************************************
  * File Name          : Hopper_MSP.c
  ******************************************************************************
  */
  /* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "Hopper_2_MSP.h"
#include "Hoppers_MSP.h"
#include "stm32f4xx_hal.h"
#include "Terminal/Terminal.h"

#ifdef TERMINAL_USE_STM
#include "cmsis_os2.h"
#elif defined(TERMINAL_USE_WINDOWS)
#include "..\Threads.h"
#include <Windows.h>
#endif /*TERMINAL_USE_STM*/

extern uint32_t Check_CMSIS_Flags_Functions_Error_Codes(uint32_t flags);

namespace Hopper2MSPNS
{

using namespace HoppersMSPNS;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
//used when debugging, declared in the file Terminal.h
#ifdef DEBUG_TERMINAL_HOPPER_MSP
#undef DEBUG /* DEBUG */
#undef DEBUG_PRINT /* DEBUG_PRINT */
#define DEBUG(...)		do {debug_header("HOPPER 2 MSP: ", __VA_ARGS__);} while (0)
#define DEBUG_PRINT(x)		debug_print x;
#else
#define DEBUG(...)
#define DEBUG_PRINT(x)
#endif // DEBUG_TERMINAL_HOPPER_MSP

 /* definition and creation of defaultTask */
uint64_t hopper2msp_stk[2048 / 8];
const osThreadAttr_t Hopper2MSPTask_attributes = {
  .name = "Hopper2MSPTask",
  .stack_mem = &hopper2msp_stk[0],
  .stack_size = sizeof(hopper2msp_stk),
  .priority = (osPriority_t)osPriorityAboveNormal,
};
osThreadId_t Hopper2MSP_TaskHandle;


/* Private variables ---------------------------------------------------------*/
HopperMSPClass hopper_2_msp;
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
static void Debug_Pins(void);

HopperMSPClass::HopperMSPClass() {
  alarm_inhibit = false;
  alarm_coint_emply = false;
  alarm_credit = false;
  Start = false;
}

void HopperMSPClass::GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;  

	GPIO_InitStruct.Pin = HOPPER_2_INHIBIT_Pin;
	HAL_GPIO_Init(HOPPER_2_INHIBIT_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = HOPPER_2_METER_Pin;
	HAL_GPIO_Init(HOPPER_2_METER_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = HOPPER_2_CREDIT_Pin;
	HAL_GPIO_Init(HOPPER_2_CREDIT_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = HOPPER_2_COIN_EMPTY_Pin;
	HAL_GPIO_Init(HOPPER_2_COIN_EMPTY_GPIO_Port, &GPIO_InitStruct);

	PAYOUT_Pin_Set();
	GPIO_InitStruct.Pin = HOPPER_2_PAYOUT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(HOPPER_2_PAYOUT_GPIO_Port, &GPIO_InitStruct);

  inhibit_pin_state = HAL_GPIO_ReadPin(HOPPER_2_INHIBIT_GPIO_Port, HOPPER_2_INHIBIT_Pin);
  meter_pin_state = HAL_GPIO_ReadPin(HOPPER_2_METER_GPIO_Port, HOPPER_2_METER_Pin);
  credit_pin_state = HAL_GPIO_ReadPin(HOPPER_2_CREDIT_GPIO_Port, HOPPER_2_CREDIT_Pin);
  coin_empty_pin_state = HAL_GPIO_ReadPin(HOPPER_2_COIN_EMPTY_GPIO_Port, HOPPER_2_COIN_EMPTY_Pin);
}


void HopperMSPClass::Init()
{
  Messages.queue_in = osMessageQueueNew(10, sizeof(Messages.message), NULL);
  Messages.queue_out = osMessageQueueNew(10, sizeof(Messages.message), NULL);
  Event_ID = osEventFlagsNew(NULL);
  GPIO_Init();
}


void HopperMSPClass::PAYOUT_Pin_Set(void) {
	HAL_GPIO_WritePin(HOPPER_2_PAYOUT_GPIO_Port, HOPPER_2_PAYOUT_Pin, GPIO_PIN_SET);
}

void HopperMSPClass::PAYOUT_Pin_Reset(void) {
  HAL_GPIO_WritePin(HOPPER_2_PAYOUT_GPIO_Port, HOPPER_2_PAYOUT_Pin, GPIO_PIN_RESET);
}

void HopperMSPClass::Hopper_2_MSP_Thread(void* argument)
{
	uint32_t flags;
  hopper_2_msp.Start = true;
	for (;;)
	{
    hopper_2_msp.Check_Alarm();
    
    MessageClass msg;
		osStatus_t status;
		status = hopper_2_msp.Messages.popMessageIn(&msg, 1);   // wait for message
		
    if (status == osOK) {
			//Coints out
			int32_t coint_out = msg.coins;
			hopper_2_msp.Out_Coins(&coint_out);
			msg.coins = coint_out;
      hopper_2_msp.Messages.pushMessageOut(&msg);
			osThreadYield();
		}
		flags = osEventFlagsWait(hopper_2_msp.Event_ID, HOPPER_FLAGS_MSK, osFlagsWaitAny, 0U);
		if (Check_CMSIS_Flags_Functions_Error_Codes(flags) == 0) {
//      if(flags&EventHopperMSP::INHIBIT_PIN_RISING){
//        DEBUG("NOISE ON LINE HOPPER_2_INHIBIT_Pin, RISING\n");
//      }
//      if(flags&EventHopperMSP::METER_PIN_RISING){
//        DEBUG("NOISE ON LINE HOPPER_2_METER_Pin, RISING\n");
//      }
//      if(flags&EventHopperMSP::CREDIT_PIN_RISING){
//        DEBUG("NOISE ON LINE HOPPER_2_CREDIT_Pin, RISING\n");
//      }
//			if (flags & EventHopperMSP::COIN_EMPTY_PIN_RISING) {
//				DEBUG("NOISE ON LINE HOPPER_2_COIN_EMPTY_Pin, RISING\n");
//			}
//      if(flags&EventHopperMSP::INHIBIT_PIN_FALLING){
//        DEBUG("NOISE ON LINE HOPPER_2_INHIBIT_Pin, FALLING\n");
//      }
//      if(flags&EventHopperMSP::METER_PIN_FALLING){
//        DEBUG("NOISE ON LINE HOPPER_2_METER_Pin, FALLING\n");
//      }
//      if(flags&EventHopperMSP::CREDIT_PIN_FALLING){
//        DEBUG("NOISE ON LINE HOPPER_2_CREDIT_Pin, FALLING\n");
//      }
//			if (flags & EventHopperMSP::COIN_EMPTY_PIN_FALLING) {
//				DEBUG("NOISE ON LINE HOPPER_2_COIN_EMPTY_Pin, FALLING\n");
//			}
//      if(flags&EventHopperMSP::INHIBIT_PIN_NOISE){
//        DEBUG("NOISE ON LINE HOPPER_2_INHIBIT_Pin, NOISE\n");
//      }
//      if(flags&EventHopperMSP::METER_PIN_NOISE){
//        DEBUG("NOISE ON LINE HOPPER_2_METER_Pin, NOISE\n");
//      }
//      if(flags&EventHopperMSP::CREDIT_PIN_NOISE){
//        DEBUG("NOISE ON LINE HOPPER_2_CREDIT_Pin, NOISE\n");
//      }
//			if (flags & EventHopperMSP::COIN_EMPTY_PIN_NOISE) {
//				DEBUG("NOISE ON LINE HOPPER_2_COIN_EMPTY_Pin, NOISE\n");
//			}
      if (flags & EventHopperMSP::GET_PINS_STATE) {
				Debug_Pins();
			}
		}
	}
}

bool HopperMSPClass::isAlarm(void) {
  return ((alarm_credit)||(alarm_inhibit)||(alarm_coint_emply));
}


void HopperMSPClass::Check_Alarm(void) {
  bool alarm = false;
  if  (inhibit_pin_state != INHIBIT_NORMAL_STATE)
  {
    osDelay(1);
    if  (inhibit_pin_state != INHIBIT_NORMAL_STATE)
    {
      alarm = true;
    }
  }
  alarm_inhibit = alarm;
  
  alarm = false;
  if  (hopper_2_msp.coin_empty_pin_state != COIN_EMPTY_NORMAL_STATE)
  {
    osDelay(1);
    if  (hopper_2_msp.coin_empty_pin_state != COIN_EMPTY_NORMAL_STATE)
    {
      alarm = true;
    }
  }
  alarm_coint_emply = alarm;
  
  alarm = false;
  if  (hopper_2_msp.credit_pin_state != CREDIT_NORMAL_STATE)
  {
    osDelay(1);
    if  (hopper_2_msp.credit_pin_state != CREDIT_NORMAL_STATE)
    {
      alarm = true;
    }
  }
  alarm_credit = alarm;
}
  
static void Debug_Pins(void) {
  DEBUG(
    "READ PIN:\n"
    "HOPPER_2_INHIBIT_Pin is %d - %s\n"
    "HOPPER_2_METER_Pin is %d - %s\n"
    "HOPPER_2_CREDIT_Pin is %d - %s\n"
    "HOPPER_2_COIN_EMPTY_Pin is %d - %s\n",
    hopper_2_msp.inhibit_pin_state,
    hopper_2_msp.inhibit_pin_state == INHIBIT_NORMAL_STATE ? "OK": "FAULT",
    hopper_2_msp.meter_pin_state,
    hopper_2_msp.meter_pin_state ? "OK": "FAULT",
    hopper_2_msp.credit_pin_state,
    hopper_2_msp.credit_pin_state ? "FAULT": "OK",
    hopper_2_msp.coin_empty_pin_state,
    hopper_2_msp.coin_empty_pin_state == COIN_EMPTY_NORMAL_STATE ? "OK": "FAULT"
  ); 
}

bool HopperMSPClass::isLineNormalState(void) {
	bool error = true;
	if (inhibit_pin_state != INHIBIT_NORMAL_STATE) {
		DEBUG("ERROR: Hopper is inhibit!!!\n");
		error = false;
	}
	if (coin_empty_pin_state != COIN_EMPTY_NORMAL_STATE) {
		DEBUG("ERROR: Coin empty!!!\n");
		error = false;
	}
  if (meter_pin_state == GPIO_PIN_RESET) {
		DEBUG("ERROR: HOPPER_1_METER_Pin line is RESET!!!\n");
		error = false;
	}
  if (credit_pin_state != CREDIT_NORMAL_STATE) {
		DEBUG("ERROR: CREDIT line is Error!!!\n");
		error = false;
	}
	return error;
}


bool HopperMSPClass::Out_Coins(int* num) {
	uint32_t flags;
	bool error = false;
  //bool error_coints_out = false;

  if(!isLineNormalState()) return true;

		
  bool skip = false;
  uint32_t flags_store = 0;
  uint32_t start_signal_tick = 0;
  uint32_t credit_signal_delay = 0;  
  uint32_t meter_signal_delay = 0;  
  uint32_t inhibit_signal_delay = 0;
	osEventFlagsClear(Event_ID, HOPPER_MSP_PINS_FLAGS_MSK);	
  
	int split_all_coints = *num;

		if(split_all_coints >= 2){
			HoppersMSPNS::MessageClass msg;
			msg.command = SPLIT_OUT_HOPPER_2;
			msg.pulses = 1;
			HoppersMSP.Messages.pushMessageIn(&msg);
			split_all_coints--;
		}

  for (int i = *num; i > 0; i--)
	{  
		if(split_all_coints > 0){
			HoppersMSPNS::MessageClass msg;
			msg.command = SPLIT_OUT_HOPPER_2;
			msg.pulses = 1;
			HoppersMSP.Messages.pushMessageIn(&msg);
			split_all_coints--;
		}
    //создаем хранилище флагов, куда будем складывать флаги. Так мы будем ждать
    //пока все события на линиях произойдут, а если нет, то будем знать какие
    //были, какие нет
    flags_store = 0;   
    start_signal_tick = 0;
    credit_signal_delay = 0;  
    meter_signal_delay = 0;   
    skip = false;
    #define SPLITOUT_SIGNAL_TIMEOUT 10000
	

    //начинаем с сигнала CREDIT
    if(!skip){
      flags = osEventFlagsWait(Event_ID, EventHopperMSP::CREDIT_PIN_RISING, osFlagsWaitAll, SPLITOUT_SIGNAL_TIMEOUT);
      if (Check_CMSIS_Flags_Functions_Error_Codes(flags) != 0) {
        skip = true;
      }else{
        start_signal_tick = HAL_GetTick();
        flags_store |= flags;
      }
    }
  
    if(!skip){
      flags = osEventFlagsWait(Event_ID, EventHopperMSP::CREDIT_PIN_FALLING, osFlagsWaitAll, SPLITOUT_SIGNAL_TIMEOUT);
      if (Check_CMSIS_Flags_Functions_Error_Codes(flags) != 0) {
          skip = true;
      }else{
        flags_store |= flags;
        credit_signal_delay = HAL_GetTick() - start_signal_tick;
      }
    }
  
  //теперь ждем сигнал METER
    if(!skip){
      flags = osEventFlagsWait(Event_ID, EventHopperMSP::METER_PIN_FALLING, osFlagsWaitAll, 500);
      if (Check_CMSIS_Flags_Functions_Error_Codes(flags) != 0) {
        skip = true;
      }else{
        start_signal_tick = HAL_GetTick();
        flags_store |= flags;
      }
    }
 

    if(!skip){
      flags = osEventFlagsWait(Event_ID, EventHopperMSP::METER_PIN_RISING, osFlagsWaitAll, 500);
      if (Check_CMSIS_Flags_Functions_Error_Codes(flags) != 0) {
        skip = true;
      }else{
        meter_signal_delay = HAL_GetTick() - start_signal_tick;
        flags_store |= flags;
      }
    }  
    
    //тут мы начинаем проверять какие сигналы получили   
    //если не получили CREDIT сигнал
    if((flags_store & (EventHopperMSP::CREDIT_PIN_FALLING | EventHopperMSP::CREDIT_PIN_RISING)) != (EventHopperMSP::CREDIT_PIN_FALLING | EventHopperMSP::CREDIT_PIN_RISING)){
      DEBUG("ERROR: Timeout CREDIT signal\n");
      error = true;
      break;  
    }else{
      DEBUG("CREDIT signal delay %d ms\n", credit_signal_delay);
    }

    //если не получили METER сигнал
    if((flags_store & (EventHopperMSP::METER_PIN_FALLING | EventHopperMSP::METER_PIN_RISING)) != (EventHopperMSP::METER_PIN_FALLING | EventHopperMSP::METER_PIN_RISING)){
      DEBUG("ERROR: Timeout METER signal\n");
      //error = TERMINAL_HOPPER_MSP_ERROR_METER_SIGNAL;
      //return error;  
    }else{
      DEBUG("METER signal delay %d ms\n", meter_signal_delay);
    }  
    
    (*num)--;
}
 	//теперь ждем сигнал INHIBIT
  if(!skip){
    flags = osEventFlagsWait(Event_ID, EventHopperMSP::INHIBIT_PIN_FALLING, osFlagsWaitAll, 5000);
    if (Check_CMSIS_Flags_Functions_Error_Codes(flags) != 0) {
      skip = true;
      DEBUG("ERROR: Timeout INHIBIT FALLING signal\n");
    }else{
      start_signal_tick = HAL_GetTick();
      flags_store |= flags;
    }
  }
 
  if(!skip){
    flags = osEventFlagsWait(Event_ID, EventHopperMSP::INHIBIT_PIN_RISING, osFlagsWaitAll, 5000);
    if (Check_CMSIS_Flags_Functions_Error_Codes(flags) != 0) {
      skip = true;
      DEBUG("ERROR: Timeout INHIBIT RISING signal\n");
    }else{
      inhibit_signal_delay = HAL_GetTick() - start_signal_tick;
      flags_store |= flags;
      DEBUG("INHIBIT signal delay %d ms\n", inhibit_signal_delay);
    }
  }  
  
  
	return error;
}


/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HopperMSPClass::EXTI_Callback()
{
	GPIO_PinState state;
  uint64_t flag;

    state = HAL_GPIO_ReadPin(HOPPER_2_INHIBIT_GPIO_Port, HOPPER_2_INHIBIT_Pin);
    if (state != hopper_2_msp.inhibit_pin_state)
    {
     if (state == GPIO_PIN_RESET) {
        osEventFlagsSet(Event_ID, EventHopperMSP::INHIBIT_PIN_FALLING);
      }
      else {
        osEventFlagsSet(Event_ID, EventHopperMSP::INHIBIT_PIN_RISING);
      }
      hopper_2_msp.inhibit_pin_state = state;
    }


		state = HAL_GPIO_ReadPin(HOPPER_2_METER_GPIO_Port, HOPPER_2_METER_Pin);
		if (state != hopper_2_msp.meter_pin_state)
		{
			if (state == GPIO_PIN_RESET) {
				osEventFlagsSet(Event_ID, EventHopperMSP::METER_PIN_FALLING);
			}
			else {
				osEventFlagsSet(Event_ID, EventHopperMSP::METER_PIN_RISING);
			}
			hopper_2_msp.meter_pin_state = state;
		}


		state = HAL_GPIO_ReadPin(HOPPER_2_CREDIT_GPIO_Port, HOPPER_2_CREDIT_Pin);
		if (state != hopper_2_msp.credit_pin_state)
		{
			if (state == GPIO_PIN_RESET) {
				osEventFlagsSet(Event_ID, EventHopperMSP::CREDIT_PIN_FALLING);
			}
			else {
				osEventFlagsSet(Event_ID, EventHopperMSP::CREDIT_PIN_RISING);
			}
			hopper_2_msp.credit_pin_state = state;
		}

		state = HAL_GPIO_ReadPin(HOPPER_2_COIN_EMPTY_GPIO_Port, HOPPER_2_COIN_EMPTY_Pin);
		if (state != hopper_2_msp.coin_empty_pin_state)
		{
			if (state == GPIO_PIN_RESET) {
				osEventFlagsSet(Event_ID, EventHopperMSP::COIN_EMPTY_PIN_FALLING);
			}
			else {
				osEventFlagsSet(Event_ID, EventHopperMSP::COIN_EMPTY_PIN_RISING);
			}
			hopper_2_msp.coin_empty_pin_state = state;
		}
}

} //namespace Hopper1MSPNS
