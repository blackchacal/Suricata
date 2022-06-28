/*****************************************************************************
 *                                                                           *
 * \file led.c                                                               *
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

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/

#include <stddef.h>

#include <Arduino.h>
#include "SAMDTimerInterrupt.h"

#include "led.h"
#include "logger.h"

/*****************************************************************************
 * Macros                                                                    *    
 *****************************************************************************/

/**
 * @def LED_POLARITY
 * If zero LED is common anode, 1 for common cathode.
 */
#define LED_POLARITY  1

/**
 * LED signal is inverted because the LEDs are controlled via a MOSFET
 */
#if LED_POLARITY == 0
#define SET_LED HIGH
#define CLR_LED LOW
#define DUTY_100 255
#define DUTY_0 0
#else
#define SET_LED LOW
#define CLR_LED HIGH
#define DUTY_100 0
#define DUTY_0 255
#endif

#define LED_TIMER_INTERVAL_MS   (10L) /* 10 ms */

/*****************************************************************************
 * Static Data                                                               *
 *****************************************************************************/
  
SAMDTimer ITimerLED(LED_TIMER);

uint8_t blink_timer_cnt = 0;
uint8_t nreps_cnt = 0;

/*****************************************************************************
 * Public Data                                                               *
 *****************************************************************************/

extern led_t rgb_led;

/*****************************************************************************
 * Private Function Prototypes                                               *
 *****************************************************************************/

uint8_t led_convert_ch_val (uint8_t ch_val);

void TimerHandler0(void);

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/

/**
 * @brief Initializes the LED driver.
 */
int led_init (led_t * rgb_led, uint8_t red_pin, uint8_t green_pin, uint8_t blue_pin)
{
    int err = ERR_OK;

    if (rgb_led == NULL)
    {
        err = ERR_LED_NULL_POINTER;
    }
    if ((red_pin > 12) || (green_pin > 12) || (blue_pin > 12))
    {
        err = ERR_LED_INVALID_PIN_NUMBER;
    }
    else
    {
        pinMode(red_pin, OUTPUT);
        pinMode(green_pin, OUTPUT);
        pinMode(blue_pin, OUTPUT);

        /* Disable LEDs */
        digitalWrite(red_pin, CLR_LED);
        digitalWrite(green_pin, CLR_LED);
        digitalWrite(blue_pin, CLR_LED);

        rgb_led->freq = 0;
        rgb_led->nreps = 0;
        rgb_led->is_blink = false;
        rgb_led->blink_ch = 0;

        rgb_led->r_pin = red_pin;
        rgb_led->g_pin = green_pin;
        rgb_led->b_pin = blue_pin;
        rgb_led->r_ch = DUTY_0;
        rgb_led->g_ch = DUTY_0;
        rgb_led->b_ch = DUTY_0;
        rgb_led->r_ch_2 = DUTY_0;
        rgb_led->g_ch_2 = DUTY_0;
        rgb_led->b_ch_2 = DUTY_0;

        // Setup blink timer Interval in microsecs
        if (!ITimerLED.attachInterruptInterval_MS(LED_TIMER_INTERVAL_MS, TimerHandler0))
        {
            err = ERR_LED_FAILED_INIT_TIMER;
        }
    }

    return err;
}

/**
 * @brief Turns the RGB LED on with the choosen color.
 */
int led_on (led_t * rgb_led, uint8_t red_ch, uint8_t green_ch, uint8_t blue_ch)
{
    int err = ERR_OK;

    if (rgb_led == NULL)
    {
        err = ERR_LED_NULL_POINTER;
    }
    else
    {
        analogWrite(rgb_led->r_pin, led_convert_ch_val(red_ch));
        analogWrite(rgb_led->g_pin, led_convert_ch_val(green_ch));
        analogWrite(rgb_led->b_pin, led_convert_ch_val(blue_ch));
    }

    return err;
}

/**
 * @brief Turns the RGB LED off.
 */
int led_off (led_t * rgb_led)
{
    int err = ERR_OK;

    if (rgb_led == NULL)
    {
        err = ERR_LED_NULL_POINTER;
    }
    else
    {
        rgb_led->r_ch = DUTY_0;
        rgb_led->g_ch = DUTY_0;
        rgb_led->b_ch = DUTY_0;

        rgb_led->is_blink = false;
        
        /**
         * Reset pin mode to disable PWM timers.
         * Just using analogWrite with value 0 was not 
         * working. PWM was still on.
         */
        pinMode(rgb_led->r_pin, OUTPUT);
        pinMode(rgb_led->g_pin, OUTPUT);
        pinMode(rgb_led->b_pin, OUTPUT);

        digitalWrite(rgb_led->r_pin, CLR_LED);
        digitalWrite(rgb_led->g_pin, CLR_LED);
        digitalWrite(rgb_led->b_pin, CLR_LED);
    }

    return err;
}

/**
 * @brief Blinks the LED with the two choosen colors for a number of repetitions
 * and frequency.
 */
int led_blink (led_t * rgb_led, uint16_t freq, uint8_t nreps, uint8_t red_ch, uint8_t green_ch, 
              uint8_t blue_ch, uint8_t red_ch_2, uint8_t green_ch_2, uint8_t blue_ch_2)
{
    int err = ERR_OK;

    if (rgb_led == NULL)
    {
        err = ERR_LED_NULL_POINTER;
    }
    else
    {
        rgb_led->freq = freq;
        rgb_led->nreps = nreps;
        rgb_led->is_blink = true;

        rgb_led->r_ch = red_ch;
        rgb_led->g_ch = green_ch;
        rgb_led->b_ch = blue_ch;
        rgb_led->r_ch_2 = red_ch_2;
        rgb_led->g_ch_2 = green_ch_2;
        rgb_led->b_ch_2 = blue_ch_2;
    }

    return err;
}              

/**
 * @brief Processes LED blink timings.
 */
int led_process (led_t * rgb_led)
{

}

/*****************************************************************************
 * Private Functions                                                         *
 *****************************************************************************/

uint8_t led_convert_ch_val (uint8_t ch_val)
{
#if LED_POLARITY == 0
    return ch_val;
#else
    return ((-1) * ch_val + DUTY_0);
#endif
}

/*****************************************************************************
 * Interrupt Handlers                                                        *
 *****************************************************************************/

void TimerHandler0(void)
{
    if (rgb_led.is_blink)
    {
        /* Timer is @100 Hz. Cnt = (100 / desired_blink_freq) / 2 */
        if (blink_timer_cnt % (50 / rgb_led.freq) == 0)
        {
            if (rgb_led.blink_ch == 0)
            {
                led_on(&rgb_led, rgb_led.r_ch, rgb_led.g_ch, rgb_led.b_ch);
                rgb_led.blink_ch = 1;
            }
            else
            {
                led_on(&rgb_led, rgb_led.r_ch_2, rgb_led.g_ch_2, rgb_led.b_ch_2);
                rgb_led.blink_ch = 0;
            }

            if (blink_timer_cnt != 0)
            {
                blink_timer_cnt = 0;    
                nreps_cnt++;
            }

            if ((rgb_led.nreps > 0) && (nreps_cnt >= 2 * rgb_led.nreps))
            {
                led_off(&rgb_led);
            }
        }
    }
    blink_timer_cnt++;
}