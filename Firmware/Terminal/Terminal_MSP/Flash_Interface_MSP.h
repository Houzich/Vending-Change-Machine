/**
  ******************************************************************************
  * File Name          : Flash_Interface.h
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BOOT_FLASH_INTERFACE_H
#define __BOOT_FLASH_INTERFACE_H
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Base address of the Flash sectors Bank 1 */
/*--------------------------------------- STM32F40xxx/STM32F41xxx -------------------------------------*/
#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx)
#define ADDR_FLASH_SECTOR_0 ((uint32_t)0x08000000)  /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1 ((uint32_t)0x08004000)  /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2 ((uint32_t)0x08008000)  /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3 ((uint32_t)0x0800C000)  /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4 ((uint32_t)0x08010000)  /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5 ((uint32_t)0x08020000)  /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6 ((uint32_t)0x08040000)  /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7 ((uint32_t)0x08060000)  /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8 ((uint32_t)0x08080000)  /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9 ((uint32_t)0x080A0000)  /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10 ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11 ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */
#define ADDR_FLASH_END ((uint32_t)0x080FFFFF)
#define NUM_FLASH_SECTORS ((uint32_t)12)
#define FLASH_SECTOR_NO 0xFFU
#elif defined(STM32F103xB) || defined(STM32F103x8)
#define FLASH_SECTORS_SIZE          0x400U
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Page 0, 1 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08000400) /* Base @ of Page 1, 1 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08000800) /* Base @ of Page 2, 1 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x08000C00) /* Base @ of Page 3, 1 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08001000) /* Base @ of Page 4, 1 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08001400) /* Base @ of Page 5, 1 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08001800) /* Base @ of Page 6, 1 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08001C00) /* Base @ of Page 7, 1 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08002000) /* Base @ of Page 8, 1 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x08002400) /* Base @ of Page 9, 1 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x08002800) /* Base @ of Page 10, 1 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x08002C00) /* Base @ of Page 11, 1 Kbytes */
#define ADDR_FLASH_SECTOR_12    ((uint32_t)0x08003000) /* Base @ of Page 12, 1 Kbytes */
#define ADDR_FLASH_SECTOR_13    ((uint32_t)0x08003400) /* Base @ of Page 13, 1 Kbytes */
#define ADDR_FLASH_SECTOR_14    ((uint32_t)0x08003800) /* Base @ of Page 14, 1 Kbytes */
#define ADDR_FLASH_SECTOR_15    ((uint32_t)0x08003C00) /* Base @ of Page 15, 1 Kbytes */
#define ADDR_FLASH_SECTOR_16    ((uint32_t)0x08004000) /* Base @ of Page 16, 1 Kbytes */
#define ADDR_FLASH_SECTOR_17    ((uint32_t)0x08004400) /* Base @ of Page 17, 1 Kbytes */
#define ADDR_FLASH_SECTOR_18    ((uint32_t)0x08004800) /* Base @ of Page 18, 1 Kbytes */
#define ADDR_FLASH_SECTOR_19    ((uint32_t)0x08004C00) /* Base @ of Page 19, 1 Kbytes */
#define ADDR_FLASH_SECTOR_20    ((uint32_t)0x08005000) /* Base @ of Page 20, 1 Kbytes */
#define ADDR_FLASH_SECTOR_21    ((uint32_t)0x08005400) /* Base @ of Page 21, 1 Kbytes */
#define ADDR_FLASH_SECTOR_22    ((uint32_t)0x08005800) /* Base @ of Page 22, 1 Kbytes */
#define ADDR_FLASH_SECTOR_23    ((uint32_t)0x08005C00) /* Base @ of Page 23, 1 Kbytes */
#define ADDR_FLASH_SECTOR_24    ((uint32_t)0x08006000) /* Base @ of Page 24, 1 Kbytes */
#define ADDR_FLASH_SECTOR_25    ((uint32_t)0x08006400) /* Base @ of Page 25, 1 Kbytes */
#define ADDR_FLASH_SECTOR_26    ((uint32_t)0x08006800) /* Base @ of Page 26, 1 Kbytes */
#define ADDR_FLASH_SECTOR_27    ((uint32_t)0x08006C00) /* Base @ of Page 27, 1 Kbytes */
#define ADDR_FLASH_SECTOR_28    ((uint32_t)0x08007000) /* Base @ of Page 28, 1 Kbytes */
#define ADDR_FLASH_SECTOR_29    ((uint32_t)0x08007400) /* Base @ of Page 29, 1 Kbytes */
#define ADDR_FLASH_SECTOR_30    ((uint32_t)0x08007800) /* Base @ of Page 30, 1 Kbytes */
#define ADDR_FLASH_SECTOR_31    ((uint32_t)0x08007C00) /* Base @ of Page 31, 1 Kbytes */
#define ADDR_FLASH_SECTOR_32    ((uint32_t)0x08008000) /* Base @ of Page 32, 1 Kbytes */
#define ADDR_FLASH_SECTOR_33    ((uint32_t)0x08008400) /* Base @ of Page 33, 1 Kbytes */
#define ADDR_FLASH_SECTOR_34    ((uint32_t)0x08008800) /* Base @ of Page 34, 1 Kbytes */
#define ADDR_FLASH_SECTOR_35    ((uint32_t)0x08008C00) /* Base @ of Page 35, 1 Kbytes */
#define ADDR_FLASH_SECTOR_36    ((uint32_t)0x08009000) /* Base @ of Page 36, 1 Kbytes */
#define ADDR_FLASH_SECTOR_37    ((uint32_t)0x08009400) /* Base @ of Page 37, 1 Kbytes */
#define ADDR_FLASH_SECTOR_38    ((uint32_t)0x08009800) /* Base @ of Page 38, 1 Kbytes */
#define ADDR_FLASH_SECTOR_39    ((uint32_t)0x08009C00) /* Base @ of Page 39, 1 Kbytes */
#define ADDR_FLASH_SECTOR_40    ((uint32_t)0x0800A000) /* Base @ of Page 40, 1 Kbytes */
#define ADDR_FLASH_SECTOR_41    ((uint32_t)0x0800A400) /* Base @ of Page 41, 1 Kbytes */
#define ADDR_FLASH_SECTOR_42    ((uint32_t)0x0800A800) /* Base @ of Page 42, 1 Kbytes */
#define ADDR_FLASH_SECTOR_43    ((uint32_t)0x0800AC00) /* Base @ of Page 43, 1 Kbytes */
#define ADDR_FLASH_SECTOR_44    ((uint32_t)0x0800B000) /* Base @ of Page 44, 1 Kbytes */
#define ADDR_FLASH_SECTOR_45    ((uint32_t)0x0800B400) /* Base @ of Page 45, 1 Kbytes */
#define ADDR_FLASH_SECTOR_46    ((uint32_t)0x0800B800) /* Base @ of Page 46, 1 Kbytes */
#define ADDR_FLASH_SECTOR_47    ((uint32_t)0x0800BC00) /* Base @ of Page 47, 1 Kbytes */
#define ADDR_FLASH_SECTOR_48    ((uint32_t)0x0800C000) /* Base @ of Page 48, 1 Kbytes */
#define ADDR_FLASH_SECTOR_49    ((uint32_t)0x0800C400) /* Base @ of Page 49, 1 Kbytes */
#define ADDR_FLASH_SECTOR_50    ((uint32_t)0x0800C800) /* Base @ of Page 50, 1 Kbytes */
#define ADDR_FLASH_SECTOR_51    ((uint32_t)0x0800CC00) /* Base @ of Page 51, 1 Kbytes */
#define ADDR_FLASH_SECTOR_52    ((uint32_t)0x0800D000) /* Base @ of Page 52, 1 Kbytes */
#define ADDR_FLASH_SECTOR_53    ((uint32_t)0x0800D400) /* Base @ of Page 53, 1 Kbytes */
#define ADDR_FLASH_SECTOR_54    ((uint32_t)0x0800D800) /* Base @ of Page 54, 1 Kbytes */
#define ADDR_FLASH_SECTOR_55    ((uint32_t)0x0800DC00) /* Base @ of Page 55, 1 Kbytes */
#define ADDR_FLASH_SECTOR_56    ((uint32_t)0x0800E000) /* Base @ of Page 56, 1 Kbytes */
#define ADDR_FLASH_SECTOR_57    ((uint32_t)0x0800E400) /* Base @ of Page 57, 1 Kbytes */
#define ADDR_FLASH_SECTOR_58    ((uint32_t)0x0800E800) /* Base @ of Page 58, 1 Kbytes */
#define ADDR_FLASH_SECTOR_59    ((uint32_t)0x0800EC00) /* Base @ of Page 59, 1 Kbytes */
#define ADDR_FLASH_SECTOR_60    ((uint32_t)0x0800F000) /* Base @ of Page 60, 1 Kbytes */
#define ADDR_FLASH_SECTOR_61    ((uint32_t)0x0800F400) /* Base @ of Page 61, 1 Kbytes */
#define ADDR_FLASH_SECTOR_62    ((uint32_t)0x0800F800) /* Base @ of Page 62, 1 Kbytes */
#define ADDR_FLASH_SECTOR_63    ((uint32_t)0x0800FC00) /* Base @ of Page 63, 1 Kbytes */
#define ADDR_FLASH_SECTOR_64    ((uint32_t)0x08010000) /* Base @ of Page 64, 1 Kbytes */
#define ADDR_FLASH_SECTOR_65    ((uint32_t)0x08010400) /* Base @ of Page 65, 1 Kbytes */
#define ADDR_FLASH_SECTOR_66    ((uint32_t)0x08010800) /* Base @ of Page 66, 1 Kbytes */
#define ADDR_FLASH_SECTOR_67    ((uint32_t)0x08010C00) /* Base @ of Page 67, 1 Kbytes */
#define ADDR_FLASH_SECTOR_68    ((uint32_t)0x08011000) /* Base @ of Page 68, 1 Kbytes */
#define ADDR_FLASH_SECTOR_69    ((uint32_t)0x08011400) /* Base @ of Page 69, 1 Kbytes */
#define ADDR_FLASH_SECTOR_70    ((uint32_t)0x08011800) /* Base @ of Page 70, 1 Kbytes */
#define ADDR_FLASH_SECTOR_71    ((uint32_t)0x08011C00) /* Base @ of Page 71, 1 Kbytes */
#define ADDR_FLASH_SECTOR_72    ((uint32_t)0x08012000) /* Base @ of Page 72, 1 Kbytes */
#define ADDR_FLASH_SECTOR_73    ((uint32_t)0x08012400) /* Base @ of Page 73, 1 Kbytes */
#define ADDR_FLASH_SECTOR_74    ((uint32_t)0x08012800) /* Base @ of Page 74, 1 Kbytes */
#define ADDR_FLASH_SECTOR_75    ((uint32_t)0x08012C00) /* Base @ of Page 75, 1 Kbytes */
#define ADDR_FLASH_SECTOR_76    ((uint32_t)0x08013000) /* Base @ of Page 76, 1 Kbytes */
#define ADDR_FLASH_SECTOR_77    ((uint32_t)0x08013400) /* Base @ of Page 77, 1 Kbytes */
#define ADDR_FLASH_SECTOR_78    ((uint32_t)0x08013800) /* Base @ of Page 78, 1 Kbytes */
#define ADDR_FLASH_SECTOR_79    ((uint32_t)0x08013C00) /* Base @ of Page 79, 1 Kbytes */
#define ADDR_FLASH_SECTOR_80    ((uint32_t)0x08014000) /* Base @ of Page 80, 1 Kbytes */
#define ADDR_FLASH_SECTOR_81    ((uint32_t)0x08014400) /* Base @ of Page 81, 1 Kbytes */
#define ADDR_FLASH_SECTOR_82    ((uint32_t)0x08014800) /* Base @ of Page 82, 1 Kbytes */
#define ADDR_FLASH_SECTOR_83    ((uint32_t)0x08014C00) /* Base @ of Page 83, 1 Kbytes */
#define ADDR_FLASH_SECTOR_84    ((uint32_t)0x08015000) /* Base @ of Page 84, 1 Kbytes */
#define ADDR_FLASH_SECTOR_85    ((uint32_t)0x08015400) /* Base @ of Page 85, 1 Kbytes */
#define ADDR_FLASH_SECTOR_86    ((uint32_t)0x08015800) /* Base @ of Page 86, 1 Kbytes */
#define ADDR_FLASH_SECTOR_87    ((uint32_t)0x08015C00) /* Base @ of Page 87, 1 Kbytes */
#define ADDR_FLASH_SECTOR_88    ((uint32_t)0x08016000) /* Base @ of Page 88, 1 Kbytes */
#define ADDR_FLASH_SECTOR_89    ((uint32_t)0x08016400) /* Base @ of Page 89, 1 Kbytes */
#define ADDR_FLASH_SECTOR_90    ((uint32_t)0x08016800) /* Base @ of Page 90, 1 Kbytes */
#define ADDR_FLASH_SECTOR_91    ((uint32_t)0x08016C00) /* Base @ of Page 91, 1 Kbytes */
#define ADDR_FLASH_SECTOR_92    ((uint32_t)0x08017000) /* Base @ of Page 92, 1 Kbytes */
#define ADDR_FLASH_SECTOR_93    ((uint32_t)0x08017400) /* Base @ of Page 93, 1 Kbytes */
#define ADDR_FLASH_SECTOR_94    ((uint32_t)0x08017800) /* Base @ of Page 94, 1 Kbytes */
#define ADDR_FLASH_SECTOR_95    ((uint32_t)0x08017C00) /* Base @ of Page 95, 1 Kbytes */
#define ADDR_FLASH_SECTOR_96    ((uint32_t)0x08018000) /* Base @ of Page 96, 1 Kbytes */
#define ADDR_FLASH_SECTOR_97    ((uint32_t)0x08018400) /* Base @ of Page 97, 1 Kbytes */
#define ADDR_FLASH_SECTOR_98    ((uint32_t)0x08018800) /* Base @ of Page 98, 1 Kbytes */
#define ADDR_FLASH_SECTOR_99    ((uint32_t)0x08018C00) /* Base @ of Page 99, 1 Kbytes */
#define ADDR_FLASH_SECTOR_100   ((uint32_t)0x08019000) /* Base @ of Page 100, 1 Kbytes */
#define ADDR_FLASH_SECTOR_101   ((uint32_t)0x08019400) /* Base @ of Page 101, 1 Kbytes */
#define ADDR_FLASH_SECTOR_102   ((uint32_t)0x08019800) /* Base @ of Page 102, 1 Kbytes */
#define ADDR_FLASH_SECTOR_103   ((uint32_t)0x08019C00) /* Base @ of Page 103, 1 Kbytes */
#define ADDR_FLASH_SECTOR_104   ((uint32_t)0x0801A000) /* Base @ of Page 104, 1 Kbytes */
#define ADDR_FLASH_SECTOR_105   ((uint32_t)0x0801A400) /* Base @ of Page 105, 1 Kbytes */
#define ADDR_FLASH_SECTOR_106   ((uint32_t)0x0801A800) /* Base @ of Page 106, 1 Kbytes */
#define ADDR_FLASH_SECTOR_107   ((uint32_t)0x0801AC00) /* Base @ of Page 107, 1 Kbytes */
#define ADDR_FLASH_SECTOR_108   ((uint32_t)0x0801B000) /* Base @ of Page 108, 1 Kbytes */
#define ADDR_FLASH_SECTOR_109   ((uint32_t)0x0801B400) /* Base @ of Page 109, 1 Kbytes */
#define ADDR_FLASH_SECTOR_110   ((uint32_t)0x0801B800) /* Base @ of Page 110, 1 Kbytes */
#define ADDR_FLASH_SECTOR_111   ((uint32_t)0x0801BC00) /* Base @ of Page 111, 1 Kbytes */
#define ADDR_FLASH_SECTOR_112   ((uint32_t)0x0801C000) /* Base @ of Page 112, 1 Kbytes */
#define ADDR_FLASH_SECTOR_113   ((uint32_t)0x0801C400) /* Base @ of Page 113, 1 Kbytes */
#define ADDR_FLASH_SECTOR_114   ((uint32_t)0x0801C800) /* Base @ of Page 114, 1 Kbytes */
#define ADDR_FLASH_SECTOR_115   ((uint32_t)0x0801CC00) /* Base @ of Page 115, 1 Kbytes */
#define ADDR_FLASH_SECTOR_116   ((uint32_t)0x0801D000) /* Base @ of Page 116, 1 Kbytes */
#define ADDR_FLASH_SECTOR_117   ((uint32_t)0x0801D400) /* Base @ of Page 117, 1 Kbytes */
#define ADDR_FLASH_SECTOR_118   ((uint32_t)0x0801D800) /* Base @ of Page 118, 1 Kbytes */
#define ADDR_FLASH_SECTOR_119   ((uint32_t)0x0801DC00) /* Base @ of Page 119, 1 Kbytes */
#define ADDR_FLASH_SECTOR_120   ((uint32_t)0x0801E000) /* Base @ of Page 120, 1 Kbytes */
#define ADDR_FLASH_SECTOR_121   ((uint32_t)0x0801E400) /* Base @ of Page 121, 1 Kbytes */
#define ADDR_FLASH_SECTOR_122   ((uint32_t)0x0801E800) /* Base @ of Page 122, 1 Kbytes */
#define ADDR_FLASH_SECTOR_123   ((uint32_t)0x0801EC00) /* Base @ of Page 123, 1 Kbytes */
#define ADDR_FLASH_SECTOR_124   ((uint32_t)0x0801F000) /* Base @ of Page 124, 1 Kbytes */
#define ADDR_FLASH_SECTOR_125   ((uint32_t)0x0801F400) /* Base @ of Page 125, 1 Kbytes */
#define ADDR_FLASH_SECTOR_126   ((uint32_t)0x0801F800) /* Base @ of Page 126, 1 Kbytes */
#define ADDR_FLASH_SECTOR_127   ((uint32_t)0x0801FC00) /* Base @ of Page 127, 1 Kbytes */
#define ADDR_FLASH_END ((uint32_t)(ADDR_FLASH_SECTOR_127 + FLASH_SECTORS_SIZE))
#endif


