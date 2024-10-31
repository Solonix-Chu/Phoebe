/**
 * @file launcher_widget_ability.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../widget/widget.h"
#include <cstdint>
#include <memory>
#include <mooncake.h>

class LauncherWidgetAbilityBase : public mooncake::WorkerAbility {
public:
    LauncherWidgetAbilityBase(widget::WidgetBase* canvas) : _canvas(canvas) {}

protected:
    widget::WidgetBase* _canvas = NULL;
};

class LauncherWidgetTime : public LauncherWidgetAbilityBase {
public:
    LauncherWidgetTime(widget::WidgetBase* canvas) : LauncherWidgetAbilityBase(canvas) {}

    void onCreate() override;
    void onRunning() override;

private:
    uint32_t _time_count = 0;
    std::unique_ptr<widget::WidgetClock> _clock;
    std::unique_ptr<widget::WidgetLabel> _time_title;
    std::unique_ptr<widget::WidgetLabel> _time;
    std::string _string_buffer;
};

class LauncherWidgetDate : public LauncherWidgetAbilityBase {
public:
    LauncherWidgetDate(widget::WidgetBase* canvas) : LauncherWidgetAbilityBase(canvas) {}

    void onCreate() override;
    void onRunning() override;

private:
    uint32_t _time_count = 0;
    std::unique_ptr<widget::WidgetLabel> _date_title;
    std::unique_ptr<widget::WidgetLabel> _date;
    std::string _string_buffer;
};

class LauncherWidgetBattery : public LauncherWidgetAbilityBase {
public:
    LauncherWidgetBattery(widget::WidgetBase* canvas) : LauncherWidgetAbilityBase(canvas) {}

    void onCreate() override;
    void onRunning() override;

private:
    uint32_t _time_count = 0;
    std::unique_ptr<widget::WidgetBase> _bat_icon_shell;
    std::unique_ptr<widget::WidgetBase> _bat_icon_level;
    std::unique_ptr<widget::WidgetLabel> _bat_title;
    std::unique_ptr<widget::WidgetLabel> _bat_level;
    std::string _string_buffer;
    int _last_charging_level = -1;

    void set_battery_icon_level(float batteryLevel);
};
