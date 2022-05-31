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

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/

/* --- Standard libraries -------------------- */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* --- Arduino libraries -------------------- */
#include <Arduino.h>

/* --- Custom modules -------------------- */
#include "rbuffer.h"

/*****************************************************************************
 * Macros                                                                    *
 *****************************************************************************/

#define ENTER_CRITICAL  noInterrupts();
#define EXIT_CRITICAL   interrupts();

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/

/**
 * @brief Initializes rbuffer struct.
 */
int rbuffer_init (rbuffer_t * rb, uint8_t * buffer, uint16_t buf_size)
{
    int err = ERR_OK;

    if ((rb == NULL) || (buffer == NULL))
    {
        err = ERR_RBUFFER_NULL_POINTER;
    }
    else if ((buf_size == 0) || ((buf_size & (buf_size - 1)) != 0))
    {
        err = ERR_RBUFFER_INVALID_SIZE;
    }
    else
    {
        rb->buf = buffer;
        rb->head = 0;
        rb->tail = 0;
        rb->lot = 0;
        rb->size = buf_size;
    }

    return err;
}

/**
 * @brief Adds one byte to rbuffer.
 */
int rbuffer_add_byte (rbuffer_t * rb, uint8_t byte)
{
    int err = ERR_OK;

    if (rb == NULL)
    {
        err = ERR_RBUFFER_NULL_POINTER;
    }
    else if (rbuffer_full(rb))
    {
        err = ERR_RBUFFER_FULL;
    }
    else
    {
        rb->buf[rb->head] = byte;
        ENTER_CRITICAL
        rb->head = (rb->head + 1) & (rb->size - 1);
        rb->lot++;
        EXIT_CRITICAL
    }

    return err;
}

/**
 * @brief Adds several bytes to rbuffer.
 */
int rbuffer_add_bytes (rbuffer_t * rb, uint8_t * data, uint16_t nbytes)
{
    int err = ERR_OK;

    if (rb == NULL)
    {
        err = ERR_RBUFFER_NULL_POINTER;
    }
    else if (rbuffer_full(rb))
    {
        err = ERR_RBUFFER_FULL;
    }
    else if (nbytes == 0)
    {
        err = ERR_RBUFFER_INVALID_SIZE;
    }
    else if (nbytes > rbuffer_free(rb))
    {
        err = ERR_RBUFFER_NOT_ENOUGH_SPACE;
    }
    else
    {
        uint16_t size_to_end = rb->size - rb->head;
        if (size_to_end < nbytes)
        {
            memcpy(rb->buf + rb->head, data, size_to_end);
            memcpy(rb->buf, data + size_to_end, nbytes - size_to_end);
        }
        else
        {
            memcpy(rb->buf + rb->head, data, nbytes);
        }
        ENTER_CRITICAL
        rb->head = (rb->head + nbytes) & (rb->size - 1);
        rb->lot += nbytes;
        EXIT_CRITICAL
    }

    return err;
}

/**
 * @brief Gets one byte from rbuffer.
 */
int rbuffer_get_byte (rbuffer_t * rb, uint8_t * byte)
{
    int err = ERR_OK;

    if (rb == NULL)
    {
        err = ERR_RBUFFER_NULL_POINTER;
    }
    else if (rbuffer_empty(rb))
    {
        err = ERR_RBUFFER_EMPTY;
    }
    else
    {
        *byte = rb->buf[rb->tail];
        ENTER_CRITICAL
        rb->tail = (rb->tail + 1) & (rb->size - 1);
        rb->lot--;
        EXIT_CRITICAL
    }

    return err;
}

/**
 * @brief Gets several bytes from rbuffer.
 */
int rbuffer_get_bytes (rbuffer_t * rb, uint8_t * data, uint8_t nbytes)
{
    int err = ERR_OK;

    if (rb == NULL)
    {
        err = ERR_RBUFFER_NULL_POINTER;
    }
    else if (rbuffer_empty(rb))
    {
        err = ERR_RBUFFER_EMPTY;
    }
    else if (nbytes == 0)
    {
        err = ERR_RBUFFER_INVALID_SIZE;
    }
    else if (nbytes > rbuffer_used(rb))
    {
        err = ERR_RBUFFER_NOT_ENOUGH_DATA;
    }
    else
    {
        uint16_t size_to_end = rb->size - rb->tail;
        if (size_to_end < nbytes)
        {
            memcpy(data, rb->buf + rb->tail, size_to_end);
            memcpy(data + size_to_end, rb->buf, nbytes - size_to_end);
        }
        else
        {
            memcpy(data, rb->buf + rb->tail, nbytes);
        }
        ENTER_CRITICAL
        rb->tail = (rb->tail + nbytes) & (rb->size - 1);
        rb->lot -= nbytes;
        EXIT_CRITICAL
    }

    return err;
}

/**
 * @brief Check if rbuffer is empty.
 */
bool rbuffer_empty (const rbuffer_t * rb)
{
    return (rb == NULL) ? false : ((rb->head == rb->tail) && (rb->lot == 0));
}

/**
 * @brief Checks if rbuffer is full.
 */
bool rbuffer_full (const rbuffer_t * rb)
{
    return (rb == NULL) ? false : ((rb->head == rb->tail) && (rb->lot == rb->size));
}

/**
 * @brief Returns rbuffer free space.
 */
uint16_t rbuffer_free (const rbuffer_t * rb)
{
    return (rb == NULL) ? 0 : (rb->size - rbuffer_used(rb));
}

/**
 * @brief Returns rbuffer used space.
 */
uint16_t rbuffer_used (const rbuffer_t * rb)
{
    return (rb == NULL) ? 0 : rb->lot;
}

/**
 * @brief Clears rbuffer by resetting all pointers.
 */
int rbuffer_clear (rbuffer_t * rb)
{
    int err = ERR_OK;

    if (rb == NULL)
    {
        err = ERR_RBUFFER_NULL_POINTER;
    }
    else
    {
        rb->head = 0;
        rb->tail = 0;
        rb->lot = 0;
    }

    return err;
}

/* end of file */