/**
  ******************************************************************************
  * File Name          : Terminal.c
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include <stdarg.h>
#include <stdio.h>

#include "Terminal_MSP.h"
#include "Hopper_1_MSP.h"
#include "Hopper_2_MSP.h"
#include "Bill_Acceptor_MSP.h"
#include "RTE_Components.h"
#include "cmsis_os2.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
using  namespace Hopper1MSPNS;
using  namespace Hopper2MSPNS;
using  namespace BillAcceptorMSPNS;

#ifdef DEBUG_TERMINAL_CORE
#undef DEBUG
#define DEBUG(...)		do {debug_header("TERMINAL MSP: ", __VA_ARGS__);} while (0)
#define DEBUG_PRINT(...)		    do {debug_print(__VA_ARGS__);} while (0)

#else
#define DEBUG(...)
#define DEBUG_PRINT(...)
#endif // DEBUG_TERMINAL_CORE

/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

  //Buttons_EXTI_Callback(GPIO_Pin);
}

extern bool fl_end_pulse;
extern __IO uint32_t  countPulse;
extern int Count_Pulse;
void prvvTIMERExpiredISR( void );



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
//  if(htim->Instance == TIM3){
//    if(BillAcceptorMSP.Start) BillAcceptorMSP.EXTI_Callback();
//    if(hopper_1_msp.Start) hopper_1_msp.EXTI_Callback();
//    if(hopper_2_msp.Start) hopper_2_msp.EXTI_Callback();    
//  }
}


uint32_t Get_APB1_Timer_Clock(void)
{
  /* Get PCLK1 frequency */
  uint32_t pclk1 = HAL_RCC_GetPCLK1Freq();
 
  /* Get PCLK1 prescaler */
  if((RCC->CFGR & RCC_CFGR_PPRE1) == 0)
  {
    /* PCLK1 prescaler equal to 1 => TIMCLK = PCLK1 */
    return (pclk1);
  }
  else
  {
    /* PCLK1 prescaler different from 1 => TIMCLK = 2 * PCLK1 */
    return(2 * pclk1);
  }
}

uint32_t Get_APB2_Timer_Clock(void)
{
  /* Get PCLK2 frequency */
  uint32_t pclk2 = HAL_RCC_GetPCLK2Freq();
 
  /* Get PCLK1 prescaler */
  if((RCC->CFGR & RCC_CFGR_PPRE2) == 0)
  {
    /* PCLK2 prescaler equal to 2 => TIMCLK = PCLK2 */
    return (pclk2);
  }
  else
  {
    /* PCLK1 prescaler different from 1 => TIMCLK = 2 * PCLK1 */
    return(2 * pclk2);
  }
}


void Debug_Event_Flags_Error(uint32_t flags){
	switch(flags){
		case osFlagsErrorUnknown:
			DEBUG_PRINT("OS Event_Flags_Error: unspecified error!!!\n");
			for(;;);
			break;
		case osFlagsErrorTimeout: 
			DEBUG_PRINT("OS Event_Flags_Error: awaited flags have not been set in the given time!!!\n");
			for(;;);
			break;
		case osFlagsErrorResource: 
			DEBUG_PRINT("OS Event_Flags_Error: awaited flags have not been set when no timeout was specified!!!\n");
			for(;;);
			break;
		case osFlagsErrorParameter: 
			DEBUG_PRINT("OS Event_Flags_Error: parameter ef_id does not identify a valid event flags object or flags has highest bit set!!!\n");
			for(;;);
			break;				
	}
}
