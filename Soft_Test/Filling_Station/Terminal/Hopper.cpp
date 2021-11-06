/**
  ******************************************************************************
  * File Name          : Hopper.c
  ******************************************************************************
  */
  /* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "Terminal/Terminal.h"

#ifdef TERMINAL_USE_STM
#include "cmsis_os2.h"
#elif defined(TERMINAL_USE_WINDOWS)

#endif /*TERMINAL_USE_STM*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
//used when debugging, declared in the file Terminal.h
#ifdef DEBUG_TERMINAL_HOPPER
#undef DEBUG /* DEBUG */
#undef DEBUG_PRINT /* DEBUG_PRINT */
#define DEBUG(...)		do {debug_header("HOPPER: ", __VA_ARGS__);} while (0)
#define DEBUG_PRINT(x)		debug_print x;
#else
#define DEBUG(...)
#define DEBUG_PRINT(x)
#endif // DEBUG_TERMINAL_HOPPER

namespace HoppersNS
{
	HopperCoreClass Hoppers;
	HopperClass::HopperClass() {

	}
  void HopperClass::Init()
	{
    #ifdef TERMINAL_USE_STM
    Messages.queue_in = osMessageQueueNew(100, sizeof(Messages.message), NULL);
    Messages.queue_out = osMessageQueueNew(100, sizeof(Messages.message), NULL);
    #endif /*TERMINAL_USE_STM*/
  } 
  void HopperCoreClass::Init()
	{
    Hopper_1.Init();
    Hopper_2.Init();  

    #ifdef TERMINAL_USE_STM
    Hopper1MSPNS::hopper_1_msp.Init();
    Hopper2MSPNS::hopper_2_msp.Init();
    HoppersMSPNS::HoppersMSP.Init();
    Messages.queue_in = osMessageQueueNew(100, sizeof(Messages.message), NULL);
    Messages.queue_out = osMessageQueueNew(100, sizeof(Messages.message), NULL);
    #endif /*TERMINAL_USE_STM*/
  } 
  
bool HopperCoreClass::isAlarm() {
#ifdef TERMINAL_USE_STM
  return ((Hopper1MSPNS::hopper_1_msp.isAlarm())||(Hopper2MSPNS::hopper_2_msp.isAlarm()));
#else
	return 0;
#endif /*TERMINAL_USE_STM*/
}  
  
  
	/*###############################################################*/
	/*###############################################################* Split_Out -->*/
	/*###############################################################*/
	int HopperClass::Split_Out() {
    int coins = money_for_out / value_of_coins;
    if(num == 1){
#ifdef TERMINAL_USE_STM
      Hopper1MSPNS::MessageClass msg;
      msg.command = Hopper1MSPNS::SPIT_OUT;
		  msg.coins = coins;
      Hopper1MSPNS::hopper_1_msp.Messages.pushMessageIn(&msg);
      Hopper1MSPNS::hopper_1_msp.Messages.popMessageOut(&msg, osWaitForever);
      coins = msg.coins;
#endif /*TERMINAL_USE_STM*/
    }
    if(num == 2){
#ifdef TERMINAL_USE_STM
      Hopper2MSPNS::MessageClass msg;
      msg.command = Hopper2MSPNS::SPIT_OUT;
		  msg.coins = coins;
      Hopper2MSPNS::hopper_2_msp.Messages.pushMessageIn(&msg);
      Hopper2MSPNS::hopper_2_msp.Messages.popMessageOut(&msg, osWaitForever);
      coins = msg.coins;
#endif /*TERMINAL_USE_STM*/
    }
		return coins * value_of_coins;
	}


