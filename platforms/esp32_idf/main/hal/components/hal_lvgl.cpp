/**
 * @file hal_lvgl.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../hal_esp32.h"
#include "../hal_config.h"
#include "utils/sharpe_mlcd/sharpe_mlcd.h"
#include <mooncake_log.h>
#include <lvgl.h>
#include <esp_timer.h>
#include <stdint.h>

using namespace mooncake;

extern SharpeMlcd* __get_sharpe_lcd();

static void lvgl_flush_cb(lv_display_t* disp, const lv_area_t* area, uint8_t* px_map)
{
    // mclog::info("{} {} {} {}", area->x1, area->x2, area->y1, area->y2);
    // for (int i = 0; i < 20; i++) {
    //     mclog::info("{}", ((uint16_t*)px_map)[i]);
    // }

    __get_sharpe_lcd()->copyBuffer((uint16_t*)px_map);
    __get_sharpe_lcd()->refreshScreen();

    lv_display_flush_ready(disp);
}

static void lvgl_tick_timer(void* arg)
{
    (void)arg;
    lv_tick_inc(10);
}

void HalEsp32::lvgl_init()
{
    mclog::info("lvgl init");

    lv_init();

    // Display
    mclog::info("create lvgl display");
    auto display = lv_display_create(HAL_SCREEN_WIDTH, HAL_SCREEN_HEIGHT);
    lv_display_set_flush_cb(display, lvgl_flush_cb);

    mclog::info("create display buffer");
    static uint8_t* buf1 = (uint8_t*)malloc(HAL_SCREEN_WIDTH * HAL_SCREEN_HEIGHT * sizeof(uint16_t));
    lv_display_set_buffers(display, (void*)buf1, NULL, HAL_SCREEN_WIDTH * HAL_SCREEN_HEIGHT * sizeof(uint16_t),
                           LV_DISPLAY_RENDER_MODE_FULL);

    // Tick
    mclog::info("create lvgl tick timer");
    const esp_timer_create_args_t periodic_timer_args = {.callback = &lvgl_tick_timer, .name = "lvgl_tick_timer"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 10 * 1000));
}
