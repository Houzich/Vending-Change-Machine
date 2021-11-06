/**
  ******************************************************************************
  * File Name          : Flash.c
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "stm32f4xx_hal.h"
#include "Terminal/Terminal.h"
#include "Calendar.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef DEBUG_RTC
#undef DEBUG
#undef DEBUG_PRINTF
#undef DEBUG_PUTCHAR
#define DEBUG(...)		do {debug_header("RTC: ", __VA_ARGS__);} while (0)
#define DEBUG_PRINT(...)		    do {debug_print(__VA_ARGS__);} while (0)
#else
#define DEBUG(...)
#define DEBUG_PRINTF(x)
#define DEBUG_PUTCHAR(x)
#endif // DEBUG_FLASH
/* Private variables ---------------------------------------------------------*/
/* RTC handler declaration */
RTC_HandleTypeDef RtcHandle;
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


/**
  * @brief  Configure the current time and date.
  * @param  None
  * @retval None
  */
void RTC_CalendarConfig(void)
{
  RTC_DateTypeDef sDate;
  RTC_TimeTypeDef sTime;

  /*##-1- Configure the Date #################################################*/
  /* Set Date: Tuesday April 14th 2015 */
  sDate.Year = 0x19;
  sDate.Month = RTC_MONTH_OCTOBER;
  sDate.Date = 0x26;
  sDate.WeekDay = RTC_WEEKDAY_SATURDAY;
  
  if(HAL_RTC_SetDate(&RtcHandle,&sDate,RTC_FORMAT_BCD) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  } 
  
  /*##-2- Configure the Time #################################################*/
  /* Set Time: 02:00:00 */
  sTime.Hours = 0x00;
  sTime.Minutes = 0x00;
  sTime.Seconds = 0x00;
  sTime.TimeFormat = RTC_HOURFORMAT12_AM;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  
  if(HAL_RTC_SetTime(&RtcHandle,&sTime,RTC_FORMAT_BCD) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  /*##-3- Writes a data in a RTC Backup data Register1 #######################*/
  HAL_RTCEx_BKUPWrite(&RtcHandle, RTC_BKP_DR1, 0x32F2);
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
void MX_RTC_Init(void)
{

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  RTC_AlarmTypeDef sAlarm = {0};

  /** Initialize RTC Only 
  */
  RtcHandle.Instance = RTC;
  RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
  RtcHandle.Init.AsynchPrediv = 127;
  RtcHandle.Init.SynchPrediv = 255;
  RtcHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
  RtcHandle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  RtcHandle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&RtcHandle) != HAL_OK)
  {
    Error_Handler();
  }

  /* Read the BackUp Register 1 Data */
  if(HAL_RTCEx_BKUPRead(&RtcHandle, RTC_BKP_DR1) != 0x32F2)
  {  
    /* Configure RTC Calendar */
    RTC_CalendarConfig();
  }
  /** Enable the Alarm A 
  */
  sAlarm.AlarmTime.Hours = 0;
  sAlarm.AlarmTime.Minutes = 0;
  sAlarm.AlarmTime.Seconds = 0;
  sAlarm.AlarmTime.SubSeconds = 0;
  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
  sAlarm.AlarmMask = RTC_ALARMMASK_ALL;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarm.AlarmDateWeekDay = 1;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm_IT(&RtcHandle, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
}
/*###############################################################*/
/*###############################################################* Synchronization_Time -->*/
/*###############################################################*/
static void Synchronization_Time(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *date, RTC_TimeTypeDef *time)
{
			RTC_TimeTypeDef curr_time = {0};
			RTC_DateTypeDef curr_date = {0};
	
				/* Get the RTC current Time */
			HAL_RTC_GetTime(hrtc, &curr_time, RTC_FORMAT_BIN);
			/* Get the RTC current Date */
			HAL_RTC_GetDate(hrtc, &curr_date, RTC_FORMAT_BIN);			
			if(
				(curr_time.Seconds != time->Seconds)
				||(curr_time.Minutes != time->Minutes)			
				||(curr_time.Hours != time->Hours)			
				||(curr_date.Date != date->Date)			
				||(curr_date.Month != date->Month)			
				||(curr_date.Year != date->Year)			
			)			
			time->DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
			time->StoreOperation = RTC_STOREOPERATION_RESET;
			if (HAL_RTC_SetTime(hrtc, time, RTC_FORMAT_BIN) != HAL_OK)
			{
				Error_Handler();
			}
			date->WeekDay = RTC_WEEKDAY_MONDAY;
			if (HAL_RTC_SetDate(hrtc, date, RTC_FORMAT_BIN) != HAL_OK)
			{
				Error_Handler();
			}		
}
/*###############################################################*/
/*###############################################################* TameDate_To_String -->*/
/*###############################################################*/
int32_t TimeDate_To_String(char *str)
{
			//16.05.19 19:04:35
			RTC_TimeTypeDef time;
			RTC_DateTypeDef date;
	
				/* Get the RTC current Time */
			HAL_RTC_GetTime(&RtcHandle, &time, RTC_FORMAT_BIN);
			/* Get the RTC current Date */
			HAL_RTC_GetDate(&RtcHandle, &date, RTC_FORMAT_BIN);			
			int ret = sprintf(str,"%.2d/%.2d/%.2d %.2d:%.2d:%.2d; ", date.Date,date.Month,date.Year,
																			 time.Hours,time.Minutes,time.Seconds);
			return ret;
}

/*###############################################################*/
/*###############################################################* setDateTimeString -->*/
/*###############################################################*/
void setDateTimeString(uint8_t *inMessage_u8a)
{
    volatile uint8_t i_u8;   
}

/**
  * @brief  Display the current time.
	* @param  time: RTC Time structure
	* @param  date: RTC Date structure
  * @retval None
  */
void debug_rtc_time(RTC_TimeTypeDef *time)
{
  /* Display time Format : hh:mm:ss */
  DEBUG("Current Time: %02d:%02d:%02d\n",time->Hours, time->Minutes, time->Seconds);
} 
/**
  * @brief  Alarm callback
  * @param  hrtc : RTC handle
  * @retval None
  */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
	
	  /* Get the RTC current Time */
  HAL_RTC_GetTime(hrtc, &sTime, RTC_FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(hrtc, &sDate, RTC_FORMAT_BIN);
	
#ifdef DEBUG_RTC	
	//debug_rtc_time(&sTime);
#endif // DEBUG_RTC	
	
	//TimeDate_To_String(hrtc, (char *)DateTime_String);
}
/*###############################################################*/
/*###############################################################* Time_To_Counter -->*/
/*###############################################################*/
//Not use
#define JD0 2451911 // days until Jan 01, 2001 Mon
uint32_t Time_To_Counter(RTC_TimeTypeDef *Time, RTC_DateTypeDef *Date)
{
uint8_t a;
uint16_t y;
uint8_t m;
uint32_t JDN;

//Calculation of the required coefficients
a=(14-Date->Month)/12;
y=Date->Year+4800-a;
m=Date->Month+(12*a)-3;
//Calculate the value of the current Julian day
JDN=Date->Date;
JDN+=(153*m+2)/5;
JDN+=365*y;
JDN+=y/4;
JDN+=-y/100;
JDN+=y/400;
JDN-=32045;
JDN-=JD0; // remove the days that passed before January 01, 2001
JDN*=86400;     // convert days to seconds
JDN+=(Time->Hours*3600); // and complement it with seconds of the current day
JDN+=(Time->Minutes*60);
JDN+=(Time->Seconds);
// total we have the number of seconds from 00-00 01 Jan 2001
return JDN;
} 
/*###############################################################*/
/*###############################################################* RTC_Alarm_IRQHandler -->*/
/*###############################################################*/
/**
  * @brief This function handles RTC alarms A and B interrupt through EXTI line 17.
  */
void RTC_Alarm_IRQHandler(void)
{
  HAL_RTC_AlarmIRQHandler(&RtcHandle);
}