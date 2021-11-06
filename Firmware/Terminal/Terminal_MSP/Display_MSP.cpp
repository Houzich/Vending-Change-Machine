/**
  ******************************************************************************
  * File Name          : Display.c
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include <string.h>
#include <stdbool.h>
#include "Terminal/Terminal.h"
#ifdef TERMINAL_USE_FREERTOS
#include "cmsis_os2.h"
#include "stm32f4xx.h"
#elif defined(TERMINAL_USE_WINDOWS)
#include "..\Threads.h"
#include <Windows.h>
#endif /*TERMINAL_USE_FREERTOS*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#undef TERMINAL_DISPLAY_DATA_DEBUG
//#define TERMINAL_DISPLAY_DATA_DEBUG
#define DELAY_FOR_TEST(x)		//Delay(x);
/* Private macro -------------------------------------------------------------*/
#ifdef DEBUG_TERMINAL_DISPLAY
#undef DEBUG
#define DEBUG(x)		print("TERMINAL DISPLAY: "); print x ;
#else
#define DEBUG(x)
#endif // DEBUG_TERMINAL_DISPLAY


#define TERMINAL_DISPLAY_SET_ERROR(x)   serial.error = x;\
										serial.status = TERMINAL_PORT_STATUS_ERROR;


#define TERMINAL_DISPLAY_IF_ERROR(x)    ((serial.error == x)&&\
										(serial.status == TERMINAL_PORT_STATUS_ERROR))

/* Private function prototypes -----------------------------------------------*/
static bool Init(void);
static bool Reset(void);
static bool Reset_TickStart(void);
static void Transmit_Enable(void);
static void Receive_Enable(void);
static bool Display_Send(TERMINAL_HandleDisplayTypeDef *display, uint8_t *data, uint32_t size);
static bool Display_Receive(TERMINAL_HandleDisplayTypeDef *display, uint8_t *data, uint32_t size);
static void Display_1_Loop(void const * argument);
static void Display_2_Loop(void const * argument);
void Show_Delate(uint8_t *data_1, uint8_t *data_2, TERMINAL_DisplayStatusTypeDef cmd, uint32_t timeout);
void Show(uint8_t *data_1, uint8_t *data_2, TERMINAL_DisplayStatusTypeDef cmd, uint32_t timeout);
/* Exported functions --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef DISPLAY_PORT_RS485
TERMINAL_PortTypeDef	serial_if;
#endif // DISPLAY_PORT_RS485

// declare the structure of the module, initialize the initial values
// set links to module functions
static TERMINAL_HandleDisplayTypeDef hdisplay_1 =
{
	TERMINAL_DISPLAY_STATUS_READY,
	TERMINAL_DISPLAY_STATUS_READY,
	TERMINAL_DISPLAY_ERROR_OK,
	0,
	0,
	{0},
	{0},
	{0},

	0,

	//500,
	0,
	Transmit_Enable,
	Receive_Enable,
	NULL,	//Init,
	NULL,	//Reset,
	NULL,	//Reset_TickStart,
	//Display_Send,
	//Display_Receive,
	Display_1_Loop,	//Display_1_Loop,
};

static TERMINAL_HandleDisplayTypeDef hdisplay_2 =
{
	TERMINAL_DISPLAY_STATUS_READY,
	TERMINAL_DISPLAY_STATUS_READY,
	TERMINAL_DISPLAY_ERROR_OK,
	0,
	0,
	{0},
	{0},
	{0},

	0,

	//500,
	0,
	Transmit_Enable,
	Receive_Enable,
	NULL,	//Init,
	NULL,	//Reset,
	NULL,	//Reset_TickStart,
	//Display_Send,
	//Display_Receive,
	Display_2_Loop,	//Display_2_Loop,
};

static TERMINAL_HandleDisplaysTypeDef hdisplay =
{
	TERMINAL_DISPLAY_STATUS_READY,
	TERMINAL_DISPLAY_STATUS_READY,
	TERMINAL_DISPLAY_ERROR_OK,
	&hdisplay_1,
	&hdisplay_2,
	500,
	0,
	NULL,
	Init,
	Reset,
	Reset_TickStart,
	Display_Send,
	Display_Receive,
};
/*###############################################################*/
/*###############################################################* debug_usart_send -->*/
/*###############################################################*/
static void debug_usart_send(uint8_t *data, uint32_t size)
{
	#ifdef TERMINAL_DISPLAY_DATA_DEBUG
	printf("SLAVE SEND %u BYTES: ", size);
	for(int i = 0; i < size; i++)
	{
		printf("%02X ", data[i]);
	}
	printf("\n");
	#endif // TERMINAL_DISPLAY_DATA_DEBUG
}
/*###############################################################*/
/*###############################################################* debug_usart_receive -->*/
/*###############################################################*/
static void debug_usart_receive(uint8_t *data, uint32_t size)
{
	#ifdef TERMINAL_DISPLAY_DATA_DEBUG
	printf("SLAVE RECEIVE %u BYTES: ", size);
	for(int i = 0; i < size; i++)
	{
		printf("%02X ", data[i]);
	}
	printf("\n");
	#endif // TERMINAL_DISPLAY_DATA_DEBUG
}
/*###############################################################*/
/*###############################################################* Terminal_Get_HandleDisplay -->*/
/*###############################################################*/
//returns a pointer to the module structure
TERMINAL_HandleDisplaysTypeDef *Terminal_Get_HandleDisplay(void)
{
	return &hdisplay;
}
/*###############################################################*/
/*###############################################################* Delay -->*/
/*###############################################################*/
static void Delay(uint32_t ms)
{
#ifdef TERMINAL_USE_FREERTOS
	osDelay(ms);
#elif defined(TERMINAL_USE_HAL)
	HAL_Delay(ms);
#elif defined(TERMINAL_USE_WINDOWS)
	//std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	Sleep(ms);
#endif /*TERMINAL_USE_FREERTOS*/
}

