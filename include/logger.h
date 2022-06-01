/*****************************************************************************
 *                                                                           *
 * \file logger.h                                                            *
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

#ifndef _LOGGER_H
#define _LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/

#include "suricata_config.h"

/*****************************************************************************
 * Configuration Macros                                                      *
 *****************************************************************************/

#ifndef LOGGER_EN
#define LOGGER_EN 0
#endif

#ifndef LOG_INFO_EN
#define LOG_INFO_EN 1
#endif

#ifndef LOG_WARN_EN
#define LOG_WARN_EN 1
#endif

#ifndef LOG_DEBUG_EN
#define LOG_DEBUG_EN 1
#endif

#ifndef LOG_ERROR_EN
#define LOG_ERROR_EN 1
#endif

#ifndef SERIAL_SPEED
#define SERIAL_SPEED  9600
#endif

#ifndef MAX_LOG_MSG_SIZE
#define MAX_LOG_MSG_SIZE  512
#endif

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/

void LOG_INIT (void);

void LOG_INFO (const char * tag, const char * fmt, ...);

void LOG_WARN (const char * tag, const char * fmt, ...);

void LOG_DEBUG (const char * tag, const char * fmt, ...);

void LOG_ERROR (const char * tag, const char * fmt, ...);

void LOG_ERROR_LOCK (const char * tag, const char * fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* _LOGGER_H */

/* end of file */