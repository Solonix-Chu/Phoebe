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
#include "../../utils/watch_face_ability/watch_face_ability.h"
#include <hal/hal.h>
#include <memory>
#include <mooncake_log.h>
#include <utility>

using namespace mooncake;
using namespace SmoothUIToolKit;

static const char* _tag = "PageWatchFace";

static constexpr int _canvas_start_up_x = 150;
static constexpr int _canvas_start_up_y = 32;
static constexpr int _canvas_start_up_w = 20;
static constexpr int _canvas_start_up_h = 40;
static constexpr int _canvas_x = 0;
static constexpr int _canvas_y = 0;
static constexpr int _canvas_w = 144;
static constexpr int _canvas_h = 168;

void LauncherPageWatchFace::onCreate()
{
    mclog::tagInfo(_tag, "on create");

    _canvas = std::make_unique<smooth_lv_widgets::LvObj>(lv_obj_create(lv_screen_active()));
    _canvas->setBorderWidth(0);
    _canvas->setRadius(5);
    lv_obj_set_style_outline_width(_canvas->get(), 2, LV_PART_MAIN);
    lv_obj_set_style_outline_color(_canvas->get(), lv_color_black(), LV_PART_MAIN);
    _canvas->Position().setTransitionPath(EasingPath::easeOutBack);
    _canvas->Size().setTransitionPath(EasingPath::easeOutBack);
    _canvas->Position().jumpTo(_canvas_start_up_x, _canvas_start_up_y);
    _canvas->Size().jumpTo(_canvas_start_up_w, _canvas_start_up_h);

    _watch_face_ability_id = GetMooncake().createExtension(std::make_unique<WatchFaceAbility>());
    GetMooncake().getExtensionInstance<WatchFaceAbility>(_watch_face_ability_id)->init(_canvas->get());
}

void LauncherPageWatchFace::onShow()
{
    mclog::tagInfo(_tag, "on show");

    _canvas->Position().setDuration(800);
    _canvas->Position().setDelay(0);
    _canvas->Size().setDuration(800);
    _canvas->Size().setDelay(100);
    _canvas->Position().moveTo(_canvas_x, _canvas_y);
    _canvas->Size().moveTo(_canvas_w, _canvas_h);
    lv_obj_move_foreground(_canvas->get());

    GetMooncake().extensionManager()->resumeWorkerAbility(_watch_face_ability_id);
}

void LauncherPageWatchFace::onForeground()
{
    if (isOnSubPage() && HAL::BtnPower().wasClicked()) {
        quitSubPage();
    }

    _canvas->update();
}

void LauncherPageWatchFace::onBackground()
{
    _canvas->update();
}

void LauncherPageWatchFace::onHide()
{
    mclog::tagInfo(_tag, "on hide");

    _canvas->Position().setDuration(800);
    _canvas->Position().setDelay(100);
    _canvas->Size().setDuration(800);
    _canvas->Size().setDelay(0);
    _canvas->Position().moveTo(_canvas_start_up_x, _canvas_start_up_y);
    _canvas->Size().moveTo(_canvas_start_up_w, _canvas_start_up_h);
    lv_obj_move_background(_canvas->get());

    GetMooncake().extensionManager()->pauseWorkerAbility(_watch_face_ability_id);
}

void LauncherPageWatchFace::onDestroy()
{
    mclog::tagInfo(_tag, "on destroy");
    GetMooncake().destroyExtension(_watch_face_ability_id);
}