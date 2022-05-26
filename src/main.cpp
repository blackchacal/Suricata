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

/* --- Arduino libraries -------------------- */
#include <Arduino.h>

/* --- Custom modules -------------------- */
#include "suricata_config.h"
#include "logger.h"

/*****************************************************************************
 * Code                                                                      *
 *****************************************************************************/

void setup() {
    LOG_INIT();
}

void loop() {
    LOG_INFO("SETUP", "Start SETUP: %d", 45);
    delay(1000);
    LOG_WARN("SETUP", "Start SETUP: %d", 10);
    delay(1000);
    LOG_DEBUG("SETUP", "Start SETUP: %d", 15);
    delay(1000);
    LOG_ERROR("SETUP", "Start SETUP: %d", 20);
    delay(1000);
}