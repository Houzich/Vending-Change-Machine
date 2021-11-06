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
#include "FLASH.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef DEBUG_FLASH
#undef DEBUG
#undef DEBUG_PRINTF
#undef DEBUG_PUTCHAR
#define DEBUG(...)		do {debug_header("FLASH: ", __VA_ARGS__);} while (0)
#define DEBUG_PRINT(...)		    do {debug_print(__VA_ARGS__);} while (0)
#define DEBUG_PUTCHAR(x)	ITM_SendChar x ;
#else
#define DEBUG(...)
#define DEBUG_PRINTF(x)
#define DEBUG_PUTCHAR(x)
#endif // DEBUG_FLASH
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


/*###############################################################*/
/*###############################################################* FLASH_Save_Settings -->*/
/*###############################################################*/
/**
  * @brief  Save Settings structure in flash.
  * @param  None
  * @retval write status:
  *           - false: error write
  *           - true: if Settings structure is write 
  */
HAL_StatusTypeDef FLASH_Save_Settings(void)
{
  HAL_StatusTypeDef FlashStatus = HAL_OK;
  uint32_t SectorError = 0;
  TERMINAL_HandleTypeDef *terminal = Terminal_Get_Handle();
  
  FLASH_EraseInitTypeDef pEraseInit;
  pEraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;  
  pEraseInit.Sector = FLASH_SECTOR_7;
  pEraseInit.NbSectors = 1;
  pEraseInit.VoltageRange = VOLTAGE_RANGE;
  
  FlashStatus = HAL_FLASH_Unlock();
  if (FlashStatus != HAL_OK)
  {
    HAL_FLASH_Lock();
    DEBUG("ERROR: Flash Unlock!!!\n");
    return FlashStatus;
  }
  FlashStatus = HAL_FLASHEx_Erase(&pEraseInit, &SectorError); 
  /* If erase operation was failed, a Flash error code is returned */
  if (FlashStatus != HAL_OK)
  {
    HAL_FLASH_Lock();
    DEBUG("ERROR: Erase Sector!!!\n");
    return FlashStatus;
  }
  
  uint32_t *pFlash = (uint32_t *)DATA_FLASH_START_ADDRESS;
  uint32_t *pData = (uint32_t *)&terminal->settings;
  terminal->settings.key = 1;
	for (int i = 0; i < sizeof(TERMINAL_SettingsTypeDef)/4; i++)
  {
    /* Set variable data */
    FlashStatus = HAL_FLASH_Program(TYPEPROGRAM_WORD,(uint32_t)pFlash++, *(pData++));       
    /* If program operation was failed, a Flash error code is returned */
    if (FlashStatus != HAL_OK)
    {
      HAL_FLASH_Lock();
      DEBUG("ERROR: Program word num %d!!!\n", i);
      memset(&terminal->settings, 0, sizeof(TERMINAL_SettingsTypeDef));
      return FlashStatus;
    }
  }
  
  HAL_FLASH_Lock();
	return FlashStatus; 
}
/*###############################################################*/
/*###############################################################* FLASH_Get_Settings -->*/
/*###############################################################*/
/**
  * @brief  Get Settings structure from flash.
  * @param  None
	* @retval read status:
  *           - false: error read
  *           - true: if Settings structure is read and fill 
  */
bool FLASH_Get_Settings(void)
{
  TERMINAL_HandleTypeDef *terminal = Terminal_Get_Handle();
  uint32_t *pFlash = (uint32_t *)DATA_FLASH_START_ADDRESS;
  uint32_t *pData = (uint32_t *)&terminal->settings;
	for (int i = 0; i < sizeof(TERMINAL_SettingsTypeDef)/4; i++)
  {
    *(pData++) = *(pFlash++);
  }
  
  if(terminal->settings.key != 1){
  	terminal->settings.cost_coin_1 = 100; //Стоимость монет в хоппере 1
		terminal->settings.cost_coin_2 = 200; //Стоимость монет в хоппере 2
		terminal->settings.cost_card = 0; //Стоимость карт в диспенсере
		terminal->settings.number_buttons = 2; //Количество кнопок
		terminal->settings.number_spit_out_coins = 1; //Кол-во выдаваемых монет за нажатие
		terminal->settings.number_spit_out_cards = 0; //Кол-во выдаваемых карт за нажатие
		terminal->settings.number_coins = 500; //Кол-во монет в хопперах
		terminal->settings.number_cards = 500; //Кол-во карт в диспенсере
		terminal->settings.proportion_hoppers = 60; //Пропорция выдачи монет
		terminal->settings.number_coinacceptors = 0; //Количество монетоприемников
		terminal->settings.number_billacceptors = 1; //Количество купюроприемников
		terminal->settings.number_hoppers = 2; //Количество хопперов
		terminal->settings.number_carddispensers = 0; //Количество диспенсеров
		terminal->settings.number_cardreaders = 0; //Количество считывателей rfid
		terminal->settings.diapason_hold_acceptors = 100; //Разница между внесенными деньгами и общей суммой в хопперах, для отключения приемников
  }
 
	return true;
}
