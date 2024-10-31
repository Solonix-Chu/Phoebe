/**
 * @file date.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../launcher_widget.h"
#include "../../widget/widget.h"
#include <hal/hal.h>
#include <memory>
#include <mooncake_log.h>
#include <vector>

using namespace mooncake;
using namespace widget;

void LauncherWidgetDate::onCreate()
{
    _date_title = std::make_unique<WidgetLabel>(_canvas->get());
    _date_title->setAlign("lv_align_top_right");
    _date_title->setFont("RajdhaniBold16");
    _date_title->setPos(-8, 9);

    _date = std::make_unique<WidgetLabel>(_canvas->get());
    _date->setAlign("lv_align_top_right");
    _date->setFont("RajdhaniBold36");
    _date->setPos(-8, 27);

    onRunning();
}

void LauncherWidgetDate::onRunning()
{
    if (HAL::SysCtrl().millis() - _time_count > 1000) {
        time_t now;
        struct tm* tm_info;
        time(&now);
        tm_info = localtime(&now);

        const std::vector<const char*> week_day = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
        _string_buffer = fmt::format("{} {}.", tm_info->tm_year + 1900, week_day[tm_info->tm_wday]);
        _date_title->setText(_string_buffer.c_str());

        _string_buffer = fmt::format("{}/{}", tm_info->tm_mon + 1, tm_info->tm_mday);
        _date->setText(_string_buffer.c_str());

        _time_count = HAL::SysCtrl().millis();
    }
}
