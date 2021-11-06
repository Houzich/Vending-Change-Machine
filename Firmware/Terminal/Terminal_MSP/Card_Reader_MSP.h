/**
  ******************************************************************************
  * File Name          : Card_Reader_MSP.h
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_CARD_READER_MSP_H
#define __TERMINAL_CARD_READER_MSP_H
#ifdef __cplusplus
 extern "C" {
#endif
//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#define USART(num)  			Driver_USART##num

//<h>Card_Reader
//  <h> Interface

// <e> USART
#define CARD_READER_USART_En	0
#if (CARD_READER_USART_En	== 1)
//   <o> USART <1=>USART1 <2=>USART2 <3=>USART3 <4=>UART4 <5=>UART5 <6=>USART6 <7=>UART7
//   <8=>UART8 <9=>UART9 <10=>UART10
#define CARD_READER_DRIVER_USART	USART(1)
#endif
// </e>

//	</h>
//</h>

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include "cmsis_os2.h"
#include "Terminal/Terminal.h"
#include "Driver_USART.h"

enum FlagCardReaderMSP{
  
  
  USART_MASK = (ARM_USART_EVENT_RECEIVE_COMPLETE  |
         ARM_USART_EVENT_TRANSFER_COMPLETE |
         ARM_USART_EVENT_RX_TIMEOUT        |
         ARM_USART_EVENT_RX_OVERFLOW       |
         ARM_USART_EVENT_TX_UNDERFLOW      |
         ARM_USART_EVENT_SEND_COMPLETE     |
         ARM_USART_EVENT_TX_COMPLETE),
};

/**
  * @brief  Card_Reader MSP structure
  */
typedef struct __TERMINAL_HandleCardReaderMSPTypeDef
{
  uint8_t response;

} TERMINAL_HandleCardReaderMSPTypeDef;
/* Exported constants --------------------------------------------------------*/
 extern const osThreadAttr_t CardReaderMSPTask_attributes;
 extern osThreadId_t CardReaderMSP_TaskHandle;
 extern TERMINAL_HandleCardReaderMSPTypeDef cardreader_msp;
 extern osEventFlagsId_t Card_Reader_MSP_Event_id;                        // event flags id
/* Exported Macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void Card_Reader_MspInit(void);
void Card_Reader_MSP_Thread(void *argument);
void Card_Reader_GPIO_Callback(uint16_t GPIO_Pin);
void Card_Reader_MSP_TIM_Init(void);
#ifdef __cplusplus
}
#endif
#endif /*__TERMINAL_CARD_READER_MSP_H*/
