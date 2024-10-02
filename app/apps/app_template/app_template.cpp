/**
 * @file app_template.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date <date></date>
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app_template.h"
#include "hal/hal.h"
#include <mooncake.h>
#include <mooncake_log.h>
#include <lvgl.h>
#include <src/core/lv_obj_style_gen.h>
#include <src/display/lv_display.h>
#include <src/misc/lv_color.h>
#include <src/misc/lv_timer.h>
#include <lv_demos.h>
#include <widgets/lv_demo_widgets.h>
#include <widgets/lv_example_widgets.h>

using namespace mooncake;

AppTemplate::AppTemplate()
{
    // 配置 App 信息
    setAppInfo().name = "AppTemplate";
}

void AppTemplate::onCreate()
{
    mclog::tagInfo(getAppInfo().name, "on create");

    // 打开自己
    open();
}

void AppTemplate::onOpen()
{
    mclog::tagInfo(getAppInfo().name, "on open");

    // lv_demo_widgets();
    lv_example_switch_1();

    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_white(), LV_STATE_DEFAULT);
}

void AppTemplate::onRunning()
{
    lv_timer_handler();
}

void AppTemplate::onClose()
{
    mclog::tagInfo(getAppInfo().name, "on close");
}

void AppTemplate::update_clock()
{
    if (GetHAL().SystemControl().millis() - _clock_time_count < 1000) {
        return;
    }

    _clock_time_count = GetHAL().SystemControl().millis();
}
