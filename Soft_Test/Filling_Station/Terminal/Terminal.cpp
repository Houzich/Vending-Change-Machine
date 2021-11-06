/**
  ******************************************************************************
  * File Name          : Terminal.c
  ******************************************************************************
  */
  /* Includes ------------------------------------------------------------------*/
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


#include "Terminal/Terminal.h"
#ifdef TERMINAL_USE_STM
//#include "USB_CDC_Debug.h"
//#include "USBD_CDC_User.h"
//#include "rl_usb.h"                     /* RL-USB function prototypes         */
#include "RTE_Components.h"
#include "cmsis_os2.h"
#include "TCP_Client.h"
#include "Calendar.h"
#endif //TERMINAL_USE_STM

#ifdef DEBUG_TERMINAL_CORE
#undef DEBUG
#define DEBUG(...)		do {debug_header("TERMINAL: ", __VA_ARGS__);} while (0)
#define DEBUG_PRINT(...)		    do {debug_print(__VA_ARGS__);} while (0)

#else
#define DEBUG(...)
#define DEBUG_PRINT(...)
#endif // DEBUG_TERMINAL_CORE
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


#ifdef TERMINAL_USE_USB_FOR_DEBUG
static  uint8_t tx_buf[DEBUG_USB_BUFFER_SIZE];
#elif defined(TERMINAL_USE_ETH_FOR_DEBUG)
uint8_t* EthDebugBuf = NULL;
static int Len_Header;
#endif // TERMINAL_USE_USB_FOR_DEBUG

uint8_t* EthSettingsBuf = NULL;
uint8_t* DisplayBuf = NULL;

#ifdef TERMINAL_USE_STM
#ifdef TERMINAL_USE_TCP_SEMAPHORE
osSemaphoreId_t sid_ClientTCP_Semaphore;
//osSemaphoreId_t sid_ETH_Debug_Semaphore;
//osSemaphoreId_t sid_ETH_Display_Semaphore;
#endif // TERMINAL_USE_TCP_SEMAPHORE

osMutexId_t ClientTCP_Mutex_ID;

const osMutexAttr_t ClientTCP_Mutex_attr = {
  "ClientTCP_Mutex",     // human readable mutex name
  osMutexRecursive,    // attr_bits
  NULL,                // memory for control block   
  0U                   // size for control block
};

/*###############################################################*/
 /* definition and creation of CoreTask */
uint64_t core_stk[2048 * 2 / 8];
const osThreadAttr_t CoreTask_attributes = {
  .name = "CoreTask",
  .stack_mem = &core_stk[0],
  .stack_size = sizeof(core_stk),
  .priority = (osPriority_t)osPriorityNormal,
};
osThreadId_t Core_TaskHandle = NULL;
/*###############################################################*/
 /* definition and creation of BillAcceptorTask */
uint64_t billacceptor_stk[2048 / 8];
const osThreadAttr_t BillAcceptorTask_attributes = {
  .name = "BillAcceptorTask",
  .stack_mem = &billacceptor_stk[0],
  .stack_size = sizeof(billacceptor_stk),
  .priority = (osPriority_t)osPriorityNormal,
};
osThreadId_t BillAcceptor_TaskHandle = NULL;
/*###############################################################*/
 /* definition and creation of Display1Task */
uint64_t display1_stk[2048 / 8];
const osThreadAttr_t Display1Task_attributes = {
  .name = "Display1Task",
  .stack_mem = &display1_stk[0],
  .stack_size = sizeof(display1_stk),
  .priority = (osPriority_t)osPriorityNormal,
};
osThreadId_t Display1_TaskHandle = NULL;
/*###############################################################*/
 /* definition and creation of Display2Task */
uint64_t display2_stk[2048 / 8];
const osThreadAttr_t Display2Task_attributes = {
  .name = "Display2Task",
  .stack_mem = &display2_stk[0],
  .stack_size = sizeof(display2_stk),
  .priority = (osPriority_t)osPriorityNormal,
};
osThreadId_t Display2_TaskHandle = NULL;
/*###############################################################*/
 /* definition and creation of HopperTask */
uint64_t hopper_stk[2048 / 8];
const osThreadAttr_t HopperTask_attributes = {
  .name = "HopperTask",
  .stack_mem = &hopper_stk[0],
  .stack_size = sizeof(hopper_stk),
  .priority = (osPriority_t)osPriorityNormal,
};
osThreadId_t Hopper_TaskHandle = NULL;
#endif //TERMINAL_USE_STM


