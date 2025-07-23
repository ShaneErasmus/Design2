/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_storage_if.c
  * @version        : v2.0_Cube
  * @brief          : Memory management layer.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_storage_if.h"

/* USER CODE BEGIN INCLUDE */
#include "ff.h"
#include "main.h"  // For accessing globals
/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
// Flash write operation pending flag - to be checked in main loop
volatile uint8_t flash_write_pending = 0;
volatile uint32_t flash_pending_blk_addr = 0;
volatile uint16_t flash_pending_blk_len = 0;
/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @defgroup USBD_STORAGE
  * @brief Usb mass storage device module
  * @{
  */

/** @defgroup USBD_STORAGE_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Defines
  * @brief Private defines.
  * @{
  */

#define STORAGE_LUN_NBR                  1
#define STORAGE_BLK_NBR                  0x10000
#define STORAGE_BLK_SIZ                  0x200

/* USER CODE BEGIN PRIVATE_DEFINES */

#define USE_RAM
// #define USE_FLASH
#define STORAGE_LUN_NBR                  1
#define STORAGE_BLK_NBR                  70*2  // enter twice the size of the Memory that you want to use
#define STORAGE_BLK_SIZ                  0x200

#define FLASH_PAGE_SIZE 0x800 // 2KB
#define ADDR_FLASH_PAGE_128 (0x08000000 + 128 * FLASH_PAGE_SIZE)
#define ADDR_FLASH_PAGE_255 (0x08000000 + 255 * FLASH_PAGE_SIZE)
#define FLASH_USER_START_ADDR   ADDR_FLASH_PAGE_128
#define FLASH_USER_END_ADDR     (ADDR_FLASH_PAGE_255 + FLASH_PAGE_SIZE - 1)
#define FLASH_ROW_SIZE          32 // 32 doublewords (256 bytes per row)

#define USB_FLASH_START_ADDRESS   0x08040000   
#define TOTAL_USB_DEVICE_SIZE   ( STORAGE_BLK_NBR * STORAGE_BLK_SIZ )

#ifdef USE_RAM
uint8_t USB_storage_buffer[STORAGE_BLK_NBR*STORAGE_BLK_SIZ];
#endif
#ifdef USE_FLASH
uint8_t USB_storage_buffer[2048];
#endif
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Variables
  * @brief Private variables.
  * @{
  */

/* USER CODE BEGIN INQUIRY_DATA_FS */
/** USB Mass storage Standard Inquiry Data. */
const int8_t STORAGE_Inquirydata_FS[] = {/* 36 */

  /* LUN 0 */
  0x00,
  0x80,
  0x02,
  0x02,
  (STANDARD_INQUIRY_DATA_LEN - 5),
  0x00,
  0x00,
  0x00,
  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
  'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', /* Product      : 16 Bytes */
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  '0', '.', '0' ,'1'                      /* Version      : 4 Bytes */
};
/* USER CODE END INQUIRY_DATA_FS */

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t STORAGE_Init_FS(uint8_t lun);
static int8_t STORAGE_GetCapacity_FS(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
static int8_t STORAGE_IsReady_FS(uint8_t lun);
static int8_t STORAGE_IsWriteProtected_FS(uint8_t lun);
static int8_t STORAGE_Read_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t STORAGE_Write_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t STORAGE_GetMaxLun_FS(void);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */
#include <stdbool.h>
#include "stm32l4xx_hal_flash.h"
#include "stm32l4xx_hal_flash_ex.h"

#ifdef USE_FLASH
/**
  * @brief  Variables for flash storage
  */
static uint16_t data_offset = 0;
static uint8_t flash_backup_buffer[2048];  // Buffer to hold existing flash data

/**
  * @brief  Writes data buffer to flash memory
  * @param  blk_addr: USB block address to write
  * @param  blk_len: Number of blocks to write
  * @retval HAL status
  */
static HAL_StatusTypeDef write_data_to_flash(uint32_t blk_addr, uint16_t blk_len)
{
  HAL_StatusTypeDef ret = HAL_OK;
  
  // Calculate which page this block belongs to (4 blocks per 2KB page)
  uint32_t target_page = blk_addr / 4;
  
  // Calculate flash address for this page
  uint32_t page_addr = USB_FLASH_START_ADDRESS + (target_page * FLASH_PAGE_SIZE);
  
  // Ensure page_addr is within user area
  if (page_addr < FLASH_USER_START_ADDR || page_addr > FLASH_USER_END_ADDR) {
    return HAL_ERROR;
  }
  
  // Read existing page content into backup buffer
  memcpy(flash_backup_buffer, (const void*)page_addr, FLASH_PAGE_SIZE);

  // Calculate the start offset within the page
  uint32_t start_offset = (blk_addr % 4) * STORAGE_BLK_SIZ;
  uint32_t end_offset = start_offset + (blk_len * STORAGE_BLK_SIZ);
  
  // Preserve any existing data in the page that we're not updating
  for (uint32_t i = 0; i < FLASH_PAGE_SIZE; i++) {
    if (i < start_offset || i >= end_offset) {
      USB_storage_buffer[i] = flash_backup_buffer[i];
    }
  }
  
  // Page number is relative to the bank (Bank 2, page numbers start at 128)
  uint32_t page_num = 128 + ((page_addr - USB_FLASH_START_ADDRESS) / FLASH_PAGE_SIZE);
  
  // Check if block address crosses a page boundary
  uint32_t current_block_page = target_page;
  uint32_t end_block_page = (blk_addr + blk_len - 1) / 4;
  
  // Erase and program the flash page
  FLASH_EraseInitTypeDef EraseInitStruct;
  uint32_t SectorError = 0;
  
  HAL_FLASH_Unlock();
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);
  
  // Set up erase parameters
  EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.Banks = FLASH_BANK_2;
  EraseInitStruct.Page = page_num;
  EraseInitStruct.NbPages = 1;
  
  // Erase the page
  ret = HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError);
  if (SectorError != 0xFFFFFFFF && ret != HAL_OK) {
    HAL_FLASH_Lock();
    return HAL_ERROR;
  }

  // Write 2KB page as 256 consecutive 64-bit doublewords
  for (uint32_t i = 0; i < 256; i++) {
    // Get the current address to write to
    uint32_t current_addr = page_addr + (i * 8);
    
    // Check if the memory is fully erased (should be all 0xFF after erase)
    uint64_t *flash_ptr = (uint64_t*)current_addr;
    uint64_t current_value = *flash_ptr;
    
    // If memory is not properly erased, we need to re-erase
    if (current_value != 0xFFFFFFFFFFFFFFFFULL) {
      HAL_FLASH_Lock();
      
      // Log the error or take other action as needed
      // Attempt to erase again
      HAL_FLASH_Unlock();
      __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY);
      ret = HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError);
      if (ret != HAL_OK) {
        HAL_FLASH_Lock();
        data_offset = 0;
        return HAL_ERROR;
      }
      
      // Start the write loop again from the beginning
      i = 0;
      continue;
    }
    
    // Prepare the data and program the flash
    uint64_t dword;
    memcpy(&dword, &USB_storage_buffer[i * 8], 8);
    ret = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, current_addr, dword);
    if (ret != HAL_OK) {
      HAL_FLASH_Lock();
      data_offset = 0;
      return HAL_ERROR;
    }
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY);
  }
  HAL_FLASH_Lock();
  
  // If we crossed a page boundary, prepare for the next page
  if (current_block_page != end_block_page) {
    // Calculate the next block address to start from
    uint32_t next_page_start_blk = (target_page + 1) * 4;
    uint32_t blocks_written = next_page_start_blk - blk_addr;
    uint32_t remaining_blocks = blk_len - blocks_written;
    
    if (remaining_blocks > 0) {
      // Call recursively to handle the next page
      return write_data_to_flash(next_page_start_blk, remaining_blocks);
    }
  }
  
  // Reset buffer offset
  data_offset = 0;
  
  return ret;
}
#endif
/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

