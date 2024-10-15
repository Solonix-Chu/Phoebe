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
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_scroll.h>
#include <src/core/lv_obj_style_gen.h>
#include <src/display/lv_display.h>
#include <src/misc/lv_area.h>
#include <src/misc/lv_color.h>
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

    lv_obj_set_scrollbar_mode(lv_screen_active(), LV_SCROLLBAR_MODE_OFF);

    _obj = new LvObj(lv_obj_create(lv_screen_active()));
    _obj->Size().jumpTo(50, 5);
    _obj->Size().setTransitionPath(EasingPath::easeOutBack);
    _obj->Size().setDuration(500);
    _obj->Size().moveTo(30, 120);

    _obj->Position().jumpTo(50, 5);
    _obj->Position().setTransitionPath(EasingPath::easeOutBack);
    _obj->Position().setDuration(300);
    _obj->Position().moveTo(30, 30);

    _obj->setAlign(LV_ALIGN_CENTER);
    _obj->setScrollbarMode(LV_SCROLLBAR_MODE_OFF);
    _obj->setRadius(12);
    _obj->setBgColor(lv_color_black());
    _obj->setBorderWidth(0);
}

void AppTestShit::onRunning()
{
    HAL::BtnUpdate();

    if (HAL::BtnOk().wasClicked()) {
        Vector2D_t new_shit;
        new_shit.x = math::getRandomInt(20, 114);
        new_shit.y = math::getRandomInt(20, 114);
        mclog::info("new shit: {} {}", new_shit.x, new_shit.y);
        _obj->Size().moveTo(new_shit);

        new_shit.x = math::getRandomInt(-60, 60);
        new_shit.y = math::getRandomInt(-60, 60);
        _obj->Position().moveTo(new_shit);
    }

    if (HAL::BtnPower().wasClicked()) {
        mclog::info("bye");
        delete _obj;
        _obj = nullptr;
    }

    if (_obj) {
        _obj->update();
    }

    lv_timer_handler();
}

void AppTestShit::onClose()
{
    mclog::tagInfo(_tag, "on close");
}