#ifdef TERMINAL_USE_USB_FOR_DEBUG
/*###############################################################*/
/*###############################################################* print -->*/
/*###############################################################*/
_ARMABI int print(const char* format, ...)
{
	//  va_list arg;
	//  int done;
	//  va_start (arg, format);
	//	snprintf((char *)usb_tx_buf, sizeof(usb_tx_buf), format, arg);
	//	done = USBD_CDC_ACM_WriteData(0U, (const uint8_t *)"Anton!!!\n", sizeof("Anton!!!\n"));
	//	if (done > 0) {
	//	}else if (done == 0){
	//		DEBUG_PRINT("USBD print Error: was written 0 bytes");
	//	}else{
	//		DEBUG_PRINT("USBD print Error: ");
	//		debug_usb_status_printf(done);
	//	}
	//  va_end (arg);
	//  return done;
	return 0;
}
#endif // TERMINAL_USE_USB_FOR_DEBUG
#ifdef TERMINAL_USE_ETH_FOR_DEBUG
/*###############################################################*/
/*###############################################################* eth_print -->*/
/*###############################################################*/
_ARMABI int eth_print(const char* format, ...)
{
	int size = 0;
	TCPClientSemaphoreAcquire(sid_ETH_Debug_Semaphore, osWaitForever);
	uint8_t* buff = NULL;

	for (int i = 0; i < 500; i++) {
    if (tcp_sock < 0) goto EXIT;
		if (netTCP_GetState(tcp_sock) != netTCP_StateESTABLISHED) goto EXIT;
		if (netTCP_SendReady(tcp_sock) == true) {
			buff = netTCP_GetBuffer(DEBUG_ETH_BUFFER_SIZE);
			break;
		}
		osDelay(10);
	}

	if (buff == NULL) {
		goto EXIT;
	}
	strncpy((char*)&buff[0], "DEBUG:__", 8);
	va_list arg;
	va_start(arg, format);
	size = vsnprintf((char*)&buff[8], DEBUG_ETH_BUFFER_SIZE, format, arg);
	va_end(arg);
	size += 8 + 1;
	//send the data
	if (size >= DEBUG_ETH_BUFFER_SIZE) {
		DEBUG_PRINT("ERROR DISPLAY SEND ETH!!!\n");
		TCPClientSemaphoreRelease(sid_ETH_Debug_Semaphore);
		osThreadYield();
		return size;
	}

	for (int i = 0; i < 100; i++) {
    if (tcp_sock < 0) goto EXIT;
		if (netTCP_GetState(tcp_sock) != netTCP_StateESTABLISHED) goto EXIT;
		if (netTCP_SendReady(tcp_sock) == true)break;
		osDelay(10);
	}

	if (netTCP_SendReady(tcp_sock) == true) {
		netTCP_Send(tcp_sock, buff, size);
	}
	else {
		netTCP_Send(tcp_sock, buff, 0); //release a buffer
	}

	TCPClientSemaphoreRelease(sid_ETH_Debug_Semaphore);
	return size;
EXIT:
	TCPClientSemaphoreRelease(sid_ETH_Debug_Semaphore);
	osThreadYield();
	return -1;
}
/*###############################################################*/
/*###############################################################* eth_header_print -->*/
/*###############################################################*/
_ARMABI int eth_header_print(const char* str, const char* format, ...)
{
	int size = 0;
	uint8_t* buff = NULL;
  int len_str = 0;
	TCPClientSemaphoreAcquire(sid_ETH_Debug_Semaphore, osWaitForever);

	for (int i = 0; i < 500; i++) {
    if (tcp_sock < 0) goto EXIT;
		if (netTCP_GetState(tcp_sock) != netTCP_StateESTABLISHED) goto EXIT;
		if (netTCP_SendReady(tcp_sock) == true) {
			buff = netTCP_GetBuffer(DEBUG_ETH_BUFFER_SIZE);
			break;
		}
		osDelay(10);
	}

	if (buff == NULL) {
		goto EXIT;
	}
	size = 8;
	strncpy((char*)&buff[0], "DEBUG:__", size);
	size += TimeDate_To_String((char*)&buff[size]);
	len_str = strlen(str);
	strncpy((char*)&buff[size], str, len_str);
	size += len_str;
	va_list arg;
	va_start(arg, format);
	size += vsnprintf((char*)&buff[size], DEBUG_ETH_BUFFER_SIZE, format, arg);
	va_end(arg);
	//send the data
	size += 1; //add null char
	if (size >= DEBUG_ETH_BUFFER_SIZE) {
		DEBUG_PRINT("ERROR DISPLAY SEND ETH!!!\n");
		TCPClientSemaphoreRelease(sid_ETH_Debug_Semaphore);
		osThreadYield();
		return size;
	}

	for (int i = 0; i < 100; i++) {
		if (netTCP_SendReady(tcp_sock) == true)break;
		osDelay(10);
	}

	if (netTCP_SendReady(tcp_sock) == true) {
		netTCP_Send(tcp_sock, buff, size);
	}
	else {
		netTCP_Send(tcp_sock, buff, 0); //release a buffer
	}

	TCPClientSemaphoreRelease(sid_ETH_Debug_Semaphore);
	osThreadYield();
	return size;
  
  EXIT:
	TCPClientSemaphoreRelease(sid_ETH_Debug_Semaphore);
	osThreadYield();
	return -1;
}
#else
#ifdef TERMINAL_USE_STM
_ARMABI int header_print(const char* str, const char* format, ...)
#else
int header_print(const char* str, const char* format, ...)
#endif // TERMINAL_USE_STM
{
	int ret;
	ret = printf("%s", str);
	va_list arg;
	va_start(arg, format);
	ret = vprintf(format, arg);
	va_end(arg);
	return ret;
}