/*--------------------------------------- STM32F40xxx/STM32F41xxx -------------------------------------*/
#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx)
#define FLASH_SECTOR_0     0U  /*!< Sector Number 0   */
#define FLASH_SECTOR_1     1U  /*!< Sector Number 1   */
#define FLASH_SECTOR_2     2U  /*!< Sector Number 2   */
#define FLASH_SECTOR_3     3U  /*!< Sector Number 3   */
#define FLASH_SECTOR_4     4U  /*!< Sector Number 4   */
#define FLASH_SECTOR_5     5U  /*!< Sector Number 5   */
#define FLASH_SECTOR_6     6U  /*!< Sector Number 6   */
#define FLASH_SECTOR_7     7U  /*!< Sector Number 7   */
#define FLASH_SECTOR_8     8U  /*!< Sector Number 8   */
#define FLASH_SECTOR_9     9U  /*!< Sector Number 9   */
#define FLASH_SECTOR_10    10U /*!< Sector Number 10  */
#define FLASH_SECTOR_11    11U /*!< Sector Number 11  */
#endif /* STM32F405xx || STM32F415xx || STM32F407xx || STM32F417xx || STM32F412Zx || STM32F412Vx || STM32F412Rx || STM32F412Cx */
/*-----------------------------------------------------------------------------------------------------*/

