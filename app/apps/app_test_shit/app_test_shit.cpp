/**
 * @file app_test_shit.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-14
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app_test_shit.h"
#include <mooncake_log.h>
#include <hal/hal.h>
#include <lvgl.h>
#include <src/core/lv_obj.h>
#include <src/display/lv_display.h>
#include "../utils/smooth_lv_obj/smooth_lv_obj.h"
#include "../utils/math/math.h"
#include "core/easing_path/easing_path.h"
#include "core/types/types.h"

using namespace mooncake;
using namespace SmoothUIToolKit;
using namespace math;

#define _tag (getAppInfo().name)

AppTestShit::AppTestShit()
{
    // 配置 App 信息
    setAppInfo().name = "AppTestShit";
}

void AppTestShit::onCreate()
{
    mclog::tagInfo(_tag, "on create");

    // 打开自己
    open();
}

SmoothLvObj* _obj;

void AppTestShit::onOpen()
{
    mclog::tagInfo(_tag, "on open");

    _obj = new SmoothLvObj(lv_obj_create(lv_screen_active()));
    _obj->Size().jumpTo(50, 5);
    _obj->Size().setTransitionPath(EasingPath::easeOutBack);
    _obj->Size().setDuration(300);
    _obj->Size().moveTo(30, 120);
}

void AppTestShit::onRunning()
{
    HAL::BtnUpdate();
    if (HAL::BtnOk().wasClicked()) {
        Vector2D_t new_shit;
        new_shit.x = math::getRandomInt(0, 200);
        new_shit.y = math::getRandomInt(0, 200);
        mclog::info("new shit: {} {}", new_shit.x, new_shit.y);
        _obj->Size().setTransitionPath(EasingPath::easeOutBack);
        _obj->Size().setDuration(300);
        _obj->Size().moveTo(new_shit);
    }

    _obj->update();
    lv_timer_handler();
}

void AppTestShit::onClose()
{
    mclog::tagInfo(_tag, "on close");
}
