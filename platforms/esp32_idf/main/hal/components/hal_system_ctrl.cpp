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
#include <mooncake_log.h>
#include <memory>
#include <M5GFX.h>

using namespace mooncake;

/**
 * @brief 派生组件
 *
 */
class SystemControlDesktop : public hal_components::SystemControlBase {
public:
    std::uint32_t millis() override
    {
        return lgfx::millis();
    }

    void delay(std::uint32_t ms) override
    {
        lgfx::delay(ms);
    }
};

void HalEsp32::_system_ctrl_init()
{
    mclog::info("system ctrl init");

    // 创建组件实例
    _components.system_control = std::make_unique<SystemControlDesktop>();
}
