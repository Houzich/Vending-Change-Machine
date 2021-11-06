/**
  ******************************************************************************
  * File Name          : Bill_Acceptor_MSP.c
  ******************************************************************************
  */
  /* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "main.h"
#include "Terminal/Terminal.h"
#include "Bill_Acceptor_MSP.h"
#include "Terminal_MSP.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"

#ifdef TERMINAL_USE_FREERTOS
#include "cmsis_os2.h"
#elif defined(TERMINAL_USE_WINDOWS)
#include "..\Threads.h"
#include <Windows.h>
#endif /*TERMINAL_USE_FREERTOS*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
//used when debugging, declared in the file Terminal.h
#ifdef DEBUG_TERMINAL_BILL_ACCEPTOR_MSP
#undef DEBUG /* DEBUG */
#undef DEBUG_PRINT /* DEBUG_PRINT */
#define DEBUG(x)			debug_print("BILL_ACCEPTOR MSP: ");  debug_print x;
#define DEBUG_PRINT(x)		debug_print x;
#else
#define DEBUG(x)
#define DEBUG_PRINT(x)
#endif // DEBUG_TERMINAL_BILL_ACCEPTOR_MSP

#define TIM_BILL_ACCEPTOR 20000
#define TIM_BILL_ACCEPTOR_SEC_PERIOD 5

 /* definition and creation of defaultTask */
  const osThreadAttr_t BillAcceptorMSPTask_attributes = {
    .name = "Bill_AcceptorMSPTask",
    .priority = (osPriority_t) osPriorityAboveNormal,
    .stack_size = 2048
  };
	osThreadId_t BillAcceptorMSP_TaskHandle;
	
	
	//TIMER
/* Timer handler declaration */
TIM_HandleTypeDef        BillAcceptorTimHandle;
/* Timer Input Capture Configuration Structure declaration */
TIM_IC_InitTypeDef       sConfig;
/* Slave configuration structure */
TIM_SlaveConfigTypeDef   sSlaveConfig;
#define MAX_RECEIVE_PULSES	100
	/* Captured Value */
__IO uint32_t            countPulse = 0;
/* Captured Value */
__IO uint32_t            pulseStartValue[MAX_RECEIVE_PULSES] = {0};
/* Captured Value */
__IO uint32_t            pulseEndValue[MAX_RECEIVE_PULSES] = {0};


bool fl_pulse = false;
	
/* Private variables ---------------------------------------------------------*/
TERMINAL_HandleBill_AcceptorMSPTypeDef bill;
osEventFlagsId_t Bill_Acceptor_MSP_Event_id;                        // event flags id
static BillMsgQueueTypeDef msg;

#define FLAG_CREDIT_RELAY_PIN_RISING			(uint64_t)(1<<0)
#define FLAG_CREDIT_RELAY_PIN_FALLING			(uint64_t)(1<<1)
#define FLAG_BILL_IN											(uint64_t)(1<<2)	
#define FLAG_RECEIVE_PULSE								(uint64_t)(1<<3)
#define TIMER_COUNTER_OVERFLOW						(uint64_t)(1<<4)
#define BILL_ACCEPTOR_INHIBIT_OFF					(uint64_t)(1<<5)
#define BILL_ACCEPTOR_INHIBIT_ON					(uint64_t)(1<<6)
#define FLAGS_MSK (uint64_t)(FLAG_CREDIT_RELAY_PIN_RISING|FLAG_CREDIT_RELAY_PIN_FALLING| \
														 FLAG_BILL_IN|FLAG_RECEIVE_PULSE|TIMER_COUNTER_OVERFLOW| \
                              BILL_ACCEPTOR_INHIBIT_OFF|BILL_ACCEPTOR_INHIBIT_ON  \
                              )
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
static void debug_pulses (int cnt);
static void Inhibit_On (void);
static void Inhibit_Off (void);

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

