/*****************************************************************************
 *                                                                           *
 * \file main.cpp                                                            *
 *                                                                           *
 * \brief Suricata main code.                                                *
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
#include "led.h"

/*****************************************************************************
 * Public Vars                                                               *
 *****************************************************************************/

/* --- Array Buffers ------------------- */

uint8_t data_buf[DATA_BUFFER_SIZE] = {0};

/* --- Module vars --------------------- */

rbuffer_t data_rbuffer;
led_t rgb_led;

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

    LOG_INFO("SETUP:LED", "> Init LED driver...");
    err = led_init(&rgb_led, LED_R_PIN, LED_G_PIN, LED_B_PIN);
    if (err != ERR_OK)
    {
        LOG_ERROR_LOCK("SETUP:LED", ">> LED driver init error: %d", err);
    }
    LOG_INFO("SETUP:LED", ">> LED driver initialized.");
    led_blink_block(&rgb_led, 10, 10, 255, 0, 0, 0, 0, 0);
}

void loop() 
{
}

/* --- Private functions --------------------------------------------------- */

/* end of file */