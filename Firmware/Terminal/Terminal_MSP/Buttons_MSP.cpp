/**
  ******************************************************************************
  * File Name          : Buttons.c
  ******************************************************************************
  */
  /* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "Terminal/Terminal.h"
#include "Buttons_MSP.h"
#include "stm32f4xx_hal.h"

#ifdef TERMINAL_USE_STM
#include "cmsis_os2.h"
#elif defined(TERMINAL_USE_WINDOWS)
#endif /*TERMINAL_USE_STM*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
//used when debugging, declared in the file Terminal.h
#ifdef DEBUG_TERMINAL_BUTTONS_MSP
#undef DEBUG /* DEBUG */
#undef DEBUG_PRINT /* DEBUG_PRINT */
#define DEBUG(...)		do { debug_header("BUTTONS MSP: ", __VA_ARGS__); } while (0)
#define DEBUG_PRINT(x)		debug_print x;
#else
#define DEBUG(...)
#define DEBUG_PRINT(x)
#endif // DEBUG_TERMINAL_HOPPER_MSP

#define BUTTONS_FLAGS_MSK (uint64_t)(EventButtonsMSP::BUTTON_ENCASHMENT_PIN_RISING|EventButtonsMSP::BUTTON_ENCASHMENT_PIN_FALLING| \
                             EventButtonsMSP::BUTTON_ENCASHMENT_PIN_NOISE)

/* Private variables ---------------------------------------------------------*/
 /* definition and creation of defaultTask */
uint64_t buttonsmsp_stk[2048 / 8];
const osThreadAttr_t ButtonsMSPTask_attributes = {
  .name = "ButtonsMSPTask",
  .stack_mem = &buttonsmsp_stk[0],
  .stack_size = sizeof(buttonsmsp_stk),
  .priority = (osPriority_t)osPriorityAboveNormal,
};
osThreadId_t ButtonsMSP_TaskHandle;


TERMINAL_HandleButtonsMSPTypeDef buttons = {
  BUTTON_ENCASHMENT_Pin,
  BUTTON_ENCASHMENT_Port,
};
osEventFlagsId_t Buttons_MSP_Event_ID;                        // event flags id


/* Private function prototypes -----------------------------------------------*/
void Buttons_MSP_Read_Pins(void);

/* Exported functions --------------------------------------------------------*/

void Buttons_GPIO_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

#define INIT_BUTTONS_PIN(port, pin) \
	GPIO_InitStruct.Pin = pin; \
	HAL_GPIO_Init(port, &GPIO_InitStruct);  	
	
  buttons.exti[BUTTON_ENCASHMENT] = TERMINAL_EXTI_NONE;
	INIT_BUTTONS_PIN(buttons.port[BUTTON_ENCASHMENT], buttons.pin[BUTTON_ENCASHMENT])  
  Buttons_MSP_Read_Pins();
}

namespace ButtonsNS
{
  ButtonsMSPClass Buttons;
  
void ButtonsMSPClass::Init(){
	Buttons_MSP_Event_ID = osEventFlagsNew(NULL);
	if (Buttons_MSP_Event_ID == NULL) {
		DEBUG("Event Flags object not created, handle failure!!!\n"); // Event Flags object not created, handle failure
		for (;;);
	}
  
  #ifdef TERMINAL_USE_STM
  Messages.queue_in = osMessageQueueNew(100, sizeof(Messages.message), NULL);
  Messages.queue_out = osMessageQueueNew(100, sizeof(Messages.message), NULL);
  
  if (Messages.queue_in == NULL) {
    DEBUG("Queue object not created, handle failure!!!\n");
    for(;;);
  }
  if (Messages.queue_out == NULL) {
    DEBUG("Queue object not created, handle failure!!!\n");
    for(;;);
  }    
  #endif /*TERMINAL_USE_STM*/
  Buttons_GPIO_MspInit();
}


void ButtonsMSPClass::Buttons_MSP_Thread(void* arg)
{
	uint32_t flags;
	GPIO_PinState state;
  static MessageClass msg;
	
	for (;;)
	{
		//osThreadYield();
		osDelay(1);	
		
	for(int i = 0; i < NUM_BUTTONS; i++)
  {
      state = HAL_GPIO_ReadPin(buttons.port[i], buttons.pin[i]);
      if (state == buttons.state[i])
      {
        //it means there is noise
        //PIN_NOISE
        //osEventFlagsSet(Buttons_MSP_Event_ID, (1<<(NUM_BUTTONS*2 + i)));
      } else {
       if (state == GPIO_PIN_RESET) {
          buttons.exti[i] = TERMINAL_EXTI_FALLING;
         //PIN_FALLING
          osEventFlagsSet(Buttons_MSP_Event_ID, (1<<(NUM_BUTTONS + i)));
        } else {
          buttons.exti[i] = TERMINAL_EXTI_RISING;
          //PIN_RISING
          osEventFlagsSet(Buttons_MSP_Event_ID, (1<<i));
          
        }
        buttons.state[i] = state;
      }
  } 
		
			
  osStatus_t status;
  flags = osEventFlagsWait(Buttons_MSP_Event_ID, BUTTONS_FLAGS_MSK, osFlagsWaitAny, 0U);
  if (Check_CMSIS_Flags_Functions_Error_Codes(flags) == 0) {
    
    if(flags&EventButtonsMSP::BUTTON_ENCASHMENT_PIN_RISING){
      DEBUG("NOISE ON LINE BUTTONS_ENCASHMENT_Pin, RISING\n");	
    }
//_____________________________________
    if(flags&EventButtonsMSP::BUTTON_ENCASHMENT_PIN_FALLING){
      DEBUG("EVENT ON LINE BUTTONS_ENCASHMENT_Pin, FALLING\n");
      osDelay(5);
      state = HAL_GPIO_ReadPin(buttons.port[BUTTON_ENCASHMENT], buttons.pin[BUTTON_ENCASHMENT]);
      if (state == buttons.state[BUTTON_ENCASHMENT]){
        msg.command = RESET;
        Buttons.Messages.pushMessageOut(&msg);
      }         
    }

    if(flags&EventButtonsMSP::BUTTON_ENCASHMENT_PIN_NOISE){
      DEBUG("NOISE ON LINE BUTTONS_ENCASHMENT_Pin, NOISE\n");	
    }      
    
  }
}
  
}
} //ButtonsNS
void Buttons_MSP_Read_Pins(void) {
  //Buttons_GPIO_Input_MspInit();  
  
  for(int i = 0; i < NUM_BUTTONS; i++)
  {
    buttons.state[i] = HAL_GPIO_ReadPin(buttons.port[i], buttons.pin[i]);
  }
  
  DEBUG(
  "READ BUTTONS PIN:\n"
  "ENCASHMENT is %d\n",
    buttons.state[BUTTON_ENCASHMENT]
  );
  
}



