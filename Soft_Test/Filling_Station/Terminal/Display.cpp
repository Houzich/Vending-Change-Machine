/**
  ******************************************************************************
  * File Name          : Display.c
  ******************************************************************************
  */
  /* Includes ------------------------------------------------------------------*/

#include <string.h>
#include <stdbool.h>
#include "Terminal/Terminal.h"
#include "Terminal/Display.h"
#include "cmsis_os2.h"
#ifdef TERMINAL_USE_STM
#include "stm32f4xx.h"
#include "TCP_Client.h"
#include "Driver_USART.h"
#include "Modbus_CRC.h"
#endif /*TERMINAL_USE_STM*/

#ifdef DISPLAY_PORT_RS485
static ARM_DRIVER_USART* USARTdrv;
/* USART Driver */
extern ARM_DRIVER_USART Driver_USART2;
#endif // DISPLAY_PORT_RS485

namespace DisplayNS
{
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#undef TERMINAL_DISPLAY_DATA_DEBUG
//#define TERMINAL_DISPLAY_DATA_DEBUG
/* Private macro -------------------------------------------------------------*/
#ifdef DEBUG_TERMINAL_DISPLAY
#undef DEBUG
#define DEBUG(...)		do {debug_header("DISPLAY: ", __VA_ARGS__);} while (0)
#define DEBUG_PRINT(...)		    do {debug_print(__VA_ARGS__);} while (0)

#else
#define DEBUG(...)
#define DEBUG_PRINT(...)
#endif // DEBUG_TERMINAL_DISPLAY

/* Private function prototypes -----------------------------------------------*/
#ifdef DISPLAY_PORT_ETH  
static bool Display_Send_ETH(DisplayMSPClass* display, uint8_t* data);
#endif //DISPLAY_PORT_ETH  
/* Exported functions --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


	// declare the structure of the module, initialize the initial values
	// set links to module functions
	DisplayClass Displays;
	/*###############################################################*/
	/*###############################################################* debug_usart_send -->*/
	/*###############################################################*/
	static void debug_usart_send(uint8_t* data, uint32_t size)
	{
#ifdef TERMINAL_DISPLAY_DATA_DEBUG
		DEBUG_PRINT("SLAVE SEND %u BYTES: ", size);
		for (int i = 0; i < size; i++)
		{
			DEBUG_PRINT("%02X ", data[i]);
		}
		DEBUG_PRINT("\n");
#endif // TERMINAL_DISPLAY_DATA_DEBUG
	}
	/*###############################################################*/
	/*###############################################################* debug_usart_receive -->*/
	/*###############################################################*/
	static void debug_usart_receive(uint8_t* data, uint32_t size)
	{
#ifdef TERMINAL_DISPLAY_DATA_DEBUG
		DEBUG_PRINT("SLAVE RECEIVE %u BYTES: ", size);
		for (int i = 0; i < size; i++)
		{
			DEBUG_PRINT("%02X ", data[i]);
		}
		DEBUG_PRINT("\n");
#endif // TERMINAL_DISPLAY_DATA_DEBUG
	}
	/*###############################################################*/
	/*###############################################################* Transmit_Enable -->*/
	/*###############################################################*/
	//set pin for transmit via rs485
	static void Transmit_Enable(void)
	{
#ifdef TERMINAL_TEST
		Slave_Transmit_Enable = true;
		Slave_Receive_Enable = false;
		if (Master_Transmit_Enable) {
			DEBUG_PRINT("BOOT SLAVE: ERROR RS485 CONFLICT TRANSMITTERS!!!!!! \r\n\r\n");
		}
#endif // TERMINAL_TEST
#ifdef DISPLAY_PORT_RS485		
		HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, GPIO_PIN_SET);
#endif // DISPLAY_PORT_RS485 
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
#ifdef DISPLAY_PORT_RS485	
		HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, GPIO_PIN_RESET);
#endif // DISPLAY_PORT_RS485 

	}

