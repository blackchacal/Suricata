/*****************************************************************************
 *                                                                           *
 * \file led.h                                                               *
 *                                                                           *
 * \brief LED driver module.                                                 *
 *                                                                           *
 * \author blackchacal <ribeiro.tonet@gmail.com>                             *
 * \date Jun 26, 2022                                                        *
 *                                                                           *
 * \version 1.0 | \author blackchacal                                        *
 * File creation.                                                            *
 *                                                                           *
 *****************************************************************************/

#ifndef _LED_H
#define _LED_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/

#include "stdint.h"
#include "stdbool.h"

#include "suricata_config.h"

/*****************************************************************************
 * Macros                                                                    *    
 *****************************************************************************/

/* --- Error codes ----------------------------------------------------------*/

#define ERR_OK                          (0)
#define ERR_LED_NULL_POINTER            (-1)
#define ERR_LED_INVALID_PIN_NUMBER      (-2)
#define ERR_LED_FAILED_INIT_TIMER       (-3)

/*****************************************************************************
 * Datatypes                                                                 *
 *****************************************************************************/

typedef enum
{
    FADE_IN,
    FADE_OUT
} fade_type_t;

typedef struct
{
    uint16_t freq;
    uint8_t nreps;
    bool is_blink;
    uint8_t blink_ch;

    uint16_t fade_time;
    bool is_fade;
    fade_type_t fade_type;
    float fade_step;

    uint8_t r_pin;
    uint8_t g_pin;
    uint8_t b_pin;
    uint8_t r_ch;
    uint8_t g_ch;
    uint8_t b_ch;
    uint8_t r_ch_2;
    uint8_t g_ch_2;
    uint8_t b_ch_2;
} led_t;

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/

/**
 * @brief Initializes the LED driver.
 * 
 * @param rgb_led 
 * @param red_pin 
 * @param green_pin 
 * @param blue_pin 
 * @return int 
 */
int led_init (led_t * rgb_led, uint8_t red_pin, uint8_t green_pin, uint8_t blue_pin);

/**
 * @brief Turns the RGB LED on with the choosen color.
 * 
 * @param rgb_led 
 * @param red_ch 
 * @param green_ch 
 * @param blue_ch 
 * @return int 
 */
int led_on (led_t * rgb_led, uint8_t red_ch, uint8_t green_ch, uint8_t blue_ch);

/**
 * @brief Turns the RGB LED off.
 * 
 * @param rgb_led 
 * @return int 
 */
int led_off (led_t * rgb_led);

/**
 * @brief Blinks the LED with the two choosen colors for a number of repetitions
 * and frequency.
 * 
 * @param rgb_led 
 * @param red_ch 
 * @param green_ch 
 * @param blue_ch 
 * @param red_ch_2 
 * @param green_ch_2 
 * @param blue_ch_2 
 * @return int 
 */
int led_blink (led_t * rgb_led, uint16_t freq, uint8_t nreps, uint8_t red_ch, uint8_t green_ch, 
              uint8_t blue_ch, uint8_t red_ch_2, uint8_t green_ch_2, uint8_t blue_ch_2);

/**
 * @brief Blinks the LED with the two choosen colors for a number of repetitions
 * and frequency, and blocks execution until blink is complete.
 * 
 * @param rgb_led 
 * @param red_ch 
 * @param green_ch 
 * @param blue_ch 
 * @param red_ch_2 
 * @param green_ch_2 
 * @param blue_ch_2 
 * @return int 
 */
int led_blink_block (led_t * rgb_led, uint16_t freq, uint8_t nreps, uint8_t red_ch, uint8_t green_ch, 
              uint8_t blue_ch, uint8_t red_ch_2, uint8_t green_ch_2, uint8_t blue_ch_2);              

/**
 * @brief Turn on the LED with a fade in effect.
 * 
 * @param rgb_led 
 * @param time Fade duration in seconds
 * @param fade_type
 * @param red_ch 
 * @param green_ch 
 * @param blue_ch 
 * @param red_ch_2 
 * @param green_ch_2 
 * @param blue_ch_2 
 * @return int 
 */
int led_fade (led_t * rgb_led, uint16_t time, fade_type_t fade_type, uint8_t red_ch, uint8_t green_ch, 
              uint8_t blue_ch);

/**
 * @brief Turn on the LED with a fade in effect, and blocks until effect is 
 * complete.
 * 
 * @param rgb_led 
 * @param time Fade duration in seconds
 * @param fade_type
 * @param red_ch 
 * @param green_ch 
 * @param blue_ch 
 * @param red_ch_2 
 * @param green_ch_2 
 * @param blue_ch_2 
 * @return int 
 */
int led_fade_block (led_t * rgb_led, uint16_t time, fade_type_t fade_type, uint8_t red_ch, uint8_t green_ch, 
              uint8_t blue_ch);            

#ifdef __cplusplus
}
#endif

#endif /* _LED_H */

/* end of file */