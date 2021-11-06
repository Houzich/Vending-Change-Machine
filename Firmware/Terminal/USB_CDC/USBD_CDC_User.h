/**
  ******************************************************************************
  * File Name          : VirtualCOM.h
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VIRTUAL_COM
#define __VIRTUAL_COM
/* Includes ------------------------------------------------------------------*/
//#include "rl_usb.h"
#include "cmsis_os2.h"
/* Exported constants --------------------------------------------------------*/
extern const osThreadAttr_t virtual_com_attr;
/* Exported Macros -----------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void Virtual_COM_Start (void *arg);
__NO_RETURN void Virtual_COM_Thread (void *arg);
#endif /*__VIRTUAL_COM*/
