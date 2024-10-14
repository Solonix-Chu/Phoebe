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
#include "../utils/smooth_lv_widgets/lv_obj.h"
#include "../utils/math/math.h"
#include "core/easing_path/easing_path.h"
#include "core/types/types.h"

using namespace mooncake;
using namespace SmoothUIToolKit;
using namespace math;
using namespace smooth_lv_widgets;

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

LvObj* _obj;

void AppTestShit::onOpen()
{
    mclog::tagInfo(_tag, "on open");

    _obj = new LvObj(lv_obj_create(lv_screen_active()));
    _obj->Size().jumpTo(50, 5);
    _obj->Size().setTransitionPath(EasingPath::easeOutBack);
    _obj->Size().setDuration(500);
    _obj->Size().moveTo(30, 120);

    _obj->Position().jumpTo(50, 5);
    _obj->Position().setTransitionPath(EasingPath::easeOutBack);
    _obj->Position().setDuration(500);
    _obj->Position().moveTo(30, 30);
}

void AppTestShit::onRunning()
{
    HAL::BtnUpdate();

    if (HAL::BtnOk().wasClicked()) {
        Vector2D_t new_shit;
        new_shit.x = math::getRandomInt(1, 114);
        new_shit.y = math::getRandomInt(1, 114);
        mclog::info("new shit: {} {}", new_shit.x, new_shit.y);
        _obj->Size().moveTo(new_shit);

        new_shit.x = math::getRandomInt(1, 114);
        new_shit.y = math::getRandomInt(1, 114);
        _obj->Position().moveTo(new_shit);
    }

    _obj->update();
    lv_timer_handler();
}

void AppTestShit::onClose()
{
    mclog::tagInfo(_tag, "on close");
}
