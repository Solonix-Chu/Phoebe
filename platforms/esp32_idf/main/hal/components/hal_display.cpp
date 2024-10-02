/**
 * @file hal_display.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../hal_esp32.h"
#include "../hal_config.h"
#include <mooncake_log.h>
#include <memory>
#include <M5GFX.h>
#include <Arduino.h>
#include <SPI.h>
// https://github.com/adafruit/Adafruit_SHARP_Memory_Display/blob/master/Adafruit_SharpMem.h

using namespace mooncake;

#define SHARPMEM_BIT_WRITECMD (0x01) // 0x80 in LSB format
#define SHARPMEM_BIT_VCOM     (0x02) // 0x40 in LSB format
#define SHARPMEM_BIT_CLEAR    (0x04) // 0x20 in LSB format

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) \
    {                       \
        int16_t t = a;      \
        a = b;              \
        b = t;              \
    }
#endif
#ifndef _swap_uint16_t
#define _swap_uint16_t(a, b) \
    {                        \
        uint16_t t = a;      \
        a = b;               \
        b = t;               \
    }
#endif

// 1<<n is a costly operation on AVR -- table usu. smaller & faster
static const uint8_t PROGMEM set[] = {1, 2, 4, 8, 16, 32, 64, 128},
                             clr[] = {(uint8_t)~1,  (uint8_t)~2,  (uint8_t)~4,  (uint8_t)~8,
                                      (uint8_t)~16, (uint8_t)~32, (uint8_t)~64, (uint8_t)~128};

class SharpMem {
public:
    void init()
    {
        // CS
        gpio_reset_pin((gpio_num_t)HAL_PIN_MLCD_SCS);
        gpio_set_direction((gpio_num_t)HAL_PIN_MLCD_SCS, GPIO_MODE_OUTPUT);
        gpio_set_pull_mode((gpio_num_t)HAL_PIN_MLCD_SCS, GPIO_PULLUP_PULLDOWN);

        // // SPI
        // auto config = _spi_bus.config();
        // config.freq_write = 1000000;
        // config.pin_sclk = HAL_PIN_MLCD_SCLK;
        // config.pin_mosi = HAL_PIN_MLCD_SI;
        // config.spi_mode = 0;
        // _spi_bus.config(config);
        // mclog::info("spi init: {}", _spi_bus.init());

        SPI.setFrequency(2000000);
        SPI.setBitOrder(SPI_LSBFIRST);
        SPI.begin(HAL_PIN_MLCD_SCLK, -1, HAL_PIN_MLCD_SI, -1);

        // SPISettings _spi_settings(1000000, SPI_LSBFIRST, SPI_MODE0);
        _spi_settings = new SPISettings(2000000, SPI_LSBFIRST, SPI_MODE0);

        // Set the vcom bit to a defined state
        _sharpmem_vcom = SHARPMEM_BIT_VCOM;

        _sharpmem_buffer = (uint8_t*)malloc((HAL_SCREEN_WIDTH * HAL_SCREEN_HEIGHT) / 8);

        gpio_set_level((gpio_num_t)HAL_PIN_MLCD_SCS, 0);
        lgfx::delay(100);
        gpio_set_level((gpio_num_t)HAL_PIN_MLCD_SCS, 1);
        lgfx::delay(100);
        gpio_set_level((gpio_num_t)HAL_PIN_MLCD_SCS, 0);
        lgfx::delay(100);
    }

    void clear()
    {
        mclog::info("clear");

        memset(_sharpmem_buffer, 0xff, (HAL_SCREEN_WIDTH * HAL_SCREEN_HEIGHT) / 8);

        // _spi_bus.beginTransaction();
        SPI.beginTransaction(*_spi_settings);

        // lgfx::gpio_hi(HAL_PIN_MLCD_SCS);
        gpio_set_level((gpio_num_t)HAL_PIN_MLCD_SCS, 1);

        // Send the clear screen command rather than doing a HW refresh (quicker)
        uint8_t data[2] = {(uint8_t)(_sharpmem_vcom | SHARPMEM_BIT_CLEAR), 0x00};
        // _spi_bus.writeBytes(data, 2, false, false);
        SPI.transfer(data, 2);

        toggle_vcom();

        // lgfx::gpio_lo(HAL_PIN_MLCD_SCS);
        gpio_set_level((gpio_num_t)HAL_PIN_MLCD_SCS, 0);

        // _spi_bus.endTransaction();
        SPI.endTransaction();
    }

    void refresh()
    {
        mclog::info("refresh");

        uint16_t i, currentline;

        // _spi_bus.beginTransaction();
        SPI.beginTransaction(*_spi_settings);

        // Send the write command
        // lgfx::gpio_hi(HAL_PIN_MLCD_SCS);
        gpio_set_level((gpio_num_t)HAL_PIN_MLCD_SCS, 1);

        // uint8_t data = _sharpmem_vcom | SHARPMEM_BIT_WRITECMD;
        // _spi_bus.writeBytes(&data, 1, false, false);

        SPI.transfer(_sharpmem_vcom | SHARPMEM_BIT_WRITECMD);

        toggle_vcom();

        uint8_t bytes_per_line = HAL_SCREEN_WIDTH / 8;
        uint16_t totalbytes = (HAL_SCREEN_WIDTH * HAL_SCREEN_HEIGHT) / 8;

        for (i = 0; i < totalbytes; i += bytes_per_line) {
            uint8_t line[bytes_per_line + 2];

            // Send address byte
            currentline = ((i + 1) / (HAL_SCREEN_WIDTH / 8)) + 1;
            line[0] = currentline;
            // copy over this line
            memcpy(line + 1, _sharpmem_buffer + i, bytes_per_line);
            // Send end of line
            line[bytes_per_line + 1] = 0x00;
            // send it!
            // spidev->transfer(line, bytes_per_line + 2);
            // _spi_bus.writeBytes(line, bytes_per_line + 2, false, false);
            SPI.transfer(line, bytes_per_line + 2);
        }

        // Send another trailing 8 bits for the last line
        // spidev->transfer(0x00);
        // digitalWrite(_cs, LOW);
        // spidev->endTransaction();

        // data = 0x00;
        // _spi_bus.writeBytes(&data, 1, false, false);
        SPI.transfer(0x00);
        // lgfx::gpio_lo(HAL_PIN_MLCD_SCS);
        gpio_set_level((gpio_num_t)HAL_PIN_MLCD_SCS, 0);
        // _spi_bus.endTransaction();
        SPI.endTransaction();
    }

    void clearBuffer()
    {
        memset(_sharpmem_buffer, 0xff, (HAL_SCREEN_WIDTH * HAL_SCREEN_HEIGHT) / 8);
    }

    void clearBuffer2()
    {
        memset(_sharpmem_buffer, 0x00, (HAL_SCREEN_WIDTH * HAL_SCREEN_HEIGHT) / 8);
    }

    void drawPixel(int16_t x, int16_t y, uint16_t color)
    {
        // mclog::info("draw pixel {} {}", x, y, color);

        if ((x < 0) || (x >= HAL_SCREEN_WIDTH) || (y < 0) || (y >= HAL_SCREEN_HEIGHT))
            return;

        uint8_t rotation = 0;
        switch (rotation) {
            case 1:
                _swap_int16_t(x, y);
                x = HAL_SCREEN_WIDTH - 1 - x;
                break;
            case 2:
                x = HAL_SCREEN_WIDTH - 1 - x;
                y = HAL_SCREEN_HEIGHT - 1 - y;
                break;
            case 3:
                _swap_int16_t(x, y);
                y = HAL_SCREEN_HEIGHT - 1 - y;
                break;
        }

        if (color) {
            _sharpmem_buffer[(y * HAL_SCREEN_WIDTH + x) / 8] |= pgm_read_byte(&set[x & 7]);
        } else {
            _sharpmem_buffer[(y * HAL_SCREEN_WIDTH + x) / 8] &= pgm_read_byte(&clr[x & 7]);
        }
    }

private:
    // lgfx::Bus_SPI _spi_bus;
    SPISettings* _spi_settings;
    uint8_t* _sharpmem_buffer = NULL;
    uint8_t _sharpmem_vcom;

    void toggle_vcom()
    {
        do {
            _sharpmem_vcom = _sharpmem_vcom ? 0x00 : SHARPMEM_BIT_VCOM;
        } while (0);
    }
};

/**
 * @brief 派生组件
 *
 */
