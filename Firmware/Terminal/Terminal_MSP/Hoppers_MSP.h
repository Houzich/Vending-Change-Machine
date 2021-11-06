/**
  ******************************************************************************
  * File Name          : Hoppers_MSP.h
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_HOPPERS_MSP_H
#define __TERMINAL_HOPPERS_MSP_H

enum EventHopperMSP{
  INHIBIT_PIN_RISING = (1<<0),
  METER_PIN_RISING = (1<<1),
  CREDIT_PIN_RISING = (1<<2),
  COIN_EMPTY_PIN_RISING = (1<<3),
  PAYOUT_PIN_RISING = (1<<4),
  INHIBIT_PIN_FALLING = (1<<5),
  METER_PIN_FALLING = (1<<6),
  CREDIT_PIN_FALLING = (1<<7),
  COIN_EMPTY_PIN_FALLING = (1<<8),
  PAYOUT_PIN_FALLING = (1<<9),
  COIN_OUT = (1<<10),
  INHIBIT_PIN_NOISE = (1<<11),
  METER_PIN_NOISE = (1<<12),
  CREDIT_PIN_NOISE = (1<<13),
  COIN_EMPTY_PIN_NOISE = (1<<14),
  GET_PINS_STATE = (1<<15),
};


#define HOPPER_FLAGS_MSK (uint64_t)(EventHopperMSP::INHIBIT_PIN_RISING|EventHopperMSP::METER_PIN_RISING| \
														 EventHopperMSP::CREDIT_PIN_RISING|EventHopperMSP::COIN_EMPTY_PIN_RISING| \
														 EventHopperMSP::INHIBIT_PIN_FALLING|EventHopperMSP::METER_PIN_FALLING| \
														 EventHopperMSP::CREDIT_PIN_FALLING|EventHopperMSP::COIN_EMPTY_PIN_FALLING| \
                             EventHopperMSP::INHIBIT_PIN_NOISE|EventHopperMSP::METER_PIN_NOISE| \
                             EventHopperMSP::CREDIT_PIN_NOISE|EventHopperMSP::COIN_EMPTY_PIN_NOISE| \
														 EventHopperMSP::COIN_OUT|EventHopperMSP::GET_PINS_STATE)

#define HOPPER_MSP_PINS_FLAGS_MSK (uint64_t)(EventHopperMSP::INHIBIT_PIN_RISING|EventHopperMSP::METER_PIN_RISING| \
														 EventHopperMSP::CREDIT_PIN_RISING|EventHopperMSP::COIN_EMPTY_PIN_RISING| \
														 EventHopperMSP::INHIBIT_PIN_FALLING|EventHopperMSP::METER_PIN_FALLING| \
														 EventHopperMSP::CREDIT_PIN_FALLING|EventHopperMSP::COIN_EMPTY_PIN_FALLING)

#define HOPPER_MSP_PINS_RESPONCE_FLAGS_MSK (uint64_t)(EventHopperMSP::CREDIT_PIN_FALLING|EventHopperMSP::CREDIT_PIN_RISING| \
                                                        EventHopperMSP::METER_PIN_FALLING|EventHopperMSP::METER_PIN_RISING)

#define COIN_EMPTY_NORMAL_STATE GPIO_PIN_SET
#define INHIBIT_NORMAL_STATE GPIO_PIN_SET
#define CREDIT_NORMAL_STATE GPIO_PIN_RESET



/* Includes ------------------------------------------------------------------*/
namespace HoppersMSPNS
{

	enum COMMAND {
		SPLIT_OUT_HOPPER_1 = 0x01,
		SPLIT_OUT_HOPPER_2 = 0x02,
	};

	struct MessageClass
	{
		COMMAND command;
		uint32_t pulses;
	};


	class HoppersMSPClass
	{
	public:
		QueueMessageClass< MessageClass, 10 > Messages;
	public:
		HoppersMSPClass();
    void Init();
		static void Hoppers_MSP_Thread(void* arg);
	};
  
	extern HoppersMSPClass HoppersMSP;

  extern const osThreadAttr_t HoppersMSPTask_attributes;
  extern osThreadId_t HoppersMSP_TaskHandle;
}
/* Exported constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#endif /*__TERMINAL_HOPPERS_MSP_H*/
