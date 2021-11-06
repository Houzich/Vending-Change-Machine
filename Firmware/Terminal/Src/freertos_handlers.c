/*------------------------------------------------------------------------------
* Name:    rtx_handlers.c
 *----------------------------------------------------------------------------*/

//#include "FreeRTOS.h"
//#include "task.h"
#include <stdio.h>
#include "rtx_os.h"
#include "main.h"

#if (configUSE_MALLOC_FAILED_HOOK == 1)
void vApplicationMallocFailedHook (void)
{
	taskDISABLE_INTERRUPTS(); 
	for(int i = 0 ; i< 0xFFFFF; i++);
	printf("Error: MALLOC FAILED HOOK");
	for( ;; );
}
#endif

#if (configCHECK_FOR_STACK_OVERFLOW > 0)
void vApplicationStackOverflowHook (TaskHandle_t xTask, signed char *pcTaskName) {
	taskDISABLE_INTERRUPTS(); 
	for(int i = 0 ; i< 0xFFFFF; i++);
	printf("Error: STACK OVERFLOW HOOK\n");
	printf("Task Name: %s\n", pcTaskName);
	for( ;; );
}
#endif



#if (configUSE_TICK_HOOK == 1)
void vApplicationTickHook (void)
{
	for(int i = 0 ; i< 0xFFFFF; i++);
	printf("TICK HOOK\n");
	for( ;; );
}
#endif

#if (configUSE_DAEMON_TASK_STARTUP_HOOK == 1)
void vApplicationDaemonTaskStartupHook (void)
{
	for(int i = 0 ; i< 0xFFFFF; i++);
	printf("Error: DAEMON TASK STARTUP HOOK\n");
	for( ;; );
}
#endif
#if (configUSE_IDLE_HOOK == 1)
void vApplicationIdleHook (void)
{
	for(int i = 0 ; i< 0xFFFFF; i++);
	printf("Error: IDLE HOOK\n");
	for( ;; );
}
#endif



// OS Error Callback function
uint32_t osRtxErrorNotify (uint32_t code, void *object_id) {
  (void)object_id;

  switch (code) {
    case osRtxErrorStackUnderflow:
      // Stack overflow detected for thread (thread_id=object_id)
			printf("ERROR RTX OS: Stack overflow detected for thread (thread_id = %d)\n", (uint32_t)object_id);
      break;
    case osRtxErrorISRQueueOverflow:
      // ISR Queue overflow detected when inserting object (object_id)
			printf("ERROR RTX OS: ISR Queue overflow detected when inserting object (object_id = %d)\n", (uint32_t)object_id);
      //return 0U;
      break;
    case osRtxErrorTimerQueueOverflow:
      // User Timer Callback Queue overflow detected for timer (timer_id=object_id)
			printf("ERROR RTX OS: User Timer Callback Queue overflow detected for timer (timer_id = %d)\n", (uint32_t)object_id);
      break;
    case osRtxErrorClibSpace:
      // Standard C/C++ library libspace not available: increase OS_THREAD_LIBSPACE_NUM
			printf("ERROR RTX OS: Standard C/C++ library libspace not available: increase OS_THREAD_LIBSPACE_NUM\n");
      break;
    case osRtxErrorClibMutex:
      // Standard C/C++ library mutex initialization failed
			printf("ERROR RTX OS: Standard C/C++ library mutex initialization failed\n");
      break;
    default:
      // Reserved
      break;
  }
	//assert_param(0);
  for (;;) {}
//return 0U;
}



