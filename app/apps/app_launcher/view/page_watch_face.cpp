/**
 * @file page_watch_face.cpp
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
#include <memory>
#include <mooncake_log.h>
#include <src/core/lv_obj_scroll.h>
#include <src/lv_api_map_v8.h>

using namespace mooncake;
using namespace SmoothUIToolKit;

static const char* _tag = "PageWatchFace";

static constexpr int _canvas_start_up_x = 150;
static constexpr int _canvas_start_up_y = 12;
static constexpr int _canvas_start_up_w = 20;
static constexpr int _canvas_start_up_h = 40;
static constexpr int _canvas_x = -4;
static constexpr int _canvas_y = -4;
static constexpr int _canvas_w = 152;
static constexpr int _canvas_h = 176;

void LauncherPageWatchFace::onShow()
{
    mclog::tagInfo(_tag, "on show");

    if (!_canvas) {
        _canvas = std::make_unique<smooth_lv_widgets::LvObj>(lv_obj_create(lv_screen_active()));
        _canvas->Position().setTransitionPath(EasingPath::easeOutBack);
        _canvas->Size().setTransitionPath(EasingPath::easeOutBack);
        _canvas->Position().jumpTo(_canvas_start_up_x, _canvas_start_up_y);
        _canvas->Size().jumpTo(_canvas_start_up_w, _canvas_start_up_h);
    }

    _canvas->Position().setDuration(600);
    _canvas->Size().setDuration(1000);
    _canvas->Position().moveTo(_canvas_x, _canvas_y);
    _canvas->Size().moveTo(_canvas_w, _canvas_h);
    lv_obj_move_foreground(_canvas->get());
}

void LauncherPageWatchFace::onForeground()
{
    if (isOnSubPage() && HAL::BtnPower().wasClicked()) {
        quitSubPage();
    }

    if (_canvas) {
        _canvas->update();
    }
}

void LauncherPageWatchFace::onBackground()
{
    if (_canvas) {
        _canvas->update();
    }
}

void LauncherPageWatchFace::onHide()
{
    mclog::tagInfo(_tag, "on hide");

    _canvas->Position().setDuration(600);
    _canvas->Size().setDuration(400);
    _canvas->Position().moveTo(_canvas_start_up_x, _canvas_start_up_y);
    _canvas->Size().moveTo(_canvas_start_up_w, _canvas_start_up_h);
    lv_obj_move_background(_canvas->get());
}
