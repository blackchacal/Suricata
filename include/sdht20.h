/*****************************************************************************
 *                                                                           *
 * \file sdht20.h                                                            *
 *                                                                           *
 * \brief Suricate DHT20 driver module.                                      *
 *                                                                           *
 * \details It uses an external library to interface directly with DHT20     *
 * sensor. It is basically a custom wrapper.                                 *
 *                                                                           *
 * \author blackchacal <ribeiro.tonet@gmail.com>                             *
 * \date Jul 10, 2022                                                        *
 *                                                                           *
 * \version 1.0 | \author blackchacal                                        *
 * File creation.                                                            *
 *                                                                           *
 *****************************************************************************/

#ifndef _SDHT20_H
#define _SDHT20_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/

#include "stdint.h"
#include "stdbool.h"

#include "suricata_config.h"

#include "DHT20.h"

/*****************************************************************************
 * Macros                                                                    *    
 *****************************************************************************/

/* --- Error codes ----------------------------------------------------------*/

#define ERR_OK                          (0)
#define ERR_DHT20_NULL_POINTER          (-1)
#define ERR_DHT20_CHECKSUM              (-2)
#define ERR_DHT20_CONNECT               (-3)
#define ERR_DHT20_MISSING_BYTES         (-4)
#define ERR_DHT20_UNKNOWN               (-5)

/*****************************************************************************
 * Datatypes                                                                 *
 *****************************************************************************/

typedef struct
{
    DHT20   instance;
    uint8_t sda_pin;
    uint8_t scl_pin;
    float temp;   
    float humidity;
} dht20_t;

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/         

/**
 * @brief Initializes the DHT20 driver module.
 * 
 * @param dht20 
 * @param sda_pin 
 * @param sdl_pin 
 * @return int 
 */
int dht20_init (dht20_t * dht20, uint8_t sda_pin, uint8_t sdl_pin);

/**
 * @brief Reads the current temperature.
 * 
 * @param dht20 
 * @param temp 
 * @return int 
 */
int dht20_read_temperature (dht20_t * dht20, float * temp);

/**
 * @brief Reads the current humidity.
 * 
 * @param dht20 
 * @param humidity 
 * @return int 
 */
int dht20_read_humidity (dht20_t * dht20, float * humidity);

#ifdef __cplusplus
}
#endif

#endif /* _SDHT20_H */

/* end of file */