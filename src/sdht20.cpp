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

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/

#include <stddef.h>

#include <Arduino.h>

#include "sdht20.h"
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

extern dht20_t dht20;
extern DHT20 DHT;

/*****************************************************************************
 * Private Function Prototypes                                               *
 *****************************************************************************/

int dht20_check_status (dht20_t * dht20);

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/            

/**
 * @brief Initializes the DHT20 driver module.
 */
int dht20_init (dht20_t * dht20, uint8_t sda_pin, uint8_t scl_pin)
{
    int err = ERR_OK;
#if DHT20_EN == 1    

    if (dht20 == NULL)
    {
        err = ERR_DHT20_NULL_POINTER;
    }
    else
    {
        dht20->sda_pin = sda_pin;
        dht20->scl_pin = scl_pin;
        dht20->temp = 0;
        dht20->humidity = 0;

        dht20->instance = DHT;
        dht20->instance.begin();

        err = dht20_check_status(dht20);
    }
#endif
    return err;
}

/**
 * @brief Reads the current temperature.
 */
int dht20_read_temperature (dht20_t * dht20, float * temp)
{
    int err = ERR_OK;
#if DHT20_EN == 1    

    if (dht20 == NULL)
    {
        err = ERR_DHT20_NULL_POINTER;
    }
    else if ((err = dht20_check_status(dht20)) != ERR_OK)
    {
        return err;
    }
    else
    {
        *temp = dht20->instance.getTemperature();
    }

#endif
    return err;
}

/**
 * @brief Reads the current humidity.
 */
int dht20_read_humidity (dht20_t * dht20, float * humidity)
{
    int err = ERR_OK;
#if DHT20_EN == 1   

    if (dht20 == NULL)
    {
        err = ERR_DHT20_NULL_POINTER;
    }
    else if ((err = dht20_check_status(dht20)) != ERR_OK)
    {
        return err;
    }
    else
    {
        *humidity = dht20->instance.getHumidity();
    }

#endif
    return err;
}

/*****************************************************************************
 * Private Functions                                                         *
 *****************************************************************************/

int dht20_check_status (dht20_t * dht20)
{
    int err = ERR_OK;
    int status = 0;

    status = dht20->instance.read();
    switch (status)
    {
    case DHT20_OK:
        break;
    case DHT20_ERROR_CHECKSUM:
        err = ERR_DHT20_CHECKSUM;
        break;
    case DHT20_ERROR_CONNECT:
        err = ERR_DHT20_CONNECT;
        break;
    case DHT20_MISSING_BYTES:
        err = ERR_DHT20_MISSING_BYTES;
        break;
    default:
        err = ERR_DHT20_UNKNOWN;
        break;
    }

    return err;
}

/* end of file */