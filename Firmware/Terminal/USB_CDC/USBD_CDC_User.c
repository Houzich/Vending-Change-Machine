/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2018 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    VirtualCOM.c
 * Purpose: USB Device Virtual COM Port demonstration
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "main.h"
#include "USBD_CDC_User.h"
#include "Terminal/Terminal.h"
#include "USB_CDC_Debug.h"
#include "rl_usb.h"                     /* RL-USB function prototypes         */
#include "RTE_Components.h"
#include "OTG_FS_STM32F4xx.h"



#ifdef DEBUG_USB_CDC
#undef DEBUG
#undef DEBUG_PRINTF
#undef DEBUG_PUTCHAR
#define DEBUG(x)					printf("USB_CDC: "); printf x ;
#define DEBUG_PRINTF(x)		printf x ;
#else
#define DEBUG(x)
#define DEBUG_PRINTF(x)
#endif // DEBUG_USB_CDC

#ifdef RTE_Compiler_EventRecorder
#include "EventRecorder.h"
#endif

static   void                  *cdc_device_tid  =   0U;
static   CDC_LINE_CODING        cdc_line_coding = { 0U, 0U, 0U, 0U };
 
#define  USB_BUFFER_SIZE      (1024)    // USB Buffer Size
static            uint8_t       usb_rx_buf[USB_BUFFER_SIZE];
static            uint8_t       usb_tx_buf[USB_BUFFER_SIZE];


// Virtual COM Start stack size must be multiple of 8 Bytes
#define VIRTUAL_COM_STK_SZ (1024U)
uint64_t virtual_com_stk[VIRTUAL_COM_STK_SZ / 8];
const osThreadAttr_t virtual_com_attr = {
  .stack_mem  = &virtual_com_stk[0],
  .stack_size = sizeof(virtual_com_stk)
};



//// Virtual COM stack size must be multiple of 8 Bytes
//#define VIRTUAL_COM_START_STK_SZ (1024U)
//uint64_t virtual_com_start_stk[VIRTUAL_COM_START_STK_SZ / 8];
//const osThreadAttr_t virtual_com_start_attr = {
//  .stack_mem  = &virtual_com_start_stk[0],
//  .stack_size = sizeof(virtual_com_start_stk)
//};

//int fputc (int c, FILE * stream) {
//  if (stream == &__stdout) {
//		USBD_CDC_ACM_WriteData(0U, (const uint8_t *)c, 1);
//  }
//    return c;
//}
/*------------------------------------------------------------------------------
 *        Application
 *----------------------------------------------------------------------------*/
void Virtual_COM_Start (void *arg) {
  (void)arg;
	usbStatus usb_status;
	
#ifdef RTE_Compiler_EventRecorder
  EventRecorderInitialize(0, 1);
  EventRecorderEnable (EventRecordError, 0xA0U, 0xA6U);  /* USBD Error Events */
  EventRecorderEnable (EventRecordAll  , 0xA0U, 0xA0U);  /* Core Events */
  EventRecorderEnable (EventRecordAll  , 0xA4U, 0xA4U);  /* CDC Events */
#endif


  usb_status = USBD_Initialize(0);    // USB Device 0 Initialization
	
//	  GPIO_InitTypeDef GPIO_InitStruct;
//    GPIO_InitStruct.Pin         =  MX_USB_OTG_FS_DP_GPIO_Pin;
//    GPIO_InitStruct.Mode        =  MX_USB_OTG_FS_DP_GPIO_Mode;
//    GPIO_InitStruct.Pull        =  GPIO_PULLUP;
//    GPIO_InitStruct.Speed       =  MX_USB_OTG_FS_DP_GPIO_Speed;
//    GPIO_InitStruct.Alternate   =  MX_USB_OTG_FS_DP_GPIO_AF;
//    HAL_GPIO_Init                 (MX_USB_OTG_FS_DP_GPIOx, &GPIO_InitStruct);

	
  DEBUG("USBD_Initialize: "));
	debug_usb_status_printf(usb_status);
	usb_status = USBD_Connect(0);         				// USB Device 0 Connect
  DEBUG("USBD_Connect: "));
	debug_usb_status_printf(usb_status);


//  for (;;) {                            // Loop forever
//    osDelay(1000U);
//  }
}

__NO_RETURN void Virtual_COM_Thread (void *arg) {
  (void)arg;
	int32_t cnt;
	
	
  for (;;) {                            // Loop forever
		cnt = USBD_CDC_ACM_WriteData(0U, (const uint8_t *)"Anton!!!\n", sizeof("Anton!!!\n"));
		if (cnt > 0) {
			//usb_tx_cnt += cnt;
		}else if (cnt == 0){
			DEBUG("USBD_WriteData Error: was written 0 bytes\n");
		}else{
			DEBUG("USBD_WriteData Error: "));
			debug_usb_status_printf(cnt);
		}
    osDelay(1000U);
  }
}
#ifndef USB_FS_VIRTUAL_COM
// CDC ACM Callbacks -----------------------------------------------------------

// Called when new data was received from the USB Host.
// \param[in]   len           number of bytes available to read.
void USBD_CDC0_ACM_DataReceived (uint32_t len) {
  int32_t cnt;
  (void)(len);
 
    cnt = USBD_CDC_ACM_ReadData(0U, usb_rx_buf, USB_BUFFER_SIZE);

}
 
// Called during USBD_Initialize to initialize the USB CDC class instance (ACM).
void USBD_CDC0_ACM_Initialize (void) {
 
#ifdef USB_CMSIS_RTOS2
  cdc_device_tid = osThreadNew (Virtual_COM_Thread, NULL, &virtual_com_attr);
#else
  cdc_device_tid = osThreadCreate (osThread (Virtual_COM_Thread), NULL);
#endif
}
 
 
// Called during USBD_Uninitialize to de-initialize the USB CDC class instance (ACM).
void USBD_CDC0_ACM_Uninitialize (void) {
 
  if (osThreadTerminate (cdc_device_tid) == osOK) {
    cdc_device_tid = NULL;
  }
}
 
 
// Called upon USB Bus Reset Event.
void USBD_CDC0_ACM_Reset (void) {
}
 
 
// Called upon USB Host request to change communication settings.
// \param[in]   line_coding   pointer to CDC_LINE_CODING structure.
// \return      true          set line coding request processed.
// \return      false         set line coding request not supported or not processed.
bool USBD_CDC0_ACM_SetLineCoding (const CDC_LINE_CODING *line_coding) {
  return true;
}
 
 
// Called upon USB Host request to retrieve communication settings.
// \param[out]  line_coding   pointer to CDC_LINE_CODING structure.
// \return      true          get line coding request processed.
// \return      false         get line coding request not supported or not processed.
bool USBD_CDC0_ACM_GetLineCoding (CDC_LINE_CODING *line_coding) {
  // Load settings from ones stored on USBD_CDC0_ACM_SetLineCoding callback
  //*line_coding = cdc_acm_line_coding;
  return true;
}
 
 
// Called upon USB Host request to set control line states.
// \param [in]  state         control line settings bitmap.
//                - bit 0: DTR state
//                - bit 1: RTS state
// \return      true          set control line state request processed.
// \return      false         set control line state request not supported or not processed.
bool USBD_CDC0_ACM_SetControlLineState (uint16_t state) {
  // Add code for set control line state 
  (void)(state); 
  return true;
}
#endif //!USB_FS_VIRTUAL_COM