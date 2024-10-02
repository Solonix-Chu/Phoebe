/**
 * @file hal_display.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../hal_desktop.h"
#include "../hal_config.h"
#include <mooncake_log.h>
#include <memory>

using namespace mooncake;

/**
 * @brief 派生组件
 *
 */
class DisplayDesktop : public hal_components::DisplayBase {
public:
private:
};

void HalDesktop::display_init()
{
    mclog::info("displat init");

    // 创建组件实例
    _components.display = std::make_unique<DisplayDesktop>();
}