#ifdef DISPLAY_PORT_RS485
	/*###############################################################*/
	/*###############################################################* RxTx_Pin_Init -->*/
	/*###############################################################*/
	static void RxTx_Pin_Init(void)
	{
		GPIO_InitTypeDef GPIO_InitStruct = { 0 };

		/*Configure GPIO pins : RS485_EN_Pin */
		GPIO_InitStruct.Pin = RS485_EN_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(RS485_EN_GPIO_Port, &GPIO_InitStruct);
	}

  bool DisplayClass::Display_Send(DisplayMSPClass* display, const char* data)
	{
		uint8_t buff[30];
		uint32_t     flags;

		flags = osThreadFlagsClear(0x0001U);

		buff[0] = 0x01; //адрес
		buff[1] = 0x10; //функция
		buff[2] = 0x00; //функция
		buff[3] = 0x1D; //номер первого регистра
		buff[4] = 0x00; //номер первого регистра
		buff[5] = 0x04; //количество регистров
		buff[6] = 0x08; //количество байт

	  //  buff[7] = 0x31; //данные
	  //  buff[8] = 0x2E; //данные
	  //  buff[9] = 0x32; //данные
	  //  buff[10] = 0x2E; //данные
	  //  buff[11] = 0x33; //данные
	  //  buff[12] = 0x00; //данные
	  //  buff[13] = 0x34; //данные
	  //  buff[14] = 0x2E; //данные
		int count = 0;
		buff[7] = data[count++]; //данные
		if ((data[count] == '.') || (data[count] == ',')) {
			buff[8] = 0x2E; count++;
		}
		else buff[8] = 0x00;

		buff[9] = data[count++];; //данные
		if ((data[count] == '.') || (data[count] == ',')) {
			buff[10] = 0x2E;  count++;
		}
		else buff[10] = 0x00;

		buff[11] = data[count++];; //данные
		if ((data[count] == '.') || (data[count] == ',')) {
			buff[12] = 0x2E;  count++;
		}
		else buff[12] = 0x00;

		buff[13] = data[count++];; //данные
		if ((data[count] == '.') || (data[count] == ',')) {
			buff[14] = 0x2E;  count++;
		}
		else buff[14] = 0x00;


		*(uint16_t*)(&buff[15]) = Modbus_CRC16(buff, 15);

		Transmit_Enable();
		USARTdrv->Send((const void*)buff, 17);
		flags = osThreadFlagsWait(0x0001U, osFlagsWaitAny, osWaitForever);
		//Delay(1000);
#ifdef DISPLAY_PORT_ETH  
		Display_Send_ETH(display, (uint8_t*)data);
#endif //DISPLAY_PORT_ETH  
		return true;
	}

	/*###############################################################*/
	/*###############################################################* Display_Send -->*/
	/*###############################################################*/
	bool DisplayClass::Display_Send(DisplayMSPClass* disp, int money)
	{
		char str[10];
		float money_f = (float)money / 100.0f;
		snprintf(str, 6, "%5.2f", money_f);
		for (int i = 0; i < 5; i++)
			if (str[i] == ' ')
				str[i] = '0';
		Display_Send(disp, str);
		return true;
	}  
  
#endif //DISPLAY_PORT_RS485

