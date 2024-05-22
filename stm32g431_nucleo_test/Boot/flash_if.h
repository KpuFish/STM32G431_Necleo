/**
  ******************************************************************************
  * @file    IAP_Main/Inc/flash_if.h 
  * @author  MCD Application Team
  * @brief   This file provides all the headers of the flash_if functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_IF_H
#define __FLASH_IF_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* STM32G431, 128KByte Flash, Single Bank [1 Page - 2KByte Range]
PAGE 0:  0x08000000 - 0x080007FF
PAGE 1:  0x08000800 - 0x08000FFF
PAGE 2:  0x08001000 - 0x080017FF
PAGE 3:  0x08001800 - 0x08001FFF
PAGE 4:  0x08002000 - 0x080027FF
PAGE 5:  0x08002800 - 0x08002FFF
PAGE 6:  0x08003000 - 0x080037FF
PAGE 7:  0x08003800 - 0x08003FFF
PAGE 8:  0x08004000 - 0x080047FF
PAGE 9:  0x08004800 - 0x08004FFF
PAGE 10: 0x08005000 - 0x080057FF
PAGE 11: 0x08005800 - 0x08005FFF
PAGE 12: 0x08006000 - 0x080067FF
PAGE 13: 0x08006800 - 0x08006FFF
PAGE 14: 0x08007000 - 0x080077FF
PAGE 15: 0x08007800 - 0x08007FFF
PAGE 16: 0x08008000 - 0x080087FF
PAGE 17: 0x08008800 - 0x08008FFF
PAGE 18: 0x08009000 - 0x080097FF
PAGE 19: 0x08009800 - 0x08009FFF
PAGE 20: 0x0800A000 - 0x0800A7FF
PAGE 21: 0x0800A800 - 0x0800AFFF
PAGE 22: 0x0800B000 - 0x0800B7FF
PAGE 23: 0x0800B800 - 0x0800BFFF
PAGE 24: 0x0800C000 - 0x0800C7FF
PAGE 25: 0x0800C800 - 0x0800CFFF
PAGE 26: 0x0800D000 - 0x0800D7FF
PAGE 27: 0x0800D800 - 0x0800DFFF
PAGE 28: 0x0800E000 - 0x0800E7FF
PAGE 29: 0x0800E800 - 0x0800EFFF
PAGE 30: 0x0800F000 - 0x0800F7FF
PAGE 31: 0x0800F800 - 0x0800FFFF
PAGE 32: 0x08010000 - 0x080107FF
PAGE 33: 0x08010800 - 0x08010FFF
PAGE 34: 0x08011000 - 0x080117FF
PAGE 35: 0x08011800 - 0x08011FFF
PAGE 36: 0x08012000 - 0x080127FF
PAGE 37: 0x08012800 - 0x08012FFF
PAGE 38: 0x08013000 - 0x080137FF
PAGE 39: 0x08013800 - 0x08013FFF
PAGE 40: 0x08014000 - 0x080147FF
PAGE 41: 0x08014800 - 0x08014FFF
PAGE 42: 0x08015000 - 0x080157FF
PAGE 43: 0x08015800 - 0x08015FFF
PAGE 44: 0x08016000 - 0x080167FF
PAGE 45: 0x08016800 - 0x08016FFF
PAGE 46: 0x08017000 - 0x080177FF
PAGE 47: 0x08017800 - 0x08017FFF
PAGE 48: 0x08018000 - 0x080187FF
PAGE 49: 0x08018800 - 0x08018FFF
PAGE 50: 0x08019000 - 0x080197FF
PAGE 51: 0x08019800 - 0x08019FFF
PAGE 52: 0x0801A000 - 0x0801A7FF
PAGE 53: 0x0801A800 - 0x0801AFFF
PAGE 54: 0x0801B000 - 0x0801B7FF
PAGE 55: 0x0801B800 - 0x0801BFFF
PAGE 56: 0x0801C000 - 0x0801C7FF
PAGE 57: 0x0801C800 - 0x0801CFFF
PAGE 58: 0x0801D000 - 0x0801D7FF
PAGE 59: 0x0801D800 - 0x0801DFFF
PAGE 60: 0x0801E000 - 0x0801E7FF
PAGE 61: 0x0801E800 - 0x0801EFFF
PAGE 62: 0x0801F000 - 0x0801F7FF
PAGE 63: 0x0801F800 - 0x0801FFFF
*/


