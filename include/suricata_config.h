/*****************************************************************************
 *                                                                           *
 * \file suricata_config.h                                                   *
 *                                                                           *
 * \brief General configuration for Suricata firmware.                       *
 *                                                                           *
 * \author blackchacal <ribeiro.tonet@gmail.com>                             *
 * \date May 25, 2022                                                        *
 *                                                                           *
 * \version 1.0 | \author blackchacal                                        *
 * File creation.                                                            *
 *                                                                           *
 *****************************************************************************/

#ifndef _SURICATA_CONFIG_H
#define _SURICATA_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
 * Configuration Macros                                                      *
 *****************************************************************************/

/* --- Logger Module ---------------------------------------- */ 

#define LOGGER_EN                 1
// #define LOG_INFO_EN               1
// #define LOG_WARN_EN               1
// #define LOG_DEBUG_EN              1
// #define LOG_ERROR_EN              1
// #define SERIAL_SPEED              9600
// #define MAX_LOG_MSG_SIZE          512


#ifdef __cplusplus
}
#endif

#endif /* _SURICATA_CONFIG_H */

/* end of file */