class DisplayEsp32 : public hal_components::DisplayM5GFXBase {
public:
    bool init() override
    {
        return true;
    }

    LGFX_Device& display() override
    {
        return *_display;
    }

    LGFX_Sprite& canvas() override
    {
        return *_canvas;
    }

    void updateCanvas() override
    {
        _canvas->pushSprite(0, 0);
    }

private:
    std::unique_ptr<LGFX_Device> _display;
    std::unique_ptr<LGFX_Sprite> _canvas;
};

void HalEsp32::_display_init()
{
    mclog::info("displat init");

    initArduino();

    // lgfx::pinMode(HAL_PIN_PWR_HOLD, lgfx::pin_mode_t::output);
    // lgfx::gpio_hi(HAL_PIN_PWR_HOLD);
    // lgfx::delay(100);

    // // 创建组件实例
    // _components.display_m5gfx = std::make_unique<DisplayEsp32>();
    // _components.display_m5gfx->init();

    auto mcld = new SharpMem;
    mcld->init();
    mcld->clear();
    // mcld->clearBuffer();
    // mcld->refresh();

    /* -------------------------------------------------------------------------- */
    /*                                    Test                                    */
    /* -------------------------------------------------------------------------- */
    while (1) {
        mcld->clearBuffer();
        int y = 0;
        for (int x = 0; x < HAL_SCREEN_WIDTH; x++) {
            mcld->drawPixel(x, y, 1);
            y++;
        }
        mcld->refresh();
        lgfx::delay(1000);

        mcld->clearBuffer();
        y = 0;
        for (int x = 0; x < HAL_SCREEN_WIDTH; x++) {
            mcld->drawPixel(x, y, 0);
            y++;
        }
        mcld->refresh();
        lgfx::delay(1000);

        // mcld->clear();
        // // mcld->refresh();
        // lgfx::delay(1000);

        // // mcld->clear();
        // mcld->clearBuffer();
        // mcld->refresh();
        // lgfx::delay(1000);

        // mcld->clearBuffer2();
        // mcld->refresh();
        // lgfx::delay(1000);
    }
}
