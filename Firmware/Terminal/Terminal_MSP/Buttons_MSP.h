/**
  ******************************************************************************
  * File Name          : Buttons_MSP.h
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_BUTTONS_MSP_H
#define __TERMINAL_BUTTONS_MSP_H
//BUTTONS

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
	 
// <e> BUTTON UP
#define BUTTON_UP_Pin_En	0
#if (BUTTON_UP_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define BUTTON_UP_Pin_Num	8
#define BUTTON_UP_Pin	GPIO_PIN(BUTTON_UP_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define BUTTON_UP_Port GPIO_PORT(0)
//   <o.0> Interrupt
//     <i> Use Interrupt
#define BUTTON_UP_IRQ_En	1
#if (BUTTON_UP_IRQ_En == 1)
  #if (BUTTON_UP_Pin_Num == 0)	
  #define BUTTON_UP_IRQ EXTI0_IRQn
  #elif (BUTTON_UP_Pin_Num == 1)
  #define BUTTON_UP_IRQ EXTI1_IRQn
  #elif (BUTTON_UP_Pin_Num == 2)
  #define BUTTON_UP_IRQ EXTI2_IRQn
  #elif (BUTTON_UP_Pin_Num == 3)
  #define BUTTON_UP_IRQ EXTI3_IRQn
  #elif (BUTTON_UP_Pin_Num == 4)
  #define BUTTON_UP_IRQ EXTI4_IRQn
  #elif (BUTTON_UP_Pin_Num > 4)&&(BUTTON_UP_Pin_Num <= 9)
  #define BUTTON_UP_IRQ EXTI9_5_IRQn
  #elif (BUTTON_UP_Pin_Num >= 10)
  #define BUTTON_UP_IRQ EXTI15_10_IRQn
  #endif	
#endif
#else
#define BUTTON_UP_Pin 0xFFFF
#define BUTTON_UP_Pin_Num 0xFF
#define BUTTON_UP_IRQ_En	0
#endif //(BUTTON_UP_Pin_En	== 1)
// </e>

// <e> BUTTON DOWN
#define BUTTON_DOWN_Pin_En	0
#if (BUTTON_DOWN_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define BUTTON_DOWN_Pin_Num	6
#define BUTTON_DOWN_Pin	GPIO_PIN(BUTTON_DOWN_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define BUTTON_DOWN_Port GPIO_PORT(2)
//   <o.0> Interrupt
//     <i> Use Interrupt
#define BUTTON_DOWN_IRQ_En	1
#if (BUTTON_DOWN_IRQ_En == 1)
  #if (BUTTON_DOWN_Pin_Num == 0)	
  #define BUTTON_DOWN_IRQ EXTI0_IRQn
  #elif (BUTTON_DOWN_Pin_Num == 1)
  #define BUTTON_DOWN_IRQ EXTI1_IRQn
  #elif (BUTTON_DOWN_Pin_Num == 2)
  #define BUTTON_DOWN_IRQ EXTI2_IRQn
  #elif (BUTTON_DOWN_Pin_Num == 3)
  #define BUTTON_DOWN_IRQ EXTI3_IRQn
  #elif (BUTTON_DOWN_Pin_Num == 4)
  #define BUTTON_DOWN_IRQ EXTI4_IRQn
  #elif (BUTTON_DOWN_Pin_Num > 4)&&(BUTTON_DOWN_Pin_Num <= 9)
  #define BUTTON_DOWN_IRQ EXTI9_5_IRQn
  #elif (BUTTON_DOWN_Pin_Num >= 10)
  #define BUTTON_DOWN_IRQ EXTI15_10_IRQn
  #endif	
#endif
#else
#define BUTTON_DOWN_Pin 0xFFFF
#define BUTTON_DOWN_Pin_Num 0xFF
#define BUTTON_DOWN_IRQ_En	0
#endif //(BUTTON_DOWN_Pin_En	== 1)
// </e>


// <e> BUTTON LEFT
#define BUTTON_LEFT_Pin_En	0
#if (BUTTON_LEFT_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define BUTTON_LEFT_Pin_Num	7
#define BUTTON_LEFT_Pin	GPIO_PIN(BUTTON_LEFT_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define BUTTON_LEFT_Port GPIO_PORT(2)
//   <o.0> Interrupt
//     <i> Use Interrupt
#define BUTTON_LEFT_IRQ_En	1
#if (BUTTON_LEFT_IRQ_En == 1)
  #if (BUTTON_LEFT_Pin_Num == 0)	
  #define BUTTON_LEFT_IRQ EXTI0_IRQn
  #elif (BUTTON_LEFT_Pin_Num == 1)
  #define BUTTON_LEFT_IRQ EXTI1_IRQn
  #elif (BUTTON_LEFT_Pin_Num == 2)
  #define BUTTON_LEFT_IRQ EXTI2_IRQn
  #elif (BUTTON_LEFT_Pin_Num == 3)
  #define BUTTON_LEFT_IRQ EXTI3_IRQn
  #elif (BUTTON_LEFT_Pin_Num == 4)
  #define BUTTON_LEFT_IRQ EXTI4_IRQn
  #elif (BUTTON_LEFT_Pin_Num > 4)&&(BUTTON_LEFT_Pin_Num <= 9)
  #define BUTTON_LEFT_IRQ EXTI9_5_IRQn
  #elif (BUTTON_LEFT_Pin_Num >= 10)
  #define BUTTON_LEFT_IRQ EXTI15_10_IRQn
  #endif	
#endif
#else
#define BUTTON_LEFT_Pin 0xFFFF
#define BUTTON_LEFT_Pin_Num 0xFF
#define BUTTON_LEFT_IRQ_En	0
#endif //(BUTTON_LEFT_Pin_En	== 1)
// </e>

// <e> BUTTON RIGHT
#define BUTTON_RIGHT_Pin_En	0
#if (BUTTON_RIGHT_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define BUTTON_RIGHT_Pin_Num	15
#define BUTTON_RIGHT_Pin	GPIO_PIN(BUTTON_RIGHT_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define BUTTON_RIGHT_Port GPIO_PORT(3)
//   <o.0> Interrupt
//     <i> Use Interrupt
#define BUTTON_RIGHT_IRQ_En	1
#if (BUTTON_RIGHT_IRQ_En == 1)
  #if (BUTTON_RIGHT_Pin_Num == 0)	
  #define BUTTON_RIGHT_IRQ EXTI0_IRQn
  #elif (BUTTON_RIGHT_Pin_Num == 1)
  #define BUTTON_RIGHT_IRQ EXTI1_IRQn
  #elif (BUTTON_RIGHT_Pin_Num == 2)
  #define BUTTON_RIGHT_IRQ EXTI2_IRQn
  #elif (BUTTON_RIGHT_Pin_Num == 3)
  #define BUTTON_RIGHT_IRQ EXTI3_IRQn
  #elif (BUTTON_RIGHT_Pin_Num == 4)
  #define BUTTON_RIGHT_IRQ EXTI4_IRQn
  #elif (BUTTON_RIGHT_Pin_Num > 4)&&(BUTTON_RIGHT_Pin_Num <= 9)
  #define BUTTON_RIGHT_IRQ EXTI9_5_IRQn
  #elif (BUTTON_RIGHT_Pin_Num >= 10)
  #define BUTTON_RIGHT_IRQ EXTI15_10_IRQn
  #endif	
#endif
#else
#define BUTTON_RIGHT_Pin 0xFFFF
#define BUTTON_RIGHT_Pin_Num 0xFF
#define BUTTON_RIGHT_IRQ_En	0
#endif //(BUTTON_RIGHT_Pin_En	== 1)
// </e>

// <e> BUTTON OK
#define BUTTON_OK_Pin_En	0
#if (BUTTON_OK_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define BUTTON_OK_Pin_Num	13
#define BUTTON_OK_Pin	GPIO_PIN(BUTTON_OK_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define BUTTON_OK_Port GPIO_PORT(3)
//   <o.0> Interrupt
//     <i> Use Interrupt
#define BUTTON_OK_IRQ_En	1
#if (BUTTON_OK_IRQ_En == 1)
  #if (BUTTON_OK_Pin_Num == 0)	
  #define BUTTON_OK_IRQ EXTI0_IRQn
  #elif (BUTTON_OK_Pin_Num == 1)
  #define BUTTON_OK_IRQ EXTI1_IRQn
  #elif (BUTTON_OK_Pin_Num == 2)
  #define BUTTON_OK_IRQ EXTI2_IRQn
  #elif (BUTTON_OK_Pin_Num == 3)
  #define BUTTON_OK_IRQ EXTI3_IRQn
  #elif (BUTTON_OK_Pin_Num == 4)
  #define BUTTON_OK_IRQ EXTI4_IRQn
  #elif (BUTTON_OK_Pin_Num > 4)&&(BUTTON_OK_Pin_Num <= 9)
  #define BUTTON_OK_IRQ EXTI9_5_IRQn
  #elif (BUTTON_OK_Pin_Num >= 10)
  #define BUTTON_OK_IRQ EXTI15_10_IRQn
  #endif	
#endif
#else
#define BUTTON_OK_Pin 0xFFFF
#define BUTTON_OK_Pin_Num 0xFF
#define BUTTON_OK_IRQ_En	0
#endif //(BUTTON_OK_Pin_En	== 1)
// </e>

// <e> BUTTON RETURN
#define BUTTON_RETURN_Pin_En	0
#if (BUTTON_RETURN_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define BUTTON_RETURN_Pin_Num	11
#define BUTTON_RETURN_Pin	GPIO_PIN(BUTTON_RETURN_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define BUTTON_RETURN_Port GPIO_PORT(3)
//   <o.0> Interrupt
//     <i> Use Interrupt
#define BUTTON_RETURN_IRQ_En	1
#if (BUTTON_RETURN_IRQ_En == 1)
  #if (BUTTON_RETURN_Pin_Num == 0)	
  #define BUTTON_RETURN_IRQ EXTI0_IRQn
  #elif (BUTTON_RETURN_Pin_Num == 1)
  #define BUTTON_RETURN_IRQ EXTI1_IRQn
  #elif (BUTTON_RETURN_Pin_Num == 2)
  #define BUTTON_RETURN_IRQ EXTI2_IRQn
  #elif (BUTTON_RETURN_Pin_Num == 3)
  #define BUTTON_RETURN_IRQ EXTI3_IRQn
  #elif (BUTTON_RETURN_Pin_Num == 4)
  #define BUTTON_RETURN_IRQ EXTI4_IRQn
  #elif (BUTTON_RETURN_Pin_Num > 4)&&(BUTTON_RETURN_Pin_Num <= 9)
  #define BUTTON_RETURN_IRQ EXTI9_5_IRQn
  #elif (BUTTON_RETURN_Pin_Num >= 10)
  #define BUTTON_RETURN_IRQ EXTI15_10_IRQn
  #endif	
#endif
#else
#define BUTTON_RETURN_Pin 0xFFFF
#define BUTTON_RETURN_Pin_Num 0xFF
#define BUTTON_RETURN_IRQ_En	0
#endif //(BUTTON_RETURN_Pin_En	== 1)
// </e>

// <e> BUTTON SETTINGS
#define BUTTON_SETTINGS_Pin_En	0
#if (BUTTON_SETTINGS_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define BUTTON_SETTINGS_Pin_Num	9
#define BUTTON_SETTINGS_Pin	GPIO_PIN(BUTTON_SETTINGS_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define BUTTON_SETTINGS_Port GPIO_PORT(3)
//   <o.0> Interrupt
//     <i> Use Interrupt
#define BUTTON_SETTINGS_IRQ_En	1
#if (BUTTON_SETTINGS_IRQ_En == 1)
  #if (BUTTON_SETTINGS_Pin_Num == 0)	
  #define BUTTON_SETTINGS_IRQ EXTI0_IRQn
  #elif (BUTTON_SETTINGS_Pin_Num == 1)
  #define BUTTON_SETTINGS_IRQ EXTI1_IRQn
  #elif (BUTTON_SETTINGS_Pin_Num == 2)
  #define BUTTON_SETTINGS_IRQ EXTI2_IRQn
  #elif (BUTTON_SETTINGS_Pin_Num == 3)
  #define BUTTON_SETTINGS_IRQ EXTI3_IRQn
  #elif (BUTTON_SETTINGS_Pin_Num == 4)
  #define BUTTON_SETTINGS_IRQ EXTI4_IRQn
  #elif (BUTTON_SETTINGS_Pin_Num > 4)&&(BUTTON_SETTINGS_Pin_Num <= 9)
  #define BUTTON_SETTINGS_IRQ EXTI9_5_IRQn
  #elif (BUTTON_SETTINGS_Pin_Num >= 10)
  #define BUTTON_SETTINGS_IRQ EXTI15_10_IRQn
  #endif	
#endif
#else
#define BUTTON_SETTINGS_Pin 0xFFFF
#define BUTTON_SETTINGS_Pin_Num 0xFF
#define BUTTON_SETTINGS_IRQ_En	0
#endif //(BUTTON_SETTINGS_Pin_En	== 1)
// </e>

// <e> BUTTON ENCASHMENT
#define BUTTON_ENCASHMENT_Pin_En	1
#if (BUTTON_ENCASHMENT_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define BUTTON_ENCASHMENT_Pin_Num	10
#define BUTTON_ENCASHMENT_Pin	GPIO_PIN(BUTTON_ENCASHMENT_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define BUTTON_ENCASHMENT_Port GPIO_PORT(4)
//   <o.0> Interrupt
//     <i> Use Interrupt
#define BUTTON_ENCASHMENT_IRQ_En	1
#if (BUTTON_ENCASHMENT_IRQ_En == 1)
  #if (BUTTON_ENCASHMENT_Pin_Num == 0)	
  #define BUTTON_ENCASHMENT_IRQ EXTI0_IRQn
  #elif (BUTTON_ENCASHMENT_Pin_Num == 1)
  #define BUTTON_ENCASHMENT_IRQ EXTI1_IRQn
  #elif (BUTTON_ENCASHMENT_Pin_Num == 2)
  #define BUTTON_ENCASHMENT_IRQ EXTI2_IRQn
  #elif (BUTTON_ENCASHMENT_Pin_Num == 3)
  #define BUTTON_ENCASHMENT_IRQ EXTI3_IRQn
  #elif (BUTTON_ENCASHMENT_Pin_Num == 4)
  #define BUTTON_ENCASHMENT_IRQ EXTI4_IRQn
  #elif (BUTTON_ENCASHMENT_Pin_Num > 4)&&(BUTTON_ENCASHMENT_Pin_Num <= 9)
  #define BUTTON_ENCASHMENT_IRQ EXTI9_5_IRQn
  #elif (BUTTON_ENCASHMENT_Pin_Num >= 10)
  #define BUTTON_ENCASHMENT_IRQ EXTI15_10_IRQn
  #endif	
#endif //(BUTTON_ENCASHMENT_IRQ_En == 1)
#else
#define BUTTON_ENCASHMENT_Pin 0xFFFF
#define BUTTON_ENCASHMENT_Pin_Num 0xFF
#define BUTTON_ENCASHMENT_IRQ_En	0
#endif //(BUTTON_ENCASHMENT_Pin_En	== 1)
// </e>

// <e> BUTTON HOPPER1
#define BUTTON_HOPPER1_Pin_En	0
#if (BUTTON_HOPPER1_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define BUTTON_HOPPER1_Pin_Num	12
#define BUTTON_HOPPER1_Pin	GPIO_PIN(BUTTON_HOPPER1_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define BUTTON_HOPPER1_Port GPIO_PORT(4)
//   <o.0> Interrupt
//     <i> Use Interrupt
#define BUTTON_HOPPER1_IRQ_En	1
#if (BUTTON_HOPPER1_IRQ_En == 1)
  #if (BUTTON_HOPPER1_Pin_Num == 0)	
  #define BUTTON_HOPPER1_IRQ EXTI0_IRQn
  #elif (BUTTON_HOPPER1_Pin_Num == 1)
  #define BUTTON_HOPPER1_IRQ EXTI1_IRQn
  #elif (BUTTON_HOPPER1_Pin_Num == 2)
  #define BUTTON_HOPPER1_IRQ EXTI2_IRQn
  #elif (BUTTON_HOPPER1_Pin_Num == 3)
  #define BUTTON_HOPPER1_IRQ EXTI3_IRQn
  #elif (BUTTON_HOPPER1_Pin_Num == 4)
  #define BUTTON_HOPPER1_IRQ EXTI4_IRQn
  #elif (BUTTON_HOPPER1_Pin_Num > 4)&&(BUTTON_HOPPER1_Pin_Num <= 9)
  #define BUTTON_HOPPER1_IRQ EXTI9_5_IRQn
  #elif (BUTTON_HOPPER1_Pin_Num >= 10)
  #define BUTTON_HOPPER1_IRQ EXTI15_10_IRQn
  #endif	
#endif //(BUTTON_HOPPER1_IRQ_En == 1)
#else
#define BUTTON_HOPPER1_Pin 0xFFFF
#define BUTTON_HOPPER1_Pin_Num 0xFF
#define BUTTON_HOPPER1_IRQ_En	0
#endif //(BUTTON_HOPPER1_Pin_En	== 1)
// </e>

// <e> BUTTON HOPPER2
#define BUTTON_HOPPER2_Pin_En	0
#if (BUTTON_HOPPER2_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define BUTTON_HOPPER2_Pin_Num	11
#define BUTTON_HOPPER2_Pin	GPIO_PIN(BUTTON_HOPPER2_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define BUTTON_HOPPER2_Port GPIO_PORT(4)
//   <o.0> Interrupt
//     <i> Use Interrupt
#define BUTTON_HOPPER2_IRQ_En	1
#if (BUTTON_HOPPER2_IRQ_En == 1)
  #if (BUTTON_HOPPER2_Pin_Num == 0)	
  #define BUTTON_HOPPER2_IRQ EXTI0_IRQn
  #elif (BUTTON_HOPPER2_Pin_Num == 1)
  #define BUTTON_HOPPER2_IRQ EXTI1_IRQn
  #elif (BUTTON_HOPPER2_Pin_Num == 2)
  #define BUTTON_HOPPER2_IRQ EXTI2_IRQn
  #elif (BUTTON_HOPPER2_Pin_Num == 3)
  #define BUTTON_HOPPER2_IRQ EXTI3_IRQn
  #elif (BUTTON_HOPPER2_Pin_Num == 4)
  #define BUTTON_HOPPER2_IRQ EXTI4_IRQn
  #elif (BUTTON_HOPPER2_Pin_Num > 4)&&(BUTTON_HOPPER2_Pin_Num <= 9)
  #define BUTTON_HOPPER2_IRQ EXTI9_5_IRQn
  #elif (BUTTON_HOPPER2_Pin_Num >= 10)
  #define BUTTON_HOPPER2_IRQ EXTI15_10_IRQn
  #endif	
#endif
#else
#define BUTTON_HOPPER2_Pin 0xFFFF
#define BUTTON_HOPPER2_Pin_Num 0xFF
#define BUTTON_HOPPER2_IRQ_En	0
#endif //(BUTTON_HOPPER2_Pin_En	== 1)
// </e>

// <e> LED BUTTON HOPPER1
#define LED_BUTTON_HOPPER1_Pin_En	0
#if (LED_BUTTON_HOPPER1_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define LED_BUTTON_HOPPER1_Pin_Num	1
#define LED_BUTTON_HOPPER1_Pin	GPIO_PIN(LED_BUTTON_HOPPER1_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define LED_BUTTON_HOPPER1_Port GPIO_PORT(1)
#else
#define LED_BUTTON_HOPPER1_Pin 0xFFFF
#define LED_BUTTON_HOPPER1_Pin_Num 0xFF
#endif //(LED_BUTTON_HOPPER1_Pin_En	== 1)
// </e>

// <e> LED BUTTON HOPPER2
#define LED_BUTTON_HOPPER2_Pin_En	0
#if (LED_BUTTON_HOPPER2_Pin_En	== 1)
//   <o> Pin <0=>P0 <1=>P1 <2=>P2 <3=>P3 <4=>P4 <5=>P5 <6=>P6
//       <7=>P7   <8=>P8   <9=>P9 <10=>P10 <11=>P11 <12=>P12 <13=>P13 <14=>P14 <15=>P15
#define LED_BUTTON_HOPPER2_Pin_Num	0
#define LED_BUTTON_HOPPER2_Pin	GPIO_PIN(LED_BUTTON_HOPPER2_Pin_Num)
//   <o> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD <4=>GPIOE <5=>GPIOF <6=>GPIOG
#define LED_BUTTON_HOPPER2_Port GPIO_PORT(1)
#else
#define LED_BUTTON_HOPPER2_Pin 0xFFFF
#define LED_BUTTON_HOPPER2_Pin_Num 0xFF
#endif //(LED_BUTTON_HOPPER2_Pin_En	== 1)
// </e>

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include "cmsis_os2.h"
#include "Terminal/Tamplates.h"
/**
  * @brief  Hopper MSP structure
  */
  
