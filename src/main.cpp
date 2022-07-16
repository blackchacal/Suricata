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

/* --- Standard libraries -------------------- */

/* --- Arduino libraries -------------------- */
#include <Arduino.h>

/* --- Custom modules -------------------- */
#include "suricata_config.h"
#include "logger.h"
#include "rbuffer.h"
#include "led.h"
#include "ldr.h"
#include "mic.h"
#include "sdht20.h"

/*****************************************************************************
 * Public Vars                                                               *
 *****************************************************************************/

/* --- Array Buffers ------------------- */

uint8_t data_buf[DATA_BUFFER_SIZE] = {0};

/* --- Module vars --------------------- */

rbuffer_t data_rbuffer;
led_t rgb_led;
ldr_t ldr;
mic_t mic;
DHT20 DHT(&Wire);
dht20_t dht20;

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

    LOG_INFO("SETUP:LDR", "> Init LDR driver...");
    err = ldr_init(&ldr, LDR_PIN);
    if (err != ERR_OK)
    {
        LOG_ERROR_LOCK("SETUP:LDR", ">> LDR driver init error: %d", err);
    }
    LOG_INFO("SETUP:LDR", ">> LDR driver initialized.");

    LOG_INFO("SETUP:MIC", "> Init MIC driver...");
    err = mic_init(&mic, MIC_PIN);
    if (err != ERR_OK)
    {
        LOG_ERROR_LOCK("SETUP:MIC", ">> MIC driver init error: %d", err);
    }
    LOG_INFO("SETUP:MIC", ">> MIC driver initialized.");

    LOG_INFO("SETUP:DHT20", "> Init DHT20 driver...");
    err = dht20_init(&dht20, DHT20_SDA_PIN, DHT20_SCL_PIN);
    if (err != ERR_OK)
    {
        LOG_ERROR_LOCK("SETUP:DHT20", ">> DHT20 driver init error: %d", err);
    }
    LOG_INFO("SETUP:DHT20", ">> DHT20 driver initialized.");
}

void loop() 
{
    float humidity;
    float temperature;

    dht20_read_humidity(&dht20, &humidity);
    dht20_read_temperature(&dht20, &temperature);

    LOG_INFO("LOOP:DHT20", "DHT20 data, temp: %s ºC, hum: %s %RH\n", String(temperature, 1).c_str(), String(humidity, 1).c_str());

    delay(1000);
}

/* --- Private functions --------------------------------------------------- */

/* end of file */