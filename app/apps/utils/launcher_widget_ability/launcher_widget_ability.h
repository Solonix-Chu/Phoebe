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
#include <mooncake.h>

class LauncherWidgetAbilityBase : public mooncake::WorkerAbility {
public:
    LauncherWidgetAbilityBase(lv_obj_t* widgetParent) : _widget_parent(widgetParent) {}

private:
    lv_obj_t* _widget_parent = NULL;
};

class LauncherWidgetTime : public LauncherWidgetAbilityBase {
public:
    LauncherWidgetTime(lv_obj_t* widgetParent) : LauncherWidgetAbilityBase(widgetParent) {}

    void onCreate() override;
    void onRunning() override;

private:
    uint32_t _time_count = 0;
};
