#include "MainForm.h"
#include "Terminal/Terminal.h"

using namespace System;
using namespace System::Windows::Forms;

//TERMINAL_HandleTypeDef* hterminal;
//TERMINAL_HandleDisplaysTypeDef* hdisplay;
//TERMINAL_HandleBillAcceptorTypeDef* hbillacceptor;
//TERMINAL_HandleCoreHopperTypeDef* hhopper;
bool set_settings = false;
bool get_settings = false;

uint32_t hopper1_count_total_spit_out_coins = 0;
uint32_t hopper2_count_total_spit_out_coins = 0;

#pragma execution_character_set( "utf-8" )



[STAThreadAttribute]
void Main(array<String^>^ args) {
	SetConsoleOutputCP(65001);

	//Terminal_Init();
	//hterminal = Terminal_Get_Handle();
	//hdisplay = Terminal_Get_HandleDisplay();
	//hbillacceptor = Terminal_Get_HandleBillAcceptor();
	//hhopper = Terminal_Get_HandleHopper();


	//TERMINAL_HandleCoreHopperTypeDef *hopper;
	//hopper = Terminal_Get_HandleHopper();
	//hopper->init();

	//uint32_t count_coins_1 = 0;
	//uint32_t count_coins_2 = 0;
	//hopper->hopper_1.coins_total = 0;
	//hopper->hopper_2.coins_total = 10;

	//hopper->hopper_1.value_of_coins = 10;
	//hopper->hopper_2.value_of_coins = 20;

	//hopper->money_for_out = 110;
	//hopper->ñalculate_proportion(&count_coins_1, &count_coins_2);

	//Will you test proficiency micropython or device development experience?
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	FillingStation::MainForm form;
	Application::Run(% form);
}





