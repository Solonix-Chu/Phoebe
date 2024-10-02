/**
 * @file panel_sharpe_mlcd.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "panel_sharpe_mlcd.h"
// https://www.sharpsde.com/fileadmin/products/Displays/Specs/LS013B7DH05_25Jan24_Spec_LD-2023X06.pdf
// https://github.com/adafruit/Adafruit_SHARP_Memory_Display/blob/master/Adafruit_SharpMem.h

using namespace lgfx;

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

void PanelSharpMlcd::mlcd_init()
{
    // SPI
    SPI.setFrequency(2000000);
    SPI.setBitOrder(SPI_LSBFIRST);
    SPI.begin(_data.pin_sclk, -1, _data.pin_si, -1);
    _data.spi_settings = std::make_unique<SPISettings>(2000000, SPI_LSBFIRST, SPI_MODE0);

    // Set the vcom bit to a defined state
    _data.sharpmem_vcom = SHARPMEM_BIT_VCOM;

    _data.sharpmem_buffer = std::make_unique<uint8_t>((_data.screen_width * _data.screen_height) / 8);

    // 片选脚
    lgfxPinMode(_data.pin_scs, pin_mode_t::output);
    gpio_lo(_data.pin_scs);
}

void PanelSharpMlcd::toggle_vcom()
{
    do {
        _data.sharpmem_vcom = _data.sharpmem_vcom ? 0x00 : SHARPMEM_BIT_VCOM;
    } while (0);
}

void PanelSharpMlcd::mcld_clear_screen() {}

void PanelSharpMlcd::mlcd_refresh_screen() {}

void PanelSharpMlcd::mlcd_clear_buffer()
{
    memset(_data.sharpmem_buffer.get(), 0xff, (_data.screen_width * _data.screen_height) / 8);
}

void PanelSharpMlcd::mlcd_draw_pixel(int16_t x, int16_t y, uint16_t color) {}

/* -------------------------------------------------------------------------- */
/*                                 LGFX Panel                                 */
/* -------------------------------------------------------------------------- */

bool PanelSharpMlcd::init(bool use_reset)
{
    mlcd_init();
    return true;
}

void PanelSharpMlcd::beginTransaction(void) {}

void PanelSharpMlcd::endTransaction(void) {}

void PanelSharpMlcd::setRotation(uint_fast8_t r) {}

color_depth_t PanelSharpMlcd::setColorDepth(color_depth_t depth)
{
    _write_depth = color_depth_t::rgb565_2Byte;
    _read_depth = color_depth_t::rgb565_2Byte;
    return color_depth_t::rgb565_2Byte;
}

void PanelSharpMlcd::writeBlock(uint32_t rawcolor, uint32_t len) {}

void PanelSharpMlcd::setWindow(uint_fast16_t xs, uint_fast16_t ys, uint_fast16_t xe, uint_fast16_t ye) {}

void PanelSharpMlcd::drawPixelPreclipped(uint_fast16_t x, uint_fast16_t y, uint32_t rawcolor) {}

void PanelSharpMlcd::writeFillRectPreclipped(uint_fast16_t x,
                                             uint_fast16_t y,
                                             uint_fast16_t w,
                                             uint_fast16_t h,
                                             uint32_t rawcolor)
{
}
void PanelSharpMlcd::writeImage(uint_fast16_t x,
                                uint_fast16_t y,
                                uint_fast16_t w,
                                uint_fast16_t h,
                                pixelcopy_t* param,
                                bool use_dma)
{
}

void PanelSharpMlcd::writePixels(pixelcopy_t* param, uint32_t len, bool use_dma) {}