	HopperCoreClass::HopperCoreClass() {
		Hopper_1.value_of_coins = 100;
		Hopper_2.value_of_coins = 200;
		Hopper_1.num = 1;
		Hopper_2.num = 2;
	}
	/*###############################################################*/
	/*###############################################################* Two_Hoppers_Split_Out -->*/
	/*###############################################################*/
	int HopperCoreClass::Two_Hoppers_Split_Out(uint32_t money_out) {

		Calculate_Proportion(money_out);

		HopperClass* hopper_first;
		HopperClass* hopper_second;
		uint32_t money_left;
		//Сначала всегда выдаем большие монеты
		if (Hopper_1.value_of_coins > Hopper_2.value_of_coins)
		{
			hopper_first = &Hopper_1; hopper_second = &Hopper_2;
		}
		else
		{
			hopper_first = &Hopper_2; hopper_second = &Hopper_1;
		}
		bool error = false;
		money_left = hopper_first->Split_Out();
		if (money_left != 0) {
			error = true;
			DEBUG("Error Hopper %d, left %d RUB\n", hopper_first->num, money_left / 100);
			hopper_second->money_for_out += money_left;
			DEBUG("Hopper %d, split out %d coins\n", hopper_second->num, hopper_second->money_for_out / hopper_second->value_of_coins);
		}
		money_left = hopper_second->Split_Out();
    
    
//		if ((money_left != 0)&&(!error)) {
//			DEBUG("Error Hopper %d, left %d RUB\n", hopper_second->num, money_left / 100);
//			hopper_first->money_for_out = money_left;
//			DEBUG("Hopper %d, split out %d coins\n", hopper_first->num, hopper_first->money_for_out / hopper_first->value_of_coins);
//			money_left = hopper_first->Split_Out();
//		}

		return money_left;
	}

	void HopperCoreClass::Calculate_Proportion(int money)
	{
		HopperClass* hopper_first;
		HopperClass* hopper_second;
		if (Hopper_1.value_of_coins > Hopper_2.value_of_coins)
		{
			hopper_first = &Hopper_1; hopper_second = &Hopper_2;
		}
		else
		{
			hopper_first = &Hopper_2; hopper_second = &Hopper_1;
		}

    hopper_first->money_for_out = 0;
		hopper_second->money_for_out = 0;
    
		switch (money)
		{
		case	500:
			hopper_first->money_for_out = 400;
			hopper_second->money_for_out = 100;
			break;
		case	1000:
			hopper_first->money_for_out = 600;
			hopper_second->money_for_out = 400;
			break;
		case	2000:
			hopper_first->money_for_out = 1400;
			hopper_second->money_for_out = 600;
			break;
		case	5000:
			hopper_first->money_for_out = 3400;
			hopper_second->money_for_out = 1600;
			break;
		case	10000:
			hopper_first->money_for_out = 6600;
			hopper_second->money_for_out = 3400;
			break;
		default:
			break;
		}
    
		DEBUG("Hopper %d split out %d coins\n", hopper_first->num, hopper_first->money_for_out/ hopper_first->value_of_coins);
		DEBUG("Hopper %d split out %d coins\n", hopper_second->num, hopper_second->money_for_out / hopper_second->value_of_coins);
	}
	/*###############################################################*/
	/*###############################################################* Hoppers_Thread -->*/
	/*###############################################################*/
	void HopperCoreClass::Hoppers_Thread(void* arg)
	{
		MessageClass msg;
		osStatus_t status;

		while (1) {

			//if (hopper.command == TERMINAL_HOPPER_STATUS_SET_SETTINGS) {
			//	hopper.responce = TERMINAL_HOPPER_STATUS_SET_SETTINGS;
			//	while (hopper.command != TERMINAL_HOPPER_STATUS_NULL) {
			//		Delay(1);
			//	}
			//}

			status = Hoppers.Messages.popMessageIn(&msg, osWaitForever);
			if (msg.command == SPIT_OUT) {
				uint32_t money_left = Hoppers.Two_Hoppers_Split_Out(msg.money);
				if (money_left != 0) {
					msg.command = SPIT_OUT_ERROR;
					msg.money = money_left;
					Hoppers.Messages.pushMessageOut(&msg);
					while (true) Delay(1000);
				}
				else {
					msg.command = SPIT_OUT_OK;
					Hoppers.Messages.pushMessageOut(&msg);
				}
			}
		}
	}

}	//HoppersNS
