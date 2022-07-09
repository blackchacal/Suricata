/*****************************************************************************
 *                                                                           *
 * \file ldr.c                                                               *
 *                                                                           *
 * \brief LDR driver module.                                                 *
 *                                                                           *
 * \author blackchacal <ribeiro.tonet@gmail.com>                             *
 * \date Jul 8, 2022                                                         *
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

#include "ldr.h"
#include "logger.h"

/*****************************************************************************
 * Macros                                                                    *    
 *****************************************************************************/

#define LUX_CALIB_SCALAR    (21359957977)
#define LUX_CALIB_EXP       (-2.012)

/*****************************************************************************
 * Static Data                                                               *
 *****************************************************************************/

/*****************************************************************************
 * Public Data                                                               *
 *****************************************************************************/

extern ldr_t ldr;

/*****************************************************************************
 * Private Function Prototypes                                               *
 *****************************************************************************/

ldr_light_state_t ldr_convert_raw_to_state (uint32_t raw_val);

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/            

/**
 * @brief Initializes the LDR driver module.
 */
int ldr_init (ldr_t * ldr, uint8_t pin)
{
    int err = ERR_OK;
#if LDR_EN == 1    

    if (ldr == NULL)
    {
        err = ERR_LDR_NULL_POINTER;
    }
    else
    {
        ldr->pin = pin;
        ldr->adc_val = 0;
        ldr->lux_val = 0;

        /* Set ADC resolution to support 16-bits 
         * Depending on the hw the resolution will be limited to max hw 
         * capabilities.
         */
        analogReadResolution(LDR_ADC_RESOLUTION);
    }
#endif
    return err;
}

/**
 * @brief Returns the raw intensity value from the ADC.
 */
int ldr_get_raw_intensity (ldr_t * ldr, uint32_t * raw_val)
{
    int err = ERR_OK;
#if LDR_EN == 1    

    if (ldr == NULL)
    {
        err = ERR_LDR_NULL_POINTER;
    }
    else
    {
        ldr->adc_val = analogRead(ldr->pin);
        *raw_val = ldr->adc_val;
    }

#endif
    return err;
}

/**
 * @brief Returns the calibrated measured LUX value.
 */
int ldr_get_lux (ldr_t * ldr, uint32_t * lux_val)
{
    int err = ERR_OK;
#if LDR_EN == 1   

    if (ldr == NULL)
    {
        err = ERR_LDR_NULL_POINTER;
    }
    else
    {
        ldr_get_raw_intensity (ldr, &ldr->adc_val);
        ldr->lux_val = (uint32_t)(LUX_CALIB_SCALAR * pow(ldr->adc_val, LUX_CALIB_EXP));
        *lux_val = ldr->lux_val;
    }

#endif
    return err;
}

/**
 * @brief Returns the brightness state
 */
int ldr_get_brightness_state (ldr_t * ldr, ldr_light_state_t * state_val)
{
    int err = ERR_OK;
#if LDR_EN == 1    
    
    if (ldr == NULL)
    {
        err = ERR_LDR_NULL_POINTER;
    }
    else
    {
        ldr_get_raw_intensity (ldr, &ldr->adc_val);
        ldr->state_val = ldr_convert_raw_to_state(ldr->adc_val);
        *state_val = ldr->state_val;
    }

#endif
    return err;
}

/*****************************************************************************
 * Private Functions                                                         *
 *****************************************************************************/

ldr_light_state_t ldr_convert_raw_to_state (uint32_t raw_val)
{
    return (ldr_light_state_t)((-((float)N_STATES / (float)LDR_ADC_MAX_VAL)) * raw_val + N_STATES);
}

/* end of file */