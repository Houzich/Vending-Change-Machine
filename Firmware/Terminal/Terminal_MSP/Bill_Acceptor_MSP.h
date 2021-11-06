/**
  ******************************************************************************
  * File Name          : Bill_Acceptor_MSP.h
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_BILL_ACCEPTOR_MSP_H
#define __TERMINAL_BILL_ACCEPTOR_MSP_H
//BILL_ACCEPTOR
//INHIBIT+ - PA4
//CREDIT_RELAY_NO - PA3
//INHIBIT_COM - GND
//CREDIT_RELAY_COM - GND 
	 
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
#else
#define INHIBIT_Pin_Num 0xFF
#endif
// </e>

// <e> CREDIT_RELAY Pin
#define CREDIT_RELAY_Pin_En	1
#if (CREDIT_RELAY_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define CREDIT_RELAY_Pin_Num	3
#define CREDIT_RELAY_Pin	GPIO_PIN(CREDIT_RELAY_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define CREDIT_RELAY_GPIO_Port GPIO_PORT(0)
#else
#define CREDIT_RELAY_Pin_Num 0xFF
#endif
// </e>

//	</h>
//</h>


/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include "cmsis_os2.h"


#define BILL_ACCEPTOR_CREDIT_RELAY_PIN_RISING			(uint64_t)(1<<0)
#define BILL_ACCEPTOR_CREDIT_RELAY_PIN_FALLING		(uint64_t)(1<<1)
#define BILL_ACCEPTOR_BILL_IN											(uint64_t)(1<<2)
#define BILL_ACCEPTOR_RECEIVE_PULSE								(uint64_t)(1<<3)
#define BILL_ACCEPTOR_TIMER_COUNTER_OVERFLOW			(uint64_t)(1<<4)
#define BILL_ACCEPTOR_INHIBIT_OFF					        (uint64_t)(1<<5)
#define BILL_ACCEPTOR_INHIBIT_ON					        (uint64_t)(1<<6)
#define BILL_ACCEPTOR_FLAGS_MSK (uint64_t)  (BILL_ACCEPTOR_CREDIT_RELAY_PIN_RISING|BILL_ACCEPTOR_CREDIT_RELAY_PIN_FALLING| \
                                            BILL_ACCEPTOR_BILL_IN|BILL_ACCEPTOR_RECEIVE_PULSE|BILL_ACCEPTOR_TIMER_COUNTER_OVERFLOW| \
                                            BILL_ACCEPTOR_INHIBIT_OFF|BILL_ACCEPTOR_INHIBIT_ON  \
                                            )
#define MAX_RECEIVE_PULSES	100
namespace BillAcceptorMSPNS
{
  class BillAcceptorMSPClass
  {
      public:
        osEventFlagsId_t Event_ID;
        GPIO_PinState	credit_relay_pin_state;
        bool	Start;
        volatile int Count_Pulse;
        volatile bool	Receive_Pulse;
        volatile uint32_t pulseStartValue[MAX_RECEIVE_PULSES];
        volatile uint32_t pulseEndValue[MAX_RECEIVE_PULSES];
      			//timers
			osTimerId_t Timer_Overflow;
      public:
        BillAcceptorMSPClass(){
          Start = false;
          Count_Pulse = 0;
          Receive_Pulse = false;
          for(int i = 0; i < MAX_RECEIVE_PULSES; i++)
          {
            pulseStartValue[i] = 0;
            pulseEndValue[i] = 0;
          }

        };
        
        void Init();
        static void Bill_Acceptor_MSP_Thread(void* arg);
        static void Timer_Overflow_Callback(void* argument);
        void Inhibit_On (void);
        void Inhibit_Off (void);
        void Start_Receive();
        void Stop_Receive();
        void Timer_Overflow_Stop();
        void Timer_Overflow_Start();
        void EXTI_Callback();
  };

/* Exported constants --------------------------------------------------------*/
 extern BillAcceptorMSPClass  BillAcceptorMSP;
 extern const osThreadAttr_t BillAcceptorMSPTask_attributes;
 extern osThreadId_t BillAcceptorMSP_TaskHandle;
/* Exported Macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
}

#endif /*__TERMINAL_BILL_ACCEPTOR_MSP_H*/