#ifdef DISPLAY_PORT_ETH
	/*###############################################################*/
	/*###############################################################* Display_Send -->*/
	/*###############################################################*/
	//send data via ETH
	static bool Display_Send_ETH(DisplayMSPClass* display, uint8_t* data)
	{
		netStatus net_status;
		osStatus_t val = osOK;
		int len = 0;
#ifdef TERMINAL_USE_TCP_SEMAPHORE
		if (sid_ETH_Display_Semaphore == NULL) return false;
		val = TCPClientSemaphoreAcquire(sid_ETH_Display_Semaphore, osWaitForever);
#endif // TERMINAL_USE_TCP_SEMAPHORE
		DisplayBuf = NULL;

		for (int i = 0; i < 30; i++) {
			if (tcp_display_sock < 0) goto EXIT;
			if (netTCP_GetState(tcp_display_sock) != netTCP_StateESTABLISHED) goto EXIT;
			if (netTCP_SendReady(tcp_display_sock) == true) {
				DisplayBuf = netTCP_GetBuffer(30);
				break;
			}
			else {
				osDelay(1);
			}
		}

		if (DisplayBuf == NULL) {
			goto EXIT;
		}
		memset(DisplayBuf, 0, 30);
		if (display == &Displays.Display_1)
			strncpy((char*)&DisplayBuf[0], "DISPL_1:", 8);
		else
			strncpy((char*)&DisplayBuf[0], "DISPL_2:", 8);

		strncpy((char*)&DisplayBuf[8], (const char*)data, 20);
		len = strlen((const char*)DisplayBuf);
		switch (val) {
		case osOK:
			//send the data
			while (netTCP_SendReady(tcp_display_sock) != true) {
				if (tcp_display_sock < 0) goto EXIT;
				if (netTCP_GetState(tcp_display_sock) != netTCP_StateESTABLISHED) goto EXIT;
				osDelay(10);
			}

			if (DisplayBuf != NULL) {
				if ((len + 1) >= 30) {
					while (1) DEBUG_PRINT("ERROR DISPLAY SEND ETH!!!\n");
				}
				net_status = netTCP_Send(tcp_display_sock, DisplayBuf, len + 1);
				if (net_status < 0) {
					//debug_net_status_printf(net_status, "Send Error: ");
				}
			}
			break;
		case osErrorResource:
			DEBUG_PRINT("Display Semaphore Error: osErrorResource!!!\n");
			break;
		case osErrorParameter:
			DEBUG_PRINT("Display Semaphore Error: osErrorParameter!!!\n");
			break;
		default:break;
		}


		TCPClientSemaphoreRelease(sid_ETH_Display_Semaphore);              // return a token back to a semaphore
		return true;
	EXIT:
		TCPClientSemaphoreRelease(sid_ETH_Display_Semaphore);
		osThreadYield();
		return false;
	}
#endif //DISPLAY_PORT_ETH


#ifdef TERMINAL_USE_WINDOWS
	/*###############################################################*/
	/*###############################################################* HAL_GetTick -->*/
	/*###############################################################*/
	static uint32_t HAL_GetTick(void) {
		using namespace std::chrono;
		uint32_t ms = (uint32_t)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		return ms;
	}
	/*###############################################################*/
	/*###############################################################* Display_Send -->*/
	/*###############################################################*/
	bool DisplayClass::Display_Send(DisplayMSPClass* disp, const char* data)
	{
		strcpy_s(disp->display_string, data);
		return true;
	}
	/*###############################################################*/
	/*###############################################################* Display_Send -->*/
	/*###############################################################*/
	bool DisplayClass::Display_Send(DisplayMSPClass* disp, int money)
	{
		char str[10];
		float money_f = (float)money / 100.0f;
		snprintf(str, 6, "%5.2f", money_f);
		for (int i = 0; i < 5; i++)
			if (str[i] == ' ')
				str[i] = '0';
		snprintf(disp->display_string, 6, "%s", str);
		return true;
	}
#endif //TERMINAL_USE_WINDOWS

#ifdef DISPLAY_PORT_RS485
	static void USART_Display_Callback(uint32_t event)
	{
		uint32_t mask;
		//  mask = ARM_USART_EVENT_RECEIVE_COMPLETE  |
		//         ARM_USART_EVENT_TRANSFER_COMPLETE |
		//         ARM_USART_EVENT_SEND_COMPLETE     |
		//         ARM_USART_EVENT_TX_COMPLETE       ;

		mask = ARM_USART_EVENT_TRANSFER_COMPLETE |
			ARM_USART_EVENT_TX_COMPLETE;

		if (event & mask) {
			/* Success: Wakeup Thread */
			osThreadFlagsSet(Display1_TaskHandle, 0x0001U);
			//osThreadFlagsSet(Display2Task_TaskHandle, 0x0001U);
		}
		//  if (event & ARM_USART_EVENT_RECEIVE_COMPLETE) {
		//    //prvvUARTRxISR();
		//  }
		//  if (event & ARM_USART_EVENT_TRANSFER_COMPLETE) {
		//    //prvvUARTTxReadyISR();
		//  }
		//  if (event & ARM_USART_EVENT_RX_TIMEOUT) {
		//    __breakpoint(0);  /* Error: Call debugger or replace with custom error handling */
		//  }
		//  if (event & (ARM_USART_EVENT_RX_OVERFLOW | ARM_USART_EVENT_TX_UNDERFLOW)) {
		//    __breakpoint(0);  /* Error: Call debugger or replace with custom error handling */
		//  }
	}
