/**
 * @file battery.cpp
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
#include "hal/components/battery_monitor.h"
#include <hal/hal.h>
#include <memory>
#include <mooncake_log.h>
#include <vector>

using namespace mooncake;
using namespace widget;

void LauncherWidgetBattery::onCreate()
{
    _bat_icon_shell = std::make_unique<WidgetBase>(_canvas->get());
    _bat_icon_shell->setAlign("lv_align_right_mid");
    _bat_icon_shell->setPos(-80, 0);
    _bat_icon_shell->setSize(25, 43);
    _bat_icon_shell->setRadius(7);

    _bat_icon_level = std::make_unique<WidgetBase>(_bat_icon_shell->get());
    _bat_icon_level->setAlign("lv_align_bottom_mid");
    _bat_icon_level->setPos(0, -2);
    _bat_icon_level->setRadius(4);
    _bat_icon_level->setBgColor("#000000");
    set_battery_icon_level(100);

    _bat_title = std::make_unique<WidgetLabel>(_canvas->get());
    _bat_title->setAlign("lv_align_top_right");
    _bat_title->setFont("RajdhaniBold16");
    _bat_title->setText("BATTERY");
    _bat_title->setPos(-8, 12);

    _bat_level = std::make_unique<WidgetLabel>(_canvas->get());
    _bat_level->setAlign("lv_align_top_right");
    _bat_level->setFont("RajdhaniBold24");
    _bat_level->setPos(-8, 32);

    onRunning();
}

void LauncherWidgetBattery::onRunning()
{
    if (HAL::SysCtrl().millis() - _time_count > 1000) {

        auto bat_level = (int)HAL::BatteryMonitor().percent();
        bool is_charging = HAL::BatteryMonitor().state() == BatteryState::Charging;
        bat_level = 66;
        is_charging = true;

        _string_buffer = fmt::format("{}%", bat_level);
        _bat_level->setText(_string_buffer.c_str());

        int bat_icon_level = bat_level;
        if (is_charging) {
            if (_last_charging_level < 0) {
                _last_charging_level = bat_level;
            } else {
                _last_charging_level += 5;
                if (_last_charging_level > 105) {
                    _last_charging_level = bat_level;
                }
            }
            bat_icon_level = _last_charging_level;
        }
        set_battery_icon_level(bat_icon_level);

        _time_count = HAL::SysCtrl().millis();
    }
}

void LauncherWidgetBattery::set_battery_icon_level(float batteryLevel)
{
    int height = 35 * batteryLevel / 100;
    _bat_icon_level->setSize(17, height);
}
