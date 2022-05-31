/*****************************************************************************
 *                                                                           *
 * \file rbuffer.h                                                           *
 *                                                                           *
 * \brief Ring buffer module.                                                *
 *                                                                           *
 * \author blackchacal <ribeiro.tonet@gmail.com>                             *
 * \date May 30, 2022                                                        *
 *                                                                           *
 * \version 1.0 | \author blackchacal                                        *
 * File creation.                                                            *
 *                                                                           *
 *****************************************************************************/

#ifndef _RBUFFER_H
#define _RBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/

#include "suricata_config.h"

/*****************************************************************************
 * Macros                                                                    *    
 *****************************************************************************/

/* --- Error codes ----------------------------------------------------------*/

#define ERR_OK                          (0)
#define ERR_RBUFFER_NULL_POINTER        (-1)
#define ERR_RBUFFER_INVALID_SIZE        (-2)
#define ERR_RBUFFER_FULL                (-3)
#define ERR_RBUFFER_EMPTY               (-4)
#define ERR_RBUFFER_NOT_ENOUGH_SPACE    (-5)
#define ERR_RBUFFER_NOT_ENOUGH_DATA     (-6)

/*****************************************************************************
 * Datatypes                                                                 *
 *****************************************************************************/

typedef struct
{
    uint8_t * buf;
    uint16_t head;
    uint16_t tail;
    uint16_t size;
    uint16_t lot;
} rbuffer_t;

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/

/**
 * @brief Initializes rbuffer struct.
 * 
 * @param rb 
 * @param buffer 
 * @param buf_size 
 * @return int 
 */
int rbuffer_init (rbuffer_t * rb, uint8_t * buffer, uint16_t buf_size);

/**
 * @brief Adds one byte to rbuffer.
 * 
 * @param rb 
 * @param byte 
 * @return int 
 */
int rbuffer_add_byte (rbuffer_t * rb, uint8_t byte);

/**
 * @brief Adds several bytes to rbuffer.
 * 
 * @param rb 
 * @param data 
 * @param nbytes 
 * @return int 
 */
int rbuffer_add_bytes (rbuffer_t * rb, uint8_t * data, uint16_t nbytes);

/**
 * @brief Gets one byte from rbuffer.
 * 
 * @param rb 
 * @param byte 
 * @return int 
 */
int rbuffer_get_byte (rbuffer_t * rb, uint8_t * byte);

/**
 * @brief Gets several bytes from rbuffer.
 * 
 * @param rb 
 * @param data 
 * @param nbytes 
 * @return int 
 */
int rbuffer_get_bytes (rbuffer_t * rb, uint8_t * data, uint8_t nbytes);

/**
 * @brief Check if rbuffer is empty.
 * 
 * @param rb 
 * @return true 
 * @return false 
 */
bool rbuffer_empty (const rbuffer_t * rb);

/**
 * @brief Checks if rbuffer is full.
 * 
 * @param rb 
 * @return true 
 * @return false 
 */
bool rbuffer_full (const rbuffer_t * rb);

/**
 * @brief Returns rbuffer free space.
 * 
 * @param rb 
 * @return uint16_t 
 */
uint16_t rbuffer_free (const rbuffer_t * rb);

/**
 * @brief Returns rbuffer used space.
 * 
 * @param rb 
 * @return uint16_t 
 */
uint16_t rbuffer_used (const rbuffer_t * rb);

/**
 * @brief Clears rbuffer by resetting all pointers.
 * 
 * @param rb 
 * @return int 
 */
int rbuffer_clear (rbuffer_t * rb);

#ifdef __cplusplus
}
#endif

#endif /* _RBUFFER_H */

/* end of file */