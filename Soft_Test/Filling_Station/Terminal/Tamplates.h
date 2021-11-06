/**
  ******************************************************************************
  * File Name          : Tamplates.h
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TAMPLATES_H
#define __TAMPLATES_H
#include "cmsis_os2.h"
#ifdef TERMINAL_USE_WINDOWS
template< class T, int SIZE_QUEUE >
class QueueMessageClass
{
private:
	std::queue<T> queue_in;
	std::queue<T> queue_out;
public:
	osStatus_t pushMessageIn(T* msg) {
		queue_in.push(*msg);
		return osOK;
	}
	osStatus_t popMessageIn(T* msg, uint32_t timeout) {
		uint32_t ms = 0;
		while (queue_in.empty() && (ms++ < timeout)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		if (queue_in.empty()) return osErrorTimeout;
		*msg = queue_in.front();
		queue_in.pop();
		return osOK;
	}
	osStatus_t pushMessageOut(T* msg) {
		queue_out.push(*msg);
		return osOK;
	}
	osStatus_t popMessageOut(T* msg, uint32_t timeout) {
		uint32_t ms = 0;
		while (queue_out.empty() && (ms++ < timeout)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		if (queue_out.empty()) return osErrorTimeout;
		*msg = queue_out.front();
		queue_out.pop();
		return osOK;
	}
};
#else

template< class T, int SIZE_QUEUE >
class QueueMessageClass
{
public:
  T message;
  osMessageQueueId_t queue_in;
  osMessageQueueId_t queue_out;
public:
	osStatus_t pushMessageIn(T* msg) {
    return osMessageQueuePut(queue_in, msg, NULL, osWaitForever);
	}
	osStatus_t popMessageIn(T* msg, uint32_t timeout) {
    return osMessageQueueGet(queue_in, msg, NULL, timeout);
	}
	osStatus_t pushMessageOut(T* msg) {
    return osMessageQueuePut(queue_out, msg, NULL, osWaitForever);
	}
	osStatus_t popMessageOut(T* msg, uint32_t timeout) {
    return osMessageQueueGet(queue_out, msg, NULL, timeout);
	}
};
#endif // TERMINAL_USE_WINDOWS

#endif /*__TAMPLATES_H*/
