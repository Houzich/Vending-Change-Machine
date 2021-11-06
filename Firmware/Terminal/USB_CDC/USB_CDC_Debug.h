/**
  ******************************************************************************
  * File Name          : USB_CDC_Debug.h
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_CDC_DEBUG
#define __USB_CDC_DEBUG
/* Includes ------------------------------------------------------------------*/
#include "rl_usb.h"

/* Exported constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void debug_string_descriptor_field_printf  (uint8_t * wcstr, uint8_t mode);
void debug_usb_status_printf  (usbStatus usb_status);
#endif /*__USBH_DEBUG_USER_CDC_0*/
