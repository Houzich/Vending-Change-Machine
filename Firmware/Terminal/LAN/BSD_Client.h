/**
  ******************************************************************************
  * @file    BSD_Client.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSD_CLIENT_H
#define __BSD_CLIENT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern uint64_t bsd_client_stk[];
extern const osThreadAttr_t bsd_client_attr;

/* Exported macro ------------------------------------------------------------*/


/* Exported functions ------------------------------------------------------- */
extern void bsd_client (void *arg);

#endif /* __BSD_CLIENT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