#define BUTTON_ENCASHMENT 0
#define NUM_BUTTONS       1
typedef struct __TERMINAL_ButtonsMSPTypeDef
{
  const uint16_t pin[NUM_BUTTONS];
  GPIO_TypeDef *port[NUM_BUTTONS];
	GPIO_PinState	state[NUM_BUTTONS];
  TERMINAL_EXTIStateTypeDef	exti[NUM_BUTTONS];
  
} TERMINAL_HandleButtonsMSPTypeDef;
/* Exported constants --------------------------------------------------------*/
 extern const osThreadAttr_t ButtonsMSPTask_attributes;
 extern osThreadId_t ButtonsMSP_TaskHandle;
 extern osEventFlagsId_t Buttons_Event_ID;                        // event flags id
/* Exported Macros -----------------------------------------------------------*/


enum EventButtonsMSP{
  BUTTON_ENCASHMENT_PIN_RISING = (1<<0),
  BUTTON_ENCASHMENT_PIN_FALLING = (1<<1),
  BUTTON_ENCASHMENT_PIN_NOISE = (1<<2),

};
namespace ButtonsNS
{
	typedef enum:uint32_t {
		NONE = 0x00,
		RESET = 0x01,
	} COMMAND;

	struct MessageClass
	{
		COMMAND command;
	};
  
	class ButtonsMSPClass
	{
    public:
      QueueMessageClass< MessageClass, 10 > Messages;
    ButtonsMSPClass() {
      }
    void Init();
    static void Buttons_MSP_Thread(void* arg);

	};

  extern ButtonsMSPClass Buttons;
  
  
  } //ButtonsNS
/* Exported functions --------------------------------------------------------*/
void Buttons_MSP_Thread(void* argument);
void Buttons_MspInit(void);
void Buttons_EXTI_Callback(uint16_t GPIO_Pin);





#endif /*__TERMINAL_BUTTONS_MSP_H*/
