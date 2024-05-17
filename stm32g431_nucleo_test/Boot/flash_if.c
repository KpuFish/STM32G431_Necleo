/**
  ******************************************************************************
  * @file    IAP_Main/Src/flash_if.c 
  * @author  MCD Application Team
  * @brief   This file provides all the memory related operation functions.
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

/** @addtogroup STM32H7xx_IAP
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include "flash_if.h"
#include "common.h"
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint32_t GetPage(uint32_t Address);

/* Private functions ---------------------------------------------------------*/


typedef struct {
  uint32_t start_addr;
  uint32_t end_addr;
  uint8_t  page_number;
} flash_map_t;
const static flash_map_t flash_map[] =
{
  { ADDR_FLASH_SECTOR_0_BANK1 , ADDR_FLASH_SECTOR_0_BANK1  - 1, FLASH_PAGE_0  },
  { ADDR_FLASH_SECTOR_1_BANK1 , ADDR_FLASH_SECTOR_1_BANK1  - 1, FLASH_PAGE_1  },
  { ADDR_FLASH_SECTOR_2_BANK1 , ADDR_FLASH_SECTOR_2_BANK1  - 1, FLASH_PAGE_2  },
  { ADDR_FLASH_SECTOR_3_BANK1 , ADDR_FLASH_SECTOR_3_BANK1  - 1, FLASH_PAGE_3  },
  { ADDR_FLASH_SECTOR_4_BANK1 , ADDR_FLASH_SECTOR_4_BANK1  - 1, FLASH_PAGE_4  },
  { ADDR_FLASH_SECTOR_5_BANK1 , ADDR_FLASH_SECTOR_5_BANK1  - 1, FLASH_PAGE_5  },
  { ADDR_FLASH_SECTOR_6_BANK1 , ADDR_FLASH_SECTOR_6_BANK1  - 1, FLASH_PAGE_6  },
  { ADDR_FLASH_SECTOR_7_BANK1 , ADDR_FLASH_SECTOR_7_BANK1  - 1, FLASH_PAGE_7  },
  { ADDR_FLASH_SECTOR_8_BANK1 , ADDR_FLASH_SECTOR_8_BANK1  - 1, FLASH_PAGE_8  },
  { ADDR_FLASH_SECTOR_9_BANK1 , ADDR_FLASH_SECTOR_9_BANK1  - 1, FLASH_PAGE_9  },
  { ADDR_FLASH_SECTOR_10_BANK1, ADDR_FLASH_SECTOR_10_BANK1 - 1, FLASH_PAGE_10 },
  { ADDR_FLASH_SECTOR_11_BANK1, ADDR_FLASH_SECTOR_11_BANK1 - 1, FLASH_PAGE_11 },
  { ADDR_FLASH_SECTOR_12_BANK1, ADDR_FLASH_SECTOR_12_BANK1 - 1, FLASH_PAGE_12 },
  { ADDR_FLASH_SECTOR_13_BANK1, ADDR_FLASH_SECTOR_13_BANK1 - 1, FLASH_PAGE_13 },
  { ADDR_FLASH_SECTOR_14_BANK1, ADDR_FLASH_SECTOR_14_BANK1 - 1, FLASH_PAGE_14 },
  { ADDR_FLASH_SECTOR_15_BANK1, ADDR_FLASH_SECTOR_15_BANK1 - 1, FLASH_PAGE_15 },
  { ADDR_FLASH_SECTOR_16_BANK1, ADDR_FLASH_SECTOR_16_BANK1 - 1, FLASH_PAGE_16 },
  { ADDR_FLASH_SECTOR_17_BANK1, ADDR_FLASH_SECTOR_17_BANK1 - 1, FLASH_PAGE_17 },
  { ADDR_FLASH_SECTOR_18_BANK1, ADDR_FLASH_SECTOR_18_BANK1 - 1, FLASH_PAGE_18 },
  { ADDR_FLASH_SECTOR_19_BANK1, ADDR_FLASH_SECTOR_19_BANK1 - 1, FLASH_PAGE_19 },
  { ADDR_FLASH_SECTOR_20_BANK1, ADDR_FLASH_SECTOR_20_BANK1 - 1, FLASH_PAGE_20 },
  { ADDR_FLASH_SECTOR_21_BANK1, ADDR_FLASH_SECTOR_21_BANK1 - 1, FLASH_PAGE_21 },
  { ADDR_FLASH_SECTOR_22_BANK1, ADDR_FLASH_SECTOR_22_BANK1 - 1, FLASH_PAGE_22 },
  { ADDR_FLASH_SECTOR_23_BANK1, ADDR_FLASH_SECTOR_23_BANK1 - 1, FLASH_PAGE_23 },
  { ADDR_FLASH_SECTOR_24_BANK1, ADDR_FLASH_SECTOR_24_BANK1 - 1, FLASH_PAGE_24 },
  { ADDR_FLASH_SECTOR_25_BANK1, ADDR_FLASH_SECTOR_25_BANK1 - 1, FLASH_PAGE_25 },
  { ADDR_FLASH_SECTOR_26_BANK1, ADDR_FLASH_SECTOR_26_BANK1 - 1, FLASH_PAGE_26 },
  { ADDR_FLASH_SECTOR_27_BANK1, ADDR_FLASH_SECTOR_27_BANK1 - 1, FLASH_PAGE_27 },
  { ADDR_FLASH_SECTOR_28_BANK1, ADDR_FLASH_SECTOR_28_BANK1 - 1, FLASH_PAGE_28 },
  { ADDR_FLASH_SECTOR_29_BANK1, ADDR_FLASH_SECTOR_29_BANK1 - 1, FLASH_PAGE_29 },
  { ADDR_FLASH_SECTOR_30_BANK1, ADDR_FLASH_SECTOR_30_BANK1 - 1, FLASH_PAGE_30 },
  { ADDR_FLASH_SECTOR_31_BANK1, ADDR_FLASH_SECTOR_31_BANK1 - 1, FLASH_PAGE_31 },
  { ADDR_FLASH_SECTOR_32_BANK1, ADDR_FLASH_SECTOR_32_BANK1 - 1, FLASH_PAGE_32 },
  { ADDR_FLASH_SECTOR_33_BANK1, ADDR_FLASH_SECTOR_33_BANK1 - 1, FLASH_PAGE_33 },
  { ADDR_FLASH_SECTOR_34_BANK1, ADDR_FLASH_SECTOR_34_BANK1 - 1, FLASH_PAGE_34 },
  { ADDR_FLASH_SECTOR_35_BANK1, ADDR_FLASH_SECTOR_35_BANK1 - 1, FLASH_PAGE_35 },
  { ADDR_FLASH_SECTOR_36_BANK1, ADDR_FLASH_SECTOR_36_BANK1 - 1, FLASH_PAGE_36 },
  { ADDR_FLASH_SECTOR_37_BANK1, ADDR_FLASH_SECTOR_37_BANK1 - 1, FLASH_PAGE_37 },
  { ADDR_FLASH_SECTOR_38_BANK1, ADDR_FLASH_SECTOR_38_BANK1 - 1, FLASH_PAGE_38 },
  { ADDR_FLASH_SECTOR_39_BANK1, ADDR_FLASH_SECTOR_39_BANK1 - 1, FLASH_PAGE_39 },
  { ADDR_FLASH_SECTOR_40_BANK1, ADDR_FLASH_SECTOR_40_BANK1 - 1, FLASH_PAGE_40 },
  { ADDR_FLASH_SECTOR_41_BANK1, ADDR_FLASH_SECTOR_41_BANK1 - 1, FLASH_PAGE_41 },
  { ADDR_FLASH_SECTOR_42_BANK1, ADDR_FLASH_SECTOR_42_BANK1 - 1, FLASH_PAGE_42 },
  { ADDR_FLASH_SECTOR_43_BANK1, ADDR_FLASH_SECTOR_43_BANK1 - 1, FLASH_PAGE_43 },
  { ADDR_FLASH_SECTOR_44_BANK1, ADDR_FLASH_SECTOR_44_BANK1 - 1, FLASH_PAGE_44 },
  { ADDR_FLASH_SECTOR_45_BANK1, ADDR_FLASH_SECTOR_45_BANK1 - 1, FLASH_PAGE_45 },
  { ADDR_FLASH_SECTOR_46_BANK1, ADDR_FLASH_SECTOR_46_BANK1 - 1, FLASH_PAGE_46 },
  { ADDR_FLASH_SECTOR_47_BANK1, ADDR_FLASH_SECTOR_47_BANK1 - 1, FLASH_PAGE_47 },
  { ADDR_FLASH_SECTOR_48_BANK1, ADDR_FLASH_SECTOR_48_BANK1 - 1, FLASH_PAGE_48 },
  { ADDR_FLASH_SECTOR_49_BANK1, ADDR_FLASH_SECTOR_49_BANK1 - 1, FLASH_PAGE_49 },
  { ADDR_FLASH_SECTOR_50_BANK1, ADDR_FLASH_SECTOR_50_BANK1 - 1, FLASH_PAGE_50 },
  { ADDR_FLASH_SECTOR_51_BANK1, ADDR_FLASH_SECTOR_51_BANK1 - 1, FLASH_PAGE_51 },
  { ADDR_FLASH_SECTOR_52_BANK1, ADDR_FLASH_SECTOR_52_BANK1 - 1, FLASH_PAGE_52 },
  { ADDR_FLASH_SECTOR_53_BANK1, ADDR_FLASH_SECTOR_53_BANK1 - 1, FLASH_PAGE_53 },
  { ADDR_FLASH_SECTOR_54_BANK1, ADDR_FLASH_SECTOR_54_BANK1 - 1, FLASH_PAGE_54 },
  { ADDR_FLASH_SECTOR_55_BANK1, ADDR_FLASH_SECTOR_55_BANK1 - 1, FLASH_PAGE_55 },
  { ADDR_FLASH_SECTOR_56_BANK1, ADDR_FLASH_SECTOR_56_BANK1 - 1, FLASH_PAGE_56 },
  { ADDR_FLASH_SECTOR_57_BANK1, ADDR_FLASH_SECTOR_57_BANK1 - 1, FLASH_PAGE_57 },
  { ADDR_FLASH_SECTOR_58_BANK1, ADDR_FLASH_SECTOR_58_BANK1 - 1, FLASH_PAGE_58 },
  { ADDR_FLASH_SECTOR_59_BANK1, ADDR_FLASH_SECTOR_59_BANK1 - 1, FLASH_PAGE_59 },
  { ADDR_FLASH_SECTOR_60_BANK1, ADDR_FLASH_SECTOR_60_BANK1 - 1, FLASH_PAGE_60 },
  { ADDR_FLASH_SECTOR_61_BANK1, ADDR_FLASH_SECTOR_61_BANK1 - 1, FLASH_PAGE_61 },
  { ADDR_FLASH_SECTOR_62_BANK1, ADDR_FLASH_SECTOR_62_BANK1 - 1, FLASH_PAGE_62 },
  { ADDR_FLASH_SECTOR_63_BANK1, ADDR_FLASH_SECTOR_63_BANK1 - 1, FLASH_PAGE_63 }
};

