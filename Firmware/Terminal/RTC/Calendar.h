/**
  ******************************************************************************
  * File Name          : Calendar.h
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CALENDAR_H
#define __CALENDAR_H
#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "stm32f4xx_hal.h"
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void MX_RTC_Init(void);
void RTC_Alarm_IRQHandler(void);
int32_t TimeDate_To_String(char *str);
#ifdef __cplusplus
}
#endif
#endif /*__CALENDAR_H*/



