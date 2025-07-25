#ifndef PREFORMATTED_FLASH_H
#define PREFORMATTED_FLASH_H

#include <stdint.h>

#undef STORAGE_LUN_NBR
#undef STORAGE_BLK_NBR
#undef STORAGE_BLK_SIZ  

// #define USE_RAM
#define USE_FLASH
#define USB_FLASH_128KB_FILE
#define USB_FLASH_START_ADDRESS   0x08040000  


#define FLASH_PAGE_SIZE 0x800 // 2KB
#define ADDR_FLASH_PAGE_128 (0x08000000 + 128 * FLASH_PAGE_SIZE)
#define ADDR_FLASH_PAGE_255 (0x08000000 + 255 * FLASH_PAGE_SIZE)
#define FLASH_USER_START_ADDR   ADDR_FLASH_PAGE_128
#define FLASH_USER_END_ADDR     (ADDR_FLASH_PAGE_255 + FLASH_PAGE_SIZE - 1)
#define FLASH_ROW_SIZE          32 // 32 doublewords (256 bytes per row)

#define TOTAL_USB_DEVICE_SIZE   ( STORAGE_BLK_NBR * STORAGE_BLK_SIZ )

#ifdef USB_FLASH_72KB_FILE
    #define STORAGE_LUN_NBR                  1
    #define STORAGE_BLK_NBR                  72*2  // enter twice the size of the Memory that you want to use
    #define STORAGE_BLK_SIZ                  0x200
    #define USB_PREFORMATED_SIZE             72*1024
#endif

#ifdef USB_FLASH_80KB_FILE
    #define STORAGE_LUN_NBR                  1
    #define STORAGE_BLK_NBR                  80*2  // enter twice the size of the Memory that you want to use
    #define STORAGE_BLK_SIZ                  0x200
    #define USB_PREFORMATED_SIZE             80*1024
#endif

#ifdef USB_FLASH_128KB_FILE
    #define STORAGE_LUN_NBR                  1
    #define STORAGE_BLK_NBR                  128*2  // enter twice the size of the Memory that you want to use
    #define STORAGE_BLK_SIZ                  0x200
    #define USB_PREFORMATED_SIZE             128*1024
#endif

#ifdef USB_FLASH_256KB_FILE
    #define STORAGE_LUN_NBR                  1
    #define STORAGE_BLK_NBR                  256*2  // enter twice the size of the Memory that you want to use
    #define STORAGE_BLK_SIZ                  0x200
    #define USB_PREFORMATED_SIZE             256*1024
#endif

// External declaration of the preformatted data array
extern const uint8_t USB_PREFORMATED[];

// Function to get a pointer to the preformatted data
uint8_t* get_preformatted_data(void);

// Function to get the size of the preformatted data
uint32_t get_preformatted_data_size(void);

#endif /* PREFORMATTED_FLASH_H */