/* Base address of the Flash pages */
#define ADDR_FLASH_SECTOR_0_BANK1      ((uint32_t)0x08000000) /* Base @ of PAGE 0,  Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_1_BANK1      ((uint32_t)0x08000800) /* Base @ of PAGE 1,  Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_2_BANK1      ((uint32_t)0x08001000) /* Base @ of PAGE 2,  Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_3_BANK1      ((uint32_t)0x08001800) /* Base @ of PAGE 3,  Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_4_BANK1      ((uint32_t)0x08002000) /* Base @ of PAGE 4,  Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_5_BANK1      ((uint32_t)0x08002800) /* Base @ of PAGE 5,  Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_6_BANK1      ((uint32_t)0x08003000) /* Base @ of PAGE 6,  Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_7_BANK1      ((uint32_t)0x08003800) /* Base @ of PAGE 7,  Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_8_BANK1      ((uint32_t)0x08004000) /* Base @ of PAGE 8,  Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_9_BANK1      ((uint32_t)0x08004800) /* Base @ of PAGE 9,  Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_10_BANK1     ((uint32_t)0x08005000) /* Base @ of PAGE 10, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_11_BANK1     ((uint32_t)0x08005800) /* Base @ of PAGE 11, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_12_BANK1     ((uint32_t)0x08006000) /* Base @ of PAGE 12, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_13_BANK1     ((uint32_t)0x08006800) /* Base @ of PAGE 13, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_14_BANK1     ((uint32_t)0x08007000) /* Base @ of PAGE 14, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_15_BANK1     ((uint32_t)0x08007800) /* Base @ of PAGE 15, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_16_BANK1     ((uint32_t)0x08008000) /* Base @ of PAGE 16, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_17_BANK1     ((uint32_t)0x08008800) /* Base @ of PAGE 17, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_18_BANK1     ((uint32_t)0x08009000) /* Base @ of PAGE 18, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_19_BANK1     ((uint32_t)0x08009800) /* Base @ of PAGE 19, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_20_BANK1     ((uint32_t)0x0800A000) /* Base @ of PAGE 20, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_21_BANK1     ((uint32_t)0x0800A800) /* Base @ of PAGE 21, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_22_BANK1     ((uint32_t)0x0800B000) /* Base @ of PAGE 22, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_23_BANK1     ((uint32_t)0x0800B800) /* Base @ of PAGE 23, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_24_BANK1     ((uint32_t)0x0800C000) /* Base @ of PAGE 24, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_25_BANK1     ((uint32_t)0x0800C800) /* Base @ of PAGE 25, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_26_BANK1     ((uint32_t)0x0800D000) /* Base @ of PAGE 26, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_27_BANK1     ((uint32_t)0x0800D800) /* Base @ of PAGE 27, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_28_BANK1     ((uint32_t)0x0800E000) /* Base @ of PAGE 28, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_29_BANK1     ((uint32_t)0x0800E800) /* Base @ of PAGE 29, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_30_BANK1     ((uint32_t)0x0800F000) /* Base @ of PAGE 30, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_31_BANK1     ((uint32_t)0x0800F800) /* Base @ of PAGE 31, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_32_BANK1     ((uint32_t)0x08010000) /* Base @ of PAGE 32, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_33_BANK1     ((uint32_t)0x08010800) /* Base @ of PAGE 32, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_34_BANK1     ((uint32_t)0x08011000) /* Base @ of PAGE 33, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_35_BANK1     ((uint32_t)0x08011800) /* Base @ of PAGE 34, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_36_BANK1     ((uint32_t)0x08012000) /* Base @ of PAGE 35, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_37_BANK1     ((uint32_t)0x08012800) /* Base @ of PAGE 36, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_38_BANK1     ((uint32_t)0x08013000) /* Base @ of PAGE 37, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_39_BANK1     ((uint32_t)0x08013800) /* Base @ of PAGE 38, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_40_BANK1     ((uint32_t)0x08014000) /* Base @ of PAGE 39, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_41_BANK1     ((uint32_t)0x08014800) /* Base @ of PAGE 40, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_42_BANK1     ((uint32_t)0x08015000) /* Base @ of PAGE 41, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_43_BANK1     ((uint32_t)0x08015800) /* Base @ of PAGE 42, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_44_BANK1     ((uint32_t)0x08016000) /* Base @ of PAGE 43, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_45_BANK1     ((uint32_t)0x08016800) /* Base @ of PAGE 44, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_46_BANK1     ((uint32_t)0x08017000) /* Base @ of PAGE 45, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_47_BANK1     ((uint32_t)0x08017800) /* Base @ of PAGE 46, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_48_BANK1     ((uint32_t)0x08018000) /* Base @ of PAGE 47, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_49_BANK1     ((uint32_t)0x08018800) /* Base @ of PAGE 48, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_50_BANK1     ((uint32_t)0x08019000) /* Base @ of PAGE 49, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_51_BANK1     ((uint32_t)0x08019800) /* Base @ of PAGE 50, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_52_BANK1     ((uint32_t)0x0801A000) /* Base @ of PAGE 51, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_53_BANK1     ((uint32_t)0x0801A800) /* Base @ of PAGE 52, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_54_BANK1     ((uint32_t)0x0801B000) /* Base @ of PAGE 53, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_55_BANK1     ((uint32_t)0x0801B800) /* Base @ of PAGE 54, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_56_BANK1     ((uint32_t)0x0801C000) /* Base @ of PAGE 55, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_57_BANK1     ((uint32_t)0x0801C800) /* Base @ of PAGE 56, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_58_BANK1     ((uint32_t)0x0801D000) /* Base @ of PAGE 57, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_59_BANK1     ((uint32_t)0x0801D800) /* Base @ of PAGE 58, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_60_BANK1     ((uint32_t)0x0801E000) /* Base @ of PAGE 59, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_61_BANK1     ((uint32_t)0x0801E800) /* Base @ of PAGE 60, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_62_BANK1     ((uint32_t)0x0801F000) /* Base @ of PAGE 61, Bank1, 2  Kbytes */
#define ADDR_FLASH_SECTOR_63_BANK1     ((uint32_t)0x0801F800) /* Base @ of PAGE 62, Bank1, 2  Kbytes */


