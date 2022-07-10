/*****************************************************************************
 *                                                                           *
 * \file mic.c                                                               *
 *                                                                           *
 * \brief MIC driver module.                                                 *
 *                                                                           *
 * \author blackchacal <ribeiro.tonet@gmail.com>                             *
 * \date Jul 9, 2022                                                         *
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

#include "mic.h"
#include "logger.h"

/*****************************************************************************
 * Macros                                                                    *    
 *****************************************************************************/

#define ADC_REF_VOLTAGE     (3.3f) /* Volts */
#define MIC_VREF_RMS        (0.07943f) /* Volts */

/*****************************************************************************
 * Static Data                                                               *
 *****************************************************************************/

/*****************************************************************************
 * Public Data                                                               *
 *****************************************************************************/

extern mic_t mic;

/*****************************************************************************
 * Private Function Prototypes                                               *
 *****************************************************************************/

float conv_adc_to_voltage (uint16_t adc_val);
uint8_t calc_db_from_voltage (float voltage);

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/            

/**
 * @brief Initializes the MIC driver module.
 */
int mic_init (mic_t * mic, uint8_t pin)
{
    int err = ERR_OK;
#if MIC_EN == 1    

    if (mic == NULL)
    {
        err = ERR_MIC_NULL_POINTER;
    }
    else
    {
        mic->pin = pin;
        mic->adc_val = 0;
        mic->db_val = 0;

        /* Set ADC resolution to support 16-bits 
         * Depending on the hw the resolution will be limited to max hw 
         * capabilities.
         */
        analogReadResolution(MIC_ADC_RESOLUTION);
    }
#endif
    return err;
}

/**
 * @brief Returns the raw intensity value from the ADC.
 */
int mic_read_raw_intensity (mic_t * mic, uint32_t * raw_val)
{
    int err = ERR_OK;
#if MIC_EN == 1    

    if (mic == NULL)
    {
        err = ERR_MIC_NULL_POINTER;
    }
    else
    {
        mic->adc_val = analogRead(mic->pin);
        *raw_val = mic->adc_val;
    }

#endif
    return err;
}

/**
 * @brief Returns the measured dB value.
 */
int mic_read_db (mic_t * mic, uint8_t * db_val)
{
    int err = ERR_OK;
#if MIC_EN == 1   

    if (mic == NULL)
    {
        err = ERR_MIC_NULL_POINTER;
    }
    else
    {
        mic_read_raw_intensity(mic, &mic->adc_val);
        float voltage = conv_adc_to_voltage(mic->adc_val);
        mic->db_val = calc_db_from_voltage(voltage);
        *db_val = mic->db_val;
    }

#endif
    return err;
}

/*****************************************************************************
 * Private Functions                                                         *
 *****************************************************************************/

float conv_adc_to_voltage (uint16_t adc_val)
{
    return ((adc_val * ADC_REF_VOLTAGE) / MIC_ADC_MAX_VAL);
}

uint8_t calc_db_from_voltage (float voltage)
{
    return (94 + 20 * log10(voltage / MIC_VREF_RMS)); 
}

/* end of file */