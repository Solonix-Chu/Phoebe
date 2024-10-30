/**
 * @file time.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../launcher_widget_ability.h"
#include <hal/hal.h>
#include <mooncake_log.h>

using namespace mooncake;
using namespace widget;

void LauncherWidgetTime::onCreate() {}

void LauncherWidgetTime::onRunning()
{
    if (HAL::SysCtrl().millis() - _time_count > 1000) {
        mclog::info("6");
        _time_count = HAL::SysCtrl().millis();
    }
}
