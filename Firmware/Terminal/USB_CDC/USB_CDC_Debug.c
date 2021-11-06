/*------------------------------------------------------------------------------
 * Name:    USB_CDC_Debug.c
 * Purpose: 
 * Rev.:    V0
 *----------------------------------------------------------------------------*/

#include <stdio.h>

#include "rl_usb.h"

#include "USB_CDC_Debug.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define DEBUG_USB_CDC

#ifdef DEBUG_USB_CDC
#undef DEBUG
#undef DEBUG_PRINTF
#undef DEBUG_PUTCHAR
#define DEBUG(x)					printf("USB_CDC: "); printf x ;
#define DEBUG_PRINTF(x)		printf x ;
#define DEBUG_PUTCHAR(x)	ITM_SendChar x ;
#else
#define DEBUG(x)
#define DEBUG_PRINTF(x)
#define DEBUG_PUTCHAR(x)
#endif // DEBUG_USB_CDC
 
 
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


void debug_usb_status_printf  (usbStatus usb_status) {
	switch(usb_status)
	{
		case usbOK:               DEBUG_PRINTF(("usbOK - Function completed with no error\n")); break;
		case usbTimeout:          DEBUG_PRINTF(("usbTimeout - Function completed; time-out occurred\n")); break;
		case usbInvalidParameter: DEBUG_PRINTF(("usbInvalidParameter - Invalid Parameter error: a mandatory parameter was missing or specified an incorrect object\n")); break;
		case usbThreadError:      DEBUG_PRINTF(("usbThreadError - CMSIS-RTOS Thread creation/termination failed\n")); break;
		case usbTimerError:       DEBUG_PRINTF(("usbTimerError - CMSIS-RTOS Timer creation/deletion failed\n")); break;
		case usbSemaphoreError:   DEBUG_PRINTF(("usbSemaphoreError - CMSIS-RTOS Semaphore creation failed\n")); break;
		case usbMutexError:       DEBUG_PRINTF(("usbMutexError - CMSIS-RTOS Mutex creation failed\n")); break;
		case usbControllerError:  DEBUG_PRINTF(("usbControllerError - Controller does not exist\n")); break;
		case usbDeviceError:      DEBUG_PRINTF(("usbDeviceError - Device does not exist\n")); break;
		case usbDriverError:      DEBUG_PRINTF(("usbDriverError - Driver function produced error\n")); break;
		case usbDriverBusy:       DEBUG_PRINTF(("usbDriverBusy - Driver function is busy\n")); break;
		case usbMemoryError:      DEBUG_PRINTF(("usbMemoryError - Memory management function produced error\n")); break;
		case usbNotConfigured:    DEBUG_PRINTF(("usbNotConfigured - Device is not configured (is connected)\n")); break;
		case usbClassErrorADC:    DEBUG_PRINTF(("usbClassErrorADC - Audio Device Class (ADC) error (no device or device produced error)\n")); break;
		case usbClassErrorCDC:    DEBUG_PRINTF(("usbClassErrorCDC - Communication Device Class (CDC) error (no device or device produced error)\n")); break;
		case usbClassErrorHID:    DEBUG_PRINTF(("usbClassErrorHID - Human Interface Device (HID) error (no device or device produced error)\n")); break;
		case usbClassErrorMSC:    DEBUG_PRINTF(("usbClassErrorMSC - Mass Storage Device (MSC) error (no device or device produced error)\n")); break;
		case usbClassErrorCustom: DEBUG_PRINTF(("usbClassErrorCustom - Custom device Class (Class) error (no device or device produced error)\n")); break;
		case usbUnsupportedClass: DEBUG_PRINTF(("usbUnsupportedClass - Unsupported Class\n")); break;
		case usbTransferStall:    DEBUG_PRINTF(("usbTransferStall - Transfer handshake was stall\n")); break;
		case usbTransferError:    DEBUG_PRINTF(("usbTransferError - Transfer error\n")); break;
		case usbUnknownError:     DEBUG_PRINTF(("usbUnknownError - Unspecified USB error\n")); break;
		default: 						 			DEBUG_PRINTF(("ERROR device_info.status. UNKNOWN STATUS!!!\n")); break;
	}	
}