void Bill_Acceptor_MSP_Thread (void *argument)
{
	__IO uint32_t flags;
	Bill_Acceptor_MSP_Event_id = osEventFlagsNew(NULL);
  if (Bill_Acceptor_MSP_Event_id == NULL) {
    DEBUG(("Event Flags object not created, handle failure!!!\n")); // Event Flags object not created, handle failure
		for (;;);
	}
	for (;;) 
	{
		flags = osEventFlagsWait(Bill_Acceptor_MSP_Event_id, FLAGS_MSK, osFlagsWaitAny, osWaitForever);	
		Debug_Event_Flags_Error(flags);

		if(flags&FLAG_RECEIVE_PULSE){
			DEBUG(("Received an impulse from bill accepter, number: %d\n", countPulse));
		}		
		
		if(flags&TIMER_COUNTER_OVERFLOW){
      int cnt = msg.count_pulse;
      osMessageQueuePut(mid_BillMsgQueue, &msg, 0U, 0U);
      osThreadYield();
      debug_pulses(cnt);
      Inhibit_Off();
		}			
		
		if(flags&BILL_ACCEPTOR_INHIBIT_OFF){
      Inhibit_Off();            
    }
    
    if(flags&BILL_ACCEPTOR_INHIBIT_ON){
      Inhibit_On();            
    }
	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
		HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
		HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
		HAL_GPIO_TogglePin(LED_3_GPIO_Port, LED_3_Pin);
	if((countPulse != 0)&&(!fl_pulse)){
      msg.count_pulse = countPulse;
      countPulse = 0;
			osEventFlagsSet(Bill_Acceptor_MSP_Event_id, TIMER_COUNTER_OVERFLOW);
	} else {
		fl_pulse = false;
	}
}
/**
  * @brief  Input Capture callback in non blocking mode 
  * @param  htim: TIM IC handle
  * @retval None
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
  {
    Inhibit_On();
    /* Get the Input Capture value */
    pulseEndValue[countPulse] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
    /* Get the Input Capture value */
		pulseStartValue[countPulse] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
    countPulse++;
		if(countPulse >= MAX_RECEIVE_PULSES){
			countPulse = 0;
		}
		fl_pulse = true;
		osEventFlagsSet(Bill_Acceptor_MSP_Event_id, FLAG_RECEIVE_PULSE);
  }
  if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
  {
//		/* Get the Input Capture value */
//		pulseStartValue[countPulse] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
  }
  
  
}
/*###############################################################*/
/*###############################################################* Inhibit_On -->*/
/*###############################################################*/
static void Inhibit_On (void)
{
  //HAL_GPIO_WritePin(INHIBIT_GPIO_Port, INHIBIT_Pin, GPIO_PIN_SET);
}
/*###############################################################*/
/*###############################################################* Inhibit_Off -->*/
/*###############################################################*/
static void Inhibit_Off (void)
{
  //HAL_GPIO_WritePin(INHIBIT_GPIO_Port, INHIBIT_Pin, GPIO_PIN_RESET);
}


