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
#include "rbuffer.h"

/*****************************************************************************
 * Public Vars                                                               *
 *****************************************************************************/

/* --- Array Buffers ------------------- */

uint8_t data_buf[DATA_BUFFER_SIZE] = {0};

/* --- Module vars --------------------- */

rbuffer_t data_rbuffer;

/*****************************************************************************
 * Function Prototypes                                                       *
 *****************************************************************************/

/*****************************************************************************
 * Code                                                                      *
 *****************************************************************************/

void setup() 
{
    int err = ERR_OK;

    delay(5000);
    /* Init log system */
    LOG_INIT();

    LOG_INFO("SETUP", "> ----- Suricata ----- <\n");
    LOG_INFO("SETUP", "FW Version: %d.%d.%d", FW_MAJOR, FW_MINOR, FW_PATCH);
    LOG_INFO("SETUP", "HW Version: %d.%d\n", HW_MAJOR, HW_MINOR);
    LOG_INFO("SETUP", "> System init...\n");

    /* Init ring buffer */
    LOG_INFO("SETUP:RBUFFER", "> Init Data Ring Buffer...");
    err = rbuffer_init(&data_rbuffer, data_buf, DATA_BUFFER_SIZE);
    if (err != ERR_OK)
    {
        LOG_ERROR_LOCK("SETUP:RBUFFER", ">> Data Ring Buffer init error: %d", err);
    }
    LOG_INFO("SETUP:RBUFFER", ">> Data Ring Buffer initialized.");
}

void loop() 
{
}

/* --- Private functions --------------------------------------------------- */

/* end of file */