#ifdef DISPLAY_PORT_RS485
#ifdef TERMINAL_USE_DMA
/*###############################################################*/
/*###############################################################* Tx_DMA_Reset -->*/
/*###############################################################*/
//reset DMA
static void Tx_DMA_Reset(UART_HandleTypeDef *huart)
{
	__HAL_DMA_DISABLE(huart->hdmatx);/* Disable the peripheral */
  /* Clear all flags */
	__HAL_DMA_CLEAR_FLAG (huart->hdmatx, __HAL_DMA_GET_TC_FLAG_INDEX(huart->hdmatx));
	__HAL_DMA_CLEAR_FLAG (huart->hdmatx, __HAL_DMA_GET_HT_FLAG_INDEX(huart->hdmatx));
	__HAL_DMA_CLEAR_FLAG (huart->hdmatx, __HAL_DMA_GET_TE_FLAG_INDEX(huart->hdmatx));
	__HAL_DMA_CLEAR_FLAG (huart->hdmatx, __HAL_DMA_GET_DME_FLAG_INDEX(huart->hdmatx));
	__HAL_DMA_CLEAR_FLAG (huart->hdmatx, __HAL_DMA_GET_FE_FLAG_INDEX(huart->hdmatx));

	__HAL_UART_CLEAR_OREFLAG(huart);
	huart->hdmatx->Instance->NDTR = 0;
}
/*###############################################################*/
/*###############################################################* Rx_DMA_Reset -->*/
/*###############################################################*/
//reset DMA
static void Rx_DMA_Reset(UART_HandleTypeDef *huart)
{
	__HAL_DMA_DISABLE(huart->hdmarx);/* Disable the peripheral */
  /* Clear all flags */
  __HAL_DMA_CLEAR_FLAG (huart->hdmarx, __HAL_DMA_GET_TC_FLAG_INDEX(huart->hdmarx));
  __HAL_DMA_CLEAR_FLAG (huart->hdmarx, __HAL_DMA_GET_HT_FLAG_INDEX(huart->hdmarx));
  __HAL_DMA_CLEAR_FLAG (huart->hdmarx, __HAL_DMA_GET_TE_FLAG_INDEX(huart->hdmarx));
  __HAL_DMA_CLEAR_FLAG (huart->hdmarx, __HAL_DMA_GET_DME_FLAG_INDEX(huart->hdmarx));
  __HAL_DMA_CLEAR_FLAG (huart->hdmarx, __HAL_DMA_GET_FE_FLAG_INDEX(huart->hdmarx));

  __HAL_UART_CLEAR_OREFLAG(huart);
  huart->hdmarx->Instance->NDTR = 0;
}
#endif /*TERMINAL_USE_DMA*/
/*###############################################################*/
/*###############################################################* Transmit_Enable -->*/
/*###############################################################*/
//set pin for transmit via rs485
static void Transmit_Enable(void)
{
	#ifdef TERMINAL_TEST
	Slave_Transmit_Enable = true;
	Slave_Receive_Enable = false;
	if(Master_Transmit_Enable){
		printf("BOOT SLAVE: ERROR RS485 CONFLICT TRANSMITTERS!!!!!! \r\n\r\n");
	}
	#endif // TERMINAL_TEST
	
	//HAL_GPIO_WritePin((void *)serial.rs485_re_port, serial.rs485_re_pin, GPIO_PIN_SET);
	//HAL_GPIO_WritePin((void *)serial.rs485_de_port, serial.rs485_de_pin, GPIO_PIN_SET);
}
/*###############################################################*/
/*###############################################################* Receive_Enable -->*/
/*###############################################################*/
//set pins for receive via rs485
static void Receive_Enable(void)
{
	#ifdef TERMINAL_TEST
	Slave_Transmit_Enable = false;
	Slave_Receive_Enable = true;
	#endif // TERMINAL_TEST
	
	//HAL_GPIO_WritePin((void *)serial.rs485_de_port, serial.rs485_de_pin, GPIO_PIN_RESET);
	//HAL_GPIO_WritePin((void *)serial.rs485_re_port, serial.rs485_re_pin, GPIO_PIN_RESET);
}
#ifdef TERMINAL_USE_DMA
/*###############################################################*/
/*###############################################################* Display_Send -->*/
/*###############################################################*/
//
static bool Display_Send(uint8_t *data, uint32_t size)
{
	uint32_t tickstart = HAL_GetTick();
	uint32_t timeout = serial.tx_timeout;
	while((serial.huart->gState != HAL_UART_STATE_READY)
		||(serial.huart->hdmarx->Instance->NDTR != 0)
		||(serial.huart->hdmatx->Instance->NDTR != 0))
	{
		if(HAL_GetTick() - tickstart >= timeout){
		TERMINAL_DISPLAY_SET_ERROR(TERMINAL_PORT_ERROR_TX_TIMEOUT);
		return false;
		}
	}
	
	if(data!=buff.buff){
		memcpy(buff.buff, data, size);
	}
	
	//Delay(1);
	debug_usart_send(buff.buff, size);
	Transmit_Enable();
	HAL_StatusTypeDef err = HAL_UART_Transmit_DMA(serial.huart, buff.buff, size);
	if (err == HAL_OK)
	{
		while(serial.huart->hdmatx->Instance->NDTR != 0){DELAY_FOR_TEST(1);}
		while(serial.huart->gState != HAL_UART_STATE_READY){}
		Receive_Enable();
		return true;
	}
	else
	{
		TERMINAL_DISPLAY_SET_ERROR(TERMINAL_PORT_ERROR_TX);
		DEBUG(("ERROR USART\r\n"));
		goto error;
	}
	error:	
		Tx_DMA_Reset(serial.huart);
		return false;
}
/*###############################################################*/
/*###############################################################* Display_Receive -->*/
/*###############################################################*/
//
static bool Display_Receive(uint8_t *data, uint32_t size)
{
	HAL_StatusTypeDef err;
	uint32_t tickstart = HAL_GetTick();
	uint32_t timeout = serial.rx_timeout;
	
	while((serial.huart->RxState != HAL_UART_STATE_READY)
		||(serial.huart->gState != HAL_UART_STATE_READY)
		||(serial.huart->hdmarx->Instance->NDTR != 0)
		||(serial.huart->hdmatx->Instance->NDTR != 0))
	{
		if(HAL_GetTick() - tickstart >= timeout){
			TERMINAL_DISPLAY_SET_ERROR(TERMINAL_PORT_ERROR_RX_TIMEOUT);
			return false;
		}
	}

	Receive_Enable();
	err = HAL_UART_Receive_DMA(serial.huart, buff.buff, size);
	if (err == HAL_OK)
	{
		tickstart = HAL_GetTick();
		while(serial.huart->hdmarx->Instance->NDTR != 0)
		{		
			if(HAL_GetTick() - tickstart >= timeout){
				uint32_t receive_size = size - serial.huart->hdmarx->Instance->NDTR;
				if (receive_size != size && receive_size > 0){
					DEBUG(("ERROR USART RECEIVE NOT ALL, %u BYTE \n", receive_size));
					debug_usart_receive(buff.buff, size);
				}
				memcpy(data, buff.buff, receive_size);
				TERMINAL_DISPLAY_SET_ERROR(TERMINAL_PORT_ERROR_RX_TIMEOUT);
				goto error;
			}
		}
		debug_usart_receive(buff.buff, size);
		memcpy(data, buff.buff, size);
		return true;
	}
	else
	{
		TERMINAL_DISPLAY_SET_ERROR(TERMINAL_PORT_ERROR_RX);
		DEBUG(("ERROR USART\r\n"));
		goto error;
	}	
error:	
		Rx_DMA_Reset(serial.huart);
		return false;	
}
#else
/*###############################################################*/
/*###############################################################* Display_Send -->*/
/*###############################################################*/
//send data via USART
static bool Display_Send(TERMINAL_HandleDisplayTypeDef *display, uint8_t *data, uint32_t size)
{
//	Transmit_Enable();
//	uint32_t timeout = serial_if.rx_timeout;
//	HAL_StatusTypeDef err = HAL_UART_Transmit(serial_if.huart, data, size, timeout);
//	if (err == HAL_OK)
//	{
//		return true;
//	}
//	else if (err == HAL_TIMEOUT)
//	{
//		TERMINAL_DISPLAY_SET_ERROR(TERMINAL_PORT_ERROR_TX_TIMEOUT);
//		__HAL_UART_CLEAR_OREFLAG(serial_if.huart);
//		return false;
//	}
//	else
//	{
//		TERMINAL_DISPLAY_SET_ERROR(TERMINAL_PORT_ERROR_TX);
//		DEBUG(("ERROR USART\r\n"));
//		return false;
//	}
	return true;
}
/*###############################################################*/
/*###############################################################* Display_Receive -->*/
/*###############################################################*/
//receive data via USART
static bool Display_Receive(TERMINAL_HandleDisplayTypeDef *display, uint8_t *data, uint32_t size)
{
//	Receive_Enable();
//	uint32_t timeout = serial_if.rx_timeout;
//	HAL_StatusTypeDef err = HAL_UART_Receive(serial_if.huart, data, size, timeout);
//	if (err == HAL_OK)
//	{
//		return true;
//	}
//	else if (err == HAL_TIMEOUT)
//	{
//		TERMINAL_DISPLAY_SET_ERROR(TERMINAL_PORT_ERROR_RX_TIMEOUT);
//		__HAL_UART_CLEAR_OREFLAG(boot_serial_if.huart);
//		return false;
//	}
//	else
//	{
//		TERMINAL_DISPLAY_SET_ERROR(TERMINAL_PORT_ERROR_RX);
//		DEBUG(("ERROR USART\r\n"));
//		return false;
//	}
	return true;
}
#endif /*TERMINAL_USE_DMA*/
#else
#endif /*DISPLAY_PORT_RS485*/


