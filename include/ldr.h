/*****************************************************************************
 *                                                                           *
 * \file ldr.h                                                               *
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

#ifndef _LDR_H
#define _LDR_H

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
#define ERR_LDR_NULL_POINTER            (-1)

#define N_STATES    4 /* Number of brightness states */

/*****************************************************************************
 * Datatypes                                                                 *
 *****************************************************************************/

typedef enum
{
    DARK,
    DIM,
    NORMAL,
    BRIGHT
} ldr_light_state_t;

typedef struct
{
    uint8_t pin;
    uint32_t adc_val;   
    uint32_t lux_val;
    ldr_light_state_t state_val;   
} ldr_t;

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/         

/**
 * @brief Initializes the LDR driver module.
 * 
 * @param ldr 
 * @param pin 
 * @return int 
 */
int ldr_init (ldr_t * ldr, uint8_t pin);

/**
 * @brief Returns the raw intensity value from the ADC.
 * 
 * @param ldr 
 * @param raw_val 
 * @return int 
 */
int ldr_get_raw_intensity (ldr_t * ldr, uint32_t * raw_val);

/**
 * @brief Returns the calibrated measured LUX value.
 * 
 * @param ldr 
 * @param lux_val 
 * @return int 
 */
int ldr_get_lux (ldr_t * ldr, uint32_t * lux_val);

/**
 * @brief Returns the brightness state
 * 
 * @details Returns an enum value that verbally describes
 * several possible brightness states, calculated in a
 * linear approximation.
 * 
 * @param ldr 
 * @param state_val 
 * @return int 
 */
int ldr_get_brightness_state (ldr_t * ldr, ldr_light_state_t * state_val);

#ifdef __cplusplus
}
#endif

#endif /* _LDR_H */

/* end of file */