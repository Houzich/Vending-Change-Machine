/**
  ******************************************************************************
  * File Name          : Hopper_1_MSP.h
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_HOPPER_1_MSP_H
#define __TERMINAL_HOPPER_1_MSP_H
//HOPPER
//CREDIT_NO - B7	 
//METER_NO - E1
//INHIBIT_NO - E4
//PAYONT_IN - E6
//COIN-EMPTY_O -C0
//CREDIT_COM - GND
//INHIBIT_COM - GND
//METER_COM - GND

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
	 
// <h>Hopper ICT
//<e> Hopper Interface
#define HOPPER_1_HOPPER_INTERFACE_En	1
#if (HOPPER_1_HOPPER_INTERFACE_En	== 1)
// <e> INHIBIT Pin
#define HOPPER_1_INHIBIT_Pin_En	1
#if (HOPPER_1_INHIBIT_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define HOPPER_1_INHIBIT_Pin_Num	4
#define HOPPER_1_INHIBIT_Pin	GPIO_PIN(HOPPER_1_INHIBIT_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define HOPPER_1_INHIBIT_GPIO_Port GPIO_PORT(4)
#else
#define HOPPER_1_INHIBIT_Pin 0xFFFF
#define HOPPER_1_INHIBIT_Pin_Num 0xFF
#endif //(HOPPER_1_INHIBIT_Pin_En	== 1)
// </e>

// <e> METER Pin
#define HOPPER_1_METER_Pin_En	1
#if (HOPPER_1_METER_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define HOPPER_1_METER_Pin_Num	1
#define HOPPER_1_METER_Pin	GPIO_PIN(HOPPER_1_METER_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define HOPPER_1_METER_GPIO_Port GPIO_PORT(4)
#else
#define HOPPER_1_METER_Pin 0xFFFF
#define HOPPER_1_METER_Pin_Num 0xFF
#endif //(HOPPER_1_METER_Pin_En	== 1)
// </e>

// <e> CREDIT Pin
#define HOPPER_1_CREDIT_Pin_En	1
#if (HOPPER_1_CREDIT_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define HOPPER_1_CREDIT_Pin_Num	7
#define HOPPER_1_CREDIT_Pin	GPIO_PIN(HOPPER_1_CREDIT_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define HOPPER_1_CREDIT_GPIO_Port GPIO_PORT(1)
#else
#define HOPPER_1_CREDIT_Pin 0xFFFF
#define HOPPER_1_CREDIT_Pin_Num 0xFF
#endif //(HOPPER_1_CREDIT_Pin_En	== 1)
// </e>

// <e> COIN_EMPTY Pin
#define HOPPER_1_COIN_EMPTY_Pin_En	1
#if (HOPPER_1_COIN_EMPTY_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define HOPPER_1_COIN_EMPTY_Pin_Num	6
#define HOPPER_1_COIN_EMPTY_Pin	GPIO_PIN(HOPPER_1_COIN_EMPTY_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define HOPPER_1_COIN_EMPTY_GPIO_Port GPIO_PORT(4)
#else
#define HOPPER_1_COIN_EMPTY_Pin 0xFFFF
#define HOPPER_1_COIN_EMPTY_Pin_Num 0xFF
#endif //(HOPPER_1_COIN_EMPTY_Pin_En	== 1)
// </e>

// <e> PAYOUT Pin
#define HOPPER_1_PAYOUT_Pin_En	1
#if (HOPPER_1_PAYOUT_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define HOPPER_1_PAYOUT_Pin_Num	0
#define HOPPER_1_PAYOUT_Pin	GPIO_PIN(HOPPER_1_PAYOUT_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define HOPPER_1_PAYOUT_GPIO_Port GPIO_PORT(2)

#else
#define HOPPER_1_PAYOUT_Pin 0xFFFF
#define HOPPER_1_PAYOUT_Pin_Num 0xFF
#endif //(HOPPER_1_PAYOUT_Pin_En	== 1)
// </e>
#else
  #define HOPPER_1_INHIBIT_Pin 0xFFFF
  #define HOPPER_1_INHIBIT_Pin_Num 0xFF
  
  #define HOPPER_1_METER_Pin 0xFFFF
  #define HOPPER_1_METER_Pin_Num 0xFF
  
  #define HOPPER_1_CREDIT_Pin 0xFFFF
  #define HOPPER_1_CREDIT_Pin_Num 0xFF
  
  #define HOPPER_1_COIN_EMPTY_Pin 0xFFFF
  #define HOPPER_1_COIN_EMPTY_Pin_Num 0xFF
  
  #define HOPPER_1_PAYOUT_Pin 0xFFFF
  #define HOPPER_1_PAYOUT_Pin_Num 0xFF
#endif //HOPPER_1_HOPPER_INTERFACE_En
//	</e>
//</h>


/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include "cmsis_os2.h"
#include "Terminal/Tamplates.h"

namespace Hopper1MSPNS
{
/**
  * @brief  Hopper MSP structure
  */
  
   typedef enum {
      READY = 0x00,
      SPIT_OUT = 0x01,
      SPIT_OUT_OK = 0x02,
      SPIT_OUT_ERROR = 0x03,
  } COMMAND;

  struct MessageClass
  {
      COMMAND command;
      uint32_t coins;
  }; 
  
class HopperMSPClass
{
  	public:
      GPIO_PinState	inhibit_pin_state;
      GPIO_PinState	meter_pin_state;
      GPIO_PinState	credit_pin_state;
      GPIO_PinState	coin_empty_pin_state;
      osEventFlagsId_t Event_ID;                        // event flags id
    
      bool	alarm_inhibit = false; //если сработал сенсор
      bool	alarm_coint_emply = false; //если закончились монеты физически
      bool	alarm_credit = false; //если 
      QueueMessageClass< MessageClass, 10 > Messages;
      bool	Start = false;
    public:
      HopperMSPClass();
      void Init();
      void GPIO_Init(void);
      static void Hopper_1_MSP_Thread(void* arg);
      bool Out_Coins (int *num);
      void PAYOUT_Pin_Set(void);
      void PAYOUT_Pin_Reset(void);    
      void EXTI_Callback(); 
      void Check_Alarm(void);    
      bool isLineNormalState(void);
      bool isAlarm();
};
/* Exported constants --------------------------------------------------------*/
 extern const osThreadAttr_t Hopper1MSPTask_attributes;
 extern osThreadId_t Hopper1MSP_TaskHandle;
 extern HopperMSPClass hopper_1_msp;
/* Exported Macros -----------------------------------------------------------*/



} //namespace Hopper1MSPNS
/* Exported functions --------------------------------------------------------*/



#endif /*__TERMINAL_HOPPER_1_MSP_H*/