#ifdef TERMINAL_USE_WINDOWS
static void Transmit_Enable(void) {}
static void Receive_Enable(void) {}
/*###############################################################*/
/*###############################################################* HAL_GetTick -->*/
/*###############################################################*/
static uint32_t HAL_GetTick(void) {
	uint32_t result = GetTickCount();
	return result;
}
/*###############################################################*/
/*###############################################################* Display_Send -->*/
/*###############################################################*/
//
static bool Display_Send(TERMINAL_HandleDisplayTypeDef *display, uint8_t *data, uint32_t size)
{
	strcpy_s(display->display_string, (const char *)data);
	return true;
}
/*###############################################################*/
/*###############################################################* Display_Receive -->*/
/*###############################################################*/
//receive data via USART
static bool Display_Receive(TERMINAL_HandleDisplayTypeDef *display, uint8_t *data, uint32_t size)
{
	return true;
}
#endif //TERMINAL_USE_WINDOWS
/*###############################################################*/
/*###############################################################* Init -->*/
/*###############################################################*/
//initialize the module
static bool Init(void)
{
	strncpy(hdisplay.display_1->display_string, "    ", 4);
	strncpy(hdisplay.display_1->display_string_1, "    ", 4);
	strncpy(hdisplay.display_1->display_string_2, "    ", 4);
	hdisplay.display_1->status = TERMINAL_DISPLAY_STATUS_READY;
	hdisplay.display_1->error = TERMINAL_DISPLAY_ERROR_OK;
	hdisplay.display_1->command = TERMINAL_DISPLAY_STATUS_NULL;
	hdisplay.display_1->count = 0;

	strncpy(hdisplay.display_2->display_string, "    ", 4);
	strncpy(hdisplay.display_2->display_string_1, "    ", 4);
	strncpy(hdisplay.display_2->display_string_2, "    ", 4);
	hdisplay.display_2->status = TERMINAL_DISPLAY_STATUS_READY;
	hdisplay.display_2->error = TERMINAL_DISPLAY_ERROR_OK;
	hdisplay.display_2->command = TERMINAL_DISPLAY_STATUS_NULL;
	hdisplay.display_2->count = 0;
	return true;
}
/*###############################################################*/
/*###############################################################* Reset -->*/
/*###############################################################*/
//reset the module
static bool Reset(void)
{
	strncpy(hdisplay.display_1->display_string, "    ", 4);
	strncpy(hdisplay.display_2->display_string_1, "    ", 4);
	strncpy(hdisplay.display_2->display_string_2, "    ", 4);
	hdisplay.display_1->status = TERMINAL_DISPLAY_STATUS_READY;
	hdisplay.display_1->error = TERMINAL_DISPLAY_ERROR_OK;
	hdisplay.display_1->command = TERMINAL_DISPLAY_STATUS_NULL;

	strncpy(hdisplay.display_2->display_string, "    ", 4);
	strncpy(hdisplay.display_1->display_string_1, "    ", 4);
	strncpy(hdisplay.display_1->display_string_2, "    ", 4);
	hdisplay.display_2->status = TERMINAL_DISPLAY_STATUS_READY;
	hdisplay.display_2->error = TERMINAL_DISPLAY_ERROR_OK;
	hdisplay.display_2->command = TERMINAL_DISPLAY_STATUS_NULL;
	return true;
}
/*###############################################################*/
/*###############################################################* Reset_TickStart -->*/
/*###############################################################*/
//reset the module
static bool Reset_TickStart(void)
{
	hdisplay.tickstart = HAL_GetTick();
	return true;
}
/*###############################################################*/
/*###############################################################* Show_Ready -->*/
/*###############################################################*/
static void Show_Ready(void)
{
	if (hdisplay.command == TERMINAL_DISPLAY_STATUS_READY) {
		static bool fl_change = false;
		hdisplay.status = TERMINAL_DISPLAY_STATUS_READY;
		if (fl_change) Show((uint8_t *)"-_-_", (uint8_t *)"-_-_", hdisplay.status, hdisplay.timeout_state_ready);
		else Show((uint8_t *)"_-_-", (uint8_t *)"_-_-", hdisplay.status, hdisplay.timeout_state_ready);
		fl_change = !fl_change;
	}

	if ((hdisplay.command == TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED)||
		(hdisplay.command == TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED_REPLAY)) {
		hdisplay.status = hdisplay.command;
		Show((uint8_t *)"    ", NULL, hdisplay.status, 200);
		Show_Delate((uint8_t *)hdisplay.display_1->display_string_1, NULL, hdisplay.status, 2000);
		Show((uint8_t *)"    ", NULL, hdisplay.status, 200);
		Show_Delate((uint8_t *)hdisplay.display_1->display_string_2, NULL, hdisplay.status, 0xFFFFFFFF);
		hdisplay.status = TERMINAL_DISPLAY_STATUS_WAIT;
	}

	if ((hdisplay.command == TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED_WITH_CARD) ||
		(hdisplay.command == TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED_REPLAY_WITH_CARD)) {
		hdisplay.status = hdisplay.command;
		Show((uint8_t *)"    ", NULL, hdisplay.status, 200);
		Show_Delate((uint8_t *)hdisplay.display_1->display_string_1, NULL, hdisplay.status, 2000);
		Show((uint8_t *)"    ", NULL, hdisplay.status, 200);
		Show_Delate((uint8_t *)hdisplay.display_1->display_string_2, NULL, hdisplay.status, 0xFFFFFFFF);
		hdisplay.status = TERMINAL_DISPLAY_STATUS_WAIT;
	}


	if (hdisplay.command == TERMINAL_DISPLAY_STATUS_MONEY_TOTAL) {
		hdisplay.status = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
		Display_Send(hdisplay.display_1, (uint8_t *)hdisplay.display_1->display_string_1, 4);
		hdisplay.status = TERMINAL_DISPLAY_STATUS_WAIT;
	}

	if (hdisplay.command == TERMINAL_DISPLAY_STATUS_SPIT_OUT_CARDS) {
		hdisplay.status = TERMINAL_DISPLAY_STATUS_SPIT_OUT_CARDS;
		Show_Delate((uint8_t *)"----", NULL, TERMINAL_DISPLAY_STATUS_MONEY_TOTAL, 1000);
		Display_Send(hdisplay.display_1, (uint8_t *)hdisplay.display_1->display_string_1, 4);
		hdisplay.status = TERMINAL_DISPLAY_STATUS_WAIT;
	}

	if (hdisplay.command == TERMINAL_DISPLAY_STATUS_STRING) {
		hdisplay.status = TERMINAL_DISPLAY_STATUS_STRING;
		Display_Send(hdisplay.display_1, (uint8_t *)hdisplay.display_1->display_string_1, 4);
		hdisplay.status = TERMINAL_DISPLAY_STATUS_WAIT;
	}

	Delay(1);
}
/*###############################################################*/
/*###############################################################* Show_Delate -->*/
/*###############################################################*/
void Show_Delate(uint8_t *data_1, uint8_t *data_2, TERMINAL_DisplayStatusTypeDef cmd, uint32_t timeout)

