/*! \file hdw-led.h
 *
 * \section led_design Design Philosophy
 *
 * LED code is based on <a
 * href="https://github.com/espressif/esp-idf/tree/release/v5.0/examples/peripherals/rmt/led_strip">Espressif's RMT
 * Transmit Example - LED Strip</a>.
 *
 * Each LED has a red, green, and blue component. Each component ranges from 0 to 255.
 *
 * LED brightness is not linear, so differences in brightness are more noticeable between small values (like 1 and 10)
 * than between large values (like 240 and 250).
 *
 * The number of LEDs are configurable by "idf.py menuconfig" and is accessible in code with the CONFIG_NUM_LEDS macro.
 *
 * \section led_usage Usage
 *
 * You don't need to call initLeds() or deinitLeds(). The system does so at the appropriate time.
 *
 * You should call setLeds() any time you want to set the LEDs. There is no buffer, so the LEDs are immediately set to
 * the values given. setLeds() takes a pointer to an array of ::led_t as an argument. These structs each have a red,
 * green, and blue field.
 *
 * \section led_example Example
 *
 * Set the LEDs to a rough rainbow:
 * \code{.c}
 * #include "hdw-led.h"
 *
 * led_t leds[CONFIG_NUM_LEDS] = {0};
 * for (uint8_t i = 0; i < CONFIG_NUM_LEDS; i++)
 * {
 *     leds[i].r = (255 * ((i + 0) % CONFIG_NUM_LEDS)) / (CONFIG_NUM_LEDS - 1);
 *     leds[i].g = (255 * ((i + 3) % CONFIG_NUM_LEDS)) / (CONFIG_NUM_LEDS - 1);
 *     leds[i].b = (255 * ((i + 6) % CONFIG_NUM_LEDS)) / (CONFIG_NUM_LEDS - 1);
 * }
 * setLeds(leds, CONFIG_NUM_LEDS);
 * \endcode
 */

#ifndef _HDW_LED_H_
#define _HDW_LED_H_

#include <stdint.h>

#include <esp_err.h>
#include <hal/gpio_types.h>

typedef struct __attribute__((packed))
{
    uint8_t g; //!< The green component, 0-255
    uint8_t r; //!< The red component, 0-255
    uint8_t b; //!< The blue component, 0-255
} led_t;

esp_err_t initLeds(gpio_num_t gpio);
esp_err_t deinitLeds(void);
esp_err_t setLeds(led_t* leds, uint8_t numLeds);

#endif