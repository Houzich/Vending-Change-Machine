/**
  ******************************************************************************
  * File Name          : Flash_Interface.c
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "Bootloader_Flash/Bootloader.h"
#include "Bootloader_Flash/Flash_Interface.h"
#if defined(BOOTLOADER_USE_USB_FS)
	#include "usbd_core.h"
#endif
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef DEBUG_BOOTLOADER_FLASH_INTERFACE
#undef DEBUG
#define DEBUG(x)		printf("BOOT FLASH INTERFACE: "); printf x;
#else
#define DEBUG(x)
#endif // DEBUG_BOOTLOADER_FLASH_INTERFACE

/* Private variables ---------------------------------------------------------*/
#if defined(BOOTLOADER_USE_USB_FS)
	extern USBD_HandleTypeDef hUsbDeviceFS;
#endif
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*###############################################################*/
/*###############################################################* Get_Sector -->*/
/*###############################################################*/
//determine which sector the address belongs to in the flash
uint32_t Get_Sector(uint32_t address)
{
  uint32_t sector = 0;
#if defined(STM32F407xx)
  if ((address < ADDR_FLASH_SECTOR_1) && (address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_SECTOR_0;
  }
  else if ((address < ADDR_FLASH_SECTOR_2) && (address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_SECTOR_1;
  }
  else if ((address < ADDR_FLASH_SECTOR_3) && (address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_SECTOR_2;
  }
  else if ((address < ADDR_FLASH_SECTOR_4) && (address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_SECTOR_3;
  }
  else if ((address < ADDR_FLASH_SECTOR_5) && (address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_SECTOR_4;
  }
  else if ((address < ADDR_FLASH_SECTOR_6) && (address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_SECTOR_5;
  }
  else if ((address < ADDR_FLASH_SECTOR_7) && (address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_SECTOR_6;
  }
  else if ((address < ADDR_FLASH_SECTOR_8) && (address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_SECTOR_7;
  }
  else if ((address < ADDR_FLASH_SECTOR_9) && (address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_SECTOR_8;
  }
  else if ((address < ADDR_FLASH_SECTOR_10) && (address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_SECTOR_9;
  }
  else if ((address < ADDR_FLASH_SECTOR_11) && (address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_SECTOR_10;
  }
  else if ((address < ADDR_FLASH_SECTOR_12) && (address >= ADDR_FLASH_SECTOR_11))
  {
    sector = FLASH_SECTOR_11;
  }
  else
  {
    sector = FLASH_SECTOR_NO;
  }
#elif defined(STM32F103xB) || defined(STM32F103x8)
  if ((address > ADDR_FLASH_END) || (address < ADDR_FLASH_SECTOR_0))
  {
	sector = FLASH_SECTOR_NO;
  }
  else
  {
	sector = (address - ADDR_FLASH_SECTOR_0)/FLASH_PAGE_SIZE;
  }
#endif
  return sector;
}
/*###############################################################*/
/*###############################################################* Get_Sector_Size -->*/
/*###############################################################*/
//returns sector size
uint32_t Get_Sector_Size(uint32_t Sector)
{
  uint32_t sectorsize = 0x00;
#if defined(STM32F407xx)
  if ((Sector == FLASH_SECTOR_0) || (Sector == FLASH_SECTOR_1) || (Sector == FLASH_SECTOR_2) ||
      (Sector == FLASH_SECTOR_3))
  {
    sectorsize = 16 * 1024;
  }
  else if  (Sector == FLASH_SECTOR_4)
  {
    sectorsize = 64 * 1024;
  }
  else
  {
    sectorsize = 128 * 1024;
  }
#elif defined(STM32F103xB) || defined(STM32F103x8)
  sectorsize = FLASH_PAGE_SIZE;
#endif
  return sectorsize;
}
/*###############################################################*/
/*###############################################################* Read_Word_Flash -->*/
/*###############################################################*/
//read the word in flash
uint32_t Read_Word_Flash(uint32_t address)
{
  return (*(volatile uint32_t *)address);
}
/*###############################################################*/
/*###############################################################* Get_Sector_Addresses -->*/
/*###############################################################*/
//determine the starting and ending address of the sector
bool Get_Sector_Addresses(uint32_t sector, uint32_t *start_address, uint32_t *end_address)
{
	DEBUG(("BOOT_FLASH_Get_Sector_Addresses \n"))
		bool ret = true;
#if defined(STM32F407xx)
	switch (sector)
	{
	case FLASH_SECTOR_0:
		*start_address = ADDR_FLASH_SECTOR_0;
		*end_address = ADDR_FLASH_SECTOR_1 - 1;
		break;
	case FLASH_SECTOR_1:
		*start_address = ADDR_FLASH_SECTOR_1;
		*end_address = ADDR_FLASH_SECTOR_2 - 1;
		break;
	case FLASH_SECTOR_2:
		*start_address = ADDR_FLASH_SECTOR_2;
		*end_address = ADDR_FLASH_SECTOR_3 - 1;
		break;
	case FLASH_SECTOR_3:
		*start_address = ADDR_FLASH_SECTOR_3;
		*end_address = ADDR_FLASH_SECTOR_4 - 1;
		break;
	case FLASH_SECTOR_4:
		*start_address = ADDR_FLASH_SECTOR_4;
		*end_address = ADDR_FLASH_SECTOR_5 - 1;
		break;
	case FLASH_SECTOR_5:
		*start_address = ADDR_FLASH_SECTOR_5;
		*end_address = ADDR_FLASH_SECTOR_6 - 1;
		break;
	case FLASH_SECTOR_6:
		*start_address = ADDR_FLASH_SECTOR_6;
		*end_address = ADDR_FLASH_SECTOR_7 - 1;
		break;
	case FLASH_SECTOR_7:
		*start_address = ADDR_FLASH_SECTOR_7;
		*end_address = ADDR_FLASH_SECTOR_8 - 1;
		break;
	case FLASH_SECTOR_8:
		*start_address = ADDR_FLASH_SECTOR_8;
		*end_address = ADDR_FLASH_SECTOR_9 - 1;
		break;
	case FLASH_SECTOR_9:
		*start_address = ADDR_FLASH_SECTOR_9;
		*end_address = ADDR_FLASH_SECTOR_10 - 1;
		break;
	case FLASH_SECTOR_10:
		*start_address = ADDR_FLASH_SECTOR_10;
		*end_address = ADDR_FLASH_SECTOR_11 - 1;
		break;
	case FLASH_SECTOR_11:
		*start_address = ADDR_FLASH_SECTOR_11;
		*end_address = ADDR_FLASH_END;
		break;
	default:
		*start_address = 0;
		*end_address = 0;
		ret = false;
		break;
	}
#elif defined(STM32F103xB) || defined(STM32F103x8)
  if (sector > 127)
  {
		*start_address = 0;
		*end_address = 0;
		ret = false;
  }
  else
  {
		*start_address = ADDR_FLASH_SECTOR_0 + sector*FLASH_SECTORS_SIZE;
		*end_address = ADDR_FLASH_SECTOR_0 + (sector + 1)*FLASH_SECTORS_SIZE - 1;
  }
#endif
	return ret;
}

/*###############################################################*/
/*###############################################################* NVIC_SetVectorTable -->*/
/*###############################################################*/
/**
  * @brief  Sets the vector table location and Offset.
  * @param  NVIC_VectTab: specifies if the vector table is in RAM or FLASH memory.
  *   This parameter can be one of the following values:
  *     @arg NVIC_VectTab_RAM
  *     @arg NVIC_VectTab_FLASH
  * @param  Offset: Vector Table base offset field. This value must be a multiple 
  *         of 0x200.
  * @retval None
  */
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{ 
  /* Check the parameters */
  assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
  assert_param(IS_NVIC_OFFSET(Offset));  
   
  SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}
/*###############################################################*/
/*###############################################################* Jump_To_Addres_Flash -->*/
/*###############################################################*/
//jump to address
void Jump_To_Address_Firmware(uint32_t addr)
{
  __disable_irq();

	//disable all interrupts in NVIC
	NVIC->ICER[0] = 0xFFFFFFFF;
	NVIC->ICER[1] = 0xFFFFFFFF;
	NVIC->ICER[2] = 0xFFFFFFFF;

	//clean all pending bit
	NVIC->ICPR[0] = 0xFFFFFFFF;
	NVIC->ICPR[1] = 0xFFFFFFFF;
	NVIC->ICPR[2] = 0xFFFFFFFF;

	//Peripheral risit enable (do not touch reserved bits)
	RCC->APB1RSTR = 0x3E7EC83F;
	RCC->APB2RSTR = 0x00005E7D;
	//Peripheral  risit disable
	RCC->APB1RSTR = 0;
	RCC->APB2RSTR = 0;
	//Peripheral  disable clock
	RCC->APB1ENR = 0;
	RCC->APB2ENR = 0;	
	
	HAL_RCC_DeInit();
#if defined(BOOTLOADER_USE_USB_FS)
	USBD_DeInit(&hUsbDeviceFS);
#endif
	
	
	  SysTick->CTRL = 0;
	  SysTick->LOAD = 0;
	  SysTick->VAL = 0;

#if defined(STM32F4)
  __HAL_SYSCFG_REMAPMEMORY_FLASH();
#endif

	/* Set system control register SCR->VTOR  */
	SCB->VTOR = addr;

	  void (*SysMemJump)(void);
	  SysMemJump = (void (*)(void))(*((uint32_t *)(addr + 4)));
	  __set_MSP(*(uint32_t *)addr);
	  SysMemJump();
}
