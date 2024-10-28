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

using namespace mooncake;
using namespace SmoothUIToolKit;
using namespace smooth_widget;

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

    // Create and setup watch face canvas
    _canvas = std::make_unique<SmoothWidgetBase>(lv_screen_active());
    _canvas->setBorderWidth(0);
    _canvas->setRadius(5);
    _canvas->setOutlineWidth(2);
    _canvas->setOutlineColor("#000000");
    _canvas->smoothPosition().setTransitionPath(EasingPath::easeOutBack);
    _canvas->smoothPosition().jumpTo(_canvas_start_up_x, _canvas_start_up_y);
    _canvas->smoothSize().setTransitionPath(EasingPath::easeOutBack);
    _canvas->smoothSize().jumpTo(_canvas_start_up_w, _canvas_start_up_h);

    // Create watch face ability
    _watch_face_ability_id = GetMooncake().createExtension(std::make_unique<WatchFaceAbility>());
    GetMooncake().getExtensionInstance<WatchFaceAbility>(_watch_face_ability_id)->init(_canvas->get());
}

void LauncherPageWatchFace::onShow()
{
    mclog::tagInfo(_tag, "on show");

    // Setup watch face canvas pop out anim
    _canvas->smoothPosition().setDelay(0);
    _canvas->smoothPosition().setDuration(800);
    _canvas->smoothPosition().moveTo(_canvas_x, _canvas_y);
    _canvas->smoothSize().setDuration(800);
    _canvas->smoothSize().setDelay(100);
    _canvas->smoothSize().moveTo(_canvas_w, _canvas_h);
    lv_obj_move_foreground(_canvas->get());

    // Resume watch face ability
    GetMooncake().extensionManager()->resumeWorkerAbility(_watch_face_ability_id);
}

void LauncherPageWatchFace::onForeground()
{
    if (isOnSubPage() && HAL::BtnPower().wasClicked()) {
        quitSubPage();
    }

    _canvas->updateSmoothing();
}

void LauncherPageWatchFace::onBackground()
{
    _canvas->updateSmoothing();
}

void LauncherPageWatchFace::onHide()
{
    mclog::tagInfo(_tag, "on hide");

    // Setup watch face canvas hide anim
    _canvas->smoothPosition().setDelay(100);
    _canvas->smoothPosition().setDuration(800);
    _canvas->smoothPosition().moveTo(_canvas_start_up_x, _canvas_start_up_y);
    _canvas->smoothSize().setDuration(800);
    _canvas->smoothSize().setDelay(0);
    _canvas->smoothSize().moveTo(_canvas_start_up_w, _canvas_start_up_h);
    lv_obj_move_background(_canvas->get());

    // Pause watch face ability
    GetMooncake().extensionManager()->pauseWorkerAbility(_watch_face_ability_id);
}

void LauncherPageWatchFace::onDestroy()
{
    mclog::tagInfo(_tag, "on destroy");
    GetMooncake().destroyExtension(_watch_face_ability_id);
}
