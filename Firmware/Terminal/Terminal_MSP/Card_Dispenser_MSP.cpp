/**
  ******************************************************************************
  * File Name          : Card_Dispenser_MSP.c
  ******************************************************************************
  */
  /* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "main.h"
#include "Terminal/Terminal.h"
#include "Card_Dispenser_MSP.h"
#include "Terminal_MSP.h"
#include "stm32f4xx_hal.h"
#include "Driver_USART.h"

#ifdef TERMINAL_USE_STM
#include "cmsis_os2.h"
#elif defined(TERMINAL_USE_WINDOWS)
#include "..\Threads.h"
#include <Windows.h>
#endif /*TERMINAL_USE_STM*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
//used when debugging, declared in the file Terminal.h
#ifdef DEBUG_TERMINAL_CARD_DISPENSER_MSP
#undef DEBUG /* DEBUG */
#undef DEBUG_PRINT /* DEBUG_PRINT */
#define DEBUG(...)			{debug_header("CARD_DISPENSER MSP: ", __VA_ARGS__);} while (0)
#define DEBUG_PRINT(x)	debug_print x;
#else
#define DEBUG(...)
#define DEBUG_PRINT(x)
#endif // DEBUG_TERMINAL_CARD_DISPENSER_MSP

/* Private variables ---------------------------------------------------------*/
TERMINAL_HandleCardDispenserMSPTypeDef carddispanser;
osEventFlagsId_t Card_Dispenser_MSP_Event_id;                        // event flags id
//CardDispenserMsgQueueTypeDef csrddispensermsg;

static ARM_DRIVER_USART * USARTdrv;
/* USART Driver */
extern ARM_DRIVER_USART CARD_DISPENSER_DRIVER_USART;
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
static void debug_pulses (int cnt);
/*###############################################################*/
/*###############################################################* Delay -->*/
/*###############################################################*/
static void Delay(uint32_t ms)
{
#ifdef TERMINAL_USE_STM
	osDelay(ms);
#elif defined(TERMINAL_USE_HAL)
	HAL_Delay(ms);
#elif defined(TERMINAL_USE_WINDOWS)
	//std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	Sleep(ms);
#endif /*TERMINAL_USE_STM*/
}



static void debug_pulses (int cnt){
#ifdef DEBUG_TERMINAL_CARD_DISPENSER_MSP
  DEBUG("Received an impulses from bill accepter, quantity: %d\n", cnt);
  for (int i = 0; i < cnt; i++){
    int32_t duration = pulseEndValue[i] - pulseStartValue[i];
    duration = (duration * TIM_CARD_DISPENSER_SEC_PERIOD * 1000)/TIM_CARD_DISPENSER;
    DEBUG_PRINT(("Impulse %d, duration %d ms\n", i, duration));
  }
#endif
}

static void USART_Display_Callback(uint32_t event)
{
  uint32_t mask;
  mask = ARM_USART_EVENT_RECEIVE_COMPLETE  |
         ARM_USART_EVENT_TRANSFER_COMPLETE |
         ARM_USART_EVENT_RX_TIMEOUT        |
         ARM_USART_EVENT_RX_OVERFLOW       |
         ARM_USART_EVENT_TX_UNDERFLOW      |
         ARM_USART_EVENT_SEND_COMPLETE     |
         ARM_USART_EVENT_TX_COMPLETE       ;
  if (event & mask) {
    /* Success: Wakeup Thread */
    //osThreadFlagsSet(CardDispanser_TaskHandle, 0x0001U);
  }
  if (event & ARM_USART_EVENT_RECEIVE_COMPLETE) {
    osThreadFlagsSet(CardDispanser_TaskHandle, ARM_USART_EVENT_RECEIVE_COMPLETE);
  }
  if (event & ARM_USART_EVENT_TRANSFER_COMPLETE) {
    osThreadFlagsSet(CardDispanser_TaskHandle, ARM_USART_EVENT_TRANSFER_COMPLETE);
  }
  if (event & ARM_USART_EVENT_RX_TIMEOUT) {
    osThreadFlagsSet(CardDispanser_TaskHandle, ARM_USART_EVENT_RX_TIMEOUT);  /* Error: Call debugger or replace with custom error handling */
  }
  if (event & (ARM_USART_EVENT_RX_OVERFLOW | ARM_USART_EVENT_TX_UNDERFLOW)) {
    osThreadFlagsSet(CardDispanser_TaskHandle, ARM_USART_EVENT_RX_OVERFLOW | ARM_USART_EVENT_TX_UNDERFLOW);  /* Error: Call debugger or replace with custom error handling */
  }
}


void Card_Dispenser_MspInit(void)
{
  
#if (CARD_DISPENSER_USART_En != 0)
  USARTdrv = &CARD_DISPENSER_DRIVER_USART;
  /*Initialize the USART driver */
  USARTdrv->Initialize(USART_Display_Callback);
  /*Power up the USART peripheral */
  USARTdrv->PowerControl(ARM_POWER_FULL);
  /*Configure the USART to 115200 Bits/sec */
  USARTdrv->Control(ARM_USART_MODE_ASYNCHRONOUS |
                    ARM_USART_DATA_BITS_8 |
                    ARM_USART_PARITY_EVEN |
                    ARM_USART_STOP_BITS_1 |
                    ARM_USART_FLOW_CONTROL_NONE, 115200);
   
  /* Enable Receiver and Transmitter lines */
  USARTdrv->Control (ARM_USART_CONTROL_TX, 1);
  USARTdrv->Control (ARM_USART_CONTROL_RX, 1);
#endif //(CARD_DISPENSER_DRIVER_USART != NULL)
}