void Bill_Acceptor_MSP_TIM_Init(void){
	
	GPIO_InitTypeDef   GPIO_InitStruct;
 
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* TIMx Peripheral clock enable */
  TIM_CREDIT_RELAY_CLK_ENABLE();

  /*##-2- Configure the NVIC for TIMx #########################################*/
  /* Sets the priority grouping field */
  HAL_NVIC_SetPriority(TIM_CREDIT_RELAY_CC_IRQn, 0, 0);  
  /* Enable the TIM4 global Interrupt */
  HAL_NVIC_EnableIRQ(TIM_CREDIT_RELAY_CC_IRQn);
	
  /* Sets the priority grouping field */
  HAL_NVIC_SetPriority(TIM_CREDIT_RELAY_OVERLOAD_IRQn, 1, 0); 
  /* Enable the TIM4 global Interrupt */
  HAL_NVIC_EnableIRQ(TIM_CREDIT_RELAY_OVERLOAD_IRQn);	
	
  /*##-1- Configure the TIM peripheral #######################################*/ 
  /* Set TIMx instance */
  BillAcceptorTimHandle.Instance = TIM_CREDIT_RELAY;

  /* Initialize TIMx peripheral as follow:
       + Period = 0xFFFF
       + Prescaler = 0
       + ClockDivision = 0
       + Counter direction = Up
  */
	uint32_t apb1_tim_clock = Get_APB1_Timer_Clock();	
	uint32_t apb2_tim_clock = Get_APB2_Timer_Clock();
	//uint32_t period = 0xFFFF;
	uint32_t period = TIM_BILL_ACCEPTOR - 1;
	uint32_t prescaler = ((apb2_tim_clock / TIM_BILL_ACCEPTOR) - 1) * TIM_BILL_ACCEPTOR_SEC_PERIOD;	
  BillAcceptorTimHandle.Init.Period = period;
  BillAcceptorTimHandle.Init.Prescaler = prescaler;
  BillAcceptorTimHandle.Init.ClockDivision = 0;
  BillAcceptorTimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;  
  if(HAL_TIM_IC_Init(&BillAcceptorTimHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /*##-2- Configure the Input Capture channels ###############################*/ 
  /* Common configuration */
  sConfig.ICPrescaler = TIM_ICPSC_DIV1;
  sConfig.ICFilter = 15;  
  
  /* Configure the Input Capture of channel 1 */
  sConfig.ICPolarity = TIM_ICPOLARITY_FALLING;
  sConfig.ICSelection = TIM_ICSELECTION_INDIRECTTI;    
  if(HAL_TIM_IC_ConfigChannel(&BillAcceptorTimHandle, &sConfig, TIM_CHANNEL_1) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }
  
  /* Configure the Input Capture of channel 2 */
  sConfig.ICPolarity = TIM_ICPOLARITY_RISING;
  sConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;
  if(HAL_TIM_IC_ConfigChannel(&BillAcceptorTimHandle, &sConfig, TIM_CHANNEL_2) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }
  /*##-3- Configure the slave mode ###########################################*/
  /* Select the slave Mode: Reset Mode */
  sSlaveConfig.SlaveMode     = TIM_SLAVEMODE_RESET;
  sSlaveConfig.InputTrigger  = TIM_TS_TI2FP2;
  if(HAL_TIM_SlaveConfigSynchronization(&BillAcceptorTimHandle, &sSlaveConfig) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }
  
  /*##-4- Start the Input Capture in interrupt mode ##########################*/
  if(HAL_TIM_IC_Start_IT(&BillAcceptorTimHandle, TIM_CHANNEL_2) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
  
  /*##-5- Start the Input Capture in interrupt mode ##########################*/
  if(HAL_TIM_IC_Start_IT(&BillAcceptorTimHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
	
  if(HAL_TIM_Base_Start_IT(&BillAcceptorTimHandle) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }	
	
}


static void debug_pulses (int cnt){
#ifdef DEBUG_TERMINAL_BILL_ACCEPTOR_MSP
  DEBUG(("Received an impulses from bill accepter, quantity: %d\n", cnt));
  for (int i = 0; i < cnt; i++){
    int32_t duration = pulseEndValue[i] - pulseStartValue[i];
    duration = (duration * TIM_BILL_ACCEPTOR_SEC_PERIOD)/TIM_BILL_ACCEPTOR;
    DEBUG_PRINT(("Impulse %d, duration %d ms\n", i, duration));
  }
#endif 
}

void Bill_Acceptor_MspInit(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};	
	
#if (CREDIT_RELAY_Pin_En)
	GPIO_InitStruct.Pin = CREDIT_RELAY_Pin;
	
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Alternate = GPIO_AF_TIM_CREDIT_RELAY;
	
	//GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(CREDIT_RELAY_GPIO_Port, &GPIO_InitStruct);
	
#endif	

#if (INHIBIT_Pin_En)
	HAL_GPIO_WritePin(INHIBIT_GPIO_Port,INHIBIT_Pin, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = INHIBIT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(INHIBIT_GPIO_Port, &GPIO_InitStruct);
#endif


//#if (CREDIT_RELAY_IRQ_En)
//  /* Enable and set EXTI Line Interrupt to the lowest priority */
//  HAL_NVIC_SetPriority(CREDIT_RELAY_IRQ, 2, 0);
//  HAL_NVIC_EnableIRQ(CREDIT_RELAY_IRQ);
//#endif	

}

/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void Bill_Acceptor_GPIO_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == CREDIT_RELAY_Pin)
	{
		if(HAL_GPIO_ReadPin(CREDIT_RELAY_GPIO_Port,CREDIT_RELAY_Pin) == GPIO_PIN_RESET){
			bill.credit_relay_pin = GPIO_PIN_SET;
			bill.credit_relay_pin_exti = TERMINAL_EXTI_FALLING;
			osEventFlagsSet(Bill_Acceptor_MSP_Event_id, FLAG_CREDIT_RELAY_PIN_FALLING);
		}
		else{	
			bill.credit_relay_pin = GPIO_PIN_RESET;
			bill.credit_relay_pin_exti = TERMINAL_EXTI_RISING;
			osEventFlagsSet(Bill_Acceptor_MSP_Event_id, FLAG_CREDIT_RELAY_PIN_RISING);
		}
	}
}