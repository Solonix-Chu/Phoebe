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
#include "freertos/projdefs.h"
#include <mooncake_log.h>
#include <memory>
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

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

void HalEsp32::system_ctrl_init()
{
    mclog::info("system ctrl init");

    // 创建组件实例
    _components.system_control = std::make_unique<SystemControlEsp32>();
}