/*--------------------------------------- STM32F303xC -------------------------------------*/
#if defined(STM32F303xC)
#define FLASH_SECTOR_0     0U  /*!< Sector Number 0   */
#define FLASH_SECTOR_1     1U  /*!< Sector Number 1   */
#define FLASH_SECTOR_2     2U  /*!< Sector Number 2   */
#define FLASH_SECTOR_3     3U  /*!< Sector Number 3   */
#define FLASH_SECTOR_4     4U  /*!< Sector Number 4   */
#define FLASH_SECTOR_5     5U  /*!< Sector Number 5   */
#define FLASH_SECTOR_6     6U  /*!< Sector Number 6   */
#define FLASH_SECTOR_7     7U  /*!< Sector Number 7   */
#define FLASH_SECTOR_8     8U  /*!< Sector Number 8   */
#define FLASH_SECTOR_9     9U  /*!< Sector Number 9   */
#define FLASH_SECTOR_10    10U /*!< Sector Number 10  */
#define FLASH_SECTOR_11    11U /*!< Sector Number 11  */
#define IS_FLASH_SECTOR(SECTOR) ( ((SECTOR) == FLASH_SECTOR_0)   || ((SECTOR) == FLASH_SECTOR_1)   ||\
                                  ((SECTOR) == FLASH_SECTOR_2)   || ((SECTOR) == FLASH_SECTOR_3)   ||\
                                  ((SECTOR) == FLASH_SECTOR_4)   || ((SECTOR) == FLASH_SECTOR_5)   ||\
                                  ((SECTOR) == FLASH_SECTOR_6)   || ((SECTOR) == FLASH_SECTOR_7)   ||\
                                  ((SECTOR) == FLASH_SECTOR_8)   || ((SECTOR) == FLASH_SECTOR_9)   ||\
                                  ((SECTOR) == FLASH_SECTOR_10)  || ((SECTOR) == FLASH_SECTOR_11))