/**
  * @brief  Unlocks Flash for write access
  * @param  None
  * @retval None
  */
void FLASH_If_Init(void)
{
    /* Clear all FLASH flags */
  __HAL_FLASH_CLEAR_FLAG( FLASH_FLAG_EOP     | FLASH_FLAG_OPERR   |
                          FLASH_FLAG_PGSERR  | FLASH_FLAG_PROGERR |
                          FLASH_FLAG_WRPERR  | FLASH_FLAG_PGAERR  |
                          FLASH_FLAG_SIZERR  | FLASH_FLAG_MISERR  |
                          FLASH_FLAG_FASTERR);// | FLASH_FLAG_OPTVERR );
}

/**
  * @brief  This function does an erase of all user flash area
  * @param  StartSector: start of user flash area
  * @retval 0: user flash area successfully erased
  *         1: error occurred
  */
uint32_t FLASH_If_Erase(uint32_t StartPage)
{
  uint32_t UserStartPage;
  uint32_t PageErr;
  FLASH_EraseInitTypeDef pEraseInit;

  if (StartPage > APPLICATION_ADDRESS_M4_END) {
    return FALSE;
  }
  
  /* Unlock the Flash to enable the flash control register access *************/ 
  HAL_FLASH_Unlock(); 
  FLASH_If_Init();
  
  /* Get the sector where start the user flash area */
  UserStartPage           = GetPage(StartPage);
  pEraseInit.TypeErase    = FLASH_TYPEERASE_PAGES;
  pEraseInit.Page         = UserStartPage;
  pEraseInit.NbPages      = FLASH_PAGE_63 - UserStartPage;
  pEraseInit.Banks        = FLASH_BANK_1;
#if M4_LEGACY
  pEraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;
#endif

  if (HAL_FLASHEx_Erase(&pEraseInit, &PageErr) != HAL_OK) {
    HAL_FLASH_Lock();
    /* Error occurred while sector erase */
    return FALSE;
  }
  HAL_FLASH_Lock();

#if 0 // DBG
  printf("Page Number %d Target Address 0x%08lx\r\n", pEraseInit.Page, (uint32_t)StartPage);
#endif
  return TRUE;
}