#endif //DISPLAY_PORT_RS485

  DisplayClass::DisplayClass(){
    
    
  }
  
  void DisplayMSPClass::Init()
  {
    #ifdef TERMINAL_USE_STM
    Messages.queue_in = osMessageQueueNew(100, sizeof(Messages.message), NULL);
    Messages.queue_out = osMessageQueueNew(10, sizeof(Messages.message), NULL);
    
    if (Messages.queue_in == NULL) {
      DEBUG_PRINT("Queue object not created, handle failure!!!\n");
      for(;;);
    }
    if (Messages.queue_out == NULL) {
      DEBUG_PRINT("Queue object not created, handle failure!!!\n");
      for(;;);
    }    
    #endif /*TERMINAL_USE_STM*/
  }

  /*###############################################################*/
  /*###############################################################* Init -->*/
  /*###############################################################*/
  //initialize the module
  void DisplayClass::Init()
  {
    Display_1.Init();    
  #ifdef DISPLAY_PORT_RS485
    RxTx_Pin_Init();
    USARTdrv = &Driver_USART2;
    /*Initialize the USART driver */
    USARTdrv->Initialize(USART_Display_Callback);
    /*Power up the USART peripheral */
    USARTdrv->PowerControl(ARM_POWER_FULL);
    /*Configure the USART to 115200 Bits/sec */
    USARTdrv->Control(ARM_USART_MODE_ASYNCHRONOUS |
      ARM_USART_DATA_BITS_8 |
      ARM_USART_PARITY_EVEN |
      ARM_USART_STOP_BITS_1 |
      ARM_USART_FLOW_CONTROL_NONE, 115200);

    /* Enable Receiver and Transmitter lines */
    USARTdrv->Control(ARM_USART_CONTROL_TX, 1);
    //USARTdrv->Control(ARM_USART_CONTROL_RX, 1);
  #endif //DISPLAY_PORT_RS485
  }
	/*###############################################################*/
	/*###############################################################* Display_1_Thread -->*/
	/*###############################################################*/
	void DisplayClass::Display_1_Thread(void* arg)
	{
		static MessageClass msg;
		osStatus_t status;
		status = Displays.Display_1.Messages.popMessageIn(&msg, osWaitForever);
		while (1) {
			if (msg.command == READY) {
				bool fl_change = false;
				while (true)
				{
					if (fl_change) Displays.Display_Send(&Displays.Display_1, "-_-_");
					else Displays.Display_Send(&Displays.Display_1, "_-_-");
					fl_change = !fl_change;

					status = Displays.Display_1.Messages.popMessageIn(&msg, 500);
					if (status == osOK) break;
				}
			}

			if (msg.command == MONEY)
			{
				int money = msg.money;
				while (true)
				{
					Displays.Display_Send(&Displays.Display_1, money);
					status = Displays.Display_1.Messages.popMessageIn(&msg, 500);
					if (status == osOK) break;
				}
			}

			if (msg.command == SPIT_OUT_MONEY)
			{
				while (true)
				{
					Displays.Display_Send(&Displays.Display_1, "----");
					status = Displays.Display_1.Messages.popMessageIn(&msg, 500);
					if (status == osOK) break;
				}
			}

			if (msg.command == STRING_ERROR)
			{
				while (true)
				{
					Displays.Display_Send(&Displays.Display_1, "Err ");
					status = Displays.Display_1.Messages.popMessageIn(&msg, 1500);
					if (status == osOK) break;
				}
			}
      
      if (msg.command == STRING)
			{
				while (true)
				{
					Displays.Display_Send(&Displays.Display_1, Displays.Display_1.display_string);
					status = Displays.Display_1.Messages.popMessageIn(&msg, 500);
					if (status == osOK) break;
				}
			}
      
		}
	}
}	//DisplayNameSpace
/************************ (C) COPYRIGHT *****END OF FILE****/