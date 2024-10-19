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
static constexpr int _canvas_start_up_y = 121;
static constexpr int _canvas_start_up_w = 20;
static constexpr int _canvas_start_up_h = 40;
static constexpr int _canvas_x = 10;
static constexpr int _canvas_y = 10;
static constexpr int _canvas_w = 124;
static constexpr int _canvas_h = 68;

void LauncherPageWidgets::onShow()
{
    mclog::tagInfo(_tag, "on show");

    if (!_canvas) {
        _canvas = std::make_unique<smooth_lv_widgets::LvObj>(lv_obj_create(lv_screen_active()));
        _canvas->Position().setTransitionPath(EasingPath::easeOutBack);
        _canvas->Size().setTransitionPath(EasingPath::easeOutBack);
        _canvas->setRadius(16);
        _canvas->Position().jumpTo(_canvas_start_up_x, _canvas_start_up_y);
        _canvas->Size().jumpTo(_canvas_start_up_w, _canvas_start_up_h);
    }

    // _canvas->Position().setDelay(100);
    // _canvas->Size().setDelay(100);
    _canvas->Position().setDuration(600);
    _canvas->Size().setDuration(1000);
    _canvas->Position().moveTo(_canvas_x, _canvas_y);
    _canvas->Size().moveTo(_canvas_w, _canvas_h);
}

void LauncherPageWidgets::onForeground()
{
    if (isOnSubPage() && HAL::BtnPower().wasClicked()) {
        quitSubPage();
    }

    if (_canvas) {
        _canvas->update();
    }
}

void LauncherPageWidgets::onBackground()
{
    if (_canvas) {
        _canvas->update();
    }
}

void LauncherPageWidgets::onHide()
{
    mclog::tagInfo(_tag, "on hide");

    _canvas->Position().setDelay(0);
    _canvas->Size().setDelay(0);
    _canvas->Position().setDuration(600);
    _canvas->Size().setDuration(400);
    _canvas->Position().moveTo(_canvas_start_up_x, _canvas_start_up_y);
    _canvas->Size().moveTo(_canvas_start_up_w, _canvas_start_up_h);
}