/**
  * @brief  This function writes a data buffer in flash (data are 32-bit aligned).
  * @note   After writing data buffer, the flash content is checked.
  * @param  FlashAddress: start address for writing data buffer
  * @param  Data: pointer on data buffer
  * @param  DataLength: length of data buffer (unit is 32-bit word)   
  * @retval 0: Data successfully written to Flash memory
  *         1: Error occurred while writing data in Flash memory
  *         2: Written Data in flash memory is different from expected one
  */
uint32_t FLASH_If_Write(uint32_t FlashAddress, uint32_t* Data ,uint32_t DataLength)
{
  uint32_t i = 0;
 /* Unlock the Flash to enable the flash control register access *************/ 
  HAL_FLASH_Unlock();

  for (i = 0; (i < DataLength) && (FlashAddress <= (USER_FLASH_END_ADDRESS-32)); i+=8)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */ 
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, FlashAddress, ((uint32_t)(Data+i))) == HAL_OK)
    {
     /* Check the written value */
      if (*(uint32_t*)FlashAddress != *(uint32_t*)(Data+i))
      {
        /* Flash content doesn't match SRAM content */
        return(FLASHIF_WRITINGCTRL_ERROR);
      }
      /* Increment FLASH destination address */
      FlashAddress += 32;
    }
    else
    {
      /* Error occurred while writing data in Flash memory */
      return (FLASHIF_WRITING_ERROR);
    }
  }

  HAL_FLASH_Lock();

  return (FLASHIF_OK);
}