{
	hdisplay.tickstart = HAL_GetTick();
	while (hdisplay.command == cmd) {
		if (timeout != NULL){
			if (HAL_GetTick() - hdisplay.tickstart >= timeout) {
				break;
			}
		}
		Display_Send(hdisplay.display_1, data_1, 4);
		if(data_2 != NULL) Display_Send(hdisplay.display_2, data_2, 4);
		Delay(1);
	}
}
/*###############################################################*/
/*###############################################################* Show -->*/
/*###############################################################*/
void Show(uint8_t *data_1, uint8_t *data_2, TERMINAL_DisplayStatusTypeDef cmd, uint32_t timeout)

{
	uint32_t tickstart = HAL_GetTick();
	while (hdisplay.command == cmd) {
		if (timeout != NULL) {
			if (HAL_GetTick() - tickstart >= timeout) {
				break;
			}
		}
		if (data_1 != NULL) Display_Send(hdisplay.display_1, data_1, 4);
		if (data_2 != NULL) Display_Send(hdisplay.display_2, data_2, 4);
		Delay(1);
	}
}
/*###############################################################*/
/*###############################################################* Show -->*/
/*###############################################################*/
void Show_Display_2(uint8_t *data, TERMINAL_DisplayStatusTypeDef cmd, uint32_t timeout)

