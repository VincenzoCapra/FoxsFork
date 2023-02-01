#ifndef _HDW_TFT_H_
#define _HDW_TFT_H_

#include <stdint.h>

#include "hal/gpio_types.h"
#include "hal/spi_types.h"
#include "driver/ledc.h"

#include "palette.h"

#if defined(CONFIG_ST7735_160x80)
    #define TFT_WIDTH  160
    #define TFT_HEIGHT 80
#elif defined(CONFIG_ST7735_128x160)
    #define TFT_WIDTH  160
    #define TFT_HEIGHT 128
#elif defined(CONFIG_ST7789_240x135)
    #define TFT_WIDTH  240
    #define TFT_HEIGHT 135
#elif defined(CONFIG_ST7789_240x240)
    #define TFT_WIDTH  240
    #define TFT_HEIGHT 240
#elif defined(CONFIG_GC9307_240x280)
    #define TFT_WIDTH  280
    #define TFT_HEIGHT 240
#else
    #error "Please pick a screen size"
#endif

/**
 * @brief This is a typedef for a function pointer passed to drawDisplayTft()
 * which will be called to draw a background image while the SPI transfer is
 * occurring. This will be called multiple times to draw multiple areas for
 * the current frame.
 *
 * @param x The X coordinate to start filling in
 * @param y The Y coordinate to start filling in
 * @param w The width of the background area to draw
 * @param h The height of the background area to draw
 * @param up The number of times this function has been called for the current frame (an incrementing number)
 * @param upNum The total number of times this will be called for the current frame
 */
typedef void (*fnBackgroundDrawCallback_t)(int16_t x, int16_t y, int16_t w, int16_t h, int16_t up, int16_t upNum);

void initTFT(spi_host_device_t spiHost, gpio_num_t sclk, gpio_num_t mosi, gpio_num_t dc, gpio_num_t cs, gpio_num_t rst,
             gpio_num_t backlight, bool isPwmBacklight, ledc_channel_t ledcChannel);
int setTFTBacklightBrightness(uint8_t intensity);
void disableTFTBacklight(void);
void enableTFTBacklight(void);

void setPxTft(int16_t x, int16_t y, paletteColor_t px);
paletteColor_t getPxTft(int16_t x, int16_t y);
paletteColor_t* getPxTftFramebuffer(void);
void clearPxTft(void);
void drawDisplayTft(fnBackgroundDrawCallback_t cb);

#endif
