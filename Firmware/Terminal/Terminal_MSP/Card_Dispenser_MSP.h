/**
  ******************************************************************************
  * File Name          : Card_Dispenser_MSP.h
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_CARD_DISPENSER_MSP_H
#define __TERMINAL_CARD_DISPENSER_MSP_H
#ifdef __cplusplus
 extern "C" {
#endif
//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#define USART(num)  			Driver_USART##num

//<h>Card_Dispenser
//  <h> Interface

// <e> USART
#define CARD_DISPENSER_USART_En	1
#if (CARD_DISPENSER_USART_En	== 1)
//   <o> USART <1=>USART1 <2=>USART2 <3=>USART3 <4=>UART4 <5=>UART5 <6=>USART6 <7=>UART7
//   <8=>UART8 <9=>UART9 <10=>UART10
#define CARD_DISPENSER_DRIVER_USART	USART(1)
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

#define CARD_DISPENSER_CREDIT_RELAY_PIN_RISING		(uint64_t)(1<<0)
#define CARD_DISPENSER_CREDIT_RELAY_PIN_FALLING		(uint64_t)(1<<1)
#define CARD_DISPENSER_BILL_IN										(uint64_t)(1<<2)
#define CARD_DISPENSER_RECEIVE_PULSE							(uint64_t)(1<<3)
#define CARD_DISPENSER_TIMER_COUNTER_OVERFLOW			(uint64_t)(1<<4)
#define CARD_DISPENSER_INHIBIT_OFF					      (uint64_t)(1<<5)
#define CARD_DISPENSER_INHIBIT_ON					        (uint64_t)(1<<6)
#define CARD_DISPENSER_FLAGS_MSK (uint64_t)  (CARD_DISPENSER_CREDIT_RELAY_PIN_RISING|CARD_DISPENSER_CREDIT_RELAY_PIN_FALLING| \
                                            CARD_DISPENSER_BILL_IN|CARD_DISPENSER_RECEIVE_PULSE|CARD_DISPENSER_TIMER_COUNTER_OVERFLOW| \
                                            CARD_DISPENSER_INHIBIT_OFF|CARD_DISPENSER_INHIBIT_ON  \
                                            )


/**
  * @brief  Card_Dispenser MSP structure
  */
typedef struct __TERMINAL_HandleCardDispenserMSPTypeDef
{
  uint8_t response;

} TERMINAL_HandleCardDispenserMSPTypeDef;
/* Exported constants --------------------------------------------------------*/
 extern const osThreadAttr_t CardDispenserMSPTask_attributes;
 extern osThreadId_t CardDispenserMSP_TaskHandle;
 extern osEventFlagsId_t Card_Dispenser_MSP_Event_id;
/* Exported Macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void Card_Dispenser_MspInit(void);
void Card_Dispenser_MSP_Thread(void *argument);
void Card_Dispenser_GPIO_Callback(uint16_t GPIO_Pin);
void Card_Dispenser_MSP_TIM_Init(void);
#ifdef __cplusplus
}
#endif
#endif /*__TERMINAL_CARD_DISPENSER_MSP_H*/
