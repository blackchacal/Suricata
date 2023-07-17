/*****************************************************************************
 *                                                                           *
 * \file batt.h                                                              *
 *                                                                           *
 * \brief Battery level module.                                              *
 *                                                                           *
 * \author blackchacal <ribeiro.tonet@gmail.com>                             *
 * \date Aug 22, 2022                                                        *
 *                                                                           *
 * \version 1.0 | \author blackchacal                                        *
 * File creation.                                                            *
 *                                                                           *
 *****************************************************************************/

#ifndef _BATT_H
#define _BATT_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/

#include "stdint.h"
#include "stdbool.h"

#include "suricata_config.h"

/*****************************************************************************
 * Macros                                                                    *    
 *****************************************************************************/

/* --- Error codes ----------------------------------------------------------*/

#define ERR_OK                          (0)
#define ERR_BATT_NULL_POINTER           (-1)

/*****************************************************************************
 * Datatypes                                                                 *
 *****************************************************************************/

typedef struct
{
    uint8_t pin;
    int raw_level;   
    uint8_t level;   
    uint8_t prev_level;   
} batt_t;

/*****************************************************************************
 * Public Data                                                               *
 *****************************************************************************/

extern batt_t batt;

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/         

/**
 * @brief Initializes the Battery Level module.
 * 
 * @param batt 
 * @param pin 
 * @return int 
 */
int batt_init (batt_t * batt, uint8_t pin);

/**
 * @brief Returns the battery level value from ADC.
 * 
 * @param batt 
 * @param raw_level 
 * @return int 
 */
int batt_read_raw_level (batt_t * batt, int * raw_level);

/**
 * @brief Returns the battery level in percentage (0-100).
 * 
 * @param batt 
 * @param level 
 * @return int 
 */
int batt_read_level (batt_t * batt, uint8_t * level);

/**
 * @brief Checks if battery level changed.
 * 
 * @param batt 
 * @param level 
 * @return int 
 */
int batt_is_level_changed (batt_t * batt, uint8_t * level);

#ifdef __cplusplus
}
#endif

#endif /* _BATT_H */

/* end of file */