USBD_StorageTypeDef USBD_Storage_Interface_fops_FS =
{
  STORAGE_Init_FS,
  STORAGE_GetCapacity_FS,
  STORAGE_IsReady_FS,
  STORAGE_IsWriteProtected_FS,
  STORAGE_Read_FS,
  STORAGE_Write_FS,
  STORAGE_GetMaxLun_FS,
  (int8_t *)STORAGE_Inquirydata_FS
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initializes over USB FS IP
  * @param  lun:
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Init_FS(uint8_t lun)
{
  /* USER CODE BEGIN 2 */

  return (USBD_OK);
  /* USER CODE END 2 */
}

/**
  * @brief  .
  * @param  lun: .
  * @param  block_num: .
  * @param  block_size: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_GetCapacity_FS(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
  /* USER CODE BEGIN 3 */
  *block_num  = STORAGE_BLK_NBR;
  *block_size = STORAGE_BLK_SIZ;
  return (USBD_OK);
  /* USER CODE END 3 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_IsReady_FS(uint8_t lun)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_IsWriteProtected_FS(uint8_t lun)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Read_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  /* USER CODE BEGIN 6 */
#ifdef USE_FLASH
  memcpy( buf,
          (const void *)(USB_FLASH_START_ADDRESS + ( blk_addr * STORAGE_BLK_SIZ )),
          (blk_len * STORAGE_BLK_SIZ)
        );
#endif
#ifdef USE_RAM
  memcpy(buf, &USB_storage_buffer[blk_addr*STORAGE_BLK_SIZ], blk_len*STORAGE_BLK_SIZ);
  
#endif
  
  return (USBD_OK);
  /* USER CODE END 6 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Write_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  /* USER CODE BEGIN 7 */
#ifdef USE_FLASH
  // Copy data to our buffer at current offset
  memcpy(&USB_storage_buffer[data_offset], buf, blk_len * STORAGE_BLK_SIZ);
  data_offset += blk_len * STORAGE_BLK_SIZ;
  
  // If buffer is full (2KB) or this is the last block, set flag for main loop to write to flash
  if (data_offset >= FLASH_PAGE_SIZE) {
    // Calculate the starting block address for this buffer
    uint32_t start_blk_addr = blk_addr - ((data_offset - (blk_len * STORAGE_BLK_SIZ)) / STORAGE_BLK_SIZ);
    uint16_t total_blks = data_offset / STORAGE_BLK_SIZ;
    
    // Set the flag and parameters for the main loop to handle
    flash_pending_blk_addr = start_blk_addr;
    flash_pending_blk_len = total_blks;
    flash_write_pending = 1;
  }
#endif
#ifdef USE_RAM

  memcpy(&USB_storage_buffer[blk_addr*STORAGE_BLK_SIZ], buf, blk_len*STORAGE_BLK_SIZ);

  #endif
  return (USBD_OK);
  /* USER CODE END 7 */
}

/**
  * @brief  .
  * @param  None
  * @retval .
  */
int8_t STORAGE_GetMaxLun_FS(void)
{
  /* USER CODE BEGIN 8 */
  return (STORAGE_LUN_NBR - 1);
  /* USER CODE END 8 */
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @brief  Process pending flash writes - to be called from main loop
  * @note   This function checks if there are pending flash writes and processes them
  * @retval None
  */
void USBD_STORAGE_ProcessPendingWrites(void)
{
  // Check if we have a pending flash write operation
  if (flash_write_pending) {
    // Clear the flag first to prevent reentrance issues
    flash_write_pending = 0;
    
    // Local copies of the volatile variables for safety
    uint32_t blk_addr = flash_pending_blk_addr;
    uint16_t blk_len = flash_pending_blk_len;
    
    // Process the flash write
    HAL_StatusTypeDef status = write_data_to_flash(blk_addr, blk_len);
    
    // Could add error handling here if needed
    if (status != HAL_OK) {
      // Handle error if needed
      // Maybe set an error flag or retry counter
    }
  }
}

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */

/**
  * @}
  */