#if 0
#define ADDR_FLASH_SECTOR_0_BANK2     ((uint32_t)0x08100000) /* Base @ of Sector 0, Bank2, 128 Kbyte */
#define ADDR_FLASH_SECTOR_1_BANK2     ((uint32_t)0x08120000) /* Base @ of Sector 1, Bank2, 128 Kbyte */
#define ADDR_FLASH_SECTOR_2_BANK2     ((uint32_t)0x08140000) /* Base @ of Sector 2, Bank2, 128 Kbyte */
#define ADDR_FLASH_SECTOR_3_BANK2     ((uint32_t)0x08160000) /* Base @ of Sector 3, Bank2, 128 Kbyte */
#define ADDR_FLASH_SECTOR_4_BANK2     ((uint32_t)0x08180000) /* Base @ of Sector 4, Bank2, 128 Kbyte */
#define ADDR_FLASH_SECTOR_5_BANK2     ((uint32_t)0x081A0000) /* Base @ of Sector 5, Bank2, 128 Kbyte */
#define ADDR_FLASH_SECTOR_6_BANK2     ((uint32_t)0x081C0000) /* Base @ of Sector 6, Bank2, 128 Kbyte */
#define ADDR_FLASH_SECTOR_7_BANK2     ((uint32_t)0x081E0000) /* Base @ of Sector 7, Bank2, 128 Kbyte */
#endif

/* Error code */
enum 
{
  FLASHIF_OK = 0,
  FLASHIF_ERASEKO,
  FLASHIF_WRITINGCTRL_ERROR,
  FLASHIF_WRITING_ERROR
};
  
enum
{
  FLASHIF_PROTECTION_NONE         = 0,
  FLASHIF_PROTECTION_PCROPENABLED = 0x1,
  FLASHIF_PROTECTION_WRPENABLED   = 0x2,
  FLASHIF_PROTECTION_RDPENABLED   = 0x4,
};

