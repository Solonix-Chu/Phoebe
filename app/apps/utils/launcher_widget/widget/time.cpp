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
#include "../launcher_widget.h"
#include "../../widget/widget.h"
#include <hal/hal.h>
#include <memory>
#include <mooncake_log.h>

#include <mooncake.h>

using namespace mooncake;
using namespace widget;

void LauncherWidgetTime::onCreate()
{
    _clock = std::make_unique<WidgetClock>(_canvas->get());
    _clock->centerX = 30;
    _clock->centerY = 30;
    _clock->hourHandLength = 13;
    _clock->minHandLength = 20;
    _clock->secHandLength = 30;

    _time_title = std::make_unique<WidgetLabel>(_canvas->get());
    _time_title->setText("TIME");
    _time_title->setAlign("lv_align_top_right");
    _time_title->setFont("RajdhaniBold16");
    _time_title->setPos(-8, 12);

    _time = std::make_unique<WidgetLabel>(_canvas->get());
    _time->setText("22:33");
    _time->setAlign("lv_align_top_right");
    _time->setFont("RajdhaniBold24");
    _time->setPos(-8, 32);

    _clock->update();
}

void LauncherWidgetTime::onRunning()
{
    if (HAL::SysCtrl().millis() - _time_count > 1000) {
        _clock->update();

        time_t now;
        struct tm* tm_info;
        time(&now);
        tm_info = localtime(&now);
        _string_buffer = fmt::format("{:02d}:{:02d}", tm_info->tm_hour, tm_info->tm_min);
        _time->setText(_string_buffer.c_str());

        _time_count = HAL::SysCtrl().millis();
    }
}
