#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Terminal/Terminal.h"
#include "Winsock_Server.h"
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")


using namespace DisplayNS;
using namespace BillAcceptorNS;
using namespace HoppersNS;

#define DEFAULT_BUFLEN 1024*10
#define DEFAULT_PORT_1	"2000"
#define DEFAULT_PORT_2	"81"
char SendBuf[DEFAULT_BUFLEN];

SOCKET ListenSocket_1 = INVALID_SOCKET;
SOCKET ListenSocket_2 = INVALID_SOCKET;
SOCKET ClientSocket_1 = INVALID_SOCKET;
SOCKET ClientSocket_2 = INVALID_SOCKET;

extern bool set_settings;
extern bool get_settings;


void Parse_Message_Received(char* buff, int len) {
	if (strstr(buff, "DEBUG:__") == buff) {
		printf((const char*)(buff + 8));
	}
	else if (strstr(buff, "DISPL_1:") == buff) {
		strcpy_s(Displays.Display_1.display_string, (const char*)(buff + 8));
	}
	else if (strstr(buff, "DISPL_2:") == buff) {
		//strcpy_s(Displays.Display_2.display_string, (const char*)(buff + 8));
	}
	else if (strstr(buff, "SETT:___") == buff) {
	}
	else if (strstr(buff, "BUTT:STA") == buff) {
	}
	else if (strstr(buff, "TERM:STA") == buff) {
	}

}


int Send_Settings(void) {
	//int iSendResult = SOCKET_ERROR;
	//printf("Отправляем настройки\n");
	//memcpy(SendBuf, "SETT:___", 8);
	////memcpy(&SendBuf[8], &hterminal->settings_send, sizeof(TERMINAL_SettingsTypeDef));
	//int len = 8 + sizeof(TERMINAL_SettingsTypeDef);
	//do {
	//	if (ClientSocket_1 != INVALID_SOCKET) {
	//		iSendResult = send(ClientSocket_1, SendBuf, len, 0);
	//		if (iSendResult == SOCKET_ERROR) {
	//			printf("send setting failed with error: %d\n", WSAGetLastError());
	//			closesocket(ClientSocket_1);
	//			//WSACleanup();
	//			//return 1;
	//		}
	//	}
	//	else {
	//		Sleep(10);
	//	}
	//} while (iSendResult == SOCKET_ERROR);
	//Send_Request_Settings();
	return 0;
}

