/**
 * @file page_widgets.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "core/easing_path/easing_path.h"
#include "page.h"
#include <hal/hal.h>
#include <mooncake_log.h>

using namespace mooncake;
using namespace SmoothUIToolKit;

static const char* _tag = "PageWidgets";

static constexpr int _canvas_start_up_x = 150;
static constexpr int _canvas_start_up_y = 64;
static constexpr int _canvas_start_up_w = 20;
static constexpr int _canvas_start_up_h = 40;
static constexpr int _canvas_x = 10;
static constexpr int _canvas_y = 10;
static constexpr int _canvas_w = 124;
static constexpr int _canvas_h = 68;

void LauncherPageWidgets::onCreate()
{
    _canvas_list.resize(2);
}

void LauncherPageWidgets::onShow()
{
    mclog::tagInfo(_tag, "on show");

    int i = 0;
    for (auto& canvas : _canvas_list) {
        if (!canvas) {
            canvas = std::make_unique<smooth_lv_widgets::LvObj>(lv_obj_create(lv_screen_active()));
            canvas->Position().setTransitionPath(EasingPath::easeOutBack);
            canvas->Size().setTransitionPath(EasingPath::easeOutBack);
            canvas->setRadius(16);
            canvas->Position().jumpTo(_canvas_start_up_x, _canvas_start_up_y + i * 52);
            canvas->Size().jumpTo(_canvas_start_up_w, _canvas_start_up_h);
        }

        canvas->Position().setDelay(i * 100);
        canvas->Size().setDelay(i * 100);
        canvas->Position().setDuration(600);
        canvas->Size().setDuration(1000);
        canvas->Position().moveTo(_canvas_x, _canvas_y + i * 80);
        canvas->Size().moveTo(_canvas_w, _canvas_h);

        i++;
    }
}

void LauncherPageWidgets::onForeground()
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

void LauncherPageWidgets::onBackground()
{
    for (auto& canvas : _canvas_list) {
        if (canvas) {
            canvas->update();
        }
    }
}

void LauncherPageWidgets::onHide()
{
    mclog::tagInfo(_tag, "on hide");

    int i = 0;
    for (auto& canvas : _canvas_list) {
        canvas->Position().setDelay((_canvas_list.size() - 1 - i) * 50);
        canvas->Size().setDelay((_canvas_list.size() - 1 - i) * 50);
        canvas->Position().setDuration(600);
        canvas->Size().setDuration(400);
        canvas->Position().moveTo(_canvas_start_up_x, _canvas_start_up_y + i * 52);
        canvas->Size().moveTo(_canvas_start_up_w, _canvas_start_up_h);

        i++;
    }
}