#ifdef TERMINAL_USE_STM
_ARMABI int print(const char* format, ...)
#else
int print(const char* format, ...)
#endif // TERMINAL_USE_STM
{
	int ret;
	va_list arg;
	va_start(arg, format);
	ret = vprintf(format, arg);
	va_end(arg);
	return ret;
}
#endif // TERMINAL_USE_ETH_FOR_DEBUG

#ifdef TERMINAL_USE_STM
/*###############################################################*/
/*###############################################################* Send_Settings_ETH -->*/
/*###############################################################*/
int Send_Settings_ETH(void)
{
    return 0;
//  int size = 0;
//	TERMINAL_HandleTypeDef* term = Terminal_Get_Handle();
//	TCPClientSemaphoreAcquire(sid_ClientTCP_Semaphore, osWaitForever);

//	while (1) {
//    if (tcp_sock < 0) goto EXIT;
//		if (netTCP_GetState(tcp_sock) != netTCP_StateESTABLISHED) goto EXIT;
//		if (netTCP_SendReady(tcp_sock) == true) {
//			EthSettingsBuf = netTCP_GetBuffer(sizeof(TERMINAL_SettingsTypeDef) + 20);
//			break;
//		}
//		osDelay(1);
//	}

//	if (EthSettingsBuf == NULL) {
//		goto EXIT;
//	}
//	strncpy((char*)&EthSettingsBuf[0], "SETT:___", 8);
//	memcpy(&EthSettingsBuf[8], &term->settings, sizeof(TERMINAL_SettingsTypeDef));
//	size = 8 + sizeof(TERMINAL_SettingsTypeDef);
//	//send the data
//	while (1) {
//    if (tcp_sock < 0) goto EXIT;
//		if (netTCP_GetState(tcp_sock) != netTCP_StateESTABLISHED) goto EXIT;
//		if (netTCP_SendReady(tcp_sock) == true) {
//			netTCP_Send(tcp_sock, EthSettingsBuf, size);
//			break;
//		}
//		osDelay(10);
//	}
//	TCPClientSemaphoreRelease(sid_ClientTCP_Semaphore);
//	return size;
//EXIT:
//	TCPClientSemaphoreRelease(sid_ClientTCP_Semaphore);
//	osThreadYield();
//	return -1;
}
/*###############################################################*/
/*###############################################################* Send_Button_State_ETH -->*/
/*###############################################################*/
int Send_Button_State_ETH(void)
{
  return 0;
//	TERMINAL_HandleTypeDef* term = Terminal_Get_Handle();
//	TCPClientSemaphoreAcquire(sid_ClientTCP_Semaphore, osWaitForever);
//	uint8_t* buff = NULL;
//	uint32_t button_state = 0;
//	int size = 0;
//	while (1) {
//    if (tcp_sock < 0) goto EXIT;
//		if (netTCP_GetState(tcp_sock) != netTCP_StateESTABLISHED) goto EXIT;
//		if (netTCP_SendReady(tcp_sock) == true) {
//			buff = netTCP_GetBuffer(sizeof(uint32_t) + 20);
//			break;
//		}
//		osDelay(1);
//	}

//	if (buff == NULL) {
//		goto EXIT;
//	}
//	strncpy((char*)&buff[0], "BUTT:STA", 8);
//	if (term->enable_button_hoppers) button_state |= TERMINAL_BUTTON_HOPPERS;
//	if (term->enable_button_hopper_1) button_state |= TERMINAL_BUTTON_HOPPER_1;
//	if (term->enable_button_hopper_2) button_state |= TERMINAL_BUTTON_HOPPER_2;
//	if (term->enable_button_carddispenser) button_state |= TERMINAL_BUTTON_CARD_DISPANSER;
//	if (term->enable_button_deposit) button_state |= TERMINAL_BUTTON_DEPOSIT;
//	if (term->enable_button_up) button_state |= TERMINAL_BUTTON_UP;
//	if (term->enable_button_down) button_state |= TERMINAL_BUTTON_DOWN;
//	if (term->enable_button_left) button_state |= TERMINAL_BUTTON_LEFT;
//	if (term->enable_button_right) button_state |= TERMINAL_BUTTON_RIGHT;
//	if (term->enable_button_ok) button_state |= TERMINAL_BUTTON_OK;
//	if (term->enable_button_settings) button_state |= TERMINAL_BUTTON_SETTINGS;
//	if (term->enable_button_return) button_state |= TERMINAL_BUTTON_RETURN;
//	if (term->enable_button_encashment) button_state |= TERMINAL_BUTTON_ENCASHMENT;

//	memcpy(&buff[8], &button_state, sizeof(uint32_t));
//	size = 8 + sizeof(uint32_t);
//	//send the data
//	while (1) {
//    if (tcp_sock < 0) goto EXIT;
//		if (netTCP_GetState(tcp_sock) != netTCP_StateESTABLISHED) goto EXIT;
//		if (netTCP_SendReady(tcp_sock) == true) {
//			netTCP_Send(tcp_sock, buff, size);
//			break;
//		}
//		osDelay(10);
//	}
//	TCPClientSemaphoreRelease(sid_ClientTCP_Semaphore);
//	return size;
//EXIT:
//	TCPClientSemaphoreRelease(sid_ClientTCP_Semaphore);
//	osThreadYield();
//	return -1;
}