{
	uint32_t tickstart = HAL_GetTick();
	while (hdisplay.display_2->command == cmd) {
		if (timeout != NULL) {
			if (HAL_GetTick() - tickstart >= timeout) {
				break;
			}
		}
		Display_Send(hdisplay.display_2, data, 4);
		Delay(1);
	}
}
/*###############################################################*/
/*###############################################################* Show -->*/
/*###############################################################*/
void Show_String(TERMINAL_HandleDisplayTypeDef *display, uint8_t *string, uint32_t timeout)

{
	display->command = TERMINAL_DISPLAY_STATUS_STRING;
	sprintf(display->display_string_1, "%s", string);

}
/*###############################################################*/
/*###############################################################* Display_1_Loop -->*/
/*###############################################################*/
//Display_1_Loop
static void Display_1_Loop(void const * argument)
{
	while (1) {
		Show_Ready();
		//if (WaitForSingleObject(hEvent_Display, 0) == WAIT_OBJECT_0) return;
	}

}


/*###############################################################*/
/*###############################################################* Display_2_Loop -->*/
/*###############################################################*/
//Display_2_Loop
static void Display_2_Loop(void const * argument)
{
	while (1) {

		if (hdisplay.command == TERMINAL_DISPLAY_STATUS_READY) {
			Delay(1);
			continue;
		}
		if (hdisplay_2.command == TERMINAL_DISPLAY_STATUS_READY) {
			static bool fl_change = false;
			if (fl_change) Show_Display_2((uint8_t *)"-_-_", hdisplay_2.status, hdisplay.timeout_state_ready);
			else Show_Display_2((uint8_t *)"_-_-", hdisplay_2.status, hdisplay.timeout_state_ready);
			fl_change = !fl_change;
		}

		if ((hdisplay_2.command == TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED) ||
			(hdisplay_2.command == TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED_REPLAY)) {
			hdisplay_2.status = hdisplay_2.command;
			Display_Send(&hdisplay_2, (uint8_t *)hdisplay_2.display_string_1, 4);
			hdisplay_2.status = TERMINAL_DISPLAY_STATUS_WAIT;
		}

		if ((hdisplay_2.command == TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED_WITH_CARD) ||
			(hdisplay_2.command == TERMINAL_DISPLAY_STATUS_COINS_ACCEPTED_REPLAY_WITH_CARD)) {
			hdisplay_2.status = hdisplay_2.command;
			Display_Send(&hdisplay_2, (uint8_t *)hdisplay_2.display_string_1, 4);
			hdisplay_2.status = TERMINAL_DISPLAY_STATUS_WAIT;
		}


		if (hdisplay_2.command == TERMINAL_DISPLAY_STATUS_MONEY_TOTAL) {
			hdisplay_2.status = TERMINAL_DISPLAY_STATUS_MONEY_TOTAL;
			Display_Send(&hdisplay_2, (uint8_t *)hdisplay_2.display_string_1, 4);
			hdisplay_2.status = TERMINAL_DISPLAY_STATUS_WAIT;
		}

		if (hdisplay_2.command == TERMINAL_DISPLAY_STATUS_SPIT_OUT_CARDS) {
			hdisplay_2.status = TERMINAL_DISPLAY_STATUS_SPIT_OUT_CARDS;
			Display_Send(&hdisplay_2, (uint8_t *)hdisplay_2.display_string_1, 4);
			hdisplay_2.status = TERMINAL_DISPLAY_STATUS_WAIT;
		}

		if (hdisplay_2.command == TERMINAL_DISPLAY_STATUS_STRING) {
			hdisplay_2.status = TERMINAL_DISPLAY_STATUS_STRING;
			Display_Send(&hdisplay_2, (uint8_t *)hdisplay_2.display_string_1, 4);
			hdisplay_2.status = TERMINAL_DISPLAY_STATUS_WAIT;
		}

		Delay(1);
	}

}
