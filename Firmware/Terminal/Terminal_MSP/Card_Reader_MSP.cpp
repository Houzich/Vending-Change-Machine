/**
  ******************************************************************************
  * File Name          : Card_Reader_MSP.c
  ******************************************************************************
  */
  /* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "main.h"
#include "Terminal/Terminal.h"
#include "Card_Reader_MSP.h"
#include "Terminal_MSP.h"
#include "stm32f4xx_hal.h"


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
#ifdef DEBUG_TERMINAL_CARD_READER_MSP
#undef DEBUG /* DEBUG */
#undef DEBUG_PRINT /* DEBUG_PRINT */
#define DEBUG(...)			{debug_header("CARD_READER MSP: ", __VA_ARGS__);} while (0)
#define DEBUG_PRINT(...)	{debug_print(__VA_ARGS__);} while (0)
#else
#define DEBUG(...)
#define DEBUG_PRINT(x)
#endif // DEBUG_TERMINAL_CARD_READER_MSP

/* Private variables ---------------------------------------------------------*/
const osThreadAttr_t CardReaderMSPTask_attributes = {
  .name = "CardReaderMSPTask",
  .stack_size = 1024,
  .priority = (osPriority_t)osPriorityAboveNormal,
};
osThreadId_t CardReaderMSP_TaskHandle;

TERMINAL_HandleCardReaderMSPTypeDef cardreader_msp;
osEventFlagsId_t Card_Reader_MSP_Event_ID;                        // event flags id
HopperMsgQueueTypeDef csrddispensermsg;

static uint8_t CardReader[20];


ARM_DRIVER_USART * USARTCardReaderdrv;
/* USART Driver */
extern ARM_DRIVER_USART CARD_READER_DRIVER_USART;
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
void Debug_USART_Events(uint32_t event)
{
  printf("USART Events:\n");
  if (event & ARM_USART_EVENT_SEND_COMPLETE)       printf("Send completed; however USART may still transmit data\n");
  if (event & ARM_USART_EVENT_RECEIVE_COMPLETE)    printf("Receive completed\n");
  if (event & ARM_USART_EVENT_TRANSFER_COMPLETE)   printf("Transfer completed\n");
  if (event & ARM_USART_EVENT_TX_COMPLETE)         printf("Transmit completed (optional)\n");
  if (event & ARM_USART_EVENT_TX_UNDERFLOW)        printf("Transmit data not available (Synchronous Slave)\n");
  if (event & ARM_USART_EVENT_RX_OVERFLOW)         printf("Receive data overflow\n");
  if (event & ARM_USART_EVENT_RX_TIMEOUT)          printf("Receive character timeout (optional)\n");
  if (event & ARM_USART_EVENT_RX_BREAK)            printf("Break detected on receive\n");
  if (event & ARM_USART_EVENT_RX_FRAMING_ERROR)    printf("Framing error detected on receive\n");
  if (event & ARM_USART_EVENT_RX_PARITY_ERROR)     printf("Parity error detected on receive\n");
  if (event & ARM_USART_EVENT_CTS)                 printf("CTS state changed (optional)\n");
  if (event & ARM_USART_EVENT_DSR)                 printf("DSR state changed (optional)\n");
  if (event & ARM_USART_EVENT_DCD)                 printf("DCD state changed (optional)\n");
  if (event & ARM_USART_EVENT_RI)                  printf("RI  state changed (optional)\n");
}
static void USART_Card_Reader_Callback(uint32_t event)
{
  uint32_t mask;
  mask = FlagCardReaderMSP::USART_MASK;
  
  Debug_USART_Events(event);
  
  if (event & mask) {
    /* Success: Wakeup Thread */
    osThreadFlagsSet(CardDispanser_TaskHandle, event & mask);
  }
}


void Card_Reader_MspInit(void)
{
  
#if (CARD_READER_USART_En != 0)
  USARTCardReaderdrv = &CARD_READER_DRIVER_USART;
  /*Initialize the USART driver */
  USARTCardReaderdrv->Initialize(USART_Card_Reader_Callback);
  /*Power up the USART peripheral */
  USARTCardReaderdrv->PowerControl(ARM_POWER_FULL);
  /*Configure the USART to 115200 Bits/sec */
  USARTCardReaderdrv->Control(ARM_USART_MODE_ASYNCHRONOUS |
                    ARM_USART_DATA_BITS_8 |
                    ARM_USART_PARITY_NONE |
                    ARM_USART_STOP_BITS_1 |
                    ARM_USART_FLOW_CONTROL_NONE, 115200);
   
  /* Enable Receiver and Transmitter lines */
  USARTCardReaderdrv->Control (ARM_USART_CONTROL_TX, 1);
  USARTCardReaderdrv->Control (ARM_USART_CONTROL_RX, 1);
#endif //(CARD_READER_DRIVER_USART != NULL)
}

void Card_Reader_MSP_Thread(void* argument)
{
	uint32_t flags;
	Card_Reader_MSP_Event_ID = osEventFlagsNew(NULL);
	if (Card_Reader_MSP_Event_ID == NULL) {
		DEBUG("Event Flags object not created, handle failure!!!\n"); // Event Flags object not created, handle failure
		for (;;);
	}
  
	Card_Reader_MspInit();
  uint8_t *pbuff = CardReader;
  USARTCardReaderdrv->Receive(pbuff, 1);          /* Get byte from UART */
	for (;;)
	{
		osDelay(1);
		osStatus_t status;
    flags = osThreadFlagsWait(FlagCardReaderMSP::USART_MASK, osFlagsWaitAny, 300);
		if (Check_CMSIS_Flags_Functions_Error_Codes(flags) != 0) {
      //DEBUG("ERROR THREAD FLAGS!!!\n");
      continue;
    }
    if (flags & ARM_USART_EVENT_RECEIVE_COMPLETE) {
      if (pbuff == &CardReader[sizeof(CardReader) - 1] ) pbuff = CardReader;
       USARTCardReaderdrv->Receive(pbuff++, 1);          /* Get byte from UART */
    } else if (flags & ARM_USART_EVENT_RX_TIMEOUT) {
      int size = USARTCardReaderdrv->GetRxCount();
      static uint8_t id[20];
      
      memset(id, 0, sizeof(id));
      if(size >= sizeof(id)){
        DEBUG("ERROR: Receive long message!!!\n");
      } else {
        memcpy(id, CardReader, size);
        DEBUG("Receive id card: %s\n", id);
      }
      pbuff = CardReader;
      
    }
    else{
      DEBUG("UNKNOWN THREAD FLAGS!!\n");
    }
      

	}
}