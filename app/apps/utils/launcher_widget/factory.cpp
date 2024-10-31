/**
 * @file factory.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "launcher_widget.h"
#include <memory>
#include <mooncake.h>

using namespace mooncake;

int launcher_widget_factory::create(widget::WidgetBase* canvas, const std::string& widgetType)
{
    if (widgetType == "time") {
        return GetMooncake().createExtension(std::make_unique<LauncherWidgetTime>(canvas));
    } else if (widgetType == "date") {
        return GetMooncake().createExtension(std::make_unique<LauncherWidgetDate>(canvas));
    } else if (widgetType == "battery") {
        return GetMooncake().createExtension(std::make_unique<LauncherWidgetBattery>(canvas));
    } else if (widgetType == "weather") {
    }
    return -1;
}