int Send_Request_Settings(void) {
	int iSendResult = SOCKET_ERROR;
	//printf("Запрашиваем настройки\n");
	memcpy(SendBuf, "SETT_IN:", 8);
	// Echo the buffer back to the sender
	iSendResult = send(ClientSocket_1, SendBuf, 8, 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("send request setting failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket_1);
		//WSACleanup();
		return 1;
	}
	return 0;
}

int Send_Request_Button_State(void) {
	int iSendResult = SOCKET_ERROR;
	//printf("Requested button state\n");
	memcpy(SendBuf, "BUTT:STA", 8);
	// Echo the buffer back to the sender
	iSendResult = send(ClientSocket_1, SendBuf, 8, 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("send request button state failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket_1);
		return 1;
	}
	return 0;
}

int Send_Request_Terminal_State(void) {
	int iSendResult = SOCKET_ERROR;
	//printf("Requested button state\n");
	memcpy(SendBuf, "TERM:STA", 8);
	// Echo the buffer back to the sender
	iSendResult = send(ClientSocket_1, SendBuf, 8, 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("send request terminal state failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket_1);
		return 1;
	}
	return 0;
}

int Send_Request_State(char *request) {
	int iSendResult = SOCKET_ERROR;
	memcpy(SendBuf, request, 8);
	// Echo the buffer back to the sender
	iSendResult = send(ClientSocket_1, SendBuf, 8, 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("send request %s state failed with error: %d\n", request, WSAGetLastError());
		closesocket(ClientSocket_1);
		return 1;
	}
	return 0;
}


int Send_Bill(uint32_t bill) {
	int iSendResult = SOCKET_ERROR;
	char buff[40];
	printf("Send Bill\n");
	memcpy(buff, "CMD:BILL", 8);
	memcpy(&buff[8], &bill, sizeof(uint32_t));
	int len = 8 + sizeof(uint32_t);
	do {
		if (ClientSocket_1 != INVALID_SOCKET) {
			iSendResult = send(ClientSocket_1, buff, len, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send bill failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket_1);
			}
		}
		else {
			Sleep(10);
		}
	} while (iSendResult == SOCKET_ERROR);
	return 0;
}

int Send_Coin(uint32_t coin) {
	int iSendResult = SOCKET_ERROR;
	char buff[40];
	printf("Send Coin\n");
	memcpy(buff, "CMD:COIN", 8);
	memcpy(&buff[8], &coin, sizeof(uint32_t));
	int len = 8 + sizeof(uint32_t);
	do {
		if (ClientSocket_1 != INVALID_SOCKET) {
			iSendResult = send(ClientSocket_1, buff, len, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send coin failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket_1);
			}
		}
		else {
			Sleep(10);
		}
	} while (iSendResult == SOCKET_ERROR);
	return 0;
}

int Send_Button(uint32_t button) {
	int iSendResult = SOCKET_ERROR;
	char buff[40];
	printf("Send Button\n");
	memcpy(buff, "CMD:BUTT", 8);
	memcpy(&buff[8], &button, sizeof(uint32_t));
	int len = 8 + sizeof(uint32_t);
	do {
		// Echo the buffer back to the sender
		if (ClientSocket_1 != INVALID_SOCKET) {
			iSendResult = send(ClientSocket_1, buff, len, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send button failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket_1);
			}
		}
		else {
			Sleep(10);
		}
	} while (iSendResult == SOCKET_ERROR);
	return 0;
}

std::queue<MessageServerClass> server_queue_in;
//std::queue<SERVER_COMMAND> server_queue_out;

