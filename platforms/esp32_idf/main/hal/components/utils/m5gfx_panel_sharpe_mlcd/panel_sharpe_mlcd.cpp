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
// #include <mooncake_log.h>

using namespace lgfx;
// using namespace mooncake;

bool PanelSharpMlcd::init(bool use_reset)
{
    // mclog::info("panel init");

    _width = _cfg.panel_width;
    _height = _cfg.panel_height;

    return true;
}

void PanelSharpMlcd::beginTransaction(void)
{
    // mclog::info("begin");
}

void PanelSharpMlcd::endTransaction(void)
{
    // mclog::info("end");
}

void PanelSharpMlcd::setRotation(uint_fast8_t r)
{
    // mclog::info("set r: {}", r);
    _rotation = r;
    _sharp_mlcd->setConfig().rotation = r;
}

color_depth_t PanelSharpMlcd::setColorDepth(color_depth_t depth)
{
    _write_depth = color_depth_t::rgb565_2Byte;
    _read_depth = color_depth_t::rgb565_2Byte;
    return color_depth_t::rgb565_2Byte;
}

void PanelSharpMlcd::writeBlock(uint32_t rawcolor, uint32_t len)
{
    // mclog::info("write b");
}

void PanelSharpMlcd::setWindow(uint_fast16_t xs, uint_fast16_t ys, uint_fast16_t xe, uint_fast16_t ye)
{
    // mclog::info("set win");
}

void PanelSharpMlcd::drawPixelPreclipped(uint_fast16_t x, uint_fast16_t y, uint32_t rawcolor) {}

void PanelSharpMlcd::writeFillRectPreclipped(uint_fast16_t x,
                                             uint_fast16_t y,
                                             uint_fast16_t w,
                                             uint_fast16_t h,
                                             uint32_t rawcolor)
{
    // mclog::info("write fill rect pre {}", rawcolor);
}

// 只用全屏画布的话重写这一个就行了，懒得优化了
void PanelSharpMlcd::writeImage(uint_fast16_t x,
                                uint_fast16_t y,
                                uint_fast16_t w,
                                uint_fast16_t h,
                                pixelcopy_t* param,
                                bool use_dma)
{
    // mclog::info("write image: {} {} {} {}", x, y, w, h);
    // for (int i = 0; i < 6; i++) {
    //     mclog::info("{}", ((uint8_t*)param->src_data)[i]);
    // }

    // auto bytes = param->dst_bits >> 3;
    // mclog::info("bytes: {}", bytes);

    _sharp_mlcd->copyBuffer((uint16_t*)param->src_data);
    _sharp_mlcd->refreshScreen();
}

void PanelSharpMlcd::writePixels(pixelcopy_t* param, uint32_t len, bool use_dma)
{
    // mclog::info("write pi");
}