enum
{
  FLASH_PAGE_0 = 0,
  FLASH_PAGE_1,
  FLASH_PAGE_2,
  FLASH_PAGE_3,
  FLASH_PAGE_4,
  FLASH_PAGE_5,
  FLASH_PAGE_6,
  FLASH_PAGE_7,
  FLASH_PAGE_8,
  FLASH_PAGE_9,
  FLASH_PAGE_10,
  FLASH_PAGE_11,
  FLASH_PAGE_12,
  FLASH_PAGE_13,
  FLASH_PAGE_14,
  FLASH_PAGE_15,
  FLASH_PAGE_16,
  FLASH_PAGE_17,
  FLASH_PAGE_18,
  FLASH_PAGE_19,
  FLASH_PAGE_20,
  FLASH_PAGE_21,
  FLASH_PAGE_22,
  FLASH_PAGE_23,
  FLASH_PAGE_24,
  FLASH_PAGE_25,
  FLASH_PAGE_26,
  FLASH_PAGE_27,
  FLASH_PAGE_28,
  FLASH_PAGE_29,
  FLASH_PAGE_30,
  FLASH_PAGE_31,
  FLASH_PAGE_32,
  FLASH_PAGE_33,
  FLASH_PAGE_34,
  FLASH_PAGE_35,
  FLASH_PAGE_36,
  FLASH_PAGE_37,
  FLASH_PAGE_38,
  FLASH_PAGE_39,
  FLASH_PAGE_40,
  FLASH_PAGE_41,
  FLASH_PAGE_42,
  FLASH_PAGE_43,
  FLASH_PAGE_44,
  FLASH_PAGE_45,
  FLASH_PAGE_46,
  FLASH_PAGE_47,
  FLASH_PAGE_48,
  FLASH_PAGE_49,
  FLASH_PAGE_50,
  FLASH_PAGE_51,
  FLASH_PAGE_52,
  FLASH_PAGE_53,
  FLASH_PAGE_54,
  FLASH_PAGE_55,
  FLASH_PAGE_56,
  FLASH_PAGE_57,
  FLASH_PAGE_58,
  FLASH_PAGE_59,
  FLASH_PAGE_60,
  FLASH_PAGE_61,
  FLASH_PAGE_62,
  FLASH_PAGE_63
};




#define FLASH_RANGE_START         ADDR_FLASH_SECTOR_0_BANK1
#define FLASH_RANGE_END           APPLICATION_ADDRESS_M4_END
#define ADDR_INTERNAL_SRAM_START  0x20000000
#define ADDR_INTERNAL_SRAM_END    0x20023FFF


/* End of the Flash address */
#define USER_FLASH_END_ADDRESS        APPLICATION_ADDRESS_M4_END
/* Define the user application size */
#define USER_FLASH_SIZE   (USER_FLASH_END_ADDRESS - APPLICATION_ADDRESS + 1)

#define FLASH_BASE_MAIN_APP         0x08011000

/* Define the address from where user application will be loaded.*/
#define APPLICATION_ADDRESS         (uint32_t)FLASH_BASE_MAIN_APP
#define APPLICATION_ADDRESS_M4      (uint32_t)ADDR_FLASH_SECTOR_0_BANK1
#define APPLICATION_ADDRESS_M4_END  (uint32_t)0x0801FFFF - 1
#define APPLICATION_ADDRESS_M4_SIZE (uint32_t)(APPLICATION_ADDRESS_M4_END - APPLICATION_ADDRESS_M4 + 1)

// external sdram
#define APPLICATION_BUFADDRESS      (uint32_t)0x24002000
#define APPLICATION_BUFADDRESS_END  (uint32_t)0x2407FFFF
#define APPLICATION_BUFADDRESS_SIZE (uint32_t)(APPLICATION_BUFADDRESS_END - APPLICATION_BUFADDRESS + 1)

#define APPLICATION_BUFADDRESS2      (uint32_t)0x30000000
#define APPLICATION_BUFADDRESS2_END  (uint32_t)0x30047FFF
#define APPLICATION_BUFADDRESS2_SIZE (uint32_t)(APPLICATION_BUFADDRESS2_END - APPLICATION_BUFADDRESS2 + 1)


/* Define bitmap representing user flash area that could be write protected (check restricted to pages 8-39). */
#if LEGACY_M4
#define FLASH_SECTOR_TO_BE_PROTECTED (OB_WRP_SECTOR_0 | OB_WRP_SECTOR_1 | OB_WRP_SECTOR_2 | OB_WRP_SECTOR_3 |\
                                      OB_WRP_SECTOR_4 | OB_WRP_SECTOR_5 | OB_WRP_SECTOR_6 | OB_WRP_SECTOR_7)
#else
#define FLASH_SECTOR_TO_BE_PROTECTED (OPTIONBYTE_WRP)
#endif
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void              FLASH_If_Init(void);
uint32_t          FLASH_If_Erase(uint32_t StartPage);
uint32_t          FLASH_If_Write(uint32_t destination, uint32_t *p_source, uint32_t length);
uint16_t          FLASH_If_GetWriteProtectionStatus(uint32_t ProcessAddress);
HAL_StatusTypeDef FLASH_If_WriteProtectionConfig(uint32_t modifier, uint32_t ProcessAddress);

#endif  /* __FLASH_IF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
