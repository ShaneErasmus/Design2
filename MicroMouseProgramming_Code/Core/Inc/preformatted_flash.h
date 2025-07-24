#ifndef PREFORMATTED_FLASH_H
#define PREFORMATTED_FLASH_H

#include <stdint.h>

// Define the size of preformatted data
#define USB_PREFORMATED_SIZE 71680

// External declaration of the preformatted data array
extern const uint8_t USB_PREFORMATED[];

// Function to get a pointer to the preformatted data
uint8_t* get_preformatted_data(void);

// Function to get the size of the preformatted data
uint32_t get_preformatted_data_size(void);

#endif /* PREFORMATTED_FLASH_H */
