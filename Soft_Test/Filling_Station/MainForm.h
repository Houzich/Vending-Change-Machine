
#pragma once
#include "Threads.h"
#include "Winsock_Server.h"
#include "Terminal/Terminal.h"
#include "Terminal/Display.h"



#include <msclr/marshal_cppstd.h>
#include <atlstr.h>
//extern TERMINAL_HandleTypeDef* hterminal;
//extern TERMINAL_HandleDisplaysTypeDef* hdisplay;
//extern TERMINAL_HandleBillAcceptorTypeDef* hbillacceptor;
//extern TERMINAL_HandleCoreHopperTypeDef* hhopper;

extern bool set_settings;
extern bool get_settings;

namespace FillingStation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::Globalization;
	using namespace msclr::interop;

	using namespace DisplayNS;
	using namespace BillAcceptorNS;
	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			set_settings = false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button_Send_Test;
	private: System::Windows::Forms::TextBox^ textBox_Coin_Acceptor;
	private: System::Windows::Forms::TextBox^ textBox_Bill_Acceptor;


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button_Exchange;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ textBox_CardReader;

	private: System::Windows::Forms::TextBox^ textBox_Card;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ textBox_Card_Dispenser;

	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ textBox_Hopper_1;
	private: System::Windows::Forms::Button^ button_DepositMoney;




	private: System::Windows::Forms::Timer^ timer_display;
	private: System::Windows::Forms::Button^ button_Coin_01;
	private: System::Windows::Forms::Button^ button_Coin_02;
	private: System::Windows::Forms::Button^ button_Coin_05;
	private: System::Windows::Forms::Button^ button_Coin_10;
	private: System::Windows::Forms::Button^ button_Coin_20;
	private: System::Windows::Forms::Button^ button_Bill_100;





	private: System::Windows::Forms::Button^ button_Bill_050;

	private: System::Windows::Forms::Button^ button_Bill_020;

	private: System::Windows::Forms::Button^ button_Bill_010;

	private: System::Windows::Forms::Button^ button_Bill_005;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBox_cost_coint_2;


	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ textBox_cost_card;

	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::TextBox^ textBox_number_buttons;

	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ textBox_number_coins;

	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::TextBox^ textBox_number_spit_out_cards;

	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::TextBox^ textBox_number_spit_out_coins;

	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::TextBox^ textBox_number_cards;

	private: System::Windows::Forms::Button^ button_SplitOutCards;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::TextBox^ textBox_Hopper_2;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::TextBox^ textBox_cost_coint_1;
	private: System::Windows::Forms::Button^ button_Card;
	private: System::Windows::Forms::Button^ button_SettingsSoft;
	private: System::Windows::Forms::Button^ button_Settings;


	private: System::Windows::Forms::Button^ button_Left;
	private: System::Windows::Forms::Button^ button_Right;


	private: System::Windows::Forms::Button^ button_Down;
	private: System::Windows::Forms::Button^ button_Up;
	private: System::Windows::Forms::Button^ button_Ok;



	private: System::Windows::Forms::Button^ button_Hopper_1;
	private: System::Windows::Forms::Button^ button_Hopper_2;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::TextBox^ textBox_ProportionHoppers;
	private: System::Windows::Forms::Label^ label_TimeForSplitOut;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::TextBox^ textBox_Num_Hoppers;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::TextBox^ textBox_Num_Dispenser;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::TextBox^ textBox_Num_Card_Reader;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::TextBox^ textBox_Number_CoinAcceptor;

	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::TextBox^ textBox_Number_BillAcceptor;
	private: System::Windows::Forms::Button^ button_Return;
	private: System::Windows::Forms::Label^ label_Display_1;

	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label_Display_4;

	private: System::Windows::Forms::Label^ label_Display_3;

	private: System::Windows::Forms::Label^ label_Display_2;
	private: System::Windows::Forms::RadioButton^ radioButton_Server;
	private: System::Windows::Forms::RadioButton^ radioButton_Client;
	private: System::Windows::Forms::ComboBox^ comboBox_COMPorts;
	private: System::Windows::Forms::Button^ button_Connect_COM;

	private: System::Windows::Forms::Label^ label22;
	public: System::IO::Ports::SerialPort^ serialPort;
	private:

	private:

	private:


	private:
		String^ currCOMPort;

		bool flagCOMPortEnable = false;
		bool flagProcess = false;
		bool flagConnectToBoard = false;
		bool flagStartUSB = false;

	public: delegate void Send_Message_WS_Test_Delegate(void);
	public: delegate void Test_Delegate(int arg);
	private: System::Windows::Forms::Label^ label_STATE_COM;
	public:



	private: System::Windows::Forms::Button^ button_Start_USB;
	private: System::Windows::Forms::Button^ button_Disconnect_COM;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Label^ label_Display_8;
	private: System::Windows::Forms::Label^ label_Display_7;
	private: System::Windows::Forms::Label^ label_Display_6;
	private: System::Windows::Forms::Label^ label_Display_5;
	private: System::Windows::Forms::RadioButton^ radioButton_Test;
	private: System::Windows::Forms::Button^ button_Test;
	private: System::Windows::Forms::RichTextBox^ richTextBox_WS_Client_1;
	private: System::Windows::Forms::TextBox^ textBox_WS_Client_2;


	private: System::Windows::Forms::Button^ button_Send_To_WS_Server_1;
	private: System::Windows::Forms::TextBox^ textBox_WS_Client_3;
	private: System::Windows::Forms::Button^ button_Send_To_WS_Server_2;
	private: System::Windows::Forms::Button^ button_Send_To_WS_Server_3;
	private: System::Windows::Forms::Button^ button_Send_To_WS_Server_4;
	private: System::Windows::Forms::TextBox^ textBox_WS_Client_4;
	private: System::Windows::Forms::Button^ button_Request_State_1;
	private: System::Windows::Forms::Label^ label23;
	private: System::Windows::Forms::Button^ button_Request_State_2;
	private: System::Windows::Forms::Button^ button_Request_State_3;
	private: System::Windows::Forms::TextBox^ textBox_sett_Number_BillAcceptor;
	private: System::Windows::Forms::TextBox^ textBox_sett_Number_CoinAcceptor;
	private: System::Windows::Forms::TextBox^ textBox_sett_Num_Card_Reader;
	private: System::Windows::Forms::TextBox^ textBox_sett_Num_Dispenser;
	private: System::Windows::Forms::TextBox^ textBox_sett_Num_Hoppers;
	private: System::Windows::Forms::TextBox^ textBox_sett_ProportionHoppers;
	private: System::Windows::Forms::TextBox^ textBox_sett_cost_coint_1;
	private: System::Windows::Forms::TextBox^ textBox_sett_number_cards;
	private: System::Windows::Forms::TextBox^ textBox_sett_number_coins;
	private: System::Windows::Forms::TextBox^ textBox_sett_number_spit_out_cards;
	private: System::Windows::Forms::TextBox^ textBox_sett_number_spit_out_coins;
	private: System::Windows::Forms::TextBox^ textBox_sett_number_buttons;
	private: System::Windows::Forms::TextBox^ textBox_sett_cost_card;
	private: System::Windows::Forms::TextBox^ textBox_sett_cost_coint_2;
	private: System::Windows::Forms::Button^ button_Encashment;
	private: System::Windows::Forms::TextBox^ textBox_Hopper2_Real;

	private: System::Windows::Forms::TextBox^ textBox_Hopper1_Real;
private: System::Windows::Forms::Label^ label_Sensor_Hopper1;
private: System::Windows::Forms::Label^ label_Sensor_Hopper2;



	private: System::Windows::Forms::TextBox^ textBox_sett_Diapason_Hold_Acceptors;
	private: System::Windows::Forms::Label^ label26;
	private: System::Windows::Forms::TextBox^ textBox_Diapason_Hold_Acceptors;