#endif /* STM32F303xC */
/*-----------------------------------------------------------------------------------------------------*/

/*--------------------------------------- STM32F103xB -------------------------------------*/
#if defined(STM32F103xB) || defined(STM32F103x8)
#define FLASH_SECTOR_0     	0  /*!< Sector Number    */
#define FLASH_SECTOR_1     	1U  /*!< Sector Number    */
#define FLASH_SECTOR_2     	2U  /*!< Sector Number    */
#define FLASH_SECTOR_3     	3U  /*!< Sector Number    */
#define FLASH_SECTOR_4     	4U  /*!< Sector Number    */
#define FLASH_SECTOR_5     	5U  /*!< Sector Number    */
#define FLASH_SECTOR_6     	6U  /*!< Sector Number    */
#define FLASH_SECTOR_7     	7U  /*!< Sector Number    */
#define FLASH_SECTOR_8     	8U  /*!< Sector Number    */
#define FLASH_SECTOR_9     	9U  /*!< Sector Number    */
#define FLASH_SECTOR_10     10U  /*!< Sector Number    */
#define FLASH_SECTOR_11     11U  /*!< Sector Number    */
#define FLASH_SECTOR_12     12U  /*!< Sector Number    */
#define FLASH_SECTOR_13     13U  /*!< Sector Number    */
#define FLASH_SECTOR_14     14U  /*!< Sector Number    */
#define FLASH_SECTOR_15     15U  /*!< Sector Number    */
#define FLASH_SECTOR_16     16U  /*!< Sector Number    */
#define FLASH_SECTOR_17     17U  /*!< Sector Number    */
#define FLASH_SECTOR_18     18U  /*!< Sector Number    */
#define FLASH_SECTOR_19     19U  /*!< Sector Number    */
#define FLASH_SECTOR_20     20U  /*!< Sector Number    */
#define FLASH_SECTOR_21     21U  /*!< Sector Number    */
#define FLASH_SECTOR_22     22U  /*!< Sector Number    */
#define FLASH_SECTOR_23     23U  /*!< Sector Number    */
#define FLASH_SECTOR_24     24U  /*!< Sector Number    */
#define FLASH_SECTOR_25     25U  /*!< Sector Number    */
#define FLASH_SECTOR_26     26U  /*!< Sector Number    */
#define FLASH_SECTOR_27     27U  /*!< Sector Number    */
#define FLASH_SECTOR_28     28U  /*!< Sector Number    */
#define FLASH_SECTOR_29     29U  /*!< Sector Number    */
#define FLASH_SECTOR_30     30U  /*!< Sector Number    */
#define FLASH_SECTOR_31     31U  /*!< Sector Number    */
#define FLASH_SECTOR_32    	32U  /*!< Sector Number    */
#define FLASH_SECTOR_33     33U  /*!< Sector Number    */
#define FLASH_SECTOR_34     34U  /*!< Sector Number    */
#define FLASH_SECTOR_35     35U  /*!< Sector Number    */
#define FLASH_SECTOR_36     36U  /*!< Sector Number    */
#define FLASH_SECTOR_37     37U  /*!< Sector Number    */
#define FLASH_SECTOR_38     38U  /*!< Sector Number    */
#define FLASH_SECTOR_39     39U  /*!< Sector Number    */
#define FLASH_SECTOR_40     40U  /*!< Sector Number    */
#define FLASH_SECTOR_41     41U  /*!< Sector Number    */
#define FLASH_SECTOR_42     42U  /*!< Sector Number    */
#define FLASH_SECTOR_43     43U  /*!< Sector Number    */
#define FLASH_SECTOR_44     44U  /*!< Sector Number    */
#define FLASH_SECTOR_45     45U  /*!< Sector Number    */
#define FLASH_SECTOR_46     46U  /*!< Sector Number    */
#define FLASH_SECTOR_47     47U  /*!< Sector Number    */
#define FLASH_SECTOR_48     48U  /*!< Sector Number    */
#define FLASH_SECTOR_49     49U  /*!< Sector Number    */
#define FLASH_SECTOR_50     50U  /*!< Sector Number    */
#define FLASH_SECTOR_51     51U  /*!< Sector Number    */
#define FLASH_SECTOR_52     52U  /*!< Sector Number    */
#define FLASH_SECTOR_53     53U  /*!< Sector Number    */
#define FLASH_SECTOR_54     54U  /*!< Sector Number    */
#define FLASH_SECTOR_55     55U  /*!< Sector Number    */
#define FLASH_SECTOR_56     56U  /*!< Sector Number    */
#define FLASH_SECTOR_57     57U  /*!< Sector Number    */
#define FLASH_SECTOR_58     58U  /*!< Sector Number    */
#define FLASH_SECTOR_59     59U  /*!< Sector Number    */
#define FLASH_SECTOR_60     60U  /*!< Sector Number    */
#define FLASH_SECTOR_61     61U  /*!< Sector Number    */
#define FLASH_SECTOR_62     62U  /*!< Sector Number    */
#define FLASH_SECTOR_63     63U  /*!< Sector Number    */
#define FLASH_SECTOR_64     64U  /*!< Sector Number    */
#define FLASH_SECTOR_65     65U  /*!< Sector Number    */
#define FLASH_SECTOR_66     66U  /*!< Sector Number    */
#define FLASH_SECTOR_67     67U  /*!< Sector Number    */
#define FLASH_SECTOR_68     68U  /*!< Sector Number    */
#define FLASH_SECTOR_69     69U  /*!< Sector Number    */
#define FLASH_SECTOR_70     70U  /*!< Sector Number    */
#define FLASH_SECTOR_71     71U  /*!< Sector Number    */
#define FLASH_SECTOR_72     72U  /*!< Sector Number    */
#define FLASH_SECTOR_73     73U  /*!< Sector Number    */
#define FLASH_SECTOR_74     74U  /*!< Sector Number    */
#define FLASH_SECTOR_75     75U  /*!< Sector Number    */
#define FLASH_SECTOR_76     76U  /*!< Sector Number    */
#define FLASH_SECTOR_77     77U  /*!< Sector Number    */
#define FLASH_SECTOR_78     78U  /*!< Sector Number    */
#define FLASH_SECTOR_79     79U  /*!< Sector Number    */
#define FLASH_SECTOR_80     80U  /*!< Sector Number    */
#define FLASH_SECTOR_81     81U  /*!< Sector Number    */
#define FLASH_SECTOR_82     82U  /*!< Sector Number    */
#define FLASH_SECTOR_83     83U  /*!< Sector Number    */
#define FLASH_SECTOR_84     84U  /*!< Sector Number    */
#define FLASH_SECTOR_85     85U  /*!< Sector Number    */
#define FLASH_SECTOR_86     86U  /*!< Sector Number    */
#define FLASH_SECTOR_87     87U  /*!< Sector Number    */
#define FLASH_SECTOR_88     88U  /*!< Sector Number    */
#define FLASH_SECTOR_89     89U  /*!< Sector Number    */
#define FLASH_SECTOR_90     90U  /*!< Sector Number    */
#define FLASH_SECTOR_91     91U  /*!< Sector Number    */
#define FLASH_SECTOR_92     92U  /*!< Sector Number    */
#define FLASH_SECTOR_93     93U  /*!< Sector Number    */
#define FLASH_SECTOR_94     94U  /*!< Sector Number    */
#define FLASH_SECTOR_95     95U  /*!< Sector Number    */
#define FLASH_SECTOR_96     96U  /*!< Sector Number    */
#define FLASH_SECTOR_97     97U  /*!< Sector Number    */
#define FLASH_SECTOR_98     98U  /*!< Sector Number    */
#define FLASH_SECTOR_99     99U  /*!< Sector Number    */
#define FLASH_SECTOR_100    100U  /*!< Sector Number    */
#define FLASH_SECTOR_101    101U  /*!< Sector Number    */
#define FLASH_SECTOR_102    102U  /*!< Sector Number    */
#define FLASH_SECTOR_103    103U  /*!< Sector Number    */
#define FLASH_SECTOR_104    104U  /*!< Sector Number    */
#define FLASH_SECTOR_105    105U  /*!< Sector Number    */
#define FLASH_SECTOR_106    106U  /*!< Sector Number    */
#define FLASH_SECTOR_107    107U  /*!< Sector Number    */
#define FLASH_SECTOR_108    108U  /*!< Sector Number    */
#define FLASH_SECTOR_109    109U  /*!< Sector Number    */
#define FLASH_SECTOR_110    110U  /*!< Sector Number    */
#define FLASH_SECTOR_111    111U  /*!< Sector Number    */
#define FLASH_SECTOR_112    112U  /*!< Sector Number    */
#define FLASH_SECTOR_113    113U  /*!< Sector Number    */
#define FLASH_SECTOR_114    114U  /*!< Sector Number    */
#define FLASH_SECTOR_115    115U  /*!< Sector Number    */
#define FLASH_SECTOR_116    116U  /*!< Sector Number    */
#define FLASH_SECTOR_117    117U  /*!< Sector Number    */
#define FLASH_SECTOR_118    118U  /*!< Sector Number    */
#define FLASH_SECTOR_119    119U  /*!< Sector Number    */
#define FLASH_SECTOR_120    120U  /*!< Sector Number    */
#define FLASH_SECTOR_121    121U  /*!< Sector Number    */
#define FLASH_SECTOR_122    122U  /*!< Sector Number    */
#define FLASH_SECTOR_123    123U  /*!< Sector Number    */
#define FLASH_SECTOR_124    124U  /*!< Sector Number    */
#define FLASH_SECTOR_125    125U  /*!< Sector Number    */
#define FLASH_SECTOR_126    126U  /*!< Sector Number    */
#define FLASH_SECTOR_127    127U  /*!< Sector Number    */
#define NUM_FLASH_SECTORS ((uint32_t)128)
#define FLASH_SECTOR_NO 0xFFU
#define IS_FLASH_SECTOR(SECTOR) ((uint32_t)(SECTOR) <= FLASH_SECTOR_127)
#endif /* STM32F103xB */
/*-----------------------------------------------------------------------------------------------------*/
#define NVIC_VectTab_RAM             ((uint32_t)0x20000000)
#define NVIC_VectTab_FLASH           ((uint32_t)0x08000000)
#define IS_NVIC_VECTTAB(VECTTAB) (((VECTTAB) == NVIC_VectTab_RAM) || \
                                  ((VECTTAB) == NVIC_VectTab_FLASH))
#define IS_NVIC_OFFSET(OFFSET)  ((OFFSET) < 0x000FFFFF)

/* Exported Macros -----------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/



uint32_t Get_Sector(uint32_t address);
uint32_t Get_Sector_Size(uint32_t Sector);
uint32_t Read_Word_Flash(uint32_t address);
bool Get_Sector_Addresses(uint32_t sector, uint32_t *start_address, uint32_t *end_address);
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
void Jump_To_Address_Firmware(uint32_t addr);
#endif /*__BOOT_FLASH_INTERFACE_H*/
	   /************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
