#include "Terminal/Terminal.h"
#include "Threads.h"
#include "Winsock_Server.h"

int Simulate_Hardware();

using namespace DisplayNS;
using namespace BillAcceptorNS;
using namespace HoppersNS;
std::thread thr1;
std::thread thr2;
std::thread thr3;
std::thread thr4;
std::thread thr10;
void Terminal_Close_Threads()
{
	thr1.join();
	thr2.join();
	thr3.join();
	thr4.join();
	thr10.join();
}


int Terminal_Threads()
{
	thr1 = std::thread(DisplayClass::Display_1_Thread, &Displays);
	thr2 = std::thread(CoreClass::Core_Thread, &Terminal);
	thr3 = std::thread(BillAcceptorClass::BillAcceptor_Thread, &BillAcceptor);
	thr4 = std::thread(HopperCoreClass::Hoppers_Thread, &Hoppers);

	thr10 = std::thread(Simulate_Hardware);

	return 0;
}

int Server_Threads()
{
	thr1 = std::thread(Socket_Server_1);
	thr2 = std::thread(Socket_Server_2);
	thr3 = std::thread(Server_Thread);
	
	return 0;
}



int Simulate_Hardware()
{
	osStatus_t status;

	HoppersNS::MessageClass msg_hopper;
	while (true) {


		status = Hoppers.Hopper_1.Messages.popMessageOut(&msg_hopper, 1);
		if (status == osOK) {
			if (msg_hopper.command == SPIT_OUT)
			{
				Delay(1000);
				msg_hopper.coins = 0;
				Hoppers.Hopper_1.Messages.pushMessageIn(&msg_hopper);
			}

		}

		status = Hoppers.Hopper_2.Messages.popMessageOut(&msg_hopper, 1);
		if (status == osOK) {
			if (msg_hopper.command == SPIT_OUT)
			{
				Delay(1000);
				msg_hopper.coins = 0;
				Hoppers.Hopper_2.Messages.pushMessageIn(&msg_hopper);
			}

		}

		Delay(100);
	}


	return 0;
}