int Send_Message_ETH(uint8_t* mess, int len)
{
	TCPClientSemaphoreAcquire(sid_ClientTCP_Semaphore, osWaitForever);
	uint8_t* buff = NULL;
	while (1) {
    if (tcp_sock < 0) goto EXIT;
		if (netTCP_GetState(tcp_sock) != netTCP_StateESTABLISHED) goto EXIT;
		if (netTCP_SendReady(tcp_sock) == true) {
			buff = netTCP_GetBuffer(len);
			break;
		}
		osDelay(1);
	}

	if (buff == NULL) {
		goto EXIT;
	}

	memcpy(&buff, &mess, len);
	//send the data
	while (1) {
    if (tcp_sock < 0) goto EXIT;
		if (netTCP_GetState(tcp_sock) != netTCP_StateESTABLISHED) goto EXIT;
		if (netTCP_SendReady(tcp_sock) == true) {
			netTCP_Send(tcp_sock, buff, len);
			break;
		}
		osDelay(10);
	}
	TCPClientSemaphoreRelease(sid_ClientTCP_Semaphore);
	return 0;
EXIT:
	TCPClientSemaphoreRelease(sid_ClientTCP_Semaphore);
	osThreadYield();
	return -1;
}
static TERMINAL_HopperStateForServerTypeDef hopper_state = { 0 };
#include <stdlib.h>
/*###############################################################*/
/*###############################################################* Send_Hopper_State_ETH -->*/
/*###############################################################*/
int Send_Hopper_State_ETH(int num) {
	return 0;
}

uint32_t Check_CMSIS_Flags_Functions_Error_Codes(uint32_t flags) {
	uint32_t ret = flags;
	switch (flags)
	{
	case  osFlagsErrorUnknown:
		printf("osFlagsErrorUnknown: unspecified error\n");
		break;
	case  osFlagsErrorTimeout:
		//printf("osFlagsErrorTimeout: awaited flags have not been set in the given time\n");
		break;
	case  osFlagsErrorResource:
		//printf("osFlagsErrorResource: awaited flags have not been set when no timeout was specified\n");
		break;
	case  osFlagsErrorParameter:
		printf("osFlagsErrorParameter: parameter ef_id does not identify a valid event flags object or flags has\n");
		break;
	default:
		ret = 0;
		break;
	}
	return ret;
}
#endif //TERMINAL_USE_STM





