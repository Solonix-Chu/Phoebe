/**
 * @file hal_system_ctrl.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../hal_esp32.h"
#include "esp32-hal-gpio.h"
#include "freertos/projdefs.h"
#include <mooncake_log.h>
#include <memory>
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <Arduino.h>
#include <time.h>

using namespace mooncake;

/**
 * @brief 派生组件
 *
 */
class SystemControlEsp32 : public hal_components::SystemControlBase {
public:
    std::uint32_t millis() override
    {
        return esp_timer_get_time() / 1000;
    }

    void delay(std::uint32_t ms) override
    {
        vTaskDelay(pdMS_TO_TICKS(ms));
    }
};

static void _mission_destroy(void* param)
{
    pinMode(18, INPUT_PULLUP);

    while (1) {
        if (!digitalRead(18)) {
            // esp_restart();
            digitalWrite(4, 0);
        }
        delay(100);
    }
}

void HalEsp32::system_ctrl_init()
{
    mclog::info("system ctrl init");

    xTaskCreate(_mission_destroy, "bb", 4000, NULL, 10, NULL);

    tm set_time;
    set_time.tm_year = 2024 - 1900;
    set_time.tm_mon = 10 - 1;
    set_time.tm_mday = 2;
    set_time.tm_wday = 3;
    set_time.tm_hour = 20;
    set_time.tm_min = 8;
    set_time.tm_sec = 0;

    // 将 tm 转换为 time_t
    time_t time_seconds = mktime(&set_time);

    // 设置 timeval 结构
    struct timeval tv;
    tv.tv_sec = time_seconds; // 设置秒
    tv.tv_usec = 0;           // 设置微秒
    settimeofday(&tv, nullptr);

    // 创建组件实例
    _components.system_control = std::make_unique<SystemControlEsp32>();
}
