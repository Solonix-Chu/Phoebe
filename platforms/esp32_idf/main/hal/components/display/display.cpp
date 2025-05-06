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
#include <lvgl.h>

SharpeMlcd* __get_sharp_mlcd();
uint8_t* __get_lvgl_buffer();

void DisplayMlcd::init()
{
    // Setting monochrome (1-bit) color depth for OLED
    setColorDepth(lgfx::color_depth_t::palette_1bit);
    // setBuffer((void*)__get_lvgl_buffer(), HAL_SCREEN_WIDTH, HAL_SCREEN_HEIGHT);
    createSprite(HAL_SCREEN_WIDTH, HAL_SCREEN_HEIGHT);
    
    // Set black background color for LVGL
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x000000), LV_PART_MAIN);
}

void DisplayMlcd::push_buffer_to_display(void* buffer)
{
    // For ESP32 implementation, would need to properly send monochrome data to OLED
    // This depends on your specific OLED driver (SSD1306, SH1106, etc.)
    // This is a placeholder - you'll need to replace with actual OLED implementation
    __get_sharp_mlcd()->copyMonoBuffer((uint8_t*)buffer, HAL_SCREEN_WIDTH, HAL_SCREEN_HEIGHT);
    __get_sharp_mlcd()->refreshScreen();
}
