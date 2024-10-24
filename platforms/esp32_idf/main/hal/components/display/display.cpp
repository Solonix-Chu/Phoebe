/**
 * @file display.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-24
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "display.h"
#include "../utils/sharpe_mlcd/sharpe_mlcd.h"
#include "../../hal_config.h"
#include <cstdint>

SharpeMlcd* __get_sharp_mlcd();
uint8_t* __get_lvgl_buffer();

void DisplayMlcd::init()
{
    setColorDepth(lgfx::color_depth_t::rgb565_nonswapped);
    // setBuffer((void*)__get_lvgl_buffer(), HAL_SCREEN_WIDTH, HAL_SCREEN_HEIGHT);
    createSprite(HAL_SCREEN_WIDTH, HAL_SCREEN_HEIGHT);
}

void DisplayMlcd::push_buffer_to_display(void* buffer)
{
    __get_sharp_mlcd()->copyBuffer((uint16_t*)buffer);
    __get_sharp_mlcd()->refreshScreen();
}
