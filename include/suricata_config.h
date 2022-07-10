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
 * General Macros                                                            *
 *****************************************************************************/

/* --- Versions ------------------------------------------------------------- */

#define FW_MAJOR  0
#define FW_MINOR  2
#define FW_PATCH  0

#define HW_MAJOR  1
#define HW_MINOR  0

/* --- Data buffer --------------------------------------------------------- */

/**
 * @def DATA_BUFFER_SIZE
 * Defines the size of the general data buffer.
 */
#define DATA_BUFFER_SIZE        (256)

/*****************************************************************************
 * Configuration Macros                                                      *
 *****************************************************************************/

/* --- Logger Module ------------------------------------------------------- */ 

#define LOGGER_EN                 1
// #define LOG_INFO_EN               1
// #define LOG_WARN_EN               1
// #define LOG_DEBUG_EN              1
// #define LOG_ERROR_EN              1
// #define SERIAL_SPEED              9600
// #define MAX_LOG_MSG_SIZE          512

/* --- LED Driver Module --------------------------------------------------- */

#define LED_EN                    1
#define LED_R_PIN                 11
#define LED_G_PIN                 10
#define LED_B_PIN                 9
#define LED_TIMER                 TIMER_TC3 /* Check available timers */

/* --- LDR Driver Module --------------------------------------------------- */

#define LDR_EN                    1
#define LDR_PIN                   15
#define LDR_ADC_RESOLUTION        16 /* 16 bits */
#define LDR_ADC_MAX_VAL           (1L << LDR_ADC_RESOLUTION) /* 16 bits */
#define LDR_ADC_MIN_VAL           0

/* --- MIC Driver Module --------------------------------------------------- */

#define MIC_EN                    1
#define MIC_PIN                   14
#define MIC_ADC_RESOLUTION        12 /* 16 bits */
#define MIC_ADC_MAX_VAL           (1L << MIC_ADC_RESOLUTION) /* 16 bits */
#define MIC_ADC_MIN_VAL           0

#ifdef __cplusplus
}
#endif

#endif /* _SURICATA_CONFIG_H */

/* end of file */