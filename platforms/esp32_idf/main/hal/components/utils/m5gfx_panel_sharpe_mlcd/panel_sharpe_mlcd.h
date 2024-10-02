/**
 * @file panel_sharpe_mlcd.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <M5GFX.h>
#include <Arduino.h>
#include <SPI.h>

namespace lgfx {

class PanelSharpMlcd : public Panel_Device {
public:
    PanelSharpMlcd(uint16_t screenWidth, uint16_t screenHeight, int8_t pinSCS, int8_t pinSCLK, int8_t pinSI)
    {
        _data.screen_width = screenWidth;
        _data.screen_height = screenHeight;
        _data.pin_scs = pinSCS;
        _data.pin_sclk = pinSCLK;
        _data.pin_si = pinSI;
    }

    void mlcd_init();
    void mcld_clear_screen();
    void mlcd_refresh_screen();
    void mlcd_clear_buffer();
    void mlcd_draw_pixel(int16_t x, int16_t y, uint16_t color);

    /* -------------------------------------------------------------------------- */
    /*                                 LGFX Panel                                 */
    /* -------------------------------------------------------------------------- */
    bool init(bool use_reset) override;
    void beginTransaction(void) override;
    void endTransaction(void) override;
    void setRotation(uint_fast8_t r);
    void waitDisplay(void) override {}
    bool displayBusy(void) override
    {
        return false;
    }
    color_depth_t setColorDepth(color_depth_t depth) override;
    void setInvert(bool invert) override {}
    void setSleep(bool flg) override {}
    void setPowerSave(bool) override {}
    void writeBlock(uint32_t rawcolor, uint32_t len) override;
    void setWindow(uint_fast16_t xs, uint_fast16_t ys, uint_fast16_t xe, uint_fast16_t ye) override;
    void drawPixelPreclipped(uint_fast16_t x, uint_fast16_t y, uint32_t rawcolor) override;
    void writeFillRectPreclipped(uint_fast16_t x,
                                 uint_fast16_t y,
                                 uint_fast16_t w,
                                 uint_fast16_t h,
                                 uint32_t rawcolor) override;
    void writeImage(uint_fast16_t x,
                    uint_fast16_t y,
                    uint_fast16_t w,
                    uint_fast16_t h,
                    pixelcopy_t* param,
                    bool use_dma) override;
    void writePixels(pixelcopy_t* param, uint32_t len, bool use_dma) override;
    uint32_t readCommand(uint_fast16_t, uint_fast8_t, uint_fast8_t) override
    {
        return 0;
    }
    uint32_t readData(uint_fast8_t, uint_fast8_t) override
    {
        return 0;
    }
    void readRect(uint_fast16_t x, uint_fast16_t y, uint_fast16_t w, uint_fast16_t h, void* dst, pixelcopy_t* param)
        override
    {
    }
    void setTilePattern(uint_fast8_t) {}

private:
    struct Data_t {
        // Config
        uint16_t screen_width = 0;
        uint16_t screen_height = 0;
        int8_t pin_scs = -1;
        int8_t pin_sclk = -1;
        int8_t pin_si = -1;
        uint8_t rotation = 0;

        // Buffer
        std::unique_ptr<SPISettings> spi_settings;
        std::unique_ptr<uint8_t> sharpmem_buffer;
        uint8_t sharpmem_vcom = 0;
    };
    Data_t _data;

    void toggle_vcom();
};

} // namespace lgfx