void Push_Server_Message(MessageServerClass* msg) {
	server_queue_in.push(*msg);
}
void Pop_Server_Message(MessageServerClass* msg) {
	uint32_t ms = 0;
	while (server_queue_in.empty()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	*msg = server_queue_in.front();
	server_queue_in.pop();
}

int Server_Thread()
{
	Server_Message msg;
	while (true)
	{
		Pop_Server_Message(&msg);
		if (msg.command == REQUEST_HOPPER_1) {
			printf("Send request hopper 1 state\n");
			Send_Request_State("HOP1:STA");
		}

		if (msg.command == REQUEST_HOPPER_2) {
			printf("Send request hopper 2 state\n");
			Send_Request_State("HOP2:STA");
		}

		if (msg.command == REQUEST_HOPPER_3) {
			printf("Send request hopper 3 state\n");
			Send_Request_State("HOP3:STA");
		}

		if (msg.command == SEND_BILL) {
			Send_Bill(msg.money);
		}

		//if (hterminal->billacceptor->fl_accepted == true) {
		//	if (Send_Bill(hterminal->billacceptor->bill)) continue;
		//	hterminal->billacceptor->fl_accepted = false;
		//}

	}
}


int Socket_Server_1(void)
{
	WSADATA wsaData;
	int iResult;

	struct addrinfo* result = NULL;
	struct addrinfo hints;

	//int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	bool req_sett = true;
	

	while (1) {
		printf("Start Server 1!!!\n");
		req_sett = false;
		//Sleep(100);
		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			continue;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		// Resolve the server address and port
		iResult = getaddrinfo(NULL, DEFAULT_PORT_1, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			continue;
		}

		// Create a SOCKET for connecting to server
		ListenSocket_1 = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (ListenSocket_1 == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			//freeaddrinfo(result);
			WSACleanup();
			continue;
		}

		// Setup the TCP listening socket
		iResult = bind(ListenSocket_1, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			//freeaddrinfo(result);
			closesocket(ListenSocket_1);
			WSACleanup();
			continue;
		}

		freeaddrinfo(result);

		iResult = listen(ListenSocket_1, SOMAXCONN);
		if (iResult == SOCKET_ERROR) {
			printf("listen failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket_1);
			WSACleanup();
			continue;
		}

		// Accept a client socket
		ClientSocket_1 = accept(ListenSocket_1, NULL, NULL);
		if (ClientSocket_1 == INVALID_SOCKET) {
			printf("accept ClientSocket_1 failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket_1);
			WSACleanup();
			continue;
		}

		//// No longer need server socket
		//closesocket(ListenSocket_1);
		//if (hThread_Winsock_Server_Send == NULL) {
		//	hThread_Winsock_Server_Send = CreateThread(NULL, 0, WinsockServerSendThreadFunction, 0, 0, NULL);
		//}
		//if (hThread_Winsock_Server_Send == NULL)
		//{
		//	printf("Error Create Thread Winsock_Server_Send");
		//	ExitProcess(3);
		//}

		printf("Connect ClientSocket_1 is OK\n");
		// Receive until the peer shuts down the connection
		do {

			iResult = recv(ClientSocket_1, recvbuf, recvbuflen, 0);
			if (iResult > 0) {
				Parse_Message_Received(recvbuf, iResult);
				memset(recvbuf, 0, iResult);
				if (!req_sett) {
					Send_Request_Settings();
					req_sett = true;
				}
			}
			else if (iResult == 0)
				printf("Connection closing...\n");
			else {
				printf("recv ClientSocket_1 failed with error: %d\n", WSAGetLastError());
				break;
			}

		} while (iResult > 0);

		// shutdown the connection since we're done
		iResult = shutdown(ClientSocket_1, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
		}
		
		
	//80293629425
		// cleanup
		closesocket(ClientSocket_1);
		WSACleanup();

	}
	return 0;
}

int Socket_Server_2(void)
{
	WSADATA wsaData;
	int iResult;

	struct addrinfo* result = NULL;
	struct addrinfo hints;

	//int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	bool req_sett = true;
	printf("Start Server 2!!!\n");

	while (1) {
		req_sett = false;
		Sleep(100);
		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			continue;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		// Resolve the server address and port
		iResult = getaddrinfo(NULL, DEFAULT_PORT_2, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			continue;
		}

		// Create a SOCKET for connecting to server
		ListenSocket_2 = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (ListenSocket_2 == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			continue;
		}

		// Setup the TCP listening socket
		iResult = bind(ListenSocket_2, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			closesocket(ListenSocket_2);
			WSACleanup();
			continue;
		}

		freeaddrinfo(result);

		iResult = listen(ListenSocket_2, SOMAXCONN);
		if (iResult == SOCKET_ERROR) {
			printf("listen failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket_2);
			WSACleanup();
			continue;
		}

		// Accept a client socket
		ClientSocket_2 = accept(ListenSocket_2, NULL, NULL);
		if (ClientSocket_2 == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket_2);
			WSACleanup();
			continue;
		}

		// No longer need server socket
		closesocket(ListenSocket_2);

		// Receive until the peer shuts down the connection
		do {

			iResult = recv(ClientSocket_2, recvbuf, recvbuflen, 0);
			if (iResult > 0) {
				Parse_Message_Received(recvbuf, iResult);
			}
			else if (iResult == 0)
				printf("Connection closing...\n");
			else {
				printf("recv ClientSocket_2 failed with error: %d\n", WSAGetLastError());
				break;
			}

		} while (iResult > 0);

		// shutdown the connection since we're done
		iResult = shutdown(ClientSocket_2, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
		}

		// cleanup
		closesocket(ClientSocket_2);
		WSACleanup();

	}
	return 0;
}