/*****************************************************************************
 *                                                                           *
 * \file ble.c                                                               *
 *                                                                           *
 * \brief Bluetooth Low-Energy module.                                       *
 *                                                                           *
 * \author blackchacal <ribeiro.tonet@gmail.com>                             *
 * \date Aug 22, 2022                                                        *
 *                                                                           *
 * \version 1.0 | \author blackchacal                                        *
 * File creation.                                                            *
 *                                                                           *
 *****************************************************************************/

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/

#include <stddef.h>

#include <Arduino.h>

#include "ble.h"
#include "batt.h"
#include "logger.h"

/*****************************************************************************
 * Macros                                                                    *    
 *****************************************************************************/

/*****************************************************************************
 * Static Data                                                               *
 *****************************************************************************/

/*****************************************************************************
 * Public Data                                                               *
 *****************************************************************************/

extern ble_t ble;

/* --- Battery Service & Characteristics ----------------------------------- */

/* Bluetooth® Battery Service */
BLEService batteryService("180F");
/* Bluetooth® Low Energy Battery Level Characteristic */
BLEUnsignedCharCharacteristic batteryLevelChar("2A19", BLERead | BLENotify);

/* Bluetooth® Device Information Service */
BLEService DeviceInfoService("180A");
/* Bluetooth® Manufacturer Name String Characteristic */
BLEStringCharacteristic ManufacturerNameChar("2A29", BLERead, 11);
/* Bluetooth® Hardware Revision String Characteristic */
BLEStringCharacteristic HardwareRevisionChar("2A27", BLERead, 4);
/* Bluetooth® Firmware Revision String Characteristic */
BLEStringCharacteristic FirmwareRevisionChar("2A26", BLERead, 6);

/*****************************************************************************
 * Private Function Prototypes                                               *
 *****************************************************************************/

int ble_update_battery_level (ble_t * ble);

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/            

/**
 * @brief Initializes the BLE module.
 */
int ble_init (ble_t * ble)
{
    int err = ERR_OK;
#if BLE_EN == 1    

    if (ble == NULL)
    {
        err = ERR_BLE_NULL_POINTER;
    }
    else
    {
        if (!BLE.begin()) 
        {
            err = ERR_BLE_FAILED_INIT;
        }
        else
        {
            BLE.setLocalName(BLE_LOCAL_NAME);
            
            /* --- Add services --- */
            /* Battery Service */
            BLE.setAdvertisedService(batteryService);
            batteryService.addCharacteristic(batteryLevelChar); 
            BLE.addService(batteryService);
            batteryLevelChar.writeValue(0);

            BLE.setAdvertisedService(DeviceInfoService);
            DeviceInfoService.addCharacteristic(ManufacturerNameChar); 
            DeviceInfoService.addCharacteristic(HardwareRevisionChar); 
            DeviceInfoService.addCharacteristic(FirmwareRevisionChar); 
            BLE.addService(DeviceInfoService);
            ManufacturerNameChar.writeValue("BlackChacal");
            char hw_version[4] = {0};
            char fw_version[6] = {0};
            sprintf(hw_version, "%d.%d", HW_MAJOR, HW_MINOR);
            sprintf(fw_version, "%d.%d.%d", FW_MAJOR, FW_MINOR, FW_PATCH);
            HardwareRevisionChar.writeValue(hw_version);
            FirmwareRevisionChar.writeValue(fw_version);

            BLE.advertise();
        }
    }
#endif
    return err;
}

/**
 * @brief Processes the BLE events.
 */
int ble_process (ble_t * ble)
{
    int err = ERR_OK;
#if BLE_EN == 1    

    if (ble == NULL)
    {
        err = ERR_BLE_NULL_POINTER;
    }
    else
    {
        // wait for a Bluetooth® Low Energy central
        ble->central = BLE.central();

        // if a central is connected to the peripheral:
        if (ble->central) 
        {
            Serial.print("Connected to central: ");
            Serial.println(ble->central.address());

            ble_update_battery_level(ble);
        }
    }
#endif
    return err;
}

/*****************************************************************************
 * Private Functions                                                         *
 *****************************************************************************/

int ble_update_battery_level (ble_t * ble)
{
    int err = ERR_OK;
#if BLE_EN == 1    

    if (ble == NULL)
    {
        err = ERR_BLE_NULL_POINTER;
    }
    else
    {
        uint8_t batt_level = 0;
        if (batt_is_level_changed(&batt, &batt_level))
        {
            batteryLevelChar.writeValue(batt_level);
        }
    }
#endif
    return err;
}

/* end of file */