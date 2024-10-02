/**
 * @file sharpe_mlcd.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <memory>

class SharpeMlcd {
public:
    struct Config_t {
        uint16_t screen_width = 144;
        uint16_t screen_height = 168;
        int8_t pin_scs = -1;
        int8_t pin_sclk = -1;
        int8_t pin_si = -1;
        uint8_t rotation = 0;
        uint32_t spi_clk_freq = 1000000;
    };

    Config_t& setConfig()
    {
        return _config;
    }

    bool init();
    void clearScreen();
    void refreshScreen();
    void clearBuffer();
    void fillBufferBlack();
    void drawPixel(int16_t x, int16_t y, uint16_t color);

private:
    Config_t _config;
    std::unique_ptr<SPISettings> _spi_settings;
    std::unique_ptr<uint8_t> _sharpmem_buffer;
    uint8_t _sharpmem_vcom = 0;

    void toggle_vcom();
};