private: System::Windows::Forms::CheckBox^ checkBox_Enable_Sensor_Hopper1;
private: System::Windows::Forms::CheckBox^ checkBox_Enable_Sensor_Hopper2;








	private: System::ComponentModel::IContainer^ components;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
	private: System::Void Enable_Disable_Button(System::Object^ sender, bool state) {
		System::Windows::Forms::Button^ button;
		button = (System::Windows::Forms::Button^) sender;

		if (state) {
			button->Enabled = true;
			button->BackColor = System::Drawing::Color::FromName("Green");
		}
		else {
			button->Enabled = false;
			button->BackColor = System::Drawing::Color::FromName("Gray");
		}
	}
	private: System::Void Enable_Disable_Yellow_Button(System::Object^ sender, bool state) {
		System::Windows::Forms::Button^ button;
		button = (System::Windows::Forms::Button^) sender;

		if (state) {
			button->Enabled = true;
			button->BackColor = System::Drawing::Color::FromName("Gold");
		}
		else {
			button->Enabled = false;
			button->BackColor = System::Drawing::Color::FromName("Gray");
		}
	}
	public:
		static void Set_Settings_Terminal(void)
		{
			set_settings = true;
		}

	//private: System::Void Set_Settings(TERMINAL_SettingsTypeDef* sett) {
	//	sett->cost_coin_1 = Convert::ToInt32(100 * Convert::ToDouble(textBox_sett_cost_coint_1->Text, CultureInfo::InvariantCulture), CultureInfo::InvariantCulture);
	//	sett->cost_coin_2 = Convert::ToInt32(100 * Convert::ToDouble(textBox_sett_cost_coint_2->Text, CultureInfo::InvariantCulture), CultureInfo::InvariantCulture);
	//	sett->cost_card = Convert::ToInt32(100 * Convert::ToDouble(textBox_sett_cost_card->Text, CultureInfo::InvariantCulture), CultureInfo::InvariantCulture);
	//	sett->number_buttons = (uint32_t)Convert::ToInt32(textBox_sett_number_buttons->Text, CultureInfo::InvariantCulture);
	//	sett->number_spit_out_coins = (uint32_t)Convert::ToInt32(textBox_sett_number_spit_out_coins->Text, CultureInfo::InvariantCulture);
	//	sett->number_spit_out_cards = (uint32_t)Convert::ToInt32(textBox_sett_number_spit_out_cards->Text, CultureInfo::InvariantCulture);
	//	sett->number_coins = (uint32_t)Convert::ToInt32(textBox_sett_number_coins->Text, CultureInfo::InvariantCulture);
	//	sett->number_cards = (uint32_t)Convert::ToInt32(textBox_sett_number_cards->Text, CultureInfo::InvariantCulture);
	//	sett->proportion_hoppers = (uint32_t)Convert::ToInt32(textBox_sett_ProportionHoppers->Text, CultureInfo::InvariantCulture);
	//	sett->number_coinacceptors = (uint32_t)Convert::ToInt32(textBox_sett_Number_CoinAcceptor->Text, CultureInfo::InvariantCulture);
	//	sett->number_billacceptors = (uint32_t)Convert::ToInt32(textBox_sett_Number_BillAcceptor->Text, CultureInfo::InvariantCulture);
	//	sett->number_hoppers = (uint32_t)Convert::ToInt32(textBox_sett_Num_Hoppers->Text, CultureInfo::InvariantCulture);
	//	sett->number_carddispensers = (uint32_t)Convert::ToInt32(textBox_sett_Num_Dispenser->Text, CultureInfo::InvariantCulture);
	//	sett->number_cardreaders = (uint32_t)Convert::ToInt32(textBox_sett_Num_Card_Reader->Text, CultureInfo::InvariantCulture);
	//	sett->diapason_hold_acceptors = (uint32_t)Convert::ToInt32(textBox_sett_Diapason_Hold_Acceptors->Text, CultureInfo::InvariantCulture);
	//}

	private: System::Void Get_Settings(void) {
		//textBox_cost_coint_1->Text = Convert::ToString((float)(hterminal->settings.cost_coin_1) / 100, CultureInfo::InvariantCulture);
		//textBox_cost_coint_2->Text = Convert::ToString((float)(hterminal->settings.cost_coin_2) / 100, CultureInfo::InvariantCulture);
		//textBox_cost_card->Text = Convert::ToString((float)(hterminal->settings.cost_card) / 100, CultureInfo::InvariantCulture);
		//textBox_number_buttons->Text = Convert::ToString(hterminal->settings.number_buttons, CultureInfo::InvariantCulture);
		//textBox_number_spit_out_coins->Text = Convert::ToString(hterminal->settings.number_spit_out_coins, CultureInfo::InvariantCulture);
		//textBox_number_spit_out_cards->Text = Convert::ToString(hterminal->settings.number_spit_out_cards, CultureInfo::InvariantCulture);
		//textBox_number_coins->Text = Convert::ToString(hterminal->settings.number_coins, CultureInfo::InvariantCulture);
		//textBox_number_cards->Text = Convert::ToString(hterminal->settings.number_cards, CultureInfo::InvariantCulture);
		//textBox_ProportionHoppers->Text = Convert::ToString(hterminal->settings.proportion_hoppers, CultureInfo::InvariantCulture);
		//textBox_Number_CoinAcceptor->Text = Convert::ToString(hterminal->settings.number_coinacceptors, CultureInfo::InvariantCulture);
		//textBox_Number_BillAcceptor->Text = Convert::ToString(hterminal->settings.number_billacceptors, CultureInfo::InvariantCulture);
		//textBox_Num_Hoppers->Text = Convert::ToString(hterminal->settings.number_hoppers, CultureInfo::InvariantCulture);
		//textBox_Num_Dispenser->Text = Convert::ToString(hterminal->settings.number_carddispensers, CultureInfo::InvariantCulture);
		//textBox_Num_Card_Reader->Text = Convert::ToString(hterminal->settings.number_cardreaders, CultureInfo::InvariantCulture);
		//textBox_Diapason_Hold_Acceptors->Text = Convert::ToString(hterminal->settings.diapason_hold_acceptors, CultureInfo::InvariantCulture);
	}

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			   this->button_Send_Test = (gcnew System::Windows::Forms::Button());
			   this->textBox_Coin_Acceptor = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_Bill_Acceptor = (gcnew System::Windows::Forms::TextBox());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->button_Exchange = (gcnew System::Windows::Forms::Button());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->textBox_CardReader = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_Card = (gcnew System::Windows::Forms::TextBox());
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   this->textBox_Card_Dispenser = (gcnew System::Windows::Forms::TextBox());
			   this->label6 = (gcnew System::Windows::Forms::Label());
			   this->textBox_Hopper_1 = (gcnew System::Windows::Forms::TextBox());
			   this->button_DepositMoney = (gcnew System::Windows::Forms::Button());
			   this->timer_display = (gcnew System::Windows::Forms::Timer(this->components));
			   this->button_Coin_01 = (gcnew System::Windows::Forms::Button());
			   this->button_Coin_02 = (gcnew System::Windows::Forms::Button());
			   this->button_Coin_05 = (gcnew System::Windows::Forms::Button());
			   this->button_Coin_10 = (gcnew System::Windows::Forms::Button());
			   this->button_Coin_20 = (gcnew System::Windows::Forms::Button());
			   this->button_Bill_100 = (gcnew System::Windows::Forms::Button());
			   this->button_Bill_050 = (gcnew System::Windows::Forms::Button());
			   this->button_Bill_020 = (gcnew System::Windows::Forms::Button());
			   this->button_Bill_010 = (gcnew System::Windows::Forms::Button());
			   this->button_Bill_005 = (gcnew System::Windows::Forms::Button());
			   this->label7 = (gcnew System::Windows::Forms::Label());
			   this->textBox_cost_coint_2 = (gcnew System::Windows::Forms::TextBox());
			   this->label8 = (gcnew System::Windows::Forms::Label());
			   this->textBox_cost_card = (gcnew System::Windows::Forms::TextBox());
			   this->label9 = (gcnew System::Windows::Forms::Label());
			   this->textBox_number_buttons = (gcnew System::Windows::Forms::TextBox());
			   this->label10 = (gcnew System::Windows::Forms::Label());
			   this->textBox_number_coins = (gcnew System::Windows::Forms::TextBox());
			   this->label11 = (gcnew System::Windows::Forms::Label());
			   this->textBox_number_spit_out_cards = (gcnew System::Windows::Forms::TextBox());
			   this->label12 = (gcnew System::Windows::Forms::Label());
			   this->textBox_number_spit_out_coins = (gcnew System::Windows::Forms::TextBox());
			   this->label13 = (gcnew System::Windows::Forms::Label());
			   this->textBox_number_cards = (gcnew System::Windows::Forms::TextBox());
			   this->button_SplitOutCards = (gcnew System::Windows::Forms::Button());
			   this->label14 = (gcnew System::Windows::Forms::Label());
			   this->textBox_Hopper_2 = (gcnew System::Windows::Forms::TextBox());
			   this->label15 = (gcnew System::Windows::Forms::Label());
			   this->textBox_cost_coint_1 = (gcnew System::Windows::Forms::TextBox());
			   this->button_Card = (gcnew System::Windows::Forms::Button());
			   this->button_SettingsSoft = (gcnew System::Windows::Forms::Button());
			   this->button_Settings = (gcnew System::Windows::Forms::Button());
			   this->button_Left = (gcnew System::Windows::Forms::Button());
			   this->button_Right = (gcnew System::Windows::Forms::Button());
			   this->button_Down = (gcnew System::Windows::Forms::Button());
			   this->button_Up = (gcnew System::Windows::Forms::Button());
			   this->button_Ok = (gcnew System::Windows::Forms::Button());
			   this->button_Hopper_1 = (gcnew System::Windows::Forms::Button());
			   this->button_Hopper_2 = (gcnew System::Windows::Forms::Button());
			   this->label16 = (gcnew System::Windows::Forms::Label());
			   this->textBox_ProportionHoppers = (gcnew System::Windows::Forms::TextBox());
			   this->label_TimeForSplitOut = (gcnew System::Windows::Forms::Label());
			   this->label17 = (gcnew System::Windows::Forms::Label());
			   this->textBox_Num_Hoppers = (gcnew System::Windows::Forms::TextBox());
			   this->label18 = (gcnew System::Windows::Forms::Label());
			   this->textBox_Num_Dispenser = (gcnew System::Windows::Forms::TextBox());
			   this->label19 = (gcnew System::Windows::Forms::Label());
			   this->textBox_Num_Card_Reader = (gcnew System::Windows::Forms::TextBox());
			   this->label20 = (gcnew System::Windows::Forms::Label());
			   this->textBox_Number_CoinAcceptor = (gcnew System::Windows::Forms::TextBox());
			   this->label21 = (gcnew System::Windows::Forms::Label());
			   this->textBox_Number_BillAcceptor = (gcnew System::Windows::Forms::TextBox());
			   this->button_Return = (gcnew System::Windows::Forms::Button());
			   this->label_Display_1 = (gcnew System::Windows::Forms::Label());
			   this->panel1 = (gcnew System::Windows::Forms::Panel());
			   this->label_Display_4 = (gcnew System::Windows::Forms::Label());
			   this->label_Display_3 = (gcnew System::Windows::Forms::Label());
			   this->label_Display_2 = (gcnew System::Windows::Forms::Label());
			   this->radioButton_Server = (gcnew System::Windows::Forms::RadioButton());
			   this->radioButton_Client = (gcnew System::Windows::Forms::RadioButton());
			   this->comboBox_COMPorts = (gcnew System::Windows::Forms::ComboBox());
			   this->button_Connect_COM = (gcnew System::Windows::Forms::Button());
			   this->label22 = (gcnew System::Windows::Forms::Label());
			   this->serialPort = (gcnew System::IO::Ports::SerialPort(this->components));
			   this->label_STATE_COM = (gcnew System::Windows::Forms::Label());
			   this->button_Start_USB = (gcnew System::Windows::Forms::Button());
			   this->button_Disconnect_COM = (gcnew System::Windows::Forms::Button());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->panel2 = (gcnew System::Windows::Forms::Panel());
			   this->label_Display_8 = (gcnew System::Windows::Forms::Label());
			   this->label_Display_7 = (gcnew System::Windows::Forms::Label());
			   this->label_Display_6 = (gcnew System::Windows::Forms::Label());
			   this->label_Display_5 = (gcnew System::Windows::Forms::Label());
			   this->radioButton_Test = (gcnew System::Windows::Forms::RadioButton());
			   this->button_Test = (gcnew System::Windows::Forms::Button());
			   this->richTextBox_WS_Client_1 = (gcnew System::Windows::Forms::RichTextBox());
			   this->textBox_WS_Client_2 = (gcnew System::Windows::Forms::TextBox());
			   this->button_Send_To_WS_Server_1 = (gcnew System::Windows::Forms::Button());
			   this->textBox_WS_Client_3 = (gcnew System::Windows::Forms::TextBox());
			   this->button_Send_To_WS_Server_2 = (gcnew System::Windows::Forms::Button());
			   this->button_Send_To_WS_Server_3 = (gcnew System::Windows::Forms::Button());
			   this->button_Send_To_WS_Server_4 = (gcnew System::Windows::Forms::Button());
			   this->textBox_WS_Client_4 = (gcnew System::Windows::Forms::TextBox());
			   this->button_Request_State_1 = (gcnew System::Windows::Forms::Button());
			   this->label23 = (gcnew System::Windows::Forms::Label());
			   this->button_Request_State_2 = (gcnew System::Windows::Forms::Button());
			   this->button_Request_State_3 = (gcnew System::Windows::Forms::Button());
			   this->textBox_sett_Number_BillAcceptor = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_sett_Number_CoinAcceptor = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_sett_Num_Card_Reader = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_sett_Num_Dispenser = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_sett_Num_Hoppers = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_sett_ProportionHoppers = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_sett_cost_coint_1 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_sett_number_cards = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_sett_number_coins = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_sett_number_spit_out_cards = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_sett_number_spit_out_coins = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_sett_number_buttons = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_sett_cost_card = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_sett_cost_coint_2 = (gcnew System::Windows::Forms::TextBox());
			   this->button_Encashment = (gcnew System::Windows::Forms::Button());
			   this->textBox_Hopper2_Real = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_Hopper1_Real = (gcnew System::Windows::Forms::TextBox());
			   this->label_Sensor_Hopper1 = (gcnew System::Windows::Forms::Label());
			   this->label_Sensor_Hopper2 = (gcnew System::Windows::Forms::Label());
			   this->textBox_sett_Diapason_Hold_Acceptors = (gcnew System::Windows::Forms::TextBox());
			   this->label26 = (gcnew System::Windows::Forms::Label());
			   this->textBox_Diapason_Hold_Acceptors = (gcnew System::Windows::Forms::TextBox());
			   this->checkBox_Enable_Sensor_Hopper1 = (gcnew System::Windows::Forms::CheckBox());
			   this->checkBox_Enable_Sensor_Hopper2 = (gcnew System::Windows::Forms::CheckBox());
			   this->panel1->SuspendLayout();
			   this->panel2->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // button_Send_Test
			   // 
			   this->button_Send_Test->BackColor = System::Drawing::Color::Green;
			   this->button_Send_Test->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Send_Test->Location = System::Drawing::Point(12, 12);
			   this->button_Send_Test->Name = L"button_Send_Test";
			   this->button_Send_Test->Size = System::Drawing::Size(130, 30);
			   this->button_Send_Test->TabIndex = 226;
			   this->button_Send_Test->Tag = L"Start";
			   this->button_Send_Test->Text = L"Test";
			   this->button_Send_Test->UseVisualStyleBackColor = false;
			   this->button_Send_Test->Click += gcnew System::EventHandler(this, &MainForm::button_Send_Test_Click);
			   // 
			   // textBox_Coin_Acceptor
			   // 
			   this->textBox_Coin_Acceptor->Enabled = false;
			   this->textBox_Coin_Acceptor->Location = System::Drawing::Point(544, 83);
			   this->textBox_Coin_Acceptor->MaxLength = 4;
			   this->textBox_Coin_Acceptor->Name = L"textBox_Coin_Acceptor";
			   this->textBox_Coin_Acceptor->Size = System::Drawing::Size(50, 20);
			   this->textBox_Coin_Acceptor->TabIndex = 227;
			   this->textBox_Coin_Acceptor->Text = L"0";
			   // 
			   // textBox_Bill_Acceptor
			   // 
			   this->textBox_Bill_Acceptor->Enabled = false;
			   this->textBox_Bill_Acceptor->Location = System::Drawing::Point(544, 128);
			   this->textBox_Bill_Acceptor->MaxLength = 4;
			   this->textBox_Bill_Acceptor->Name = L"textBox_Bill_Acceptor";
			   this->textBox_Bill_Acceptor->Size = System::Drawing::Size(50, 20);
			   this->textBox_Bill_Acceptor->TabIndex = 228;
			   this->textBox_Bill_Acceptor->Text = L"0";
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label1->Location = System::Drawing::Point(548, 64);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(117, 16);
			   this->label1->TabIndex = 229;
			   this->label1->Text = L"Монетоприемник ";
			   this->label1->Click += gcnew System::EventHandler(this, &MainForm::label1_Click);
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label2->Location = System::Drawing::Point(548, 110);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(109, 16);
			   this->label2->TabIndex = 230;
			   this->label2->Text = L"Купюроприемник";
			   // 
			   // button_Exchange
			   // 
			   this->button_Exchange->BackColor = System::Drawing::Color::Green;
			   this->button_Exchange->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Exchange->Location = System::Drawing::Point(417, 232);
			   this->button_Exchange->Name = L"button_Exchange";
			   this->button_Exchange->Size = System::Drawing::Size(130, 30);
			   this->button_Exchange->TabIndex = 231;
			   this->button_Exchange->Tag = L"Exchange";
			   this->button_Exchange->Text = L"Размен";
			   this->button_Exchange->UseVisualStyleBackColor = false;
			   this->button_Exchange->Click += gcnew System::EventHandler(this, &MainForm::button_Exchange_Click);
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label3->Location = System::Drawing::Point(394, 23);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(149, 16);
			   this->label3->TabIndex = 235;
			   this->label3->Text = L"Считыватель rfid карт";
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label4->Location = System::Drawing::Point(548, 22);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(215, 16);
			   this->label4->TabIndex = 234;
			   this->label4->Text = L"Бесконтактная банковская карта";
			   // 
			   // textBox_CardReader
			   // 
			   this->textBox_CardReader->Enabled = false;
			   this->textBox_CardReader->Location = System::Drawing::Point(390, 41);
			   this->textBox_CardReader->MaxLength = 4;
			   this->textBox_CardReader->Name = L"textBox_CardReader";
			   this->textBox_CardReader->Size = System::Drawing::Size(50, 20);
			   this->textBox_CardReader->TabIndex = 233;
			   // 
			   // textBox_Card
			   // 
			   this->textBox_Card->Enabled = false;
			   this->textBox_Card->Location = System::Drawing::Point(544, 41);
			   this->textBox_Card->MaxLength = 4;
			   this->textBox_Card->Name = L"textBox_Card";
			   this->textBox_Card->Size = System::Drawing::Size(50, 20);
			   this->textBox_Card->TabIndex = 232;
			   this->textBox_Card->Text = L"0";
			   // 
			   // label5
			   // 
			   this->label5->AutoSize = true;
			   this->label5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label5->Location = System::Drawing::Point(394, 65);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(126, 16);
			   this->label5->TabIndex = 237;
			   this->label5->Text = L"Диспенсер rfid карт";
			   // 
			   // textBox_Card_Dispenser
			   // 
			   this->textBox_Card_Dispenser->Enabled = false;
			   this->textBox_Card_Dispenser->Location = System::Drawing::Point(390, 83);
			   this->textBox_Card_Dispenser->MaxLength = 4;
			   this->textBox_Card_Dispenser->Name = L"textBox_Card_Dispenser";
			   this->textBox_Card_Dispenser->Size = System::Drawing::Size(50, 20);
			   this->textBox_Card_Dispenser->TabIndex = 236;
			   this->textBox_Card_Dispenser->Text = L"0";
			   // 
			   // label6
			   // 
			   this->label6->AutoSize = true;
			   this->label6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label6->Location = System::Drawing::Point(394, 110);
			   this->label6->Name = L"label6";
			   this->label6->Size = System::Drawing::Size(61, 16);
			   this->label6->TabIndex = 239;
			   this->label6->Text = L"Хоппер 1";
			   // 
			   // textBox_Hopper_1
			   // 
			   this->textBox_Hopper_1->Enabled = false;
			   this->textBox_Hopper_1->Location = System::Drawing::Point(390, 128);
			   this->textBox_Hopper_1->MaxLength = 4;
			   this->textBox_Hopper_1->Name = L"textBox_Hopper_1";
			   this->textBox_Hopper_1->Size = System::Drawing::Size(50, 20);
			   this->textBox_Hopper_1->TabIndex = 238;
			   this->textBox_Hopper_1->Text = L"0";
			   // 
			   // button_DepositMoney
			   // 
			   this->button_DepositMoney->BackColor = System::Drawing::Color::Green;
			   this->button_DepositMoney->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_DepositMoney->Location = System::Drawing::Point(417, 196);
			   this->button_DepositMoney->Name = L"button_DepositMoney";
			   this->button_DepositMoney->Size = System::Drawing::Size(130, 30);
			   this->button_DepositMoney->TabIndex = 242;
			   this->button_DepositMoney->Tag = L"Exchange";
			   this->button_DepositMoney->Text = L"Зачислить на rfid";
			   this->button_DepositMoney->UseVisualStyleBackColor = false;
			   this->button_DepositMoney->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			   // 
			   // timer_display
			   // 
			   this->timer_display->Enabled = true;
			   this->timer_display->Interval = 50;
			   this->timer_display->Tick += gcnew System::EventHandler(this, &MainForm::timer_display_Tick);
			   // 
			   // button_Coin_01
			   // 
			   this->button_Coin_01->BackColor = System::Drawing::Color::Gold;
			   this->button_Coin_01->Font = (gcnew System::Drawing::Font(L"Impact", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Coin_01->Location = System::Drawing::Point(611, 81);
			   this->button_Coin_01->Name = L"button_Coin_01";
			   this->button_Coin_01->Size = System::Drawing::Size(33, 26);
			   this->button_Coin_01->TabIndex = 245;
			   this->button_Coin_01->Tag = L"0.1";
			   this->button_Coin_01->Text = L"0.1";
			   this->button_Coin_01->UseVisualStyleBackColor = false;
			   this->button_Coin_01->Click += gcnew System::EventHandler(this, &MainForm::button_Coin_01_Click);
			   // 
			   // button_Coin_02
			   // 
			   this->button_Coin_02->BackColor = System::Drawing::Color::Gold;
			   this->button_Coin_02->Font = (gcnew System::Drawing::Font(L"Impact", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Coin_02->Location = System::Drawing::Point(650, 81);
			   this->button_Coin_02->Name = L"button_Coin_02";
			   this->button_Coin_02->Size = System::Drawing::Size(36, 26);
			   this->button_Coin_02->TabIndex = 246;
			   this->button_Coin_02->Tag = L"0.2";
			   this->button_Coin_02->Text = L"0.2";
			   this->button_Coin_02->UseVisualStyleBackColor = false;
			   this->button_Coin_02->Click += gcnew System::EventHandler(this, &MainForm::button_Coin_01_Click);
			   // 
			   // button_Coin_05
			   // 
			   this->button_Coin_05->BackColor = System::Drawing::Color::Gold;
			   this->button_Coin_05->Font = (gcnew System::Drawing::Font(L"Impact", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Coin_05->Location = System::Drawing::Point(692, 81);
			   this->button_Coin_05->Name = L"button_Coin_05";
			   this->button_Coin_05->Size = System::Drawing::Size(36, 26);
			   this->button_Coin_05->TabIndex = 247;
			   this->button_Coin_05->Tag = L"0.5";
			   this->button_Coin_05->Text = L"0.5";
			   this->button_Coin_05->UseVisualStyleBackColor = false;
			   this->button_Coin_05->Click += gcnew System::EventHandler(this, &MainForm::button_Coin_01_Click);
			   // 
			   // button_Coin_10
			   // 
			   this->button_Coin_10->BackColor = System::Drawing::Color::Gold;
			   this->button_Coin_10->Font = (gcnew System::Drawing::Font(L"Impact", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Coin_10->Location = System::Drawing::Point(734, 81);
			   this->button_Coin_10->Name = L"button_Coin_10";
			   this->button_Coin_10->Size = System::Drawing::Size(36, 26);
			   this->button_Coin_10->TabIndex = 248;
			   this->button_Coin_10->Tag = L"1";
			   this->button_Coin_10->Text = L"1";
			   this->button_Coin_10->UseVisualStyleBackColor = false;
			   this->button_Coin_10->Click += gcnew System::EventHandler(this, &MainForm::button_Coin_01_Click);
			   // 
			   // button_Coin_20
			   // 
			   this->button_Coin_20->BackColor = System::Drawing::Color::Gold;
			   this->button_Coin_20->Font = (gcnew System::Drawing::Font(L"Impact", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Coin_20->Location = System::Drawing::Point(776, 81);
			   this->button_Coin_20->Name = L"button_Coin_20";
			   this->button_Coin_20->Size = System::Drawing::Size(36, 26);
			   this->button_Coin_20->TabIndex = 249;
			   this->button_Coin_20->Tag = L"2";
			   this->button_Coin_20->Text = L"2";
			   this->button_Coin_20->UseVisualStyleBackColor = false;
			   this->button_Coin_20->Click += gcnew System::EventHandler(this, &MainForm::button_Coin_01_Click);
			   // 
			   // button_Bill_100
			   // 
			   this->button_Bill_100->BackColor = System::Drawing::Color::Gold;
			   this->button_Bill_100->Font = (gcnew System::Drawing::Font(L"Impact", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Bill_100->Location = System::Drawing::Point(776, 128);
			   this->button_Bill_100->Name = L"button_Bill_100";
			   this->button_Bill_100->Size = System::Drawing::Size(43, 26);
			   this->button_Bill_100->TabIndex = 254;
			   this->button_Bill_100->Tag = L"100";
			   this->button_Bill_100->Text = L"100";
			   this->button_Bill_100->UseVisualStyleBackColor = false;
			   this->button_Bill_100->Click += gcnew System::EventHandler(this, &MainForm::button_Bill_005_Click);
			   // 
			   // button_Bill_050
			   // 
			   this->button_Bill_050->BackColor = System::Drawing::Color::Gold;
			   this->button_Bill_050->Font = (gcnew System::Drawing::Font(L"Impact", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Bill_050->Location = System::Drawing::Point(734, 128);
			   this->button_Bill_050->Name = L"button_Bill_050";
			   this->button_Bill_050->Size = System::Drawing::Size(36, 26);
			   this->button_Bill_050->TabIndex = 253;
			   this->button_Bill_050->Tag = L"50";
			   this->button_Bill_050->Text = L"50";
			   this->button_Bill_050->UseVisualStyleBackColor = false;
			   this->button_Bill_050->Click += gcnew System::EventHandler(this, &MainForm::button_Bill_005_Click);
			   // 
			   // button_Bill_020
			   // 
			   this->button_Bill_020->BackColor = System::Drawing::Color::Gold;
			   this->button_Bill_020->Font = (gcnew System::Drawing::Font(L"Impact", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Bill_020->Location = System::Drawing::Point(692, 128);
			   this->button_Bill_020->Name = L"button_Bill_020";
			   this->button_Bill_020->Size = System::Drawing::Size(36, 26);
			   this->button_Bill_020->TabIndex = 252;
			   this->button_Bill_020->Tag = L"20";
			   this->button_Bill_020->Text = L"20";
			   this->button_Bill_020->UseVisualStyleBackColor = false;
			   this->button_Bill_020->Click += gcnew System::EventHandler(this, &MainForm::button_Bill_005_Click);
			   // 
			   // button_Bill_010
			   // 
			   this->button_Bill_010->BackColor = System::Drawing::Color::Gold;
			   this->button_Bill_010->Font = (gcnew System::Drawing::Font(L"Impact", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Bill_010->Location = System::Drawing::Point(650, 128);
			   this->button_Bill_010->Name = L"button_Bill_010";
			   this->button_Bill_010->Size = System::Drawing::Size(36, 26);
			   this->button_Bill_010->TabIndex = 251;
			   this->button_Bill_010->Tag = L"10";
			   this->button_Bill_010->Text = L"10";
			   this->button_Bill_010->UseVisualStyleBackColor = false;
			   this->button_Bill_010->Click += gcnew System::EventHandler(this, &MainForm::button_Bill_005_Click);
			   // 
			   // button_Bill_005
			   // 
			   this->button_Bill_005->BackColor = System::Drawing::Color::Gold;
			   this->button_Bill_005->Font = (gcnew System::Drawing::Font(L"Impact", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Bill_005->Location = System::Drawing::Point(611, 128);
			   this->button_Bill_005->Name = L"button_Bill_005";
			   this->button_Bill_005->Size = System::Drawing::Size(33, 26);
			   this->button_Bill_005->TabIndex = 250;
			   this->button_Bill_005->Tag = L"5";
			   this->button_Bill_005->Text = L"5";
			   this->button_Bill_005->UseVisualStyleBackColor = false;
			   this->button_Bill_005->Click += gcnew System::EventHandler(this, &MainForm::button_Bill_005_Click);
			   // 
			   // label7
			   // 
			   this->label7->AutoSize = true;
			   this->label7->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label7->Location = System::Drawing::Point(77, 120);
			   this->label7->Name = L"label7";
			   this->label7->Size = System::Drawing::Size(190, 16);
			   this->label7->TabIndex = 256;
			   this->label7->Text = L"Стоимость монет в хоппере 2";
			   // 
			   // textBox_cost_coint_2
			   // 
			   this->textBox_cost_coint_2->Enabled = false;
			   this->textBox_cost_coint_2->Location = System::Drawing::Point(41, 118);
			   this->textBox_cost_coint_2->MaxLength = 4;
			   this->textBox_cost_coint_2->Name = L"textBox_cost_coint_2";
			   this->textBox_cost_coint_2->Size = System::Drawing::Size(36, 20);
			   this->textBox_cost_coint_2->TabIndex = 255;
			   this->textBox_cost_coint_2->Text = L"XXX";
			   // 
			   // label8
			   // 
			   this->label8->AutoSize = true;
			   this->label8->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label8->Location = System::Drawing::Point(77, 141);
			   this->label8->Name = L"label8";
			   this->label8->Size = System::Drawing::Size(189, 16);
			   this->label8->TabIndex = 258;
			   this->label8->Text = L"Стоимость карт в диспенсере";
			   // 
			   // textBox_cost_card
			   // 
			   this->textBox_cost_card->Enabled = false;
			   this->textBox_cost_card->Location = System::Drawing::Point(41, 139);
			   this->textBox_cost_card->MaxLength = 4;
			   this->textBox_cost_card->Name = L"textBox_cost_card";
			   this->textBox_cost_card->Size = System::Drawing::Size(36, 20);
			   this->textBox_cost_card->TabIndex = 257;
			   this->textBox_cost_card->Text = L"XXX";
			   // 
			   // label9
			   // 
			   this->label9->AutoSize = true;
			   this->label9->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label9->Location = System::Drawing::Point(77, 162);
			   this->label9->Name = L"label9";
			   this->label9->Size = System::Drawing::Size(125, 16);
			   this->label9->TabIndex = 260;
			   this->label9->Text = L"Количество кнопок";
			   // 
			   // textBox_number_buttons
			   // 
			   this->textBox_number_buttons->Enabled = false;
			   this->textBox_number_buttons->Location = System::Drawing::Point(41, 160);
			   this->textBox_number_buttons->MaxLength = 4;
			   this->textBox_number_buttons->Name = L"textBox_number_buttons";
			   this->textBox_number_buttons->Size = System::Drawing::Size(36, 20);
			   this->textBox_number_buttons->TabIndex = 259;
			   this->textBox_number_buttons->Text = L"XXX";
			   // 
			   // label10
			   // 
			   this->label10->AutoSize = true;
			   this->label10->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label10->Location = System::Drawing::Point(77, 225);
			   this->label10->Name = L"label10";
			   this->label10->Size = System::Drawing::Size(157, 16);
			   this->label10->TabIndex = 266;
			   this->label10->Text = L"Кол-во монет в хопперах";
			   // 
			   // textBox_number_coins
			   // 
			   this->textBox_number_coins->Enabled = false;
			   this->textBox_number_coins->Location = System::Drawing::Point(41, 223);
			   this->textBox_number_coins->MaxLength = 4;
			   this->textBox_number_coins->Name = L"textBox_number_coins";
			   this->textBox_number_coins->Size = System::Drawing::Size(36, 20);
			   this->textBox_number_coins->TabIndex = 265;
			   this->textBox_number_coins->Text = L"XXX";
			   // 
			   // label11
			   // 
			   this->label11->AutoSize = true;
			   this->label11->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label11->Location = System::Drawing::Point(77, 204);
			   this->label11->Name = L"label11";
			   this->label11->Size = System::Drawing::Size(231, 16);
			   this->label11->TabIndex = 264;
			   this->label11->Text = L"Кол-во выдаваемых карт за нажатие";
			   // 
			   // textBox_number_spit_out_cards
			   // 
			   this->textBox_number_spit_out_cards->Enabled = false;
			   this->textBox_number_spit_out_cards->Location = System::Drawing::Point(41, 202);
			   this->textBox_number_spit_out_cards->MaxLength = 4;
			   this->textBox_number_spit_out_cards->Name = L"textBox_number_spit_out_cards";
			   this->textBox_number_spit_out_cards->Size = System::Drawing::Size(36, 20);
			   this->textBox_number_spit_out_cards->TabIndex = 263;
			   this->textBox_number_spit_out_cards->Text = L"XXX";
			   // 
			   // label12
			   // 
			   this->label12->AutoSize = true;
			   this->label12->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label12->Location = System::Drawing::Point(77, 183);
			   this->label12->Name = L"label12";
			   this->label12->Size = System::Drawing::Size(239, 16);
			   this->label12->TabIndex = 262;
			   this->label12->Text = L"Кол-во выдаваемых монет за нажатие";
			   // 
			   // textBox_number_spit_out_coins
			   // 
			   this->textBox_number_spit_out_coins->Enabled = false;
			   this->textBox_number_spit_out_coins->Location = System::Drawing::Point(41, 181);
			   this->textBox_number_spit_out_coins->MaxLength = 4;
			   this->textBox_number_spit_out_coins->Name = L"textBox_number_spit_out_coins";
			   this->textBox_number_spit_out_coins->Size = System::Drawing::Size(36, 20);
			   this->textBox_number_spit_out_coins->TabIndex = 261;
			   this->textBox_number_spit_out_coins->Text = L"XXX";
			   // 
			   // label13
			   // 
			   this->label13->AutoSize = true;
			   this->label13->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label13->Location = System::Drawing::Point(77, 246);
			   this->label13->Name = L"label13";
			   this->label13->Size = System::Drawing::Size(158, 16);
			   this->label13->TabIndex = 268;
			   this->label13->Text = L"Кол-во карт в диспенсере";
			   // 
			   // textBox_number_cards
			   // 
			   this->textBox_number_cards->Enabled = false;
			   this->textBox_number_cards->Location = System::Drawing::Point(41, 244);
			   this->textBox_number_cards->MaxLength = 4;
			   this->textBox_number_cards->Name = L"textBox_number_cards";
			   this->textBox_number_cards->Size = System::Drawing::Size(36, 20);
			   this->textBox_number_cards->TabIndex = 267;
			   this->textBox_number_cards->Text = L"XXX";
			   // 
			   // button_SplitOutCards
			   // 
			   this->button_SplitOutCards->BackColor = System::Drawing::Color::Green;
			   this->button_SplitOutCards->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_SplitOutCards->Location = System::Drawing::Point(417, 268);
			   this->button_SplitOutCards->Name = L"button_SplitOutCards";
			   this->button_SplitOutCards->Size = System::Drawing::Size(130, 30);
			   this->button_SplitOutCards->TabIndex = 269;
			   this->button_SplitOutCards->Tag = L"Exchange";
			   this->button_SplitOutCards->Text = L"Выдача карты";
			   this->button_SplitOutCards->UseVisualStyleBackColor = false;
			   this->button_SplitOutCards->Click += gcnew System::EventHandler(this, &MainForm::button_SplitOutCards_Click);
			   // 
			   // label14
			   // 
			   this->label14->AutoSize = true;
			   this->label14->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label14->Location = System::Drawing::Point(394, 157);
			   this->label14->Name = L"label14";
			   this->label14->Size = System::Drawing::Size(61, 16);
			   this->label14->TabIndex = 271;
			   this->label14->Text = L"Хоппер 2";
			   // 
			   // textBox_Hopper_2
			   // 
			   this->textBox_Hopper_2->Enabled = false;
			   this->textBox_Hopper_2->Location = System::Drawing::Point(390, 175);
			   this->textBox_Hopper_2->MaxLength = 4;
			   this->textBox_Hopper_2->Name = L"textBox_Hopper_2";
			   this->textBox_Hopper_2->Size = System::Drawing::Size(50, 20);
			   this->textBox_Hopper_2->TabIndex = 270;
			   this->textBox_Hopper_2->Text = L"0";
			   // 
			   // label15
			   // 
			   this->label15->AutoSize = true;
			   this->label15->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label15->Location = System::Drawing::Point(77, 99);
			   this->label15->Name = L"label15";
			   this->label15->Size = System::Drawing::Size(190, 16);
			   this->label15->TabIndex = 273;
			   this->label15->Text = L"Стоимость монет в хоппере 1";
			   // 
			   // textBox_cost_coint_1
			   // 
			   this->textBox_cost_coint_1->Enabled = false;
			   this->textBox_cost_coint_1->Location = System::Drawing::Point(41, 97);
			   this->textBox_cost_coint_1->MaxLength = 4;
			   this->textBox_cost_coint_1->Name = L"textBox_cost_coint_1";
			   this->textBox_cost_coint_1->Size = System::Drawing::Size(36, 20);
			   this->textBox_cost_coint_1->TabIndex = 272;
			   this->textBox_cost_coint_1->Text = L"XXX";
			   // 
			   // button_Card
			   // 
			   this->button_Card->BackColor = System::Drawing::Color::Gold;
			   this->button_Card->Font = (gcnew System::Drawing::Font(L"Impact", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Card->Location = System::Drawing::Point(611, 38);
			   this->button_Card->Name = L"button_Card";
			   this->button_Card->Size = System::Drawing::Size(93, 26);
			   this->button_Card->TabIndex = 274;
			   this->button_Card->Tag = L"нет";
			   this->button_Card->Text = L"нет";
			   this->button_Card->UseVisualStyleBackColor = false;
			   this->button_Card->Click += gcnew System::EventHandler(this, &MainForm::button_Card_Click);
			   // 
			   // button_SettingsSoft
			   // 
			   this->button_SettingsSoft->BackColor = System::Drawing::Color::Gold;
			   this->button_SettingsSoft->Enabled = false;
			   this->button_SettingsSoft->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_SettingsSoft->Location = System::Drawing::Point(3, 427);
			   this->button_SettingsSoft->Name = L"button_SettingsSoft";
			   this->button_SettingsSoft->Size = System::Drawing::Size(130, 30);
			   this->button_SettingsSoft->TabIndex = 275;
			   this->button_SettingsSoft->Tag = L"Exchange";
			   this->button_SettingsSoft->Text = L"Settings";
			   this->button_SettingsSoft->UseVisualStyleBackColor = false;
			   this->button_SettingsSoft->Click += gcnew System::EventHandler(this, &MainForm::button1_Click_1);
			   // 
			   // button_Settings
			   // 
			   this->button_Settings->BackColor = System::Drawing::Color::Gray;
			   this->button_Settings->Enabled = false;
			   this->button_Settings->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Settings->Location = System::Drawing::Point(708, 191);
			   this->button_Settings->Name = L"button_Settings";
			   this->button_Settings->Size = System::Drawing::Size(119, 30);
			   this->button_Settings->TabIndex = 276;
			   this->button_Settings->Tag = L"Settings";
			   this->button_Settings->Text = L"Настройки";
			   this->button_Settings->UseVisualStyleBackColor = false;
			   this->button_Settings->Click += gcnew System::EventHandler(this, &MainForm::button_Settings_Click);
			   // 
			   // button_Left
			   // 
			   this->button_Left->BackColor = System::Drawing::Color::Gray;
			   this->button_Left->Enabled = false;
			   this->button_Left->Font = (gcnew System::Drawing::Font(L"Impact", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Left->Location = System::Drawing::Point(708, 259);
			   this->button_Left->Name = L"button_Left";
			   this->button_Left->Size = System::Drawing::Size(36, 26);
			   this->button_Left->TabIndex = 277;
			   this->button_Left->Tag = L"Left";
			   this->button_Left->UseVisualStyleBackColor = false;
			   this->button_Left->Click += gcnew System::EventHandler(this, &MainForm::button_Settings_Click);
			   // 
			   // button_Right
			   // 
			   this->button_Right->BackColor = System::Drawing::Color::Gray;
			   this->button_Right->Enabled = false;
			   this->button_Right->Font = (gcnew System::Drawing::Font(L"Impact", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Right->Location = System::Drawing::Point(793, 259);
			   this->button_Right->Name = L"button_Right";
			   this->button_Right->Size = System::Drawing::Size(36, 26);
			   this->button_Right->TabIndex = 278;
			   this->button_Right->Tag = L"Right";
			   this->button_Right->UseVisualStyleBackColor = false;
			   this->button_Right->Click += gcnew System::EventHandler(this, &MainForm::button_Settings_Click);
			   // 
			   // button_Down
			   // 
			   this->button_Down->BackColor = System::Drawing::Color::Gray;
			   this->button_Down->Enabled = false;
			   this->button_Down->Font = (gcnew System::Drawing::Font(L"Impact", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Down->Location = System::Drawing::Point(751, 291);
			   this->button_Down->Name = L"button_Down";
			   this->button_Down->Size = System::Drawing::Size(36, 26);
			   this->button_Down->TabIndex = 279;
			   this->button_Down->Tag = L"Down";
			   this->button_Down->UseVisualStyleBackColor = false;
			   this->button_Down->Click += gcnew System::EventHandler(this, &MainForm::button_Settings_Click);
			   // 
			   // button_Up
			   // 
			   this->button_Up->BackColor = System::Drawing::Color::Gray;
			   this->button_Up->Enabled = false;
			   this->button_Up->Font = (gcnew System::Drawing::Font(L"Impact", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Up->Location = System::Drawing::Point(751, 227);
			   this->button_Up->Name = L"button_Up";
			   this->button_Up->Size = System::Drawing::Size(36, 26);
			   this->button_Up->TabIndex = 280;
			   this->button_Up->Tag = L"Up";
			   this->button_Up->UseVisualStyleBackColor = false;
			   this->button_Up->Click += gcnew System::EventHandler(this, &MainForm::button_Settings_Click);
			   // 
			   // button_Ok
			   // 
			   this->button_Ok->BackColor = System::Drawing::Color::Gray;
			   this->button_Ok->Enabled = false;
			   this->button_Ok->Font = (gcnew System::Drawing::Font(L"Impact", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Ok->Location = System::Drawing::Point(751, 259);
			   this->button_Ok->Name = L"button_Ok";
			   this->button_Ok->Size = System::Drawing::Size(36, 26);
			   this->button_Ok->TabIndex = 281;
			   this->button_Ok->Tag = L"Ok";
			   this->button_Ok->Text = L"OK";
			   this->button_Ok->UseVisualStyleBackColor = false;
			   this->button_Ok->Click += gcnew System::EventHandler(this, &MainForm::button_Settings_Click);
			   // 
			   // button_Hopper_1
			   // 
			   this->button_Hopper_1->BackColor = System::Drawing::Color::Gray;
			   this->button_Hopper_1->Enabled = false;
			   this->button_Hopper_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Hopper_1->Location = System::Drawing::Point(553, 196);
			   this->button_Hopper_1->Name = L"button_Hopper_1";
			   this->button_Hopper_1->Size = System::Drawing::Size(119, 30);
			   this->button_Hopper_1->TabIndex = 282;
			   this->button_Hopper_1->Tag = L"Exchange";
			   this->button_Hopper_1->Text = L"Хоппер 1";
			   this->button_Hopper_1->UseVisualStyleBackColor = false;
			   this->button_Hopper_1->Click += gcnew System::EventHandler(this, &MainForm::button_Hopper_1_Click);
			   // 
			   // button_Hopper_2
			   // 
			   this->button_Hopper_2->BackColor = System::Drawing::Color::Gray;
			   this->button_Hopper_2->Enabled = false;
			   this->button_Hopper_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Hopper_2->Location = System::Drawing::Point(553, 232);
			   this->button_Hopper_2->Name = L"button_Hopper_2";
			   this->button_Hopper_2->Size = System::Drawing::Size(119, 30);
			   this->button_Hopper_2->TabIndex = 283;
			   this->button_Hopper_2->Tag = L"Exchange";
			   this->button_Hopper_2->Text = L"Хоппер 2";
			   this->button_Hopper_2->UseVisualStyleBackColor = false;
			   this->button_Hopper_2->Click += gcnew System::EventHandler(this, &MainForm::button_Hopper_2_Click);
			   // 
			   // label16
			   // 
			   this->label16->AutoSize = true;
			   this->label16->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label16->Location = System::Drawing::Point(77, 267);
			   this->label16->Name = L"label16";
			   this->label16->Size = System::Drawing::Size(161, 16);
			   this->label16->TabIndex = 285;
			   this->label16->Text = L"Пропорция выдачи монет";
			   // 
			   // textBox_ProportionHoppers
			   // 
			   this->textBox_ProportionHoppers->Enabled = false;
			   this->textBox_ProportionHoppers->Location = System::Drawing::Point(41, 265);
			   this->textBox_ProportionHoppers->MaxLength = 4;
			   this->textBox_ProportionHoppers->Name = L"textBox_ProportionHoppers";
			   this->textBox_ProportionHoppers->Size = System::Drawing::Size(36, 20);
			   this->textBox_ProportionHoppers->TabIndex = 284;
			   this->textBox_ProportionHoppers->Text = L"XXX";
			   // 
			   // label_TimeForSplitOut
			   // 
			   this->label_TimeForSplitOut->AutoSize = true;
			   this->label_TimeForSplitOut->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label_TimeForSplitOut->ForeColor = System::Drawing::Color::Maroon;
			   this->label_TimeForSplitOut->Location = System::Drawing::Point(445, 131);
			   this->label_TimeForSplitOut->Name = L"label_TimeForSplitOut";
			   this->label_TimeForSplitOut->Size = System::Drawing::Size(50, 16);
			   this->label_TimeForSplitOut->TabIndex = 286;
			   this->label_TimeForSplitOut->Text = L"Время:";
			   // 
			   // label17
			   // 
			   this->label17->AutoSize = true;
			   this->label17->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label17->Location = System::Drawing::Point(77, 330);
			   this->label17->Name = L"label17";
			   this->label17->Size = System::Drawing::Size(137, 16);
			   this->label17->TabIndex = 288;
			   this->label17->Text = L"Количество хопперов";
			   // 
			   // textBox_Num_Hoppers
			   // 
			   this->textBox_Num_Hoppers->Enabled = false;
			   this->textBox_Num_Hoppers->Location = System::Drawing::Point(41, 328);
			   this->textBox_Num_Hoppers->MaxLength = 1;
			   this->textBox_Num_Hoppers->Name = L"textBox_Num_Hoppers";
			   this->textBox_Num_Hoppers->Size = System::Drawing::Size(36, 20);
			   this->textBox_Num_Hoppers->TabIndex = 287;
			   this->textBox_Num_Hoppers->Text = L"XXX";
			   // 
			   // label18
			   // 
			   this->label18->AutoSize = true;
			   this->label18->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label18->Location = System::Drawing::Point(77, 351);
			   this->label18->Name = L"label18";
			   this->label18->Size = System::Drawing::Size(154, 16);
			   this->label18->TabIndex = 290;
			   this->label18->Text = L"Количество диспенсеров";
			   // 
			   // textBox_Num_Dispenser
			   // 
			   this->textBox_Num_Dispenser->Enabled = false;
			   this->textBox_Num_Dispenser->Location = System::Drawing::Point(41, 349);
			   this->textBox_Num_Dispenser->MaxLength = 1;
			   this->textBox_Num_Dispenser->Name = L"textBox_Num_Dispenser";
			   this->textBox_Num_Dispenser->Size = System::Drawing::Size(36, 20);
			   this->textBox_Num_Dispenser->TabIndex = 289;
			   this->textBox_Num_Dispenser->Text = L"XXX";
			   // 
			   // label19
			   // 
			   this->label19->AutoSize = true;
			   this->label19->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label19->Location = System::Drawing::Point(77, 372);
			   this->label19->Name = L"label19";
			   this->label19->Size = System::Drawing::Size(194, 16);
			   this->label19->TabIndex = 292;
			   this->label19->Text = L"Количество считывателей rfid";
			   // 
			   // textBox_Num_Card_Reader
			   // 
			   this->textBox_Num_Card_Reader->Enabled = false;
			   this->textBox_Num_Card_Reader->Location = System::Drawing::Point(41, 370);
			   this->textBox_Num_Card_Reader->MaxLength = 1;
			   this->textBox_Num_Card_Reader->Name = L"textBox_Num_Card_Reader";
			   this->textBox_Num_Card_Reader->Size = System::Drawing::Size(36, 20);
			   this->textBox_Num_Card_Reader->TabIndex = 291;
			   this->textBox_Num_Card_Reader->Text = L"XXX";
			   // 
			   // label20
			   // 
			   this->label20->AutoSize = true;
			   this->label20->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label20->Location = System::Drawing::Point(77, 288);
			   this->label20->Name = L"label20";
			   this->label20->Size = System::Drawing::Size(199, 16);
			   this->label20->TabIndex = 294;
			   this->label20->Text = L"Количество монетоприемников";
			   // 
			   // textBox_Number_CoinAcceptor
			   // 
			   this->textBox_Number_CoinAcceptor->Enabled = false;
			   this->textBox_Number_CoinAcceptor->Location = System::Drawing::Point(41, 286);
			   this->textBox_Number_CoinAcceptor->MaxLength = 1;
			   this->textBox_Number_CoinAcceptor->Name = L"textBox_Number_CoinAcceptor";
			   this->textBox_Number_CoinAcceptor->Size = System::Drawing::Size(36, 20);
			   this->textBox_Number_CoinAcceptor->TabIndex = 293;
			   this->textBox_Number_CoinAcceptor->Text = L"XXX";
			   // 
			   // label21
			   // 
			   this->label21->AutoSize = true;
			   this->label21->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label21->Location = System::Drawing::Point(77, 309);
			   this->label21->Name = L"label21";
			   this->label21->Size = System::Drawing::Size(196, 16);
			   this->label21->TabIndex = 296;
			   this->label21->Text = L"Количество купюроприемников";
			   // 
			   // textBox_Number_BillAcceptor
			   // 
			   this->textBox_Number_BillAcceptor->Enabled = false;
			   this->textBox_Number_BillAcceptor->Location = System::Drawing::Point(41, 307);
			   this->textBox_Number_BillAcceptor->MaxLength = 1;
			   this->textBox_Number_BillAcceptor->Name = L"textBox_Number_BillAcceptor";
			   this->textBox_Number_BillAcceptor->Size = System::Drawing::Size(36, 20);
			   this->textBox_Number_BillAcceptor->TabIndex = 295;
			   this->textBox_Number_BillAcceptor->Text = L"XXX";
			   // 
			   // button_Return
			   // 
			   this->button_Return->BackColor = System::Drawing::Color::Gray;
			   this->button_Return->Enabled = false;
			   this->button_Return->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Return->Location = System::Drawing::Point(708, 327);
			   this->button_Return->Name = L"button_Return";
			   this->button_Return->Size = System::Drawing::Size(119, 30);
			   this->button_Return->TabIndex = 297;
			   this->button_Return->Tag = L"Return";
			   this->button_Return->Text = L"Возврат";
			   this->button_Return->UseVisualStyleBackColor = false;
			   this->button_Return->Click += gcnew System::EventHandler(this, &MainForm::button_Settings_Click);
			   // 
			   // label_Display_1
			   // 
			   this->label_Display_1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_Display_1->AutoSize = true;
			   this->label_Display_1->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label_Display_1->ForeColor = System::Drawing::Color::Red;
			   this->label_Display_1->Location = System::Drawing::Point(1, 0);
			   this->label_Display_1->Name = L"label_Display_1";
			   this->label_Display_1->Size = System::Drawing::Size(38, 33);
			   this->label_Display_1->TabIndex = 244;
			   this->label_Display_1->Text = L"S.";
			   this->label_Display_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // panel1
			   // 
			   this->panel1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			   this->panel1->Controls->Add(this->label_Display_4);
			   this->panel1->Controls->Add(this->label_Display_3);
			   this->panel1->Controls->Add(this->label_Display_2);
			   this->panel1->Controls->Add(this->label_Display_1);
			   this->panel1->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->panel1->Location = System::Drawing::Point(162, 12);
			   this->panel1->Name = L"panel1";
			   this->panel1->Size = System::Drawing::Size(117, 34);
			   this->panel1->TabIndex = 244;
			   this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::panel1_Paint_1);
			   // 
			   // label_Display_4
			   // 
			   this->label_Display_4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_Display_4->AutoSize = true;
			   this->label_Display_4->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label_Display_4->ForeColor = System::Drawing::Color::Red;
			   this->label_Display_4->Location = System::Drawing::Point(82, 0);
			   this->label_Display_4->Name = L"label_Display_4";
			   this->label_Display_4->Size = System::Drawing::Size(38, 33);
			   this->label_Display_4->TabIndex = 300;
			   this->label_Display_4->Text = L"S.";
			   this->label_Display_4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label_Display_3
			   // 
			   this->label_Display_3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_Display_3->AutoSize = true;
			   this->label_Display_3->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label_Display_3->ForeColor = System::Drawing::Color::Red;
			   this->label_Display_3->Location = System::Drawing::Point(55, 0);
			   this->label_Display_3->Name = L"label_Display_3";
			   this->label_Display_3->Size = System::Drawing::Size(38, 33);
			   this->label_Display_3->TabIndex = 299;
			   this->label_Display_3->Text = L"S.";
			   this->label_Display_3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label_Display_2
			   // 
			   this->label_Display_2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_Display_2->AutoSize = true;
			   this->label_Display_2->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label_Display_2->ForeColor = System::Drawing::Color::Red;
			   this->label_Display_2->Location = System::Drawing::Point(28, 0);
			   this->label_Display_2->Name = L"label_Display_2";
			   this->label_Display_2->Size = System::Drawing::Size(38, 33);
			   this->label_Display_2->TabIndex = 298;
			   this->label_Display_2->Text = L"S.";
			   this->label_Display_2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // radioButton_Server
			   // 
			   this->radioButton_Server->AutoSize = true;
			   this->radioButton_Server->Checked = true;
			   this->radioButton_Server->Location = System::Drawing::Point(3, 44);
			   this->radioButton_Server->Name = L"radioButton_Server";
			   this->radioButton_Server->Size = System::Drawing::Size(56, 17);
			   this->radioButton_Server->TabIndex = 298;
			   this->radioButton_Server->TabStop = true;
			   this->radioButton_Server->Text = L"Server";
			   this->radioButton_Server->UseVisualStyleBackColor = true;
			   // 
			   // radioButton_Client
			   // 
			   this->radioButton_Client->AutoSize = true;
			   this->radioButton_Client->Location = System::Drawing::Point(59, 44);
			   this->radioButton_Client->Name = L"radioButton_Client";
			   this->radioButton_Client->Size = System::Drawing::Size(51, 17);
			   this->radioButton_Client->TabIndex = 299;
			   this->radioButton_Client->Text = L"Client";
			   this->radioButton_Client->UseVisualStyleBackColor = true;
			   // 
			   // comboBox_COMPorts
			   // 
			   this->comboBox_COMPorts->FormattingEnabled = true;
			   this->comboBox_COMPorts->Items->AddRange(gcnew cli::array< System::Object^  >(22) {
				   L"None", L"Stack My", L"Stack Player 1",
					   L"Stack Player 2", L"Stack Player 3", L"Stack Player 4", L"Stack Player 5", L"Bet My", L"Bet Player 1", L"Bet Player 2", L"Bet Player 3",
					   L"Bet Player 4", L"Bet Player 5", L"Pot", L"Call", L"Raise", L"Header", L"Header Dollar Bitmap", L"Pot Dollar Bitmap", L"Bet Dollar Bitmap",
					   L"Call/Raise Dollar Bitmap", L"Stack Dollar Bitmap"
			   });
			   this->comboBox_COMPorts->Location = System::Drawing::Point(557, 346);
			   this->comboBox_COMPorts->Name = L"comboBox_COMPorts";
			   this->comboBox_COMPorts->Size = System::Drawing::Size(100, 21);
			   this->comboBox_COMPorts->TabIndex = 300;
			   this->comboBox_COMPorts->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBox_COMPorts_SelectedIndexChanged);
			   // 
			   // button_Connect_COM
			   // 
			   this->button_Connect_COM->BackColor = System::Drawing::Color::Green;
			   this->button_Connect_COM->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Connect_COM->Location = System::Drawing::Point(417, 341);
			   this->button_Connect_COM->Name = L"button_Connect_COM";
			   this->button_Connect_COM->Size = System::Drawing::Size(130, 30);
			   this->button_Connect_COM->TabIndex = 301;
			   this->button_Connect_COM->Tag = L"Start";
			   this->button_Connect_COM->Text = L"Connect";
			   this->button_Connect_COM->UseVisualStyleBackColor = false;
			   this->button_Connect_COM->Click += gcnew System::EventHandler(this, &MainForm::button_Connect_COM_Click);
			   // 
			   // label22
			   // 
			   this->label22->AutoSize = true;
			   this->label22->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label22->ForeColor = System::Drawing::Color::Maroon;
			   this->label22->Location = System::Drawing::Point(419, 322);
			   this->label22->Name = L"label22";
			   this->label22->Size = System::Drawing::Size(93, 16);
			   this->label22->TabIndex = 302;
			   this->label22->Text = L"Отладка USB:";
			   // 
			   // serialPort
			   // 
			   this->serialPort->BaudRate = 115200;
			   this->serialPort->ReadTimeout = 5000;
			   this->serialPort->WriteTimeout = 5000;
			   // 
			   // label_STATE_COM
			   // 
			   this->label_STATE_COM->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label_STATE_COM->ForeColor = System::Drawing::Color::Red;
			   this->label_STATE_COM->Location = System::Drawing::Point(516, 321);
			   this->label_STATE_COM->Name = L"label_STATE_COM";
			   this->label_STATE_COM->Size = System::Drawing::Size(186, 17);
			   this->label_STATE_COM->TabIndex = 303;
			   this->label_STATE_COM->Text = L"DEVICE NOT CONNECTED";
			   // 
			   // button_Start_USB
			   // 
			   this->button_Start_USB->BackColor = System::Drawing::Color::Gray;
			   this->button_Start_USB->Enabled = false;
			   this->button_Start_USB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Start_USB->Location = System::Drawing::Point(417, 406);
			   this->button_Start_USB->Name = L"button_Start_USB";
			   this->button_Start_USB->Size = System::Drawing::Size(130, 30);
			   this->button_Start_USB->TabIndex = 304;
			   this->button_Start_USB->Tag = L"Start USB";
			   this->button_Start_USB->Text = L"Start";
			   this->button_Start_USB->UseVisualStyleBackColor = false;
			   this->button_Start_USB->Click += gcnew System::EventHandler(this, &MainForm::button_Start_USB_Click);
			   // 
			   // button_Disconnect_COM
			   // 
			   this->button_Disconnect_COM->BackColor = System::Drawing::Color::Green;
			   this->button_Disconnect_COM->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Disconnect_COM->Location = System::Drawing::Point(417, 370);
			   this->button_Disconnect_COM->Name = L"button_Disconnect_COM";
			   this->button_Disconnect_COM->Size = System::Drawing::Size(130, 30);
			   this->button_Disconnect_COM->TabIndex = 305;
			   this->button_Disconnect_COM->Tag = L"Start";
			   this->button_Disconnect_COM->Text = L"Disconnect";
			   this->button_Disconnect_COM->UseVisualStyleBackColor = false;
			   this->button_Disconnect_COM->Click += gcnew System::EventHandler(this, &MainForm::button_Disconnect_COM_Click);
			   // 
			   // button1
			   // 
			   this->button1->BackColor = System::Drawing::Color::Green;
			   this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button1->Location = System::Drawing::Point(663, 341);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(39, 30);
			   this->button1->TabIndex = 306;
			   this->button1->Tag = L"Start";
			   this->button1->Text = L"@";
			   this->button1->UseVisualStyleBackColor = false;
			   this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click_2);
			   // 
			   // panel2
			   // 
			   this->panel2->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			   this->panel2->Controls->Add(this->label_Display_8);
			   this->panel2->Controls->Add(this->label_Display_7);
			   this->panel2->Controls->Add(this->label_Display_6);
			   this->panel2->Controls->Add(this->label_Display_5);
			   this->panel2->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->panel2->Location = System::Drawing::Point(162, 48);
			   this->panel2->Name = L"panel2";
			   this->panel2->Size = System::Drawing::Size(117, 34);
			   this->panel2->TabIndex = 307;
			   // 
			   // label_Display_8
			   // 
			   this->label_Display_8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_Display_8->AutoSize = true;
			   this->label_Display_8->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label_Display_8->ForeColor = System::Drawing::Color::Red;
			   this->label_Display_8->Location = System::Drawing::Point(82, 0);
			   this->label_Display_8->Name = L"label_Display_8";
			   this->label_Display_8->Size = System::Drawing::Size(38, 33);
			   this->label_Display_8->TabIndex = 300;
			   this->label_Display_8->Text = L"S.";
			   this->label_Display_8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label_Display_7
			   // 
			   this->label_Display_7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_Display_7->AutoSize = true;
			   this->label_Display_7->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label_Display_7->ForeColor = System::Drawing::Color::Red;
			   this->label_Display_7->Location = System::Drawing::Point(55, 0);
			   this->label_Display_7->Name = L"label_Display_7";
			   this->label_Display_7->Size = System::Drawing::Size(38, 33);
			   this->label_Display_7->TabIndex = 299;
			   this->label_Display_7->Text = L"S.";
			   this->label_Display_7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label_Display_6
			   // 
			   this->label_Display_6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_Display_6->AutoSize = true;
			   this->label_Display_6->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label_Display_6->ForeColor = System::Drawing::Color::Red;
			   this->label_Display_6->Location = System::Drawing::Point(28, 0);
			   this->label_Display_6->Name = L"label_Display_6";
			   this->label_Display_6->Size = System::Drawing::Size(38, 33);
			   this->label_Display_6->TabIndex = 298;
			   this->label_Display_6->Text = L"S.";
			   this->label_Display_6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label_Display_5
			   // 
			   this->label_Display_5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_Display_5->AutoSize = true;
			   this->label_Display_5->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label_Display_5->ForeColor = System::Drawing::Color::Red;
			   this->label_Display_5->Location = System::Drawing::Point(1, 0);
			   this->label_Display_5->Name = L"label_Display_5";
			   this->label_Display_5->Size = System::Drawing::Size(38, 33);
			   this->label_Display_5->TabIndex = 244;
			   this->label_Display_5->Text = L"S.";
			   this->label_Display_5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // radioButton_Test
			   // 
			   this->radioButton_Test->AutoSize = true;
			   this->radioButton_Test->Location = System::Drawing::Point(111, 44);
			   this->radioButton_Test->Name = L"radioButton_Test";
			   this->radioButton_Test->Size = System::Drawing::Size(46, 17);
			   this->radioButton_Test->TabIndex = 308;
			   this->radioButton_Test->Text = L"Test";
			   this->radioButton_Test->UseVisualStyleBackColor = true;
			   // 
			   // button_Test
			   // 
			   this->button_Test->BackColor = System::Drawing::Color::Green;
			   this->button_Test->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Test->Location = System::Drawing::Point(793, 437);
			   this->button_Test->Name = L"button_Test";
			   this->button_Test->Size = System::Drawing::Size(130, 30);
			   this->button_Test->TabIndex = 309;
			   this->button_Test->Tag = L"Exchange";
			   this->button_Test->Text = L"Test";
			   this->button_Test->UseVisualStyleBackColor = false;
			   this->button_Test->Click += gcnew System::EventHandler(this, &MainForm::button_Test_Click);
			   // 
			   // richTextBox_WS_Client_1
			   // 
			   this->richTextBox_WS_Client_1->Location = System::Drawing::Point(14, 473);
			   this->richTextBox_WS_Client_1->Name = L"richTextBox_WS_Client_1";
			   this->richTextBox_WS_Client_1->Size = System::Drawing::Size(803, 68);
			   this->richTextBox_WS_Client_1->TabIndex = 311;
			   this->richTextBox_WS_Client_1->Tag = L"1";
			   this->richTextBox_WS_Client_1->Text = resources->GetString(L"richTextBox_WS_Client_1.Text");
			   // 
			   // textBox_WS_Client_2
			   // 
			   this->textBox_WS_Client_2->Location = System::Drawing::Point(14, 544);
			   this->textBox_WS_Client_2->MaxLength = 1;
			   this->textBox_WS_Client_2->Name = L"textBox_WS_Client_2";
			   this->textBox_WS_Client_2->Size = System::Drawing::Size(803, 20);
			   this->textBox_WS_Client_2->TabIndex = 312;
			   this->textBox_WS_Client_2->Tag = L"2";
			   this->textBox_WS_Client_2->Text = L"{\"message\":\"all_options\",\"data\":[]}";
			   // 
			   // button_Send_To_WS_Server_1
			   // 
			   this->button_Send_To_WS_Server_1->BackColor = System::Drawing::Color::Green;
			   this->button_Send_To_WS_Server_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold,
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->button_Send_To_WS_Server_1->Location = System::Drawing::Point(823, 473);
			   this->button_Send_To_WS_Server_1->Name = L"button_Send_To_WS_Server_1";
			   this->button_Send_To_WS_Server_1->Size = System::Drawing::Size(61, 30);
			   this->button_Send_To_WS_Server_1->TabIndex = 313;
			   this->button_Send_To_WS_Server_1->Tag = L"Send_To_WS_Server_1";
			   this->button_Send_To_WS_Server_1->Text = L"Send";
			   this->button_Send_To_WS_Server_1->UseVisualStyleBackColor = false;
			   this->button_Send_To_WS_Server_1->Click += gcnew System::EventHandler(this, &MainForm::button_Send_To_WS_Server_1_Click);
			   // 
			   // textBox_WS_Client_3
			   // 
			   this->textBox_WS_Client_3->Location = System::Drawing::Point(14, 567);
			   this->textBox_WS_Client_3->MaxLength = 1;
			   this->textBox_WS_Client_3->Name = L"textBox_WS_Client_3";
			   this->textBox_WS_Client_3->Size = System::Drawing::Size(803, 20);
			   this->textBox_WS_Client_3->TabIndex = 314;
			   this->textBox_WS_Client_3->Tag = L"3";
			   this->textBox_WS_Client_3->Text = L"1";
			   // 
			   // button_Send_To_WS_Server_2
			   // 
			   this->button_Send_To_WS_Server_2->BackColor = System::Drawing::Color::Green;
			   this->button_Send_To_WS_Server_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold,
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->button_Send_To_WS_Server_2->Location = System::Drawing::Point(823, 542);
			   this->button_Send_To_WS_Server_2->Name = L"button_Send_To_WS_Server_2";
			   this->button_Send_To_WS_Server_2->Size = System::Drawing::Size(61, 27);
			   this->button_Send_To_WS_Server_2->TabIndex = 315;
			   this->button_Send_To_WS_Server_2->Tag = L"Send_To_WS_Server_2";
			   this->button_Send_To_WS_Server_2->Text = L"Send";
			   this->button_Send_To_WS_Server_2->UseVisualStyleBackColor = false;
			   this->button_Send_To_WS_Server_2->Click += gcnew System::EventHandler(this, &MainForm::button_Send_To_WS_Server_1_Click);
			   // 
			   // button_Send_To_WS_Server_3
			   // 
			   this->button_Send_To_WS_Server_3->BackColor = System::Drawing::Color::Green;
			   this->button_Send_To_WS_Server_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold,
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->button_Send_To_WS_Server_3->Location = System::Drawing::Point(823, 567);
			   this->button_Send_To_WS_Server_3->Name = L"button_Send_To_WS_Server_3";
			   this->button_Send_To_WS_Server_3->Size = System::Drawing::Size(61, 27);
			   this->button_Send_To_WS_Server_3->TabIndex = 316;
			   this->button_Send_To_WS_Server_3->Tag = L"Send_To_WS_Server_3";
			   this->button_Send_To_WS_Server_3->Text = L"Send";
			   this->button_Send_To_WS_Server_3->UseVisualStyleBackColor = false;
			   this->button_Send_To_WS_Server_3->Click += gcnew System::EventHandler(this, &MainForm::button_Send_To_WS_Server_1_Click);
			   // 
			   // button_Send_To_WS_Server_4
			   // 
			   this->button_Send_To_WS_Server_4->BackColor = System::Drawing::Color::Green;
			   this->button_Send_To_WS_Server_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold,
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->button_Send_To_WS_Server_4->Location = System::Drawing::Point(823, 592);
			   this->button_Send_To_WS_Server_4->Name = L"button_Send_To_WS_Server_4";
			   this->button_Send_To_WS_Server_4->Size = System::Drawing::Size(61, 27);
			   this->button_Send_To_WS_Server_4->TabIndex = 317;
			   this->button_Send_To_WS_Server_4->Tag = L"Send_To_WS_Server_4";
			   this->button_Send_To_WS_Server_4->Text = L"Send";
			   this->button_Send_To_WS_Server_4->UseVisualStyleBackColor = false;
			   this->button_Send_To_WS_Server_4->Click += gcnew System::EventHandler(this, &MainForm::button_Send_To_WS_Server_1_Click);
			   // 
			   // textBox_WS_Client_4
			   // 
			   this->textBox_WS_Client_4->Location = System::Drawing::Point(14, 592);
			   this->textBox_WS_Client_4->MaxLength = 1;
			   this->textBox_WS_Client_4->Name = L"textBox_WS_Client_4";
			   this->textBox_WS_Client_4->Size = System::Drawing::Size(803, 20);
			   this->textBox_WS_Client_4->TabIndex = 318;
			   this->textBox_WS_Client_4->Tag = L"3";
			   this->textBox_WS_Client_4->Text = L"1";
			   // 
			   // button_Request_State_1
			   // 
			   this->button_Request_State_1->BackColor = System::Drawing::Color::Green;
			   this->button_Request_State_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Request_State_1->Location = System::Drawing::Point(871, 31);
			   this->button_Request_State_1->Name = L"button_Request_State_1";
			   this->button_Request_State_1->Size = System::Drawing::Size(88, 25);
			   this->button_Request_State_1->TabIndex = 319;
			   this->button_Request_State_1->Tag = L"hopper_1";
			   this->button_Request_State_1->Text = L"Хоппер 1";
			   this->button_Request_State_1->UseVisualStyleBackColor = false;
			   this->button_Request_State_1->Click += gcnew System::EventHandler(this, &MainForm::button_Request_State_1_Click);
			   // 
			   // label23
			   // 
			   this->label23->AutoSize = true;
			   this->label23->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label23->ForeColor = System::Drawing::Color::Maroon;
			   this->label23->Location = System::Drawing::Point(839, 9);
			   this->label23->Name = L"label23";
			   this->label23->Size = System::Drawing::Size(120, 16);
			   this->label23->TabIndex = 320;
			   this->label23->Text = L"Запрос состояний:";
			   // 
			   // button_Request_State_2
			   // 
			   this->button_Request_State_2->BackColor = System::Drawing::Color::Green;
			   this->button_Request_State_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Request_State_2->Location = System::Drawing::Point(871, 57);
			   this->button_Request_State_2->Name = L"button_Request_State_2";
			   this->button_Request_State_2->Size = System::Drawing::Size(88, 25);
			   this->button_Request_State_2->TabIndex = 321;
			   this->button_Request_State_2->Tag = L"hopper_2";
			   this->button_Request_State_2->Text = L"Хоппер 2";
			   this->button_Request_State_2->UseVisualStyleBackColor = false;
			   this->button_Request_State_2->Click += gcnew System::EventHandler(this, &MainForm::button_Request_State_1_Click);
			   // 
			   // button_Request_State_3
			   // 
			   this->button_Request_State_3->BackColor = System::Drawing::Color::Green;
			   this->button_Request_State_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Request_State_3->Location = System::Drawing::Point(871, 83);
			   this->button_Request_State_3->Name = L"button_Request_State_3";
			   this->button_Request_State_3->Size = System::Drawing::Size(88, 25);
			   this->button_Request_State_3->TabIndex = 322;
			   this->button_Request_State_3->Tag = L"hopper_3";
			   this->button_Request_State_3->Text = L"Хоппер 3";
			   this->button_Request_State_3->UseVisualStyleBackColor = false;
			   this->button_Request_State_3->Click += gcnew System::EventHandler(this, &MainForm::button_Request_State_1_Click);
			   // 
			   // textBox_sett_Number_BillAcceptor
			   // 
			   this->textBox_sett_Number_BillAcceptor->Location = System::Drawing::Point(3, 307);
			   this->textBox_sett_Number_BillAcceptor->MaxLength = 1;
			   this->textBox_sett_Number_BillAcceptor->Name = L"textBox_sett_Number_BillAcceptor";
			   this->textBox_sett_Number_BillAcceptor->Size = System::Drawing::Size(36, 20);
			   this->textBox_sett_Number_BillAcceptor->TabIndex = 336;
			   this->textBox_sett_Number_BillAcceptor->Text = L"1";
			   // 
			   // textBox_sett_Number_CoinAcceptor
			   // 
			   this->textBox_sett_Number_CoinAcceptor->Location = System::Drawing::Point(3, 286);
			   this->textBox_sett_Number_CoinAcceptor->MaxLength = 1;
			   this->textBox_sett_Number_CoinAcceptor->Name = L"textBox_sett_Number_CoinAcceptor";
			   this->textBox_sett_Number_CoinAcceptor->Size = System::Drawing::Size(36, 20);
			   this->textBox_sett_Number_CoinAcceptor->TabIndex = 335;
			   this->textBox_sett_Number_CoinAcceptor->Text = L"0";
			   // 
			   // textBox_sett_Num_Card_Reader
			   // 
			   this->textBox_sett_Num_Card_Reader->Location = System::Drawing::Point(3, 370);
			   this->textBox_sett_Num_Card_Reader->MaxLength = 1;
			   this->textBox_sett_Num_Card_Reader->Name = L"textBox_sett_Num_Card_Reader";
			   this->textBox_sett_Num_Card_Reader->Size = System::Drawing::Size(36, 20);
			   this->textBox_sett_Num_Card_Reader->TabIndex = 334;
			   this->textBox_sett_Num_Card_Reader->Text = L"0";
			   // 
			   // textBox_sett_Num_Dispenser
			   // 
			   this->textBox_sett_Num_Dispenser->Location = System::Drawing::Point(3, 349);
			   this->textBox_sett_Num_Dispenser->MaxLength = 1;
			   this->textBox_sett_Num_Dispenser->Name = L"textBox_sett_Num_Dispenser";
			   this->textBox_sett_Num_Dispenser->Size = System::Drawing::Size(36, 20);
			   this->textBox_sett_Num_Dispenser->TabIndex = 333;
			   this->textBox_sett_Num_Dispenser->Text = L"0";
			   // 
			   // textBox_sett_Num_Hoppers
			   // 
			   this->textBox_sett_Num_Hoppers->Location = System::Drawing::Point(3, 328);
			   this->textBox_sett_Num_Hoppers->MaxLength = 1;
			   this->textBox_sett_Num_Hoppers->Name = L"textBox_sett_Num_Hoppers";
			   this->textBox_sett_Num_Hoppers->Size = System::Drawing::Size(36, 20);
			   this->textBox_sett_Num_Hoppers->TabIndex = 332;
			   this->textBox_sett_Num_Hoppers->Text = L"2";
			   // 
			   // textBox_sett_ProportionHoppers
			   // 
			   this->textBox_sett_ProportionHoppers->Location = System::Drawing::Point(3, 265);
			   this->textBox_sett_ProportionHoppers->MaxLength = 4;
			   this->textBox_sett_ProportionHoppers->Name = L"textBox_sett_ProportionHoppers";
			   this->textBox_sett_ProportionHoppers->Size = System::Drawing::Size(36, 20);
			   this->textBox_sett_ProportionHoppers->TabIndex = 331;
			   this->textBox_sett_ProportionHoppers->Text = L"60";
			   // 
			   // textBox_sett_cost_coint_1
			   // 
			   this->textBox_sett_cost_coint_1->Location = System::Drawing::Point(3, 97);
			   this->textBox_sett_cost_coint_1->MaxLength = 4;
			   this->textBox_sett_cost_coint_1->Name = L"textBox_sett_cost_coint_1";
			   this->textBox_sett_cost_coint_1->Size = System::Drawing::Size(36, 20);
			   this->textBox_sett_cost_coint_1->TabIndex = 330;
			   this->textBox_sett_cost_coint_1->Text = L"1";
			   // 
			   // textBox_sett_number_cards
			   // 
			   this->textBox_sett_number_cards->Location = System::Drawing::Point(3, 244);
			   this->textBox_sett_number_cards->MaxLength = 4;
			   this->textBox_sett_number_cards->Name = L"textBox_sett_number_cards";
			   this->textBox_sett_number_cards->Size = System::Drawing::Size(36, 20);
			   this->textBox_sett_number_cards->TabIndex = 329;
			   this->textBox_sett_number_cards->Text = L"0";
			   // 
			   // textBox_sett_number_coins
			   // 
			   this->textBox_sett_number_coins->Location = System::Drawing::Point(3, 223);
			   this->textBox_sett_number_coins->MaxLength = 4;
			   this->textBox_sett_number_coins->Name = L"textBox_sett_number_coins";
			   this->textBox_sett_number_coins->Size = System::Drawing::Size(36, 20);
			   this->textBox_sett_number_coins->TabIndex = 328;
			   this->textBox_sett_number_coins->Text = L"500";
			   // 
			   // textBox_sett_number_spit_out_cards
			   // 
			   this->textBox_sett_number_spit_out_cards->Location = System::Drawing::Point(3, 202);
			   this->textBox_sett_number_spit_out_cards->MaxLength = 4;
			   this->textBox_sett_number_spit_out_cards->Name = L"textBox_sett_number_spit_out_cards";
			   this->textBox_sett_number_spit_out_cards->Size = System::Drawing::Size(36, 20);
			   this->textBox_sett_number_spit_out_cards->TabIndex = 327;
			   this->textBox_sett_number_spit_out_cards->Text = L"0";
			   // 
			   // textBox_sett_number_spit_out_coins
			   // 
			   this->textBox_sett_number_spit_out_coins->Location = System::Drawing::Point(3, 181);
			   this->textBox_sett_number_spit_out_coins->MaxLength = 4;
			   this->textBox_sett_number_spit_out_coins->Name = L"textBox_sett_number_spit_out_coins";
			   this->textBox_sett_number_spit_out_coins->Size = System::Drawing::Size(36, 20);
			   this->textBox_sett_number_spit_out_coins->TabIndex = 326;
			   this->textBox_sett_number_spit_out_coins->Text = L"0";
			   // 
			   // textBox_sett_number_buttons
			   // 
			   this->textBox_sett_number_buttons->Location = System::Drawing::Point(3, 160);
			   this->textBox_sett_number_buttons->MaxLength = 4;
			   this->textBox_sett_number_buttons->Name = L"textBox_sett_number_buttons";
			   this->textBox_sett_number_buttons->Size = System::Drawing::Size(36, 20);
			   this->textBox_sett_number_buttons->TabIndex = 325;
			   this->textBox_sett_number_buttons->Text = L"2";
			   // 
			   // textBox_sett_cost_card
			   // 
			   this->textBox_sett_cost_card->Location = System::Drawing::Point(3, 139);
			   this->textBox_sett_cost_card->MaxLength = 4;
			   this->textBox_sett_cost_card->Name = L"textBox_sett_cost_card";
			   this->textBox_sett_cost_card->Size = System::Drawing::Size(36, 20);
			   this->textBox_sett_cost_card->TabIndex = 324;
			   this->textBox_sett_cost_card->Text = L"0";
			   // 
			   // textBox_sett_cost_coint_2
			   // 
			   this->textBox_sett_cost_coint_2->Location = System::Drawing::Point(3, 118);
			   this->textBox_sett_cost_coint_2->MaxLength = 4;
			   this->textBox_sett_cost_coint_2->Name = L"textBox_sett_cost_coint_2";
			   this->textBox_sett_cost_coint_2->Size = System::Drawing::Size(36, 20);
			   this->textBox_sett_cost_coint_2->TabIndex = 323;
			   this->textBox_sett_cost_coint_2->Text = L"2";
			   // 
			   // button_Encashment
			   // 
			   this->button_Encashment->BackColor = System::Drawing::Color::Gray;
			   this->button_Encashment->Enabled = false;
			   this->button_Encashment->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Encashment->Location = System::Drawing::Point(840, 190);
			   this->button_Encashment->Name = L"button_Encashment";
			   this->button_Encashment->Size = System::Drawing::Size(119, 30);
			   this->button_Encashment->TabIndex = 337;
			   this->button_Encashment->Tag = L"Encashment";
			   this->button_Encashment->Text = L"Инкассация";
			   this->button_Encashment->UseVisualStyleBackColor = false;
			   this->button_Encashment->Click += gcnew System::EventHandler(this, &MainForm::button_Settings_Click);
			   // 
			   // textBox_Hopper2_Real
			   // 
			   this->textBox_Hopper2_Real->Location = System::Drawing::Point(324, 175);
			   this->textBox_Hopper2_Real->MaxLength = 4;
			   this->textBox_Hopper2_Real->Name = L"textBox_Hopper2_Real";
			   this->textBox_Hopper2_Real->Size = System::Drawing::Size(50, 20);
			   this->textBox_Hopper2_Real->TabIndex = 338;
			   this->textBox_Hopper2_Real->Tag = L"Hopper_2";
			   this->textBox_Hopper2_Real->Text = L"10";
			   // 
			   // textBox_Hopper1_Real
			   // 
			   this->textBox_Hopper1_Real->Location = System::Drawing::Point(323, 128);
			   this->textBox_Hopper1_Real->MaxLength = 4;
			   this->textBox_Hopper1_Real->Name = L"textBox_Hopper1_Real";
			   this->textBox_Hopper1_Real->Size = System::Drawing::Size(50, 20);
			   this->textBox_Hopper1_Real->TabIndex = 339;
			   this->textBox_Hopper1_Real->Tag = L"Hopper_1";
			   this->textBox_Hopper1_Real->Text = L"10";
			   // 
			   // label_Sensor_Hopper1
			   // 
			   this->label_Sensor_Hopper1->AutoSize = true;
			   this->label_Sensor_Hopper1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label_Sensor_Hopper1->ForeColor = System::Drawing::Color::Maroon;
			   this->label_Sensor_Hopper1->Location = System::Drawing::Point(324, 109);
			   this->label_Sensor_Hopper1->Name = L"label_Sensor_Hopper1";
			   this->label_Sensor_Hopper1->Size = System::Drawing::Size(66, 16);
			   this->label_Sensor_Hopper1->TabIndex = 340;
			   this->label_Sensor_Hopper1->Text = L"Sensor: 30";
			   // 
			   // label_Sensor_Hopper2
			   // 
			   this->label_Sensor_Hopper2->AutoSize = true;
			   this->label_Sensor_Hopper2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label_Sensor_Hopper2->ForeColor = System::Drawing::Color::Maroon;
			   this->label_Sensor_Hopper2->Location = System::Drawing::Point(324, 156);
			   this->label_Sensor_Hopper2->Name = L"label_Sensor_Hopper2";
			   this->label_Sensor_Hopper2->Size = System::Drawing::Size(66, 16);
			   this->label_Sensor_Hopper2->TabIndex = 341;
			   this->label_Sensor_Hopper2->Text = L"Sensor: 30";
			   // 
			   // textBox_sett_Diapason_Hold_Acceptors
			   // 
			   this->textBox_sett_Diapason_Hold_Acceptors->Location = System::Drawing::Point(3, 391);
			   this->textBox_sett_Diapason_Hold_Acceptors->MaxLength = 4;
			   this->textBox_sett_Diapason_Hold_Acceptors->Name = L"textBox_sett_Diapason_Hold_Acceptors";
			   this->textBox_sett_Diapason_Hold_Acceptors->Size = System::Drawing::Size(36, 20);
			   this->textBox_sett_Diapason_Hold_Acceptors->TabIndex = 344;
			   this->textBox_sett_Diapason_Hold_Acceptors->Text = L"100";
			   // 
			   // label26
			   // 
			   this->label26->AutoSize = true;
			   this->label26->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label26->Location = System::Drawing::Point(77, 393);
			   this->label26->Name = L"label26";
			   this->label26->Size = System::Drawing::Size(312, 16);
			   this->label26->TabIndex = 343;
			   this->label26->Text = L"Разность для отключения приемников (в копейках)";
			   // 
			   // textBox_Diapason_Hold_Acceptors
			   // 
			   this->textBox_Diapason_Hold_Acceptors->Enabled = false;
			   this->textBox_Diapason_Hold_Acceptors->Location = System::Drawing::Point(41, 391);
			   this->textBox_Diapason_Hold_Acceptors->MaxLength = 4;
			   this->textBox_Diapason_Hold_Acceptors->Name = L"textBox_Diapason_Hold_Acceptors";
			   this->textBox_Diapason_Hold_Acceptors->Size = System::Drawing::Size(36, 20);
			   this->textBox_Diapason_Hold_Acceptors->TabIndex = 342;
			   this->textBox_Diapason_Hold_Acceptors->Text = L"XXX";
			   // 
			   // checkBox_Enable_Sensor_Hopper1
			   // 
			   this->checkBox_Enable_Sensor_Hopper1->AutoSize = true;
			   this->checkBox_Enable_Sensor_Hopper1->Location = System::Drawing::Point(304, 112);
			   this->checkBox_Enable_Sensor_Hopper1->Name = L"checkBox_Enable_Sensor_Hopper1";
			   this->checkBox_Enable_Sensor_Hopper1->Size = System::Drawing::Size(15, 14);
			   this->checkBox_Enable_Sensor_Hopper1->TabIndex = 345;
			   this->checkBox_Enable_Sensor_Hopper1->UseVisualStyleBackColor = true;
			   // 
			   // checkBox_Enable_Sensor_Hopper2
			   // 
			   this->checkBox_Enable_Sensor_Hopper2->AutoSize = true;
			   this->checkBox_Enable_Sensor_Hopper2->Location = System::Drawing::Point(304, 159);
			   this->checkBox_Enable_Sensor_Hopper2->Name = L"checkBox_Enable_Sensor_Hopper2";
			   this->checkBox_Enable_Sensor_Hopper2->Size = System::Drawing::Size(15, 14);
			   this->checkBox_Enable_Sensor_Hopper2->TabIndex = 346;
			   this->checkBox_Enable_Sensor_Hopper2->UseVisualStyleBackColor = true;
			   // 
			   // MainForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(965, 618);
			   this->Controls->Add(this->checkBox_Enable_Sensor_Hopper2);
			   this->Controls->Add(this->checkBox_Enable_Sensor_Hopper1);
			   this->Controls->Add(this->textBox_sett_Diapason_Hold_Acceptors);
			   this->Controls->Add(this->label26);
			   this->Controls->Add(this->textBox_Diapason_Hold_Acceptors);
			   this->Controls->Add(this->label_Sensor_Hopper2);
			   this->Controls->Add(this->label_Sensor_Hopper1);
			   this->Controls->Add(this->textBox_Hopper1_Real);
			   this->Controls->Add(this->textBox_Hopper2_Real);
			   this->Controls->Add(this->button_Encashment);
			   this->Controls->Add(this->textBox_sett_Number_BillAcceptor);
			   this->Controls->Add(this->textBox_sett_Number_CoinAcceptor);
			   this->Controls->Add(this->textBox_sett_Num_Card_Reader);
			   this->Controls->Add(this->textBox_sett_Num_Dispenser);
			   this->Controls->Add(this->textBox_sett_Num_Hoppers);
			   this->Controls->Add(this->textBox_sett_ProportionHoppers);
			   this->Controls->Add(this->textBox_sett_cost_coint_1);
			   this->Controls->Add(this->textBox_sett_number_cards);
			   this->Controls->Add(this->textBox_sett_number_coins);
			   this->Controls->Add(this->textBox_sett_number_spit_out_cards);
			   this->Controls->Add(this->textBox_sett_number_spit_out_coins);
			   this->Controls->Add(this->textBox_sett_number_buttons);
			   this->Controls->Add(this->textBox_sett_cost_card);
			   this->Controls->Add(this->textBox_sett_cost_coint_2);
			   this->Controls->Add(this->button_Request_State_3);
			   this->Controls->Add(this->button_Request_State_2);
			   this->Controls->Add(this->label23);
			   this->Controls->Add(this->button_Request_State_1);
			   this->Controls->Add(this->textBox_WS_Client_4);
			   this->Controls->Add(this->button_Send_To_WS_Server_4);
			   this->Controls->Add(this->button_Send_To_WS_Server_3);
			   this->Controls->Add(this->button_Send_To_WS_Server_2);
			   this->Controls->Add(this->textBox_WS_Client_3);
			   this->Controls->Add(this->button_Send_To_WS_Server_1);
			   this->Controls->Add(this->textBox_WS_Client_2);
			   this->Controls->Add(this->richTextBox_WS_Client_1);
			   this->Controls->Add(this->button_Test);
			   this->Controls->Add(this->radioButton_Test);
			   this->Controls->Add(this->panel2);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->button_Disconnect_COM);
			   this->Controls->Add(this->button_Start_USB);
			   this->Controls->Add(this->label_STATE_COM);
			   this->Controls->Add(this->label22);
			   this->Controls->Add(this->comboBox_COMPorts);
			   this->Controls->Add(this->button_Connect_COM);
			   this->Controls->Add(this->radioButton_Client);
			   this->Controls->Add(this->radioButton_Server);
			   this->Controls->Add(this->button_Return);
			   this->Controls->Add(this->label21);
			   this->Controls->Add(this->textBox_Number_BillAcceptor);
			   this->Controls->Add(this->label20);
			   this->Controls->Add(this->textBox_Number_CoinAcceptor);
			   this->Controls->Add(this->label19);
			   this->Controls->Add(this->textBox_Num_Card_Reader);
			   this->Controls->Add(this->label18);
			   this->Controls->Add(this->textBox_Num_Dispenser);
			   this->Controls->Add(this->label17);
			   this->Controls->Add(this->textBox_Num_Hoppers);
			   this->Controls->Add(this->label_TimeForSplitOut);
			   this->Controls->Add(this->label16);
			   this->Controls->Add(this->textBox_ProportionHoppers);
			   this->Controls->Add(this->button_Hopper_2);
			   this->Controls->Add(this->button_Hopper_1);
			   this->Controls->Add(this->button_Ok);
			   this->Controls->Add(this->button_Up);
			   this->Controls->Add(this->button_Down);
			   this->Controls->Add(this->button_Right);
			   this->Controls->Add(this->button_Left);
			   this->Controls->Add(this->button_Settings);
			   this->Controls->Add(this->button_SettingsSoft);
			   this->Controls->Add(this->button_Card);
			   this->Controls->Add(this->label15);
			   this->Controls->Add(this->textBox_cost_coint_1);
			   this->Controls->Add(this->label14);
			   this->Controls->Add(this->textBox_Hopper_2);
			   this->Controls->Add(this->button_SplitOutCards);
			   this->Controls->Add(this->label13);
			   this->Controls->Add(this->textBox_number_cards);
			   this->Controls->Add(this->label10);
			   this->Controls->Add(this->textBox_number_coins);
			   this->Controls->Add(this->label11);
			   this->Controls->Add(this->textBox_number_spit_out_cards);
			   this->Controls->Add(this->label12);
			   this->Controls->Add(this->textBox_number_spit_out_coins);
			   this->Controls->Add(this->label9);
			   this->Controls->Add(this->textBox_number_buttons);
			   this->Controls->Add(this->label8);
			   this->Controls->Add(this->textBox_cost_card);
			   this->Controls->Add(this->label7);
			   this->Controls->Add(this->textBox_cost_coint_2);
			   this->Controls->Add(this->button_Bill_100);
			   this->Controls->Add(this->button_Bill_050);
			   this->Controls->Add(this->button_Bill_020);
			   this->Controls->Add(this->button_Bill_010);
			   this->Controls->Add(this->button_Bill_005);
			   this->Controls->Add(this->button_Coin_20);
			   this->Controls->Add(this->button_Coin_10);
			   this->Controls->Add(this->button_Coin_05);
			   this->Controls->Add(this->button_Coin_02);
			   this->Controls->Add(this->button_Coin_01);
			   this->Controls->Add(this->panel1);
			   this->Controls->Add(this->button_DepositMoney);
			   this->Controls->Add(this->label6);
			   this->Controls->Add(this->textBox_Hopper_1);
			   this->Controls->Add(this->label5);
			   this->Controls->Add(this->textBox_Card_Dispenser);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->label4);
			   this->Controls->Add(this->textBox_CardReader);
			   this->Controls->Add(this->textBox_Card);
			   this->Controls->Add(this->button_Exchange);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->textBox_Bill_Acceptor);
			   this->Controls->Add(this->textBox_Coin_Acceptor);
			   this->Controls->Add(this->button_Send_Test);
			   this->Name = L"MainForm";
			   this->Text = L" ";
			   this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			   this->panel1->ResumeLayout(false);
			   this->panel1->PerformLayout();
			   this->panel2->ResumeLayout(false);
			   this->panel2->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion



	private: System::Void button_Send_Test_Click(System::Object^ sender, System::EventArgs^ e) {
		Enable_Disable_Button(button_Send_Test, false);		
		button_SettingsSoft->Enabled = true;

		if (radioButton_Client->Checked == true) {

		}
		else if (radioButton_Server->Checked == true) {
			Server_Threads();
		}
		else {

			//Set_Settings(&hterminal->settings);
			//Terminal_Init();
			Get_Settings();
			Terminal_Threads();
			//hterminal->enable_exti_hopper1 = true;
			//hterminal->enable_exti_hopper2 = true;
			//hterminal->enable_exti_buttons = true;
		}

	}

	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void timer_display_Tick(System::Object^ sender, System::EventArgs^ e) {
		//TERMINAL_HandleTypeDef* htrmnl = hterminal;
		System::String^ str;
		System::String^ str_display;
		array<String^>^ chrArray = gcnew array<String^>(5);
		str = Marshal::PtrToStringAnsi(IntPtr(Displays.Display_1.display_string));
		if (str->Length > 4)  str_display = str->Substring(0, 5);
		else str_display = str;

		for (int i = 0; i < str_display->Length; i++) {
			chrArray[i] = str->Substring(i, 1);
			if ((chrArray[i] == ",") || (chrArray[i] == "."))
				chrArray[i - 1] += chrArray[i];
		}

		System::String^ str_temp;
		for (int i = 0; i < 4; i++) {
			if ((chrArray[i] == ",") || (chrArray[i] == ".")) {
				str_temp = chrArray[i + 1];
				chrArray[i + 1] = chrArray[i];
				chrArray[i] = str_temp;
			}
		}
		label_Display_1->Text = chrArray[0];
		label_Display_2->Text = chrArray[1];
		label_Display_3->Text = chrArray[2];
		label_Display_4->Text = chrArray[3];

		//str = Marshal::PtrToStringAnsi(IntPtr(hdisplay->display_2->display_string));
		//if (str->Length > 4)  str_display = str->Substring(0, 5);
		//else str_display = str;

		//for (int i = 0; i < str_display->Length; i++) {
		//	chrArray[i] = str->Substring(i, 1);
		//	if ((chrArray[i] == ",") || (chrArray[i] == "."))
		//		chrArray[i - 1] += chrArray[i];
		//}

		//for (int i = 0; i < 4; i++) {
		//	if ((chrArray[i] == ",") || (chrArray[i] == ".")) {
		//		str_temp = chrArray[i + 1];
		//		chrArray[i + 1] = chrArray[i];
		//		chrArray[i] = str_temp;
		//	}
		//}
		//label_Display_5->Text = chrArray[0];
		//label_Display_6->Text = chrArray[1];
		//label_Display_7->Text = chrArray[2];
		//label_Display_8->Text = chrArray[3];


		//if (hterminal->event_save_manual) {
		//	hterminal->event_save_manual = false;
		//	Get_Settings();
		//}

		//if ((hterminal->settings.number_buttons == 1)) {
		//	Enable_Disable_Button(button_Hopper_2, false);
		//	label_TimeForSplitOut->Text = "";
		//}
		//else if (hterminal->settings.number_buttons == 2) {
		//	Enable_Disable_Button(button_Exchange, false);
		//	label_TimeForSplitOut->Text = "";
		//}
		//else if (hterminal->settings.number_buttons == 0) {
		//	Enable_Disable_Button(button_Exchange, false);
		//	Enable_Disable_Button(button_Hopper_1, false);
		//	Enable_Disable_Button(button_Hopper_2, false);

		//	char str_timme[50];
		//	sprintf_s(str_timme, "Время: %d", hterminal->time_for_split_out / 1000);
		//	label_TimeForSplitOut->Text = Marshal::PtrToStringAnsi(IntPtr(str_timme));
		//}

		////if (Term_Soft.Mode != Terminal_Soft::TERMINAL_SOFT_SERVER) {
		//textBox_Bill_Acceptor->Text = Convert::ToString((float)(hbillacceptor->bills_total) / 100, CultureInfo::InvariantCulture);
		//if (hhopper->hopper_1 != NULL) {
		//	textBox_Hopper_1->Text = Convert::ToString(hhopper->hopper_1->coins_total, CultureInfo::InvariantCulture);
		//	ChangeHopperCoints(textBox_Hopper1_Real);
		//}
		//if (hhopper->hopper_2 != NULL) {
		//	textBox_Hopper_2->Text = Convert::ToString(hhopper->hopper_2->coins_total, CultureInfo::InvariantCulture);
		//	ChangeHopperCoints(textBox_Hopper2_Real);
		//}
		////}


		//if (set_settings) {
		//	//Set_Settings(&hterminal->settings);
		//	Sleep(3000);
		//	Enable_Disable_Button(button_Send_Test, false);
		//	button_SettingsSoft->Enabled = true;
		//	set_settings = false;
		//}

		//if (get_settings) {
		//	get_settings = false;
		//	Get_Settings();
		//}

		//Enable_Disable_Button(button_Up, hterminal->enable_button_up);
		//Enable_Disable_Button(button_Down, hterminal->enable_button_down);
		//Enable_Disable_Button(button_Left, hterminal->enable_button_left);
		//Enable_Disable_Button(button_Right, hterminal->enable_button_right);
		//Enable_Disable_Button(button_Ok, hterminal->enable_button_ok);
		//Enable_Disable_Button(button_Settings, hterminal->enable_button_settings);
		//Enable_Disable_Button(button_Encashment, hterminal->enable_button_encashment);
		//Enable_Disable_Button(button_Return, hterminal->enable_button_return);
		//Enable_Disable_Button(button_Start_USB, flagCOMPortEnable);

		//timer_display->Enabled = true;
		//bool enable_coin_acceptor = false;
		//Enable_Disable_Yellow_Button(button_Coin_01, enable_coin_acceptor);
		//Enable_Disable_Yellow_Button(button_Coin_02, enable_coin_acceptor);
		//Enable_Disable_Yellow_Button(button_Coin_05, enable_coin_acceptor);
		//Enable_Disable_Yellow_Button(button_Coin_10, enable_coin_acceptor);
		//Enable_Disable_Yellow_Button(button_Coin_20, enable_coin_acceptor);

		bool enable_bill_acceptor = !BillAcceptor.Inhibit;
		Enable_Disable_Yellow_Button(button_Bill_005, enable_bill_acceptor);
		Enable_Disable_Yellow_Button(button_Bill_010, enable_bill_acceptor);
		Enable_Disable_Yellow_Button(button_Bill_020, enable_bill_acceptor);
		Enable_Disable_Yellow_Button(button_Bill_050, enable_bill_acceptor);
		Enable_Disable_Yellow_Button(button_Bill_100, enable_bill_acceptor);
	}


	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		label_Display_1->Text = " ";
		label_Display_2->Text = " ";
		label_Display_3->Text = " ";
		label_Display_4->Text = " ";
	}
	private: System::Void button_Coin_01_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::Button^ button;
		button = (System::Windows::Forms::Button^) sender;
		System::String^ coin_string = (System::String^)button->Tag;
		uint32_t coin = Convert::ToInt32(100 * Convert::ToDouble(coin_string, CultureInfo::InvariantCulture), CultureInfo::InvariantCulture);
	}
	private: System::Void button_Bill_005_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::Button^ button;
		button = (System::Windows::Forms::Button^) sender;
		System::String^ bill_string = (System::String^)button->Tag;
		uint32_t bill = Convert::ToInt32(Convert::ToDouble(bill_string, CultureInfo::InvariantCulture), CultureInfo::InvariantCulture);
		
		BillAcceptorNS::MessageClass msg;
		msg.command = ACCEPTED;
		msg.count_pulse = bill / 5;
		BillAcceptor.Messages.pushMessageIn(&msg);

		Server_Message msg_server;
		msg_server.command = SEND_BILL;
		msg_server.money = bill*100;
		Push_Server_Message(&msg_server);
	}


	private: System::Void button_SplitOutCards_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button_Exchange_Click(System::Object^ sender, System::EventArgs^ e) {
		//hterminal->hopper->hopper_1->coins_total_real = (uint32_t)Convert::ToInt32(textBox_Hopper1_Real->Text, CultureInfo::InvariantCulture);
		//hterminal->hopper->hopper_2->coins_total_real = (uint32_t)Convert::ToInt32(textBox_Hopper2_Real->Text, CultureInfo::InvariantCulture);
		//hterminal->event_spit_out_coins = true;
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		//hterminal->event_spit_in_card = true;
		//hterminal->event_deposit_money = true;
	}
	private: System::Void button_Card_Click(System::Object^ sender, System::EventArgs^ e) {
		if (button_Card->Tag == "нет") {
			button_Card->Tag = "вставлена";
			button_Card->Text = "вставлена";
			textBox_CardReader->Text = "ID";
			button_Card->BackColor = System::Drawing::Color::FromName("Red");
		}
		else {
			button_Card->Tag = "нет";
			button_Card->Text = "нет";
			textBox_CardReader->Text = "";
			button_Card->BackColor = System::Drawing::Color::FromName("Yellow");
		}
	}
	private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
			printf("LAN: Received settings from the server\n");
			//Set_Settings(&hterminal->settings_receive);
			Get_Settings();
			//hterminal->command = TERMINAL_STATUS_SET_SETTINGS;

	}

	private: System::Void button_Hopper_1_Click(System::Object^ sender, System::EventArgs^ e) {
		//hterminal->hopper->hopper_1->coins_total_real = (uint32_t)Convert::ToInt32(textBox_Hopper1_Real->Text, CultureInfo::InvariantCulture);
		//hterminal->hopper->hopper_2->coins_total_real = (uint32_t)Convert::ToInt32(textBox_Hopper2_Real->Text, CultureInfo::InvariantCulture);
		//hterminal->event_spit_out_hopper_1 = true;
	}
	private: System::Void button_Hopper_2_Click(System::Object^ sender, System::EventArgs^ e) {
		//hterminal->hopper->hopper_1->coins_total_real = (uint32_t)Convert::ToInt32(textBox_Hopper1_Real->Text, CultureInfo::InvariantCulture);
		//hterminal->hopper->hopper_2->coins_total_real = (uint32_t)Convert::ToInt32(textBox_Hopper2_Real->Text, CultureInfo::InvariantCulture);
		//hterminal->event_spit_out_hopper_2 = true;
	}
	private: System::Void button_Settings_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::Button^ button;
		button = (System::Windows::Forms::Button^) sender;
		System::String^ tag = (System::String^)button->Tag;
		if (tag == "Up") {
			//Callback_Buttons_Settings(TERMINAL_BUTTON_UP);
		}
		if (tag == "Down") {
			//Callback_Buttons_Settings(TERMINAL_BUTTON_DOWN);
		}
		if (tag == "Left") {
			//Callback_Buttons_Settings(TERMINAL_BUTTON_LEFT);
		}
		if (tag == "Right") {
			//Callback_Buttons_Settings(TERMINAL_BUTTON_RIGHT);
		}
		if (tag == "Ok") {
			//Callback_Buttons_Settings(TERMINAL_BUTTON_OK);
		}
		if (tag == "Return") {
			//Callback_Buttons_Settings(TERMINAL_BUTTON_RETURN);
		}
		if (tag == "Settings") {
			//hterminal->command = TERMINAL_STATUS_SET_SETTINGS_MANUAL;
		}
		if (tag == "Encashment") {
			//hterminal->command = TERMINAL_STATUS_ENCASHMENT;
		}
	}
	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void panel1_Paint_1(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void button_Connect_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void comboBox_COMPorts_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button_Start_USB_Click(System::Object^ sender, System::EventArgs^ e) {
		flagStartUSB = false;
		//hThread_SerialCOM_Debug = CreateThread(NULL, 0, SerialCOMDebugThreadFunction, 0, 0, NULL);
		//if (hThread_SerialCOM_Debug == NULL)
		//{
		//	ErrorHandler(TEXT("CreateThread SerialCOM_Debug"));
		//	ExitProcess(3);
		//}

	}
	private: System::Void button_Connect_COM_Click(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void button_Disconnect_COM_Click(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void button1_Click_2(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button_Test_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button_Send_To_WS_Server_1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button_Request_State_1_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::Button^ button;
		button = (System::Windows::Forms::Button^) sender;
		System::String^ tag = (System::String^)button->Tag;
		Server_Message msg;
		if (tag == "hopper_1")
		{
			msg.command = REQUEST_HOPPER_1;
			Push_Server_Message(&msg);
		}
		else 	if (tag == "hopper_2")
		{
			msg.command = REQUEST_HOPPER_2;
			Push_Server_Message(&msg);
		}
		else 	if (tag == "hopper_3")
		{
			msg.command = REQUEST_HOPPER_3;
			Push_Server_Message(&msg);
		}
	
	}

};
}
