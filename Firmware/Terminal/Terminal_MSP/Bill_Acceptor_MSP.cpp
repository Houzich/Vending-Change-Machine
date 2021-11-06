/**
  ******************************************************************************
  * File Name          : Bill_Acceptor_MSP.c
  ******************************************************************************
  */
  /* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "main.h"
#include "Terminal/Terminal.h"
#include "Bill_Acceptor_MSP.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"

#ifdef TERMINAL_USE_STM
#include "cmsis_os2.h"
#elif defined(TERMINAL_USE_WINDOWS)
#include "..\Threads.h"
#include <Windows.h>
#endif /*TERMINAL_USE_STM*/

namespace BillAcceptorMSPNS
{
  
using namespace BillAcceptorNS;
  
BillAcceptorMSPClass  BillAcceptorMSP;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
//used when debugging, declared in the file Terminal.h
#ifdef DEBUG_TERMINAL_BILL_ACCEPTOR_MSP
#undef DEBUG /* DEBUG */
#undef DEBUG_PRINT /* DEBUG_PRINT */
#define DEBUG(...)			{debug_header("BILL_ACCEPTOR MSP: ", __VA_ARGS__);} while (0);
#define DEBUG_PRINT(x)	debug_print x;
#else
#define DEBUG(...)
#define DEBUG_PRINT(x)
#endif // DEBUG_TERMINAL_BILL_ACCEPTOR_MSP

#define TIM_BILL_ACCEPTOR 1000

/* definition and creation of defaultTask */
uint64_t billacceptormsp_stk[2048 / 8];
const osThreadAttr_t BillAcceptorMSPTask_attributes = {
  .name = "Bill_AcceptorMSPTask",
  .stack_mem = &billacceptormsp_stk[0],
  .stack_size = sizeof(billacceptormsp_stk),
  .priority = (osPriority_t) osPriorityAboveNormal,
};
osThreadId_t BillAcceptorMSP_TaskHandle;

/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
static void debug_pulses (int cnt);
static void Inhibit_On (void);
static void Inhibit_Off (void);


void BillAcceptorMSPClass::Bill_Acceptor_MSP_Thread (void *argument)
{
	__IO uint32_t flags;
  BillAcceptorMSP.Start = true;
	for (;;)
	{
		flags = osEventFlagsWait(BillAcceptorMSP.Event_ID, BILL_ACCEPTOR_FLAGS_MSK, osFlagsWaitAny, osWaitForever);
		Debug_Event_Flags_Error(flags);

		if(flags&BILL_ACCEPTOR_RECEIVE_PULSE){
			DEBUG("Received an impulse from bill accepter, number: %d\n", BillAcceptorMSP.Count_Pulse);
		}

		if(flags&BILL_ACCEPTOR_TIMER_COUNTER_OVERFLOW){
      int cnt = BillAcceptorMSP.Count_Pulse;
      BillAcceptorMSP.Inhibit_On();
      DEBUG("End read pulses!!!\n");
      BillAcceptorNS::MessageClass msg;
      msg.command = ACCEPTED;
      msg.count_pulse = BillAcceptorMSP.Count_Pulse;
      BillAcceptorNS::BillAcceptor.Messages.pushMessageIn(&msg);
      osThreadYield();
      debug_pulses(cnt);      
		}

		if(flags&BILL_ACCEPTOR_INHIBIT_OFF){
      BillAcceptorMSP.Inhibit_Off();
    }

    if(flags&BILL_ACCEPTOR_INHIBIT_ON){
      BillAcceptorMSP.Inhibit_On();
    }
    
    GPIO_PinState state;
    
    
    if(flags&BILL_ACCEPTOR_CREDIT_RELAY_PIN_FALLING){
      state = HAL_GPIO_ReadPin(CREDIT_RELAY_GPIO_Port, CREDIT_RELAY_Pin);
      if (state == GPIO_PIN_RESET)
      {
        BillAcceptorMSP.Receive_Pulse = true;
        BillAcceptorMSP.pulseStartValue[BillAcceptorMSP.Count_Pulse] = HAL_GetTick();
      } 
    }
    if(flags&BILL_ACCEPTOR_CREDIT_RELAY_PIN_RISING){
      state = HAL_GPIO_ReadPin(CREDIT_RELAY_GPIO_Port, CREDIT_RELAY_Pin);
      if ((state == GPIO_PIN_SET)&&(BillAcceptorMSP.Receive_Pulse))
      {
        BillAcceptorMSP.Receive_Pulse = false;
        BillAcceptorMSP.pulseEndValue[BillAcceptorMSP.Count_Pulse] = HAL_GetTick();
        int32_t duration = BillAcceptorMSP.pulseEndValue[BillAcceptorMSP.Count_Pulse] - BillAcceptorMSP.pulseStartValue[BillAcceptorMSP.Count_Pulse];
        if(duration < 40){
          DEBUG("ERROR! Pulse duration is negative: %d. It's a noise!!!\nPulse start - %d, Pulse end - %d\n", 
          BillAcceptorMSP.pulseEndValue[BillAcceptorMSP.Count_Pulse] - BillAcceptorMSP.pulseStartValue[BillAcceptorMSP.Count_Pulse], 
          BillAcceptorMSP.pulseStartValue[BillAcceptorMSP.Count_Pulse], 
          BillAcceptorMSP.pulseEndValue[BillAcceptorMSP.Count_Pulse]);
          BillAcceptorMSP.Start_Receive();
          
          //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
          //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
          //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
          //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
          
        }else{
          BillAcceptorMSP.Inhibit_On();
					DEBUG("Receive pulse %d. Start Timer.\n", BillAcceptorMSP.Count_Pulse);
					BillAcceptorMSP.Timer_Overflow_Stop();
          BillAcceptorMSP.Timer_Overflow_Start();
          BillAcceptorMSP.Count_Pulse++;
          if(BillAcceptorMSP.Count_Pulse >= MAX_RECEIVE_PULSES) BillAcceptorMSP.Count_Pulse = 0;
          osEventFlagsSet(BillAcceptorMSP.Event_ID, BILL_ACCEPTOR_RECEIVE_PULSE);
        }
      } 
    }
	}
}
/*###############################################################*/
/*###############################################################* Start_Receive -->*/
/*###############################################################*/
void BillAcceptorMSPClass::Start_Receive(){
  Timer_Overflow_Stop();
  Receive_Pulse = false;
	DEBUG("Reset Count_Pulse \n");
  Count_Pulse = 0;
}
/*###############################################################*/
/*###############################################################* Stop_Receive -->*/
/*###############################################################*/
void BillAcceptorMSPClass::Stop_Receive(){
  Timer_Overflow_Stop();
}
/*###############################################################*/
/*###############################################################* Timer_Overflow_Stop -->*/
/*###############################################################*/
void BillAcceptorMSPClass::Timer_Overflow_Stop() {
  if(Timer_Overflow != NULL){
		osTimerStop(Timer_Overflow);
		osTimerDelete(Timer_Overflow);
	}
}

/*###############################################################*/
/*###############################################################* Timer_Overflow_Start -->*/
/*###############################################################*/
void BillAcceptorMSPClass::Timer_Overflow_Start() {
	Timer_Overflow = osTimerNew(Timer_Overflow_Callback, osTimerOnce, &BillAcceptorMSP, NULL);
	osTimerStart(Timer_Overflow, TIM_BILL_ACCEPTOR);
}
/*###############################################################*/
/*###############################################################* Timer_Overflow_Start -->*/
/*###############################################################*/
void BillAcceptorMSPClass::Timer_Overflow_Callback(void* argument)
{
	DEBUG("Timer_Overflow_Callback. Set Flag BILL_ACCEPTOR_TIMER_COUNTER_OVERFLOW \n");
 osEventFlagsSet(BillAcceptorMSP.Event_ID, BILL_ACCEPTOR_TIMER_COUNTER_OVERFLOW); 
}
/*###############################################################*/
/*###############################################################* Inhibit_On -->*/
/*###############################################################*/
void BillAcceptorMSPClass::Inhibit_Off (void)
{
  Start_Receive();
  HAL_GPIO_WritePin(INHIBIT_GPIO_Port, INHIBIT_Pin, GPIO_PIN_RESET);
}
/*###############################################################*/
/*###############################################################* Inhibit_Off -->*/
/*###############################################################*/
void BillAcceptorMSPClass::Inhibit_On (void)
{
  Stop_Receive();
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	HAL_GPIO_DeInit(INHIBIT_GPIO_Port, INHIBIT_Pin);
	osDelay(1);
	#if (INHIBIT_Pin_En)
	HAL_GPIO_WritePin(INHIBIT_GPIO_Port,INHIBIT_Pin, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = INHIBIT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(INHIBIT_GPIO_Port, &GPIO_InitStruct);
#endif
  HAL_GPIO_WritePin(INHIBIT_GPIO_Port, INHIBIT_Pin, GPIO_PIN_SET);
}

static void debug_pulses (int cnt){
#ifdef DEBUG_TERMINAL_BILL_ACCEPTOR_MSP
  DEBUG("Received an impulses from bill accepter, quantity: %d\n", cnt);
  for (int i = 0; i < cnt; i++){
    int32_t duration = BillAcceptorMSP.pulseEndValue[i] - BillAcceptorMSP.pulseStartValue[i];
    DEBUG_PRINT(("Impulse %d, duration %d ms\n", i, duration));
  }
#endif
}

void BillAcceptorMSPClass::Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  Event_ID = osEventFlagsNew(NULL);
  if (Event_ID == NULL) {
    DEBUG("Event Flags object not created, handle failure!!!\n"); // Event Flags object not created, handle failure
		for (;;);
	}
  
#if (CREDIT_RELAY_Pin_En)
	GPIO_InitStruct.Pin = CREDIT_RELAY_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(CREDIT_RELAY_GPIO_Port, &GPIO_InitStruct);
#endif

#if (INHIBIT_Pin_En)
	HAL_GPIO_WritePin(INHIBIT_GPIO_Port,INHIBIT_Pin, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = INHIBIT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(INHIBIT_GPIO_Port, &GPIO_InitStruct);
#endif
  
  credit_relay_pin_state = HAL_GPIO_ReadPin(CREDIT_RELAY_GPIO_Port, CREDIT_RELAY_Pin);
}

void BillAcceptorMSPClass::EXTI_Callback()
{
  GPIO_PinState state;
  uint64_t flag;

    state = HAL_GPIO_ReadPin(CREDIT_RELAY_GPIO_Port, CREDIT_RELAY_Pin);
    if (state != credit_relay_pin_state)
    {
     if (state == GPIO_PIN_RESET) {
        osEventFlagsSet(Event_ID, BILL_ACCEPTOR_CREDIT_RELAY_PIN_FALLING);
      }
      else {
        osEventFlagsSet(Event_ID, BILL_ACCEPTOR_CREDIT_RELAY_PIN_RISING);
      }
      credit_relay_pin_state = state;
    }  
}
} //namespace BillAcceptorMSPNS

