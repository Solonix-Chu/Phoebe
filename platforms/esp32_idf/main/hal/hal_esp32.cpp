/**
 * @file hal_esp32.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "hal_esp32.h"
#include "hal_config.h"
#include <mooncake_log.h>
#include <Arduino.h>
#include <lvgl.h>
#include <esp_timer.h>
#include "components/utils/sharpe_mlcd/sharpe_mlcd.h"
#include "components/system_ctrl/system_ctrl.h"

using namespace mooncake;

void HALESP32::init()
{
    initArduino();

    // 创建系统控制组件
    _components.system_control = std::make_unique<SystemControlArduino>();
    _components.system_control->init();

    display_init();
    lvgl_init();

    /* -------------------------------------------------------------------------- */
    /*                                    Test                                    */
    /* -------------------------------------------------------------------------- */
}

/* -------------------------------------------------------------------------- */
/*                                   Display                                  */
/* -------------------------------------------------------------------------- */

static SharpeMlcd* _sharp_mlcd = nullptr;

void HALESP32::display_init()
{
    mclog::info("display init");

    _sharp_mlcd = new SharpeMlcd;
    _sharp_mlcd->setConfig().screen_width = HAL_SCREEN_WIDTH;
    _sharp_mlcd->setConfig().screen_height = HAL_SCREEN_HEIGHT;
    _sharp_mlcd->setConfig().pin_scs = HAL_PIN_MLCD_SCS;
    _sharp_mlcd->setConfig().pin_sclk = HAL_PIN_MLCD_SCLK;
    _sharp_mlcd->setConfig().pin_si = HAL_PIN_MLCD_SI;
    _sharp_mlcd->setConfig().spi_clk_freq = 4000000;
    _sharp_mlcd->setConfig().rotation = 2;
    _sharp_mlcd->init();

    _sharp_mlcd->clearScreen();
}

/* -------------------------------------------------------------------------- */
/*                                    Lvgl                                    */
/* -------------------------------------------------------------------------- */

static void lvgl_flush_cb(lv_display_t* disp, const lv_area_t* area, uint8_t* px_map)
{
    // mclog::info("{} {} {} {}", area->x1, area->x2, area->y1, area->y2);
    // for (int i = 0; i < 20; i++) {
    //     mclog::info("{}", ((uint16_t*)px_map)[i]);
    // }

    _sharp_mlcd->copyBuffer((uint16_t*)px_map);
    _sharp_mlcd->refreshScreen();

    lv_display_flush_ready(disp);
}

static void lvgl_tick_timer(void* arg)
{
    (void)arg;
    lv_tick_inc(10);
}

void HALESP32::lvgl_init()
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
