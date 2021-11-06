#pragma once
  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WINSOCK_SERVER_H
#define __WINSOCK_SERVER_H
#include <chrono>
#include <queue>

typedef enum {
	NONE = 0x00,
	REQUEST_HOPPER_1 = 0X01,
	REQUEST_HOPPER_2 = 0X02,
	REQUEST_HOPPER_3 = 0X03,
	SEND_BILL = 0X04,
} SERVER_COMMAND;

struct MessageServerClass
{
	SERVER_COMMAND command;
	uint32_t money;
};

typedef MessageServerClass Server_Message;

extern std::queue<MessageServerClass> server_queue_in;
//extern std::queue<SERVER_COMMAND> server_queue_out;

void Push_Server_Message(MessageServerClass* msg);
void Pop_Server_Message(MessageServerClass* msg);

int Server_Thread();
int Socket_Server_1(void);
int Socket_Server_2(void);
int Send_Settings(void);
int Send_Request_Settings(void);
int Send_Bill(uint32_t bill);
int Send_Request_Button_State(void);
#endif /*__WINSOCK_SERVER_H*/