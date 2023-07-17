/*****************************************************************************
 *                                                                           *
 * \file batt.c                                                              *
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

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/

#include <stddef.h>

#include <Arduino.h>

#include "batt.h"
#include "logger.h"

/*****************************************************************************
 * Macros                                                                    *    
 *****************************************************************************/

/*****************************************************************************
 * Static Data                                                               *
 *****************************************************************************/

/*****************************************************************************
 * Public Data                                                               *
 *****************************************************************************/

extern batt_t batt;

/*****************************************************************************
 * Private Function Prototypes                                               *
 *****************************************************************************/

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/            

/**
 * @brief Initializes the Battery Level module.
 */
int batt_init (batt_t * batt, uint8_t pin)
{
    int err = ERR_OK;
#if BATT_EN == 1    

    if (batt == NULL)
    {
        err = ERR_BATT_NULL_POINTER;
    }
    else
    {
        batt->pin = pin;
        batt->raw_level = 0;
        batt->level = 0;
        batt->prev_level = 0;
    }
#endif
    return err;
}

/**
 * @brief Returns the battery level value from ADC.
 */
int batt_read_raw_level (batt_t * batt, int * raw_level)
{
    int err = ERR_OK;
#if BATT_EN == 1    

    if (batt == NULL)
    {
        err = ERR_BATT_NULL_POINTER;
    }
    else
    {
        batt->raw_level = analogRead(batt->pin);
        *raw_level = batt->raw_level;
    }
#endif
    return err;
}

/**
 * @brief Returns the battery level in percentage (0-100).
 */
int batt_read_level (batt_t * batt, uint8_t * level)
{
    int err = ERR_OK;
#if BATT_EN == 1    

    if (batt == NULL)
    {
        err = ERR_BATT_NULL_POINTER;
    }
    else
    {
        /**
         * The Battery level is measured with a voltage divider, 100k / 39k:
         *          
         *    Batt Voltage
         *        |
         *    R1 | | 100k
         *        |_________ Batt Level (to ADC)
         *        |
         *    R2 | | 39k
         *        |
         *       _|_
         *       \_/ GND
         * 
         * Assuming an Arduino pin internal resistor of ~32k powered at 3.3V,
         * we have the following range:
         *   
         *                         Batt(V)    Level(V)     ADC (10-bit)    ADC (12-bit)    ADC (16-bit)
         * Discharged (0%):         3.0V   ->  0.446V   ->     139      ->     554      ->     8858
         * Low (10%):               3.2V   ->  0.476V   ->     148      ->     591      ->     9453
         * Fully Charged (100%):    4.2V   ->  0.625V   ->     194      ->     776      ->     12412
         */
        // 0.842 - 261 / 1.2 - 372
        int battRaw = analogRead(batt->pin);
        int batteryLevel = map(battRaw, 260, 370, 0, 100);
        // int batteryLevel = map(battRaw, 130, 190, 0, 100);
        batt->prev_level = batt->level;
        batt->level = (uint8_t)batteryLevel;
        *level = batt->level;
    }
#endif
    return err;
}

/**
 * @brief Checks if battery level changed.
 */
int batt_is_level_changed (batt_t * batt, uint8_t * level)
{
    int err = ERR_OK;
#if BATT_EN == 1    

    if (batt == NULL)
    {
        err = ERR_BATT_NULL_POINTER;
    }
    else
    {
        uint8_t new_level;
        batt_read_level(batt, &new_level);
        *level = new_level;
        return (batt->level != batt->prev_level);
    }
#endif
    return err;
}

/*****************************************************************************
 * Private Functions                                                         *
 *****************************************************************************/

/* end of file */