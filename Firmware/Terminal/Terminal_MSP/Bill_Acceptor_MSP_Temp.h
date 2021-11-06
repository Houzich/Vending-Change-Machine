/**
  ******************************************************************************
  * File Name          : Bill_Acceptor_MSP.h
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_BILL_ACCEPTOR_MSP_H
#define __TERMINAL_BILL_ACCEPTOR_MSP_H
#ifdef __cplusplus
 extern "C" {
//BILL_ACCEPTOR
//INHIBIT+ - PA4
//CREDIT_RELAY_NO - PA5
//INHIBIT_COM - GND
//CREDIT_RELAY_COM - GND 
	 
#endif
//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#define GPIO_PORT0      GPIOA
#define GPIO_PORT1      GPIOB
#define GPIO_PORT2      GPIOC
#define GPIO_PORT3      GPIOD
#define GPIO_PORT4      GPIOE
#define GPIO_PORT5      GPIOF
#define GPIO_PORT6      GPIOG
#define GPIO_PORT7      GPIOH
#define GPIO_PORT8      GPIOI
#define GPIO_PORT9      GPIOJ
#define GPIO_PORT10     GPIOK

#define GPIO_PORT(num)  			GPIO_PORT##num
#define GPIO_PIN(num)  				(uint16_t)(1 << num)
	 
// <h>Bill_Acceptor


//<h> Pulse/ Bill_Acceptor Interface

// <e> INHIBIT Pin
#define INHIBIT_Pin_En	1
#if (INHIBIT_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define INHIBIT_Pin_Num	4
#define INHIBIT_Pin	GPIO_PIN(INHIBIT_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define INHIBIT_GPIO_Port GPIO_PORT(0)
//   <o.0> Interrupt
//     <i> Use Interrupt
#define INHIBIT_IRQ_En	0
#if (INHIBIT_IRQ_En == 1)
#if (INHIBIT_Pin_Num == 0)	
#define INHIBIT_IRQ EXTI0_IRQn
#elif (INHIBIT_Pin_Num == 1)
#define INHIBIT_IRQ EXTI1_IRQn
#elif (INHIBIT_Pin_Num == 2)
#define INHIBIT_IRQ EXTI2_IRQn
#elif (INHIBIT_Pin_Num == 3)
#define INHIBIT_IRQ EXTI3_IRQn
#elif (INHIBIT_Pin_Num == 4)
#define INHIBIT_IRQ EXTI4_IRQn
#elif (INHIBIT_Pin_Num > 4)&&(INHIBIT_Pin_Num <= 9)
#define INHIBIT_IRQ EXTI9_5_IRQn
#elif (INHIBIT_Pin_Num >= 10)
#define INHIBIT_IRQ EXTI15_10_IRQn
#endif	
#endif
#else
#define INHIBIT_Pin_Num 0xFF
#endif
// </e>

// <e> CREDIT_RELAY Pin
#define CREDIT_RELAY_Pin_En	1
#if (CREDIT_RELAY_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define CREDIT_RELAY_Pin_Num	11
#define CREDIT_RELAY_Pin	GPIO_PIN(CREDIT_RELAY_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define CREDIT_RELAY_GPIO_Port GPIO_PORT(4)
//   <o.0> Interrupt
//     <i> Use Interrupt
#define CREDIT_RELAY_IRQ_En	1
#if (CREDIT_RELAY_IRQ_En == 1)
#if (CREDIT_RELAY_Pin_Num == 0)	
#define CREDIT_RELAY_IRQ EXTI0_IRQn
#elif (CREDIT_RELAY_Pin_Num == 1)
#define CREDIT_RELAY_IRQ EXTI1_IRQn
#elif (CREDIT_RELAY_Pin_Num == 2)
#define CREDIT_RELAY_IRQ EXTI2_IRQn
#elif (CREDIT_RELAY_Pin_Num == 3)
#define CREDIT_RELAY_IRQ EXTI3_IRQn
#elif (CREDIT_RELAY_Pin_Num == 4)
#define CREDIT_RELAY_IRQ EXTI4_IRQn
#elif (CREDIT_RELAY_Pin_Num >= 5)&&(CREDIT_RELAY_Pin_Num <= 9)
#define CREDIT_RELAY_IRQ EXTI9_5_IRQn
#elif (CREDIT_RELAY_Pin_Num >= 10)
#define CREDIT_RELAY_IRQ EXTI15_10_IRQn
#endif	
#endif
#else
#define CREDIT_RELAY_Pin_Num 0xFF
#endif
// </e>

//	</h>
//</h>



/* Definition for TIMx clock resources */
#define TIM_CREDIT_RELAY     											 TIM1
#define TIM_CREDIT_RELAY_CLK_ENABLE()              __HAL_RCC_TIM1_CLK_ENABLE()

/* Definition for TIMx Pins */
#define GPIO_AF_TIM_CREDIT_RELAY                   GPIO_AF1_TIM1

/* Definition for TIMx's NVIC */
#define TIM_CREDIT_RELAY_CC_IRQn                      TIM1_CC_IRQn
#define TIM_CREDIT_RELAY_CC_IRQHandler                TIM1_CC_IRQHandler

#define TIM_CREDIT_RELAY_OVERLOAD_IRQn                TIM1_UP_TIM10_IRQn
#define TIM_CREDIT_RELAY_OVERLOAD_IRQHandler          TIM1_UP_TIM10_IRQHandler

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include "cmsis_os2.h"
#include "Terminal/Terminal.h"

#define BILL_ACCEPTOR_INHIBIT_OFF					(uint64_t)(1<<5)
#define BILL_ACCEPTOR_INHIBIT_ON					(uint64_t)(1<<6)

/**
  * @brief  Bill_Acceptor MSP structure
  */
typedef struct __TERMINAL_HandleBill_AcceptorMSPTypeDef
{

	GPIO_PinState	credit_relay_pin;
	TERMINAL_EXTIStateTypeDef	credit_relay_pin_exti;

} TERMINAL_HandleBill_AcceptorMSPTypeDef;
/* Exported constants --------------------------------------------------------*/
 extern const osThreadAttr_t BillAcceptorMSPTask_attributes;
 extern osThreadId_t BillAcceptorMSP_TaskHandle;
 extern osEventFlagsId_t Bill_Acceptor_MSP_Event_id;
/* Exported Macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void Bill_Acceptor_MspInit(void);
void Bill_Acceptor_MSP_Thread(void *argument);
void Bill_Acceptor_GPIO_Callback(uint16_t GPIO_Pin);
void Bill_Acceptor_MSP_TIM_Init(void);
#ifdef __cplusplus
}
#endif
#endif /*__TERMINAL_BILL_ACCEPTOR_MSP_H*/