/**
  * @brief  Returns the write protection status of user flash area.
  * @param  None
  * @retval 0: No write protected sectors inside the user flash area
  *         1: Some sectors inside the user flash area are write protected
  */
uint16_t FLASH_If_GetWriteProtectionStatus(uint32_t ProcessAddress)
{
  FLASH_OBProgramInitTypeDef OptionsBytesStruct;

  #if LEGACY
  uint32_t ProtectedSECTOR = 0x0;
  if (ProcessAddress < APPLICATION_ADDRESS_M4_END)
  {
    /* Select Bank1 */
    OptionsBytesStruct.Banks = 1;//FLASH_BANK_1;
    
    /* Check if there are write protected sectors inside the user flash area ****/
    HAL_FLASHEx_OBGetConfig(&OptionsBytesStruct);
  
    /* Get pages already write protected ****************************************/
    ProtectedSECTOR = OptionsBytesStruct.OptionType & FLASH_SECTOR_TO_BE_PROTECTED;
  }
  else
  { 
  /* Select Bank2*/
  OptionsBytesStruct.Banks = 2;//FLASH_BANK_2;
  
  /* Check if there are write protected sectors inside the user flash area ****/
  HAL_FLASHEx_OBGetConfig(&OptionsBytesStruct);

  /* Get pages already write protected ****************************************/
  ProtectedSECTOR |= OptionsBytesStruct.OptionType & FLASH_SECTOR_TO_BE_PROTECTED;
  }
  /* Check if desired pages are already write protected ***********************/
  if(ProtectedSECTOR != 0)
  {
    /* Some sectors inside the user flash area are write protected */
    return FLASHIF_PROTECTION_WRPENABLED;
  }
  else
  { 
    /* No write protected sectors inside the user flash area */
    return FLASHIF_PROTECTION_NONE;
  }
  #else
  uint32_t ProtectedPAGE = FLASHIF_PROTECTION_NONE;
  /* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();

  /* Check if there are write protected sectors inside the user flash area ****/
  HAL_FLASHEx_OBGetConfig(&OptionsBytesStruct);

  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  HAL_FLASH_Lock();

  /* Get pages already write protected ****************************************/
  ProtectedPAGE = (OptionsBytesStruct.OptionType & OPTIONBYTE_WRP);

  /* Check if desired pages are already write protected ***********************/
  if(ProtectedPAGE != 0)
  {
    /* Some sectors inside the user flash area are write protected */
    return FLASHIF_PROTECTION_WRPENABLED;
  }
  else
  {
    /* No write protected sectors inside the user flash area */
    return FLASHIF_PROTECTION_NONE;
  }
  #endif
}

