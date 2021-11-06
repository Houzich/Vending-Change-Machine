/**
******************************************************************************
* File Name          : Terminal_MSP.h
******************************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_MSP_H
#define __TERMINAL_MSP_H
//#ifdef __cplusplus
// extern "C" {
//#endif
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum {
	TERMINAL_HOPPER_MSP_ERROR_OK = 1 << 0,
	TERMINAL_HOPPER_MSP_ERROR_INHIBIT = 1 << 1,
	TERMINAL_HOPPER_MSP_ERROR_COIN_EMPTY = 1 << 2,
	TERMINAL_HOPPER_MSP_ERROR_TIMEOUT = 1 << 3,
	TERMINAL_HOPPER_MSP_ERROR_EVENT_BEFORE_CREDIT_SIGNAL = 1 << 4,
	TERMINAL_HOPPER_MSP_ERROR_EVENT_BEFORE_METER_SIGNAL = 1 << 5,
  TERMINAL_HOPPER_MSP_ERROR_METER_LINE = 1 << 6,
	TERMINAL_HOPPER_MSP_ERROR_CREDIT_LINE = 1 << 7,
  
	TERMINAL_HOPPER_MSP_ERROR_READY = 1 << 20,
	TERMINAL_HOPPER_MSP_ERROR_COIN_OUT = 1 << 21,
	TERMINAL_HOPPER_MSP_ERROR_METER_SIGNAL = 1 << 22,
} TERMINAL_HopperMSPErrorTypeDef;
   
/* Exported types ------------------------------------------------------------*/
/**
* @brief  Terminal exti
*/
typedef enum {
	TERMINAL_EXTI_NONE = 0x00,
	TERMINAL_EXTI_RISING = 0x01,
	TERMINAL_EXTI_FALLING = 0x02,
} TERMINAL_EXTIStateTypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
 extern uint32_t Get_APB1_Timer_Clock(void);
 extern uint32_t Get_APB2_Timer_Clock(void);
 extern void Debug_Event_Flags_Error(uint32_t flags);


//#include "Bill_Acceptor_MSP.h"
//#include "Hopper_1_MSP.h"
//#include "Hopper_2_MSP.h"
//#ifdef __cplusplus
//}
//#endif

#endif /*__TERMINAL_MSP_H*/
