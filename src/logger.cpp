/*****************************************************************************
 *                                                                           *
 * \file logger.c                                                            *
 *                                                                           *
 * \brief Module to print log and debug messages to the console.             *
 *                                                                           *
 * \author blackchacal <ribeiro.tonet@gmail.com>                             *
 * \date May 25, 2022                                                        *
 *                                                                           *
 * \version 1.0 | \author blackchacal                                        *
 * File creation.                                                            *
 *                                                                           *
 *****************************************************************************/

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/

/* --- Standard libraries -------------------- */
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* --- Arduino libraries -------------------- */
#include <Arduino.h>

/* --- Custom modules -------------------- */
#include "logger.h"

/*****************************************************************************
 * Macros                                                                    *
 *****************************************************************************/

/*****************************************************************************
 * Datatypes                                                                 *
 *****************************************************************************/

/**
 * \enum log_type_t
 * Defines the types of logs.
 */
typedef enum 
{
    LOG_TYPE_INFO,
    LOG_TYPE_WARNING,
    LOG_TYPE_DEBUG,
    LOG_TYPE_ERROR,
} log_type_t;

/*****************************************************************************
 * Static Variables                                                          *
 *****************************************************************************/

static char log_msg[MAX_LOG_MSG_SIZE];

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/

void LOG_INIT (void)
{
    Serial.begin(SERIAL_SPEED);
}

void LOG_INFO (const char * tag, const char * fmt, ...)
{
#if LOGGER_EN == 1
#if LOG_INFO_EN == 1
    snprintf(log_msg, sizeof(log_msg), "INFO - %s | ", tag);
    Serial.print(log_msg);

    va_list vargs;
    va_start(vargs, fmt);
    vsnprintf(log_msg, sizeof(log_msg), fmt, vargs);
    Serial.println(log_msg);
    va_end(vargs);
#endif
#endif
}

void LOG_WARN (const char * tag, const char * fmt, ...)
{
#if LOGGER_EN == 1
#if LOG_WARN_EN == 1
    snprintf(log_msg, sizeof(log_msg), "WARN - %s | ", tag);
    Serial.print(log_msg);

    va_list vargs;
    va_start(vargs, fmt);
    vsnprintf(log_msg, sizeof(log_msg), fmt, vargs);
    Serial.println(log_msg);
    va_end(vargs);
#endif
#endif
}

void LOG_DEBUG (const char * tag, const char * fmt, ...)
{
#if LOGGER_EN == 1
#if LOG_DEBUG_EN == 1
    snprintf(log_msg, sizeof(log_msg), "DEBUG - %s | ", tag);
    Serial.print(log_msg);

    va_list vargs;
    va_start(vargs, fmt);
    vsnprintf(log_msg, sizeof(log_msg), fmt, vargs);
    Serial.println(log_msg);
    va_end(vargs);
#endif
#endif  
}

void LOG_ERROR (const char * tag, const char * fmt, ...)
{
#if LOGGER_EN == 1
#if LOG_ERROR_EN == 1
    snprintf(log_msg, sizeof(log_msg), "ERROR - %s | ", tag);
    Serial.print(log_msg);

    va_list vargs;
    va_start(vargs, fmt);
    vsnprintf(log_msg, sizeof(log_msg), fmt, vargs);
    Serial.println(log_msg);
    va_end(vargs);
#endif
#endif
}

void LOG_ERROR_LOCK (const char * tag, const char * fmt, ...)
{
#if LOGGER_EN == 1
#if LOG_ERROR_EN == 1
    snprintf(log_msg, sizeof(log_msg), "ERROR - %s | ", tag);
    Serial.print(log_msg);

    va_list vargs;
    va_start(vargs, fmt);
    vsnprintf(log_msg, sizeof(log_msg), fmt, vargs);
    Serial.println(log_msg);
    va_end(vargs);
    
    while(1) {}
#endif
#endif
}

/* end of file */