/**
  * @brief  Gets the page of a given address
  * @param  Address: Flash address
  * @retval The page of a given address
  */
static uint32_t GetPage(uint32_t Address)
{
  uint32_t page = FLASH_PAGE_0;
  
  for (uint8_t cnt = FLASH_PAGE_0; cnt <= FLASH_PAGE_63; cnt++) {
    if (flash_map[cnt].start_addr >= Address && 
        flash_map[cnt].end_addr   <  Address) {
        page = cnt;
        break;
    }
  }
  return page;
}

/**
  * @brief  Configure the write protection status of user flash area.
  * @param  modifier DISABLE or ENABLE the protection
  * @retval HAL_StatusTypeDef HAL_OK if change is applied.
  */
HAL_StatusTypeDef FLASH_If_WriteProtectionConfig(uint32_t modifier, uint32_t ProcessAddress)
{
   FLASH_OBProgramInitTypeDef config_old;
  
   #if LEGACY_M4
   FLASH_OBProgramInitTypeDef config_new;
  uint32_t ProtectedSECTOR = 0xFFF;
  HAL_StatusTypeDef result = HAL_OK;
  /* Unlock the Flash to enable the flash control register access *************/ 
  HAL_FLASH_Unlock();
  
  /* Unlock the Options Bytes *************************************************/
  HAL_FLASH_OB_Unlock();
  if (ProcessAddress < APPLICATION_ADDRESS_M4_END)
  {
    /* Select Bank1 */
    config_old.Banks = FLASH_BANK_1;
    config_new.Banks = FLASH_BANK_1;
    
    /* Get pages write protection status ****************************************/
    HAL_FLASHEx_OBGetConfig(&config_old);
    
    /* The parameter says whether we turn the protection on or off */
    config_new.WRPState = modifier;
    
    /* We want to modify only the Write protection */
    config_new.OptionType = OPTIONBYTE_WRP;
    
    /* No read protection, keep BOR and reset settings */
    config_new.RDPLevel = OB_RDP_LEVEL_0;
    config_new.USERConfig = config_old.USERConfig;  
    /* Get pages already write protected ****************************************/
    ProtectedSECTOR = config_old.OptionType | FLASH_SECTOR_TO_BE_PROTECTED;
    
    config_new.WRPSector    = ProtectedSECTOR;
    result = HAL_FLASHEx_OBProgram(&config_new);
    
  }
  else
  {  
    /* Select Bank2 */
    config_old.Banks = 2;//FLASH_BANK_2;
    config_new.Banks = 2;//FLASH_BANK_2;
    
    /* Get pages write protection status ****************************************/
    HAL_FLASHEx_OBGetConfig(&config_old);
    
    /* The parameter says whether we turn the protection on or off */
    config_new.WRPState = modifier;
    
    /* We want to modify only the Write protection */
    config_new.OptionType = OPTIONBYTE_WRP;
    
    /* No read protection, keep BOR and reset settings */
    config_new.RDPLevel = OB_RDP_LEVEL_0;
    config_new.USERConfig = config_old.USERConfig;  
    /* Get pages already write protected ****************************************/
    ProtectedSECTOR = config_old.OptionType | FLASH_SECTOR_TO_BE_PROTECTED;
    config_new.OptionType = ProtectedSECTOR;
    result = HAL_FLASHEx_OBProgram(&config_new);
    
  }
   /* Launch the option byte loading */
  HAL_FLASH_OB_Launch();
  
  HAL_FLASH_OB_Lock();
  
  HAL_FLASH_Lock();
  
  return result;
  #else
  HAL_FLASHEx_OBGetConfig(&config_old);
  return FLASHIF_OK;
  #endif
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
