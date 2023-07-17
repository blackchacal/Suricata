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
#include "batt.h"
#include "ble.h"

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
batt_t batt;
ble_t ble;

/*****************************************************************************
 * Function Prototypes                                                       *
 *****************************************************************************/

/*****************************************************************************
 * Code                                                                      *
 *****************************************************************************/

void setup() 
{
    int err = ERR_OK;

    delay(2000);
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
    
    LOG_INFO("SETUP:BATT", "> Init Battery Level module...");
    err = batt_init(&batt, BATT_LEVEL_PIN);
    if (err != ERR_OK)
    {
        LOG_ERROR_LOCK("SETUP:BATT", ">> Battery Level module init error: %d", err);
    }
    LOG_INFO("SETUP:BATT", ">> Battery Level module initialized.");
    
    LOG_INFO("SETUP:BLE", "> Init BLE module...");
    err = ble_init(&ble);
    if (err != ERR_OK)
    {
        LOG_ERROR_LOCK("SETUP:BLE", ">> BLE module init error: %d", err);
    }
    LOG_INFO("SETUP:BLE", ">> BLE module initialized.");
}

void loop() 
{
    float humidity;
    float temperature;
    uint32_t ldr_raw;
    uint32_t ldr_lux;
    uint32_t mic_raw;
    uint8_t mic_db;
    int batt_raw;
    uint8_t batt_level;

    /* Process BLE events */
    ble_process(&ble);

    dht20_read_humidity(&dht20, &humidity);
    dht20_read_temperature(&dht20, &temperature);
    mic_read_raw_intensity(&mic, &mic_raw);
    mic_read_db(&mic, &mic_db);
    ldr_read_raw_intensity(&ldr, &ldr_raw);
    ldr_read_lux(&ldr, &ldr_lux);
    batt_read_raw_level(&batt, &batt_raw);
    batt_read_level(&batt, &batt_level);

    LOG_INFO("LOOP:DHT20", "DHT20 data, temp: %s ºC, hum: %s %RH", String(temperature, 1).c_str(), String(humidity, 1).c_str());
    LOG_INFO("LOOP:MIC", "Audio intensity raw: %d, dB: %d dB", mic_raw, mic_db);
    LOG_INFO("LOOP:LDR", "Light intensity raw: %d, lux: %d lux", ldr_raw, ldr_lux);
    LOG_INFO("LOOP:BATT", "Battery raw: %d, level: %d%\n", batt_raw, batt_level);

    led_blink(&rgb_led, 1, 0, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00);

    delay(1000);
}

/* --- Private functions --------------------------------------------------- */

/* end of file */