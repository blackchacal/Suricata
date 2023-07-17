/*****************************************************************************
 *                                                                           *
 * \file ble.h                                                               *
 *                                                                           *
 * \brief Bluetooth Low-Energy module.                                       *
 *                                                                           *
 * \author blackchacal <ribeiro.tonet@gmail.com>                             *
 * \date Aug 22, 2022                                                        *
 *                                                                           *
 * \version 1.0 | \author blackchacal                                        *
 * File creation.                                                            *
 *                                                                           *
 *****************************************************************************/

#ifndef _BLE_H
#define _BLE_H

#include "ArduinoBLE.h"

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
#define ERR_BLE_NULL_POINTER            (-1)
#define ERR_BLE_FAILED_INIT             (-2)

/*****************************************************************************
 * Datatypes                                                                 *
 *****************************************************************************/

typedef struct
{
    BLEDevice central;
} ble_t;

/*****************************************************************************
 * Public Data                                                               *
 *****************************************************************************/

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/         

/**
 * @brief Initializes the BLE module.
 * 
 * @param this 
 * @return int 
 */
int ble_init (ble_t * ble);

/**
 * @brief Processes the BLE events.
 * 
 * @details This function must be called inside loop().
 * 
 * @param this 
 * @return int 
 */
int ble_process (ble_t * ble);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_H */

/* end of file */