/**
 * @file page_notification.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "page.h"
#include <hal/hal.h>
#include <mooncake_log.h>
#include <src/lv_api_map_v8.h>
#include <src/misc/lv_area.h>

using namespace mooncake;
using namespace SmoothUIToolKit;

static const char* _tag = "PageNotification";

static constexpr int _canvas_start_up_x = 0;
static constexpr int _canvas_start_up_y = -20;
static constexpr int _canvas_start_up_w = 52;
static constexpr int _canvas_start_up_h = 17;
static constexpr int _canvas_x = 0;
static constexpr int _canvas_y = 6;
static constexpr int _canvas_w = 132;
static constexpr int _canvas_h = 40;

void LauncherPageNotification::onCreate()
{
    _canvas_list.resize(4);
}

void LauncherPageNotification::onShow()
{
    mclog::tagInfo(_tag, "on show");

    int i = 0;
    for (auto& canvas : _canvas_list) {
        if (!canvas) {
            canvas = std::make_unique<smooth_lv_widgets::LvObj>(lv_obj_create(lv_screen_active()));
            canvas->setAlign(LV_ALIGN_TOP_MID);
            canvas->Position().setTransitionPath(EasingPath::easeOutBack);
            canvas->Size().setTransitionPath(EasingPath::easeOutBack);
            canvas->setRadius(16);
            canvas->Position().jumpTo(_canvas_start_up_x, _canvas_start_up_y);
            canvas->Size().jumpTo(_canvas_start_up_w, _canvas_start_up_h);
            lv_obj_move_background(canvas->get());
        }

        canvas->Position().setDelay(i * 30);
        canvas->Size().setDelay((_canvas_list.size() - i - 1) * 30);
        canvas->Position().setDuration(600);
        canvas->Size().setDuration(1000);
        canvas->Position().moveTo(_canvas_x, _canvas_y + i * 47);
        canvas->Size().moveTo(_canvas_w, _canvas_h);

        i++;
    }
}

void LauncherPageNotification::onForeground()
{
    if (isOnSubPage() && HAL::BtnPower().wasClicked()) {
        quitSubPage();
    }

    for (auto& canvas : _canvas_list) {
        if (canvas) {
            canvas->update();
        }
    }
}

void LauncherPageNotification::onBackground()
{
    for (auto& canvas : _canvas_list) {
        if (canvas) {
            canvas->update();
        }
    }
}

void LauncherPageNotification::onHide()
{
    mclog::tagInfo(_tag, "on hide");

    int i = 0;
    for (auto& canvas : _canvas_list) {
        canvas->Position().setDelay(i * 20);
        canvas->Size().setDelay(i * 20);
        canvas->Position().setDuration(600);
        canvas->Size().setDuration(400);
        canvas->Position().moveTo(_canvas_start_up_x, _canvas_start_up_y);
        canvas->Size().moveTo(_canvas_start_up_w, _canvas_start_up_h);

        i++;
    }
}
