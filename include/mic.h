/*****************************************************************************
 *                                                                           *
 * \file mic.h                                                               *
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

#ifndef _MIC_H
#define _MIC_H

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
#define ERR_MIC_NULL_POINTER            (-1)

/*****************************************************************************
 * Datatypes                                                                 *
 *****************************************************************************/

typedef struct
{
    uint8_t pin;
    uint32_t adc_val;   
    uint8_t db_val;
} mic_t;

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/         

/**
 * @brief Initialize the MIC driver module.
 * 
 * @param mic 
 * @param pin 
 * @return int 
 */
int mic_init (mic_t * mic, uint8_t pin);

/**
 * @brief Returns the raw intensity value from ADC.
 * 
 * @param mic 
 * @param raw_val 
 * @return int 
 */
int mic_read_raw_intensity (mic_t * mic, uint32_t * raw_val);

/**
 * @brief Returns the measured dB value.
 * 
 * @param mic 
 * @param db_val 
 * @return int 
 */
int mic_read_db (mic_t * mic, uint8_t * db_val);

#ifdef __cplusplus
}
#endif

#endif /* _MIC_H */

/* end of file */